class X{
public:
	void print()const{cout<<...}
};
class Pointer{
	X*px;
public:
	Pointer(X*x):px(x){}
	X*operator->()const{return px;}
	~Pointer(){delete px;}
};
class Pointer2{
	Pointer p;
public:
	Pointer2(X*x):p(x){}
	Pointer operator->()const{return p;}
};
void main(new X){
	p->print();
	Pointer2 p2(new X);
	p2->print();

return;
}