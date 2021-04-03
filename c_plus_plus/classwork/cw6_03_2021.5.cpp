
operator char*()const
operator const char*()const
operator +(const Str&)const
operator +(const char*)const
operator +=(const Str&)const
operator [](int)
operator >>
operator <<

class Str{
	int len;
	char *str;
	public char*()const{
		char *s =new char[len+1];
		strpy(s,str);
		return s;
	}

	operator const char *() const{
		return str;
	}
	Str operator +(const Str&x)const{
		Str ret;
		Ret.len=x.len +len;
		char *S=new char[ret.len+1];
		s[0]='\0';
		s=strcat(s,str);
		strcat(s,x.str);
		//ret.str=s;
		Str s1(s);
		delete s;
		return s1;
	}
	Str operator +(const char *)const{
		Srt res(s);
		return (*this+res);
	}//сработает и без этого
	Str operator +=(const char &x){
		len = x.len;
		char*s = new char [len+1];
		strcat(s,x.str);
		selete[]str;
		str=s;
		return *this;
	}
	char& operator [](const int &x)const
	{
		return *(this->str+x);
	}
	int operator[](const char x)const{
		for(int i=0, i<len,i++){
			if(str[i]==x)return i;
		}
	}
	friend str::istream&operator>>(const istream &s, const Str &x){
		s>>x.str;
		x.len=strlen(x.s);
		return s;
	}
	friend ostream& operator<<(const ostream &s, const Str &x)
	{
		s<<X.str;
		return s;
	}
	
}
s4=s1+s2+s3;
s4+=s1;