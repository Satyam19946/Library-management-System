#include<fstream.h>
#include<stdio.h>
#include<conio.h>
//Classes
class book
{
  int bno;
  char title[40];
  char author[40];
  char publisher[40];
  float price;
  int mno;
public:
  book(){mno=0;}
  void addb();
  void dispb();
  int rbno(){return bno;};
  int rmno(){return mno;};
  void issuetom(int m){mno=m;};
  void returned(){mno=0;};
};
class member
{
  int mno;
  char name[40];
  char mobile[10];
  char email[40];
  int bno;
public:
  member(){bno=0;};
  void addm();
  void dispm();
  void bookissued(int b){bno=b;};
  int rmno(){return mno;};
  int rbno(){return bno;};
  void returned(){bno=0;};
};
//Function Prototypes
void createb();
void dispb();
void searchb();
void modifyb();
void createm();
void dispm();
void searchm();
void modifym();
void issue();
void returnthebook();
void memberswithbooks();
void availablebooks();
void issuedbooks();
void Book();
void Member();
void Utility();
void Reports();

//Main function

void main()
{
  int ch;
  clrscr();
  do
  {
  cout<<"MAIN MENU"<<endl;
  cout<<"1.Book 2.Member 3.Utility 4.Reports 5.Quit"<<endl;
  cin>>ch;
  switch(ch)
    {
      case 1:Book();break;
      case 2:Member();break;
      case 3:Utility();break;
      case 4:Reports();break;
      case 5:cout<<"Thank You!!"<<endl;
    }
  }while(ch!=5);
  getch();
}

//Function Definations


void book::addb()
{
  cout<<"Book number:";cin>>bno;
  cout<<"Title:";gets(title);
  cout<<"Author:";gets(author);
  cout<<"Publisher:";gets(publisher);
  cout<<"Price:";cin>>price;
}
void book::dispb()
{
  cout<<"Book number:"<<bno<<endl;
  cout<<"Title:"<<title<<endl;
  cout<<"Author:"<<author<<endl;
  cout<<"Publisher:"<<publisher<<endl;
  cout<<"Price:"<<price<<endl;
}
void createb()
{
  book b;
  fstream f;
  char ch;
  f.open("BOOK.DAT",ios::binary|ios::app);
  do
  {
    b.addb();
    f.write((char*)&b,sizeof(b));
    cout<<"MORE(Y/N):";cin>>ch;
  }while(ch=='y'||ch=='Y');
  f.close();
}
void displayb()
{
  book b;
  fstream f;
  f.open("BOOK.DAT",ios::binary|ios::in);
  while(f.read((char*)&b,sizeof(b)))
    b.dispb();
  f.close();
}
void searchb()
{
  book b;
  cout<<"Book Number to Search:";int n;cin>>n;
  fstream f;
  f.open("BOOK.DAT",ios::binary|ios::in);
  char ch;
  while(f.read((char*)&b,sizeof(b)))
    if(n==b.rbno())
       b.dispb();
  f.close();
}
void modifyb()
{
  book b;
  cout<<"Book Number to Modify:";
  int n,found=0;
  cin>>n;
  fstream f;
  f.open("BOOK.DAT",ios::binary|ios::in|ios::out);
  while(f.read((char*)&b,sizeof(b))&&!found)
    {
      if(n==b.rbno())
	{
	  cout<<"Enter The new Details"<<endl;
	  f.seekg(f.tellg()-sizeof(b));
	  b.addb();
	  f.write((char*)&b,sizeof(b));
	  found++;
	}
    }
  if(!found)
    cout<<"No Such Book In the Library"<<endl;
  f.close();
}
void member::addm()
{
  cout<<"Member Number:";cin>>mno;
  cout<<"Member Name:";gets(name);
  cout<<"Mobile Number:";gets(mobile);
  cout<<"Email:";gets(email);
}
void member::dispm()
{
  cout<<"Member Number:"<<mno<<endl;
  cout<<"Member Name:"<<name<<endl;
  cout<<"Mobile Number:"<<mobile<<endl;
  cout<<"Email:"<<email<<endl;
}
void createm()
{
  member m;
  fstream f;
  char ch;
  f.open("MEMBER.DAT",ios::binary|ios::app);
  do
  {
    m.addm();
    f.write((char*)&m,sizeof(m));
    cout<<"MORE(Y/N)"<<endl;
    cin>>ch;
  }while(ch=='y'||ch=='Y');
  f.close();
}
void displaym()
{
  member m;
  fstream f;
  f.open("MEMBER.DAT",ios::binary|ios::in);
  while(f.read((char*)&m,sizeof(m)))
    m.dispm();
  f.close();
}
void searchm()
{
  member m;
  cout<<"Member Number to Search:";
  int n,found=0;
  cin>>n;
  fstream f;
  f.open("MEMBER.DAT",ios::binary|ios::in);
  while(f.read((char*)&m,sizeof(m))&&!found)
    {
      if(n==m.rmno())
	{
	  m.dispm();
	  found++;
	}
    }
  if(!found)
    cout<<"No Such Member In the Library"<<endl;
  f.close();
}
void modifym()
{
  member m;
  cout<<"Member Number to Modify:";
  int n,found=0;
  cin>>n;
  fstream f;
  f.open("MEMBER.DAT",ios::binary|ios::in|ios::out);
  while(f.read((char*)&m,sizeof(m))&&!found)
    {
      if(n==m.rmno())
	{
	  cout<<"Enter The new Details"<<endl;
	  m.addm();
	  f.seekg(f.tellg()-sizeof(m));
	  f.write((char*)&m,sizeof(m));
	  found++;
	}
    }
  if(!found)
    cout<<"No Such Member In the Library"<<endl;
  f.close();
}
void issue()
{
  book b;
  member m;
  int bn,mn,found=0;
  cout<<"Book Number:";cin>>bn;
  cout<<"Member Number:";cin>>mn;
  fstream f1,f2;
  f1.open("BOOK.DAT",ios::binary|ios::in|ios::out);
  f2.open("MEMBER.DAT",ios::binary|ios::out|ios::in);
  while(f1.read((char*)&b,sizeof(b))&&!found)
  {
    if(b.rmno()==0&&b.rbno()==bn)
    {
      found++;
      b.issuetom(mn);
      while(f2.read((char*)&m,sizeof(m)))
      {
	if(m.rmno()==mn)
	{
	  m.bookissued(bn);
	  f2.seekg(f2.tellg()-sizeof(m));
	  f2.write((char*)&m,sizeof(m));
	}
      }
      f1.seekg(f1.tellg()-sizeof(b));
      f1.write((char*)&b,sizeof(b));
  }
 }
  f1.close();
  f2.close();
  if(!found)
    cout<<"This Book is Unavailable"<<endl;
}
void returnthebook()
{
  book b;
  member m;
  int bn,mn,found=0;
  cout<<"Book Number:";cin>>bn;
  cout<<"Member Number:";cin>>mn;
  fstream f1,f2;
  f1.open("BOOK.DAT",ios::binary|ios::in|ios::out);
  f2.open("MEMBER.DAT",ios::binary|ios::out|ios::in);
  while(f1.read((char*)&b,sizeof(b))&&!found)
  {
    if(b.rmno()==0&&b.rbno()==bn)
    {
      found++;
      b.returned();
      while(f2.read((char*)&m,sizeof(m)))
      {
	if(m.rmno()==mn)
	{
	  m.returned();
	  f2.seekg(f2.tellg()-sizeof(m));
	  f2.write((char*)&m,sizeof(m));
	}
      }
      f1.seekg(f1.tellg()-sizeof(b));
      f1.write((char*)&b,sizeof(b));
  }
  }
  f1.close();
  f2.close();
}
void availablebooks()
{
  book b;
  fstream f;
  f.open("BOOK.DAT",ios::binary|ios::in);
  while(f.read((char*)&b,sizeof(b)))
    if(b.rmno()==0)
      b.dispb();
  f.close();
}
void memberswithbooks()
{
  member m;
  fstream f;
  f.open("MEMBER.DAT",ios::binary|ios::in);
  while(f.read((char*)&m,sizeof(m)))
    if(m.rbno()!=0)
      m.dispm();
  f.close();
}
void issuedbooks()
{
  book b;
  fstream f;
  f.open("BOOK.DAT",ios::binary|ios::in);
  while(f.read((char*)&b,sizeof(b)))
    if(b.rmno()!=0)
      b.dispb();
  f.close();
}
void Book()
{
  int ch;
  do
  {
  cout<<"1.Enter 2.Display 3.Search 4.Modify 5.Main Menu"<<endl;
  cin>>ch;
  switch(ch)
  {
    case 1:createb(); break;
    case 2:displayb(); break;
    case 3:searchb(); break;
    case 4:modifyb(); break;
    case 5:cout<<"Return to Main Menu"<<endl; break;
    default:cout<<"Invalid Entry"<<endl;
  }
  }while(ch!=5);
}
void Member()
{
  int ch;
  do
  {
  cout<<"1.Enter 2.Display 3.Search 4.Modify 5.Main Menu"<<endl;
  cin>>ch;
  switch(ch)
  {
    case 1:createm(); break;
    case 2:displaym(); break;
    case 3:searchm(); break;
    case 4:modifym(); break;
    case 5:cout<<"Return to Main Menu"<<endl; break;
    default:cout<<"Invalid Entry"<<endl;
  }
  }while(ch!=5);
}
void Utility()
{
  int ch;
  do
  {
  cout<<"1.Issue 2.Return 3.Main Menu"<<endl;
  cin>>ch;
  switch(ch)
  {
    case 1:issue();break;
    case 2:returnthebook();break;
    case 3:cout<<"Returning to Main Menu"<<endl; break;
    default:cout<<"Invalid Entry"<<endl;
  }
  }while(ch!=3);
}
void Reports()
{
  int ch;
  do
  {
  cout<<"1.Available Books 2.Issued Books 3.Members with books 4.Main Menu"<<endl;
  cin>>ch;
  switch(ch)
  {
    case 1:availablebooks(); break;
    case 2:issuedbooks(); break;
    case 3:memberswithbooks();break;
    case 4:cout<<"Returning To Main Menu"<<endl; break;
    default:cout<<"Invalid Choice"<<endl;
  }
 }while(ch!=4);
}
