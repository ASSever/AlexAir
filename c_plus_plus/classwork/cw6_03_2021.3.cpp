class B
{
public:
	// virtual void f();
	// virtual void f2();
	// virtual void f3() const;
	// void f4() const;
	// void f5();
	// virtual void f6();
	// virtual void f7(B* x);
	// virtual void f8();
	// virtual void f8_1(double);
	// private void f9();
	// public virtual void f10();
	// virtual int f11(int a = 5,int b = 5);
};
class D:public/*protected*/ B
{
public:
	// virtual int f();//err
	// virtual int f2() const;
	// virtual void f3(); 
	// virtual void f4(); 
	// virtual void f5(); 
	// нету f6()
	// virtual void f7(D*); 
	// virtual void f8(int);
	// virtual void f8_1(int); 
	// virtual void f9(); 
	// private void f10();
	// int f11(int a,int b = 5);
};
void main()
{
	D d;


	B* pb=&d;
	B& rb=&d;
	pb->f();//D::f
	fb.f();

	B* pb=new D;
	delete pb;

	D* pd = &d;
	pd->f2();//D::f

	const B*pbc;
	const D bc;
	pbc=&bc;
	pb->f2();//error
	pb->f3();//B::f3
	pb->f4();//B::f4
	pb->f5();//err
	pb->f6();//B::f6
	pb->f7(&d);//B::f7
	pb->f8(1);//err
	pb->f8_1(1.5);//B::
	pb->f9();//err
	pb->f10();//D::
	pb->f11(1,2);//1,2
	pb->f11(1);//1, 5
	D* pd =&d;pd->f11(1);//1, 0
	&b->f11();//5,5
}