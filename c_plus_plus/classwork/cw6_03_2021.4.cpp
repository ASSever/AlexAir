//нельзя перегружать
/*
::
.
.*
?:
sizeof
typeid
dynamic_cast
static_cast
reinterpet_cast
*/
//только в классе можно переопределить
/*
oper =
	[]
	->
	()
operator Type()
*/
class X{public:
T operator Q();
T operator Q2(par);

X x;
x.operatorQ();
Q x;

x Q2 par;
x.operatorQ2(par);
};

//вне:
T operator Q();
operatorQ();
T operator Q2(x1,x2);
operatorQ();
x1 Q2 x2

class B
{
	private int x;
	protected int y;
	public int z;
	B(int x=0,int y=0,int z=0):x(x),y(y),z(z){}
	void fb(){x++;y++;y++;}
};
class D:public/*protected*/ B
{
public:
}
void main()
{
	D d;

	d.x++;
	d.y++;
	d.z++;
	B* b=&d;
}