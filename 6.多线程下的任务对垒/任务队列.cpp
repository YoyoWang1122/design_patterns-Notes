#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
using namespace std;
//���ڶ���ʽ�������
class Singleton_TaskQueue {
public:
	//��ֹ�����ط������µĵ�����
	//Singleton_TaskQueue() = delete;
	Singleton_TaskQueue(const Singleton_TaskQueue& instance) = delete;
	Singleton_TaskQueue& operator = (const Singleton_TaskQueue& instance) = delete;
	static Singleton_TaskQueue* getInstance()
	{
		return m_instance.get();
	}
	void print()
	{
		cout << "���ǵ���ģʽ�ࡪ���������" << endl;
	}

	//�ж���������Ƿ�Ϊ��

	bool isEmpty()
	{
		lock_guard<mutex> locker(m_mutex);//lock_guard�Զ�������ֹ����
		return m_data.empty();
	}
	
	//�������

	void addTask( int node )
	{
		lock_guard<mutex> locker(m_mutex);//lock_guard�Զ�������ֹ����
		m_data.push(node);
		cout << "Push Data:" << node << "   threadID: " << this_thread::get_id() << endl;
	}

	//ɾ������

	bool popTask()
	{
		lock_guard<mutex> locker(m_mutex);//lock_guard�Զ�������ֹ����
		if(m_data.empty())
		{
			return false;
		}
		m_data.pop();
		return true;
	}

	//ȡ��һ������

	int getTask()
	{
		lock_guard<mutex> locker(m_mutex);//lock_guard�Զ�������ֹ����
		if (m_data.empty())
		{
			return -1;
		}
		cout << "getTask:" << m_data.front() << "   threadID: " << this_thread::get_id() << endl;
		return m_data.front();
	}

private:
	//��ֹ�����ط������µĵ�����
	Singleton_TaskQueue() = default;//��Ϊ��̬��Ա����ֻ����������г�ʼ�������Ա���ʹ��Ĭ�ϵĹ��캯��
	/*Singleton_TaskQueue(const Singleton& instance) = default;
	Singleton_TaskQueue& operator = (const Singleton& instance) = default;*/

	//static Singleton* m_instance;
	static shared_ptr<Singleton_TaskQueue> m_instance;

	queue<int> m_data;
	mutex m_mutex;

};

//Singleton* Singleton::m_instance = new Singleton();
shared_ptr<Singleton_TaskQueue> Singleton_TaskQueue::m_instance(new Singleton_TaskQueue);// = make_shared<Singleton>();


int main()
{
	Singleton_TaskQueue* test = Singleton_TaskQueue::getInstance();
	test->print();

	//������
	thread t1([=]()
		{
			for (size_t i = 0; i < 100; i++)
			{
				test->addTask(i + 100);
				
				this_thread::sleep_for(chrono::microseconds(5000));
			}
		});
	

	//������
	thread t2([=]()
		{
			this_thread::sleep_for(chrono::microseconds(1000));
			while(!test->isEmpty())
			{
				
				test->getTask();
				test->popTask();
				this_thread::sleep_for(chrono::microseconds(7000));
			}
		});

	t1.join();
	t2.join();

	return 0;

}