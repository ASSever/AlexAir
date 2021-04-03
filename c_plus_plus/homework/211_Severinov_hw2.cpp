
/*
1. АТД. Список данных.
Класс — список (двунаправленный), элемент данных — int (либо произвольного типа).
Смотрите ДЗ-3, этот класс «Список» потребуется для дальнейшей работы, поэтому
желательно, чтобы его легко было потом адаптировать для работы с данными
произвольного типа.
Определить необходимые конструкторы.
Обеспечить корректное уничтожение объектов.
В классе должны быть функции:
добавления элемента в начало (push_front) и в конец (push_back),
чтение первого элемента списка (front),  !!!!!!!!!!!! информация хранимая в первом элементе
чтение последнего элемента списка (back),!!!!!!!!!!!! информация хранимая в последнем элементе
удаление первого элемента списка (pop_front),
удаление последнего элемента списка (pop_back),
добавление элемента x перед позицией p ( insert(p,x)),!!!!!! считаю что первый элемент имеет номер 1 (а не 0)
удаление элемента из позиции p (erase(p))
проверка списка на пустоту (empty),
текущее число элементов (size),
вывод информации об элементах списка (print).
Использование STL и типа string запрещено.
Функция main должна демонстрировать работу с объектами данного класса.
Пример работы: List l1; l1.push_front(1); ... l1.print(); и т.д.
*/

#include <iostream>
using namespace std;
//Severinov Alexandr homework 2

class Data
{
//private:
	int d;
public:
	void setD(int x){this->d=x;};
	int getD() const {return this->d;}
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
    out << x.getD();
    return out;
}


class Block
{
//private:
	Block* frontB;//ближе к началу
	Block* backB;//ближе к концу
	Data data;
public:
	void SetFront(Block* x){this->frontB=x;};
	void SetBack(Block* x){this->backB=x;};
	void SetData(Data x){this->data=x;};
	Block* GetFront() const {return this->frontB;};
	Block* GetBack() const {return this->backB;};
	Data GetData() const {return this->data;};
	void PrintData(){(this->data).print();};
	Block(Data data = Data(), Block* frontB = NULL, Block* backB = NULL):data(data),frontB(frontB),backB(backB){/*cout<<"Block("<<data.getD()<<','<<frontB<<','<<backB<<");"<<endl;*/};
	Block(const Block&x)
	{
		this->frontB = x.frontB;
		this->backB = x.backB;
		this->data = x.data;
	}
	Block & operator=(const Block&x)
	{
		if (this != &x)
		{
			this->frontB = x.frontB;
			this->backB = x.backB;
			this->data = x.data;//через перегруженную операцию равно
		}
		return *this;
	}
	//перегрузка опрератора << 
	friend ostream& operator<<(ostream &out, const Block x);
	~Block(){};
};
ostream& operator<<(ostream &out, const Block x)
{
	out<<x.GetFront()<<" (front), "<<x.GetBack()<<" (back), "<<x.GetData()<<" (data)";
    return out;
}

class List
{
//private:
	Block* frontB;//начало
	Block* backB;//конец
	int count;
	void SetCount(int x){this->count=x;};
public:
	void SetFront(Block* x){this->frontB=x;};
	void SetBack(Block* x){this->backB=x;};
	void incCount(){this->count+=1;};
	void decCount(){this->count-=1;};
	Block* GetFront() const {return this->frontB;};
	Block* GetBack() const {return this->backB;};
	int size() const {return this->count;};//GetCount()
	List():frontB(NULL),backB(NULL),count(0){};
	List(const List&x)
	{
		this->SetCount(0);
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
	List & operator=(const List&x)
	{
		while (this->size()>0)
			this->pop_back();
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
		return *this;
	}
	~List()
	{
		while (this->size()>0)
			this->pop_back();
	}
/*
push_front
push_back
front
back
pop_front
pop_back
insert(p,x)
erase(p)
empty
size
print
*/	
	Block* push_front(Data data = Data())
	{
		Block* new_front;
		new_front = new Block [1];
		if (this->size() == 0)
		{
			this->frontB = new_front;
			this->backB = new_front;
		}
		else
		{
			new_front->SetBack(this->frontB);
			(this->frontB)->SetFront(new_front);
			this->frontB = new_front;
		}
		new_front->SetData(data);
		this->incCount();
		return new_front;
	}
	Block* push_back(Data data = Data())
	{
		Block* new_back;
		new_back = new Block [1];
		if (this->size() == 0)
		{
			this->frontB = new_back;
			this->backB = new_back;
		}
		else
		{
			new_back->SetFront(this->backB);
			(this->backB)->SetBack(new_back);
			this->backB = new_back;
		}
		new_back->SetData(data);
		this->incCount();
		return new_back;
	}
	Data const front(){return (this->frontB)->GetData();}
	Data const back(){return (this->backB)->GetData();}
	void pop_front()
	{
		if (this->empty()) {return;}
		Block* new_front;
		new_front = (this->frontB)->GetBack();
		if (new_front != NULL)
			new_front->SetFront(NULL);
		delete[] this->frontB;
		this->frontB = new_front;
		this->decCount();
		if (this->empty()) {this->backB = NULL;}
	}	
	void pop_back()
	{
		if (this->empty()) {return;}
		Block* new_back;
		new_back = (this->backB)->GetFront();
		if (new_back != NULL)
			new_back->SetBack(NULL);
		delete[] this->backB;
		this->backB = new_back;
		this->decCount();
		if (this->empty()) {this->frontB = NULL;}
	}
	Block* insert(int position, Block* new_block)
	{
		if ((new_block->GetFront()!=NULL)||(new_block->GetBack()!=NULL)) 
		{
			Data d = new_block->GetData();
			new_block = new Block [1];
			new_block->SetData(d);
		}

		if (position>=(this->size())+2){position = (this->size())+1;}
		if (position<=0){position = 1;}
		Block* cur_block;
		Block* last_cur_block;
		int i = 1;
		if (position<(this->size())/2)
		{
			cur_block = this->frontB;
			last_cur_block = NULL;
			while (i<position)
			{
				last_cur_block = cur_block;
				cur_block = cur_block->GetBack();
				i++;
			}
		}
		else
		{//тут смысл переменных типа блок немного искажен
			i = this->size()+1;
			last_cur_block = this->backB;
			cur_block = NULL;
			while (i>position)
			{
				cur_block = last_cur_block;
				last_cur_block = last_cur_block->GetFront();
				i--;
			}
		}
		new_block->SetFront(last_cur_block);
		new_block->SetBack(cur_block);
		if (last_cur_block != NULL)
			last_cur_block->SetBack(new_block);
		if (cur_block != NULL)
			cur_block->SetFront(new_block);
		this->incCount();
		return new_block;
	}
	void erase(int position)
	{
		if ((position<=0)||(this->empty())||(position>=(this->size())+1)){return;}
		int i = 1;
		Block* cur_block;
		cur_block = this->frontB;
		while (i<position)
		{
			cur_block = cur_block->GetBack();
			i++;
		}
		Block* up;
		Block* down;
		up = cur_block->GetFront();
		down = cur_block->GetBack();
		if (up!=NULL) {up->SetBack(down);}
		if (down!=NULL) {down->SetFront(up);}
		delete[] cur_block;
		this->decCount();
	}

	bool empty(){return (this->count==0);}
	void print(int x = 0)
	{
		Block* cur = this->frontB;
		int i = 1;
		if (x==0)
		{
			cout<<"---"<<endl;
			while(cur!=NULL)
			{
				cout<<i<<" block: ";
				cur->PrintData();
				cout<<endl;
				i++;
				cur = cur->GetBack();//(*cur).GetBack() одно и тоже
			}
			cout<<"---"<<endl;
		}
		else
		{
			cout<<"list";
			while(cur!=NULL)
			{
				cur->PrintData();
				cout<<" ("<<i<<");";
				i++;
				cur = cur->GetBack();
			}
			cout<<endl;
		}
	}
	//перегрузка опрератора << 
	friend ostream& operator<<(ostream &out, const List x);
};
ostream& operator<<(ostream &out, const List x)
{
	Block* cur = x.GetFront();
	int i = 1;
	out<<"List:"<<endl;
	while(cur!=NULL)
	{
		out<<'('<<i<<") "<<*cur<<endl;
		cur = cur->GetBack();
		i++;
	}
	return out;
}
int main()
{
	srand(time(NULL));
	List l1;
	Block* b1;
	b1=l1.push_back();
	l1.print(1);
	b1->SetData(Data(34));
	l1.print(1);
	b1=l1.push_front();
	l1.print(1);
	l1.push_back();
	b1->SetData(rand()%1000);
	l1.print(1);
	cout<<"count = "<<l1.size()<<endl;
	for (int i = 0; i < 10; ++i)
	{
		i%2==0?b1=l1.push_back(rand()%1000):b1=l1.push_front(rand()%1000);
		//b1->SetData(rand()%1000);
	}
	l1.print(1);
	cout<<"count = "<<l1.size()<<endl;

	List l2(l1);
	l2.print(1);
	l2.pop_back();
	l2.pop_back();
	l2.pop_front();
	l2.pop_back();
	l2.print(1);
	cout<<"b1 = "<<b1->GetData().getD()<<endl;
	Block* b2;
	b2 = l2.insert(6,b1);
	l2.print(1);
	cout<<"b2 = "<<b2->GetData().getD()<<endl;
	l2.erase(8);
	l2.print(1);
	l1=l2;
	l1.print();
	cout<<"front block l2: "<<l2.front().getD()<<endl<<"back block l1: "<<l1.back().getD()<<endl;
	cout<<l1;
	return 0;
}