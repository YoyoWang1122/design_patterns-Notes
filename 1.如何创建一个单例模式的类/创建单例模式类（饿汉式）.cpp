#include <iostream>
using namespace std;
//饿汉式：定义类的时候创建单例对象
class Singleton {
public:
	//防止其他地方构造新的单例类
	//Singleton() = delete;
	Singleton(const Singleton& instance) = delete;
	Singleton& operator = (const Singleton& instance) = delete;
	static Singleton* getInstance()
	{
		return m_instance.get();
	}
	void print()
	{
		cout << "这是单例模式类——饿汉式" << endl;
	}

private:
	//防止其他地方构造新的单例类
	Singleton() = default;//因为静态成员变量只能在类外进行初始化，所以必须使用默认的构造函数
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