#include <iostream>


//抽象类
class calculate {
public:
	virtual void SetNumber(int a, int b) = 0;
	virtual int GetResult() = 0;
};

//加法
class plus :public calculate {
public:
	virtual void SetNumber(int a, int b)
	{
		this->m_a = a;
		this->m_b = b;
	}

	virtual int GetResult()
	{
		return m_a + m_b;
	}

private:
	int m_a;
	int m_b;
};

//减法
class minute :public calculate {
public:
	virtual void SetNumber(int a, int b)
	{
		this->m_a = a;
		this->m_b = b;
	}

	virtual int GetResult()
	{
		return m_a - m_b;
	}

private:
	int m_a;
	int m_b;
};

void test()
{
	std::shared_ptr<calculate> cal = std::make_shared<plus>();
	int a = 0;
	int b = 0;
	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;
	cal->SetNumber(a, b);
	std::cout << "res = " << cal->GetResult() << std::endl;

}

int main()
{

	test();

	return 0;

}

