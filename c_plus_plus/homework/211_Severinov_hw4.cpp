/*
ДЗ-4. Абстрактные классы. Срок сдачи — до 20.03.21
Написать абстрактный класс (содержание произвольное) и несколько (>=2) производных
от него классов. Определить независимый от этой иерархии класс, который работает с
массивом объектов типа абстрактного класса.
Использование STL запрещено.
Функция main должна демонстрировать работу с объектами указанных классов.
*/
#include <iostream>
#include <unistd.h>//для функции sleep()
using namespace std;
//Severinov Alexandr homework 4
class Transport
{
//private:
	double mileage; //пробег(км)
	int capacity; //вместимость(человек)
	double weight; //вес транспорта без топлива, людей и иных дополнительных грузов(кг)
	double speed; //средняя(км/ч)
public:
	void SetMileage(double x){this->mileage=x;};
	void SetCapacity(int x){this->capacity=x;};
	void SetWeight(double x){this->weight=x;};
	void SetSpeed(double x){this->speed=x;};
	double GetMileage() const {return this->mileage;};
	int GetCapacity() const {return this->capacity;};
	double GetWeight() const {return this->weight;};
	double GetSpeed() const {return this->speed;};
	Transport(double mileage=0, int capacity=0, double weight=0, double speed=0):
	mileage(mileage),capacity(capacity),weight(weight),speed(speed){};
	Transport(const Transport&x)
	{
		this->mileage=x.mileage;
		this->capacity=x.capacity;
		this->weight=x.weight;
		this->speed=x.speed;
	}
	Transport & operator=(const Transport&x)
	{
		if (this != &x)
		{
			this->mileage=x.mileage;
			this->capacity=x.capacity;
			this->weight=x.weight;
			this->speed=x.speed;
		}
		return *this;
	}
	~Transport(){};
	virtual double ride(double x)=0;//принимает км возвращает часы
};
class Car: public Transport
{
//private:
	double max_fuel; //литры
	double fuel; //литры
	double usage; //расход топлива л/ч
	void SetMaxFuel(double x){this->max_fuel=x;};
	void SetUsage(double x){this->usage=x;};
	void SetFuel(double x){this->fuel=x;};
public:
	double GetMaxFuel() const {return this->max_fuel;};
	double GetFuel() const {return this->fuel;};
	double GetUsage() const {return this->usage;};
	Car(double mileage=0,int capacity=5,double weight=2000,double speed=150,double max_fuel=60,double fuel=-1,double usage=0.06):
	Transport(mileage, capacity, weight, speed),max_fuel(max_fuel), usage(usage)
	{
		if (fuel==-1)
			this->fuel=max_fuel;
		else
			this->fuel=fuel;
	}
	Car(const Car&x)
	{
		this->SetMileage(x.GetMileage());
		this->SetCapacity(x.GetCapacity());
		this->SetWeight(x.GetWeight());
		this->SetSpeed(x.GetSpeed());
		this->SetMaxFuel(x.GetMaxFuel());
		this->SetFuel(x.GetFuel());
		this->SetUsage(x.GetUsage());
	}
	Car & operator=(const Car&x)
	{
		if (this != &x)
		{
			this->SetMileage(x.GetMileage());
			this->SetCapacity(x.GetCapacity());
			this->SetWeight(x.GetWeight());
			this->SetSpeed(x.GetSpeed());
			this->SetMaxFuel(x.GetMaxFuel());
			this->SetFuel(x.GetFuel());
			this->SetUsage(x.GetUsage());
		}
		return *this;
	}
	~Car(){};
	double refill(double x = 0)//заправка (возвращает количество лишнего топлива)
	{
		cout<<"Идет заправка машины"<<endl;
		double s = 10; //скорость заполнения на заправке(л/сек)
		double y, z;
		(x==0)?(y=(this->max_fuel)-(this->fuel)):(y=x);
		((y+(this->fuel))>(this->max_fuel))?(z=y+(this->fuel)-(this->max_fuel)):(z=0);
		y -= z;
		double i = y/s;
		while(i>=1)
		{
			sleep(1);
			cout<<'~'<<endl;
			i -= 1;
		}
		cout<<endl<<"Заправка завершена!"<<endl;
		this->fuel += y;
		return z;
	}
	double ride(double x)
	{
		int b = 0;
		if (x<0)
		{
			b = 1;
			x*=-1;
		}
		double hours,h;
		if ((this->fuel/this->usage)>=(x/this->GetSpeed()))
		{
			cout<<"Машина выехала"<<endl;
			hours = x/this->GetSpeed();
			h = hours;
			this->fuel -= hours*this->usage;
			if (b)
				while(hours>=1)
				{
					sleep(1);
					cout<<'.'<<endl;
					hours -= 1;
				}
			cout<<"Поездка завершена успешно!"<<endl;
			if (this->fuel<5)
				cout<<"В бензобаке осталось мало топлива ("<<this->fuel<<"л.), рекомендуется заправиться."<<endl;
		}
		else
		{
			char c;
			cout<<"Недостаточно топлива для столь длительного переезда."<<endl;
			while(1)
			{
				cout<<"Всер равно выехать? (y-да, n-нет)"<<endl;
				cin>>c;
				if (c=='y')
				{
					cout<<"Машина выехала"<<endl;
					hours = (this->fuel/this->usage);
					h = hours;
					this->fuel = 0;
					if (b)
						while(hours>=1)
						{
							sleep(1);
							cout<<'.'<<endl;
							hours -= 1;
						}
					hours = (h*this->GetSpeed())*100/x;
					cout<<"Топливо кончилось. Пройдено "<<hours<<"% пути."<<endl;
					break;
				}
				else
					if (c=='n')
					{
						cout<<"Решено никуда не ехать."<<endl;
						h=0;
						break;
					}
					else
						cout<<"Не понимаю вас."<<endl<<"Попробуйте еще раз."<<endl;
			}
		}
		if (h!=0)
			this->SetMileage(this->GetMileage()+h*this->GetSpeed());
		return h;
	}
};
class Bicycle: public Transport
{
//private:
	double energy; //в процентах
	double usage; //процент расхода энергии в ч
	void SetUsage(double x){this->usage=x;};
	void SetEnergy(double x){this->energy=x;};
public:
	double GetEnergy() const {return this->energy;};
	double GetUsage() const {return this->usage;};
	Bicycle(double mileage=0,int capacity=1,double weight=19,double speed=15,double energy=100, double usage=0.35):
	Transport(mileage, capacity, weight, speed),energy(energy), usage(usage)
	{
		if (energy>100)
			this->energy=100;
		else
			this->energy=energy;
	}
	Bicycle(const Bicycle&x)
	{
		this->SetMileage(x.GetMileage());
		this->SetCapacity(x.GetCapacity());
		this->SetWeight(x.GetWeight());
		this->SetSpeed(x.GetSpeed());
		this->SetEnergy(x.GetEnergy());
		this->SetUsage(x.GetUsage());
	}
	Bicycle & operator=(const Bicycle&x)
	{
		if (this != &x)
		{
			this->SetMileage(x.GetMileage());
			this->SetCapacity(x.GetCapacity());
			this->SetWeight(x.GetWeight());
			this->SetSpeed(x.GetSpeed());
			this->SetEnergy(x.GetEnergy());
			this->SetUsage(x.GetUsage());
		}
		return *this;
	}
	~Bicycle(){};
	void rest(double x = 0)//отдых  передаем количество часов
	{
		cout<<"Велосипедист отдыхает"<<endl;
		double s = 20; //скорость отдыха(проц/сек)
		double y;
		y = 100 - this->energy;
		((x*s<y)&&(x!=0))?(y = x*s):(x = y/s);
		while(x>=1)
		{
			sleep(1);
			cout<<'~'<<endl;
			x -= 1;
		}
		cout<<endl<<"Отдых завершен завершен!"<<endl;
		this->energy += y;
		return;
	}
	double ride(double x)
	{
		int b = 0;
		if (x<0)
		{
			b = 1;
			x*=-1;
		}
		double hours,h;
		if ((this->energy/this->usage)>=(x/this->GetSpeed()))
		{
			cout<<"Велосипедист выехал"<<endl;
			hours = x/this->GetSpeed();
			h = hours;
			this->energy -= hours*this->usage;
			if (b)
				while(hours>=1)
				{
					sleep(1);
					cout<<'.'<<endl;
					hours -= 1;
				}
			cout<<"Поездка завершена успешно!"<<endl;
			if (this->energy<5)
				cout<<"Велосипедист очень устал ("<<this->energy<<"%), рекомендуется отдохнуть."<<endl;
		}
		else
		{
			char c;
			cout<<"Велосипедисту не хватит сил доехать до назначенного места."<<endl;
			while(1)
			{
				cout<<"Всер равно выехать? (y-да, n-нет)"<<endl;
				cin>>c;
				if (c=='y')
				{
					cout<<"Велосипедист выехал"<<endl;
					hours = (this->energy/this->usage);
					h = hours;
					this->energy = 0;
					if (b)
						while(hours>=1)
						{
							sleep(1);
							cout<<'.'<<endl;
							hours -= 1;
						}
					hours = (h*this->GetSpeed())*100/x;
					cout<<"Велосипедист падает в изнеможении. Пройдено "<<hours<<"% пути."<<endl;
					break;
				}
				else
					if (c=='n')
					{
						cout<<"Решено никуда не ехать."<<endl;
						h=0;
						break;
					}
					else
						cout<<"Не понимаю вас."<<endl<<"Попробуйте еще раз."<<endl;
			}
		}
		if (h!=0)
			this->SetMileage(this->GetMileage()+h*this->GetSpeed());
		return hours;
	}
};
class Info
{
//private:
	Transport* T;
public:
	void SetTransport(Transport &x){this->T=&x;};
	Transport* GetTransport() const {return this->T;};
	Info(Transport* T = NULL):T(T){};
	Info(Transport &T){this->SetTransport(T);};
	Info(const Info&x){this->SetTransport(*(x.GetTransport()));};
	Info & operator=(const Info&x)
	{
		if (this != &x)
			this->SetTransport(*(x.GetTransport()));
		return *this;
	}
	~Info(){};
	void info()
	{
		if (this->T!=NULL)
		{
			cout<<"Info:"<<endl;
			cout<<"Пробег: "<<T->GetMileage()<<" км;"<<endl;
			cout<<"Вместимость: "<<T->GetCapacity()<<" чел.;"<<endl;
			cout<<"Чистый вес транспорта: "<<T->GetWeight()<<" кг;"<<endl;
			cout<<"Стредняя скорость: "<<T->GetSpeed()<<" км/ч;"<<endl;
		}
	}
};
int main()
{
	Car c;
	c.ride(200000);
	if (c.GetFuel()<5)
		c.refill();
	c.ride(-2000);

	Bicycle b;
	b.ride(100);
	if (b.GetEnergy()<5)
		b.rest();
	b.ride(-15);
	Info i1(b), i2;
	i2.SetTransport(c);
	i1.info();
	i2.info();

	return 0;
}