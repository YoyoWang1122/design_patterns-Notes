#include <iostream>
#include <mutex>
using namespace std;
//˫�������������ʽ�̰߳�ȫ����
class Singleton {
public:
	//��ֹ�����ط������µĵ�����
	//Singleton() = delete;
	Singleton(const Singleton& instance) = delete;
	Singleton& operator = (const Singleton& instance) = delete;
	static Singleton* getInstance()
	{
		if (m_instance.get() == nullptr)//�����������Ч�ʵ��µ�����
		{
			m_mutex.lock();
			if (m_instance.get() == nullptr)
			{
				m_instance.reset(new Singleton);
			}
			m_mutex.unlock();
		}
		return m_instance.get();
	}
	void print()
	{
		cout << "���ǵ���ģʽ�ࡪ��˫����" << endl;
	}

private:
	//��ֹ�����ط������µĵ�����
	Singleton() = default;//��Ϊ��̬��Ա����ֻ����������г�ʼ�������Ա���ʹ��Ĭ�ϵĹ��캯��
	/*Singleton(const Singleton& instance) = default;
	Singleton& operator = (const Singleton& instance) = default;*/

	static shared_ptr<Singleton> m_instance;
	static mutex m_mutex;

};

shared_ptr<Singleton> Singleton::m_instance = nullptr;
mutex Singleton::m_mutex;

int main()
{
	Singleton* test = Singleton::getInstance();
	test->print();
	return 0;

}