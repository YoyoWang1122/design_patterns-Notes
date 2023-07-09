#include <iostream>
#include <mutex>
#include <atomic>
using namespace std;
//原子变量：指定程序的执行顺序，解决双检锁底层存在的有地址无数据的问题
class Singleton {
public:
	//防止其他地方构造新的单例类
	//Singleton() = delete;
	Singleton(const Singleton& instance) = delete;
	Singleton& operator = (const Singleton& instance) = delete;
	static Singleton* getInstance()
	{
		shared_ptr<Singleton> instance = m_instance.load();
		if (instance.get() == nullptr)//解决加了锁后效率低下的问题
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
		cout << "这是单例模式类——原子变量" << endl;
	}

private:
	//防止其他地方构造新的单例类
	Singleton() = default;//因为静态成员变量只能在类外进行初始化，所以必须使用默认的构造函数
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