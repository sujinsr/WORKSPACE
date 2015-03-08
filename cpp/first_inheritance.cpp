#include <iostream>

class Person
{
public:
	std::string m_name;
	int 		m_age;
	bool		m_isMale;

	std::string getname()
	{
		return m_name;
	}
	
	int getage()
	{
		return m_age;
	}

	bool isMale()
	{
		return m_isMale;
	}

	Person(std::string name = "", int age = 0, bool ismale = true)
		: m_name(name), m_age(age), m_isMale(ismale)
	{
		std::cout << "Person constructor\n";
	}
};

class Cricketer : public Person
{
public:
	double	m_avg;
	long	m_totRuns;

	void display_cricketer();

	Cricketer(double avg=11.0, long runs = 324)
		: m_avg(avg), m_totRuns(runs)
	{
		std::cout << "Cricketer constructor\n";
	}

};

class Umpire : public Cricketer
{
public:
	int no_testmatch;
	int no_odimatch;
	
	Umpire(int test, int odi)
		: no_testmatch(test), no_odimatch(odi)
	{
		std::cout << "Umpire constructor\n";
	}
	
	void display_umpire()
	{
		display_cricketer();
		std::cout << "Test	: " << no_testmatch << std::endl;
		std::cout << "ODI	: " << no_odimatch << std::endl;
	}
};

void Cricketer::display_cricketer()
{
	std::cout << "Name	: " << m_name << std::endl;
	std::cout << "Age	: " << m_age << std::endl;
	std::cout << "Sex	: " << ((m_isMale == true) ? "Male" : "Female") << std::endl;
	std::cout << "Runs	: " << m_totRuns << std::endl;
	std::cout << "Avg	: " << m_avg << std::endl;
}



int main()
{
	Cricketer opener(55.6, 432);
	opener.m_name = "sachin";
	opener.m_age = 40;
	std::cout << "Call display member function for player " << opener.m_name << std::endl << std::endl;
	opener.display_cricketer();

	std::cout << "------------------------------------------------------------------\n";

	Umpire dravid(24, 85);
	dravid.m_name = "Rahul Dravid";
	dravid.m_age = 41;
	dravid.m_avg = 35.44;
	dravid.m_totRuns = 8054;
	dravid.display_umpire();
	
	return 0;
}
