// Dictionary.cpp : Defines the entry point for the console application.
//

#include <iostream>
//#include <stdio.h>
//#include <conio.h>
#include <windows.h>
#include <string>
//#include <stdlib.h>
//#include <dos.h>

using namespace std;

// CLASS TREE____________________________________________
 class Tree{
   char* word;
   Tree* left;
   Tree* right;
 public:
   Tree(char* w){
	word = new char[strlen(w)+1];
	strcpy(word,w);
	left=0;
	right=0;
   }
 /*  Tree(const Tree &tr){
	   if(tr.word){
	   word =new char[strlen(tr.word)+1];
	   strcpy(word,tr.word);
	   }
	   else word=0;
	   left=tr.left; right=tr.right;
   } */ // ��� ���������� ������ �������� ������
   ~Tree(){delete[]word;}  

  const char* getWord(){return word;}
  Tree* find_add(char* w, bool find=false);
  Tree* remove(char* w);
  void printSort(bool inc=true);
  
 };
 //_____________________________________________________
typedef void (*fun)(void);

// MENU________________________________________________
struct Menu{
	
	int x,y;
	char* name;
	//int color;
	fun f;
};

struct WINDOW{
int x1,y1,x2,y2,back,color;
};

 //_____________________________________________________

void DrawWindow (WINDOW );
void flush();
void DrawMenu (int n,Menu *m, WINDOW w);
void clrscr();
void textbackground(int text, int =8);
void gotoxy(int x,int y);

void File();
void Do();
void Exit();

 //   MAIN

int main()
{
	
Menu menu[3]={ //������� ����
{1,1,"File",File},
{6,1,"Do",Do},
{9,1,"Exit",Exit}
};
WINDOW w={3,3,77,23,1,14}; //������� ���� ������ �������
textbackground(0,15);
clrscr();
DrawMenu(3,menu,w); //������� ������� ������� �������
	
	char* const newWord=new char[255];
	cout<<"Input word ";
	cin>>newWord;
	Tree* dict=new Tree(newWord);
	char symb;
	Tree* oneWord;
	while(cin>>newWord){ //Cntr+Z
	//	if(newWord=="\n"){cout<<"STOP";break;}
		cout<<newWord<<"\n";
		oneWord=dict->find_add(newWord);
	}
   
    cout<<"What find? ";
	cin.clear();
	cin>>newWord;
	oneWord=dict->find_add(newWord, true);
	if(oneWord){
	//newWord=oneWord->getWord();
	cout<<" this "<< oneWord->getWord()<<"\n";
	}
	else cout<<newWord<<"Word not found\n";
	cin.clear();
	cout<<"What delete:";

	cin>>newWord;
cout<<"\n ";
	dict->printSort();
	dict=dict->remove(newWord);
	cout<<"\nSort ";
	dict->printSort();
	cout<<"\nSort decreas: ";
	dict->printSort(0);
	cout<<"\n\n";
	system("pause");
	cout<<"\nEnd";
//	cin>>symb;
	return 0;
}



//TREE_____________________________________________________
Tree* Tree::find_add(char* word, bool find){
	if(!word){cout<<"Empty string!"; return NULL;}
    Tree *prev, *pv=this;
	bool found=false;
	int cmp;
	while(pv){
		prev=pv;
		cmp =strcmp(pv->word,word);
		if(!cmp){found=true; break;}
		else if(cmp<0) pv=pv->right;
		else pv=pv->left;
	}
	if(find) return pv;
	// add
	Tree* newpv=new Tree(word);
	if(cmp<0) prev->right=newpv;
	else prev->left=newpv;
	return newpv; 
}

Tree* Tree::remove(char* word){

	//Tree* pv=this->find_add(word, true);
	//if(!pv){cout<<"Word no found"; return;}

	Tree *prev, *pv=this;
	int cmp;
	bool branch=0;
	while(pv){
		cmp=strcmp(pv->word,word);
		if(!cmp)break;
		else{
        prev = pv; 
		if(cmp<0){pv=pv->right; branch=1;}
		else {pv=pv->left; branch=0;}
		}
	}

	if(!pv){cout<<"Such word not found"; return this;}
	 
	Tree* pvrprev=0, *pvr=0, *top=this, *displ=0;
	if(pv->left){pvr=pv->left; displ=pv->left;}
	else if(pv->right)displ=pv->right;
	 
	
	while(pvr){
		pvrprev = pvr;
		pvr=pvr->right;
	}
	if(pvrprev)pvrprev->right = pv->right;
	//if(displ){
	if(pv!=this) branch? prev->right=displ:prev->left=displ;
	else top=displ;
	//}
    delete pv;


	return top;
}

void Tree::printSort(bool inc){
	Tree* pv=this;
if(pv){
   if(inc){
	pv->left->printSort(inc);
	cout<<pv->word<<"; ";
	pv->right->printSort(inc);
   }
   else {
	pv->right->printSort(inc);
	cout<<pv->word<<"; ";
	pv->left->printSort(inc);
   }
}
}
//_______________________________________




void flush(){ //�������� ����� ����������
//fflush(stdin); //�������� �� �����!
	//_asm{ cli; sub ax,ax; mov es,ax; mov al,es:[41ah]; mov es:[41ch],al; sti;}
}

void DrawWindow (WINDOW w) { //���������� ���� w
char c[]={'�','�','�','�','�','�','�','�'};
//WINDOW(1, 1,80,25); �������
textbackground(0,w.back); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),w.color);
gotoxy(w.x1-1,w.y1-1);
cout<<c[0]; //cprintf("%c",c[0]);
for (int i=w.x1; i<=w.x2; i++) cout<<c[1];//cprintf ("%c",c[1]);
cout<<c[2];//cprintf ("%c",c[2]);
for (int j=w.y1; j<=w.y2; j++) {
gotoxy (w.x1-1,j); 
cout<<c[3];//cprintf ("%c",c[3]);
for (int i=w.x1; i<=w.x2; i++) cout<<" ";//cprintf (" ");
cout<<c[4];//cprintf ("%c",c[4]);
}
gotoxy (w.x1-1,w.y2+1);
cout<<c[5];//cprintf ("%c",c[5]);
for (int i=w.x1; i<=w.x2; i++) cout<<c[6];//cprintf ("%c",c[6]);
cout<<c[7];//cprintf ("%c",c[7]);
}

void DrawMenu (int n, Menu *m,WINDOW w) { //���������� ����
int sel=0, back=7, inactivecolor=10,activecolor=4;
DrawWindow (w); //���������� ����
textbackground(back); //��������� ���� ���� ����
for (int i=0; i<n; i++){
	gotoxy(m[i].x,m[i].y);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), inactivecolor); //textcolor
cout<<m[i].name;//cprintf ("%s",m[i].str);
}
while (1) { //����������� ���� ��������� ������� ������
gotoxy(m[sel].x,m[sel].y);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), activecolor);
cout<<m[sel].name;//cprintf ("%s",m[sel].str); //������������ �������� ����� ���������� ������
flush(); //�������� ����� ����������
int ch=cin.get(); //��)� ������� �������
gotoxy(m[sel].x,m[sel].y); //�������� ���� ��������� ������
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), inactivecolor);
//cprintf ("%s",m[sel].name);
cout<<m[sel].name;

if (!ch) { //��� ����������� ���?
	ch=cin.get(); //��������� ���
switch(ch) { //��������� ����������� ����� ������
case 72: case 75: if(sel)sel--; else sel=n-1; break; //������� ����� � �����
case 80: case 77: if(sel<n-1)sel++; else sel=0; break;
} }
else { //��������� ��-����������� ����� ������
switch(ch) {
case 13: //������ Enter
textbackground(w.back); //��������� ��� � ���� ���� �������
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), w.color);
//window (w.x1,w.y1,w.x2,w.y2); //�������� ����� � ���� �������
m[sel].f(); //����� �������, ������������ �� ������� ����
clrscr(); //������, ���� �� ������� ���� ����� ������ �� �������
textbackground(0); //������������ ��� � ���� �� ���� �����
//window (1,1,80,25);
break;
case 27: Exit(); //�� Esc ������ ����� �� ����������
}
}
}
}

//���� ���������� ����� ������������

void File() { //������� �� ���� File - ���� ������ �� ������
char i=0;
//�������� �� ������� ����� ����� cprintf
while (!cin.get()) //kbhit()
	//delay(200);
	cout<<"������ ������� File, ��� %ld\r\n"<<++i;//cprintf ("������ ������� File, ��� %ld\r\n",++i);
}

void Do() { //������� �� ���� Do - ���� ������ �� ������
cout<<"������� ����� �����: ";
//cprintf ("������� ����� �����: ");
int d;
//cscanf ("%d",&d); //������� �� ������� ����� ����� cscanf
cout<<&d;
//cprintf ("\r\n�� ����� �������� %d\r\n������� ������� ��� ������...",d);
cout<<"\r\n�� ����� �������� %d\r\n������� ������� ��� ������..."<<d;
cin.get(); cin.get();
}

void Exit(){ //������������ ������� �� ��������� � �����
//window(1,1,80,25); ��������
textbackground(0);//BLACK); 
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//LIGHTGRAY); 
clrscr();
exit(0);
}

/*
//������ ��� ������������� ����
void main () {
ITEM menu1[3]={ //������� ����
{2,2,"File",File},
{2,3,"Do",Do},
{2,4,"Exit",Exit}
};
WINDOW w={8,2,78,24,BLUE,YELLOW}; //������� ���� ������ �������
textbackground (WHITE);
clrscr();
DrawMenu (3,menu1,w); //������� ������� ������� �������

*/

void clrscr(void)
{
HANDLE hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
COORD start = {0, 0};
CONSOLE_SCREEN_BUFFER_INFO info;
::GetConsoleScreenBufferInfo(hOut, &info);
::FillConsoleOutputCharacter(hOut, ' ', info.dwSize.X*info.dwSize.Y, start, NULL);
::SetConsoleCursorPosition(hOut, start);
}

void gotoxy(int x,int y){
HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );

if ( INVALID_HANDLE_VALUE != hConsole )
{
COORD pos = {x, y};
SetConsoleCursorPosition ( hConsole, pos );
}
}
void textbackground(int text, int background=8)
{
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}