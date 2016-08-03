// File.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdio>
using namespace std;

struct Monitor{
      struct displ_res{
		  int x;
		  int y;
	  }resol;
  int diag;
  float price;
  char model[30];

};
void copystr(char *, char *);
void sort_by_price(Monitor *, int );

int main()
{
	
    const int Numb=5;   
	Monitor mon[Numb];
	int disp[Numb][2]={{1024, 680},{650,1000},{500,600},{700,800},{800,680}};
	int diag[Numb]={17,15,19,21,14};
	float pr[Numb]={250.4,120.8,120.5,500,200};
	char name[Numb][30]={{"Samsung 10N"},{"NVideo"},{"ViewSonic"},{"Sony"},{"Asus"}};
	// full struct
	for(int i=0; i<Numb; i++){
		mon[i].resol.x=disp[i][0];
		mon[i].resol.y=disp[i][1];
		mon[i].diag=diag[i];
		mon[i].price=pr[i];
		copystr(mon[i].model,name[i]);
	}

	FILE *fi, *fo;
	const char path[]="D:\\temp\\monit.txt";
	    fi=fopen(path,"w+");
		if(fi==0){cout<<"Error open file "<<path; return 1;}
		fwrite(&Numb,sizeof(int),1,fi);
		for(int i=0; i<Numb; i++){
			if((fwrite(&mon[i], sizeof Monitor, 1,fi))!=1)cout<<"not write "<<i;
		}
      fclose(fi);
	  //add element and write file
	  fi=fopen(path,"r+");
	  if(fi==0){cout<<"Error open file "<<path; return 1;}
	  Monitor NewMon;
	  cout<<"\nEnter monitor characters: resolution: x,y; diadonal; preice; model:";
	  cin>>NewMon.resol.x>>NewMon.resol.y>>NewMon.diag>>NewMon.price>>NewMon.model;
	//  cout<<"\n"<<NewMon.resol.x<<NewMon.resol.y<<NewMon.diag<<NewMon.price<<NewMon.model;
	  fseek(fi,0,SEEK_END);
	  if((fwrite(&NewMon,sizeof Monitor,1,fi))!=1)cout<<"\nnot write new monitor";
	  else{
		  int kol=0;
		  fseek(fi,0,SEEK_SET);
		  long pos=ftell(fi);
		   if(fread(&kol, sizeof(int),1,fi)!=1){cout<<"\nEror read counts";return 1;}
		  kol++;
		  fseek(fi,0,SEEK_SET);
		 pos=ftell(fi);
		  fwrite(&kol, sizeof(int),1,fi);
	  }
	  fclose(fi);
	  
	  //read file, sort, write
	  int kol=0;
	  fi=fopen(path,"r+");
	  if(fi==0){cout<<"Error open file "<<path; return 1;}
	  fseek(fi,0,SEEK_SET);
	  if(fread(&kol, sizeof(int),1,fi)!=1){cout<<"\nEror read counts";return 1;}
	  Monitor *monmas=new Monitor[kol];
	//  int i=0;
	/* do{ 
	 if(fread(&NewMon, sizeof Monitor, 1,fi)!=1){cout<<"\nEror read monitor "<<i; return 1;}
		  monmas[i]=NewMon;
		  i++;
	 } while(!feof(fi));
//{
	  */
	  for(int i=0; i<kol; i++){
	  if(fread(&NewMon, sizeof(Monitor), 1,fi)!=1){cout<<"\nEror read monitor "<<i; return 1;}
	   monmas[i]=NewMon;
	// i++;
	  }
	  for(int i=0; i<kol; i++){
		  cout<<"\n"<<monmas[i].model<<"; "<<monmas[i].diag<<"; "<<monmas[i].price<<"; "<<monmas[i].resol.x<<"x"<<monmas[i].resol.y;
	  }
	    fclose(fi);
		sort_by_price(monmas,kol);
		fi=fopen(path,"w+");
	   if(fi==0){cout<<"\nError open file "<<path; return 1;}
	   fwrite(&kol, sizeof(int),1,fi);
	   for(int i=0; i<kol; i++){
			if((fwrite(&monmas[i], sizeof Monitor, 1,fi))!=1)cout<<"\nnot write "<<i;
		}
	   //read output console
	   fseek(fi,0,SEEK_SET);
	  if(fread(&kol, sizeof(int),1,fi)!=1){cout<<"\nEror read counts";return 1;}
	  cout<<"\n"<<kol<<" counts"<<"\nSORT by prise\n";
	   for(int i=0; i<kol; i++){
		   if(fread(&NewMon, sizeof Monitor, 1,fi)!=1){cout<<"\nEror read monitor "<<i; return 1;}
		  cout<<"\n"<<NewMon.model<<"; "<<NewMon.diag<<"; "<<NewMon.price<<"; "<<NewMon.resol.x<<"x"<<NewMon.resol.y;
	  }
	
	fclose(fi);
	
	system("pause");
	return 0;
}

void copystr(char* str1, char* str2){
	while(*str1++=*str2++){}
}

void sort_by_price(Monitor* mas, int count){
	
	int imin;
	float minpr;
	Monitor m;
	for(int i=0; i<count; i++){
		imin=i;
		minpr=mas[i].price;
		for(int j=i; j<count; j++){
			if(mas[j].price<minpr){
				minpr=mas[j].price;
				imin=j;
			}
		}
     if(i!=imin){
		 m=mas[i];
		 mas[i]=mas[imin];
		 mas[imin]=m;
	 }

	}

}