#include <iostream>
using namespace std;
//懒汉式：需要的时候才定义单例对象
class Singleton {
public:
	//防止其他地方构造新的单例类
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
		cout << "这是单例模式类——懒汉式" << endl;
	}

private:
	//防止其他地方构造新的单例类
	Singleton() = default;//因为静态成员变量只能在类外进行初始化，所以必须使用默认的构造函数
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