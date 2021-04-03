#include <iostream>
using namespace std;
class Arr{
	int * arr;
	int size;
public:
	int getSize()const{return this->size;}
	int* getArr()const{return this->arr;}
	void setSize(int s){this->size=s;}
	void setArr(int *a){this->arr=a;}
	Arr(int s, int date =0):size(s){if (s!=0){arr = new int[s]; for (int i=0;i<size;arr[i++]=date);}else{arr=NULL;}}
	~Arr()
	{
		delete [] arr;
	}
	Arr(const Arr&x){
		if (x.getSize()!=0)
			{
				this->size=x.getSize();
				this->arr = new int[this->size]; for (int i=0;i<this->size;i++)
				{
					this->arr[i]=x.getArr()[i];
				}
			}
		else
			{this->size=0;this->arr=NULL;}
	}
	Arr & operator|(const int&x)
	{
		if (this->arr!=NULL)
			this->arr[0]+=x;
		return *this;
	}
	// Arr & operator|(const Arr&x)
	// {
	// 	if (this->arr!=NULL)
	// 		if(x.getArr()!=NULL)
	// 			this->arr[0]+=x.getArr()[0];
	// 	return *this;
	// }
	Arr & operator|(Arr&x) const 
	{
		if (this->arr!=NULL)
			if(x.getArr()!=NULL)
				x.getArr()[0]+=this->arr[0];
		return x;
	}
	Arr & operator-() {
		if (this->arr!=NULL)
			this->arr[0]--;
		return *this;
	}

	Arr & operator=(const Arr&x)
	{
		if (this != &x)
		{
			if (x.getSize()!=0)
				{
					this->size=x.getSize();
					if (this->arr!=NULL)
					{
						delete[]this->arr;
					}
					this->arr = new int[this->size]; for (int i=0;i<this->size;i++)
					{
						this->arr[i]=x.getArr()[i];
					}
				}
			else
				{this->size=0;this->arr=NULL;}
		}
		return *this;
	}
	int &operator[](const int i) const 
	{
		if ((i<this->getSize())&&(i>=0))
		{
			return this->getArr()[i];
		}
		else 
			{
				return this->getArr()[0];
			}
	}
	Arr(Arr&& x)
	{
		this->setArr(x.getArr());
		this->setSize(x.getSize());
		x.setArr(NULL);
		x.setSize(0);
	}

	Arr& operator=(Arr&& x)
	{
		// Проверка на самоприсваивание
		if (&x == this)
			return *this;
 //null
		delete arr;
 
		this->setArr(x.getArr());
		this->setSize(x.getSize());
		x.setArr(NULL);
		x.setSize(0);
 
		return *this;
	}
	friend ostream& operator<<(ostream &out, const Arr& x);
};
ostream& operator<<(ostream &out, const Arr& x)
{
	out<<"arr: ";
	if(x.getSize() ==0){out<<"none";}
	int *a;
	a= x.getArr();
	for (int i=0;i<x.getSize();i++)
	{
		out<<a[i]<<"; ";
	}
	out<<endl;
    return out;
}

int main(){
	cout<<"обьявили все"<<endl;
	Arr a1(15), a2(20, 5), a3(30,3);
	const Arr a4(5);
	cout<<"1"<<a1<<"2"<<a2<<"3"<<a3<<"4"<<a4;
	cout<<"a2=a2|2;"<<endl;
	a2=a2|2;
	cout<<"1"<<a1<<"2"<<a2<<"3"<<a3<<"4"<<a4;
	cout<<"a3=(-a2)|a3;"<<endl;
	a3=(-a2)|a3;
	cout<<"1"<<a1<<"2"<<a2<<"3"<<a3<<"4"<<a4;
	cout<<"a3[5]=10;"<<endl;
	a3[5]=10;
	cout<<"1"<<a1<<"2"<<a2<<"3"<<a3<<"4"<<a4;
	cout<<"a1=a4|a3;"<<endl;
	a1=a4|a3;
	cout<<"1"<<a1<<"2"<<a2<<"3"<<a3<<"4"<<a4;
	cout<<"Arr a5(move(a3));"<<endl;
	Arr a5(move(a3));
	cout<<"1"<<a1<<"2"<<a2<<"3"<<a3<<"4"<<a4<<"5"<<a5;
	cout<<"a1=move(a2);"<<endl;
	a1=move(a2);
	cout<<"1"<<a1<<"2"<<a2<<"3"<<a3<<"4"<<a4<<"5"<<a5;
	return 0;
}