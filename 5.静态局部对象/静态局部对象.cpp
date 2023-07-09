#include <iostream>
using namespace std;
//静态局部变量：解决线程安全问题，编译器必须支持C++11(如果指令进入一个未被初始化的变量，所有并发执行应当等待该变量初始化完成）
class Singleton {
public:
	//防止其他地方构造新的单例类
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
		cout << "这是单例模式类——静态局部变量" << endl;
	}

private:
	//防止其他地方构造新的单例类
	Singleton() = default;//因为静态成员变量只能在类外进行初始化，所以必须使用默认的构造函数
	/*Singleton(const Singleton& instance) = default;
	Singleton& operator = (const Singleton& instance) = default;*/


};


int main()
{
	Singleton* test = Singleton::getInstance();
	test->print();
	return 0;

}