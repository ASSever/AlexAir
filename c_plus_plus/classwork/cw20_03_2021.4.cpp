#include <iostream>
#include <typeinfo>//если понадобится структура type info
using namespace std;
struct A
{
	int x;
	virtual void z(){}
};
struct B:A
{
	int x;
};
struct C:B
{
	int x;
	C(int n=4):x(n){}
};
C* f(B&rb);

C* f(B&rb)
{
	C * pc = dynamic_cast<C*>(&rb);
	if (pc) 
		return pc;
	else 
		exit(0);
}
/*
//др вариант
C* f(B&rb)
{
	try
	{
		C * pc = dynamic_cast<C&>(rb);
		return &pc;
	}
	catch(bad_cast)
	{
		exit(0);
	}
}
*/
int main()
{
	C c, *pc=f(c);
	cout<<pc->x;
	pc->x=88;
	cout<<pc->x;
	B b, *pb = f(b);
	cout<<pb->x;
	return 0;
}
