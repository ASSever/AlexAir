#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;
//Severinov Alexandr 
int strlen(char * s)
{
  int i = 0;
  while (s[i] != '\0')
    {i++;}
  return i;
}
class StrModule
{
  char *name;
  StrModule *next;
public:
  void SetName(const char*s)
  {
    if(s != NULL)
    {
      // if (this->name != NULL)
      // {
      //   delete[] this->name;
      //   this->name = NULL;
      // }
      this->name = new char [strlen(s)+1];
      strcpy(this->name,s);
    }
  }
  void SetNext(StrModule *h){this->next=h;}
  char* GetName() const {return this->name;}
  StrModule* GetNext() const {return this->next;}
  StrModule(const char *name = NULL, StrModule *next = NULL):
  name(NULL),next(next)
  {this->SetName(name);}
  StrModule(const StrModule&x)
  {
    this->SetName(x.GetName());
    this->SetNext(x.GetNext());
  }
  StrModule & operator=(const StrModule &x)
  {
    if (this != &x)
    {
      this->SetName(x.GetName());
      this->SetNext(x.GetNext());
    }
    return *this;
  }
  ~StrModule(){delete[] this->name;};
  friend ostream& operator<<(ostream &out, const StrModule &x);
};
ostream& operator<<(ostream &out, const StrModule &x)
{
    out<<x.GetName();
    return out;
}
class Block
{
  static int global_count;
  int number;
  //0
  StrModule *(host[2]);
  //1
  StrModule *(package[2]);
  //помещает хост/пакет (цепь хостов/пакетов) между существующими или ставит последним если i больше количества существующих
  StrModule*& First(bool b) {return (b)? this->package[0]: this->host[0];}
  StrModule*& Last(bool b) {return (b)?this->package[1]:this->host[1];}
  void SetStrModule(bool Bool, StrModule * h, int i = 1) 
  {
    StrModule *l = h;
    if (h != NULL)
    {
      while (l->GetNext() != NULL)
        l = l->GetNext();

      if (this->Last(Bool) == NULL)
      {
        this->First(Bool) = h;
        this->Last(Bool) = l;
      }
      else
      {
        if (i == 1)
        {
          l->SetNext(this->First(Bool));
          this->First(Bool) = h;
        }
        else
        {  
          int j = 1;
          StrModule *target = this->First(Bool);
          while((target->GetNext()!=NULL)&&(j+1<=i))
          {
            target = target->GetNext();
            j++;
          }
          if (target->GetNext() == NULL)
            this->Last(Bool) = l;
          target->SetNext(h);
        }
      }
    }
  }
  void SetHost(StrModule * h, int i = 1){this->SetStrModule(0,h,i);}
  void SetPackage(StrModule * h, int i = 1){this->SetStrModule(1,h,i);}
public:
  StrModule *GetStrModule(bool Bool, int i = 1) const
  {
    StrModule *target;
    if (Bool)
      target = this->package[0];
    else
      target = this->host[0];
    if (target == NULL)
      return NULL;
    int j = 1;
    while((target->GetNext()!=NULL)&&(j+1<=i))
    {
      target = target->GetNext();
      j++;
    }
    return target;
  }
  StrModule *GetHost(int i = 1) const {return this->GetStrModule(0,i);}
  StrModule *GetPackage(int i = 1) const {return this->GetStrModule(1,i);}
  int GetNumber() const {return this->number;}
  void NewStrModule(bool Bool, const char *s)
  {
    StrModule *h = new StrModule(s);
    this->SetStrModule(Bool,h);
  }
  void NewHost(const char *s)
  {
    StrModule *p = new StrModule(s);
    this->SetStrModule(0,p);
  }
  void NewPackage(const char *s)
  {
    StrModule *p = new StrModule(s);
    this->SetStrModule(1,p);
  }
  void AsNew()
  {
    this->global_count++;
    this->number = this->global_count;
  }
  void UnNumber()
  {
    this->global_count--;
    this->number = 0;
  }
  Block()
  {
    this->global_count++;
    this->number = this->global_count;
    this->host[0]=this->host[1]=this->package[0]=this->package[1]=NULL;
  }
  bool empty(bool b = false){return (this->First(b) == NULL);}
  int size(bool Bool = 0) const
  {
    StrModule *cur;
    if (Bool)
      cur = this->package[0];
    else
      cur = this->host[0];
    int i = 0;
    while (cur != NULL)
    {
      cur = cur->GetNext();
      i++;
    }
    return i;
  }
  void DelSrtModuleLine(StrModule * first)
  {
    StrModule * cur;
    while (first != NULL)
    {
      cur = first->GetNext();
      delete first;
      first = cur;
    }
  }
  Block(const Block&x)
  {
    int n;
    this->global_count++;
    this->number = this->global_count;
    cout<<"constr "<<this->global_count<<endl;
    if ((this->host[0] = x.GetHost(1)) == NULL)
      this->host[1] = NULL;
    else
      this->host[1] = x.GetHost(x.size());
    if ((this->package[0] = x.GetPackage(1)) == NULL)
      this->package[1] = NULL;
    else
      this->package[1] = x.GetPackage(x.size());
  }
  Block & operator=(const Block &x)
  {
    if (this != &x)
    {
      //при создании и так увеличится
      // this->global_count++;
      // this->number = this->global_count;
      if ((this->host[0] = x.GetHost(1)) == NULL)
        this->host[1] = NULL;
      else
        this->host[1] = x.GetHost(x.size());
      if ((this->package[0] = x.GetPackage(1)) == NULL)
        this->package[1] = NULL;
      else
        this->package[1] = x.GetPackage(x.size());
    }
    return *this;
  }
  //никакого копирования или присваивания
  ~Block()
  {
    if (this->First(0) == NULL)
      this->global_count--;
    // if (this->number != 0)
    this->DelSrtModuleLine(this->GetHost());
    this->DelSrtModuleLine(this->GetPackage());
  }
  friend ostream& operator<<(ostream &out, const Block &x);
};
ostream& operator<<(ostream &out, Block &x)
{
  out<<"Block "<<x.GetNumber()<<":\n";
  out<<"  hosts:\n";
  StrModule *h = x.GetHost();
  while (h != NULL)
  {
    out<<"  - "<<h->GetName()<<endl;
    h = h->GetNext();
  }
  out<<"  packages:\n";
  StrModule *p = x.GetPackage();
  while (p != NULL)
  {
    out<<"  - "<<p->GetName()<<endl;
    p = p->GetNext();
  }
  return out;
}
int Block::global_count=0;
Block GetHostNames(const char * file_name)
{
  ifstream hosts_file(file_name);
  Block b;
  if (hosts_file.is_open()==0)
  {
    cout<<"ERROR opening "<<file_name<<endl;
    return b;
  }
  int position, end;
  string line, host;
  bool hosts = false;
  while(getline(hosts_file, line))
  {
    if (line.find("  hosts:",0)!=string::npos)
      hosts = true;
    if (hosts)
    {
      position = 0;
      while ((position<line.size())&&(line[position] == ' ')){position++;}
      end = position;
      while ((end<line.size())&&(line[end] != ':')){end++;}
      if ((position == 4)&&(end<line.size()))
        b.NewHost((line.substr(position, end-position)).c_str());
    }
  }
  hosts_file.close();
  return b;
}
bool Empty(string s)
{
  int i = 0;
  while ((i<s.size())&&((s[i] == ' ')||(s[i] == '\n')||(s[i] == ' '))){i++;}
  return (i == s.size());
}
void ExecPlay(string file_name, string hosts_name, string ansible_dir)
{

}
void FillPlay(ofstream& out, Block& block)
{
  out<<"- hosts:\n";
  StrModule * cur = block.GetHost();
  while (cur != NULL)
  {
    out<<"  - "<<cur->GetName()<<endl;
    cur = cur->GetNext();
  }
  cur = block.GetPackage();
  out<<"  tasks:\n";
  out<<"  - name: massage"<<block.GetNumber()<<endl;
  out<<"    ansible.builtin.debug:\n";
  out<<"      msg: >-\n";
  out<<"        package_list:\n";
  while (cur != NULL)
  {
    out<<"        "<<cur->GetName()<<endl;
    cur = cur->GetNext();
  }
  out<<"  - name: task"<<block.GetNumber()<<endl;
  out<<"    become: true\n";
  out<<"    become_method: sudo\n";
  out<<"    block:\n";
  cur = block.GetPackage();
  while (cur != NULL)
  {
    out<<"    - name: "<<cur->GetName()<<endl;
    out<<"      block:\n";
    out<<"      - name: install "<<cur->GetName()<<endl;
    out<<"        ansible.builtin.package:\n";
    out<<"          name: \n";
    out<<"          - "<<cur->GetName()<<endl;
    out<<"          state: present\n";
    // out<<"      rescue:\n";
    // out<<"      - name: remove "<<cur.GetName()<<endl;
    // out<<"        ansible.builtin.package:\n";
    // out<<"          name: \n";
    // out<<"          - "<<cur.GetName()<<endl;
    // out<<"          state: absent\n";

    cur = cur->GetNext();
  }
  out<<"    rescue:\n";
  cur = block.GetPackage();
  while (cur != NULL)
  {
    out<<"    - name: remove "<<cur->GetName()<<endl;
    out<<"      ansible.builtin.package:\n";
    out<<"        name: \n";
    out<<"        - "<<cur->GetName()<<endl;
    out<<"        state: absent\n";

    cur = cur->GetNext();
  }
}
void ToCout(Block& hosts, Block& package_info)
{
  StrModule *cur1, *cur2, *cur3;
  cur1 = package_info.GetPackage();
  cur2 = package_info.GetHost();
  cur3 = hosts.GetPackage();
  bool b = (cur3->GetName()[0] != ' ');
  cout<<"Block:\n";
  while (cur1 != NULL)
  {
    cout<<cur1->GetName()<<" "<<cur2->GetName();
    if (b)
      cout<<"=> remove "<<cur3->GetName()<<endl;
    cur1 = cur1->GetNext();
    cur2 = cur2->GetNext();
    cur3 = cur3->GetNext();
  }
}
bool OutToCout(string file_name = "output.txt")
{
  char c;///////////////
  ifstream input_file(file_name);
  if (input_file.is_open()==0)
  {
    cout<<"ERROR opening "<<file_name<<endl;
    return false;
  }
  //этап 0 => нашли play и забираем хосты
  //этап 1=>ищем только package_list и забираем все пакеты
  //этап 2=>ищем TASK [install и TASK [remove забираем инфу о хосте и итогах установки
  //этап 3=>ищем TASK [remove забираем инфу о хосте и итогах установки
  string line, sub_line, cur_line = "", DT_host_reaction = "";
  int stage = -1;
  int position = 0;
  Block package_info, hosts;
  StrModule *cur1, *cur2, *cur3, *cur4;
  char *str_line = NULL;
  bool Fail = false;
        // cur1 = package_info.GetPackage();
        // cur2 = package_info.GetHost();
        // cur3 = hosts.GetPackage();
        // cur4 = hosts.GetHost();
  while(getline(input_file, line))
  {
    // if(Empty(line))
    //   continue;
    if (line.find("PLAY RECAP ",0)!=string::npos)
      break;
    if (line.find("PLAY [",0)!=string::npos)//выводим все что было и обнуляем все
    {
      if (Fail)
      {
        if (cur_line.size()>0)
        {
          cur3->SetName(cur_line.c_str());
          cur_line = "";
        }
      }
      else
        if (cur_line.size()>0)
        {
          cur2->SetName(cur_line.c_str());//записывает cur_line в список package_info в хост (cur2)
          cur_line = "";
        }

      cur2 = package_info.GetHost();
      while (cur2 != NULL)
      {
        if (cur2->GetName()[0] != ' ')
          break;
        cur2 = cur2->GetNext();
      }
      if (cur2 != NULL)
      {
        cur2 = package_info.GetHost();
        while (cur2 != NULL)
        {
          if (cur2->GetName()[0] == ' ')
            cur2->SetName(DT_host_reaction.c_str());
          cur2 = cur2->GetNext();
        }
      }
      if ((hosts.empty(0) == false)&&(package_info.empty(0) == false))
        ToCout(hosts,package_info);
      //cout<<"+++++++++++++++++++++++play1"<<hosts<<package_info<<endl;
      //начинаем обнулять
      Fail = false;
      cur1 = cur2 = cur3 = cur4 = NULL;
      hosts = Block();
      hosts.UnNumber();
      package_info = Block();
      package_info.UnNumber();
      cur_line = "";
      sub_line = line;
      stage = 0;
      continue;
    }
    if ((stage == 0)&&(line.find("TASK [massage",0)!=string::npos))
    {
      cur4 = hosts.GetHost();
      DT_host_reaction = "";
      while (cur4 != NULL)
      {
        DT_host_reaction += cur4->GetName();
        DT_host_reaction += "\033[35m[DT] \033[39m";//32-зеленый 35-пурпурный 39-обычный 31-красный DT-didnt try
        cur4 = cur4->GetNext();
      }
      sub_line = line;
      stage = 1;
      continue;
    }
    if ((stage <= 2)&&(line.find("TASK [install",0)!=string::npos))
    {
      position = -1;
      sub_line = line;
      stage = 2;
      continue;
    }
    if ((stage >= 2)&&(line.find("TASK [remove",0)!=string::npos))
    {
      if ((Fail == false)&&(cur_line.size()>0))
      {
        //str_line = strdup(sub_line.c_str());
        cur2->SetName(cur_line.c_str());//записывает cur_line в список package_info в хост (cur2)
      }
      else
      {
        cur3->SetName(cur_line.c_str());
      }

      cur_line = "";
      sub_line = line;
      position = -1;
      stage = 3;
      continue;
    }
    //cout<<stage<<endl;//cin>>c;///////////////
    //cout<<"до sub_line:"<<sub_line<<" line:"<<line<<" cur_line:"<<cur_line<<endl;
    switch (stage)
    {
    case 0:
      position = 6;//это первый нужный символ после PLAY [
      while ((position<sub_line.size())&&(sub_line[position]!=']'))
      {
        if ((sub_line[position] == ',')&&(cur_line.size() > 0))
        {
          hosts.NewHost(cur_line.c_str());
          cur_line = "";
        }
        else
          cur_line += sub_line[position];
        position++;
      }
      if (sub_line.size() > 0)
        hosts.NewHost(cur_line.c_str());
      cur_line = "";
      sub_line = "";
      break;
    case 1:
      if ((package_info.empty(1))&&(line.find("package_list: ",0)!=string::npos))
      {
        position = 26;//это первый нужный символ после package_list: 
        while ((position<line.size())&&(line[position]!='\"'))
        {
          if ((line[position] == ' ')&&(cur_line.size() > 0))
          {
            package_info.NewPackage(cur_line.c_str());
            package_info.NewHost(DT_host_reaction.c_str());
            hosts.NewPackage(" ");
            cur_line = "";
          }
          else
            cur_line += line[position];
          position++;
        }
        package_info.NewPackage(cur_line.c_str());
        package_info.NewHost(DT_host_reaction.c_str());
        hosts.NewPackage(" ");
      }
      cur_line = "";
      sub_line = "";
      break;
    case 2:
      if (position == -1)
      {
        if (cur_line.size()>0)
        {
          //str_line = strdup(sub_line.c_str());
          cur2->SetName(cur_line.c_str());//записывает cur_line в список package_info в хост (cur2)
          cur_line = "";
        }
        position = 14;//это первый нужный символ после TASK [install 
        cur1 = package_info.GetPackage();
        cur2 = package_info.GetHost();
        cur3 = hosts.GetPackage();
        while ((cur1!=NULL)&&(sub_line.find(cur1->GetName(),0)==string::npos))
        {
          cur1 = cur1->GetNext();
          cur2 = cur2->GetNext();
          cur3 = cur3->GetNext();
        }
        if (cur1==NULL)
        { 
          cout<<"НЕ НАШЛИ НУЖНЫЙ ПАКЕТ\n";
          while ((position<sub_line.size())&&(sub_line[position]!=']'))
          {
            cur_line += sub_line[position];
            position++;
          }
          package_info.NewPackage(cur_line.c_str());
          package_info.NewHost(DT_host_reaction.c_str());
          hosts.NewPackage(" ");
          cur1 = package_info.GetPackage();
          cur2 = package_info.GetHost();
          cur3 = hosts.GetPackage();
          cur_line = "";
          while (cur1->GetNext()!=NULL)
          {
            cur1 = cur1->GetNext();
            cur2 = cur2->GetNext();
            cur3 = cur3->GetNext();
          }
        }
        cur_line = "";
        sub_line = "";
      }
      if(Empty(line))
        continue;
      cur4 = hosts.GetHost();
      while ((cur4!=NULL)&&(line.find(cur4->GetName(),0)==string::npos))
      {
        cur4 = cur4->GetNext();
      }
      if (cur4==NULL)//FAIL
      {
        cout<<"НЕТ ТАКОГО ХОСТА\n";
        continue;
        //cur4 = hosts.GetHost();
      }
      cur_line += cur4->GetName();
      if (line.find("FAIL",0)!=string::npos)
        cur_line += "\033[31m[FAIL] \033[39m";//32-зеленый 39-обычный 31-красный
      else
        cur_line += "\033[32m[OK] \033[39m";//32-зеленый 39-обычный 31-красный

      break;
    case 3:
      Fail = true;
      if (position == -1)
      {
        if (cur_line.size()>0)
        {
          cur3->SetName(cur_line.c_str());//записывает cur_line в список package_info в хост (cur2)
          cur_line = "";
        }

        position = 13;//это первый нужный символ после TASK [remove
        cur1 = package_info.GetPackage();
        cur2 = package_info.GetHost();
        cur3 = hosts.GetPackage();
        while ((cur1!=NULL)&&(sub_line.find(cur1->GetName(),0)==string::npos))
        {
          cur1 = cur1->GetNext();
          cur2 = cur2->GetNext();
          cur3 = cur3->GetNext();
        }
        if (cur1==NULL)
        { 
          cout<<"НЕ НАШЛИ ПАКЕТ\n";
          while ((position<sub_line.size())&&(sub_line[position]!=']'))
          {
            cur_line += sub_line[position];
          }
          package_info.NewPackage(cur_line.c_str());
          package_info.NewHost(DT_host_reaction.c_str());
          hosts.NewPackage(" ");
          cur_line = "";
          cur1 = package_info.GetPackage();
          cur2 = package_info.GetHost();
          cur3 = hosts.GetPackage();
          while (cur1->GetNext()!=NULL)
          {
            cur1 = cur1->GetNext();
            cur2 = cur2->GetNext();
            cur3 = cur3->GetNext();
          }
        }
        cur_line = "";
        sub_line = "";
      }
      //cout<<"---------------------------case4"<<cur1->GetName()<<endl;
      if(Empty(line))
        continue;
      cur4 = hosts.GetHost();
      while ((cur4!=NULL)&&(line.find(cur4->GetName(),0)==string::npos))
      {
        cur4 = cur4->GetNext();
      }
      if (cur4==NULL)//FAIL
      {
        cout<<"НЕТ ТАКОГО ХОСТА\n"<<line<<endl;
        continue;
        //cur4 = hosts.GetHost();
      }
      cur_line += cur4->GetName();
      if (line.find("FAIL",0)!=string::npos)
        cur_line += "\033[31m[FAIL] \033[39m";//32-зеленый 39-обычный 31-красный
      else
        cur_line += "\033[32m[OK] \033[39m";//32-зеленый 39-обычный 31-красный
      break;
    }
    //cout<<hosts<<package_info<<endl;
    //cout<<"после sub_line:"<<sub_line<<" line:"<<line<<" cur_line:"<<cur_line<<endl;
    //cout<<"ufter while\n";//cin>>c;///////////////
  }
  cur3 = hosts.GetPackage();
  while (cur3 != NULL)
  {
    if (cur3->GetName()[0] != ' ')
      break;
    cur3 = cur3->GetNext();
  }
  if (cur3 != NULL)
  {
    cur3 = hosts.GetPackage();
    while (cur3 != NULL)
    {
      if (cur3->GetName()[0] == ' ')
        cur3->SetName(DT_host_reaction.c_str());
      cur3 = cur3->GetNext();
    }
  }
  ToCout(hosts,package_info);
  return true;
}
bool FileInputExec(string file_name, Block& hosts, string ansible_dir, string cur_dir, string hosts_name)
{
  char c;/////////////
  ifstream input_file(file_name);
  if (input_file.is_open()==0)
  {
    cout<<"ERROR opening "<<file_name<<endl;
    return false;
  }
  string line;
  char* s;
  StrModule * cur_host = NULL;
  Block b;
  string output_txt = cur_dir;
  output_txt += "output";
  output_txt += to_string(b.GetNumber());
  output_txt += ".txt";
  string output_file_name = cur_dir;
  output_file_name += "play";
  output_file_name += to_string(b.GetNumber());
  output_file_name += ".yaml";
  ofstream out;
  out.open(output_file_name);
  while(getline(input_file, line))
  {
    //при онлайн обработке здесь нужно записывать в файл и обнулять блок
    if (Empty(line))
      continue;
    cur_host = hosts.GetHost();
    while(cur_host != NULL)
    {
      if (line.find((s = cur_host->GetName()),0)!=string::npos)
      {
        if (b.empty(1) == false)//уже находили пакеты
        {
          FillPlay(out,b);
          b = Block();
          b.AsNew();
        }
        b.NewHost(s);
        break;
      }
      cur_host = cur_host->GetNext();
    }
    if (cur_host != NULL)//значит в этой строке нашли хост из списка
      continue;
    char * array_line = NULL;
    array_line = strdup(line.c_str());
    if ((s = strtok(array_line," ")) != NULL)//на первое не смотрим ибо ansible автоматически выберет через что устанавливать
      while((s = strtok(NULL," ")) != NULL) {b.NewPackage(s);}
  }
  input_file.close();
  if ((b.empty(0) == false)&&(b.empty(1) == false))
    FillPlay(out,b);
  out.close();
  string ansible_playbook_full = ansible_dir;
  ansible_playbook_full += "ansible-playbook";
  int status;
    if((fork()) == 0 )
    {
      /* порожденный процесс */
      int fd = creat(output_txt.c_str(), O_WRONLY | O_CREAT | O_TRUNC);
      if(fd < 0){cout<<"Can not open file\n"; return 0;}
      dup2(fd, 1);
      close(fd);
      if (hosts_name.size()>0)
      {
        string hosts_name_full;
        if (hosts_name[0] == '.')
          hosts_name_full = hosts_name;
        else
        {
          hosts_name_full = cur_dir;
          hosts_name_full += hosts_name;
        }
        //execl(ansible_playbook_full.c_str(), "ansible-playbook", output_file_name.c_str(), "-i", hosts_name_full.c_str(), NULL);
        execl("/Users/alex/Library/Python/3.8/bin/ansible-playbook", "ansible-playbook", "/Users/alex/Documents/SP_2-3/play1.yaml", NULL);
      }
      else
        execl("/Users/alex/Library/Python/3.8/bin/ansible-playbook", "ansible-playbook", "/Users/alex/Documents/SP_2-3/play1.yaml", NULL);
      cout<<"exec не удался\n";
      exit(1);
    }
    wait(&status);
    OutToCout(output_txt.c_str());
  //обработка записанного файла
  return true;
}
string HostInLine(string line)
{
  int pos = 0;
  string s = "";
  if ((pos = line.find("-h",0))!=string::npos)
    while ((pos+2<line.size())&&(line[pos + 2] != ' ')&&(line[pos + 2] != ' ')&&(line[pos + 2] != '\n'))
    {
      s += line[pos + 2];
      pos++;
    }
    return s;
}
string FileNameInLine(string line)
{
  int pos = 0;
  string s = "";
  if ((pos = line.find("-f",0))!=string::npos)
    while ((pos+2<line.size())&&(line[pos + 2] != ' ')&&(line[pos + 2] != ' ')&&(line[pos + 2] != '\n'))
    {
      s += line[pos + 2];
      pos++;
    }
    return s;
}
bool QuitInLine(string line){return (line.find("-q",0)!=string::npos);}

int main(int argc, char const *argv[]) 
{
  char c;/////////
  string ansible_dir = "/Users/alex/Library/Python/3.8/bin/";
  string hosts_file_name = "/Users/alex/Documents/SP_2-3/hosts/hosts.yaml";
  Block hosts = GetHostNames(hosts_file_name.c_str());
  hosts.UnNumber();
  string file_name, line;
  bool file = true;
  if (argc == 2)
  {
    if ((argv[1][0]=='.')&&(argv[1][1]=='/'))
      file_name = argv[1];
    else
    {
      file_name = "./";
      file_name += argv[1];
    }
    cin>>c;
    FileInputExec(file_name,hosts,ansible_dir,"/Users/alex/Documents/SP_2-3/","");
  }
  ofstream out;
  string cur_hosts_file_name, cur_file_name;
  bool q = false;
  cin>>c;
  
  // while(true)
  // {
  //   out.open("./input.txt");

  //   getline(cin, line);
  //   if (Empty(line))
  //   {
  //     out.close();
  //     hosts = GetHostNames(hosts_file_name.c_str());
  //     FileInputExec(file_name,hosts,ansible_dir,"/Users/alex/Documents/SP_2-3/","");//hosts_file_name);
  //     if (q)
  //       return 0;
  //   }
  //   cur_hosts_file_name = HostInLine(line);
  //   cur_file_name = FileNameInLine(line);
  //   q = QuitInLine(line);
  //   if (cur_hosts_file_name.size() > 0)
  //     hosts_file_name = cur_hosts_file_name;
  //   if (cur_file_name.size() > 0)
  //     file_name = cur_file_name;
  //   else
  //     file_name = "./input.txt";
  //   if ((cur_file_name.size() > 0)&&(cur_hosts_file_name.size() > 0)&&(q==false))
  //     out<<line;
  // }
  return 0;
}
//-q
//-f file_name
//-h hosts_file_name