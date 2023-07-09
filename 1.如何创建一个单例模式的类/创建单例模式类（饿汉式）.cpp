#include <iostream>
using namespace std;
//����ʽ���������ʱ�򴴽���������
class Singleton {
public:
	//��ֹ�����ط������µĵ�����
	//Singleton() = delete;
	Singleton(const Singleton& instance) = delete;
	Singleton& operator = (const Singleton& instance) = delete;
	static Singleton* getInstance()
	{
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

	//static Singleton* m_instance;
	static shared_ptr<Singleton> m_instance;

};

//Singleton* Singleton::m_instance = new Singleton();
shared_ptr<Singleton> Singleton::m_instance(new Singleton);// = make_shared<Singleton>();


int main()
{
	Singleton* test = Singleton::getInstance();
	test->print();
	return 0;

}