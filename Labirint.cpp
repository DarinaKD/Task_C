// Labirint.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
//#include <stdlib.h> //random
#include <time.h> //randomize
//#include <stdio.h>
using namespace std;
enum Direction {LEFT=1, RIGHT=3, UP=2, DOWN=4};

struct Way{
	int x;
	int y;
	Way* next;
	Way* prev;
	Direction dt;
};

void addWay(Way** end,int x, int y, Direction d);
Way* find(bool** mas, int n, int k, int begx, int begy);
void removelist(Way* end , bool** mas, int k);
void printWay(Way* beg);
void direction(Direction, int&, int&);

int main()
{
const int k=5, n=5;
bool** mas = new bool* [n];
for(int i=0; i<n; i++)
 mas[i]=new bool [k];
bool masstat[n][k]={{1,0,1,0,1},{1,1,0,0,0},{1,1,1,1,1},{1,1,1,1,1},{0,1,1,1,0}};

srand((unsigned)time( NULL));
for(int i=0; i<n; i++)
	for (int j=0; j<k; j++) //mas[i][j]=masstat[i][j];
		mas[i][j]=rand()%2? true: false;
//cout<<"\n";
for(int i=0; i<n; i++){
	for(int j=0; j<k; j++) cout<<mas[i][j]<<"\t";
	cout<<"\n";
}
Way* labirint;
int begx, begy;
cout<<"Input entruns: ";
cin>>begx>>begy;

labirint=find(mas, n, k, begx, begy);
cout<<"\n";
printWay(labirint);
cout<<"\n\n";
for(int i=0; i<n; i++){
	for(int j=0; j<k; j++) cout<<mas[i][j]<<"\t";
 cout<<"\n";
}


system("pause");
return 0;

}

void addWay(Way** end, int x, int y, Direction d){

	Way* newEl =new Way;
	newEl->dt=d;
	newEl->next=NULL;
	newEl->prev=*end;
	newEl->x=x;
	newEl->y=y;
	(*end)->next=newEl;
	*end = newEl;
}

void removelist(Way** end, bool** mas, int k){

 int x,y;
 x=(*end)->x;
 y=(*end)->y;
 mas[x][y]=1;
 //*(mas+x*k+y)=1;
 Way* pdel=*end; 
 *end =(*end)->prev;
 (*end)->next=NULL;
delete(pdel);
}

void direction(Direction direct, int &i, int &j){
	 switch (direct)
	 {
	 case LEFT:j=j--; break;
	 case RIGHT:j=j++; break;
	 case UP:i=i--;  break;
	 case DOWN:i=i++; break;
	 default: cout<<"no exit\n";//выход из цикла
		 break;
	 }

}

Way* find(bool** mas, int n, int k, int begx, int begy){

	if(mas[begx][begy]){cout<<"Entry point is closed\n"; return 0;} 
int i=begx;
int j=begy;

Way *lab=new Way;
lab->prev=NULL;
lab->next=0;
lab->x=begx;
lab->y=begy;
lab->dt=LEFT;

Way* labend = lab;

int tekx = i, teky = j;

//sort
// direction +1<>5
//mas[i] не изм
Direction direct=LEFT;
direction(direct,  i,j);

while((i>=0&&(i<=n-1)&&j>=0&&(j<=k-1))||(labend->x==begx&&labend->y==begy) && labend){

	if(((i==0)||(j==0)||(i==n-1)||(j==k-1))&&mas[i][j]==0 &&!(i==begx&&j==begy)){
		 //if(!(labend->x==begx&&labend->y==begy))
		 //if(!(i==labend->prev->x && j==labend->prev->y)){
		 addWay(&labend,i,j,direct); break;} 
	 if(direct>4)break;
	 if(i<0||i>n-1||j>k-1||j<0){
		 direct = Direction(direct+1); 
		 i=labend->x;
		 j=labend->y;
	     direction(direct,  i,j);
		 
		 continue;
	 }
	 if(mas[i][j]==1) {		        
	              direct = Direction(direct+1); 
				  

				  if(direct>4){
					  if(labend==lab){cout<<"No any way"; return labend;}
					 removelist(&labend,mas, k);
					  direct=LEFT; 
		//			  i=labend->x; 
	      //            j=labend->y;
			//		  continue;
				  }
				  i=labend->x; 
	              j=labend->y;

				   direction(direct, i,j);
				  continue;
				  			
	 }
	   
	 if(!(labend->x==begx&&labend->y==begy)&&labend->prev->x==i&&labend->prev->y==j){i=labend->x;j=labend->y; 
		 direct=Direction(direct+1);}
	 else {direct = LEFT; addWay(&labend, i,j,direct);}
	 direction(direct, i,j);
	
  }

 if(!labend){cout<<"No any way"; return labend;}
// else if(!(labend->x==i&&labend->y==j)&&!(labend->prev->x==i&&labend->prev->y==j)&&mas[i][j]==0)addWay(&labend,i,j,direct);
 return lab;
}

void printWay(Way* beg){
if(!beg)return;
Way* w=beg;
do{
	cout<<w->x<<"; "<<w->y<<"\t";
}while(w=w->next);
}