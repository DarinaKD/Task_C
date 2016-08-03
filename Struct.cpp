// Struct.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;
// работа с бинарным деревом
//struct Student;
struct Student{
 char FIO[100];
 short Group;
 float Maintains[5];
 };

struct BTree{
	Student st;
    BTree *left;
	BTree *right;
};

BTree* first(Student);
BTree* insert_find(BTree*,Student, bool );
void print_Tree(BTree*, int, bool);

 short compare(char*, char*);
 void copystr(char*, char*);
int main()
{
 const short NumbSt=8;
 Student* st=new Student[NumbSt];
//char** fio=new char*[NumbSt];
 //for(int i=0; i<NumbSt; i++) fio[i]=new char[100];
 char fio[NumbSt][100]={{"Ivanov L.M."},{"Popov T.H."},{"Barlentyj D.O."},{"Matroskin A.B."},{"Orven U.I."},{"Alchuk F.K."},{"Mors G.p."},{"Mors G.K."}};
 short Ngroup[NumbSt]={201,504,107,306,504,107,201,201};
 float maint[NumbSt][5]={{0,4,5,8,1},{12,7,5,3,0},{5,4,4,7,9},{1,4,6,5,6},{4,8,5,2,2},{1,7,3,6,11},{12,0,7,3,10},{11,11,0,4,9}};
 //full mas struct
 for(int i=0; i<NumbSt; i++){
	 st[i].Group=Ngroup[i];
	 copystr(st[i].FIO,fio[i]);
	// cout<<"st["<<i<<"]"<<st[i].FIO<<"\n";
	 for(int j=0; j<5;j++){
		 st[i].Maintains[j]=maint[i][j];
	 }
 }

 //create tree
 BTree * beg=first(st[0]);
 for(int i=1; i<NumbSt; i++){
	 BTree *p=insert_find(beg, st[i],0);
 }
 cout<<"\nSorting  in increasing\n";
 print_Tree(beg,0,1);
 cout<<"\nSorting  in descending\n";
 print_Tree(beg,0,0);

 //find student
 char FioSt[100];
 int gr;
 cout<<"\nEnter Group:";
 cin>>gr;
 _flushall();
 cout<<"\nEnter FIO:"<<endl;
 cin.getline(FioSt, sizeof(FioSt),'\n');

 Student s;
 copystr(s.FIO,FioSt);
 s.Group=gr;

 BTree* findSt=insert_find(beg,s,1);
 if(findSt)
 cout<<"\n Student find: group="<<findSt->st.Group<<" FIO="<<findSt->st.FIO<<"\n";

system("pause");
	return 0;
}

//работа с деревом
 BTree* first(Student st){
	 BTree* pv=new BTree;
	 pv->st=st;
	 pv->left=0;
	 pv->right=0;
	 return pv;
 }

 BTree* insert_find(BTree* beg, Student st, bool onlyFind){
	 BTree* pv=beg, *prev;
	 bool found=false, ltree;
	 while(pv&&!found){
	      prev=pv;
		 if(pv->st.Group==st.Group){
			 if(!compare(pv->st.FIO, st.FIO))found=true;
			 else if(compare(pv->st.FIO, st.FIO)>=0){pv=pv->left; ltree=1;}
			 else {pv=pv->right; ltree=0;}
		 }
		 else if(pv->st.Group>st.Group){pv=pv->left; ltree=1;}
		 else {pv=pv->right; ltree=0;}
	 }

	 if(found) return pv;
	 if(!onlyFind){
	 BTree *pnew=new BTree;
	 pnew->st.Group=st.Group;
	 copystr(pnew->st.FIO,st.FIO);
	 pnew->left=0;
	 pnew->right=0;
	 if(ltree)prev->left=pnew;
	 else prev->right=pnew;
	 return pnew;
	 }
	 else cout<<"\nStudent "<<st.FIO<<" not found\n";
	 return NULL;
 }

 void print_Tree(BTree *p, int level, bool sort){
	 
	 if(p){
		 if(sort){
		 print_Tree(p->left, level+1,sort);
		 cout<<p->st.Group<<"-"<<p->st.FIO<<"\n";
		 print_Tree(p->right, level+1,sort);
		 }
		 else {
		 print_Tree(p->right, level+1,sort);
		 cout<<p->st.Group<<"-"<<p->st.FIO<<"\n";
		 print_Tree(p->left, level+1,sort);
		 }
	 }
 }

 short compare(char* str1, char* str2){
	 short rez=-1;
	 while((*str1)&&(*str2)&&(*str1++==*str2++)){
	 }

	 if(!(*str1)&&!(*str2))rez=0;
	 else if(!(*str1)||(*(str1-1)>*(str2-1))) rez=1;
  return rez;
 }

 void copystr(char* str1, char* str2){
	 while(*str1++=*str2++){}
 }