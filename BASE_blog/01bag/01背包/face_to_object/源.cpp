#include<iostream>
using namespace std;


class d
{
public:
	int show();
	
};
class Person
{
private :
	int age=10;
	char gender;
public:
	int num;
	char male;
	friend int d::show();
protected:
	int n;
	char m;
};

int d::show()
{
	Person per=Person();
	cout << per.age << endl;
	return 0;
}
/*
  1. ���ܼ̳з�ʽ��� private �ֶβ��ܱ��̳�

  2.�ڼ̳��� protected�ڵ��ֶεȼ��� public
*/
class Son : public Person
{
public :
	void show()
	{
		//age  no
		//gender  no

		// num  yes
		//male  yes

		//n  yes
	}
};

class son : protected Person
{
public:
	void show()
	{
		//age no

		//num  yes

		//n yes
	}
};

class w :private Person
{
public:

	void show()
	{
		//age no

		// num yes

		//n  yes
	}
};

int main()
{
	cout << "hello admin" << endl;
	d d1=d();
	d1.show();
}

