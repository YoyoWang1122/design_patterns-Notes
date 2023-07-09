#include <iostream>
#include <mutex>
using namespace std;
//双检锁：解决懒汉式线程安全问题
class Singleton {
public:
	//防止其他地方构造新的单例类
	//Singleton() = delete;
	Singleton(const Singleton& instance) = delete;
	Singleton& operator = (const Singleton& instance) = delete;
	static Singleton* getInstance()
	{
		if (m_instance.get() == nullptr)//解决加了锁后效率低下的问题
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
		cout << "这是单例模式类——双检锁" << endl;
	}

private:
	//防止其他地方构造新的单例类
	Singleton() = default;//因为静态成员变量只能在类外进行初始化，所以必须使用默认的构造函数
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