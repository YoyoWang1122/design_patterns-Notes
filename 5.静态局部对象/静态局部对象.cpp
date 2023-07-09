#include <iostream>
using namespace std;
//��̬�ֲ�����������̰߳�ȫ���⣬����������֧��C++11(���ָ�����һ��δ����ʼ���ı��������в���ִ��Ӧ���ȴ��ñ�����ʼ����ɣ�
class Singleton {
public:
	//��ֹ�����ط������µĵ�����
	//Singleton() = delete;
	Singleton(const Singleton& instance) = delete;
	Singleton& operator = (const Singleton& instance) = delete;
	static Singleton* getInstance()
	{
		static Singleton instance;
		return &instance;
	}
	void print()
	{
		cout << "���ǵ���ģʽ�ࡪ����̬�ֲ�����" << endl;
	}

private:
	//��ֹ�����ط������µĵ�����
	Singleton() = default;//��Ϊ��̬��Ա����ֻ����������г�ʼ�������Ա���ʹ��Ĭ�ϵĹ��캯��
	/*Singleton(const Singleton& instance) = default;
	Singleton& operator = (const Singleton& instance) = default;*/


};


int main()
{
	Singleton* test = Singleton::getInstance();
	test->print();
	return 0;

}