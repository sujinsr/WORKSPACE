#include <iostream>

class Base
{
public:
	int m_base;

	Base(int val = 0) : m_base(val)
	{
		std::cout << "Base constructor" << std::endl;
	}
};

class Derived : public Base
{
public:
	int m_derived;
	
	Derived(int val1 = 0, int val2 = 0) 
		: m_derived(val2), Base(val1)
	{
		std::cout << "Derived constructor" << std::endl;
	}
	
	Derived() { m_derived = 0; }
};

int main()
{
	Derived obj(1000, 2000);
	std::cout << obj.m_base << std::endl;	
	std::cout << obj.m_derived << std::endl;	
	return 0;
}
	
