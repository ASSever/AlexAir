#include <iostream>
using namespace std;
struct X;
void f(X& x, int n);

struct X
{
	X()
	{
		try
		{
			f(*this, -1);
			cout<<", "<<1;
		}
		catch(X){  cout<<", "<<2; }
		catch(int ){  cout<<", "<<3;}
	}
	X(X&){  cout<<", "<<4; }
	~X(){  cout<<", "<<5; }
};
struct Y:X
{
	Y()
	{
		f(*this, -1);
		cout<<", "<<6;
	}
	Y(Y&){  cout<<", "<<7; }
	~Y(){  cout<<", "<<8; }
};
void f(X&x,int n)
{
	try
	{
		if (n<0)
			throw x;
		if (n>0)
			throw 1;
		cout<<", "<<9;
	}
	catch(int ){cout<<", "<<10;}
	catch(X&a )
	{
		cout<<", "<<11;
		f(a,1);
		cout<<", "<<12;
		throw;
	}

}
int main()
{
	try
	{
		Y a;
	}
	catch(...){cout<<", "<<13;return 0;}
	cout<<", "<<14;return 0;
}
//вывод
//4, 11, 10, 12, 4, 2, 5, 5, 4, 11, 10, 12, 5, 13, 5
//4, 11, 10, 12, 2, 5, 4, 11, 10, 12, 5, 13, 5
