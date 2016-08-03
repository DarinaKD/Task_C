// ConsoleText.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
 struct Deals {
	 char* deal;
	 Deals* next;
 };
 void strcop(char*, const char*);
 int devidedIntoDeals(char*,int, Deals*);

int main()
{
	FILE *fi, *fo;
	ifstream f;
	const char path[]="D:\\temp\\Text.dat";
	const int numbstr=70;
	char str[numbstr];
	char* buf;
	//fi=fopen(path,"r+");
	//if(fi==0){cout<<"Error in open file";return 1;}
	f.open(path, f.out);
	if(!f.is_open()){cout<<"Error in open file"; system("pause");return 1;}
	 
	//здесь получим размер файла
	f.seekg (0, ios::out);
     int len=0;
	 len= f.tellg();
     f.seekg (0, ios::beg);
	 
	 cout<<"file size "<<len;
	 //while(!eof(f))
	 buf=new char[len];
	  // читаем весь файл в память
	 f.read(buf,len);
	//закрываем файл
    f.close();
cout<<"\n";

HANDLE consoleOutput;
//COORD cursorPos;

	// Получаем хэндл консоли 
  consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); 
  CONSOLE_SCREEN_BUFFER_INFO bi;
  GetConsoleScreenBufferInfo(consoleOutput, &bi);
 

	// Задаем координаты курсора и перемещаем курсор
  
  	// Выводим строку
 // printf("Test string at position (30, 3)");

//streampos pos=tellp();
//tellp(); 

  cout.write (buf,len);
  
  char ch;
  cin>>ch;
  Deals *p;
  Deals* beg=new Deals;
	beg->next=NULL;
  int kol=devidedIntoDeals(buf,len, beg);
  int n=0;
  SetConsoleCursorPosition(consoleOutput, bi.dwCursorPosition);
   SetConsoleTextAttribute(consoleOutput, FOREGROUND_GREEN);
  p=beg; 
 do{
	 ch=getchar();
  if(ch=='a')
	  cout<<p->deal;
  } while((ch!='q') || (p->next!=NULL));

  cout<<"\n!"<<"\n";
 // cout.seekp(pos,ios::beg);
 //  pos=cout.tellp();
    cout<<"\n?"<<"\n";
//не забудем освободить память
//  delete[] buf;
	/*while(!feof(fi)){
		buf=fgets(str,numbstr,fi);
		puts(buf);
	}*/

	cout<<"\n";
	system("pause");
	return 0;
}

void strcop(char *strcopy, const char *str){
		while((*strcopy++=*str++)){ }
	}

int devidedIntoDeals(char* text,int sizet, Deals* beg){
	 int count=0;
	
	char* str=new char[200];
	for(int j=0; j<200; j++){
		str[j]='\0';
	}
	int k=0;
	Deals *prev;
	Deals *pv;
	
	prev=beg; pv=beg;
	for(int i=0; i<sizet; i++){
		str[k]=text[i];
		k++;
		
		if((text[i]=='.')||(text[i]=='!')||(text[i]=='?')||(i==sizet-1)){
		
			if(count>=1){pv=new Deals; prev=pv;}
			
			prev->deal=new char[k];
			prev->next=NULL;
			strcop(prev->deal, str);
			
			for(int n=0; n<k-1;n++)str[n]='\0';
			k=0;
			
			count++;
		}
		}
	return count;
}