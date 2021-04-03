#include <iostream>
using namespace std;
//обработка ошибок
class A
{
public:
A()
{
	try
	{
		throw 1;
	}
	catch(int ){  /*что-то (какаято обработка)*/ }
};
	
};
class B
{
public:
	B()
	{
		throw 2;
	}
	
};
class E
{
public:
	int e;
};
class E1
{
public:
	int e;
};
class E2: public Exeption
{

}
//почитать об этом
//exeption
//bab_alloc
//bad_cast
//const_cast
//reinterpret_cast // для опасных преобразований между какими-то там указателями
//bad_typeid
//logic_error
//(очень непонятно пояснила)
{
public:
	int e;
};

void main()
{
	try
	{A a1;

		try
		{
			A a;
			B b;
			E1 x;
			x.e = s;
			x.e1 = 10;
			throw x;
		}
		catch(E e){e.e = 8; throw;//(*)//throw e;(**)}

	}
	catch(E1&e){/*что-то (какаято обработка)*/}
	catch(E&e){/*что-то (какаято обработка)*/cout<<ewwbwrtbqerv}
	catch(int)//сработает при создании обьекта класса B
	catch(...){}//перехватывает все
	//поиск перехватчика происходит сверху вниз
	/*
	если напрмер есть класс E:E2

	и есть catch который ловит обьект класса E
	а потом есть catch который ловит E1

	то второй никогда не выполнится ибо даже есть произойдет throw обьекта класса Е1 то его поймает первый throw 
	поэтому надо в начале писать catch класса производного
	а потом catch базового класса

	*/
}

/*
что в каком порядке вызывается в данной проге
A()
A()
B()
E()
E1()
E(const E&)
E1(const E1&)
~E1(), ~E(), ~B(), ~A() 
E(const)
(*): ~E()
	 ~A()
	 ~E1()
	 ~E()
	 cout<<ewwbwrtbeqver
(**): E(const E&)
	  ~E1()
	  ~E()
	  ~E()
	  ~A()
	  ~E()
	  cout<<ewwbwrtbeqver
*/


