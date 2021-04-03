
/*
1. Написать класс с данными разных типов, среди которых обязательно должны быть
указатели.
Для этого класса написать конструкторы ( больше одного + конструктор копирования),
деструктор, оператор присваивания и хотя бы одну произвольную функцию-член класса.
В каждую из специальных функций класса включить отладочный вывод на экран, чтобы
было понятно, какая функция работает.
Функция main должна демонстрировать работу с объектами данного класса.
Использование STL и типа string запрещено.
*/

#include <iostream>
using namespace std;
//Severinov Alexandr homework 1

class Class //required class
{
//private:
	int class_nomber;
	int* count;
	void setCount(int x){*(this->count) = x;cout<<"Отладка(Class): count = "<<x<<endl;};

	Class(int class_nomber, int count):class_nomber(class_nomber)
	{
		cout<<"Отладка(Class): конструктор 1 (class_nomber = "<<class_nomber<<"; *count = "<<*(this->count)<<";)"<<endl;
		this->count = new int [1];
		*(this->count) = count;
	};
public:
	void setClassNomber(int x){this->class_nomber = x;cout<<x;cout<<"Отладка(Class): class_nomber = "<<x<<endl;};
	void incCount(){*(this->count)+=1;cout<<"Отладка(Class): count ++ "<<endl;};
	void decCount(){*(this->count)-=1;cout<<"Отладка(Class): count -- "<<endl;};

	int getClassNomber(){cout<<"Отладка(Class): return class_nomber; ("<<this->class_nomber<<')'<<endl;return this->class_nomber;};
	int getCount(){cout<<"Отладка(Class): return *count; ("<<*(this->count)<<')'<<endl;return *(this->count);};
	int* getCountPtr(){cout<<"Отладка(Class): return count; ("<<this->count<<')'<<endl;return this->count;};

	Class(int class_nomber);//:class_nomber(class_nomber);
	//конструктор копирования
	Class(const Class&x)
	{
		this->class_nomber=x.class_nomber;
		this->count = new int [1];
		*(this->count) = *(x.count);
		cout<<"Отладка(Class): конструктор копирования (class_nomber = "<<this->class_nomber<<"; *count = "<<*(this->count)<<";)"<<endl;
	}
	Class & operator=(const Class&x);
	~Class();
};

Class::Class(int class_nomber):class_nomber(class_nomber)
{
	cout<<"Отладка(Class): конструктор 2 (class_nomber = "<<class_nomber<<"; *count = 0; [default])"<<endl;
	this->count = new int [1];
	*(this->count) = 0;
}
Class::~Class()
{
	cout<<"Отладка(Class): деструктор"<<endl;
	delete[] this->count;
}
Class&Class:: operator=(const Class&x){
	cout<<"Отладка(Class): оператор присваивания"<<endl;
	if (this != &x)
	{
		this->class_nomber = x.class_nomber;
		delete [] this->count;
		this->count = new int [1];
		*(this->count) = *(x.count);
	}
	return *this;
}

const char *UNKNOWN = "unnamed student";
/*все студенты одного класса хранят одинаковую ссылку на область памяти 
где хранится количество студентов в классе*/
class Student
{
//private:
	int class_nomber;
	int* count;
	char* name;
public:
	void incCount(){*(this->count)+=1;cout<<"Отладка(Student): count ++ ("<<*(this->count)<<')'<<endl;};
	void decCount(){*(this->count)-=1;cout<<"Отладка(Student): count -- ("<<*(this->count)<<')'<<endl;};
	void setName(char* name);

	int getClassNomber(){cout<<"Отладка(Student): return class_nomber; ("<<this->class_nomber<<')'<<endl;return this->class_nomber;};
	int getCount(){cout<<"Отладка(Student): return *count; ("<<*(this->count)<<')'<<endl;return *(this->count);};
	int* getCountPtr(){cout<<"Отладка(Student): return count; ("<<this->count<<')'<<endl;return this->count;};
	char* getName(){cout<<"Отладка(Student): return name; ("<<this->name<<')'<<endl;return this->name;}

	Student(Class* room, char* name = NULL);
	//конструктор копирования
	Student(const Student&x)
	{
		cout<<"Отладка(Student): конструктор копирования name ="<<name<<" new name = "<<x.name<<endl;
		this->class_nomber=x.class_nomber;
		this->count = x.count;
		this->name = new char [strlen(x.name)+1];
		strcpy(this->name,x.name);
		//*(this->count) += 1;
		this->incCount();
	}
	Student & operator=(const Student&x);
	~Student();
};

void Student::setName(char* name)
{
	cout<<"Отладка(Student): name = "<<name<<endl;
	delete [] this->name;
	this->name = new char [strlen(name)+1];
	strcpy(this->name,name);
}

Student::Student(Class* room, char* name)
{
	if (name == NULL)
	{
		cout<<"Отладка(Student): конструктор name = unnamed student"<<endl;
	}
	else
	{
		cout<<"Отладка(Student): конструктор name = "<<name<<endl;
	}
	this->class_nomber = (*room).getClassNomber();
	this->count = (*room).getCountPtr();
	if (name == NULL)
	{
		this->name = new char [strlen("unnamed student")+1];
		strcpy(this->name,"unnamed student");
	}
	else
	{
		this->name = new char [strlen(name)+1];
		strcpy(this->name,name);
	}
	//*(this->count) += 1;
	this->incCount();
}
Student::~Student()
{
	cout<<"Отладка(Student): деструктор name ="<<name<<endl;
	//*(this->count) -= 1;
	this->decCount();
	delete[] this->name;
}
Student&Student:: operator=(const Student&x){
	cout<<"Отладка(Student): оператор присваивания name ="<<name<<" new name = "<<x.name<<endl;
	if (this != &x)
	{
		if (this->class_nomber!=x.class_nomber)
		{//уменшаем количество студентов в старом классе и увеличиваем в новом
			//*(this->count) -= 1;
			this->decCount();
			this->count = x.count;
			//*(this->count) += 1;
			this->incCount();
			this->class_nomber = x.class_nomber;
		}
		delete [] this->name;
		this->name = new char [strlen(x.name)+1];
		strcpy(this->name,x.name);
	}
	return *this;
}

int main()
{
	//Class Math(779, 10);
	Class Math(779);
	Class Physics(Math);
	Math.setClassNomber(515);
	Math = Physics;
	Physics.setClassNomber(214);
	//Math.setCount(23);
	Math.incCount();
	Math.decCount();
	cout<<Math.getClassNomber()<<" (Math.getClassNomber() )"<<endl;
	cout<<Math.getCount()<<" (Math.getCount() )"<<endl;
	cout<<Math.getCountPtr()<<" (Math.getCountPtr() )"<<endl;
	cout<<endl;
	Student ArrStudents[4] = {
		Student(&Math, "Alex"),
		Student(&Physics, "Ann"),
		Student(&Math),
		Student(&Math, "Jorge")
	};
	cout<<endl;
	ArrStudents[3].setName("Ivan");
	Physics.getClassNomber();
	Math.getClassNomber();
	ArrStudents[2].getName();
	ArrStudents[2].setName("Aveline");
	ArrStudents[2].getName();
	ArrStudents[2].getClassNomber();
	ArrStudents[2] = ArrStudents[0];
	ArrStudents[2].getName();
	ArrStudents[2].getClassNomber();

	Math = Physics;

	return 0;
}