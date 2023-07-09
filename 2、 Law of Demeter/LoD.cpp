#include <iostream>
#include <string>

//抽象类
class Abstruct {
public:
	virtual void Setquality() = 0;
	virtual void Sale() = 0;
};

//高品质
class Buuilding_High_quality :public Abstruct {
public:
	virtual void Setquality()
	{
		this->m_quality = "High_quality";
	}

	virtual void Sale()
	{
		if (m_quality == "High_quality")
		{
			std::cout << "We have saled a high quality building!" << std::endl;
		}
		
	}

private:
	std::string m_quality;
};

//低品质
class Buuilding_Low_quality :public Abstruct {
public:
	virtual void Setquality()
	{
		this->m_quality = "Low_quality";
	}

	virtual void Sale()
	{
		if (m_quality == "Low_quality")
		{
			std::cout << "We have saled a high quality building!" << std::endl;
		}
		
	}

private:
	std::string m_quality;
};

void Low_quality()
{
	std::shared_ptr<Abstruct> cal = std::make_shared<Buuilding_Low_quality>();
	cal->Setquality();
	cal->Sale();
}

void High_quality()
{
	std::shared_ptr<Abstruct> cal = std::make_shared<Buuilding_High_quality>();
	cal->Setquality();
	cal->Sale();
}

int main()
{

	Low_quality();
	High_quality();

	return 0;

}

