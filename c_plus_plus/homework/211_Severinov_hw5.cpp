/*
ДЗ-5. Перегрузка операций. Срок сдачи — до 27.03.21
Написать (кто уже писал – дополнить ) класс Матрица таким образом, чтобы к объектам
этого типа была применима двойная индексация.
Должен быть верным, например, следующий фрагмент программы:
 Matrix m; … m[1][2] = 5; int x = m[2][3];
 const Matrix mc; cout<< mc[1][1];
 // mc[1][1] =100 ; // ошибка компиляции 
*/
#include <iostream>
using namespace std;
//Severinov Alexandr homework 5
class Data
{
//private:
	int * d1;
	int d;
public:
	void setD(int x){this->d=x;};
	int getD() const {return this->d;};
	void print(){cout<<this->d;};
	Data(int x=0):d(x){};
	Data(const Data&x)
	{
		this->d=x.d;
	}
	Data & operator=(const Data&x)
	{
		if (this != &x)
		{
			this->d = x.d;
		}
		return *this;
	}
	//перегрузка опрератора << 
	friend ostream& operator<<(ostream &out, const Data x);

	~Data(){};

};
ostream& operator<<(ostream &out, const Data x)
{
	out.width(4);
    out<<x.getD();
    return out;
}
const int STANDART_LEN = 5;
const int MAX_LEN = 1000;
class Matrix
{//row-строка column-столбец
	Data** M;
	int row;
	int column;
	void SetM(Data** x) {this->M=x;};
	void SetRow(int x) {this->row=x;};
	void SetColumn(int x) {this->column=x;};
public:
	Data** GetM() const {return this->M;};
	int GetRow() const {return this->row;};
	int GetColumn() const {return this->column;};
	Matrix(int row = STANDART_LEN, int column = STANDART_LEN):row(row),column(column)
	{
		if((row>0)&&(column>0)&&(row<MAX_LEN)&&(column<MAX_LEN))
		{
			M = new Data* [row];
			for (int i = 0; i < row; i++)
			{
				M[i] = new Data [column];//в конструкторе умолчания класса Data все зануляется
				// for (int j = 0; j < column; j++)
				// {
				// 	M[i][j]=Data();
				// }
			}
		}
		else
		{
			row=0;
			column=0;
			M=NULL;
		}
	}
	Matrix & operator=(const Matrix&x)
	{
		if (this->M!=NULL)
		{
			for (int i = 0; i < this->row; i++)
				if((this->M)[i]!=NULL)
					delete[] (this->M)[i];
			delete[] this->M;
		}
		Data* am;
		if((x.GetRow()>0)&&(x.GetColumn()>0)&&(x.GetM()!=NULL))
		{
			this->row = x.GetRow();
			this->column = x.GetColumn();
			this->M = new Data* [row];
			for (int i = 0; i < this->row; i++)
			{
				am=x.GetM()[i];
				if (am!=NULL)
				{
					(this->M)[i] = new Data [this->column];//в конструкторе умолчания класса Data все зануляется

					for (int j = 0; j < this->column; j++)
					{
						(this->M)[i][j]=am[j];
					}
				}
				else 
					(this->M)[i]=NULL;
			}
		}
		else
		{
			this->row=0;
			this->column=0;
			this->M=NULL;
		}
		return *this;
	}
	Matrix(const Matrix&x)
	{
		Data* am;
		if((x.GetRow()>0)&&(x.GetColumn()>0)&&(x.GetM()!=NULL))
		{
			this->row = x.GetRow();
			this->column = x.GetColumn();
			this->M = new Data* [row];
			for (int i = 0; i < this->row; i++)
			{
				am=x.GetM()[i];
				if (am!=NULL)
				{
					(this->M)[i] = new Data [this->column];//в конструкторе умолчания класса Data все зануляется

					for (int j = 0; j < this->column; j++)
					{
						(this->M)[i][j]=am[j];
					}
				}
				else 
					(this->M)[i]=NULL;
			}
		}
		else
		{
			this->row=0;
			this->column=0;
			this->M=NULL;
		}
	}
	~Matrix()
	{
		if (this->M!=NULL)
		{
			for (int i = 0; i < this->row; i++)
				if((this->M)[i]!=NULL)
					delete[] (this->M)[i];
			delete[] this->M;
		}
	}
	Data* operator[](const int i) const 
	{
		if ((this->row>i)&&(i>=0)&&(this->M!=NULL))
			return (this->M)[i];
		else
			return NULL;
	}
	//friend Data& operator[](Data*x,const int i);
	friend ostream& operator<<(ostream &out, const Matrix x);
};
// Data& operator[](Data* x,const int i)
// {
// 	return x[i];
// }
ostream& operator<<(ostream &out, const Matrix x)
{
	Data* am;
	if((x.GetRow()>0)&&(x.GetColumn()>0)&&(x.GetM()!=NULL))
	{
		out<<"Matrix:"<<endl;
		out<<endl;
		for (int i = 0; i < x.GetRow(); i++)
		{
			am=x.GetM()[i];
			if (am!=NULL)
			{
				out.width(4);
				out<<"("<<(i+1)<<") ";
				for (int j = 0; j < x.GetColumn(); j++)
					out<<am[j]<<" ";
				out<<endl;
			}
			else 
			{
				out<<"("<<(i+1)<<")";
				out<<" none"<<endl;
			}
		}
	}
	else
		out<<"Matrix: none"<<endl;
	return out;
}
int main()
{
	srand(time(NULL));//rand()%1000 + 2
	cout<<endl<<"//const Matrix mc; "<<endl;
	const Matrix mc; 
	cout<<"(mc)"<< mc;

	cout<<endl<<"//cout<< mc[1][1]<<endl; "<<endl;
	cout<< mc[1][1]<<endl;
	cout<<"(mc)"<< mc;

	cout<<endl<<"//mc[1][1] =100;"<<endl;
	mc[1][1] =100;
	cout<<"(mc)"<< mc;

	cout<<endl<<"//Matrix m1(mc);"<<endl;
	Matrix m1(mc);
	cout<<"(mc)"<< mc<<"(m1)"<< m1;

	cout<<endl<<"//заполнил m1"<<endl;
	for (int i = 0; i < m1.GetRow(); ++i)
		for (int j = 0; j < m1.GetColumn(); ++j)
			m1[i][j]=rand()%100 + 1;
	cout<<"(mc)"<< mc<<"(m1)"<< m1;

	cout<<endl<<"//Matrix m2(2,7);"<<endl;
	Matrix m2(2,7);
	cout<<"(mc)"<< mc<<"(m1)"<< m1<<"(m2)"<< m2;

	cout<<endl<<"//m2=m1;"<<endl;
	m2=m1;
	cout<<"(mc)"<< mc<<"(m1)"<< m1<<"(m2)"<< m2;
	Data x = m2[2][3]; //int x = m[2][3];
	return 0;
}