#include <iostream>
using namespace std;
class Miner
{
public:
	double dimond_per_hour;
	double dimonds;
	double money;
	double money_to_rubls;
	double money_quest;
	Miner(double a=0, double b=0, double c=0, double d=0, double e=0):
	dimond_per_hour(a),dimonds(b),money(c),money_to_rubls(d),money_quest(e){}
	double HoursToDimonds(double x=0){return x/(this->dimond_per_hour);};
	double DimondsToMoney(double x=0){return x*100/0.75;};
	double DimondsToMoneyRubls(double x=0){return x*100/0.25;};
	double MoneyRublsToRubls(double x=0){return x*10;};

	double HoursToMoney(double x=0){return this->HoursToDimonds(this->DimondsToMoney(x));};
	double HoursToMoneyRubls(double x=0){return this->HoursToDimonds(this->DimondsToMoneyRubls(x));};

	double DimondsToRubls(double x=0){return this->DimondsToMoneyRubls(this->MoneyRublsToRubls(x));};

	double HoursToRubls(double x=0){return this->HoursToDimonds(this->DimondsToMoneyRubls(this->MoneyRublsToRubls(x)));};

	void Time(double x)
	{
		cout<<"Time: ";
		if (x==0)
		{
			cout<<'0'<<endl;
			return;
		}
		int y = x;
		x -= y;
		int years = y/24/365;
		int days = (y/24)%365;
		int hours = y%24;
		x *= 60;
		y = x;
		x -= y;
		int minutes = y;
		x *= 60;
		y = x;
		x -= y;
		int seconds = y;
		int miliseconds = 1000*x;
		if (years > 0)
		{
			cout<<years<<" year";
			if (years >= 2)
				cout<<'s';
			if ((days+hours+minutes+seconds+miliseconds)>0)
				cout<<',';
		}
		if (days > 0)
		{
			cout<<days<<" day";
			if (days >= 2)
				cout<<'s';
			if ((hours+minutes+seconds+miliseconds)>0)
				cout<<',';
		}
		if (hours > 0)
		{
			cout<<hours<<" hour";
			if (hours >= 2)
				cout<<'s';
			if ((minutes+seconds+miliseconds)>0)
				cout<<',';
		}
		if (minutes > 0)
		{
			cout<<minutes<<" minute";
			if (minutes >= 2)
				cout<<'s';
			if ((seconds+miliseconds)>0)
				cout<<',';
		}
		if (seconds > 0)
		{
			cout<<seconds<<" second";
			if (seconds >= 2)
				cout<<'s';
			if (miliseconds>0)
				cout<<',';
		}
		if (miliseconds > 0)
		{
			cout<<miliseconds<<" milisecond";
			if (miliseconds >= 2)
				cout<<'s';
		}
		cout<<endl;
	}
	void ToDimonds(double x=0)
	{
		cout<<"Your speed - "<<this->dimond_per_hour<<" dimonds per hour\n\n";
		cout<<"To reach "<<x<<" Dimonds you need:\n";
		this->Time(this->HoursToDimonds(x));
	}
	void ToMoney(double x=0)
	{
		cout<<"Your speed - "<<this->dimond_per_hour<<" dimonds per hour\n\n";
		cout<<"To reach "<<x<<" Money you need:\n";
		cout<<"Dimonds: "<<this->DimondsToMoney(x)<<endl;
		this->Time(this->HoursToMoney(x));
	}
	void ToMoneyRubls(double x=0)
	{
		cout<<"Your speed - "<<this->dimond_per_hour<<" dimonds per hour\n\n";
		cout<<"To reach "<<x<<" MoneyRubls you need:"<<endl;
		cout<<"Dimonds: "<<this->DimondsToMoneyRubls(x)<<endl;
		this->Time(this->HoursToMoneyRubls(x));
	}
	void ToRubls(double x=0)
	{
		cout<<"Your speed - "<<this->dimond_per_hour<<" dimonds per hour\n\n";
		cout<<"To reach "<<x<<" Rubls you need:"<<endl;
		cout<<"MoneyRubls: "<<this->MoneyRublsToRubls(x)<<endl;
		cout<<"Dimonds: "<<this->DimondsToRubls(x)<<endl;
		this->Time(this->HoursToRubls(x));
	}
};
int main()
{
	Miner m1(100);
	char c;
	double x;
	cout<<"m34 - изминить скорость на 34"<<endl;
	cout<<"D34 - сколько нужно для получения 34 Dimonds"<<endl;
	cout<<"M34 - сколько нужно для получения 34 Money"<<endl;
	cout<<"r34 - сколько нужно для получения 34 MoneyRubls"<<endl;
	cout<<"R34 - сколько нужно для получения 34 Rubls"<<endl;
	cout<<"q - завершение"<<endl;
	while(1)
	{
		cin>>c;
		switch (c)
		{
		case 'm':
			cin>>m1.dimond_per_hour;
			cout<<"Теперь скорость "<<m1.dimond_per_hour<<" алмазов в секунду"<<endl;
			cout<<endl;
			break;
		case 'D':
			cin>>x;
			cout<<endl;
			m1.ToDimonds(x);
			cout<<endl;
			break;
		case 'M':
			cin>>x;
			cout<<endl;
			m1.ToMoney(x);
			cout<<endl;
			break;
		case 'r':
			cin>>x;
			cout<<endl;
			m1.ToMoneyRubls(x);
			cout<<endl;
			break;
		case 'R':
			cin>>x;
			cout<<endl;
			m1.ToRubls(x);
			cout<<endl;
			break;
		default:
			cout<<"Exit"<<endl;
			return 0;
		}
	}
	return 0;
};