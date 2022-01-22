#include <graphics.h> 
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int n = 10;
struct TT{
	char Ten[10];
	int TgRL;
	int TgRL1;
	int Cpubust;
	int UuTien;
	int Color;
};
struct Sodo{
	char Ten[10];
	int TgCho;
	int TgVao; 
	int TgRa;
	int Color;
};

TT *NhapDL(){
	TT *t = new TT[10];
	char a[10][10] = { "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9" , "P10"};
	for (int i = 0; i < n; i++)
	{
		strcpy(t[i].Ten, a[i]);
		t[i].TgRL = rand() % 11;
		t[i].TgRL1 = t[i].TgRL;	
		t[i].Cpubust = rand() % 10 + 1;
		t[i].UuTien = rand() % 10 + 1;
		t[i].Color = i+2;
	}
	return t;
}
void InDLVao(TT t[])
{
	cout << setw(10) << "Tien Trinh" << setw(30) << "Thoi gian vao ready list" << setw(30)
			<< "Thoi gian CPU Busrt" << setw(30)
			<< "Do Uu Tien" <<endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(5) << t[i].Ten << setw(20) << t[i].TgRL << setw(35)
				<< t[i].Cpubust << setw(38)
				<< t[i].UuTien <<endl;
	}
}
void InDLRa(Sodo Sd[], int Sodo)
{
	cout << setw(10) << "Tien Trinh" << setw(20) << "Thoi gian Cho" << setw(20)
			<< "Thoi gian vao" << setw(20)
			<< "Thoi gian ra" <<endl;
 	for(int i = 0; i < Sodo; i++)
		{
			cout << setw(5) << Sd[i].Ten << setw(20) << Sd[i].TgCho << setw(20)
				<< Sd[i].TgVao << setw(20)
				<< Sd[i].TgRa <<endl;		
		}
}
void swap(TT *A, TT *B)
{
    TT *temp = A;
    *A = *B;
    *B = *temp;
}
void xoaPT(TT t[], int vt, int &n)
{
	for(int i = vt ; i < n; i++)
	{
		t[i] = t[i+1];
	}
			n--;
}
void Priority(TT t[], Sodo Sd[], int &Sodo)
{
	TT *RL = new TT[10];
	int Tg = 0;
	for(int i = 0; i < n; i++)
	{ 
		Tg = Tg + t[i].Cpubust;
	}
	int dem = 0;
	for(int i = 0; i < Tg; i++)
	{		
		for(int j = 0; j < n; j++)
		{
			if(t[j].TgRL <= i)
			{
				RL[dem] = t[j];
				xoaPT(t,j,n);
				dem++;
				j = j-1;
			}
		}		
		for(int j = 0; j < dem - 1 ; j++)
		{
			for(int l = j+1; l < dem; l++)
				if(RL[j].UuTien > RL[l].UuTien )
				{		
					swap(RL[j],RL[l]);				
				}
				else
				if(RL[j].UuTien == RL[l].UuTien)
				{
					if(RL[j].TgRL > RL[l].TgRL)
					swap(RL[j],RL[l]);
				}		
		}		
		strcpy(Sd[Sodo].Ten , RL[0].Ten);
		Sd[Sodo].TgCho = i - RL[0].TgRL;
		Sd[Sodo].TgVao = i;
		Sd[Sodo].Color = RL[0].Color;
		Sd[Sodo].TgRa = i + RL[0].Cpubust;
		i = Sd[Sodo].TgRa - 1;
		xoaPT(RL,0,dem);
		Sodo++;	
	}
}
void swapSau(TT t[], TT *dau,TT *cuoi, int dem)
{
	
	TT *tam = dau;
	for(int i = 0; i < dem-1; i++)
	{
		t[i] = t[i+1];
	}
	*cuoi = *tam;
}
void RR(TT t[], Sodo Sd[], int &Sodo,int qtime)
{
	n = 10;
	TT *RL = new TT[10];
	int Tg = 0;
	for(int i = 0; i < n; i++)
	{ 
		Tg = Tg + t[i].Cpubust;
	}
	int dem = 0;
	for(int i = 0; i < n-1; i++)
	{
		for (int j = i+1; j < n; j++)
			if(t[i].TgRL > t[j].TgRL)
			swap(t[i],t[j]);
			
	}
	for(int i = 0; i < Tg; i++)
	{		
		for(int j = 0; j < n; j++)
		{
			if(t[j].TgRL <= (i+t[j].Cpubust-1) )
			{
				RL[dem] = t[j];
				xoaPT(t,j,n);
				dem++;
				j = j-1;
			}
		}
		if(RL[0].Cpubust > qtime)
		{
			strcpy(Sd[Sodo].Ten , RL[0].Ten);
			Sd[Sodo].TgCho = (i) - RL[0].TgRL;
			Sd[Sodo].TgVao = i;
			Sd[Sodo].Color = RL[0].Color;
			Sd[Sodo].TgRa = i + qtime;
			RL[0].TgRL = i + qtime;
			i = (i-1) + qtime;
			Sodo++;	
		
			RL[0].Cpubust = RL[0].Cpubust - qtime;
			TT tam = RL[0];
			for(int k = 0; k < dem-1; k++)
			{
				RL[k] = RL[k+1];
			}
			RL[dem-1] = tam;
		}
		else
		{
			strcpy(Sd[Sodo].Ten , RL[0].Ten);
			Sd[Sodo].TgCho = (i) - RL[0].TgRL;
			Sd[Sodo].TgVao = i;
			Sd[Sodo].Color = RL[0].Color;
			Sd[Sodo].TgRa = i + RL[0].Cpubust;
			i = (i-1) + RL[0].Cpubust;
			xoaPT(RL,0,dem);
			Sodo++;	
		}
		
	}
}
void Priority_Non(TT t[], Sodo Sd[], int &Sodo)
{
	n = 10;
	TT *RL = new TT[10];
	int Tg = 0;
	for(int i = 0; i < n; i++)
	{ 
		Tg = Tg + t[i].Cpubust;
	}
	int dem = 0;
	for(int i = 0; i < Tg; i++)
	{		
		for(int j = 0; j < n; j++)
		{
			if(t[j].TgRL <= i )
			{
				RL[dem] = t[j];
				xoaPT(t,j,n);
				dem++;
				j = j-1;
			}
		}
		for(int j = 0; j < dem - 1 ; j++)
			{
				for(int l = j+1; l < dem; l++)
					if(RL[j].UuTien > RL[l].UuTien )
					{		
						swap(RL[j],RL[l]);				
					}
					else
					if(RL[j].UuTien == RL[l].UuTien)
					{
						if(RL[j].TgRL1 > RL[l].TgRL1)
						swap(RL[j],RL[l]);
					}	
			}
			if(RL[0].Cpubust == 0)
			{
				xoaPT(RL,0,dem);
			}
			strcpy(Sd[Sodo].Ten , RL[0].Ten);
			Sd[Sodo].TgCho = (i) - RL[0].TgRL;
			Sd[Sodo].TgVao = i;
			Sd[Sodo].Color = RL[0].Color;
			Sd[Sodo].TgRa = i + 1;
			RL[0].TgRL = i + 1;
			RL[0].Cpubust = RL[0].Cpubust - 1;
			Sodo++;	
		
	}
}
 void ManHinh(TT tt[], Sodo Sd[], TT ttRR[] , Sodo SdRR[], int SodoRR,TT ttNon[] , Sodo SdNon[], int SodoNon)
{
 	initwindow(getmaxx(),getmaxy());			// init window graphics
	setbkcolor(0);					// set background
   	cleardevice();
	setcolor(15);					// set text color
	outtextxy(20,50,"Priority Doc quyen");
	int x = 50, y = 100;
	int z = x + 15 * Sd[9].TgRa;
	rectangle(x , y , z , y + 40 );
	int yVao = y - 20;
	int xH = x;
	for(int i = 0; i < 10; i++)
	{
		int tam = Sd[i].TgVao;
		stringstream strs;
		strs << tam;
		string temp_str = strs.str();
		char* char_type = (char*) temp_str.c_str();
		outtextxy(x+15*Sd[i].TgVao,y+50, char_type);
	}
	for(int i = 0; i < 10; i++)
	{
		int tam = Sd[i].TgRa;
		stringstream strs;
		strs << tam;
		string temp_str = strs.str();
		char* char_type = (char*) temp_str.c_str();
		outtextxy(x+15*Sd[i].TgRa,y+50, char_type);
	}
	
	for(int i = 0; i < 10; i++)
	{
		setcolor(i+2);
		outtextxy(x + (15*tt[i].TgRL),y - 20 ,tt[i].Ten);
	}
	z = 50;
	int xCt = 20;
	int yCt = 600;
	outtextxy(xCt,yCt,"Chu Thich");
	for(int i = 0; i < 10; i++)
	{
		xCt = xCt + 100;
		setcolor(Sd[i].Color);
		setfillstyle(1,Sd[i].Color);
		outtextxy(xCt ,yCt, Sd[i].Ten);
		bar(xCt + 40,yCt,xCt+40+30,yCt+20);	
	}
	
	for(int i = 0; i < 10; i++)
	{
		setfillstyle(1,Sd[i].Color);
		z = 50 +(15 * Sd[i].TgRa); 		
		bar(xH,y,z,y+40);
		delay(1000);
		xH = z;
	}
	float TgChoTB = 0;
	for(int i = 0; i < 10; i++)
	{
		TgChoTB = TgChoTB + Sd[i].TgCho;
	}
	TgChoTB = TgChoTB / 10;
	setcolor(15);
	outtextxy(20 ,180, "Thoi Gian Cho TB:");
	float tam = TgChoTB;
	stringstream strs;
	strs << tam;
	string temp_str = strs.str();
	char* char_type = (char*) temp_str.c_str();
	outtextxy(200,180, char_type);


//	z = 50;
	
/*	for(int i = 0; i < 10; i++)
	{
		setfillstyle(1,Sd[i].Color);
		z = 50 +(15 * Sd[i].TgRa); 		
		bar(xH,y,z,y+40);
		delay(1000);
		xH = z;
	}*/
	
	x = 50;
	y = 260;
	z = x + 15 * SdRR[SodoNon-1].TgRa;
	rectangle(x , y , z , y + 40 );
	
	yVao = y - 20;
	xH = x;
	/*for(int i = 0; i < SodoNon; i++)
	{
		int tam = SdRR[i].TgVao;
		stringstream strs;
		strs << tam;
		string temp_str = strs.str();
		char* char_type = (char*) temp_str.c_str();
		outtextxy(x+15*SdNon[i].TgVao,y+50, char_type);
	}*/
	setcolor(15);
	outtextxy(20,220,"Priority Khong doc quyen");
	for(int i = 0; i < SodoNon; i++)
	{
		if(SdNon[i].TgCho != 0)
		{
			int tam = SdNon[i].TgVao;
			stringstream strs;
			strs << tam;
			string temp_str = strs.str();
			char* char_type = (char*) temp_str.c_str();
			outtextxy(50+15*SdNon[i].TgVao,y+50, char_type);
		}
	}
	outtextxy(50+15*0,y+50, "0");
	outtextxy(50+15*1,y+50, "1");
	outtextxy(50+15*5,y+50, "5");
	outtextxy(50+15*SdNon[SodoNon-1].TgRa,y+50, "69");
	for(int i = 0; i < 10; i++)
	{
		setcolor(i+2);
		outtextxy(x + (15*tt[i].TgRL),y - 20 ,tt[i].Ten);
	}
	for(int i = 0; i < SodoNon; i++)
	{
		setfillstyle(1,SdNon[i].Color);
		z = 50 +(15 * SdNon[i].TgRa); 		
		bar(xH,y,z,y+40);
		delay(100);
		xH = z;
	}
	float TgChoTB2 = 0;
	for(int i = 0; i < SodoNon; i++)
	{
		TgChoTB2 = TgChoTB2 + SdNon[i].TgCho;
	}
	TgChoTB2 = TgChoTB2 / 10;
	setcolor(15);
	outtextxy(20 ,350, "Thoi Gian Cho TB:");
	float tam2 = TgChoTB2;
	stringstream strs2;
	strs2 << tam2;
	string temp_str2 = strs2.str();
	char* char_type2 = (char*) temp_str2.c_str();
	outtextxy(200,350, char_type2);
	
	
	x = 50;
	y = 440;
	z = x + 15 * SdRR[SodoRR-1].TgRa;
	rectangle(x , y , z , y + 40 );
	yVao = y - 20;
	xH = x;
	for(int i = 0; i < SodoRR; i++)
	{
		int tam = SdRR[i].TgVao;
		stringstream strs;
		strs << tam;
		string temp_str = strs.str();
		char* char_type = (char*) temp_str.c_str();
		outtextxy(x+15*SdRR[i].TgVao,y+50, char_type);
	}
	setcolor(15);
	outtextxy(20,380,"Round Robin");
	for(int i = 0; i < SodoRR; i++)
	{
		int tam = SdRR[i].TgRa;
		stringstream strs;
		strs << tam;
		string temp_str = strs.str();
		char* char_type = (char*) temp_str.c_str();
		outtextxy(x+15*SdRR[i].TgRa,y+50, char_type);
	}
	for(int i = 0; i < 10; i++)
	{
		setcolor(i+2);
		outtextxy(x + (15*tt[i].TgRL),y - 20 ,tt[i].Ten);
	}
	for(int i = 0; i < SodoRR; i++)
	{
		setfillstyle(1,SdRR[i].Color);
		z = 50 +(15 * SdRR[i].TgRa); 		
		bar(xH,y,z,y+40);
		delay(1000);
		xH = z;
	}
	float TgChoTB1 = 0;
	for(int i = 0; i < SodoRR; i++)
	{
		TgChoTB1 = TgChoTB1 + SdRR[i].TgCho;
	}
	TgChoTB1 = TgChoTB1 / 10;
	setcolor(15);
	outtextxy(20 ,520, "Thoi Gian Cho TB:");
	float tam1 = TgChoTB1;
	stringstream strs1;
	strs1 << tam1;
	string temp_str1 = strs1.str();
	char* char_type1 = (char*) temp_str1.c_str();
	outtextxy(200,520, char_type1);
	
	
	while(!kbhit()) delay(1);		// pause screen	
}

int main(int argc, char *argv[])
{
 	TT *t = new TT[10];
 	TT *tt = new TT[10];
 	Sodo *Sd = new Sodo[100];
 	t  = NhapDL();
 	int qtime = rand() % 10 + 1;
 	cout<<"Quantim  = "<<qtime<<endl;
 	InDLVao(t);
 	for(int i = 0; i < n; i++)
 	{
 		tt[i] = t[i];
 	}
 	TT *ttnon = new TT[10];
 	for(int i = 0; i < n; i++)
 	{
 		ttnon[i] = t[i];
 	}
 	TT *ttnon2 = new TT[10];
 	for(int i = 0; i < n; i++)
 	{
 		ttnon2[i] = t[i];
 	}
 	int Sodo1 = 0;
 	Sodo *Sdnon = new Sodo[100];
 	Sodo *Sdnon2 = new Sodo[100];
 	cout<<endl;
	cout<<"Priority Doc Quyen" << endl;
 	Priority(t, Sd, Sodo1);
 	InDLRa(Sd, Sodo1);
 	int Sodonon1 = 0;
 	cout<<"Priority Khong Doc Quyen" << endl;
 	Priority_Non(ttnon2,Sdnon2,Sodonon1);
 	InDLRa(Sdnon2, Sodonon1);
 	int Sodonon2 = 0;
 	cout<<"Round Robin" << endl;
 	RR(ttnon, Sdnon, Sodonon2, qtime);
 	InDLRa(Sdnon, Sodonon2);
	ManHinh(tt, Sd, ttnon, Sdnon, Sodonon2,ttnon2,Sdnon2,Sodonon1 );
	return 0;        
	
}
