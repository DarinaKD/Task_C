// Polygon.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;
void drawPolygon(HDC, int, int**);
void calcCoef(int, int**, float **);
bool searchIntersection(HDC, int, float**, int, float**, int**, int**);
int main()
{

const int size_mas1=5, size_mas2=4;
int  **pmas1, **pmas2;
//full mas of points
int mass_1[2][5]={{20,20,50,90,30},
                  {50,60,180,100,40}};
//внутри
int mass_2[2][6]={{10,90,125,40,80,30},
                  {30,50,180,200,40,10}};
//вне
/*int mass_2[2][6]={{100,190,190,140,100,90},
                  {200,150,190,250,140,50}}; */
//пересек
/*int mass_2[2][6]={{80,100,90,40,100,90},
                  {60,80,90,250,140,50}}; */
				  

				  
//srand(time(NULL));
pmas1=new int*[2];
pmas2=new int*[2];
for(int n=0; n<2; n++){
pmas1[n]=new int[size_mas1];
pmas2[n]=new int[size_mas2];
}

for(int i=0; i<2; i++){
	for(int j=0;j<size_mas1; j++)
//	pmas1[i][j]=rand()%200+1;
		pmas1[i][j]=mass_1[i][j];
}

for(int i=0; i<2; i++){
	for(int j=0;j<size_mas2; j++)
	//pmas2[i][j]=rand()%300+1;
			pmas2[i][j]=mass_2[i][j];
}

//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);
HPEN Pen1;
HGDIOBJ hpenOld;

Pen1=CreatePen(PS_SOLID, 2, RGB(255,255,255));
hpenOld = (HPEN)SelectObject(hdc, Pen1);
// draw polygon
drawPolygon(hdc,size_mas1, pmas1);
//Polygon(hdc,mas1,10);
Pen1=CreatePen(PS_SOLID, 2, RGB(255,0,0));
hpenOld = (HPEN)SelectObject(hdc, Pen1);
drawPolygon(hdc,size_mas2, pmas2);

//paсчет коэф. пр€мых
float** masKoef1=new float*[2];
calcCoef(size_mas1, pmas1, masKoef1);

float** masKoef2=new float*[2];
calcCoef(size_mas2, pmas2, masKoef2);

//пересечение любой пр€мой первого много-ка с любой второго
bool peres=searchIntersection(hdc, size_mas1, masKoef1, size_mas2, masKoef2,pmas1, pmas2);

//if(peres) cout<<"\n yes";
//else cout<<"\nnot ";
system("pause");
return 0;
}

void drawPolygon(HDC hdc, int size_mas, int** mas){
	
//	COORD cor = {0,0};
	for(int i=0; i<size_mas-1; i++){
	/*		cor.X = mas[0][i];
            cor.Y = mas[1][i];
SetConsoleCursorPosition(hdc,cor);
cout <<i+1; */
	MoveToEx(hdc,mas[0][i],mas[1][i],NULL);
	LineTo(hdc,mas[0][i+1],mas[1][i+1]);
	Sleep(200);
}
// соедин€ем крайние точки

MoveToEx(hdc,mas[0][size_mas-1],mas[1][size_mas-1],NULL);
LineTo(hdc,mas[0][0],mas[1][0]);

}

void calcCoef(int size_mas, int** mas, float** masCoef){

	for(int n=0; n<2; n++)masCoef[n]=new float[size_mas];

	for(int i=0; i<size_mas; i++){
		//k=(y1-y2)/(x1-x2)
		int k=(i==size_mas-1)?0:i+1;
		if(!(mas[0][i]-mas[0][k])) {masCoef[0][i]=LONG_MAX;}
		else {
			masCoef[0][i]=static_cast<float>(mas[1][i]-mas[1][k])/((mas[0][i]-mas[0][k])); 
		//	cout<<"\nJ k="<<mas[1][i]<<"-"<<mas[1][k]<<"/"<<mas[0][i]<<" - "<<mas[0][k]<<"="<<masCoef[0][i]<<" J= "<<i;
			masCoef[1][i]=mas[1][i]-masCoef[0][i]*mas[0][i];
	        }
	}
	//коэф. последней пр€мой, соедин€ющей крайние точки

}

bool searchIntersection(HDC hdc,int size1,float** mask1, int size2, float** mask2, int** mas1, int** mas2){
		short ml=0, mr=0, tp=0;
		bool* line1=new bool[size1];
		for(int r=0;r<size1; r++) line1[r]=0;
	for(int i=0; i<size1; i++){
		ml=0; mr=0; tp=0;
		//cout<<"\ni="<<i;
		for(int j=0; j<size2; j++){
			// cout<<"\tj="<<j;
			int k=(i==size1-1)? 0:i+1;
			int l=(j==size2-1)? 0:j+1;
			if(!(mask1[0][i]-mask2[0][j])){//паралельные пр€мые
			//	cout<<"paralel";
				continue;}
			else if((mask1[0][i]==LONG_MAX)||(mask2[0][j]==LONG_MAX)){ //перпендикул€рна€ пр€ма€
				int y,x; //x=a; y=k*a+b;
				if(mask1[0][i]==LONG_MAX) {y=mask2[0][j]*mas1[0][i]+mask2[1][j]; x=mas2[0][j];}
				else{ y=mask1[0][j]*mas2[0][i]+mask1[1][j];x=mas1[0][i];}
				//пересекают
				int miny1,maxy1, maxy2,miny2;
				
				maxy1=(mas1[1][k]<mas1[1][i])?mas1[1][i]:mas1[1][k];
				miny1=mas1[1][k]+mas1[1][i]-maxy1;
				maxy2=(mas2[1][l]<mas2[1][j])?maxy2=mas2[1][j]:maxy2=mas2[1][l];
				miny2=mas2[1][l]+mas2[1][j]-maxy2;
				if((y<=maxy1)&&(y>=miny1)){
					//cout<<"\n"<<y<<" mas1[0][i]="<<mas1[0][i]<<" mas1[1][i]"<< mas1[1][i]<<" mas1[0][k]="<<mas1[0][k]<<" mas1[1][k]"<< mas1[1][k]<<"\nperpend";
				//	MoveToEx(hdc,mas1[0][i],mas1[1][i],NULL);
	            //    LineTo(hdc,mas1[0][k],mas1[1][k]);
				//	cout<<"perpen";
					cout<<"Polygons are INTERSECT\n";
				return 1;}
				 //сверху от диапазона у
				else if((y>maxy1)&&(y<=maxy2)&&(y>=miny2)){
					//cout<<"\ni="<<i<<" j="<<j<<" maxy="<<maxy<<" miny="<<miny<<" y="<<y; 
					mr++;}
				 //снизу
				 else if((y<miny1)&&(y<=maxy2)&&(y>=miny2)) ml++;
			}
				else {
					//x=(b1-b2)/(k2-k1);
				int x=(mask1[1][i]-mask2[1][j])/(mask2[0][j]-mask1[0][i]); //cout<<"\nmask1[1][i]="<<mask1[1][i]<<"mask2[1][j]"<<mask2[1][j]<<"mask2[0][j]"<<mask2[0][j]<<"mask1[0][i]"<<mask1[0][i];
				int minx1,minx2,maxx1,maxx2;
				maxx1=(mas1[0][k]<mas1[0][i])?maxx1=mas1[0][i]:maxx1=mas1[0][k];
				minx1=mas1[0][k]+mas1[0][i]-maxx1;
				maxx2=(mas2[0][l]<mas2[0][j])?maxx2=mas2[0][j]:maxx2=mas2[0][l];
				minx2=mas2[0][l]+mas2[0][j]-maxx2;
				if((x<=maxx1)&&(x>=minx1)&&((x<=maxx2)&&(x>=minx2))){//пересекает и наход. между соответ. точками х мас1 и мас2 
					//cout<<x<<" b1="<<mask2[1][j]<<" b="<<mask1[1][j]<<" k1="<<mask2[0][j]<<" k="<<mask1[0][j]<<" i="<<i<<" j="<<j;
					cout<<"Polygons are INTERSECT\n";
					return 1;
				}
				else if((x>maxx1)&&(x<=maxx2)&&(x>=minx2))mr++;
				else if((x<minx1)&&(x<=maxx2)&&(x>=minx2)) { ml++; 
				//cout<<"\ni="<<i<<" j="<<j<<" x="<<x<<" mas2[0]["<<l<<"]"<<mas2[0][l]<<" mas2[0][j]="<<mas2[0][j];
				}
				if((x==mas2[0][l])||(x==mas2[0][j]))tp++;
				// cout<<"\ni="<<i<<" j="<<j<<" x="<<x<<" mr="<<mr<<" ml="<<ml<<" tp="<<tp;
			//	SetPixel(hdc,x,mask1[0][j]*mas[0][i]+mask1[1][j],RGB(0,0,255));
			}
		

		}
		
		//внутри или вне
		if((mr+ml-tp/2)!=2||!(mr*ml)){//вне
			line1[i]=1;
		//	cout<<"\nout"<<"i="<<i;
			//cout<<"\npolygon1 is out polygon2"; return 0;
		}
		
	}

	int s=0;
	while(!(*line1)){s++; line1++;}
	if((*line1)&&(s<size1))cout<<"\npolygon 1 is OUT polygon 2\n";
	else cout<<"\npolygon 1 is IN polygon 2\n";
return 0;
}