#include <iostream>
using namespace std;
class Circle
{
public:
	double x;
	double y;
	double r;
	static int circle_count;
	Circle(double x=1, double y=1, double r=1):x(x),y(y),r(r)
	{
		circle_count +=1;
	}
	~Circle()
	{
		circle_count -=1;
	}
	int Circle_count()  {return circle_count;}
	void virtual print(int x=1)
	{
		if(x)
			cout<<"Круг:"<<endl;
		cout<<"Центр в точке: ("<<this->x<<", "<<this->y<<");"<<endl;
		cout<<"Радиус: "<<this->r<<";"<<endl;
	}
	void virtual Multiply(double x)
	{
		this->r *= x;
	}
	double virtual Square()
	{
		return 3.14*(this->r)*(this->r);
	}
};
class Ring: public Circle
{
public:
	double rS;//small
	static int ring_count;

	Ring(double x=1,double y=1, double r=1, double rS = 0):Circle(x,y,r),rS(rS)
	{
		try
		{
			if (r<rS)
				throw 1;
		}
		catch(int ){this->rS = r;}
		circle_count -=1;
		ring_count +=1;
	}
	~Ring()
	{
		ring_count -=1;
	}
	int Ring_count(){return ring_count;}
	void print(int x = 1)
	{
		if (x)
			cout<<"Кольцо:"<<endl;
		cout<<"Центр в точке: ("<<this->x<<", "<<this->y<<");"<<endl;
		cout<<"Радиус: "<<this->r<<";"<<endl;
		cout<<"Внутренний радиус: "<<this->rS<<";"<<endl;
	}
	void Multiply(double x)
	{
		this->r *= x;
		this->rS *= x;
	}
	double Square()
	{
		return 3.14*((this->r)*(this->r)-(this->rS)*(this->rS));
	}
};
class F
{
public:
	int d;
	F(double d=3):d(d){};
	Circle& operator()(Circle&x) const 
	{
		x.Multiply(this->d);
		return x;
	}

};
void ptr_to(Circle* x)
{

	cout<<typeid(*x).name()<<endl;
}
int Circle::circle_count=0;
int Ring::ring_count=0;
int main()
{
	Circle c1, c(1,2,5);
	Ring r1, r(1,2,5,6);
	c1.print();
	c.print();
	r1.print();
	r.print();
	cout<<r.Ring_count()<<" "<<r1.Ring_count()<<" "<<c.Circle_count()<<" "<<c1.Circle_count()<<endl;
	ptr_to(&c);
	ptr_to(&r);
	c1.Multiply(2);
	r.Multiply(3);
	c1.print();
	c.print();
	r1.print();
	r.print();
	cout<<r.Square()<<" "<<r1.Square()<<" "<<c.Square()<<" "<<c1.Square()<<endl;
	F x;
	x(c);
	x(r);
	c.print();
	r.print();

	return 0;
}