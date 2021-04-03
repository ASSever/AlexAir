#include <iostream>
using namespace std;
struct B{
	int b;
	B(int x=0):b(x){}
	virtual void func(){cout<<"f_B";}
	virtual void h(double)=0;
};
struct T{
	int a;
	T(int x=1):a(x){}
	T& operator++() { //preincrement
		(this->a)++;
		return *this;
	}
	 
	T operator++(int) { //postincrement
		T t(*this);
		++(this->a);
		return t;
	}
};
class D:B{
virtual void h(double){};
public:

};
class C:B{
virtual void h(double){};
public:

};
class P{
public:
	T* t;
	P(T*t=NULL):t(t){};
	T operator*() {
  	return *(this->t);
	}
};
int main(){
	D d;
	C c;
	B* pb=&d, *pb1=&c;
	pb->func();
	pb1->func();
	T t;
	P p(&t);
	(*p).a=28;
	cout<<t.a<<endl;
	P p1(NULL);
	cout<<(*p1).a<<endl;
	t++;
	++t;
	return 0;
}