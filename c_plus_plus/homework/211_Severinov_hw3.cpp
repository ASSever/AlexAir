/*
2. АТД. Очередь для хранения данных.
На основе класса Список_элементов_произвольного_типа (использовать класс из ДЗ-2) 
определить класс Очередь, который должен быть производным от Списка.
Элемент данных, помещаемых в очередь — см. вариант задания.
№ варианта = № в списке группы % 3 +1 .
Максимальный допустимый размер очереди определен по умолчанию, а также может
явно указываться при создании объекта-Очереди.
Определить необходимые конструкторы.
Обеспечить корректное уничтожение объектов.
В классе должны быть функции:
добавления элемента в конец очереди (back),
чтение первого элемента из очереди без его удаления (front) ,
удаление первого элемента очереди (pop),
проверка очереди на пустоту (empty),
текущее число элементов (size),
проверка, что очередь целиком заполнена (full).
вывод информации об элементах очереди без ее изменения (print).
Замечания:
Хотелось бы, чтобы класс список можно было использовать для хранения любых
данных. Поэтому нужно выделить данные в отдельный класс.
Функции класса Список должны остаться прежними, а не переделываться под
потребности очереди.
Через объект Очередь должны быть доступны только функции, указанные в задании. При
этом базовый класс остается полноценным списком.
Глобальных переменных быть НЕ должно.
Использование STL и типа string запрещено.
Пример работы: Queue q1(5), q2; List l1; q1.back(el); l1.push_back(1); l1.print();
cout<<q2.size(); и т.д.
Варианты данных, которые помещаются в очередь.
1. Элемент данных - объект, содержащий информацию о клиенте: фамилия, время
добавления в очередь (целое или строка). Хранится также информация о текущем
количестве клиентов в очереди и об общем количестве клиентов во всех очередях
(списках).
2. Элемент данных – объект, содержащий информацию о заказе: название фирмы,
номер телефона (целое или строка), номер заказа. Нумерация заказов единая для
всех списков или очередей.
3. Элемент данных – объект «банковский счет». Необходимые члены-данные: номер
счета, владелец счета, дата создания счета (число или строка), сумма денег, 
которая на нем хранится. Нумерация счетов единая для всех очередей (списков).
*/

/*
Моя интерпретация задания:
	На основе class List из 211_Severinov_hw2 определить class Queue (очередь) [производный от List]
	Дополнительное поле в классе очередь:
		max_blocks(определено по умолчанию но можно задать при инициализации очереди) [Queue q1(5), q2;]
	Должны быть корректно определены необходимые конструкторы и деструкторы
	Вне класса Очередь должен быть доступен лишь следующий список методов: (правильно произвести наследование[privat(это) public protected])
		back - добавления элемента в конец очереди [q1.back(el);] {вызвать push_back из List}
		front - чтение первого элемента из очереди без его удаления {вызвать front из List}
		pop - удаление первого элемента очереди {вызвать pop_front из List}
		empty - проверка очереди на пустоту [.size()==0]
		size - текущее число элементов {вызвать size из List}
		full - проверка, что очередь целиком заполнена [.size()==max_blocks]
		print - вывод информации об элементах очереди {вызвать front из List + вывести макс количество в очереди}
	Базовый класс не изменять (только класс Data)//07.03.2021 после пары подошел с вопросом ->
	-> разрешили добавить в класс Block ссылку на List и изменить соответтствующим образом для этого класс List(добавление удаление блоков)
	сделано это для получения доступа к информации о количестве звеньев в данном списке/данной очереди
	но такое решение достаточно универсально и пригодится для получения любой информации о листе или блоке в 
	случаее если что-то нужно хранить в дате некий дополнительный спектр данных
	Варианты содержимого класса Data:
		1)"информация о клиенте":
			фамилия(surname)
			время добавления в очередь(строка или целое) (time_date)
			количество звеньев в очереди (local_count)
			количество звеньев во всех очередях (global_count)
		2)"информация о заказе":
			название фирмы (firm_name)
			номер телефона(строка или целое) (phone)
			номер заказа (единая  и автоматическая нумерация для всех списков и очередей) (order_number)
		3)"банковский счет":
			номер счета (единая  и автоматическая нумерация для всех списков и очередей) (account_number)
			фио владельца счета (full_name)
			время добавления в очередь(строка или целое) (time_date)
			хранимая сумма в пересчете на рубли (rubles)
	Определение моего варианта:
		(номер варианта) = (номер в списке группы)%3 + 1

		мой номер в списке группы = 18 => мой номер варианта = 1
*/
#include <iostream>
#include "211_Severinov_hw2.h"
using namespace std;
//Severinov Alexandr homework 3

const int MAX_BLOCKS = 20;

//вариант 1
void Data::SetSurname(const char *s)
{
	if (this->surname !=NULL)
		delete[] this->surname;
	if (s==NULL)
		this->surname = NULL;
	else
	{
		this->surname = new char [strlen(s)+1];
		strcpy(this->surname,s);
	}
}
void Data::SetTimeDate(const char *s)
{
	if (this->time_date !=NULL)
		delete[] this->time_date;
	if (s==NULL)
		this->time_date = NULL;
	else
	{
		this->time_date = new char [strlen(s)+1];
		strcpy(this->time_date,s);
	}
}
void Data::SetLocalCount()
{
	if (this->GetBlock()!=NULL)
		if (this->GetBlock()->GetList()!=NULL)
			this->local_count = this->GetBlock()->GetList()->GetCount();
		else
			this->local_count = NULL;
	else
		this->local_count = NULL;
}
void Data::incGlobalCount(){this->global_count += 1;};
void Data::decGlobalCount(){this->global_count -= 1;};
char* Data::GetSurname() const {return this->surname;}
char* Data::GetTimeDate() const {return this->time_date;}
int Data::GetLocalCount() const {return *(this->local_count);}
int Data::GetGlobalCount() const {return this->global_count;}
void Data::SetBlock(Block* x)
{
	this->block=x;
	this->SetLocalCount();
}
Block* Data::GetBlock() const {return this->block;};
void Data::print(int x)
{
	if (x<=1)
	{
		cout<<"Фамилия: ";
		if (this->surname==NULL)
			cout<<"none";
		else
			cout<<this->surname;
		cout<<"; Время: ";
		if (this->time_date==NULL)
			cout<<"none";
		else
			cout<<this->time_date;
		if (x==1)
		{
			cout<<"; Локал. кл-во: ";
			if (this->local_count==NULL)
				cout<<"none";
			else
				cout<<*(this->local_count);
			cout<<"; Глобал. кл-во: "<<this->global_count;
		}
	}
	else
	{
		cout<<endl<<"Фамилия: ";
		if (this->surname==NULL)
			cout<<"none"<<endl;
		else
			cout<<this->surname<<endl;
		cout<<"Время: ";
		if (this->time_date==NULL)
			cout<<"none"<<endl;
		else
			cout<<this->time_date<<endl;
		cout<<"Локал. кл-во: ";
		if (this->local_count==NULL)
			cout<<"none"<<endl;
		else
			cout<<*(this->local_count)<<endl;
		cout<<"Глобал. кл-во: "<<this->global_count<<endl;
	}
}
Data::Data(const char* surname, const char* time_date, Block* b):block(b)
{
	this->surname=NULL;
	this->time_date=NULL;
	this->SetSurname(surname);
	this->SetTimeDate(time_date);
	this->SetLocalCount();
	this->incGlobalCount();
}
Data::Data(const Data&x)
{
	this->surname=NULL;
	this->time_date=NULL;
	this->SetSurname(x.surname);
	this->SetTimeDate(x.time_date);
	this->block=x.block;
	this->SetLocalCount();
	this->incGlobalCount();
}
Data & Data::operator=(const Data&x)
{
	if (this != &x)
	{
		//удаление памяти (если требуется) происходит внутри функций
		this->SetSurname(x.surname);
		this->SetTimeDate(x.time_date);
		this->block=x.block;
		this->SetLocalCount();
	}
	return *this;
}
Data::~Data()
{
	this->SetSurname(NULL);
	this->SetTimeDate(NULL);
	this->decGlobalCount();
}

//перегрузка опрератора << для класса Data
ostream& operator<<(ostream &out, const Data x)
{
	out<<"Фамилия: ";
	if (x.surname==NULL)
		out<<"none";
	else
		out<<x.surname;
	out<<"; Время: ";
	if (x.time_date==NULL)
		out<<"none";
	else
		out<<x.time_date;
	out<<"; Локал. кл-во: ";
	if (x.local_count==NULL)
		out<<"none";
	else
		out<<*(x.local_count);
	out<<"; Глобал. кл-во: "<<x.global_count;
    return out;
}

class Queue: private List
{
//private:
	int max_blocks;
	void SetMaxBlocks(int x) {this->max_blocks=x;}
	int GetMaxBlocks() const {return this->max_blocks;}
public:
	Block* back(Data data = Data()) 
	{
		if (this->full())
		{
			cout<<"попытка переполнения очереди"<<endl;
			return NULL;
		}
		else
			return List::push_back(data);
	};
	Data front() const {return List::front();};
	void pop() {pop_front();};
	bool empty() {return List::empty();};
	int size() const {return List::size();};
	bool full() {return (List::size()==this->max_blocks);};
	void print(int x = 0){List::print(x);cout<<"(max_blocks="<<this->max_blocks<<")\n";};
	Queue(int max = MAX_BLOCKS):List(),max_blocks(max){};
	Queue(const Queue&x)
	{
		this->SetMaxBlocks(x.GetMaxBlocks());
		this->SetCount(0);
		this->SetFront(NULL);
		this->SetBack(NULL);
		Block* def_list_block;
		Block* new_list_block;
		def_list_block = x.GetFront();
		while(def_list_block != NULL)
		{
			new_list_block = this->push_back(def_list_block->GetData());
			//new_list_block->SetData(def_list_block->GetData());
			def_list_block = def_list_block->GetBack();
		}
	}
	Queue & operator=(const Queue&x)
	{
		if (this != &x)
		{
			while (this->size()>0)
				this->pop_back();
			this->SetMaxBlocks(x.GetMaxBlocks());
			this->SetFront(NULL);
			this->SetBack(NULL);
			Block* def_list_block;
			Block* new_list_block;
			def_list_block = x.GetFront();
			while(def_list_block != NULL)
			{
				new_list_block = this->push_back();
				new_list_block->SetData(def_list_block->GetData());
				def_list_block = def_list_block->GetBack();
			}
		}
		return *this;
	}
	~Queue()
	{
		while (this->size()>0)
			this->pop_back();
	}
};
int main()
{
	srand(time(NULL));
	Queue q1(5), q2;
	List l1,l2; 


	l1.push_back(Data("Severinov","2013_02_23-17:13:34")); 
	l1.push_back(); 
	l1.push_back(Data(NULL,"2013_02_23-17:13:34"));
	cout<<endl<<"вывожу l1 (1)"<<endl;
	l1.print();
	char *s1, *s2;
	s2 = new char [strlen("2020_01_02-11:35:03")+1];
	strcpy(s2,"2020_01_02-11:35:03");
	l1.GetBack()->GetData().SetTimeDate(s2);
	cout<<endl<<"вывожу l1 (2)"<<endl;
	l1.print(1);
	cout<<endl<<"вывожу l1 (3)"<<endl;
	l1.print(rand()%1000 + 2);
	cout<<"количество элементов в l1"<<l1.size()<<endl;

	l2.push_back(Data(NULL,s2));
	cout<<endl<<"вывожу l2 (1)"<<endl;
	l2.print(1);

	q2.back(Data());
	cout<<endl<<"вывожу q2 (1)"<<endl; 
	q2.print(1);
	s1 = new char [strlen("Kyzina")+1];
	strcpy(s1,"Kyzina");
	q1.back(Data(s1));
	q1.back(Data(s1,s2));
	for(int i = 0; i<5; i++)
		q1.back();
	cout<<endl<<"вывожу первый элемент q1"<<endl;
	q1.front().print(3);
	cout<<endl<<endl<<"вывожу q1 (1)"<<endl;
	q1.print(3);
	q1.pop();
	q1.pop();
	cout<<endl<<"вывожу q1 (2)"<<endl;
	q1.print();
	q2.pop();
	if (q2.empty())
		cout<<"я пуст"<<endl;
	q2.back(Data("Putin",s2));
	cout<<endl<<"вывожу q2 (2)"<<endl; 
	q2.print(1);
	q2=q1;
	for(int i = 0; i<2; i++)
		q2.back();
	cout<<endl<<"вывожу q2 (3)"<<endl; 
	q2.print(1);

	delete[] s1;
	delete[] s2;
	return 0;
}