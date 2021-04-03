#include <iostream>
using namespace std;
//Severinov Alexandr homework 2
class Block;
class List;


class Data
{
private:
	//вариант1
	char* surname;
	char* time_date;
	const int* local_count;
	static int global_count;
	//int d;
	Block* block;
public:
	void SetSurname(const char *s);
	void SetTimeDate(const char *s);
	void SetLocalCount();
	void incGlobalCount();
	void decGlobalCount();
	char* GetSurname() const;
	char* GetTimeDate() const;
	int GetLocalCount() const;
	int GetGlobalCount() const;

	//void setD(int x);
	void SetBlock(Block* x);
	//int getD() const;
	Block* GetBlock() const;
	void print(int x=0);
	Data(const char* surname=NULL, const char* time_date=NULL, Block* b=NULL);
	Data(const Data&x);
	Data & operator=(const Data&x);
	//перегрузка опрератора << 
	friend ostream& operator<<(ostream &out, const Data x);
	~Data();
};
//вариант 1
int Data::global_count=0;

/*
class Data
{
//private:
	int d;
	Block* block;
public:
	void setD(int x){this->d=x;};
	void SetBlock(Block* x){this->block=x;};
	int getD() const {return this->d;};
	Block* GetBlock() const {return this->block;};
	void print(){cout<<this->d;};
	Data(int x=0, Block* b=NULL):d(x),block(b){};
	Data(const Data&x)
	{
		this->d=x.d;
		this->block=x.block;
	}
	Data & operator=(const Data&x)
	{
		if (this != &x)
		{
			this->d = x.d;
			this->block=x.block;
		}
		return *this;
	}
	//перегрузка опрератора << 
	friend ostream& operator<<(ostream &out, const Data x);

	~Data(){};

};
ostream& operator<<(ostream &out, const Data x)
{
    out<<x.getD();
    return out;
}*/


class Block
{
//private:
	Block* frontB;//ближе к началу
	Block* backB;//ближе к концу
	Data data;
	List* list;
public:
	void SetFront(Block* x){this->frontB=x;};
	void SetBack(Block* x){this->backB=x;};
	void SetData(Data x)
	{
		this->data=x;
		if (x.GetBlock()!=this)
			this->data.SetBlock(this);
		//cout<<endl<<"1 SetBlock "<<this<<endl;
	}
	void SetList(List* x){this->list=x;};
	Block* GetFront() const {return this->frontB;};
	Block* GetBack() const {return this->backB;};
	Data GetData() const {return this->data;};
	List* GetList() const {return this->list;};
	void PrintData(int x = 0){(this->data).print(x);};
	Block(Data data=Data(), Block* frontB=NULL, Block* backB=NULL, List* list=NULL):
	frontB(frontB),backB(backB),list(list)
	{
		this->data=data;
		if (data.GetBlock()!=this)
			this->data.SetBlock(this);
		//cout<<endl<<"2 SetBlock "<<this<<endl;

	/*cout<<"Block("<<data.getD()<<','<<frontB<<','<<backB<<");"<<endl;*/
	}
	Block(const Block&x)
	{
		this->frontB = x.frontB;
		this->backB = x.backB;
		this->data = x.data;
		if (x.data.GetBlock()!=this)
			this->data.SetBlock(this);
		//cout<<endl<<"3 SetBlock "<<this<<endl;
		this->list = x.list;
	}
	Block & operator=(const Block&x)
	{
		if (this != &x)
		{
			this->frontB = x.frontB;
			this->backB = x.backB;
			this->data = x.data;//через перегруженную операцию равно
			if (x.data.GetBlock()!=this)
				this->data.SetBlock(this);
			//cout<<endl<<"4 SetBlock "<<this<<endl;
			this->list = x.list;
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
protected:
	void SetCount(int x){this->count=x;};
public:
	void SetFront(Block* x)
	{
		this->frontB=x;
		if ((x!=NULL)&&(x->GetList()!=this))
			this->frontB->SetList(this);
	}
	void SetBack(Block* x)
	{
		this->backB=x;
		if ((x!=NULL)&&(x->GetList()!=this))
			this->backB->SetList(this);
	}
	void incCount(){this->count+=1;};
	void decCount(){this->count-=1;};
	Block* GetFront() const {return this->frontB;};
	Block* GetBack() const {return this->backB;};
	const int* GetCount() const {return &(this->count);};
	int size() const {return this->count;};
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
			new_list_block = this->push_back(def_list_block->GetData());
			//new_list_block->SetData(def_list_block->GetData());
			def_list_block = def_list_block->GetBack();
		}
		cout<<"22222"<<endl;
	}
	List & operator=(const List&x)
	{
		if (this != &x)
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
		new_front->SetList(this);
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
		new_back->SetList(this);
		new_back->SetData(data);
		this->incCount();
		return new_back;
	}
	Data front() const {return (this->frontB)->GetData();}
	Data back() const {return (this->backB)->GetData();}
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
		new_block->SetList(this);
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
		cout<<"list: ";
		Block* cur = this->frontB;
		int i = 1;
		if (x==0)
		{
			cout<<endl;
			cout<<"---"<<endl;
			while(cur!=NULL)
			{
				cout<<i<<" block: ";
				cur->PrintData(x);
				//cout<<cur->GetData();
				cout<<endl;
				i++;
				cur = cur->GetBack();//(*cur).GetBack() одно и тоже
			}
			cout<<"---"<<endl;
		}
		else
		{
			while(cur!=NULL)
			{
				cur->PrintData(x);
				//cout<<cur->GetData();
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
		out<<'('<<i<<") "<<cur<<"(this), "<<*cur<<endl;
		cur = cur->GetBack();
		i++;
	}
	return out;
}