#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
using namespace std;
//基于饿汉式任务对列
class Singleton_TaskQueue {
public:
	//防止其他地方构造新的单例类
	//Singleton_TaskQueue() = delete;
	Singleton_TaskQueue(const Singleton_TaskQueue& instance) = delete;
	Singleton_TaskQueue& operator = (const Singleton_TaskQueue& instance) = delete;
	static Singleton_TaskQueue* getInstance()
	{
		return m_instance.get();
	}
	void print()
	{
		cout << "这是单例模式类——任务对列" << endl;
	}

	//判断任务对列是否为空

	bool isEmpty()
	{
		lock_guard<mutex> locker(m_mutex);//lock_guard自动管理，防止死锁
		return m_data.empty();
	}
	
	//添加任务

	void addTask( int node )
	{
		lock_guard<mutex> locker(m_mutex);//lock_guard自动管理，防止死锁
		m_data.push(node);
		cout << "Push Data:" << node << "   threadID: " << this_thread::get_id() << endl;
	}

	//删除任务

	bool popTask()
	{
		lock_guard<mutex> locker(m_mutex);//lock_guard自动管理，防止死锁
		if(m_data.empty())
		{
			return false;
		}
		m_data.pop();
		return true;
	}

	//取出一个任务

	int getTask()
	{
		lock_guard<mutex> locker(m_mutex);//lock_guard自动管理，防止死锁
		if (m_data.empty())
		{
			return -1;
		}
		cout << "getTask:" << m_data.front() << "   threadID: " << this_thread::get_id() << endl;
		return m_data.front();
	}

private:
	//防止其他地方构造新的单例类
	Singleton_TaskQueue() = default;//因为静态成员变量只能在类外进行初始化，所以必须使用默认的构造函数
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

	//生产者
	thread t1([=]()
		{
			for (size_t i = 0; i < 100; i++)
			{
				test->addTask(i + 100);
				
				this_thread::sleep_for(chrono::microseconds(5000));
			}
		});
	

	//消费者
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