// Car_stek.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

struct Stak{
 static int leave;
 char numb[5];
 Stak *p;
};

Stak* first(char*, int);
void push(Stak*, char*, int);
void pop(Stak*);
Stak* leave_machine(Stak*, char*);
char strcmp(const char *, const char *);

int main()
{
    const int kol=7;  
	char car_numb[kol][5]={"0570", "7586", "0240", "1111", "0000", "0124", "1208"};
	Stak* car;
	car=first(car_numb[0],0);
	for(int i=0; i<kol; i++){
		push(car, car_numb[i],0);
	}
 cout<<"\n Full mas car: ";
 Stak* pv=car;
 for(int i=0; i<kol; i++){
	 cout<<pv->numb;
	 pv=pv->p;
 }
 
 char* cur_car="1111"; 
// pv=leave_machine(pv, cur_car);
 cout<<"\n mas car whith out: "<<cur_car;
 for(int i=0; i<kol; i++){
	 cout<<pv->numb;
	 pv=pv->p;
 }
 

//	cout<<car->numb;
	system("pause");
	return 0;
}
//copy string
void strcopy(char* str1, char* str2){
	while(*str1++=*str2++){}
}

char  strcmpd(const char *str, const char *str2){
	char rez=0;
	int len1=strlend(str);
	int len2=strlend(str2);
	
	if(!(len1+len2))return rez='0';
//   	if(!(len1*len2))return rez=(len1==0)?:1,2;
	int i=0;
	while((*str++==*str2++)&&((*str)*(*str2))){}
	str--;
	str2--;
	if(!((*str)*(*str2))){return rez=(*str2)?'1':'2'; }

	//std::cout<<"\n LEN"<<str[len1]<<"\t"<<str2[len2];
	if((*str)>(*str2))rez='2'; 
	else if((*str)<(*str2))rez='1';
	
	 return rez;
  }


//add first element
Stak* first(char* numb, int leave=0){

	Stak* beg=new Stak;
	strcopy(beg->numb, numb);
	beg->leave=leave;
	beg->p=0;

	return beg;
}

void push(Stak* beg, char* numb, int leave=0){
	Stak* pv=new Stak;
	strcopy(pv->numb, numb);
	pv->leave=leave;
	pv->p=beg;
	beg=pv;
}

void pop(Stak* beg){

	if(!beg){cout<<"\nEmpy stak."; return;}
	Stak* pv=beg;
	beg=pv->p;
	delete pv;
}

//выезд машины совсем
Stak* leave_machine(Stak* beg, char* numb){
	Stak* pv, *tempbeg;
	pv=beg;
//	if(!tempbeg){cout<<"\nEmpy stak."; return;}
	//это первый эелмент
	if(strcmp(beg->numb, numb)){
		tempbeg=first(beg->numb, beg->leave);
		pv=beg->p;
		pop(beg);
		beg=pv;
	while((beg->p)&&(strcmp(beg->numb, numb))){
		pv=beg->p; 
		push(tempbeg,beg->numb, beg->leave);
		pop(beg);
		beg=pv;
	}

	
	}
	if((beg->p)||(strcmp(beg->numb, numb))){
	// нашли машину с таким номером prev;
	cout<<"\n machine "<<numb<<" left; "<<" count leav="<<beg->leave;
	pv=beg->p;
	pop(beg);
	beg=pv;
 	}
	else cout<<"\nnot found car with number "<<numb; 
	if((!beg)&&(!tempbeg)){
		beg=first(tempbeg->numb, tempbeg->leave);
		pv=tempbeg->p;
		pop(tempbeg);
		tempbeg=pv;
	}
	while(tempbeg){
		push(beg, tempbeg->numb, tempbeg->leave);
		pv=tempbeg->p;
		pop(tempbeg);
		tempbeg=pv;
	}

 delete pv;
 return beg;
}