#include <iostream>
#include <cstdio>
//#include "stdafx.h"

using namespace std;
enum operation{PRIHOD, RASHOD};

struct Order {
	char AccountPayers[8];
	char AccountRecipient[8];
	double Summ;
};

struct SortList{
	Order  date;
	SortList* next;
};


SortList* first(Order );
SortList* add(SortList *, Order );
void writePay(FILE* , SortList* const );
void readPay(FILE *, SortList* );
double countPay(SortList* const , char* );
int strcmp(char *, char * );
void printList(SortList*);

int main()
{
	//read from file in struct
  const char path[] = "D:\\temp\\Order.txt";
  FILE *fi, *fo;
  
  if((fo=fopen(path,"r"))==0){ 
	  if(feof(fo))cout<<"Empty file";
	  cout<<"Error open file "<<path;
	  return 1;
//	  exit(1);
    }

  SortList *pay=new SortList;

  //full
   
  cout<<"\nInput first full ";
  Order ord;
 // cin>>ord;
  cin>>ord.AccountPayers>>ord.AccountRecipient>>ord.Summ;
   pay = first(ord);
  char ch;
  //ch = getchar();
  /*while((cin>>ch)!='q'){
	  putchar(ch);
	//   flushall();
	  cin>>ord.AccountPayers>>ord.AccountRecipient>>ord.Summ;
	  cout<<"  next\n";
   add(pay,ord);
   flushall();
   }*/

  while( cin>>ord.AccountPayers>>ord.AccountRecipient>>ord.Summ){

	pay = add(pay,ord);
	     cout<<"  next\n";
  }
  cout<<"\n End input"; 
  if((fi=fopen(path,"a+t"))==NULL) {cout<<"\nerror in open file for write"; cin>>ch; return 1;}
  writePay(fi,pay); 
  fclose(fi);
  
  readPay(fo,pay);
  fclose(fo);
  
  printList(pay);
 
  cout<<"\nInput account =";
  
   char account[8];
  // cin.ignore();
   cin.clear();
 
 cin.getline(account,8);
  cout<<account;
  double sum = countPay(pay,account);
  cout<<"\nSum = "<<sum;

  if((fi=fopen(path,"a"))==NULL) {cout<<"\nerror in open file for write"; exit(1);}
  writePay(fi,pay);
  
  system("pause");
  
	return 0;
}

int strcmp(char *str1, char *str2 ){
	 short rez=-1;
	 while((*str1)&&(*str2)&&(*str1++==*str2++)){ }

	 if(!(*str1)&&!(*str2)&&(*(str1-1)==*(str2-1)))rez=0;
	 else if((!(*str1)&&(*str2))||(*(str1-1)>*(str2-1))) rez=1;
  return rez;
 }

// работа со списком

SortList* first(Order st){
	SortList* list = new SortList;
	list->date = st;
	list->next = 0;
	return list;
}



SortList* add(SortList *pbeg, Order st){
	SortList *pv=pbeg;
	SortList *pprev =0;
	SortList *pOrder = new SortList;
	pOrder->date = st;
	pOrder->next = 0;
	while(pv){
		if(strcmp(st.AccountPayers,pv->date.AccountPayers)<=0){
	       if(pv == pbeg){
			  pbeg = pOrder;
			  pprev=pOrder;
			  pOrder->next=pv;
			  return pbeg;
		  }
		} 
		   
		   
		  
		   
		
		pprev = pv;
		pv = pv->next;
	}
    //не нашли, добавляем в конец
	pprev->next = pOrder;
return pbeg;
}

double countPay(SortList* const pbeg, char* account){
	SortList *pv = pbeg;
	double summa=0;
	while(pv){
		if(strcmp(pv->date.AccountPayers,account)==0){summa += pv->date.Summ; cout<<"+ "<<pv->date.Summ;}
		if(strcmp(pv->date.AccountRecipient,account)==0){summa -= pv->date.Summ; cout<<"-"<<pv->date.Summ;}
		pv = pv->next;
	}
	return summa;
}


void readPay(FILE *fo, SortList* pay){

	Order* ord = new Order;
	int kol=fread(ord, sizeof(Order),1,fo);
	if(feof(fo)){cout<<"\nEmpty file"; exit(1);}
	if(kol!=1) {cout<<"\nError read file"; exit(1);}

	pay = first(*ord);

	while(fread(ord, sizeof(Order),1,fo)==1){
		add(pay,*ord);
	}
}

void writePay(FILE *fi, SortList* const pay){
	int kol;
	SortList* pv = pay;
	while(pv){
		kol = fwrite(pv,sizeof(Order),1,fi);
		if(kol!=1){ cout<<"\nError write file "<<pv->date.AccountPayers; cin>>kol; exit(1);}
		pv = pv->next;
	}
} 

void printList(SortList* pbeg){

	SortList* pv = pbeg;
	while(pv){
		
		cout<<"\n"<<pv->date.AccountPayers<<" "<<pv->date.AccountRecipient<<" "<<pv->date.Summ;
		pv=pv->next;}
}