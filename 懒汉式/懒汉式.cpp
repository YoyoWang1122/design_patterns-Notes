#include <iostream>
using namespace std;
//����ʽ����Ҫ��ʱ��Ŷ��嵥������
class Singleton {
public:
	//��ֹ�����ط������µĵ�����
	//Singleton() = delete;
	Singleton(const Singleton& instance) = delete;
	Singleton& operator = (const Singleton& instance) = delete;
	static Singleton* getInstance()
	{
		if (m_instance.get() == nullptr)
		{
			//m_instance = make_shared<Singleton>();
			//m_instance = new Singleton;
			m_instance.reset(new Singleton);
		}
		return m_instance.get();
	}
	void print()
	{
		cout << "���ǵ���ģʽ�ࡪ������ʽ" << endl;
	}

private:
	//��ֹ�����ط������µĵ�����
	Singleton() = default;//��Ϊ��̬��Ա����ֻ����������г�ʼ�������Ա���ʹ��Ĭ�ϵĹ��캯��
	/*Singleton(const Singleton& instance) = default;
	Singleton& operator = (const Singleton& instance) = default;*/

	static shared_ptr<Singleton> m_instance;
	//static Singleton* m_instance;

};

shared_ptr<Singleton> Singleton::m_instance = nullptr;
//Singleton* Singleton::m_instance = nullptr;


int main()
{
	Singleton* test = Singleton::getInstance();
	test->print();
	return 0;

}