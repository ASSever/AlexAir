#include <iostream>
//<stdio.h>
//<cstdio>
using namespace std;
//using namespase A {int x;...}

int Ga;//глобальная переменная
int x;
struct B1{};
class B {
//private:
	int a;
public:
	void setA(int x);
	int geA() const {return a;};

	//B(int ca, int cb){a = ca; b = cb;}
	//не могут одновременно существовать
	B(int ca, int cb=1){a = ca; b = cb;}
	//B(int ca)
	//более быстрый метод инициализации
	//B(int ca, int cb=1):a(ca),b(cb){}


	//конструктор копирования
	//по умолчанию копирует выделенную под бьект память
	B(const B&x){a=x.a; b = x.b;}


//переопределили(перегрузили) операцию равно в классе  X
	B& operator=(const B&x);

};
void B::set(int x){
	a = x;
	//this->a = x;
	return;
}

	B&B::& operator=(const B&x){
	a = x.a; b=x.b; return *this;

	};

// void f(int &x){x+=1;}
// int &g(int ar[], int n){return ar[n];}
//int main(){int x= 1; f(x); cout<<x;}//2








class Str{
private:
	int l;
	char *str;
public:
	Str()
	Str(const char * s)
	Str(const Str & s)
	Str & operator=(const&x);

}, ~Str()

Str::Str(const char *str){
	str = new char [strlen(s)+1];
	strcpy(str,s)
	l=strlen(s);
}

Str::Str(){
l=0;
str = new char[1];
str[0]='\0'

}

Str::Str(const Str&s){
	str= new char [s.l+1];
	l=s.l;
	strcpy(s.str,str);
}

Str&Str:: operator=(const Str&x){
	if (this != &x)
	{
		delete [] this->str;
		this->str = new char
	}
}

int main(){

Str s1("c++");
// 	B peremennaya;
// 	B obj1, obj2;

// 	//копирование
// 	B obj3(obj1);


// 	B(1,2);


// 	// std::cout<<x;
// 	// std::cout<<::x; //глобальный х
// 	// std::cout<<A::x; // х из A
// 	// std::cin>>x

// 	int x = 5;
// 	int &r = x;
// 	x++;
// 	//одно и тоже
// 	r++;

}

/*
//класс Pub унаследовал класс Parent
class Pub: public Parent
поля класса Parent
были public   	стали -> public
были private  	стали -> недоступны
были protected	стали -> protected

//класс Pub унаследовал класс Parent
class Pub: private Parent
поля класса Parent
были public   	стали -> private
были private  	стали -> недоступны
были protected	стали -> private


//класс Pub унаследовал класс Parent
class Pub: protected Parent
поля класса Parent
были public   	стали -> protected
были private  	стали -> недоступны
были protected	стали -> protected

*/

