#include <iostream>
#include <mutex>
#include <atomic>
using namespace std;
//ԭ�ӱ�����ָ�������ִ��˳�򣬽��˫�����ײ���ڵ��е�ַ�����ݵ�����
class Singleton {
public:
	//��ֹ�����ط������µĵ�����
	//Singleton() = delete;
	Singleton(const Singleton& instance) = delete;
	Singleton& operator = (const Singleton& instance) = delete;
	static Singleton* getInstance()
	{
		shared_ptr<Singleton> instance = m_instance.load();
		if (instance.get() == nullptr)//�����������Ч�ʵ��µ�����
		{
			m_mutex.lock();
			instance = m_instance.load();
			if (instance.get() == nullptr)
			{
				instance.reset(new Singleton);
				m_instance.store(instance);
			}
			m_mutex.unlock();
		}
		return instance.get();
	}
	void print()
	{
		cout << "���ǵ���ģʽ�ࡪ��ԭ�ӱ���" << endl;
	}

private:
	//��ֹ�����ط������µĵ�����
	Singleton() = default;//��Ϊ��̬��Ա����ֻ����������г�ʼ�������Ա���ʹ��Ĭ�ϵĹ��캯��
	/*Singleton(const Singleton& instance) = default;
	Singleton& operator = (const Singleton& instance) = default;*/

	//static shared_ptr<Singleton> m_instance;
	static atomic<shared_ptr<Singleton>> m_instance;
	static mutex m_mutex;

};
//shared_ptr<Singleton> Singleton::m_instance = nullptr;
atomic<shared_ptr<Singleton>> Singleton::m_instance;
mutex Singleton::m_mutex;

int main()
{
	Singleton* test = Singleton::getInstance();
	test->print();
	return 0;

}