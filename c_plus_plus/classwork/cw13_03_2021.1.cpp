class A{
	A* a;
public:
	A(){this->a=this;};
	A(A a1){this->a=this;};
	A(A* a1){this->a=this;};
	A(const A& a1; const A& a2){this->a=this;};
	A* operator->(){return this;}
	A operator,(A&x){return x;}
};
int main1(){
	A a;
	A(a->a);
	A((a->a)->a);

return 0;
}
int main2(){
	A a;
	A x(a,a);
	A y((a,a));

return 0;
}