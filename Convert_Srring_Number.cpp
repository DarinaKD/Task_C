// Convert_Srring_Number.cpp : Defines the entry point for the console application.
//

#include <iostream>

struct NumbMas {
  char ch;
  NumbMas *next;
};

NumbMas* first(char ch);
NumbMas* addToEnd(NumbMas* end, char ch);
NumbMas* addToBeg(NumbMas* beg, char ch);
double atoid(const char*, const int);
NumbMas* convertToString(const double, const int );
void printCh(const NumbMas* );
int main()
{
	int len=30;
	char *str=new char[len];
	std::cin>>str;
	short count=10;
	std::cin>>count;
	double number=atoid(str, count);
	std::cout<<"numb "<<count<<" ="<<number<<"\n";
	
/*	NumbMas* pbeg=first('1');
	NumbMas* pend=pbeg;
	pend=addToEnd(pend,'2');
	std::cout<<"\tpbeg="<<pbeg<<"\t "<<pbeg->ch<<"\t"<<pend->ch<<"\n";*/
	std::cout<<" From numb to string: ";
	NumbMas* pn=new NumbMas;
	pn=convertToString(number,count);
	printCh(pn);

/*	std::cout<<"\nOctal\n";

	number=atoid(str,8);
	std::cout<<"\nnumb 8="<<number;

	std::cout<<"\nFrom  dec numb to string: ";
	pn=NULL; 
	pn=convertToString(number,10);
	printCh(pn);
	
	std::cout<<" \nFrom  oct numb to string: ";
	pn=NULL;
	pn=convertToString(number,8);
	printCh(pn);


	std::cout<<"\nHexademical\n";
	number=atoid(str,16);
	std::cout<<"\nnumb="<<number;
	std::cout<<" \nFrom hex numb to string: ";
	pn=NULL;
	pn=convertToString(number,16);
	printCh(pn);*/
//	number=atoid(str,8);
//	std::cout<<"8 - numb="<<number;
	int k=0x2f;
	//std::cout<<"\n"<<0xA<<0x0+k<<"\n";
	char a;
	std::cin>>a;

	return 0;
}

NumbMas* first(char ch){

	NumbMas* beg=new NumbMas;
	beg->ch=ch;
	beg->next=0;
//	std::cout<<"beg="<<beg;
	return beg;
}

NumbMas* addToEnd(NumbMas* end,char ch){
	NumbMas* p=new NumbMas;
	p->ch=ch;
	p->next=0;
	end->next=p;
	return p;
}

NumbMas* addToBeg(NumbMas* beg,char ch){
	NumbMas* p=new NumbMas;
	p->ch=ch;
	p->next=beg;
	return p;
}
double atoid(const char* s, const int count){
	long numb=0;
	double numd=0;
	int poryadok=0;
	while(*s){
      int d=0;

		switch(*s){
		case('0'):d=0;break; 
        case('1'):d=1;break;
		case('2'):if(count>=9){d=2;break;}
		case('3'):if(count>=4){d=3;break;}
		case('4'):if(count>=5){d=4;break;}
		case('5'):if(count>=6){d=5;break;}
		case('6'):if(count>=7){d=6;break;}
		case('7'):if(count>=8){d=7;break;}
		case('8'):if(count>=9){d=8;break;}
		case(','):
		case('.'):d=-1;poryadok=1;break;
		case('9'):if(count>=9){d=9;break;}
		case('A'):if(count>=16){d=10;break;}
		case('B'):if(count>=16){d=11;break;}
		case('C'):if(count>=16){d=12;break;}
		case('D'):if(count>=16){d=13;break;}
		case('E'):if(count>=16){d=14;break;}
		case('F'):if(count>=16){d=15;break;}
		default: std::cout<<"\n Undefined digit "<<*s<<"\n"; return (poryadok?((double)numb/poryadok)*count:numb);
		}
		
	//	if(count=8)d=
		if(d>=0){
		//std::cout<<"d="<<d;
		numb=numb*count+d;}
		if(poryadok)poryadok*=count;
		s++;
	}
	   //  std::cout<<"d="<<(double)numb;
	    numd=poryadok? ((double)numb/poryadok*count):numb;
	
	return numd;
}

NumbMas* convertToString( const double numb, const int count){
	short shift=short('0');
	double fract=numb-long(numb);
	long integ=long(numb-fract);
	NumbMas* pbeg=new NumbMas;
	pbeg=NULL;
	//std::cout<<"pbeg="<<pbeg;
	if(fract){pbeg=first(',');}
	  NumbMas* pend=pbeg;
	//заносим дробную часть
	//  std::cout<<"\n fract="<<fract<<"\n";
	  //int c=0;
	  float fr=0;
	  int  d=1;
	  float frc=fract;
    while(static_cast<float>(frc-fr)>0){
	//	std::cout<<"\nfloat"<<float(frc-fr);
		fract*=count;
		short fractShort=fract;
		char ch;
		if((count==16)&& (fractShort>=10)){
		switch(fractShort){
		case(10):ch='A'; break;
		case(11):ch='B'; break;
		case(12):ch='C'; break;
		case(13):ch='D'; break;
		case(14):ch='E'; break;
		case(15):ch='F'; break;
		default:std::cout<<"\nНевозможно преобразовать "<<numb<<" в "<<count<<" number system "; return pbeg;
 		}
		} 
		else ch=char(fractShort+shift); 
		pend=addToEnd(pend,ch);
//		std::cout<<"fr="<<fract<<"; "<<short(fract);
		d*=count;
		fr=fr+static_cast<float>(short(static_cast<float>(fract)))/(d);// std::cout<<"sh "<<static_cast<double>(short(fract))/(10*(c+1));
		fract=fract-static_cast<float>(short(static_cast<float>(fract)));
		
	//	std::cout<<"; f2="<<fract<<" fr="<<fr<<"\n";
	//	c++;
	//	if(c>=15)break;
	}
	//заносим целую часть
//	if(!pbeg){pbeg=first(char(long(integ%count)+shift));integ=integ/count;;
	short n;
	while((n =(integ%count))||integ){
        char ch; 
		if((count==16)&&(n>=10)){
		switch(n){
		case(10):ch='A'; break;
		case(11):ch='B'; break;
		case(12):ch='C'; break;
		case(13):ch='D'; break;
		case(14):ch='E'; break;
		case(15):ch='F'; break;
		default:std::cout<<"\nНевозможно преобразовать "<<numb<<" в "<<count<<" number system "; return pbeg;
 		}
		}
		else ch=char(n+shift); 
		integ=integ/count;
		if(!pbeg){pbeg=first(ch); continue;}
		pbeg=addToBeg(pbeg,ch); 
	    }
	
	return pbeg;
}

void printCh(const NumbMas* beg){
	if(beg==NULL){std::cout<<'0'; return; }
   const NumbMas* p=beg;
	while(p){
		std::cout<<p->ch;
		p=p->next;
	}
}