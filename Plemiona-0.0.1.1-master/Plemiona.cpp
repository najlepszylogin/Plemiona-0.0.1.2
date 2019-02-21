#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>
#include "MMSystem.h"
#include <cmath>

#define bloczek 219
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


#define skret_lewo_gora 201
#define skret_prawo_gora 187
#define prosto_dol 186
#define skret_lewo_dol 188
#define skret_prawo_dol 200
#define prosto_bok 205
#define skrzyzowanie 206
#define skrzyzowanie_lewo 185
#define skrzyzowanie_prawo 204
#define skrzyzowanie_gora 202
#define skrzyzowanie_dol 203

using namespace std;
HANDLE hOut;

string komunikat_domyslny = "Brak komunikatow moj Panie";

 

char woda=176;
char gora=94;
char dom = 178;
char stolica = 219;
 char dom2 = 177;
 char mapa[137][201];
 char postac = 193;
 
 char blok = bloczek;
 char osadnik = 79;
 char robotnik = 82;
 char osada = 254;
 char wioska = 87;
 char farma = 206;
 char kopalnia = 88;
 char tartak = 84;
  int ilosc_barbarzyncow;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void clear(int x,int y)
{
	for(int i=x;i<220;i++){
		for(int j=y;j<75;j++){
			gotoxy(i,j);
			cout << " ";
		}
	}
}

void cls()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}


struct struktura_miasto
{
	string nazwa;
	int x1;
	int y1;
	float przychod_zloto;
	float przychod_drewno;
	float przychod_zywnosc;
	float przychod_kamien;
	int ludnosc;
	int max_zolnierzy;
	float obrona;
	int przychod_nauka;
	int drewno;
	int zywnosc;
	int kamien;
	bool woda;
	int przychod_wiara;
	int produkcja;
	int przychod_produkcja;
	bool menu_osady;
	int podatek;
	int garnizon[10];
	
};

struct struktura_budowli
{
	int id;
	string nazwa;
	int koszt_drewno;
	int koszt_kamien;
	int koszt_zywnosc;
	int koszt_zloto;
	int koszt_produkcja;
	bool budowa;
	int max_lvl;
	int lvl;
	int nauka;
	int wiara;
	int zywnosc;
	int drewno;
	int kamien;
	int zloto;
	int produkcja;
	int ludnosc;
	int max_zolnierzy;
	string opis;
	string wymagania1;
	string wymagania2;
	string wymagania3;
	string wymagania4;
	string wymagania5;
	char wyglad[9][21];
};

struct struktura_budowli_osada
{
 	string nazwa;
	int koszt_drewno;
	int koszt_kamien;
	int koszt_zywnosc;
	int koszt_zloto;
	int koszt_produkcja;
	bool budowa;
	int max_lvl;
	int lvl;
	int nauka;
	int wiara;
	int zywnosc;
	int drewno;
	int kamien;
	int zloto;
	int produkcja;
	int ludnosc;
	int max_zolnierzy;
	string opis;
	string wymagania1;
	string wymagania2;
	string wymagania3;
	string wymagania4;
};

struct struktura_jednostek
{
	float atak;
	float obrona;
	int utrzymanie;
	int koszt_zloto;
	int koszt_produkcja;
	int koszt_zywnosc;
	int koszt_kamien;
	int koszt_drewno;
	int armia;
	int koszt_wiara;
	bool zasieg;
	bool jazda;
	int wielkosc;
	string wymagania;
	string wymagania_osada;
	string wymagania_najmu;
	string nazwa;
	string atuty;
};

struct struktura_armii
{
	int id;
	int x;
	int y;
	float atak;
	float obrona;
	int utrzymanie;
	int pikinierzy;
	int lucznicy;
	int kusznicy;
	int ciezkozbrojni;
	int lekka_jazda;
	int ciezka_jazda;
	int tarany;
	int elity;
	int miasto_domowe;
	string nazwa;
	int wielkosc;
};

struct struktura_garnizonu
{
string nazwa;
int ilosc;
int wielkosc;
};

struktura_garnizonu sjednostki[12][12]={{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}},
									{
									{"Robotnik",0,0},{"Osadnik",0,0},{"Pikinier",0,1},{"Lucznik",0,1},{"Kusznik",0,2},{"Ciezkozbrojny",0,2},{"Lekka Jazda",0,2},{"Ciezka Jazda",0,3},{"Taran",0,3},{"Elita",0,3},{"WYSTAW",0}}};


struktura_jednostek pikinier[12]=
{
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"},
	{3,2,1,100,200,200,200,150,0,650,false,false,1,"1 poziom koszar","1 poziom koszar","1 poziom obozu","Pikinierzy","Zadaje 1.5 razy wiecej obrazen taranom"}
};
struktura_jednostek lucznik[12]=
{
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"},
	{4,1,1,100,250,200,100,200,0,650,true,false,1,"Lowiectwo oraz koszary na 2 poziomie","Lowiectwo oraz koszary na 2 poziomie","1 poziom obozu","Lucznicy","Podczas ataku omija punkty obrony"}
};
struktura_jednostek kusznik[12]=
{
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	{5,2,2,200,400,350,200,350,0,850,true,false,2,"Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","Koszary na 3 poziomie oraz Obrobka Zelaza oraz Lowiectwo","2 poziom obozu","Kusznicy","Podczas ataku omija punkty obrony"},
	
};
struktura_jednostek ciezkozbrojny[12]=
{
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"},
	{6,4,3,250,400,300,300,200,0,1000,false,false,2,"Koszary na 4 poziomie oraz Obrobka Zelaza","Koszary w Stolicy na 4 poziomie oraz Obrobka Zelaza","2 poziom obozu","Ciezkozbrojni","x1.5 obrazen zadawanych obronie"}
};
struktura_jednostek lekka_jazda[12]=
{
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{4,2,2,150,250,250,250,200,0,1000,false,true,2,"Stajnia na 1 poziomie","Stajnia na 1 poziomie","2 poziom obozu","Lekka Jazda","Zadaja 1,25 razy wiecej obrazen pikinierom i ciezkozbrojnym"}
};
struktura_jednostek ciezka_jazda[12]=
{
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"},
	{7,3,3,300,450,350,350,250,0,1550,false,true,3,"Stajnia na 3 poziomie oraz Obrobka Stali","Stajnia na 3 poziomie oraz Obrobka Stali","3 poziom obozu","Ciezka Jazda","Zadaja 1,5 razy wiecej obrazen pikinierom i ciezkozbrojnym"}
};
struktura_jednostek taran[11]=
{
	
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"},
	{10,1,3,300,450,100,100,350,0,1750,true,false,3,"Warsztat na 2 poziomie","Warsztat na 2 poziomie","3 poziom obozu","Taran","Moze niszczyc tylko obrone wroga oraz miasta"}
};
struktura_jednostek elita=
{
	8,6,4,400,400,400,400,400,0,2300,false,false,3,"Akademia na 1 poziomie oraz Obrobka Stali","Akademia na 1 poziomie oraz Obrobka Stali","3 poziom obozu","Elita"
};



 struktura_budowli akademia=
 {
 	9,"Akademia", 700,500,250,400,1000,false,2,0,2,0,-4,-4,-4,-5,0,0,4,"Pozwala rekrutowac elity","4 poziom ratusza","5 poziom kapitolu "
 };
 struktura_budowli kapitol=
 {
 	10,"Kapitol",500,250,240,300,950,false,5,0,5,0,10,4,4,7,0,2000,3,"Jako centralny budynek panstwa daje mozliwosci rozwoju","1 poziom ratusza"," "," "," ","Administracja"
 };
 struktura_budowli ratusz=
 {
 	0,"Ratusz", 200,200,350,100,100,false,5,0,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu","4 poziom kapitolu"
 };
 struktura_budowli rynek=
 {
 	1,"Rynek",300,200,100,50,400,false,3,0,0,2,2,2,2,2,2,0,0,"Pozwala na wymiane surowcow","1 poziom ratusza","2 poziom ratusza","4 poziom ratusza oraz Waluta"
 };
 struktura_budowli mieszkalna=
 {
 	2,"Mieszkalna",200,150,300,50,350,false,3,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom ratusza","2 poziom ratusza","3 poziom ratusza"
 };
 struktura_budowli handlowa=
 {
 	3,"Handlowa",200,150,300,50,350,false,3,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom ratusza","3 poziom ratusza","4 poziom ratusza"
 };
 struktura_budowli naukowa=
 {
 	4,"Naukowa",200,150,300,50,350,false,3,0,8,0,-2,-2,-2,-2,2,0,0,"Naukowcy wytwarzaja tu nauke"," 2 poziom ratusza","3 poziom ratusza","5 poziom ratusza"
 };
 struktura_budowli wojskowa=
 {
 	5,"Wojskowa",200,150,300,50,350,false,3,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom ratusza","3 poziom ratusza","5 poziom ratusza"
 };
 struktura_budowli religijna=
 {
 	6,"Religijna",200,150,300,50,350,false,3,0,0,8,-2,-2,-2,2,0,0,-1,"Pielgrzymi studiuja tu nauki koscielne dajac wiare","2 poziom ratusza"," 4 poziom ratusza","5 poziom kapitolu"
 };
 struktura_budowli rekreacyjna=
 {
 	7,"Rekreacyjna",200,150,300,50,350,false,3,0,0,0,1,1,1,1,0,500,0,"Mieszkancy moga sie tu zrelaksowac co daje premie do surowcow","1 poziom ratusza","2 poziom ratusza","4 poziom ratusza"
 };
 struktura_budowli szkola=
 {
 	8,"Szkola",350,300,150,100,500,false,2,0,10,0,-1,-1,-1,-1,0,0,0,"Uczy wszystkich obywateli","1 poziom ratusza","3 poziom ratusza"
 };
 struktura_budowli mur=
 {
 	11,"Mur",10,30,5,0,25,false,3,0,0,0,0,0,0,0,0,0,0,"Dodaje obrone do miasta za kazdy fragment","1 poziom ratusza","3 poziom ratusza","5 poziom ratusza"
 };
 struktura_budowli koszary=
 {
 	12,"Koszary",350,300,150,100,500,false,4,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom ratusza","2 poziom ratusza","4 poziom ratusza","5 poziom ratusza"
 };
 struktura_budowli huta=
 {
 	13,"Huta",400,400,400,100,500,false,2,0,0,0,0,0,5,5,10,0,0,"Zwieksza produkcje miasta","2 poziom ratusza","4 poziom ratusza"
 };
 struktura_budowli oboz=
 {
 	14,"Oboz",200,150,300,200,350,false,3,0,0,0,0,0,0,-1,0,0,2,"Pozwala kupowac jednostki za zloto","3 poziom ratusza","4 poziom ratusza","5 poziom ratusza"
 };
 struktura_budowli bank=
 {
 	15,"Bank",400,200,400,300,500,false,2,0,0,0,0,0,0,10,0,0,0,"Zwieksza przychod zlota","4 poziom ratusza","5 poziom ratusza",
 };
 struktura_budowli gildia=
 {
 	16,"Gildia",350,300,200,100,450,false,3,0,0,0,0,0,0,-3,0,0,0,"Zmniejsza ilosc produkcji potrzebnej do stworzenia osadnikow i robotnikow","2 poziom ratusza","4 poziom ratusza","5 poziom kapitolu"
 };
 struktura_budowli biblioteka=
 {
 	17,"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom ratusza","4 poziom ratusza"
 };
 struktura_budowli park=
 {
 	19,"Park",150,200,200,50,200,false,3,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom ratusza","3 poziom ratusza","5 poziom ratusza"
 };
 struktura_budowli pomnik=
 {
 	20,"Pomnik",100,100,100,50,150,false,3,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom ratusza","2 poziom ratusza","4poziom ratusza"
 };
 struktura_budowli ambasada=
 {
 	21,"Ambasada",350,300,200,100,450,false,3,0,0,4,0,0,0,-2,0,1000,2,"Daje wieksza premie przeciwko barabrzyncom","4 poziom ratusza","5 poziom ratusza","5 poziom kapitolu"
 };
 struktura_budowli port=
 {
 	22,"Port",400,200,350,125,600,false,3,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom ratusza","3 poziom ratusza","4 poziom ratusza oraz Nawigacja"
 };
 struktura_budowli teatr=
 {
 	23,"Teatr",300,250,300,250,400,false,2,0,4,4,0,0,0,5,0,0,0,"Mieszkancy moga korzystac z dobr kultury co zwieksza produkcje niektorych surowcow","4 poziom ratusza oraz Sztuka","5 poziom kapitolu"
 };
 struktura_budowli tawerna=
 {
 	24,"Tawerna",250,300,100,50,300,false,3,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom ratusza","3 poziom ratusza","4 poziom ratusza oraz Browarnictwo"
 };
 struktura_budowli droga=
 {
 	25,"Droga",10,0,5,5,10,false,2,0,0,0,0,0,0,0,0,10,0,"Wazny element miasta"," ","4 poziom ratusza oraz Infrastruktura"
 };
 struktura_budowli magazyn=
 {
 	26,"Magazyn",400,250,400,250,300,false,4,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom ratusza","3 poziom ratusza","4 poziom ratusza oraz Hodowla","5 poziom kaitolu"
 };
 struktura_budowli mlyn=
 {
 	27,"Mlyn",250,100,250,50,250,false,4,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom ratusza","3 poziom ratusza","4 poziom ratusza","5 poziom ratusza"
 };
 struktura_budowli plac=
 {
 	28,"Plac",150,150,100,100,150,false,1,0,0,0,0,0,0,0,0,0,0,"Pozwala na formowanie armii z jednostek","1 poziom ratusza"
 };
 struktura_budowli tartakb=
 {
 	29,"Tartak",200,50,200,150,250,false,4,0,0,0,0,3,0,0,5,0,0,"Zwieksza produkcje drewna","1 poziom ratusza","3 poziom ratusza","4 poziom ratusza","5 poziom ratusza"
 };
 struktura_budowli kamieniarz=
 {
 	30,"Kamieniarz",200,50,200,150,250,false,4,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom ratusza","3 poziom ratusza","4 poziom ratusza","5 poziom ratusza"
 };
 struktura_budowli kolos=
 {
 	31,"Kolos",7000,7000,7000,7000,7000,false,1,0,20,20,20,20,20,20,20,5000,10,"Cud ktory prowadzi do wygranej","5 poziom kapitolu"
 };
 struktura_budowli kosciol=
 {
 	32,"Kosciol",300,100,300,200,300,false,3,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom ratusza","3 poziom ratusza","4 poziom ratusza"
 };
 struktura_budowli katedra=
 {
 	33,"Katedra",400,200,400,300,500,false,3,0,0,20,0,0,0,4,0,2500,0,"Zwieksza wiare","4 poziom ratusza oraz Ewangelizacja","5 poziom ratusza","5 poziom kapitolu"
 };
 struktura_budowli skarbiec=
 {
 	34,"Skarbiec",300,200,350,450,500,false,3,0,0,0,0,0,0,10,0,0,0,"Ochrona zlota daje zloto","3 poziom ratusza","5 poziom ratusza","5 poziom kapitolu"
 };
 struktura_budowli fort=
 {
 	35,"Fort",400,100,400,100,600,false,4,0,0,0,-2,-2,-2,-2,3,2000,7,"Zwieksza obrone miasta oraz ilosc zolnierzy w garnizonie","2 poziom ratusza","3 poziom ratusza","4 poziom ratusza","5 poziom kapitolu"
 };
 struktura_budowli weglarnia=
 {
 	36,"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom ratusza","3 poziom ratusza"
 };
 struktura_budowli warsztat=
 {
 	37,"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom ratusza","4 poziom ratusza oraz Mechanika"
 };
 struktura_budowli stajnia=
 {
 	38,"Stajnia",400,150,200,200,450,false,4,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom ratusza","3 poziom ratusza","4 poziom ratusza","5 poziom ratusza"
 };
 
 ////////////////////////////////////////////////////budynki osady
 
 
 struktura_budowli_osada rada_osady[11]=
 {
 {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 },
  {
 	"Rada Osady", 200,200,350,100,0,true,4,1,5,5,5,5,5,5,25,1000,3,"Przyspiesza rekrutacje robotnikow"," ","1 poziom kapitolu","2 poziom kapitolu","3 poziom kapitolu"
 }};
 
 struktura_budowli_osada koszary_osada[11]=
 {
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 },
 {
 	"Koszary",350,300,150,100,500,false,3,0,0,0,0,0,0,-2,0,0,5,"Mozliwosc rekrutacji jednostek piechoty","1 poziom rady osady","2 poziom rady osady","4 poziom rady osady" 
 }
 };
 
 struktura_budowli_osada warsztat_osada[11]=
 {{
 	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
 	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
 	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
 	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
 	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
 	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
 	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
 	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 },
 {
	"Warsztat",250,100,150,100,300,false,2,0,0,0,-2,0,0,0,7,0,0,"Zwieksza produkcje oraz pozwala rekrutowac tarany","2 poziom rady osady","4 poziom rady osady oraz Mechanika"
 }};
 
 struktura_budowli_osada stajnia_osada[11]=
 {
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	},
 	 {
 	"Stajnia",400,150,200,200,450,false,3,0,0,0,-1,-1,-1,-1,2,0,3,"Pozwala rekrutowac jazde","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 	}
 };
 
 struktura_budowli_osada magazyn_osada[11]=
 {
 	 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	},
 		 {
 	"Magazyn",400,250,400,250,300,false,3,0,0,0,5,5,5,2,5,0,0,"Zwieksza mozliwosci logistyczne dzieki temu produkcja surowcow jest zwiekszona","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady oraz Hodowla"
 	}
 };
 
 struktura_budowli_osada mlyn_osada[11]=
 {
 	 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },
 {
 	"Mlyn",250,100,250,50,250,false,3,0,0,0,0,0,0,0,5,0,0,"Zwieksza produkcje zywnosci","2 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 }
 };
 
 struktura_budowli_osada kamieniarz_osada[11]=
 {
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 }	,	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 },	
 {
 	"Kamieniarz",200,50,200,150,250,false,3,0,0,0,0,0,3,0,5,0,0,"Zwieksza produkcje kamienia","1 poziom rady osady","3 poziom rady osady","4 poziom rady osady"
 }
 };
 
 struktura_budowli_osada weglarz_osada[11]=
 {
	{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Weglarnia",150,100,350,100,300,false,2,0,0,0,-3,-1,6,0,7,0,0,"Zwieksza produkcje","1 poziom rady osady","3 poziom rady osady"
 	}
 
 };
 
 struktura_budowli_osada pomnik_osada[11]=
 {
 	 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	},
 		 {
 	"Pomnik",100,100,100,50,150,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga podziwiac potege wladcy co zwieksza produkcje surowcow","1 poziom rady osady","2 poziom rady osady"
 	}
 };
 
 struktura_budowli_osada park_osada[11]=
 {
 	{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 		{
 	"Park",150,200,200,50,200,false,2,0,2,2,1,1,1,1,1,0,0,"Mieszkancy moga sie zrelaksowac tu przez co zwiekszona jest produkcja surowcow","1 poziom rady osady","3 poziom rady osady"
 	}
 	
 };
 
 struktura_budowli_osada port_osada[11]=
 {
 	 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Port",400,200,350,125,600,false,2,0,0,0,20,4,4,-3,3,1000,0,"Zwieksza sie logistyka (wieksza produkcja surowcow i daje premie do produkcji z zewnetrznych budynkow)","2 poziom rady osady","3 poziom rady osady"
 	}
 };
 
 struktura_budowli_osada kosciol_osada[11]=
 {
 	 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	},
 		 {
 	"Kosciol",300,100,300,200,300,false,2,0,0,10,0,0,0,2,0,1000,0,"Zwieksza wiare","1 poziom rady osady","3 poziom rady osady"
 	}
 };
 
 struktura_budowli_osada biblioteka_osada[11]=
 {
 	{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	},
 		{
 	"Biblioteka",300,200,300,150,350,false,2,0,8,0,0,0,0,-3,0,0,0,"Mieszkancy moga z niej korzystac przez co zwieksza sie nauka","2 poziom rady osady","4 poziom rady osady"
 	}
 };
 
 struktura_budowli_osada mieszkalna_osada[11]=
 {
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 },
 	{
 	"Mieszkalna",200,150,300,50,350,false,2,0,0,0,-5,-4,-2,-2,5,3000,0,"Dodaje miejsca zamieszkania","1 poziom rady osady","2 poziom rady osady"
 }
 };
 
  struktura_budowli_osada handlowa_osada[11]=
  {
  	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 },
 	{
 	"Handlowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,8,2,0,0,"Dzialania handlowe dodaja zloto do skarbca"," 2 poziom rady osady","3 poziom rady osady"
 }
  };
 
 struktura_budowli_osada robotnicza_osada[11]=
 {
 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	},
 	 	 {
 	"Robotnicza",200,150,300,50,350,false,2,0,0,0,1,1,1,1,15,500,0,"Glowne miejsce pracy mieszkancow osady","1 poziom rady osady","2 poziom rady osady"
 	}
 };
 
 struktura_budowli_osada wojskowa_osada[11]=
 {
 	 {
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Wojskowa",200,150,300,50,350,false,2,0,0,0,-2,-2,-2,-2,2,0,4,"Zolnierze ucza sie tu wlaczyc i tworzy miejsca dla nich"," 2 poziom rady osady","3 poziom rady osady"
 	}
 };
 
 struktura_budowli_osada tawerna_osada[11]=
 {
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	},
 	{
 	"Tawerna",250,300,100,50,300,false,2,0,1,1,1,1,1,1,0,0,1,"Zadowoleni mieszkancy lepiej pracuja co zwieksza produkcje surowcow","1 poziom rady osady","3 poziom rady osady"
 	}
 };
 

 
 ///////////////////////////////////////////////////////////////////
 
  bool menu=true;
 bool wybor_jednostki=false;
 bool budowa=false;
 bool nazwa=false;
 bool menu_budowy=false;
 bool ruch=false;
 bool mapa_glowna=true;
 bool bmapa_stolicy=false;
 bool lista_miast=false;
 bool menu_stolica=true;
 bool budowa_miasto=false;
 bool rozbudowa=false;
bool rekrutacja=false;
int liczba_armii=0;
int liczba_zolnierzy=0;
bool bplac=false;
 char mapa_armii[127][201];
 bool najmij=false;
 bool menu_osada=false;
 bool blisko=false;
 bool bkomunikat=false;
 bool gracz1=true;
 bool gracz2=false;
 bool ruch_barbarzyncow=false;
 

 char mapa_walki[49][73];

struktura_armii armia[50];

struktura_jednostek jrobotnik[11]=
{
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"},
	{0,2,1,50,150,25,10,10,0,300,false,false,0,"1 poziom Ratusza","2 poziom Rady Osady","1 poziom obozu","Robotnik"}
};
struktura_jednostek josadnik=
{
	0,2,2,500,500,100,100,100,0,1000,false,false,0,"1 poziom Ratusza","---","2 poziom obozu","Osadnik"
};
struktura_jednostek jarmia=
{
	0,0,0,0,0,0,0,0,0,0,false,false,0,"1 poziom Ratusza","1 poziom Rady Osady","1 poziom obozu","Armia"	
};


struktura_miasto miasto[11];



void budowlanka(struktura_budowli budowla, int x, int y, char mapa_stolicy[80][150], char bufor_miasta[80][150], int *bufor_budowa_miasto,int x0,int ksztalt){
	if(budowla.nazwa!="Droga"){
		if(budowla.nazwa!="Mur")
			mapa_stolicy[x][y]=254;
		}else{
		
	
	for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
				mapa_stolicy[i][j]=budowla.wyglad[i-x][j-y];
				if(budowla.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
			}
			}
		}
		{
			if(ksztalt%10==0)mapa_stolicy[x][y]=prosto_dol;
			if(ksztalt%10==1)mapa_stolicy[x][y]=prosto_bok;
			if(ksztalt%10==2)mapa_stolicy[x][y]=skrzyzowanie;
			if(ksztalt%10==3)mapa_stolicy[x][y]=skret_lewo_dol;
			if(ksztalt%10==4)mapa_stolicy[x][y]=skret_lewo_gora;
			if(ksztalt%10==5)mapa_stolicy[x][y]=skret_prawo_dol;
			if(ksztalt%10==6)mapa_stolicy[x][y]=skret_prawo_gora;
			if(ksztalt%10==7)mapa_stolicy[x][y]=skrzyzowanie_dol;
			if(ksztalt%10==8)mapa_stolicy[x][y]=skrzyzowanie_gora;
			if(ksztalt%10==9)mapa_stolicy[x][y]=skrzyzowanie_lewo;
			if(ksztalt%10==10)mapa_stolicy[x][y]=skrzyzowanie_prawo;
		}
		
			*bufor_budowa_miasto=x0;
			gotoxy(90,27);
			for(int i=0;i<9;i++){
				for(int j=0;j<21;j++)cout << budowla.wyglad[i][j];
				gotoxy(90,28+i);
			}
			system("CLS");
			bufor_budowa_miasto=0;
			gotoxy(114,10);
			cout << budowla.nazwa<<"                                        ";
			gotoxy(110,11);
			cout << budowla.opis<<"                                        ";
			gotoxy(114,12);
			cout << "Koszt: ";
			gotoxy(110,13);
			cout <<"Drewno: "<< budowla.koszt_drewno<<"     ";
			gotoxy(110,14);
			cout<<"Kamien: " <<budowla.koszt_kamien<<"     ";
			gotoxy(110,15);
			cout<<"Zywnosc: "<<budowla.koszt_zywnosc<<"     ";
			gotoxy(110,16);
			cout <<"Zloto: "<< budowla.koszt_zloto<<"     ";
			gotoxy(110,17);
			cout << "Produkcja: "<<budowla.koszt_produkcja<<"     ";
			gotoxy(114,18);
			cout << "Zwieksza: ";
			gotoxy(110,19);
			cout << "Zloto/tura+"<<budowla.zloto<<"     ";
			gotoxy(110,20);
			cout << "Drewno/tura+"<<budowla.drewno<<"     ";
			gotoxy(110,21);
			cout<<"Kamien/tura+"<<budowla.kamien<<"     ";
			gotoxy(110,22);
			cout <<"Zywnosc/tura+"<<budowla.zywnosc<<"     ";
			gotoxy(110,23);
			cout <<"Produkcja/tura+"<<budowla.produkcja<<"     ";
			gotoxy(110,24);
			cout << "Ludnosc+"<<budowla.ludnosc<<"     ";
			gotoxy(110,25);
			cout << "Max.Zolnierzy+"<<budowla.max_zolnierzy<<"     ";
			gotoxy(110,26);
			cout << "Nauka/tura+"<<budowla.nauka<<"     ";
			gotoxy(110,27);
			cout << "Wiara/tura+"<<budowla.wiara<<"     ";
			gotoxy(110,28);
			cout <<"Wymagania: ";
			if(budowla.lvl==0){
			gotoxy(110,29);
			cout << budowla.wymagania1<<"                                        ";
			}
			if(budowla.lvl==1){
			gotoxy(110,29);
			cout << budowla.wymagania2<<"                                        ";
			}
			if(budowla.lvl==2){
			gotoxy(110,29);
			cout << budowla.wymagania3<<"                                        ";
			}
			if(budowla.lvl==3){
			gotoxy(110,29);
			cout << budowla.wymagania4<<"                                        ";
			}
			if(budowla.lvl==4){
			gotoxy(110,29);
			cout << budowla.wymagania5<<"                                        ";
			}
}

void budowlanka_osada(struktura_budowli_osada budowla){


		
			gotoxy(114,10);
			cout << budowla.nazwa<<"                                        ";
			gotoxy(110,11);
			cout << budowla.opis<<"                                        ";
			gotoxy(114,12);
			cout << "Koszt: ";
			gotoxy(110,13);
			cout <<"Drewno: "<< budowla.koszt_drewno<<"     ";
			gotoxy(110,14);
			cout<<"Kamien: " <<budowla.koszt_kamien<<"     ";
			gotoxy(110,15);
			cout<<"Zywnosc: "<<budowla.koszt_zywnosc<<"     ";
			gotoxy(110,16);
			cout <<"Zloto: "<< budowla.koszt_zloto<<"     ";
			gotoxy(110,17);
			cout << "Produkcja: "<<budowla.koszt_produkcja<<"     ";
			gotoxy(114,18);
			cout << "Zwieksza: ";
			gotoxy(110,19);
			cout << "Zloto/tura+"<<budowla.zloto<<"     ";
			gotoxy(110,20);
			cout << "Drewno/tura+"<<budowla.drewno<<"     ";
			gotoxy(110,21);
			cout<<"Kamien/tura+"<<budowla.kamien<<"     ";
			gotoxy(110,22);
			cout <<"Zywnosc/tura+"<<budowla.zywnosc<<"     ";
			gotoxy(110,23);
			cout <<"Produkcja/tura+"<<budowla.produkcja<<"     ";
			gotoxy(110,24);
			cout << "Ludnosc+"<<budowla.ludnosc<<"     ";
			gotoxy(110,25);
			cout << "Max.Zolnierzy+"<<budowla.max_zolnierzy<<"     ";
			gotoxy(110,26);
			cout << "Nauka/tura+"<<budowla.nauka<<"     ";
			gotoxy(110,27);
			cout << "Wiara/tura+"<<budowla.wiara<<"     ";
			gotoxy(110,28);
			cout <<"Wymagania: ";
			if(budowla.lvl==0){
			gotoxy(110,29);
			cout << budowla.wymagania1<<"                                        ";
			}
			if(budowla.lvl==1){
			gotoxy(110,29);
			cout << budowla.wymagania2<<"                                        ";
			}
			if(budowla.lvl==2){
			gotoxy(110,29);
			cout << budowla.wymagania3<<"                                        ";
			}
			if(budowla.lvl==3){
			gotoxy(110,29);
			cout << budowla.wymagania4<<"                                        ";
			}

}

void rozbudowlanka(int x0){
			struktura_budowli budowla;
			if(x0==0)budowla=ratusz;
			if(x0==1)budowla=rynek;
			if(x0==2)budowla=mieszkalna;
			if(x0==3)budowla=handlowa;
			if(x0==4)budowla=naukowa;
			if(x0==5)budowla=wojskowa;
			if(x0==6)budowla=religijna;
			if(x0==7)budowla=rekreacyjna;
			if(x0==8)budowla=szkola;
			if(x0==9)budowla=akademia;
			if(x0==10)budowla=kapitol;
			if(x0==11)budowla=mur;
			if(x0==12)budowla=koszary;
			if(x0==13)budowla=huta;
			if(x0==14)budowla=oboz;
			if(x0==15)budowla=bank;
			if(x0==16)budowla=gildia;
			if(x0==17)budowla=biblioteka;
			if(x0==18)budowla=park;
			if(x0==19)budowla=pomnik;
			if(x0==20)budowla=ambasada;
			if(x0==21)budowla=port;
			if(x0==22)budowla=teatr;
			if(x0==23)budowla=droga;
			if(x0==24)budowla=tawerna;
			if(x0==25)budowla=magazyn;
			if(x0==26)budowla=mlyn;
			if(x0==27)budowla=plac;
			if(x0==28)budowla=tartakb;
			if(x0==29)budowla=kamieniarz;
			if(x0==30)budowla=kolos;
			if(x0==31)budowla=kosciol;
			if(x0==32)budowla=katedra;
			if(x0==33)budowla=skarbiec;
			if(x0==34)budowla=fort;
			if(x0==35)budowla=weglarnia;
			if(x0==36)budowla=warsztat;
			if(x0==37)budowla=stajnia;
			if(x0==38)return;
			if(x0==39)return;
			if(x0==40)return;
			if(x0==41)return;

			gotoxy(114,10);
			cout << budowla.nazwa<< " bedzie rozbudowany(a) do poziomu "<<budowla.lvl+1<<"                    ";
			gotoxy(110,11);
			cout << budowla.opis;
			for(int i=110+budowla.opis.size();i<220;i++)cout << " ";
			gotoxy(114,12);
			cout << "Koszt: ";
			gotoxy(110,13);
			cout <<"Drewno: "<< budowla.koszt_drewno<<"                    ";
			gotoxy(110,14);
			cout<<"Kamien: " <<budowla.koszt_kamien<<"                    ";
			gotoxy(110,15);
			cout<<"Zywnosc: "<<budowla.koszt_zywnosc<<"                    ";
			gotoxy(110,16);
			cout <<"Zloto: "<< budowla.koszt_zloto<<"                    ";
			gotoxy(110,17);
			cout << "Produkcja: "<<budowla.koszt_produkcja<<"                    ";
			gotoxy(114,18);
			cout << "Zwieksza: ";
			gotoxy(110,19);
			cout << "Zloto/tura+"<<budowla.zloto*1.5<<"                    ";
			gotoxy(110,20);
			cout << "Drewno/tura+"<<budowla.drewno*1.5<<"                    ";
			gotoxy(110,21);
			cout<<"Kamien/tura+"<<budowla.kamien*1.5<<"                    ";
			gotoxy(110,22);
			cout <<"Zywnosc/tura+"<<budowla.zywnosc*1.5<<"                    ";
			gotoxy(110,23);
			cout <<"Produkcja/tura+"<<budowla.produkcja*1.5<<"                    ";
			gotoxy(110,24);
			cout << "Ludnosc+"<<budowla.ludnosc*1.5<<"                    ";
			gotoxy(110,25);
			cout << "Max.Zolnierzy+"<<budowla.max_zolnierzy*1.25<<"                    ";
			gotoxy(110,26);
			cout << "Nauka/tura+"<<budowla.nauka*1.5<<"                    ";
			gotoxy(110,27);
			cout << "Wiara/tura+"<<budowla.wiara*1.5<<"                    ";
			gotoxy(110,28);
			cout <<"Wymagania: ";
			if(budowla.lvl==0){
			gotoxy(110,29);
			cout << budowla.wymagania1<<"                                              ";
			}
			if(budowla.lvl==1){
			gotoxy(110,29);
			cout << budowla.wymagania2<<"                                              ";
			}
			if(budowla.lvl==2){
			gotoxy(110,29);
			cout << budowla.wymagania3<<"                                              ";
			}
			if(budowla.lvl==3){
			gotoxy(110,29);
			cout << budowla.wymagania4<<"                                              ";
			}
			if(budowla.lvl==4){
			gotoxy(110,29);
			cout << budowla.wymagania5<<"                                              ";
			}
}

void rozbudowlanka_osada(int x0, struktura_budowli_osada budowla){


			gotoxy(114,10);
			cout << budowla.nazwa<< " bedzie rozbudowany(a) do poziomu "<<budowla.lvl+1<<"                    ";
			gotoxy(110,11);
			cout << budowla.opis;
			for(int i=110+budowla.opis.size();i<220;i++)cout << " ";
			gotoxy(114,12);
			cout << "Koszt: ";
			gotoxy(110,13);
			cout <<"Drewno: "<< budowla.koszt_drewno<<"                    ";
			gotoxy(110,14);
			cout<<"Kamien: " <<budowla.koszt_kamien<<"                    ";
			gotoxy(110,15);
			cout<<"Zywnosc: "<<budowla.koszt_zywnosc<<"                    ";
			gotoxy(110,16);
			cout <<"Zloto: "<< budowla.koszt_zloto<<"                    ";
			gotoxy(110,17);
			cout << "Produkcja: "<<budowla.koszt_produkcja<<"                    ";
			gotoxy(114,18);
			cout << "Zwieksza: ";
			gotoxy(110,19);
			cout << "Zloto/tura+"<<budowla.zloto*1.5<<"                    ";
			gotoxy(110,20);
			cout << "Drewno/tura+"<<budowla.drewno*1.5<<"                    ";
			gotoxy(110,21);
			cout<<"Kamien/tura+"<<budowla.kamien*1.5<<"                    ";
			gotoxy(110,22);
			cout <<"Zywnosc/tura+"<<budowla.zywnosc*1.5<<"                    ";
			gotoxy(110,23);
			cout <<"Produkcja/tura+"<<budowla.produkcja*1.5<<"                    ";
			gotoxy(110,24);
			cout << "Ludnosc+"<<budowla.ludnosc*1.5<<"                    ";
			gotoxy(110,25);
			cout << "Max.Zolnierzy+"<<budowla.max_zolnierzy*1.25<<"                    ";
			gotoxy(110,26);
			cout << "Nauka/tura+"<<budowla.nauka*1.5<<"                    ";
			gotoxy(110,27);
			cout << "Wiara/tura+"<<budowla.wiara*1.5<<"                    ";
			gotoxy(110,28);
			cout <<"Wymagania: ";
			if(budowla.lvl==0){
			gotoxy(110,29);
			cout << budowla.wymagania1<<"                                              ";
			}
			if(budowla.lvl==1){
			gotoxy(110,29);
			cout << budowla.wymagania2<<"                                              ";
			}
			if(budowla.lvl==2){
			gotoxy(110,29);
			cout << budowla.wymagania3<<"                                              ";
			}
			if(budowla.lvl==3){
			gotoxy(110,29);
			cout << budowla.wymagania4<<"                                              ";
	}
};

void zwieksz_koszt(struktura_budowli &budowla){
	budowla.koszt_drewno=budowla.koszt_drewno*1.5;
	budowla.koszt_kamien=budowla.koszt_kamien*1.5;
	budowla.koszt_zywnosc=budowla.koszt_zywnosc*1.5;
	budowla.koszt_zloto=budowla.koszt_zloto*1.5;
	budowla.koszt_produkcja=budowla.koszt_produkcja*1.5;
}

void zwieksz_koszt_osada(struktura_budowli_osada &budowla){
	budowla.koszt_drewno=budowla.koszt_drewno*1.5;
	budowla.koszt_kamien=budowla.koszt_kamien*1.5;
	budowla.koszt_zywnosc=budowla.koszt_zywnosc*1.5;
	budowla.koszt_zloto=budowla.koszt_zloto*1.5;
	budowla.koszt_produkcja=budowla.koszt_produkcja*1.5;
}

void zwieksz_przychod(struktura_budowli &budowla, int *przychod_nauka, int *max_zolnierzy){
	
	miasto[1].przychod_zloto=miasto[1].przychod_zloto-budowla.zloto;
	miasto[1].przychod_drewno=miasto[1].przychod_drewno-budowla.drewno;
	miasto[1].przychod_kamien=miasto[1].przychod_kamien-budowla.kamien;
	miasto[1].przychod_zywnosc=miasto[1].przychod_zywnosc-budowla.zywnosc;
	miasto[1].przychod_wiara=miasto[1].przychod_wiara-budowla.wiara;
	miasto[1].przychod_produkcja=miasto[1].przychod_produkcja-budowla.produkcja;
	*przychod_nauka=*przychod_nauka-budowla.nauka;
	miasto[1].ludnosc=miasto[1].ludnosc-budowla.ludnosc;
	*max_zolnierzy=*max_zolnierzy-budowla.max_zolnierzy;
	
	budowla.drewno=budowla.drewno+budowla.drewno*0.5;
	budowla.zloto=budowla.zloto+budowla.zloto*0.5;
	budowla.kamien=budowla.kamien+budowla.kamien*0.5;
	budowla.zywnosc=budowla.zywnosc+budowla.zywnosc*0.5;
	budowla.produkcja=budowla.produkcja+budowla.produkcja*0.5;
	budowla.wiara=budowla.wiara+budowla.wiara*0.5;
	budowla.nauka=budowla.nauka+budowla.nauka*0.5;
	budowla.ludnosc=budowla.ludnosc+budowla.ludnosc*0.5;
	budowla.max_zolnierzy=budowla.max_zolnierzy+budowla.max_zolnierzy*0.25;
	
		miasto[1].przychod_zloto=miasto[1].przychod_zloto+budowla.zloto;
		miasto[1].przychod_drewno=miasto[1].przychod_drewno+budowla.drewno;
		miasto[1].przychod_kamien=miasto[1].przychod_kamien+budowla.kamien;
		miasto[1].przychod_zywnosc=miasto[1].przychod_zywnosc+budowla.zywnosc;
		miasto[1].przychod_wiara=miasto[1].przychod_wiara+budowla.wiara;
		miasto[1].przychod_produkcja=miasto[1].przychod_produkcja+budowla.produkcja;
		miasto[1].przychod_produkcja=miasto[1].przychod_produkcja+miasto[1].ludnosc*0.0005;
		*przychod_nauka=*przychod_nauka+budowla.nauka;
		miasto[1].ludnosc=miasto[1].ludnosc+budowla.ludnosc;
		*max_zolnierzy=*max_zolnierzy+budowla.max_zolnierzy;
}

void zwieksz_przychod_osada(struktura_budowli_osada &budowla, int *przychod_nauka, int *max_zolnierzy, int xm){
	
	miasto[xm].przychod_zloto=miasto[xm].przychod_zloto-budowla.zloto;
	miasto[xm].przychod_drewno=miasto[xm].przychod_drewno-budowla.drewno;
	miasto[xm].przychod_kamien=miasto[xm].przychod_kamien-budowla.kamien;
	miasto[xm].przychod_zywnosc=miasto[xm].przychod_zywnosc-budowla.zywnosc;
	miasto[xm].przychod_wiara=miasto[xm].przychod_wiara-budowla.wiara;
	miasto[xm].przychod_produkcja=miasto[xm].przychod_produkcja-budowla.produkcja;
	*przychod_nauka=*przychod_nauka-budowla.nauka;
	miasto[xm].ludnosc=miasto[xm].ludnosc-budowla.ludnosc;
	*max_zolnierzy=*max_zolnierzy-budowla.max_zolnierzy;
	
	budowla.drewno=budowla.drewno+budowla.drewno*0.5;
	budowla.zloto=budowla.zloto+budowla.zloto*0.5;
	budowla.kamien=budowla.kamien+budowla.kamien*0.5;
	budowla.zywnosc=budowla.zywnosc+budowla.zywnosc*0.5;
	budowla.produkcja=budowla.produkcja+budowla.produkcja*0.5;
	budowla.wiara=budowla.wiara+budowla.wiara*0.5;
	budowla.nauka=budowla.nauka+budowla.nauka*0.5;
	budowla.ludnosc=budowla.ludnosc+budowla.ludnosc*0.5;
	budowla.max_zolnierzy=budowla.max_zolnierzy+budowla.max_zolnierzy*0.25;
	
		miasto[xm].przychod_zloto=miasto[xm].przychod_zloto+budowla.zloto;
		miasto[xm].przychod_drewno=miasto[xm].przychod_drewno+budowla.drewno;
		miasto[xm].przychod_kamien=miasto[xm].przychod_kamien+budowla.kamien;
		miasto[xm].przychod_zywnosc=miasto[xm].przychod_zywnosc+budowla.zywnosc;
		miasto[xm].przychod_wiara=miasto[xm].przychod_wiara+budowla.wiara;
		miasto[xm].przychod_produkcja=miasto[xm].przychod_produkcja+budowla.produkcja;
		miasto[xm].przychod_produkcja=miasto[xm].przychod_produkcja+miasto[xm].ludnosc*0.0005;
		*przychod_nauka=*przychod_nauka+budowla.nauka;
		miasto[xm].ludnosc=miasto[xm].ludnosc+budowla.ludnosc;
		*max_zolnierzy=*max_zolnierzy+budowla.max_zolnierzy;
}

void zbuduj(struktura_budowli &budowla, int x, int y, char mapa_stolicy[80][150],char bufor_miasta[80][150],int *drewno, int *kamien, int *zywnosc, 
			int *zloto, int *max_zolnierzy, bool * budowa_miasto, bool *menu_budowy, bool *menu_stolica, int *przychod_nauka, int *x0){

		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=budowla.wyglad[i-x][j-y];
				
				if(budowla.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
				bufor_miasta[i][j]=mapa_stolicy[i][j];
				
		}
		}
		*drewno=*drewno-budowla.koszt_drewno;
		*kamien=*kamien-budowla.koszt_kamien;
		*zywnosc=*zywnosc-budowla.koszt_zywnosc;
		*zloto=*zloto-budowla.koszt_zloto;
		miasto[1].produkcja=miasto[1].produkcja-budowla.koszt_produkcja;
		miasto[1].przychod_zloto=miasto[1].przychod_zloto+budowla.zloto;
		miasto[1].przychod_drewno=miasto[1].przychod_drewno+budowla.drewno;
		miasto[1].przychod_kamien=miasto[1].przychod_kamien+budowla.kamien;
		miasto[1].przychod_zywnosc=miasto[1].przychod_zywnosc+budowla.zywnosc;
		miasto[1].przychod_wiara=miasto[1].przychod_wiara+budowla.wiara;
		miasto[1].przychod_produkcja=miasto[1].przychod_produkcja+budowla.produkcja;
		*przychod_nauka=*przychod_nauka+budowla.nauka;
		miasto[1].przychod_produkcja=miasto[1].przychod_produkcja+miasto[1].ludnosc*0.0005;
		miasto[1].ludnosc=miasto[1].ludnosc+budowla.ludnosc;
		*max_zolnierzy=*max_zolnierzy+budowla.max_zolnierzy;
		*budowa_miasto=false;
		*menu_budowy=false;
		*menu_stolica=true;
		budowla.budowa=true;
		*x0=0;
		system("CLS");
}

void zbuduj_osada(struktura_budowli_osada &budowla,int *drewno, int *kamien, int *zywnosc, 
			int *zloto, int *max_zolnierzy, bool *menu_budowy, bool *menu_osada, int *przychod_nauka, int *x0, int xm){

		*drewno=*drewno-budowla.koszt_drewno;
		*kamien=*kamien-budowla.koszt_kamien;
		*zywnosc=*zywnosc-budowla.koszt_zywnosc;
		*zloto=*zloto-budowla.koszt_zloto;
		miasto[xm].produkcja=miasto[xm].produkcja-budowla.koszt_produkcja;
		miasto[xm].przychod_zloto=miasto[xm].przychod_zloto+budowla.zloto;
		miasto[xm].przychod_drewno=miasto[xm].przychod_drewno+budowla.drewno;
		miasto[xm].przychod_kamien=miasto[xm].przychod_kamien+budowla.kamien;
		miasto[xm].przychod_zywnosc=miasto[xm].przychod_zywnosc+budowla.zywnosc;
		miasto[xm].przychod_wiara=miasto[xm].przychod_wiara+budowla.wiara;
		miasto[xm].przychod_produkcja=miasto[xm].przychod_produkcja+budowla.produkcja;
		*przychod_nauka=*przychod_nauka+budowla.nauka;
		miasto[xm].przychod_produkcja=miasto[xm].przychod_produkcja+miasto[xm].ludnosc*0.0005;
		miasto[xm].ludnosc=miasto[xm].ludnosc+budowla.ludnosc;
		*max_zolnierzy=*max_zolnierzy+budowla.max_zolnierzy;
		*menu_budowy=false;
		*menu_osada=true;
		budowla.budowa=true;
		*x0=0;
		system("CLS");
}


void rozbuduj(struktura_budowli budowla,int *drewno, int *kamien, int *zywnosc, 
			int *zloto, int *max_zolnierzy, bool *rozbudowa, bool *menu_stolica, int *przychod_nauka, int *x0){
	
		*drewno=*drewno-budowla.koszt_drewno;
		*kamien=*kamien-budowla.koszt_kamien;
		*zywnosc=*zywnosc-budowla.koszt_zywnosc;
		*zloto=*zloto-budowla.koszt_zloto;
		miasto[1].produkcja=miasto[1].produkcja-budowla.koszt_produkcja;
		*rozbudowa=false;
		*menu_stolica=true;

		*x0=0;
		system("CLS");
}

void rozbuduj_osada(struktura_budowli_osada budowla,int *drewno, int *kamien, int *zywnosc, 
			int *zloto, int *max_zolnierzy, bool *rozbudowa, bool *menu_osada, int *przychod_nauka, int *x0, int xm){
	
		*drewno=*drewno-budowla.koszt_drewno;
		*kamien=*kamien-budowla.koszt_kamien;
		*zywnosc=*zywnosc-budowla.koszt_zywnosc;
		*zloto=*zloto-budowla.koszt_zloto;
		miasto[xm].produkcja=miasto[xm].produkcja-budowla.koszt_produkcja;
		*rozbudowa=false;
		*menu_osada=true;

		*x0=0;
		system("CLS");
}


void rekrutowanka(int x0){
	
			if(bplac==true)x0=x0+2;
			struktura_jednostek jednostka;
			if(x0==0)jednostka=jrobotnik[1];
			if(x0==1)jednostka=josadnik;
			if(x0==2)jednostka=pikinier[1];
			if(x0==3)jednostka=lucznik[1];
			if(x0==4)jednostka=kusznik[1];
			if(x0==5)jednostka=ciezkozbrojny[1];
			if(x0==6)jednostka=lekka_jazda[1];
			if(x0==7)jednostka=ciezka_jazda[1];
			if(x0==8)jednostka=taran[1];
			if(x0==9)jednostka=elita;
			if(x0==10)return;
			if(bplac==false){
			gotoxy(114,12);
			cout << "Koszt: ";
			gotoxy(110,13);
			cout <<"Drewno: "<< jednostka.koszt_drewno<<"                    ";
			gotoxy(110,14);
			cout<<"Kamien: " <<jednostka.koszt_kamien<<"                    ";
			gotoxy(110,15);
			cout<<"Zywnosc: "<<jednostka.koszt_zywnosc<<"                    ";
			gotoxy(110,16);
			cout <<"Zloto: "<< jednostka.koszt_zloto<<"                    ";
			gotoxy(110,17);
			cout << "Produkcja: "<<jednostka.koszt_produkcja<<"                    ";
			gotoxy(110,18);
			cout << "Ludnosc: "<<jednostka.wielkosc*100<<"                    ";
			}
			
			gotoxy(114,19);
			cout << "Statystyki: ";
			gotoxy(110,20);
			cout << "Atak "<<jednostka.atak<<"                    ";
			gotoxy(110,21);
			cout << "Obrona "<<jednostka.obrona<<"                    ";
			gotoxy(110,22);
			cout<<"Zasiegowa "<<jednostka.zasieg<<"                    ";
			gotoxy(110,23);
			cout <<"Jazda "<<jednostka.jazda<<"                    ";
			gotoxy(110,24);
			cout <<"Utrzymanie "<<jednostka.utrzymanie<<"                    ";
			gotoxy(110,25);
			cout << "Wielkosc "<<jednostka.wielkosc<<"                    ";
			gotoxy(110,27);
			cout <<"Wymagania: ";
			gotoxy(110,28);
			cout << jednostka.wymagania<<"                                              ";
			gotoxy(110,29);
			cout<<"Specjalne: ";
			gotoxy(110,30);
			cout << jednostka.atuty<<"                                                       ";
}

void rekrutowanka_osada(int x0, int xm){
	
			if(bplac==true)x0=x0+2;
			struktura_jednostek jednostka;
			if(x0==0)jednostka=jrobotnik[xm];
			if(x0==1)jednostka=pikinier[xm];
			if(x0==2)jednostka=lucznik[xm];
			if(x0==3)jednostka=kusznik[xm];
			if(x0==4)jednostka=ciezkozbrojny[xm];
			if(x0==5)jednostka=lekka_jazda[xm];
			if(x0==6)jednostka=ciezka_jazda[xm];
			if(x0==7)jednostka=taran[xm];
			if(x0==8)return;
			if(bplac==false){
			gotoxy(114,12);
			cout << "Koszt: ";
			gotoxy(110,13);
			cout <<"Drewno: "<< jednostka.koszt_drewno<<"                    ";
			gotoxy(110,14);
			cout<<"Kamien: " <<jednostka.koszt_kamien<<"                    ";
			gotoxy(110,15);
			cout<<"Zywnosc: "<<jednostka.koszt_zywnosc<<"                    ";
			gotoxy(110,16);
			cout <<"Zloto: "<< jednostka.koszt_zloto<<"                    ";
			gotoxy(110,17);
			cout << "Produkcja: "<<jednostka.koszt_produkcja<<"                    ";
			gotoxy(110,18);
			cout << "Ludnosc: "<<jednostka.wielkosc*100<<"                    ";
			}
			
			gotoxy(114,19);
			cout << "Statystyki: ";
			gotoxy(110,20);
			cout << "Atak "<<jednostka.atak<<"                    ";
			gotoxy(110,21);
			cout << "Obrona "<<jednostka.obrona<<"                    ";
			gotoxy(110,22);
			cout<<"Zasiegowa "<<jednostka.zasieg<<"                    ";
			gotoxy(110,23);
			cout <<"Jazda "<<jednostka.jazda<<"                    ";
			gotoxy(110,24);
			cout <<"Utrzymanie "<<jednostka.utrzymanie<<"                    ";
			gotoxy(110,25);
			cout << "Wielkosc "<<jednostka.wielkosc<<"                    ";
			gotoxy(110,27);
			cout <<"Wymagania: ";
			gotoxy(110,28);
			cout << jednostka.wymagania_osada<<"                                              ";
			gotoxy(110,29);
			cout<<"Specjalne: ";
			gotoxy(110,30);
			cout << jednostka.atuty<<"                                                       ";
}

void najmowanka(int x0)
{
	struktura_jednostek jednostka;
			if(x0==0)jednostka=jrobotnik[1];
			if(x0==1)jednostka=josadnik;
			if(x0==2)jednostka=pikinier[1];
			if(x0==3)jednostka=lucznik[1];
			if(x0==4)jednostka=kusznik[1];
			if(x0==5)jednostka=ciezkozbrojny[1];
			if(x0==6)jednostka=lekka_jazda[1];
			if(x0==7)jednostka=ciezka_jazda[1];
			if(x0==8)jednostka=taran[1];
			if(x0==9)jednostka=elita;
			if(x0==10)return;
			if(bplac==false){
			gotoxy(114,12);
			cout << "Koszt: ";
			gotoxy(110,13);
			cout <<"Zloto: "<< jednostka.koszt_zloto*3<<"                    ";
			gotoxy(110,14);
			cout <<"Wiara: "<< jednostka.koszt_wiara<<"                    ";
			}
			
			gotoxy(114,15);
			cout << "Statystyki: ";
			gotoxy(110,16);
			cout << "Atak "<<jednostka.atak<<"                    ";
			gotoxy(110,17);
			cout << "Obrona "<<jednostka.obrona<<"                    ";
			gotoxy(110,18);
			cout<<"Zasiegowa "<<jednostka.zasieg<<"                    ";
			gotoxy(110,19);
			cout <<"Jazda "<<jednostka.jazda<<"                    ";
			gotoxy(110,20);
			cout <<"Utrzymanie "<<jednostka.utrzymanie<<"                    ";
			gotoxy(110,21);
			cout << "Wielkosc "<<jednostka.wielkosc<<"                    ";
			gotoxy(110,22);
			cout <<"Wymagania: ";
			gotoxy(110,23);
			cout << jednostka.wymagania_najmu<<"                                              ";

}

void rekrutuj(struktura_jednostek &budowla,int *drewno, int *kamien, int *zywnosc, 
			int *zloto, int *max_zolnierzy, bool *rekrutacja, bool *menu_stolica, int *x0){

		*drewno=*drewno-budowla.koszt_drewno;
		*kamien=*kamien-budowla.koszt_kamien;
		*zywnosc=*zywnosc-budowla.koszt_zywnosc;
		*zloto=*zloto-budowla.koszt_zloto;

		miasto[1].ludnosc=miasto[1].ludnosc-budowla.wielkosc*100;
		*rekrutacja=false;
		*menu_stolica=true;
		
			gotoxy(54,25);
			for(int i=0;i<70;i++)cout << blok;
			gotoxy(54,26);
			cout << blok;
			for(int i=0;i<68;i++)cout<< " ";
			cout << blok;
			gotoxy(54,28);
			cout << blok;
			for(int i=0;i<68;i++)cout<< " ";
			cout << blok;
			gotoxy(54,29);
			for(int i=0;i<70;i++)cout << blok;
			gotoxy(120,27);
			cout << "   " << blok;
			gotoxy(54,27);
			cout <<blok<< " Zrekrutowales " <<budowla.nazwa<<"                                          ";
			Sleep(1200);
		
		*x0=0;
		system("CLS");
}

void najmijv(struktura_jednostek &budowla, int *wiara, bool *najmij, int *zloto, int *x0, bool *menu_stolica)
{
		int xd=0;
		gotoxy(109,33);
		cout << "Wynierz metode platnosci";
		char ster;
		do{
		
		ster=getch();
		if(ster==KEY_RIGHT && xd!=1)xd++;
		if(ster==KEY_LEFT && xd!=0)xd--;
		gotoxy(109,33);
		SetConsoleTextAttribute( hOut, 7 );
		if(xd==0)cout << "Kup za: ZLOTO            ";
		if(xd==1)cout << "Kup za: WIARA            ";
		
		}while(ster!='e');
		if(xd==0)
		*zloto=*zloto-budowla.koszt_zloto*3;
		if(xd==1)
		*wiara=*wiara-budowla.koszt_wiara;
		*najmij=false;
		*menu_stolica=true;
		*x0=0;
		system("CLS");
}

void wystaw_armie(struktura_jednostek &jednostka, char mapa[137][201], int bufor_rekrutacji, char mapa_jednostek[137][201], int xm)
{
	char ster;
	int h=0;
	int y2=miasto[xm].y1;
	int x2=miasto[xm].x1;
	do{
		gotoxy(109,33);
		for(int i=miasto[xm].x1-1;i<=miasto[xm].x1+1;i++){
			for(int j=miasto[xm].y1-1;j<=miasto[xm].y1+1;j++){
				if(mapa_jednostek[i][j]!='R' && mapa_jednostek[i][j]!='O' && mapa_jednostek[i][j]!='A' && mapa_jednostek[i][j]!='B' && mapa[i][j]!=woda && mapa[i][j]!=gora && mapa[i][j]!=stolica && mapa[i][j]!=osada)SetConsoleTextAttribute( hOut, 10 );
				if(i==x2 && j==y2)SetConsoleTextAttribute( hOut, 14 );
				cout <<mapa[i][j];
				SetConsoleTextAttribute( hOut, 7 );
			}
			h++;
			gotoxy(109,33+h);
		}
		
		ster=getch();
		h=0;
		if(ster=='w' && x2-1!=miasto[xm].x1-2)x2--;
		if(ster=='s' && x2+1!=miasto[xm].x1+2)x2++;
		if(ster=='a' && y2-1!=miasto[xm].y1-2)y2--;
		if(ster=='d' && y2+1!=miasto[xm].y1+2)y2++;
		if(ster=='q' && mapa_jednostek[x2][y2]!='R' && mapa_jednostek[x2][y2]!='O' && mapa_jednostek[x2][y2]!='A' && mapa_jednostek[x2][y2]!='B' && mapa[x2][y2]!=woda && mapa[x2][y2]!=gora && mapa[x2][y2]!=stolica && mapa[x2][y2]!=osada){
			if(bufor_rekrutacji==0)mapa_jednostek[x2][y2]='R';
			if(bufor_rekrutacji==1)mapa_jednostek[x2][y2]='O';
			if(bufor_rekrutacji!=0 && bufor_rekrutacji!=1){	
			mapa_jednostek[x2][y2]='A';
			armia[liczba_armii].miasto_domowe=xm;
			armia[liczba_armii].x=x2;
			armia[liczba_armii].y=y2;
			armia[liczba_armii].id=liczba_armii;
			mapa_armii[x2][y2]=armia[liczba_armii].id+48;
			mapa_jednostek[x2][y2]='A';
			gotoxy(54,25);
		for(int i=0;i<40;i++)cout << blok;
		gotoxy(54,26);
		cout << blok;
		for(int i=0;i<38;i++)cout<< " ";
		cout << blok;
		gotoxy(54,28);
		cout << blok;
		for(int i=0;i<38;i++)cout<< " ";
		cout << blok;
		gotoxy(54,29);
		for(int i=0;i<40;i++)cout << blok;
		gotoxy(90,27);
		cout << "   " << blok;
		gotoxy(54,27);
		cout <<blok<< "  Wpisz nazwe armii: ";
		getline(cin, armia[liczba_armii].nazwa);

	gotoxy(54,27);
	for(int i=0;i<28;i++)cout << blok;

			cls;
			return;
			}
			return;
		}
		cls();
		
		
	}while(ster!=27);
	
}

void pokaz_armie(struktura_armii armia, int xm)
{
	int atak_razem;
	atak_razem=armia.pikinierzy*pikinier[xm].atak;
	atak_razem+=armia.lucznicy*lucznik[xm].atak;
	atak_razem+=armia.kusznicy*kusznik[xm].atak;
	atak_razem+=armia.ciezkozbrojni*ciezkozbrojny[xm].atak;
	atak_razem+=armia.lekka_jazda*lekka_jazda[xm].atak;
	atak_razem+=armia.ciezka_jazda*ciezka_jazda[xm].atak;
	atak_razem+=armia.tarany*taran[xm].atak;
	atak_razem+=armia.elity*elita.atak;
	int obrona_razem;
	obrona_razem=armia.pikinierzy*pikinier[xm].obrona;
	obrona_razem+=armia.lucznicy*lucznik[xm].obrona;
	obrona_razem+=armia.kusznicy*kusznik[xm].obrona;
	obrona_razem+=armia.ciezkozbrojni*ciezkozbrojny[xm].obrona;
	obrona_razem+=armia.lekka_jazda*lekka_jazda[xm].obrona;
	obrona_razem+=armia.ciezka_jazda*ciezka_jazda[xm].obrona;
	obrona_razem+=armia.tarany*taran[xm].obrona;
	obrona_razem+=armia.elity*elita.obrona;
	int utrzymanie;
	utrzymanie=armia.pikinierzy*pikinier[xm].utrzymanie;
	utrzymanie+=armia.lucznicy*lucznik[xm].utrzymanie;
	utrzymanie+=armia.kusznicy*kusznik[xm].utrzymanie;
	utrzymanie+=armia.ciezkozbrojni*ciezkozbrojny[xm].utrzymanie;
	utrzymanie+=armia.lekka_jazda*lekka_jazda[xm].utrzymanie;
	utrzymanie+=armia.ciezka_jazda*ciezka_jazda[xm].utrzymanie;
	utrzymanie+=armia.tarany*taran[xm].utrzymanie;
	utrzymanie+=armia.elity*elita.utrzymanie;
	
	gotoxy(110,30);
	cout << "ATAK: " << atak_razem<<"     ";
	gotoxy(110,31);
	cout << "OBRONA: "<<obrona_razem<<"    ";
	gotoxy(110,32);
	cout << "UTRZYMANIE: "<<utrzymanie<<"     ";
}

 int szansa=1;
 
 char mapa_stolicy[80][150];
 char bufor_miasta[80][150];
 char mapa_jednostek[127][201];
 char bufor_mjednostek[127][201];
 int mapa_farma[127][201];
 int mapa_wioska[127][201];
 int mapa_kopalnia[127][201];
 int mapa_tartak[127][201];
 char zasieg_miast[127][201];
 char teretorium[127][201];
 bool mgla_wojny[127][201];
 bool niewidocznosc[127][201];
 char bufor_widocznosci[137][201];
 int bufor_budowa=10;
 int bufor_budowa_miasto=45;
 int bufor_rekrutacja;
 
 int barbarzynca_x;
 int barbarzynca_y;
 bool barbarzynca_blad=false;
 int szansa_ruch;
 bool barbarzynca_atak=false;
 short bufor_barbarzyncow[137][201];
 bool koniec_ruchu=false;
 int min_x;
 int min_y;


void walka_barbarzyncy(struktura_armii armia, bool gracz1,bool gracz2,int *zloto,int *liczba_barbarzyncow){
	
	struktura_armii armia_barb;
	system("CLS");
	bool koniec=false;
	bool ruch=true;
	bool wygrana=false;
	int x0;
	int x1=-1;
	int x2=0;
	int maxrand;
	int max;
	char ster;
	bool pikinierzy=false;
	bool lucznicy=false;
	bool kusznicy=false;
	bool ciezkozbrojni=false;
	bool lekka_jazdy=false;
	bool ciezka_jazdy=false;
	bool tarany=false;
	bool elity=false;
	bool atak=false;
	bool menu=true;
	bool atak1=false;
	int rando[6];
	
	int atak_bufor;
	int atak_bufor_obrona;
	int obrona_bufor;
	int zycie_bufor;
	
	int miasto_domowe=armia.miasto_domowe;
	int identyfikator_gracz;
	int identyfikator_barb[5];
	string identyfikator_nazwy[8]={"Pikinier","Lucznik","Kusznik","Ciezkozbrojny","Lekka Jazda","Ciezka Jazda","Taran","Elita"};
	int zycie_pikinierzy[40];
	int zycie_lucznicy[40];
	int zycie_kusznicy[40];
	int zycie_ciezkozbrojni[40];
	int zycie_lekka_jazda[40];
	int zycie_ciezka_jazda[40];
	int zycie_tarany[40];
	int zycie_elity[40];
	int zycie_pikinierzy_barb[40];
	int zycie_lucznicy_barb[40];
	int zycie_kusznicy_barb[40];
	int zycie_ciezkozbrojni_barb[40];
	int zycie_lekka_jazda_barb[40];
	int zycie_ciezka_jazda_barb[40];
	////
	int obrona_pikinierzy[40];
	int obrona_lucznicy[40];
	int obrona_kusznicy[40];
	int obrona_ciezkozbrojni[40];
	int obrona_lekka_jazda[40];
	int obrona_ciezka_jazda[40];
	int obrona_tarany[40];
	int obrona_elity[40];
	int obrona_pikinierzy_barb[40];
	int obrona_lucznicy_barb[40];
	int obrona_kusznicy_barb[40];
	int obrona_ciezkozbrojni_barb[40];
	int obrona_lekka_jazda_barb[40];
	int obrona_ciezka_jazda_barb[40];
	string komunikat="Wybierz Twoja jednostke do potyczki";
	if(armia.wielkosc<=10){
	maxrand=(rand()%4+1);	
	
	}
	if(armia.wielkosc>10 && armia.wielkosc<=20){
		maxrand=(rand()%6+1);
	}
	if(armia.wielkosc>20){
	
	maxrand=(rand()%8+1);
	}
	
	armia_barb.wielkosc=0;
	max=armia.wielkosc;
	max=10;

	rando[0]=(rand()%maxrand);
	
	armia_barb.wielkosc=rando[0]*pikinier[11].wielkosc+1;
	armia_barb.pikinierzy=rando[0]+1;
	
	rando[1]=(rand()%maxrand);

	armia_barb.wielkosc+=(rando[1]*lucznik[11].wielkosc);
	armia_barb.lucznicy=rando[1];
	
	rando[2]=(rand()%maxrand);
	if(armia.wielkosc>10){
	armia_barb.wielkosc+=(rando[2]*kusznik[11].wielkosc);
	armia_barb.kusznicy=rando[2];
	}
		rando[3]=(rand()%maxrand);
	if(armia.wielkosc>10){
	armia_barb.wielkosc+=(rando[3]*ciezkozbrojny[11].wielkosc);
	armia_barb.ciezkozbrojni=rando[3];
	}
		rando[4]=(rand()%maxrand);
	if(armia.wielkosc>20){
	armia_barb.wielkosc+=(rando[4]*lekka_jazda[11].wielkosc);
	armia_barb.lekka_jazda=rando[4];
	}
			rando[5]=(rand()%maxrand);
	if(armia.wielkosc>20){
	armia_barb.wielkosc+=(rando[5]*ciezka_jazda[11].wielkosc);
	armia_barb.ciezka_jazda=rando[5];
	}
	
	
	for(int i=0;i<armia.pikinierzy;i++){
		zycie_pikinierzy[i]=pikinier[miasto_domowe].obrona*2;
		obrona_pikinierzy[i]=pikinier[miasto_domowe].obrona;
	}
		for(int i=0;i<armia.lucznicy;i++){
		zycie_lucznicy[i]=lucznik[miasto_domowe].obrona*2;
		obrona_lucznicy[i]=lucznik[miasto_domowe].obrona;
	}
		for(int i=0;i<armia.kusznicy;i++){
		zycie_kusznicy[i]=kusznik[miasto_domowe].obrona*2;
		obrona_kusznicy[i]=kusznik[miasto_domowe].obrona;
	}
		for(int i=0;i<armia.ciezkozbrojni;i++){
		zycie_ciezkozbrojni[i]=ciezkozbrojny[miasto_domowe].obrona*2;
		obrona_ciezkozbrojni[i]=ciezkozbrojny[miasto_domowe].obrona;
	}
		for(int i=0;i<armia.lekka_jazda;i++){
		zycie_lekka_jazda[i]=lekka_jazda[miasto_domowe].obrona*2;
		obrona_lekka_jazda[i]=lekka_jazda[miasto_domowe].obrona;
	}
		for(int i=0;i<armia.ciezka_jazda;i++){
		zycie_ciezka_jazda[i]=ciezka_jazda[miasto_domowe].obrona*2;
		obrona_ciezka_jazda[i]=ciezka_jazda[miasto_domowe].obrona;
	}
		for(int i=0;i<armia.tarany;i++){
		zycie_tarany[i]=taran[miasto_domowe].obrona*2;
		obrona_tarany[i]=taran[miasto_domowe].obrona;
	}
		for(int i=0;i<armia.elity;i++){
		zycie_elity[i]=elita.obrona*2;
		obrona_elity[i]=elita.obrona;
	}
	//////////////////////////
		for(int i=0;i<armia_barb.pikinierzy;i++){
		zycie_pikinierzy_barb[i]=pikinier[11].obrona*2;
		obrona_pikinierzy_barb[i]=pikinier[11].obrona;
	}
		for(int i=0;i<armia_barb.lucznicy;i++){
		zycie_lucznicy_barb[i]=lucznik[11].obrona*2;
		obrona_lucznicy_barb[i]=lucznik[11].obrona;
	}
		for(int i=0;i<armia_barb.kusznicy;i++){
		zycie_kusznicy_barb[i]=kusznik[11].obrona*2;
		obrona_kusznicy_barb[i]=kusznik[11].obrona;
	}
		for(int i=0;i<armia_barb.ciezkozbrojni;i++){
		zycie_ciezkozbrojni_barb[i]=ciezkozbrojny[11].obrona*2;
		obrona_ciezkozbrojni_barb[i]=ciezkozbrojny[11].obrona;
	}
		for(int i=0;i<armia_barb.lekka_jazda;i++){
		zycie_lekka_jazda_barb[i]=lekka_jazda[11].obrona*2;
		obrona_lekka_jazda_barb[i]=lekka_jazda[11].obrona;
	}
		for(int i=0;i<armia_barb.ciezka_jazda;i++){
		zycie_ciezka_jazda_barb[i]=ciezka_jazda[11].obrona*2;
		obrona_ciezka_jazda_barb[i]=ciezka_jazda[11].obrona;
	}
	
	
	while(koniec==false){

		

		
		gotoxy(20,17);
		cout<<"           /\                                                 /\ ";
		gotoxy(20,18);
 		cout<<" _         )(_______________________   ______________________ )(         _";
 		gotoxy(20,19);
		cout<<"(_)///////(**)______________________> <______________________(**)\\\\\\\\\\\\\\\(_)";
		gotoxy(20,20);
        cout<<"           )(                                                 )(";
        gotoxy(20,21);
        cout<<"           \/                                                 \/";
		gotoxy(30,23);
		cout << komunikat<<"                            ";
		
		gotoxy(76,1);
		cout << "Armia Gracza: ";
	gotoxy(76,2);
cout << "NAZWA/ILOSC POSIADANYCH                    ";
rekrutowanka(x0+2);
gotoxy(70,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(70,4);
cout <<blok<< "                          "<<blok;
gotoxy(70,5);
if(x0==0 && menu==true){
komunikat="Wybierz Twoja jednostke do potyczki";
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Pikinier / "<<armia.pikinierzy<<"           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Pikinier / "<<armia.pikinierzy<<"           "<<blok; 

gotoxy(70,6);
if(x0==1&& menu==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lucznik / "<<armia.lucznicy<<"            "<<blok; 
SetConsoleTextAttribute( hOut, 8 );

}
else
cout <<blok<<"   Lucznik / "<<armia.lucznicy<<"            "<<blok;
gotoxy(70,7);
if(x0==2&& menu==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kusznik / "<<armia.kusznicy<<"            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Kusznik / "<<armia.kusznicy<<"            "<<blok; 
gotoxy(70,8);
if(x0==3&& menu==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezkozbrojny / "<<armia.ciezkozbrojni<<"      "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezkozbrojny / "<<armia.ciezkozbrojni<<"      "<<blok; 

gotoxy(70,9);
if(x0==4&& menu==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lekka Jazda / "<<armia.lekka_jazda<<"        "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lekka Jazda / "<<armia.lekka_jazda<<"        "<<blok; 
gotoxy(70,10);
if(x0==5&& menu==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezka Jazda / "<<armia.ciezka_jazda<<"       "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezka Jazda / "<<armia.ciezka_jazda<<"       "<<blok;
gotoxy(70,11);
if(x0==6&& menu==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Taran / "<<armia.tarany<<"              "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Taran / "<<armia.tarany<<"              "<<blok;
gotoxy(70,12);
if(x0==7&& menu==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Elita / "<<armia.elity<<"              "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Elita / "<<armia.elity<<"              "<<blok; 
gotoxy(70,13);
cout <<blok<< "                          "<<blok;
gotoxy(70,14);
for(int i=0;i<28;i++)cout << blok;
		
		//////////////pokaz barbow///
		
gotoxy(10,1);
		cout << "Armia Barbarzyncow: ";
	gotoxy(10,2);
cout << "NAZWA/ILOSC POSIADANYCH                    ";
gotoxy(5,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(5,4);
cout <<blok<< "                          "<<blok;
gotoxy(5,5);
if(x1==0 && atak==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Pikinier / "<<armia_barb.pikinierzy<<"           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Pikinier / "<<armia_barb.pikinierzy<<"           "<<blok; 

gotoxy(5,6);
if(x1==1&& atak==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lucznik / "<<armia_barb.lucznicy<<"            "<<blok; 
SetConsoleTextAttribute( hOut, 8 );

}
else
cout <<blok<<"   Lucznik / "<<armia_barb.lucznicy<<"            "<<blok;
gotoxy(5,7);
if(x1==2&& atak==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kusznik / "<<armia_barb.kusznicy<<"            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Kusznik / "<<armia_barb.kusznicy<<"            "<<blok; 
gotoxy(5,8);
if(x1==3&& atak==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezkozbrojny / "<<armia_barb.ciezkozbrojni<<"      "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezkozbrojny / "<<armia_barb.ciezkozbrojni<<"      "<<blok; 

gotoxy(5,9);
if(x1==4&& atak==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lekka Jazda / "<<armia_barb.lekka_jazda<<"        "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lekka Jazda / "<<armia_barb.lekka_jazda<<"        "<<blok; 
gotoxy(5,10);
if(x1==5&& atak==true){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezka Jazda / "<<armia_barb.ciezka_jazda<<"       "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezka Jazda / "<<armia_barb.ciezka_jazda<<"       "<<blok;
gotoxy(5,11);
cout <<blok<< "                          "<<blok;
gotoxy(5,12);
for(int i=0;i<28;i++)cout << blok;

	if(atak1==true){
	gotoxy(0,60);	
	if(pikinierzy==true){
		for(int i=0;i<armia_barb.pikinierzy;i++){
			if(zycie_pikinierzy_barb[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Pikinier Wroga #"<<i+1<<" ("<<zycie_pikinierzy_barb[i]<<"/"<<obrona_pikinierzy_barb[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Pikinier Wroga #"<<i+1<<" ("<<zycie_pikinierzy_barb[i]<<"/"<<obrona_pikinierzy_barb[i]<<")       "; 
			}else
			cout<<"                      ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(lucznicy==true){
		for(int i=0;i<armia_barb.lucznicy;i++){
			if(zycie_lucznicy[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Lucznik Wroga #"<<i+1<<" ("<<zycie_lucznicy_barb[i]<<"/"<<obrona_lucznicy_barb[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Lucznik Wroga #"<<i+1<<" ("<<zycie_lucznicy_barb[i]<<"/"<<obrona_lucznicy_barb[i]<<")       "; 
			}else
			cout<<"                      ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(kusznicy==true){
		for(int i=0;i<armia_barb.kusznicy;i++){
			if(zycie_kusznicy_barb[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Kusznik Wroga #"<<i+1<<" ("<<zycie_kusznicy_barb[i]<<"/"<<obrona_kusznicy_barb[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Kusznik Wroga #"<<i+1<<" ("<<zycie_kusznicy_barb[i]<<"/"<<obrona_kusznicy_barb[i]<<")       "; 
			}else
			cout<<"                      ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(ciezkozbrojni==true){
		for(int i=0;i<armia_barb.ciezkozbrojni;i++){
			if(zycie_ciezkozbrojni_barb[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Ciezkozbrojny Wroga #"<<i+1<<" ("<<zycie_ciezkozbrojni_barb[i]<<"/"<<obrona_ciezkozbrojni_barb[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Ciezkozbrojny Wroga #"<<i+1<<" ("<<zycie_ciezkozbrojni_barb[i]<<"/"<<obrona_ciezkozbrojni_barb[i]<<")       "; 
			}else
			cout<<"                      ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(lekka_jazdy==true){
		for(int i=0;i<armia_barb.lekka_jazda;i++){
			if(zycie_lekka_jazda_barb[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Lekka Jazda Wroga #"<<i+1<<" ("<<zycie_lekka_jazda_barb[i]<<"/"<<obrona_lekka_jazda_barb[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Lekka Jazda Wroga #"<<i+1<<" ("<<zycie_lekka_jazda_barb[i]<<"/"<<obrona_lekka_jazda_barb[i]<<")       "; 
			}else
			cout<<"                      ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(ciezka_jazdy==true){
		for(int i=0;i<armia_barb.ciezka_jazda;i++){
			if(zycie_ciezka_jazda_barb[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Ciezka Jazda Wroga #"<<i+1<<" ("<<zycie_ciezka_jazda_barb[i]<<"/"<<obrona_ciezka_jazda_barb[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Ciezka Jazda Wroga #"<<i+1<<" ("<<zycie_ciezka_jazda_barb[i]<<"/"<<obrona_ciezka_jazda_barb[i]<<")       "; 
			}else
			cout<<"                      ";
			
			if(i%6==6)cout<< endl;
		}
	}
}
	////////////////////////////////////

	
		gotoxy(0,60);	
	if(pikinierzy==true&& atak==false){
		for(int i=0;i<armia.pikinierzy;i++){
			if(zycie_pikinierzy[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Pikinier #"<<i+1<<" ("<<zycie_pikinierzy[i]<<"/"<<obrona_pikinierzy[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Pikinier #"<<i+1<<" ("<<zycie_pikinierzy[i]<<"/"<<obrona_pikinierzy[i]<<")       "; 
			}else
			cout<<"        ------        ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(lucznicy==true&& atak==false){
		for(int i=0;i<armia.lucznicy;i++){
			if(zycie_lucznicy[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Lucznik #"<<i+1<<" ("<<zycie_lucznicy[i]<<"/"<<obrona_lucznicy[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Lucznik #"<<i+1<<" ("<<zycie_lucznicy[i]<<"/"<<obrona_lucznicy[i]<<")       "; 
			}else
			cout<<"       ------         ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(kusznicy==true&& atak==false){
		for(int i=0;i<armia.kusznicy;i++){
			if(zycie_kusznicy[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Kusznik #"<<i+1<<" ("<<zycie_kusznicy[i]<<"/"<<obrona_kusznicy[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Kusznik #"<<i+1<<" ("<<zycie_kusznicy[i]<<"/"<<obrona_kusznicy[i]<<")       "; 
			}else
			cout<<"      ------          ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(ciezkozbrojni==true&& atak==false){
		for(int i=0;i<armia.ciezkozbrojni;i++){
			if(zycie_ciezkozbrojni[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Ciezkozbrojny #"<<i+1<<" ("<<zycie_ciezkozbrojni[i]<<"/"<<obrona_ciezkozbrojni[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Ciezkozbrojny #"<<i+1<<" ("<<zycie_ciezkozbrojni[i]<<"/"<<obrona_ciezkozbrojni[i]<<")       "; 
			}else
			cout<<"       ------         ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(lekka_jazdy==true&& atak==false){
		for(int i=0;i<armia.lekka_jazda;i++){
			if(zycie_lekka_jazda[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Lekka Jazda #"<<i+1<<" ("<<zycie_lekka_jazda[i]<<"/"<<obrona_lekka_jazda[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Lekka Jazda #"<<i+1<<" ("<<zycie_lekka_jazda[i]<<"/"<<obrona_lekka_jazda[i]<<")       "; 
			}else
			cout<<"          ------      ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(ciezka_jazdy==true&& atak==false){
		for(int i=0;i<armia.ciezka_jazda;i++){
			if(zycie_ciezka_jazda[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Ciezka Jazda #"<<i+1<<" ("<<zycie_ciezka_jazda[i]<<"/"<<obrona_ciezka_jazda[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Ciezka Jazda #"<<i+1<<" ("<<zycie_ciezka_jazda[i]<<"/"<<obrona_ciezka_jazda[i]<<")       "; 
			}else
			cout<<"        ------        ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(tarany==true&& atak==false){
		for(int i=0;i<armia.tarany;i++){
			if(zycie_tarany[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Taran #"<<i+1<<" ("<<zycie_tarany[i]<<"/"<<obrona_tarany[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Taran #"<<i+1<<" ("<<zycie_tarany[i]<<"/"<<obrona_tarany[i]<<")       "; 
			}else
			cout<<"        ------        ";
			
			if(i%6==6)cout<< endl;
		}
	}
		gotoxy(0,60);	
	if(elity==true && atak==false){
		for(int i=0;i<armia.elity;i++){
			if(zycie_elity[i]>0){
			
			if(i==x2){
				SetConsoleTextAttribute( hOut, 2 );
				cout<<"Elita #"<<i+1<<" ("<<zycie_elity[i]<<"/"<<obrona_elity[i]<<")       "; 
				SetConsoleTextAttribute( hOut, 8 );
			}else
			cout<<"Elita #"<<i+1<<" ("<<zycie_elity[i]<<"/"<<obrona_elity[i]<<")       "; 
			}else
			cout<<"        ------        ";
			
			if(i%6==6)cout<< endl;
		}
	}
		
		
		
	ster=getch();
	
	
	if(ster==KEY_DOWN && x0!=7 && menu==true){
	x0++;
	cls();
	continue;
	}
	if(ster==KEY_UP && x0!=0 && menu==true){
	x0--;
	cls();
	continue;
	}	
	
	if(ster==KEY_DOWN && x1!=5 && atak==true && atak1==false){
	x1++;
	cls();
	continue;
	}
	if(ster==KEY_UP && x1!=0 && atak==true && atak1==false){
	x1--;
	cls();
	continue;
	}	
	///////////////////////////////
	if(ster==KEY_DOWN && x2!=armia.pikinierzy-1 && pikinierzy==true && atak==false){
	x2++;
	cls();
	
	}
	if(ster==KEY_UP && x2!=0){
	x2--;
	cls();
	
	}	
		if(ster==KEY_DOWN && x2!=armia.lucznicy-1 && lucznicy==true && atak==false){
	x2++;
	cls();
	
	}
	
	if(ster==KEY_DOWN && x2!=armia.kusznicy-1 && kusznicy==true && atak==false){
	x2++;
	cls();
	
	}

	if(ster==KEY_DOWN && x2!=armia.ciezkozbrojni-1 && ciezkozbrojni==true && atak==false){
	x2++;
	cls();
	
	}

	if(ster==KEY_DOWN && x2!=armia.lekka_jazda-1 && lekka_jazdy==true && atak==false){
	x2++;
	cls();
	
	}

	if(ster==KEY_DOWN && x2!=armia.ciezka_jazda-1 && ciezka_jazdy==true && atak==false){
	x2++;
	cls();
	
	}

	if(ster==KEY_DOWN && x2!=armia.tarany-1 && tarany==true && atak==false){
	x2++;
	cls();
	
	}
	if(ster==KEY_DOWN && x2!=armia.elity-1 && elity==true && atak==false){
	x2++;
	cls();
	
	}
	/////////////////////////
	if(ster==KEY_DOWN && x2!=armia_barb.pikinierzy-1 && pikinierzy==true && atak==true){
	x2++;
	cls();
	
	}

		if(ster==KEY_DOWN && x2!=armia_barb.lucznicy-1 && lucznicy==true && atak==true){
	x2++;
	cls();
	
	}
	
	if(ster==KEY_DOWN && x2!=armia_barb.kusznicy-1 && kusznicy==true && atak==true){
	x2++;
	cls();
	
	}

	if(ster==KEY_DOWN && x2!=armia_barb.ciezkozbrojni-1 && ciezkozbrojni==true && atak==true){
	x2++;
	cls();
	
	}

	if(ster==KEY_DOWN && x2!=armia_barb.lekka_jazda-1 && lekka_jazdy==true && atak==true){
	x2++;
	cls();
	
	}

	if(ster==KEY_DOWN && x2!=armia_barb.ciezka_jazda-1 && ciezka_jazdy==true && atak==true){
	x2++;
	cls();
	
	}
		if(armia_barb.wielkosc<1){
		break;
		wygrana=true;
		
		}
		
		if(armia.wielkosc<1){
		break;
		wygrana=false;
		
		}

	if(ster==27 && menu==false){
		menu=true;
		atak=false;
		elity=false;
		tarany=false;
		ciezka_jazdy=false;
		lekka_jazdy=false;
		ciezkozbrojni=false;
		kusznicy=false;
		lucznicy=false;
		pikinierzy=false;
		x0=0;
		x1=0;
		x2=0;
		system("CLS");
	}
	if(ster=='m')return;
	if(ster=='q' && x0==0 && atak==false && armia.pikinierzy>0&& pikinierzy==false){
		menu=false;
		pikinierzy=true;
		continue;
	}	
		if(ster=='q' && x0==1&& atak==false && armia.lucznicy>0&& lucznicy==false){
		menu=false;
		lucznicy=true;
		continue;
	}	
		if(ster=='q' && x0==2&& atak==false && armia.kusznicy>0&&kusznicy==false){
		menu=false;
		kusznicy=true;
		continue;
	}	
		if(ster=='q' && x0==3&& atak==false && armia.ciezkozbrojni>0&&ciezkozbrojni==false){
		menu=false;
		ciezkozbrojni=true;
		continue;
	}	
		if(ster=='q' && x0==4&& atak==false && armia.lekka_jazda>0&&lekka_jazdy==false){
		menu=false;
		lekka_jazdy=true;
		continue;
	}	
		if(ster=='q' && x0==5&& atak==false && armia.ciezka_jazda>0&&ciezka_jazdy==false){
		menu=false;
		ciezka_jazdy=true;
		continue;
	}	
		if(ster=='q' && x0==6&& atak==false && armia.tarany>0&&tarany==false){
		menu=false;
		tarany=true;
		continue;
	}	
		if(ster=='q' && x0==7&& atak==false && armia.elity>0&&elity==false){
		menu=false;
		elity=true;
		continue;
	}	
	
	//////////////////////
	if(ster=='q' && x1==0 && atak==true&& armia_barb.pikinierzy>0 && pikinierzy==false){
		menu=false;
		x2=0;
		atak1=true;
		pikinierzy=true;
		komunikat="Wybierz jednostke wroga";
		system("CLS");
		continue;
	}	
		if(ster=='q' && x1==1&& atak==true && armia_barb.lucznicy>0 && lucznicy==false){
		menu=false;
		atak1=true;
		x2=0;
		lucznicy=true;
		komunikat="Wybierz jednostke wroga";
		system("CLS");
		continue;
	}	
		if(ster=='q' && x1==2 && atak==true&& armia_barb.kusznicy>0&&kusznicy==false){
		menu=false;
		atak1=true;
		x2=0;
		kusznicy=true;
		komunikat="Wybierz jednostke wroga";
		system("CLS");
		continue;
	}	
		if(ster=='q' && x1==3&& atak==true && armia_barb.ciezkozbrojni>0&&ciezkozbrojni==false){
		menu=false;
		atak1=true;
		x2=0;
		ciezkozbrojni=true;
		komunikat="Wybierz jednostke wroga";
		system("CLS");
		continue;
	}	
		if(ster=='q' && x1==4&& atak==true && armia_barb.lekka_jazda>0&&lekka_jazdy==false){
		menu=false;
		atak1=true;
		lekka_jazdy=true;
		x2=0;
		komunikat="Wybierz jednostke wroga";
		system("CLS");
		continue;
	}	
		if(ster=='q' && x1==5 && atak==true&& armia_barb.ciezka_jazda>0&&ciezka_jazdy==false){
		menu=false;
		atak1=true;
		ciezka_jazdy=true;
		x2=0;
		komunikat="Wybierz jednostke wroga";
		system("CLS");
		continue;
	}	

		if(ster=='q' && pikinierzy==true&& atak==false && zycie_pikinierzy[x2]>0){
			komunikat="Wybierz cel ataku";
			atak=true;
			pikinierzy=false;
			identyfikator_gracz=x2;
			x1=0;
		}
				if(ster=='q' && lucznicy==true&& atak==false && zycie_lucznicy[x2]>0){
			komunikat="Wybierz cel ataku";
			atak=true;
			lucznicy=false;
			identyfikator_gracz=x2;
			x1=0;
		}
				if(ster=='q' && kusznicy==true&& atak==false && zycie_kusznicy[x2]>0){
			komunikat="Wybierz cel ataku";
			atak=true;
			kusznicy=false;
			identyfikator_gracz=x2;
			x1=0;
		}
				if(ster=='q' && ciezkozbrojni==true&& atak==false && zycie_ciezkozbrojni[x2]>0){
			komunikat="Wybierz cel ataku";
			atak=true;
			ciezkozbrojni=false;
			identyfikator_gracz=x2;
			x1=0;
		}
				if(ster=='q' && lekka_jazdy==true&& atak==false && zycie_lekka_jazda[x2]>0){
			komunikat="Wybierz cel ataku";
			atak=true;
			lekka_jazdy=false;
			identyfikator_gracz=x2;
			x1=0;
		}
				if(ster=='q' && ciezka_jazdy==true&& atak==false && zycie_ciezka_jazda[x2]>0){
			komunikat="Wybierz cel ataku";
			atak=true;
			ciezka_jazdy=false;
			identyfikator_gracz=x2;
			x1=0;
		}
				if(ster=='q' && tarany==true&& atak==false && zycie_tarany[x2]>0){
			komunikat="Wybierz cel ataku";
			atak=true;
			tarany=false;
			identyfikator_gracz=x2;
			x1=0;
		}
				if(ster=='q' && elity==true&& atak==false && zycie_elity[x2]>0){
			komunikat="Wybierz cel ataku";
			atak=true;
			elity=false;
			identyfikator_gracz=x2;
			x1=0;
		}
////////////////////////////////
		if(ster=='q' && pikinierzy==true&& atak1==true && zycie_pikinierzy_barb[x2]>0){
			komunikat="Atak w toku";
			if(x0==0){
			gotoxy(30,25);
			cout << identyfikator_nazwy[x0]<<" ("<<zycie_pikinierzy[identyfikator_gracz]<<"/"<<obrona_pikinierzy[identyfikator_gracz]<<")     VS    "<<"Pikinier ("<<zycie_pikinierzy_barb[x2]<<"/"<<obrona_pikinierzy_barb[x2]<<")";
			gotoxy(30,27);
			if(obrona_pikinierzy_barb[x2]<=0){
			atak_bufor=pikinier[miasto_domowe].atak-abs(obrona_pikinierzy_barb[x2]);
			zycie_pikinierzy_barb[x2]-=atak_bufor;
			}else
			atak_bufor=0;
			atak_bufor_obrona=0;
			if(obrona_pikinierzy_barb[x2]>0){
			atak_bufor_obrona=pikinier[miasto_domowe].atak;
			obrona_pikinierzy_barb[x2]-=atak_bufor_obrona;
			}

			
			Sleep(500);
			cout << "Zadajesz barbarzyncom "<<pikinier[miasto_domowe].atak <<" punktow obrazen ("<<atak_bufor<<"/"<<atak_bufor_obrona<<")";
				if(obrona_pikinierzy_barb[x2]<0){
				obrona_pikinierzy_barb[x2]=0;
			}
			
			gotoxy(30,28);
			if(zycie_pikinierzy_barb[x2]<=0){
				cout<<"Zabijasz wrogiego pikiniera";
				armia_barb.wielkosc-=pikinier[11].wielkosc;
				armia_barb.pikinierzy--;
			}
			Sleep(500);
			gotoxy(30,29);
			if(zycie_pikinierzy_barb[x2]>0){
			
			if(obrona_pikinierzy[identyfikator_gracz]<=0){
			atak_bufor=pikinier[11].obrona-abs(obrona_pikinierzy[identyfikator_gracz]);
			zycie_pikinierzy[identyfikator_gracz]-=atak_bufor;
			}else
			atak_bufor=0;
			atak_bufor_obrona=0;
			if(obrona_pikinierzy[identyfikator_gracz]>0){
			atak_bufor_obrona=pikinier[1].obrona;
			obrona_pikinierzy[identyfikator_gracz]-=atak_bufor_obrona;
			}
			
			cout << "Zadaja ci "<<pikinier[11].obrona <<" punktow obrazen ("<<atak_bufor<<"/"<<atak_bufor_obrona<<")";
			gotoxy(30,28);
			if(zycie_pikinierzy[identyfikator_gracz]<=0){
				cout<<"Zabijaja Ci pikiniera moj Panie";
				armia.wielkosc-=pikinier[miasto_domowe].wielkosc;
				armia.pikinierzy--;
			}
			}
			}
			getch();
			pikinierzy=false;
			atak1=false;
			atak=false;
			menu=true;
			x0=0;
			x2=-1;
			x1=0;
			system("CLS");
		}
		if(ster=='q' && lucznicy==true&& atak1==true && zycie_lucznicy_barb[x2]>0){
			komunikat="Atak w toku";
			atak=true;
			lucznicy=false;
			identyfikator_gracz=x2;
			x1=0;
		}
		if(ster=='q' && kusznicy==true&& atak1==true && zycie_kusznicy_barb[x2]>0){
			komunikat="Atak w toku";
			atak=true;
			kusznicy=false;
			identyfikator_gracz=x2;
			x1=0;
		}
		if(ster=='q' && ciezkozbrojni==true&& atak1==true && zycie_ciezkozbrojni_barb[x2]>0){
			komunikat="Atak w toku";
			atak=true;
			ciezkozbrojni=false;
			identyfikator_gracz=x2;
			x1=0;
		}
		if(ster=='q' && lekka_jazdy==true&& atak1==true && zycie_lekka_jazda_barb[x2]>0){
			komunikat="Atak w toku";
			atak=true;
			lekka_jazdy=false;
			identyfikator_gracz=x2;
			x1=0;
		}
		if(ster=='q' && ciezka_jazdy==true&& atak1==true && zycie_ciezka_jazda_barb[x2]>0){
			komunikat="Atak w toku";
			atak=true;
			ciezka_jazdy=false;
			identyfikator_gracz=x2;
			x1=0;
		}


		
		
		
		
		
		
	}
	cout<< "KONIEC";
	return;
	
	
}


void walka_gracze(struktura_armii armia, char mapa_walki[49][73], string pre_walka[49]){
	bool koniec=false;
	bool gracz1;
	bool gracz2;
	int x;
	int y;
	
	
	 for(int i=0;i<49;i++){
	for(int j=0;j<73;j++){
		if(mapa_walki[i][j]==dom2){
			szansa=(rand()%100);
			if(szansa>90){
			mapa_walki[i][j]=dom;
			}
			if(szansa<10){
			mapa_walki[i][j]=gora;
			}
		}
	}
}
	
	while(koniec==false){
		
		
		for(int i=x-15;i<=x+15;i++){
	cout << "   ";
        for(int j=y-15;j<=y+15;j++){
        		if(j==(y+15) || i==(x+15) || j==(y-15) || i==(x-15))cout << blok;
        		else{
                if(i==x && j==y){
                        SetConsoleTextAttribute( hOut,  BACKGROUND_RED );
                        cout << mapa[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && budowa==true ||mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && ruch==true){
                        SetConsoleTextAttribute( hOut,  14 |BACKGROUND_GREEN );
                        cout << mapa_jednostek[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{	
                if(mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && budowa==true ||mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && ruch==true){
                        SetConsoleTextAttribute( hOut,  14 |BACKGROUND_GREEN );
                        cout << mapa_jednostek[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && budowa==true ||mapa_jednostek[i][j]!='B' && mapa_jednostek[i][j]!=' ' && ruch==true){
                        SetConsoleTextAttribute( hOut,  14 |BACKGROUND_GREEN );
                        cout << mapa_jednostek[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{

                        	
				if(mapa_jednostek[i][j]=='B'){
        			SetConsoleTextAttribute( hOut, 4 | BACKGROUND_GREEN );
        			cout << mapa_jednostek[i][j];
        			SetConsoleTextAttribute( hOut, 8 );
						}else{
				if(mapa_jednostek[i][j]!=' '){
        			SetConsoleTextAttribute( hOut, 12 | BACKGROUND_GREEN );
        			cout << mapa_jednostek[i][j];
        			SetConsoleTextAttribute( hOut, 8 );
						}else{
                if(mapa[i][j]==dom){
                                    SetConsoleTextAttribute( hOut, 2 );
                                    cout << mapa[i][j];
                                    SetConsoleTextAttribute( hOut, 8 );
                        }else{
                                    
                if(mapa[i][j]==dom2){
                                     SetConsoleTextAttribute( hOut, 10 );
                                    cout << mapa[i][j];
                                    SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa[i][j]==woda){
                                     SetConsoleTextAttribute( hOut, 9  );
                                    cout << mapa[i][j];
                                    SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa[i][j]==gora){
                                     SetConsoleTextAttribute( hOut, 7 | BACKGROUND_GREEN );
                                     cout << mapa[i][j];
                                     SetConsoleTextAttribute( hOut, 8 );
                        }else{

                cout << mapa[i][j];
                
                }
                }
            	}
                }
            	}
                }
            	}
            	}
            	}
            	}
            	}
			
                
        cout << endl;
        }
    	}
		
		
	}
	
	for(int i=0;i<49;i++){
		for(int j=0;j<73;j++){
		mapa_walki[i][j]=pre_walka[i][j];
		}
	}
}


///////////
	 int x0=0;
	 bool technologie;
	 ////////////
	 
	 
void odkryj( bool *nazwa, int koszt, int *nauka, string NazwaTechnologii){
			*nazwa=true;
			nauka=nauka-koszt;
			technologie=false;
			menu_stolica=true;
			gotoxy(54,25);
			for(int i=0;i<70;i++)cout << blok;
			gotoxy(54,26);
			cout << blok;
			for(int i=0;i<68;i++)cout<< " ";
			cout << blok;
			gotoxy(54,28);
			cout << blok;
			for(int i=0;i<68;i++)cout<< " ";
			cout << blok;
			gotoxy(54,29);
			for(int i=0;i<70;i++)cout << blok;
			gotoxy(120,27);
			cout << "   " << blok;
			gotoxy(54,27);
			cout <<blok<< " Okdryles " <<NazwaTechnologii<<"                                          ";
			Sleep(2000);
			x0=0;
}


int main(){

 int miasta[137][201];
 string jednostki[255];
 jednostki[osadnik]="osadnik";
 jednostki[82]="robotnik";
 string gracz1_nazwa="Kuba";
 string gracz2_nazwa;
 
 srand(time(NULL));
 
 ////technologie/////
 

 

 
 bool hodowla=false;
 bool waluta=false;
 bool gildie=false;
 bool mechanika=false;
 bool lowiectwo=false;
 bool infrastruktura=false;
 bool administracja=false;
 bool obrobka_zelaza=false;
 bool obrobka_stali=false;
 bool nawigacja=false;
 bool sztuka=false;
 bool hutnictwo=false;
 bool ewangelizacja=false;
 bool browarnictwo=false;
 int nastepna_tura_domyslnie=5;
 int nastepna_tura=5;

///////////////////////////////
 
 HANDLE wHnd; 
HANDLE rHnd; 
 

 int szansa_robert;
 int punkty=0;
 char bufor_poj;
 char bufor_multi[137][201];
int idmiasta;

 ifstream wczytaj;
 wczytaj.open("Assets/Maps/map_euro.txt");
 string pre_mapa[137];
 
 ifstream wczytaj_miasto;
 wczytaj_miasto.open("Assets/Maps/map_stolica.txt");
 string pre_miasto[80];
 
int drewno=1000;
int zloto=1000;
int kamien=1000;
int zywnosc=1000;
int wiara=0;
int max_zolnierzy=5;
int nauka=400;
int przychod_nauka=0;
int przychod_drewno=0;
int przychod_kamien=0;
int przychod_zywnosc=0;
int przychod_wiara=0;
int przychod_zloto=0;
int ludnosc=0;
int ksztalt=0;
int xm=0;

 int wybor_map=0;

 int xd=0;
 int yd=0;
 int liczba_miast=1;

int h=0;
string komunikat="Brak komunikatow moj Panie";
 
for(int i=1;i<11;i++)miasto[i].podatek=100;
 
 int x=102;
 int l_robert=0;
 int y=63;

 int e=1;
 hOut = GetStdHandle( STD_OUTPUT_HANDLE );
 char ster;
 

 	ifstream wczytaj_budynek;
 	wczytaj_budynek.open("Assets/Buildings/akademia.txt" );
 	string pre[9];
 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		akademia.wyglad[i][j]=pre[i][j];
		}
	}
wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/kapitol.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		kapitol.wyglad[i][j]=pre[i][j];

		}

	}

wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/ratusz.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		ratusz.wyglad[i][j]=pre[i][j];
		}
	}
 
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/rynek.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		rynek.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/mieszkalna.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		mieszkalna.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/handlowa.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		handlowa.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/naukowa.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		naukowa.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/wojskowa.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		wojskowa.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/religijna.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		religijna.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	 	wczytaj_budynek.open("Assets/Buildings/rekreacyjna.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		rekreacyjna.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	 	wczytaj_budynek.open("Assets/Buildings/koszary.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		koszary.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/szkola.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		szkola.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/huta.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		huta.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/oboz.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		oboz.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/bank.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		bank.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/gildia.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		gildia.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/biblioteka.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		biblioteka.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/park.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		park.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/pomnik.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		pomnik.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/ambasada.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		ambasada.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/port.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		port.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/teatr.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		teatr.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/tawerna.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		tawerna.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/magazyn.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		magazyn.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/mlyn.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		mlyn.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/plac.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		plac.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/akademia.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		akademia.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/tartak.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		tartakb.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/kamieniarz.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		kamieniarz.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/kolos.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		kolos.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/kosciol.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		kosciol.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/katedra.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		katedra.wyglad[i][j]=pre[i][j];
		}
 }
 wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/skarbiec.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		skarbiec.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/fort.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		fort.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/weglarnia.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		weglarnia.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/warsztat.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		warsztat.wyglad[i][j]=pre[i][j];
		}
	}
 	wczytaj_budynek.close();
 	wczytaj_budynek.open("Assets/Buildings/stajnia.txt" );

 
 for(int i=0;i<9;i++){
	getline(wczytaj_budynek, pre[i]);
}
for(int i=0;i<9;i++){
	for(int j=0;j<21;j++){
		stajnia.wyglad[i][j]=pre[i][j];
		}
	}


 for(int i=0;i<10;i++){
	miasto[i].x1=60;
	miasto[i].y1=60;
}
 
  /* Window size coordinates, be sure to start index at zero! */
  SMALL_RECT windowSize = {0, 0, 800, 600};

  /* A COORD struct for specificying the console's screen buffer dimensions */
  COORD bufferSize = {220, 75};
  wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
  rHnd = GetStdHandle(STD_INPUT_HANDLE);
  SetConsoleTitle("Plemiona!");
  SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
  SetConsoleScreenBufferSize(wHnd, bufferSize);


for(int i=0;i<137;i++){
	getline(wczytaj, pre_mapa[i]);
}

for(int i=0;i<80;i++){
	getline(wczytaj_miasto, pre_miasto[i]);
}

wczytaj.close();
 wczytaj.open("Assets/Maps/map_attack.txt");
 string pre_walka[49];

for(int i=0;i<49;i++){
	getline(wczytaj, pre_walka[i]);
}
 
 
 for(int i=0;i<49;i++){
	for(int j=0;j<73;j++){
		mapa_walki[i][j]=pre_walka[i][j];
		cout << endl;
	}
}
 
for(int i=0;i<137;i++){
	for(int j=0;j<201;j++){
		mapa[i][j]=pre_mapa[i][j];
		if(mapa[i][j]==dom2){
			szansa=(rand()%100);
			if(szansa>70){
			mapa[i][j]=dom;
			}
		}
		cout << endl;
	}
}

for(int i=0;i<80;i++){
	for(int j=0;j<150;j++){
		mapa_stolicy[i][j]=pre_miasto[i][j];
		if(mapa_stolicy[i][j]==dom2){
			szansa=(rand()%100);
			if(szansa>70){
			mapa_stolicy[i][j]=dom;
			}
		}
		cout << endl;
	}
}

for(int i=0;i<137;i++){
	for(int j=0;j<201;j++){
		bufor_multi[i][j]=mapa[i][j];
	}
}

for(int i=0;i<80;i++){
	for(int j=0;j<150;j++){
		bufor_miasta[i][j]=mapa_stolicy[i][j];
	}
}

for(int i=0;i<137;i++){
	for(int j=0;j<201;j++){
		if(mapa[i][j]==dom || mapa[i][j]==dom2)
		zasieg_miast[i][j]='0';
	}
}

for(int i=0;i<137;i++){
	for(int j=0;j<201;j++){
		if(mapa[i][j]==dom || mapa[i][j]==dom2)
		teretorium[i][j]='x';
	}
}
for(int i=0;i<137;i++){
	for(int j=0;j<201;j++){
		if(mapa[i][j]==dom || mapa[i][j]==dom2)
		mapa_armii[i][j]='0';
	}
}
for(int i=0;i<137;i++){
	for(int j=0;j<201;j++){
		mapa_jednostek[i][j]=' ';
	}
}

struktura_budowli_osada aktualna;

wczytaj.close();
wczytaj_miasto.close();
 mapa_jednostek[107][64]=osadnik;
 mapa_jednostek[101][64]=robotnik;
 mapa_jednostek[102][64]=robotnik;
 mapa_jednostek[103][61]=osadnik;
 
miasto[1].produkcja=1000;

do{
	gotoxy(50,50);
cout << "Tura Gracza "<<gracz1_nazwa<<", wcisnij cokolwiek aby kontynuowac";
getch();
system("CLS");
while(gracz1==true){

	

while(mapa_glowna==true){
	h=0;
	przychod_zloto=0;
	przychod_drewno=0;
	przychod_kamien=0;
	przychod_zywnosc=0;
	przychod_wiara=0;
	przychod_nauka=0;
	
	////mgla wojny////

		for(int i=0;i<127;i++){
		for(int j=0;j<201;j++){
			niewidocznosc[i][j]=false;
			
		}
	}
		for(int i=0;i<137;i++){
		for(int j=0;j<201;j++){
			if((mapa_jednostek[i][j]!=' '&& mapa_jednostek[i][j]!='B') || (mapa[i][j]==stolica || mapa[i][j]==osada)){
				for(int p=i-4;p<=i+4;p++){
					for(int o=j-4;o<=j+4;o++){
						mgla_wojny[p][o]=true;
						bufor_widocznosci[p][o]=mapa[p][o];
					}
				}
			}
		}
	}
	for(int i=0;i<137;i++){
		for(int j=0;j<201;j++){
			if((mapa_jednostek[i][j]!=' ' && mapa_jednostek[i][j]!='B') && mgla_wojny[i][j]==true || (mapa[i][j]==stolica || mapa[i][j]==osada) && mgla_wojny[i][j]==true){
				for(int p=i-4;p<=i+4;p++){
					for(int o=j-4;o<=j+4;o++){
						niewidocznosc[p][o]=true;
					}
				}
			}
		}
	}

	for(int i=1;i<11;i++)przychod_zloto=przychod_zloto+miasto[i].przychod_zloto;
	if(waluta==true)przychod_zloto=przychod_zloto*1.25;
	for(int i=0;i<137;i++){
		for(int j=0;j<201;j++){
			if(mapa_armii[i][j]>0){
				przychod_zloto-+armia[mapa_armii[i][j]].utrzymanie;
			}
		}
	}
	for(int i=1;i<11;i++)przychod_drewno=przychod_drewno+miasto[i].przychod_drewno;
	for(int i=1;i<11;i++)przychod_kamien=przychod_kamien+miasto[i].przychod_kamien;
	if(huta.lvl>=1)przychod_kamien=przychod_kamien+przychod_kamien*0.3;
	for(int i=1;i<11;i++)przychod_zywnosc=przychod_zywnosc+miasto[i].przychod_zywnosc;
	if(hodowla==true)przychod_zywnosc=przychod_zywnosc*1.25;
	for(int i=1;i<11;i++)miasto[i].przychod_zywnosc=miasto[i].przychod_zywnosc-ludnosc*0.0005;
	for(int i=1;i<11;i++)przychod_wiara=przychod_wiara+miasto[i].przychod_wiara;
	if(ewangelizacja==true)przychod_wiara=przychod_wiara*1.25;
	for(int i=1;i<11;i++)przychod_nauka=przychod_nauka+miasto[i].przychod_nauka;
	if(gildie==true)przychod_nauka=przychod_nauka*1.25;
	
         cls();
         
 
         
         cout << endl <<"              MAPA SWIATA"<< endl << endl;
        if(wybor_map==0){
		
for(int i=x-19;i<=x+19;i++){
	cout << "   ";
        for(int j=y-19;j<=y+19;j++){
        		if(j==(y+19) || i==(x+19) || j==(y-19) || i==(x-19))cout << blok;
        		else{
        		if(mgla_wojny[i][j]==false)cout<<" ";
        		else{
        		if(niewidocznosc[i][j]==false){
        			    if(mapa[i][j]==woda){
                         SetConsoleTextAttribute( hOut, 9  );
                    	cout << mapa[i][j];
                    	SetConsoleTextAttribute( hOut, 8 );
                        }else{
						
        		    SetConsoleTextAttribute( hOut, 8 | BACKGROUND_GREEN );
        			cout << bufor_widocznosci[i][j];
        			SetConsoleTextAttribute( hOut, 8 );	
        			}
				}else{
				
        		if(mapa[i][j]==stolica){
        			SetConsoleTextAttribute( hOut, 4 | BACKGROUND_GREEN );
        			cout << mapa[i][j];
        			SetConsoleTextAttribute( hOut, 8 );
						}else{
				if(mapa[i][j]==osada){
                        SetConsoleTextAttribute( hOut,  4 |BACKGROUND_GREEN );
                        cout << mapa[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{
				if(mapa[i][j]==farma){
                        SetConsoleTextAttribute( hOut,  14 );
                        cout << mapa[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{
				if(mapa[i][j]==kopalnia){
                        SetConsoleTextAttribute( hOut,  5  | BACKGROUND_GREEN);
                        cout << mapa[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{
				if(mapa[i][j]==tartak){
                        SetConsoleTextAttribute( hOut,  5 |BACKGROUND_GREEN );
                        cout << mapa[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{       
				if(mapa[i][j]==wioska){
                        SetConsoleTextAttribute( hOut,  5 |BACKGROUND_GREEN );
                        cout << mapa[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{                   	
                if(i==x && j==y){
                        SetConsoleTextAttribute( hOut,  BACKGROUND_RED );
                        cout << mapa[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && budowa==true ||mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && ruch==true){
                        SetConsoleTextAttribute( hOut,  14 |BACKGROUND_GREEN );
                        cout << mapa_jednostek[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{	
                if(mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && budowa==true ||mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && ruch==true){
                        SetConsoleTextAttribute( hOut,  14 |BACKGROUND_GREEN );
                        cout << mapa_jednostek[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa_jednostek[i][j]!='B' &&mapa_jednostek[i][j]!=' ' && budowa==true ||mapa_jednostek[i][j]!='B' && mapa_jednostek[i][j]!=' ' && ruch==true){
                        SetConsoleTextAttribute( hOut,  14 |BACKGROUND_GREEN );
                        cout << mapa_jednostek[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{

                        	
				if(mapa_jednostek[i][j]=='B'){
        			SetConsoleTextAttribute( hOut, 4 | BACKGROUND_GREEN );
        			cout << mapa_jednostek[i][j];
        			SetConsoleTextAttribute( hOut, 8 );
						}else{
				if(mapa_jednostek[i][j]!=' '){
        			SetConsoleTextAttribute( hOut, 12 | BACKGROUND_GREEN );
        			cout << mapa_jednostek[i][j];
        			SetConsoleTextAttribute( hOut, 8 );
						}else{
                if(mapa[i][j]==dom){
                                    SetConsoleTextAttribute( hOut, 2 );
                                    cout << mapa[i][j];
                                    SetConsoleTextAttribute( hOut, 8 );
                        }else{
                                    
                if(mapa[i][j]==dom2){
                                     SetConsoleTextAttribute( hOut, 10 );
                                    cout << mapa[i][j];
                                    SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa[i][j]==woda){
                                     SetConsoleTextAttribute( hOut, 9  );
                                    cout << mapa[i][j];
                                    SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa[i][j]==gora){
                                     SetConsoleTextAttribute( hOut, 7 | BACKGROUND_GREEN );
                                     cout << mapa[i][j];
                                     SetConsoleTextAttribute( hOut, 8 );
                        }else{

                cout << mapa[i][j];
                
                }
                }
            	}
                }
            	}
            	}
            	}
                }
            	}
            	}
            	}
            	}
            	}
            	}
                }
            	}
            	}
            	}
                }
            	}
			
                
        cout << endl;
        }
    	}
    	
    	
    	
    if(wybor_map==1){
    	for(int i=x-19;i<=x+19;i++){
	cout << "   ";
        for(int j=y-19;j<=y+19;j++){
        		if(j==(y+19) || i==(x+19) || j==(y-19) || i==(x-19))cout << blok;
        		else{
				if(i==x && j==y){
                        SetConsoleTextAttribute( hOut,  BACKGROUND_RED );
                        cout << mapa[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
        		}else{
        			cout << zasieg_miast[i][j];
            	}
		}
     	}
        cout << endl;
        }
    	}
    	
    	    if(wybor_map==2){
    	for(int i=x-19;i<=x+19;i++){
	cout << "   ";
        for(int j=y-19;j<=y+19;j++){
        		if(j==(y+19) || i==(x+19) || j==(y-19) || i==(x-19))cout << blok;
        		else{
				if(i==x && j==y){
                        SetConsoleTextAttribute( hOut,  BACKGROUND_RED );
                        cout << mapa[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
        		}else{
        			if(teretorium[i][j]=='1'){
        				SetConsoleTextAttribute( hOut, 12  );
        				cout << teretorium[i][j];
        				SetConsoleTextAttribute( hOut, 8 );
					}else{
						if(teretorium[i][j]=='2'){
						SetConsoleTextAttribute( hOut, 9  );	
						cout << teretorium[i][j];
        				SetConsoleTextAttribute( hOut, 8 );
						}else
        			cout << teretorium[i][j];
            	}
		}
     	}
     	}
        cout << endl;
        
    	}
	}
	
	if(wybor_map==3){
    	for(int i=x-19;i<=x+19;i++){
	cout << "   ";
        for(int j=y-19;j<=y+19;j++){
        		if(j==(y+19) || i==(x+19) || j==(y-19) || i==(x-19))cout << blok;
        		else{
				if(i==x && j==y){
                        SetConsoleTextAttribute( hOut,  BACKGROUND_RED );
                        cout << mapa_armii[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
        		}else{
        			if(mapa_armii[i][j]!='0'){
        				SetConsoleTextAttribute( hOut, 12  );
        				cout << mapa_armii[i][j];
        				SetConsoleTextAttribute( hOut, 8 );
					}else
        			cout << mapa_armii[i][j];

		}
     	}
     	}
        cout << endl;
        
    	}
	}
    	
        cout << endl;
cout << "( " << y <<" , "<<x<<" )   "; 
if(miasta[x][y]>=1)cout << miasto[miasta[x][y]].nazwa;
if(mapa_armii[x][y]>48)cout << armia[mapa_armii[x][y]-48].nazwa;

if(mapa_tartak[x][y]>=1)cout << "Tartak miasta " << miasto[mapa_tartak[x][y]].nazwa;
if(mapa_kopalnia[x][y]>=1)cout << "Kopalnia miasta " << miasto[mapa_kopalnia[x][y]].nazwa;
if(mapa_farma[x][y]>=1)cout << "Farma miasta " << miasto[mapa_farma[x][y]].nazwa;
if(mapa_farma[x][y]==0)cout << "                          ";
if(mapa_wioska[x][y]>=1)cout << "Wioska miasta " << miasto[mapa_wioska[x][y]].nazwa;
if(mapa_wioska[x][y]==0)cout << "                          ";
if(mapa_jednostek[x][y]=='B')cout << "Barbarzyncy " << miasto[mapa_wioska[x][y]].nazwa;
if(mapa_jednostek[x][y]!='B')cout << "                          ";
if(mapa_kopalnia[x][y]==0)cout << "                          ";
if(mapa_tartak[x][y]==0)cout << "                          ";
if(miasta[x][y]==0)cout << "                          ";
gotoxy(54,1);
cout << "KOMUNIKATY";
gotoxy(44,3);
for(int i=0;i<komunikat.size()/7;i++){
	
	for(int j=0;j<30;j++){
		if(j==0 || i==0 || j==29 || i==(komunikat.size()/7-1))cout << blok;
		else{
		if(h<komunikat.size()){
		
		cout << komunikat[h];
		h++;
	}else
	cout << " ";
		
	}
	}
	gotoxy(44,4+i);
}
gotoxy(8,48);
cout << "Pozostalo ruchow: "<<nastepna_tura << " z " << nastepna_tura_domyslnie;
gotoxy(110,4);
 cout << "    BUDOWA " << budowa << "    WYBOR JEDNOSTKI " << wybor_jednostki <<"    MENU " << menu << "     MENU BUDOWY " << menu_budowy << "   Liczba miast "<<liczba_miast << " ilosc barbow "<<ilosc_barbarzyncow;
if(wybor_jednostki==true){
	gotoxy(110,5);
	if(mapa_jednostek[x][y]!='A')
	cout << "Wybrano: " << jednostki[mapa_jednostek[x][y]];
	else
	cout << "Wybrano: " << armia[mapa_armii[x][y]-48].nazwa;
}
SetConsoleTextAttribute( hOut, 10 );
gotoxy(8,50);
cout << "Zywnosc: "<< zywnosc<<"("<<przychod_zywnosc<<")" <<"  Drewno: " << drewno <<"("<<przychod_drewno<<")"<< "  Kamien: " << kamien<<"("<<przychod_kamien<<")"<< "  Wiara: " << wiara<<"("<<przychod_wiara<<")" << "  Max. Zolnierzy: " << max_zolnierzy<<"("<<liczba_zolnierzy<<")" << "  Zloto: " << zloto <<"("<<przychod_zloto<<")"<< "  Nauka: "<<nauka<<"("<<przychod_nauka<<")";
SetConsoleTextAttribute( hOut, 8 );

if(menu==true){


gotoxy(86,1);
cout << "MENU";
gotoxy(76,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(76,4);
cout <<blok<< "                          "<<blok;
gotoxy(76,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Powrot do stolicy      "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout << blok<<"   Powrot do stolicy      "<<blok; 
gotoxy(76,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout << "   Lista Miast            "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout <<blok<< "   Lista Miast            "<<blok; 
gotoxy(76,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Dzialania jednostki    "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Dzialania jednostki    "<<blok; 
gotoxy(76,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Nestepna Tura          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Nastepna Tura          "<<blok; 
gotoxy(76,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Anuluj                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Anuluj                 "<<blok; 
gotoxy(76,10);
cout <<blok<< "                          "<<blok;
gotoxy(76,11);
for(int i=0;i<28;i++)cout << blok;
}

if(menu==false && menu_budowy==false && wybor_jednostki==true){


gotoxy(81,1);
cout << "DZIALNIA JEDNOSTKI";
gotoxy(76,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(76,4);
cout <<blok<< "                          "<<blok;
gotoxy(76,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Ruch                   "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout << blok<<"   Ruch                   "<<blok; 
gotoxy(76,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout << "   Atakuj                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout <<blok<< "   Atakuj                 "<<blok; 
gotoxy(76,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Buduj                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Buduj                  "<<blok; 

gotoxy(76,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Powrot                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Powrot                 "<<blok; 

gotoxy(76,9);
cout <<blok<< "                          "<<blok;
gotoxy(76,10);
for(int i=0;i<28;i++)cout << blok;
}

if(nazwa==true){
	gotoxy(54,25);
	for(int i=0;i<40;i++)cout << blok;
	gotoxy(54,26);
	cout << blok;
	for(int i=0;i<38;i++)cout<< " ";
	cout << blok;
	gotoxy(54,28);
	cout << blok;
	for(int i=0;i<38;i++)cout<< " ";
	cout << blok;
	gotoxy(54,29);
	for(int i=0;i<40;i++)cout << blok;
	gotoxy(90,27);
	cout << "   " << blok;
	gotoxy(54,27);
	cout <<blok<< "  Wpisz nazwe miasta: ";
	getline(cin, miasto[liczba_miast-1].nazwa);

	gotoxy(54,27);
	for(int i=0;i<28;i++)cout << blok;
	nazwa=false;
	system("CLS");
	continue;
}


if(menu_budowy==true && mapa_jednostek[x][y]=='R'){
gotoxy(81,1);
cout << "BUDOWA                    ";
gotoxy(76,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(76,4);
cout <<blok<< "                          "<<blok;
gotoxy(76,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Farma                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout << blok<<"   Farma                  "<<blok; 
gotoxy(76,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout << "   Kopalnia               "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout <<blok<< "   Kopalnia               "<<blok; 
gotoxy(76,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Tartak                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Tartak                 "<<blok; 
gotoxy(76,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Wioska                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Wioska                 "<<blok; 

gotoxy(76,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Anuluj                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Anuluj                 "<<blok; 

gotoxy(76,10);
cout <<blok<< "                          "<<blok;
gotoxy(76,11);
for(int i=0;i<28;i++)cout << blok;

}
	
	
	
	if(lista_miast==true){
	
	
gotoxy(75,1);
cout << "        LISTA MIAST      ";
gotoxy(76,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(76,4);
cout <<blok<< "                          "<<blok;
gotoxy(76,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<miasto[1].nazwa; 
for(int i=miasto[1].nazwa.size();i<26;i++)cout << " ";
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else{

cout << blok<<miasto[1].nazwa;
for(int i=miasto[1].nazwa.size();i<26;i++)cout << " ";
cout<<blok; }
gotoxy(76,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<miasto[2].nazwa; 
for(int i=miasto[2].nazwa.size();i<26;i++)cout << " ";
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else{

cout <<blok<<miasto[2].nazwa;
for(int i=miasto[2].nazwa.size();i<26;i++)cout << " ";
cout<<blok; }
gotoxy(76,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<miasto[3].nazwa; 
for(int i=miasto[3].nazwa.size();i<26;i++)cout << " ";
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{

cout <<blok<<miasto[3].nazwa;
for(int i=miasto[3].nazwa.size();i<26;i++)cout << " ";
cout<<blok;  }
gotoxy(76,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<miasto[4].nazwa; 
for(int i=miasto[4].nazwa.size();i<26;i++)cout << " ";
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{

cout <<blok<<miasto[4].nazwa;
for(int i=miasto[4].nazwa.size();i<26;i++)cout << " ";
cout<<blok; }
gotoxy(76,9);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<miasto[5].nazwa; 
for(int i=miasto[5].nazwa.size();i<26;i++)cout << " ";
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{

cout <<blok<<miasto[5].nazwa;
for(int i=miasto[5].nazwa.size();i<26;i++)cout << " ";
cout<<blok; }
gotoxy(76,10);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<miasto[6].nazwa; 
for(int i=miasto[6].nazwa.size();i<26;i++)cout << " ";
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{

cout <<blok<<miasto[6].nazwa;
for(int i=miasto[6].nazwa.size();i<26;i++)cout << " ";
cout<<blok; }
gotoxy(76,11);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<miasto[7].nazwa; 
for(int i=miasto[7].nazwa.size();i<26;i++)cout << " ";
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{

cout <<blok<<miasto[7].nazwa;
for(int i=miasto[7].nazwa.size();i<26;i++)cout << " ";
cout<<blok; }
gotoxy(76,12);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<miasto[8].nazwa; 
for(int i=miasto[8].nazwa.size();i<26;i++)cout << " ";
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{

cout <<blok<<miasto[8].nazwa;
for(int i=miasto[8].nazwa.size();i<26;i++)cout << " ";
cout<<blok;  }
gotoxy(76,13);
if(x0==7){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<miasto[9].nazwa; 
for(int i=miasto[9].nazwa.size();i<26;i++)cout << " ";
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{

cout <<blok<<miasto[9].nazwa;
for(int i=miasto[9].nazwa.size();i<26;i++)cout << " ";
cout<<blok;  }
gotoxy(76,14);
if(x0==8){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Powrot                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<<"   Powrot                 "<<blok; 
gotoxy(76,15);
cout <<blok<<"                          "<<blok;
gotoxy(76,16);
for(int i=0;i<28;i++)cout << blok;
}





  
 ster=getch();
	
	komunikat = komunikat_domyslny;
	if(bkomunikat==true){
		system("CLS");
		bkomunikat=false;
	}
if(ster==KEY_DOWN && x0!=3 ||ster==KEY_DOWN && x0!=4 && menu==true || ster==KEY_DOWN && x0!=8 && lista_miast==true ||ster==KEY_DOWN && x0!=4 && menu_budowy==true){
	x0++;

	continue;
}
if(ster==KEY_UP && x0!=0){
x0--;

continue;
}

if(ster==']' && wybor_map!=3)wybor_map++;
if(ster=='[' && wybor_map!=0)wybor_map--;
 
 if(ster=='w' && mapa[x-1][y]!='@' && mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && wybor_jednostki==false && mgla_wojny[x-1][y]!=false){
              x--;
              }
 if(ster=='s' && mapa[x+1][y]!='@'&& mapa[x+1][y]!=woda&& mapa[x+1][y]!=gora&& wybor_jednostki==false&& mgla_wojny[x+1][y]!=false){
              x++;
              }
if(ster=='a' && mapa[x][y-1]!='@'&& mapa[x][y-1]!=woda && mapa[x][y-1]!=gora&& wybor_jednostki==false&& mgla_wojny[x][y-1]!=false){
              y--;
              }
if(ster=='d' && mapa[x][y+1]!='@'&& mapa[x][y+1]!=woda&& mapa[x][y+1]!=gora&& wybor_jednostki==false&& mgla_wojny[x][y+1]!=false){
              y++;
              }
              ///////////////////budowa/////////////
if(ster=='w' && mapa[x-1][y]!='@' && mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && budowa==true && (mapa_jednostek[x-1][y]=='O'|| mapa_jednostek[x-1][y]=='R'||mapa_jednostek[x-1][y]=='A')&& mapa_jednostek[x][y]=='O' || ster=='w' && mapa[x-1][y]!='@' && mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && ruch==true && (mapa_jednostek[x-1][y]=='O'|| mapa_jednostek[x-1][y]=='R'||mapa_jednostek[x-1][y]=='A')&& mapa_jednostek[x][y]=='O'){
              x--;
              continue;
              }
if(ster=='s' && mapa[x+1][y]!='@'&& mapa[x+1][y]!=woda&& mapa[x+1][y]!=gora&& budowa==true && (mapa_jednostek[x+1][y]=='O' ||mapa_jednostek[x+1][y]=='R' ||mapa_jednostek[x+1][y]=='A' )&& mapa_jednostek[x][y]=='O' || ster=='s' && mapa[x+1][y]!='@'&& mapa[x+1][y]!=woda&& mapa[x+1][y]!=gora&& ruch==true && (mapa_jednostek[x+1][y]=='O' ||mapa_jednostek[x+1][y]=='R' ||mapa_jednostek[x+1][y]=='A' )&& mapa_jednostek[x][y]=='O'){
              x++;
              continue;
              }
if(ster=='a' && mapa[x][y-1]!='@'&& mapa[x][y-1]!=woda && mapa[x][y-1]!=gora&& budowa==true&& (mapa_jednostek[x][y-1]=='O' ||mapa_jednostek[x][y-1]=='R' ||mapa_jednostek[x][y-1]=='A' )&& mapa_jednostek[x][y]=='O'|| ster=='a' && mapa[x][y-1]!='@'&& mapa[x][y-1]!=woda && mapa[x][y-1]!=gora&& ruch==true&& (mapa_jednostek[x][y-1]=='O' ||mapa_jednostek[x][y-1]=='R' ||mapa_jednostek[x][y-1]=='A' )&& mapa_jednostek[x][y]=='O'){
              y--;
              continue;
              }
if(ster=='d' && mapa[x][y+1]!='@'&& mapa[x][y+1]!=woda&& mapa[x][y+1]!=gora&&budowa==true && (mapa_jednostek[x][y+1]=='O' ||mapa_jednostek[x][y+1]=='R'|| mapa_jednostek[x][y+1]=='A' )&& mapa_jednostek[x][y]=='O'|| ster=='d' && mapa[x][y+1]!='@'&& mapa[x][y+1]!=woda&& mapa[x][y+1]!=gora&&ruch==true && (mapa_jednostek[x][y+1]=='O' ||mapa_jednostek[x][y+1]=='R' || mapa_jednostek[x][y]=='A')&& mapa_jednostek[x][y]=='O'){
              y++;
              continue;
              }
              /////robotnicy/////////
if(ster=='w' && mapa[x-1][y]!='@' && mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && budowa==true &&(mapa_jednostek[x-1][y]=='O'|| mapa_jednostek[x-1][y]=='R'||mapa_jednostek[x-1][y]=='A')&& mapa_jednostek[x][y]=='R' || ster=='w' && mapa[x-1][y]!='@' && mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && ruch==true &&(mapa_jednostek[x-1][y]=='O'|| mapa_jednostek[x-1][y]=='R'||mapa_jednostek[x-1][y]=='A') && mapa_jednostek[x][y]=='R'){
              x--;
              continue;
              }
if(ster=='s' && mapa[x+1][y]!='@'&& mapa[x+1][y]!=woda&& mapa[x+1][y]!=gora&& budowa==true && (mapa_jednostek[x+1][y]=='O' ||mapa_jednostek[x+1][y]=='R' ||mapa_jednostek[x+1][y]=='A' )&& mapa_jednostek[x][y]=='R' || ster=='s' && mapa[x+1][y]!='@'&& mapa[x+1][y]!=woda&& mapa[x+1][y]!=gora&& ruch==true && (mapa_jednostek[x+1][y]=='O' ||mapa_jednostek[x+1][y]=='R' ||mapa_jednostek[x+1][y]=='A' )&& mapa_jednostek[x][y]=='R'){
              x++;
              continue;
              }
if(ster=='a' && mapa[x][y-1]!='@'&& mapa[x][y-1]!=woda && mapa[x][y-1]!=gora&& budowa==true && (mapa_jednostek[x][y-1]=='O' ||mapa_jednostek[x][y-1]=='R' ||mapa_jednostek[x][y-1]=='A' )&& mapa_jednostek[x][y]=='R' || ster=='a' && mapa[x][y-1]!='@'&& mapa[x][y-1]!=woda && mapa[x][y-1]!=gora&& ruch==true && (mapa_jednostek[x][y-1]=='O' ||mapa_jednostek[x][y-1]=='R' ||mapa_jednostek[x][y-1]=='A' )&& mapa_jednostek[x][y]=='R'){
              y--;
              continue;
              }
if(ster=='d' && mapa[x][y+1]!='@'&& mapa[x][y+1]!=woda&& mapa[x][y+1]!=gora&&budowa==true && (mapa_jednostek[x][y+1]=='O' ||mapa_jednostek[x][y+1]=='R'|| mapa_jednostek[x][y+1]=='A' ) && mapa_jednostek[x][y]=='R' || ster=='d' && mapa[x][y+1]!='@'&& mapa[x][y+1]!=woda&& mapa[x][y+1]!=gora&& ruch==true && (mapa_jednostek[x][y+1]=='O' ||mapa_jednostek[x][y+1]=='R'|| mapa_jednostek[x][y+1]=='A' )&& mapa_jednostek[x][y]=='R'){
              y++;
              continue;
              }
              ////////armie////////
if( ster=='w' && mapa[x-1][y]!='@' && mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && ruch==true &&(mapa_jednostek[x-1][y]=='O'|| mapa_jednostek[x-1][y]=='R'||mapa_jednostek[x-1][y]=='A'||mapa_jednostek[x-1][y]=='B') && mapa_jednostek[x][y]=='A'&&mapa_armii[x-1][y]=='0'){
              x--;
              continue;
              }
if(ster=='s' && mapa[x+1][y]!='@'&& mapa[x+1][y]!=woda&& mapa[x+1][y]!=gora&& ruch==true && (mapa_jednostek[x+1][y]=='O' ||mapa_jednostek[x+1][y]=='R' ||mapa_jednostek[x+1][y]=='A' ||mapa_jednostek[x+1][y]=='B' )&& mapa_jednostek[x][y]=='A'&&mapa_armii[x+1][y]=='0'){
              x++;
              continue;
              }
if(ster=='a' && mapa[x][y-1]!='@'&& mapa[x][y-1]!=woda && mapa[x][y-1]!=gora&& ruch==true && (mapa_jednostek[x][y-1]=='O' ||mapa_jednostek[x][y-1]=='R' ||mapa_jednostek[x][y-1]=='A'||mapa_jednostek[x][y-1]=='B' )&& mapa_jednostek[x][y]=='A'&&mapa_armii[x][y-1]=='0'){
              y--;
              continue;
              }
if(ster=='d' && mapa[x][y+1]!='@'&& mapa[x][y+1]!=woda&& mapa[x][y+1]!=gora&& ruch==true && (mapa_jednostek[x][y+1]=='O' ||mapa_jednostek[x][y+1]=='R'|| mapa_jednostek[x][y+1]=='A' || mapa_jednostek[x][y+1]=='B')&& mapa_jednostek[x][y]=='A'&&mapa_armii[x][y+1]=='0'){
              y++;
              continue;
              }
              
              
if(ster=='e' && wybor_jednostki==false && mapa_jednostek[x][y]==osadnik || mapa_jednostek[x][y]==82 && ster=='e' && wybor_jednostki==false || mapa_jednostek[x][y]=='A' && ster=='e' && wybor_jednostki==false){
	if(nastepna_tura==0){
		komunikat="Nie masz juz punktow ruchu moj Panie";
		bkomunikat=true;
		continue;
	}
	wybor_jednostki=true;
	menu=false;
}

if(ster=='q' && menu==true && x0==1 && wybor_jednostki==false){
	menu=false;
	lista_miast=true;
	system("CLS");
	x0=0;
}

if(ster=='q' && lista_miast==true && x0==8 && wybor_jednostki==false){
	menu=true;
	lista_miast=false;
	system("CLS");
	x0=0;
}

if(ster=='q' && lista_miast==true && x0!=8){
	x=miasto[x0+1].x1;
	y=miasto[x0+1].y1;
	system("CLS");
}

/////////////////NASTEPNA TURA///////
if(ster=='q' && menu==true && x0==3){
	nastepna_tura=nastepna_tura_domyslnie;
	gracz1=false;
	//gracz2=true;
	ruch_barbarzyncow=true;
	for(int i=1;i<11;i++){
	miasto[i].obrona+=ludnosc*0.00005; 
	}
	for(int i=1;i<11;i++){
	miasto[i].produkcja+=miasto[i].przychod_produkcja; 
	}
	for(int i=1;i<11;i++){
	miasto[i].ludnosc+=100; 
	}
	zywnosc+=przychod_zywnosc;
	zloto+=przychod_zloto;
	kamien+=przychod_kamien;
	drewno+=przychod_drewno;
	nauka+=przychod_nauka;
	break;
}

if(ster=='q' && menu==false && x0==3 && mapa_jednostek[x][y]=='O' && budowa==true){
if(budowa==true){

	system("CLS");
	x=xd;
	y=yd;
	for(int i=xd-1;i<=xd+1;i++){
		for(int j=yd-1;j<=yd+1;j++){
		if(mapa[i][j]!=gora && mapa[i][j]!=woda && mapa[i][j]!=osada && mapa[i][j]!=stolica && mapa[i][j]!=tartak&& mapa[i][j]!=farma&& mapa[i][j]!=kopalnia){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		}
	}
}
}
menu=true;
budowa=false;
wybor_jednostki=false;
x0=0;
system("CLS");
}

if(ster=='q' && menu==false && x0==4 && mapa_jednostek[x][y]=='R' && budowa==true && menu_budowy==true){
	bufor_budowa=10;
	menu_budowy=false;
	system("CLS");
	x=xd;
	y=yd;
	for(int i=x-1;i<=x+1;i++){
		for(int j=y-1;j<=y+1;j++){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
	}
}
menu=true;
wybor_jednostki=false;
budowa=false;
x0=0;
system("CLS");
}
/////////////////powrot do stolicy//////////
if(menu==true && x0==0 && ster=='q' && liczba_miast>1){
	menu=false;
	mapa_glowna=false;
	bmapa_stolicy=true;
	xm=1;
	xd=x;
	yd=y;
	x=40;
	y=70;
	while(mapa_stolicy[x][y]!=dom && mapa_stolicy[x][y]!=dom2 && mapa_stolicy[x][y]!=woda && mapa_stolicy[x][y]!=gora){
		x++;
	}
	
	system("CLS");
}

if(ster=='e' && menu==true && mapa[x][y]==osada || ster=='e' && menu==true && mapa[x][y]==stolica){
	menu=false;
	mapa_glowna=false;
	xd=x;
	yd=y;
	if(mapa[x][y]==stolica){
	bmapa_stolicy=true;
	x=40;
	xm=1;
	y=70;
	while(mapa_stolicy[x][y]!=dom && mapa_stolicy[x][y]!=dom2 && mapa_stolicy[x][y]!=woda && mapa_stolicy[x][y]!=gora){
		x++;
	}
	}else{
		miasto[miasta[x][y]].menu_osady=true;
		xm=miasta[x][y];
		menu_osada=true;
	}
	system("CLS");
}


if(ster=='q' && menu==false && x0==3 && mapa_jednostek[x][y]=='R' && ruch==true && budowa==false){
	ruch=false;
	system("CLS");
	x=xd;
	y=yd;
	if(nawigacja==false){
	for(int i=x-1;i<=x+1;i++){
		for(int j=y-1;j<=y+1;j++){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
	}
}
}else{
		for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
	}
}
}
menu=true;
wybor_jednostki=false;
budowa=false;
x0=0;
system("CLS");
}
if(ster=='q' && menu==false && x0==3 && mapa_jednostek[x][y]=='A' && ruch==true && budowa==false){
	ruch=false;
	system("CLS");
	x=xd;
	y=yd;
	if(nawigacja==false){
	for(int i=x-1;i<=x+1;i++){
		for(int j=y-1;j<=y+1;j++){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
	}
}
}else{
		for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
	}
}
}
menu=true;
wybor_jednostki=false;
budowa=false;
x0=0;
system("CLS");
}
if(ster=='q' && menu==false && x0==3 && mapa_jednostek[x][y]=='O' && ruch==true && budowa==false){
	ruch=false;
	system("CLS");
	x=xd;
	y=yd;
	if(nawigacja==false){

	for(int i=x-1;i<=x+1;i++){
		for(int j=y-1;j<=y+1;j++){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
	}
}
}else{

	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
	}
}	
}
menu=true;
wybor_jednostki=false;
budowa=false;
x0=0;
system("CLS");
}

if(ster=='q' && menu==true && x0==2 && wybor_jednostki==true && menu_budowy==false){
menu=false;
x0=0;
system("CLS");
}

if(ster=='q' && menu==false && x0==3 && wybor_jednostki==true && menu_budowy==false){
wybor_jednostki=false;
x0=0;
menu=true;
system("CLS");
}

if(ster=='q' && x0==2 && wybor_jednostki==true && mapa_jednostek[x][y]=='R' && menu==false && menu_budowy==false && ruch==false){
	menu_budowy=true;
	system("CLS");
	continue;
}

if(ster=='q' && x0==4 && wybor_jednostki==true && mapa_jednostek[x][y]=='R' && menu==false && menu_budowy==true && ruch==false){
	bufor_budowa=10;
	menu_budowy=false;
	menu=false;
	system("CLS");

}


if(ster=='q' && wybor_jednostki==true && mapa_jednostek[x][y]=='O' && menu==false && x0==2 && budowa==false && bufor_multi[x][y]==dom2 && ruch==false){
	xd=x;
	yd=y;
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	mapa_jednostek[x][y]='O';
	if(mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && mapa[x-1][y]!=farma&& mapa[x-1][y]!=tartak&& mapa[x-1][y]!=kopalnia&& mapa[x-1][y]!=wioska){
	bufor_mjednostek[x-1][y]=mapa_jednostek[x-1][y];
	mapa_jednostek[x-1][y]='O';
	}
	
	if(mapa[x-1][y+1]!=woda && mapa[x-1][y+1]!=gora&& mapa[x-1][y+1]!=tartak&& mapa[x-1][y+1]!=farma&& mapa[x-1][y+1]!=kopalnia&& mapa[x-1][y+1]!=wioska){
	bufor_mjednostek[x-1][y+1]=mapa_jednostek[x-1][y+1];
	mapa_jednostek[x-1][y+1]='O';
	}
	
	if(mapa[x-1][y-1]!=woda && mapa[x-1][y-1]!=gora&& mapa[x-1][y-1]!=tartak&& mapa[x-1][y-1]!=farma&& mapa[x-1][y-1]!=kopalnia&& mapa[x-1][y-1]!=wioska){
	bufor_mjednostek[x-1][y-1]=mapa_jednostek[x-1][y-1];
	mapa_jednostek[x-1][y-1]='O';
	}
	
	if(mapa[x][y+1]!=woda &&mapa[x][y+1]!=gora&&mapa[x][y+1]!=tartak&&mapa[x][y+1]!=farma&&mapa[x][y+1]!=kopalnia&&mapa[x][y+1]!=wioska){
	bufor_mjednostek[x][y+1]=mapa_jednostek[x][y+1];
	mapa_jednostek[x][y+1]='O';
	}
	
	if(mapa[x][y-1]!=woda && mapa[x][y-1]!=gora&& mapa[x][y-1]!=tartak&& mapa[x][y-1]!=farma&& mapa[x][y-1]!=kopalnia&& mapa[x][y-1]!=wioska){
	bufor_mjednostek[x][y-1]=mapa_jednostek[x][y-1];
	mapa_jednostek[x][y-1]='O';
	}
	
	if(mapa[x+1][y-1]!=woda && mapa[x+1][y-1]!=gora&& mapa[x+1][y-1]!=tartak&& mapa[x+1][y-1]!=farma&& mapa[x+1][y-1]!=kopalnia&& mapa[x+1][y-1]!=wioska){
	bufor_mjednostek[x+1][y-1]=mapa_jednostek[x+1][y-1];
	mapa_jednostek[x+1][y-1]='O';
	}
	
	if(mapa[x+1][y]!=woda && mapa[x+1][y]!=gora&& mapa[x+1][y]!=tartak&& mapa[x+1][y]!=farma&& mapa[x+1][y]!=kopalnia&& mapa[x+1][y]!=wioska){
	bufor_mjednostek[x+1][y]=mapa_jednostek[x+1][y];
	mapa_jednostek[x+1][y]='O';
	}
	
	if(mapa[x+1][y+1]!=woda && mapa[x+1][y+1]!=gora&& mapa[x+1][y+1]!=tartak&& mapa[x+1][y+1]!=farma&& mapa[x+1][y+1]!=kopalnia&& mapa[x+1][y+1]!=wioska){
	bufor_mjednostek[x+1][y+1]=mapa_jednostek[x+1][y+1];
	mapa_jednostek[x+1][y+1]='O';
	}
	
	budowa=true;
}





////////////tartak/////////////
if(ster=='q' && wybor_jednostki==true && menu==false && x0==2 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true && bufor_multi[x][y]==dom){
	
	bufor_budowa=2;
	xd=x;
	yd=y;
	
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	if(bufor_multi[x][y]==dom)
	mapa_jednostek[x][y]='R';
	
	bufor_mjednostek[x-1][y]=mapa_jednostek[x-1][y];
	if(mapa[x-1][y]==dom){
	
	mapa_jednostek[x-1][y]='R';
	}
	bufor_mjednostek[x-1][y+1]=mapa_jednostek[x-1][y+1];
	if(bufor_multi[x-1][y+1]==dom){
	
	mapa_jednostek[x-1][y+1]='R';
	}
	bufor_mjednostek[x-1][y-1]=mapa_jednostek[x-1][y-1];
	if(bufor_multi[x-1][y-1]==dom){
	
	mapa_jednostek[x-1][y-1]='R';
	}
	bufor_mjednostek[x][y+1]=mapa_jednostek[x][y+1];
	if(bufor_multi[x][y+1]==dom){
	
	mapa_jednostek[x][y+1]='R';
	}
	bufor_mjednostek[x][y-1]=mapa_jednostek[x][y-1];
	if(bufor_multi[x][y-1]==dom){
	
	mapa_jednostek[x][y-1]='R';
	}
	bufor_mjednostek[x+1][y-1]=mapa_jednostek[x+1][y-1];
	if(bufor_multi[x+1][y-1]==dom){
	
	mapa_jednostek[x+1][y-1]='R';
	}
	bufor_mjednostek[x+1][y]=mapa_jednostek[x+1][y];
	if(bufor_multi[x+1][y]==dom){
	
	mapa_jednostek[x+1][y]='R';
	}
	bufor_mjednostek[x+1][y+1]=mapa_jednostek[x+1][y+1];
	if(bufor_multi[x+1][y+1]==dom){
	
	mapa_jednostek[x+1][y+1]='R';
	}
	budowa=true;
}
////////////farma

if(ster=='q' && wybor_jednostki==true && menu==false && x0==0 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true){

	bufor_budowa=0;
	xd=x;
	yd=y;
		bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	if(bufor_multi[x][y]==dom2 && bufor_multi[x][y]!=wioska && bufor_multi[x][y]!=kopalnia)
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	
	mapa_jednostek[x][y]='R';
	
	bufor_mjednostek[x-1][y]=mapa_jednostek[x-1][y];
	if(mapa[x-1][y]==dom2 && bufor_multi[x-1][y]!=wioska && bufor_multi[x-1][y]!=kopalnia){
	mapa_jednostek[x-1][y]='R';
	}
	bufor_mjednostek[x-1][y+1]=mapa_jednostek[x-1][y+1];
	if(bufor_multi[x-1][y+1]==dom2 && bufor_multi[x-1][y+1]!=wioska && bufor_multi[x-1][y+1]!=kopalnia){
	
	mapa_jednostek[x-1][y+1]='R';
	}
	bufor_mjednostek[x-1][y-1]=mapa_jednostek[x-1][y-1];
	if(bufor_multi[x-1][y-1]==dom2 && bufor_multi[x-1][y-1]!=wioska && bufor_multi[x-1][y-1]!=kopalnia){
	
	mapa_jednostek[x-1][y-1]='R';
	}
	bufor_mjednostek[x][y+1]=mapa_jednostek[x][y+1];
	if(bufor_multi[x][y+1]==dom2 && bufor_multi[x][y+1]!=wioska && bufor_multi[x][y+1]!=kopalnia){
	
	mapa_jednostek[x][y+1]='R';
	}
	bufor_mjednostek[x][y-1]=mapa_jednostek[x][y-1];
	if(bufor_multi[x][y-1]==dom2 && bufor_multi[x][y-1]!=wioska && bufor_multi[x][y-1]!=kopalnia){
	
	mapa_jednostek[x][y-1]='R';
	}
	bufor_mjednostek[x+1][y-1]=mapa_jednostek[x+1][y-1];
	if(bufor_multi[x+1][y-1]==dom2&& bufor_multi[x+1][y-1]!=wioska && bufor_multi[x+1][y-1]!=kopalnia){
	
	mapa_jednostek[x+1][y-1]='R';
	}
	bufor_mjednostek[x+1][y]=mapa_jednostek[x+1][y];
	if(bufor_multi[x+1][y]==dom2&& bufor_multi[x+1][y]!=wioska && bufor_multi[x+1][y]!=kopalnia){
	
	mapa_jednostek[x+1][y]='R';
	}
	bufor_mjednostek[x+1][y+1]=mapa_jednostek[x+1][y+1];
	if(bufor_multi[x+1][y+1]==dom2&& bufor_multi[x+1][y+1]!=wioska && bufor_multi[x+1][y+1]!=kopalnia){
	
	mapa_jednostek[x+1][y+1]='R';
	}
	budowa=true;

}

/////////wioska//////////
if(ster=='q' && wybor_jednostki==true && menu==false && x0==3 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true){

	bufor_budowa=3;
	xd=x;
	yd=y;
		bufor_mjednostek[x][y]=mapa_jednostek[x][y];
		if(bufor_multi[x][y]==dom2 && bufor_multi[x][y]!=farma && bufor_multi[x][y]!=kopalnia)
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	
	mapa_jednostek[x][y]='R';
	
	bufor_mjednostek[x-1][y]=mapa_jednostek[x-1][y];
	if(mapa[x-1][y]==dom2 && bufor_multi[x-1][y]!=farma && bufor_multi[x-1][y]!=kopalnia){
	mapa_jednostek[x-1][y]='R';
	}
	bufor_mjednostek[x-1][y+1]=mapa_jednostek[x-1][y+1];
	if(bufor_multi[x-1][y+1]==dom2 && bufor_multi[x-1][y+1]!=farma && bufor_multi[x-1][y+1]!=kopalnia){
	
	mapa_jednostek[x-1][y+1]='R';
	}
	bufor_mjednostek[x-1][y-1]=mapa_jednostek[x-1][y-1];
	if(bufor_multi[x-1][y-1]==dom2 && bufor_multi[x-1][y-1]!=farma && bufor_multi[x-1][y-1]!=kopalnia){
	
	mapa_jednostek[x-1][y-1]='R';
	}
	bufor_mjednostek[x][y+1]=mapa_jednostek[x][y+1];
	if(bufor_multi[x][y+1]==dom2 && bufor_multi[x][y+1]!=farma && bufor_multi[x][y+1]!=kopalnia){
	
	mapa_jednostek[x][y+1]='R';
	}
	bufor_mjednostek[x][y-1]=mapa_jednostek[x][y-1];
	if(bufor_multi[x][y-1]==dom2 && bufor_multi[x][y-1]!=farma && bufor_multi[x][y-1]!=kopalnia){
	
	mapa_jednostek[x][y-1]='R';
	}
	bufor_mjednostek[x+1][y-1]=mapa_jednostek[x+1][y-1];
	if(bufor_multi[x+1][y-1]==dom2&& bufor_multi[x+1][y-1]!=farma && bufor_multi[x+1][y-1]!=kopalnia){
	
	mapa_jednostek[x+1][y-1]='R';
	}
	bufor_mjednostek[x+1][y]=mapa_jednostek[x+1][y];
	if(bufor_multi[x+1][y]==dom2&& bufor_multi[x+1][y]!=farma && bufor_multi[x+1][y]!=kopalnia){
	
	mapa_jednostek[x+1][y]='R';
	}
	bufor_mjednostek[x+1][y+1]=mapa_jednostek[x+1][y+1];
	if(bufor_multi[x+1][y+1]==dom2&& bufor_multi[x+1][y+1]!=farma && bufor_multi[x+1][y+1]!=kopalnia){
	
	mapa_jednostek[x+1][y+1]='R';
	}
	budowa=true;

}

/////////kopalnia

if(ster=='q' && wybor_jednostki==true && menu==false && x0==1 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true && mapa[x][y-1]==gora || 
ster=='q' && wybor_jednostki==true && menu==false && x0==1 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true && mapa[x][y+1]==gora || 
ster=='q' && wybor_jednostki==true && menu==false && x0==1 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true && mapa[x-1][y+1]==gora ||
ster=='q' && wybor_jednostki==true && menu==false && x0==1 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true && mapa[x-1][y]==gora ||
ster=='q' && wybor_jednostki==true && menu==false && x0==1 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true && mapa[x-1][y-1]==gora ||
ster=='q' && wybor_jednostki==true && menu==false && x0==1 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true && mapa[x+1][y+1]==gora||
ster=='q' && wybor_jednostki==true && menu==false && x0==1 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true && mapa[x+1][y]==gora||
ster=='q' && wybor_jednostki==true && menu==false && x0==1 && budowa==false && mapa_jednostek[x][y]=='R' && menu_budowy==true && mapa[x+1][y-1]==gora){

	bufor_budowa=1;
	xd=x;
	yd=y;
	
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	if(bufor_multi[x][y]==dom2 && bufor_multi[x][y]!=wioska && bufor_multi[x][y]!=farma)
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	
	mapa_jednostek[x][y]='R';
	
	bufor_mjednostek[x-1][y]=mapa_jednostek[x-1][y];
	if(mapa[x-1][y]==dom2 && bufor_multi[x-1][y]!=wioska && bufor_multi[x-1][y]!=farma){
	mapa_jednostek[x-1][y]='R';
	}
	bufor_mjednostek[x-1][y+1]=mapa_jednostek[x-1][y+1];
	if(bufor_multi[x-1][y+1]==dom2 && bufor_multi[x-1][y+1]!=wioska && bufor_multi[x-1][y+1]!=farma){
	
	mapa_jednostek[x-1][y+1]='R';
	}
	bufor_mjednostek[x-1][y-1]=mapa_jednostek[x-1][y-1];
	if(bufor_multi[x-1][y-1]==dom2 && bufor_multi[x-1][y-1]!=wioska && bufor_multi[x-1][y-1]!=farma){
	
	mapa_jednostek[x-1][y-1]='R';
	}
	bufor_mjednostek[x][y+1]=mapa_jednostek[x][y+1];
	if(bufor_multi[x][y+1]==dom2 && bufor_multi[x][y+1]!=wioska && bufor_multi[x][y+1]!=farma){
	
	mapa_jednostek[x][y+1]='R';
	}
	bufor_mjednostek[x][y-1]=mapa_jednostek[x][y-1];
	if(bufor_multi[x][y-1]==dom2 && bufor_multi[x][y-1]!=wioska && bufor_multi[x][y-1]!=farma){
	
	mapa_jednostek[x][y-1]='R';
	}
	bufor_mjednostek[x+1][y-1]=mapa_jednostek[x+1][y-1];
	if(bufor_multi[x+1][y-1]==dom2&& bufor_multi[x+1][y-1]!=wioska && bufor_multi[x+1][y-1]!=farma){
	
	mapa_jednostek[x+1][y-1]='R';
	}
	bufor_mjednostek[x+1][y]=mapa_jednostek[x+1][y];
	if(bufor_multi[x+1][y]==dom2&& bufor_multi[x+1][y]!=wioska && bufor_multi[x+1][y]!=farma){
	
	mapa_jednostek[x+1][y]='R';
	}
	bufor_mjednostek[x+1][y+1]=mapa_jednostek[x+1][y+1];
	if(bufor_multi[x+1][y+1]==dom2&& bufor_multi[x+1][y+1]!=wioska && bufor_multi[x+1][y+1]!=farma){
	
	mapa_jednostek[x+1][y+1]='R';
	}
	budowa=true;

}


if(budowa==true && ster=='e' && wybor_jednostki==true && menu==false && mapa_jednostek[x][y]=='O' && teretorium[x][y]=='x' || budowa==true && ster=='e' && wybor_jednostki==true && menu==false && mapa_jednostek[x][y]=='O' && teretorium[x][y]=='1'){
	
		if(liczba_miast==11)
	{
	komunikat="Masz maksymalna ilosc miast moj Panie";
	bkomunikat=true;
	continue;
	}
	for(int i=x-3;i<=x+3;i++){
		for(int j=y-3;j<=y+3;j++){
			if(mapa[i][j]==stolica || mapa[i][j]==osada || mapa_jednostek[x][y]=='B'){
				komunikat = "Jestes za blisko innego miasta lub za blisko jednostek wroga moj Panie";
				blisko=true;
			}
		}
	}
	if(blisko==true){
		blisko=false;
		bkomunikat=true;
		continue;
		
	}

	miasta[x][y]=liczba_miast;
	if(liczba_miast==1)
	mapa[x][y]=stolica;
	else
	mapa[x][y]=osada;
	
	if(mapa[x-1][y]==woda || mapa[x-1][y-1]==woda || mapa[x-1][y+1]==woda || mapa[x][y-1]==woda || mapa[x][y+1]==woda || mapa[x+1][y-1]==woda || mapa[x+1][y]==woda || mapa[x+1][y+1]==woda)
	miasto[liczba_miast].woda=true;
	

	
	for(int i=x-5;i<x+5;i++){
		for(int j=y-5;j<y+5;j++){
			if(mapa[i][j]!=woda && mapa[i][j]!=gora && zasieg_miast[i][j]=='0'){
				zasieg_miast[i][j]=liczba_miast-208;
				teretorium[i][j]='1';
				if(mapa[i][j]==tartak)mapa_tartak[i][j]=liczba_miast;
				if(mapa[i][j]==kopalnia)mapa_kopalnia[i][j]=liczba_miast;
				if(mapa[i][j]==farma)mapa_farma[i][j]=liczba_miast;
				if(mapa[i][j]==wioska)mapa_wioska[i][j]=liczba_miast;
			}
		}
	}
	for(int i=x-1;i<x+1;i++){
		for(int j=y-1;j<y+1;j++){
			if(mapa[i][j]!=woda && mapa[i][j]!=gora){
				zasieg_miast[i][j]=liczba_miast-208;
				
			}
		}
	}
	
	miasto[liczba_miast].x1=x;
	miasto[liczba_miast].y1=y;
	bufor_multi[x][y]=mapa[x][y];
	liczba_miast++;
	budowa=false;
	wybor_jednostki=false;
	menu=true;
	nazwa=true;
	for(int i=xd-1;i<=xd+1;i++){
		for(int j=yd-1;j<=yd+1;j++){
		if(mapa[i][j]!=gora && mapa[i][j]!=woda){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		}
	}
	if(mapa_jednostek[xd][yd]=='O')mapa_jednostek[xd][yd]=' ';
}
nastepna_tura--;
system("CLS");
}

/////////tartak////////
if(budowa==true && ster=='e' && wybor_jednostki==true && menu==false && mapa_jednostek[x][y]=='R'&&(bufor_mjednostek[x][y]!='R' || x==xd && y==yd) && menu_budowy==true && bufor_budowa==2 && teretorium[x][y]=='1'){

	mapa[x][y]=tartak;
	budowa=false;
	menu_budowy=false;
	wybor_jednostki=false;
	menu=true;
	for(int i=xd-1;i<=xd+1;i++){
		for(int j=yd-1;j<=yd+1;j++){
		if(mapa[i][j]!=gora && mapa[i][j]!=woda){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		}
	}
	if(mapa_jednostek[xd][yd]=='R')mapa_jednostek[xd][yd]=' ';
}
mapa_tartak[x][y]=zasieg_miast[x][y]-48;
bufor_multi[x][y]=mapa[x][y];
system("CLS");
miasto[mapa_tartak[x][y]].przychod_drewno=miasto[mapa_tartak[x][y]].przychod_drewno+30;
if(tartakb.lvl==3)
miasto[mapa_tartak[x][y]].przychod_drewno=miasto[mapa_tartak[x][y]].przychod_drewno+20;
nastepna_tura--;
}
///////////////farma///////////
if(budowa==true && ster=='e' && wybor_jednostki==true && menu==false && mapa_jednostek[x][y]=='R'&&(bufor_mjednostek[x][y]!='R' || x==xd && y==yd) && menu_budowy==true && bufor_budowa==0 && teretorium[x][y]=='1'){

	mapa[x][y]=farma;
	budowa=false;
	menu_budowy=false;
	wybor_jednostki=false;
	menu=true;
	for(int i=xd-1;i<=xd+1;i++){
		for(int j=yd-1;j<=yd+1;j++){
		if(mapa[i][j]!=gora && mapa[i][j]!=woda){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		}
	}
	if(mapa_jednostek[xd][yd]=='R')mapa_jednostek[xd][yd]=' ';
}
mapa_farma[x][y]=zasieg_miast[x][y]-48;
bufor_multi[x][y]=mapa[x][y];
system("CLS");
miasto[mapa_farma[x][y]].przychod_zywnosc=miasto[mapa_farma[x][y]].przychod_zywnosc+30;
if(port.lvl>=2){
	miasto[mapa_farma[x][y]].przychod_zywnosc=miasto[mapa_farma[x][y]].przychod_zywnosc+miasto[mapa_farma[x][y]].przychod_zywnosc*port.lvl*0.1;
}
nastepna_tura--;
}
/////////////wioska///////////////////
if(budowa==true && ster=='e' && wybor_jednostki==true && menu==false && mapa_jednostek[x][y]=='R'&&(bufor_mjednostek[x][y]!='R' || x==xd && y==yd) && menu_budowy==true && bufor_budowa==3 && teretorium[x][y]=='1'){

	mapa[x][y]=wioska;
	budowa=false;
	menu_budowy=false;
	wybor_jednostki=false;
	menu=true;
	for(int i=xd-1;i<=xd+1;i++){
		for(int j=yd-1;j<=yd+1;j++){
		if(mapa[i][j]!=gora && mapa[i][j]!=woda){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		}
	}
	if(mapa_jednostek[xd][yd]=='R')mapa_jednostek[xd][yd]=' ';
}
mapa_wioska[x][y]=zasieg_miast[x][y]-48;
bufor_multi[x][y]=mapa[x][y];
system("CLS");
miasto[mapa_wioska[x][y]].przychod_produkcja=miasto[mapa_wioska[x][y]].przychod_produkcja+30;
miasto[mapa_wioska[x][y]].ludnosc+=1000;
if(magazyn.lvl>=2){
	miasto[mapa_wioska[x][y]].przychod_produkcja=miasto[mapa_wioska[x][y]].przychod_produkcja+miasto[mapa_wioska[x][y]].przychod_produkcja*magazyn.lvl*0.1;
}
nastepna_tura--;
}
///////////////kopalnia///////////////
if(budowa==true && ster=='e' && wybor_jednostki==true && menu==false && mapa_jednostek[x][y]=='R' &&(bufor_mjednostek[x][y]!='R' || x==xd && y==yd) && menu_budowy==true && bufor_budowa==1 && teretorium[x][y]=='1'){

	mapa[x][y]=kopalnia;
	budowa=false;
	menu_budowy=false;
	wybor_jednostki=false;
	menu=true;
	for(int i=xd-1;i<=xd+1;i++){
		for(int j=yd-1;j<=yd+1;j++){
		if(mapa[i][j]!=gora && mapa[i][j]!=woda){
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		}
	}
	if(mapa_jednostek[xd][yd]=='R')mapa_jednostek[xd][yd]=' ';
}
bufor_multi[xd][yd]=kopalnia;
mapa_kopalnia[x][y]=zasieg_miast[x][y]-48;
bufor_multi[x][y]=mapa[x][y];
system("CLS");
miasto[mapa_kopalnia[x][y]].przychod_kamien=miasto[mapa_kopalnia[x][y]].przychod_kamien+30;
miasto[mapa_kopalnia[x][y]].przychod_zloto=miasto[mapa_kopalnia[x][y]].przychod_zloto+15;
if(port.lvl==2){
miasto[mapa_kopalnia[x][y]].przychod_kamien=miasto[mapa_kopalnia[x][y]].przychod_kamien+10;
miasto[mapa_kopalnia[x][y]].przychod_zloto=miasto[mapa_kopalnia[x][y]].przychod_zloto+10;
}
if(port.lvl==3){
miasto[mapa_kopalnia[x][y]].przychod_kamien=miasto[mapa_kopalnia[x][y]].przychod_kamien+20;
miasto[mapa_kopalnia[x][y]].przychod_zloto=miasto[mapa_kopalnia[x][y]].przychod_zloto+20;
}
nastepna_tura--;
}

///////////////RUCH//////////////

if(ster=='q' && wybor_jednostki==true && mapa_jednostek[x][y]=='O' && menu==false && x0==0 && budowa==false && ruch==false && nawigacja==false){
	xd=x;
	yd=y;
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	mapa_jednostek[x][y]='O';
	bufor_mjednostek[x-1][y]=mapa_jednostek[x-1][y];
	if(mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && mapa_jednostek[x-1][y]!=osadnik && mapa_jednostek[x-1][y]!=robotnik && mapa[x-1][y]!=stolica && mapa[x-1][y]!=osada && mapa_jednostek[x-1][y]!='B' && mapa_jednostek[x-1][y]!='A'){

	mapa_jednostek[x-1][y]='O';
	}
	bufor_mjednostek[x-1][y+1]=mapa_jednostek[x-1][y+1];
	if(mapa[x-1][y+1]!=woda && mapa[x-1][y+1]!=gora && mapa_jednostek[x-1][y+1]!=osadnik && mapa_jednostek[x-1][y+1]!=robotnik&& mapa[x-1][y+1]!=stolica&& mapa[x-1][y+1]!=osada&& mapa_jednostek[x-1][y+1]!='B' && mapa_jednostek[x-1][y+1]!='A'){
	mapa_jednostek[x-1][y+1]='O';
	}
	bufor_mjednostek[x-1][y-1]=mapa_jednostek[x-1][y-1];
	if(mapa[x-1][y-1]!=woda && mapa[x-1][y-1]!=gora && mapa_jednostek[x-1][y-1]!=osadnik && mapa_jednostek[x-1][y-1]!=robotnik&& mapa[x-1][y-1]!=stolica&& mapa[x-1][y-1]!=osada&& mapa_jednostek[x-1][y-1]!='B'&& mapa_jednostek[x-1][y-1]!='A'){
	mapa_jednostek[x-1][y-1]='O';
	}
		bufor_mjednostek[x][y+1]=mapa_jednostek[x][y+1];
	if(mapa[x][y+1]!=woda &&mapa[x][y+1]!=gora && mapa_jednostek[x][y+1]!=osadnik && mapa_jednostek[x][y+1]!=robotnik && mapa[x][y+1]!=stolica && mapa[x][y+1]!=osada && mapa_jednostek[x][y+1]!='B' && mapa_jednostek[x][y+1]!='A'){

	mapa_jednostek[x][y+1]='O';
	}
		bufor_mjednostek[x][y-1]=mapa_jednostek[x][y-1];
	if(mapa[x][y-1]!=woda && mapa[x][y-1]!=gora && mapa_jednostek[x][y-1]!=osadnik && mapa_jednostek[x][y-1]!=robotnik&& mapa[x][y-1]!=stolica&& mapa[x][y-1]!=osada&& mapa_jednostek[x][y-1]!='B'&& mapa_jednostek[x][y-1]!='A'){

	mapa_jednostek[x][y-1]='O';
	}
		bufor_mjednostek[x+1][y-1]=mapa_jednostek[x+1][y-1];
	if(mapa[x+1][y-1]!=woda && mapa[x+1][y-1]!=gora && mapa_jednostek[x+1][y-1]!=osadnik && mapa_jednostek[x+1][y-1]!=robotnik&& mapa[x+1][y-1]!=stolica&& mapa[x+1][y-1]!=osada&& mapa_jednostek[x+1][y-1]!='A'&& mapa_jednostek[x+1][y-1]!='B'){

	mapa_jednostek[x+1][y-1]='O';
	}
		bufor_mjednostek[x+1][y]=mapa_jednostek[x+1][y];
	if(mapa[x+1][y]!=woda && mapa[x+1][y]!=gora && mapa_jednostek[x+1][y]!=osadnik && mapa_jednostek[x+1][y]!=robotnik&& mapa[x+1][y]!=stolica&& mapa[x+1][y]!=osada&& mapa_jednostek[x+1][y]!='A'&& mapa_jednostek[x+1][y]!='B'){

	mapa_jednostek[x+1][y]='O';
	}
		bufor_mjednostek[x+1][y+1]=mapa_jednostek[x+1][y+1];
	if(mapa[x+1][y+1]!=woda && mapa[x+1][y+1]!=gora && mapa_jednostek[x+1][y+1]!=osadnik && mapa_jednostek[x+1][y+1]!=robotnik&& mapa[x+1][y+1]!=stolica&& mapa[x+1][y+1]!=osada&& mapa_jednostek[x+1][y+1]!='A'&& mapa_jednostek[x+1][y+1]!='B'){

	mapa_jednostek[x+1][y+1]='O';
	}
	
	ruch=true;
}

if(ruch==true && ster=='e' && wybor_jednostki==true && mapa_jednostek[x][y]=='O' && x0==0 && ruch==true && nawigacja==false && bufor_mjednostek[x][y]!='O' && x0==0 && bufor_multi[x][y]!=stolica && bufor_multi[x][y]!=osada && mapa_jednostek[x][y]!='R'&& mapa_jednostek[x][y]!='B'&& mapa_jednostek[x][y]!='A'){
		for(int i=xd-1;i<=xd+1;i++){
		for(int j=yd-1;j<=yd+1;j++){
		mapa_jednostek[i][j]=bufor_mjednostek[i][j];
	}
	if(mapa_jednostek[xd][yd]=='O')mapa_jednostek[xd][yd]=' ';
}
	mapa_jednostek[x][y]='O';
	ruch=false;
	wybor_jednostki=false;
	menu=true;
	nastepna_tura--;
}

if(ster=='q' && wybor_jednostki==true && mapa_jednostek[x][y]=='R' && menu==false && x0==0 && budowa==false && ruch==false && nawigacja==false){
	xd=x;
	yd=y;
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	mapa_jednostek[x][y]='R';
	bufor_mjednostek[x-1][y]=mapa_jednostek[x-1][y];
	if(mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && mapa_jednostek[x-1][y]!=osadnik && mapa_jednostek[x-1][y]!=robotnik&& mapa_jednostek[x-1][y]!='B'){

	mapa_jednostek[x-1][y]='R';
	}
	bufor_mjednostek[x-1][y+1]=mapa_jednostek[x-1][y+1];
	if(mapa[x-1][y+1]!=woda && mapa[x-1][y+1]!=gora && mapa_jednostek[x-1][y+1]!=osadnik && mapa_jednostek[x-1][y+1]!=robotnik&& mapa_jednostek[x-1][y+1]!='B'){
	mapa_jednostek[x-1][y+1]='R';
	}
	bufor_mjednostek[x-1][y-1]=mapa_jednostek[x-1][y-1];
	if(mapa[x-1][y-1]!=woda && mapa[x-1][y-1]!=gora && mapa_jednostek[x-1][y-1]!=osadnik && mapa_jednostek[x-1][y-1]!=robotnik&& mapa_jednostek[x-1][y-1]!='B'){
	mapa_jednostek[x-1][y-1]='R';
	}
		bufor_mjednostek[x][y+1]=mapa_jednostek[x][y+1];
	if(mapa[x][y+1]!=woda &&mapa[x][y+1]!=gora && mapa_jednostek[x][y+1]!=osadnik && mapa_jednostek[x][y+1]!=robotnik&& mapa_jednostek[x][y+1]!='B'){

	mapa_jednostek[x][y+1]='R';
	}
		bufor_mjednostek[x][y-1]=mapa_jednostek[x][y-1];
	if(mapa[x][y-1]!=woda && mapa[x][y-1]!=gora && mapa_jednostek[x][y-1]!=osadnik && mapa_jednostek[x][y-1]!=robotnik&& mapa_jednostek[x][y-1]!='B'){

	mapa_jednostek[x][y-1]='R';
	}
		bufor_mjednostek[x+1][y-1]=mapa_jednostek[x+1][y-1];
	if(mapa[x+1][y-1]!=woda && mapa[x+1][y-1]!=gora && mapa_jednostek[x+1][y-1]!=osadnik && mapa_jednostek[x+1][y-1]!=robotnik&& mapa_jednostek[x+1][y-1]!='B'){

	mapa_jednostek[x+1][y-1]='R';
	}
		bufor_mjednostek[x+1][y]=mapa_jednostek[x+1][y];
	if(mapa[x+1][y]!=woda && mapa[x+1][y]!=gora && mapa_jednostek[x+1][y]!=osadnik && mapa_jednostek[x+1][y]!=robotnik&& mapa_jednostek[x+1][y]!='B'){

	mapa_jednostek[x+1][y]='R';
	}
		bufor_mjednostek[x+1][y+1]=mapa_jednostek[x+1][y+1];
	if(mapa[x+1][y+1]!=woda && mapa[x+1][y+1]!=gora && mapa_jednostek[x+1][y+1]!=osadnik && mapa_jednostek[x+1][y+1]!=robotnik&& mapa_jednostek[x+1][y+1]!='B'){

	mapa_jednostek[x+1][y+1]='R';
	}
	
	ruch=true;
}

if(ruch==true && ster=='e' && wybor_jednostki==true && mapa_jednostek[x][y]=='R' && bufor_mjednostek[x][y]!='R' && x0==0 && ruch==true && nawigacja==false && bufor_multi[x][y]!=stolica && bufor_multi[x][y]!=osada && mapa_jednostek[x][y]!='O'&& mapa_jednostek[x][y]!='B'&& mapa_jednostek[x][y]!='A'){
		for(int i=xd-1;i<=xd+1;i++){
		for(int j=yd-1;j<=yd+1;j++){
		
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		
	}
	if(mapa_jednostek[xd][yd]=='R')mapa_jednostek[xd][yd]=' ';
}
	mapa_jednostek[x][y]='R';
	ruch=false;
	wybor_jednostki=false;
	menu=true;
	nastepna_tura--;
}

if(ster=='q' && wybor_jednostki==true && mapa_jednostek[x][y]=='A' && menu==false && x0==0 && budowa==false && ruch==false && nawigacja==false){
	xd=x;
	yd=y;
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	mapa_jednostek[x][y]='A';
	bufor_mjednostek[x-1][y]=mapa_jednostek[x-1][y];
	if(mapa[x-1][y]!=woda && mapa[x-1][y]!=gora && mapa_jednostek[x-1][y]!=osadnik && mapa_jednostek[x-1][y]!=robotnik && mapa[x-1][y]!=stolica && mapa[x-1][y]!=osada && mapa_jednostek[x-1][y]!='O'&& mapa_jednostek[x-1][y]!='B' && mapa_jednostek[x-1][y]!='A'){

	mapa_jednostek[x-1][y]='A';
	}
	bufor_mjednostek[x-1][y+1]=mapa_jednostek[x-1][y+1];
	if(mapa[x-1][y+1]!=woda && mapa[x-1][y+1]!=gora && mapa_jednostek[x-1][y+1]!=osadnik && mapa_jednostek[x-1][y+1]!=robotnik&& mapa[x-1][y+1]!=stolica&& mapa[x-1][y+1]!=osada&& mapa_jednostek[x-1][y+1]!='O'&& mapa_jednostek[x-1][y+1]!='B' && mapa_jednostek[x-1][y+1]!='A'){
	mapa_jednostek[x-1][y+1]='A';
	}
	bufor_mjednostek[x-1][y-1]=mapa_jednostek[x-1][y-1];
	if(mapa[x-1][y-1]!=woda && mapa[x-1][y-1]!=gora && mapa_jednostek[x-1][y-1]!=osadnik && mapa_jednostek[x-1][y-1]!=robotnik&& mapa[x-1][y-1]!=stolica&& mapa[x-1][y-1]!=osada&& mapa_jednostek[x-1][y-1]!='O'&& mapa_jednostek[x-1][y-1]!='B'&& mapa_jednostek[x-1][y-1]!='A'){
	mapa_jednostek[x-1][y-1]='A';
	}
		bufor_mjednostek[x][y+1]=mapa_jednostek[x][y+1];
	if(mapa[x][y+1]!=woda &&mapa[x][y+1]!=gora && mapa_jednostek[x][y+1]!=osadnik && mapa_jednostek[x][y+1]!=robotnik && mapa[x][y+1]!=stolica && mapa[x][y+1]!=osada && mapa_jednostek[x][y+1]!='O'&& mapa_jednostek[x][y+1]!='B' && mapa_jednostek[x][y+1]!='A'){

	mapa_jednostek[x][y+1]='A';
	}
		bufor_mjednostek[x][y-1]=mapa_jednostek[x][y-1];
	if(mapa[x][y-1]!=woda && mapa[x][y-1]!=gora && mapa_jednostek[x][y-1]!=osadnik && mapa_jednostek[x][y-1]!=robotnik&& mapa[x][y-1]!=stolica&& mapa[x][y-1]!=osada&& mapa_jednostek[x][y-1]!='O'&& mapa_jednostek[x][y-1]!='B'&& mapa_jednostek[x][y-1]!='A'){

	mapa_jednostek[x][y-1]='A';
	}
		bufor_mjednostek[x+1][y-1]=mapa_jednostek[x+1][y-1];
	if(mapa[x+1][y-1]!=woda && mapa[x+1][y-1]!=gora && mapa_jednostek[x+1][y-1]!=osadnik && mapa_jednostek[x+1][y-1]!=robotnik&& mapa[x+1][y-1]!=stolica&& mapa[x+1][y-1]!=osada&& mapa_jednostek[x+1][y-1]!='O'&& mapa_jednostek[x+1][y-1]!='B'&& mapa_jednostek[x+1][y-1]!='B'){

	mapa_jednostek[x+1][y-1]='A';
	}
		bufor_mjednostek[x+1][y]=mapa_jednostek[x+1][y];
	if(mapa[x+1][y]!=woda && mapa[x+1][y]!=gora && mapa_jednostek[x+1][y]!=osadnik && mapa_jednostek[x+1][y]!=robotnik&& mapa[x+1][y]!=stolica&& mapa[x+1][y]!=osada&& mapa_jednostek[x+1][y]!='O'&& mapa_jednostek[x+1][y]!='B'&& mapa_jednostek[x+1][y]!='B'){

	mapa_jednostek[x+1][y]='A';
	}
		bufor_mjednostek[x+1][y+1]=mapa_jednostek[x+1][y+1];
	if(mapa[x+1][y+1]!=woda && mapa[x+1][y+1]!=gora && mapa_jednostek[x+1][y+1]!=osadnik && mapa_jednostek[x+1][y+1]!=robotnik&& mapa[x+1][y+1]!=stolica&& mapa[x+1][y+1]!=osada&& mapa_jednostek[x+1][y+1]!='O'&& mapa_jednostek[x+1][y+1]!='B'&& mapa_jednostek[x+1][y+1]!='B'){

	mapa_jednostek[x+1][y+1]='A';
	}
	
	ruch=true;
}

if(ruch==true && ster=='e' && wybor_jednostki==true && (mapa_jednostek[x][y]=='A'||mapa_jednostek[x][y]=='B') && x0==0 && ruch==true && nawigacja==false && bufor_mjednostek[x][y]!='A' && x0==0 && bufor_multi[x][y]!=stolica && bufor_multi[x][y]!=osada && mapa_jednostek[x][y]!='R'&& mapa_jednostek[x][y]!='O'){
	
		if(mapa_jednostek[x][y]=='B'){
			walka_barbarzyncy(armia[mapa_armii[x][y]-48],true,false,&zloto,&ilosc_barbarzyncow);
		}
			
		for(int i=xd-1;i<=xd+1;i++){
		for(int j=yd-1;j<=yd+1;j++){
		mapa_jednostek[i][j]=bufor_mjednostek[i][j];
	}
	if(mapa_jednostek[xd][yd]=='A')mapa_jednostek[xd][yd]=' ';
}

	mapa_jednostek[x][y]='A';
	armia[mapa_armii[xd][yd]-48].x=x;
	armia[mapa_armii[xd][yd]-48].y=y;
	mapa_armii[x][y]=mapa_armii[xd][yd];
	mapa_armii[xd][yd]='0';
	ruch=false;
	wybor_jednostki=false;
	menu=true;
	nastepna_tura--;
}
/////////////nawigacja/////////

if(ster=='q' && wybor_jednostki==true && mapa_jednostek[x][y]=='O' && menu==false && x0==0 && budowa==false && ruch==false && nawigacja==true){
	xd=x;
	yd=y;
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	mapa_jednostek[x][y]='O';
	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
				bufor_mjednostek[i][j]=mapa_jednostek[i][j];
	if(mapa[i][j]!=woda && mapa[i][j]!=gora  && mapa_jednostek[i][j]!=osadnik && mapa_jednostek[i][j]!=robotnik && mapa_jednostek[i][j]!='B'){

	mapa_jednostek[i][j]='O';
	}
		}
	}
	ruch=true;
}

if(ruch==true && ster=='e' && wybor_jednostki==true && mapa_jednostek[x][y]=='O' && bufor_mjednostek[x][y]!='O' && x0==0 && ruch==true && nawigacja==true && bufor_multi[x][y]!=stolica && bufor_multi[x][y]!=osada && mapa_jednostek[x][y]!='R'&& mapa_jednostek[x][y]!='B'&& mapa_jednostek[x][y]!='A'){
		for(int i=xd-2;i<=xd+2;i++){
		for(int j=yd-2;j<=yd+2;j++){
		
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		
	}
	if(mapa_jednostek[xd][yd]=='O')mapa_jednostek[xd][yd]=' ';
}
	mapa_jednostek[x][y]='O';
	ruch=false;
	wybor_jednostki=false;
	menu=true;
	nastepna_tura--;
}

if(ster=='q' && wybor_jednostki==true && mapa_jednostek[x][y]=='R' && menu==false && x0==0 && budowa==false && ruch==false && nawigacja==true){
	xd=x;
	yd=y;
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	mapa_jednostek[x][y]='R';
	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
				bufor_mjednostek[i][j]=mapa_jednostek[i][j];
	if(mapa[i][j]!=woda && mapa[i][j]!=gora && mapa_jednostek[i][j]!=osadnik && mapa_jednostek[i][j]!=robotnik && mapa_jednostek[i][j]!='B' ){

	mapa_jednostek[i][j]='R';
	}
		}
	}
	
	ruch=true;
}

if(ruch==true && ster=='e' && wybor_jednostki==true && mapa_jednostek[x][y]=='A' && x0==0 && ruch==true && nawigacja==true && bufor_mjednostek[x][y]!='A' && bufor_multi[x][y]!=stolica && bufor_multi[x][y]!=osada && mapa_jednostek[x][y]!='O'&& mapa_jednostek[x][y]!='B'&& mapa_jednostek[x][y]!='R'){
		for(int i=xd-2;i<=xd+2;i++){
		for(int j=yd-2;j<=yd+2;j++){
		
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		
	}
	if(mapa_jednostek[xd][yd]=='A')mapa_jednostek[xd][yd]=' ';
}
	armia[mapa_armii[xd][yd]-48].x=x;
	armia[mapa_armii[xd][yd]-48].y=y;
	mapa_armii[x][y]=mapa_armii[xd][yd];
	mapa_armii[xd][yd]='0';
	mapa_jednostek[x][y]='A';
	ruch=false;
	wybor_jednostki=false;
	menu=true;
	nastepna_tura--;
}

if(ster=='q' && wybor_jednostki==true && mapa_jednostek[x][y]=='A' && menu==false && x0==0 && budowa==false && ruch==false && nawigacja==true){
	xd=x;
	yd=y;
	bufor_mjednostek[x][y]=mapa_jednostek[x][y];
	
	mapa_jednostek[x][y]='A';
	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
				bufor_mjednostek[i][j]=mapa_jednostek[i][j];
	if(mapa[i][j]!=woda && mapa[i][j]!=gora && mapa_jednostek[i][j]!=osadnik && mapa_jednostek[i][j]!=robotnik &&mapa_jednostek[i][j]!='B' ){

	mapa_jednostek[i][j]='A';
	}
		}
	}
	
	ruch=true;
}

if(ruch==true && ster=='e' && wybor_jednostki==true && mapa_jednostek[x][y]=='R' && x0==0 && ruch==true && nawigacja==true && bufor_mjednostek[x][y]!='R' && bufor_multi[x][y]!=stolica && bufor_multi[x][y]!=osada && mapa_jednostek[x][y]!='O'&& mapa_jednostek[x][y]!='B'&& mapa_jednostek[x][y]!='A'){
		for(int i=xd-2;i<=xd+2;i++){
		for(int j=yd-2;j<=yd+2;j++){
		
			mapa_jednostek[i][j]=bufor_mjednostek[i][j];
		
	}
	if(mapa_jednostek[xd][yd]=='R')mapa_jednostek[xd][yd]=' ';
}
	mapa_jednostek[x][y]='R';
	ruch=false;
	wybor_jednostki=false;
	menu=true;
	nastepna_tura--;
}

 if(ster=='c'){
 	zloto=zloto+1000;
 	nauka=nauka+1000;
 	for(int i=1;i<11;i++)
 	miasto[i].produkcja=miasto[i].produkcja+1000;
 	zywnosc+=1000;
 	kamien+=1000;
 	drewno+=1000;
 	wiara+=1000;
 }
 if(ster=='x'){
 	hodowla=true;
 	waluta=true;
 	nawigacja=true;
 	obrobka_zelaza=true;
 	obrobka_stali=true;
 	ratusz.lvl=5;
 	kapitol.lvl=5;
 	koszary.lvl=4;
 	stajnia.lvl=4;
 	warsztat.lvl=2;
 	plac.lvl=1;
 	miasto[1].ludnosc=30000;
 }
 
 if(ster=='b'){
 	mapa_jednostek[x][y]='B';
 }
  if(ster=='o'){
 	mapa_jednostek[x][y]='O';
 }
  if(ster=='r'){
 	mapa_jednostek[x][y]='R';
 }
 if(ster=='l'){
 	walka_barbarzyncy(armia[1],true,false,&zloto,&ilosc_barbarzyncow);
 }
 if(ster=='n'){
 	mapa_jednostek[x][y]='A';
 	liczba_armii++;
 	armia[liczba_armii].ciezka_jazda=5;
 	armia[liczba_armii].pikinierzy=5;
 	armia[liczba_armii].lucznicy=5;
 	armia[liczba_armii].kusznicy=5;
 	armia[liczba_armii].ciezkozbrojni=5;
 	armia[liczba_armii].lekka_jazda=5;
 	armia[liczba_armii].tarany=5;
 	armia[liczba_armii].elity=5;
 	armia[liczba_armii].miasto_domowe=2;
 	armia[liczba_armii].wielkosc=40;
 	armia[liczba_armii].nazwa="ARMIA SMIERCI";
 }
 
}

/////////////////MAPA STOLICY////////////////



while(bmapa_stolicy==true){
	
	przychod_zloto=0;
	przychod_drewno=0;
	przychod_kamien=0;
	przychod_zywnosc=0;
	przychod_wiara=0;
	przychod_nauka=0;
	for(int i=1;i<11;i++)przychod_zloto=przychod_zloto+miasto[i].przychod_zloto;
	if(waluta==true)przychod_zloto=przychod_zloto*1.25;
	for(int i=1;i<11;i++)przychod_drewno=przychod_drewno+miasto[i].przychod_drewno;
	for(int i=1;i<11;i++)przychod_kamien=przychod_kamien+miasto[i].przychod_kamien;
	if(huta.lvl>=1)przychod_kamien=przychod_kamien+przychod_kamien*0.3;
	for(int i=1;i<11;i++)przychod_zywnosc=przychod_zywnosc+miasto[i].przychod_zywnosc;
	if(hodowla==true)przychod_zywnosc=przychod_zywnosc*1.25;
	for(int i=1;i<11;i++)miasto[i].przychod_zywnosc=miasto[i].przychod_zywnosc-ludnosc*0.0005;
	for(int i=1;i<11;i++)przychod_wiara=przychod_wiara+miasto[i].przychod_wiara;
	if(ewangelizacja==true)przychod_wiara=przychod_wiara*1.25;
	for(int i=1;i<11;i++)przychod_nauka=przychod_nauka+miasto[i].przychod_nauka;
	if(gildie==true)przychod_nauka=przychod_nauka*1.25;
         cls();
	
	if(technologie==false){
	
         cls();
         cout << endl <<"                MAPA STOLICY"<< endl << endl;



		
for(int i=x-19;i<=x+19;i++){
	cout << "   ";
        for(int j=y-19;j<=y+19;j++){
        		if(j==(y-19) || i==(x-19) || j==(y+19) || i==(x+19))cout << blok;
        		else{
                      	
                if(i==x && j==y){
                        SetConsoleTextAttribute( hOut,  BACKGROUND_RED );
                        cout << mapa_stolicy[i][j];
                        SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa_stolicy[i][j]==dom){
                                    SetConsoleTextAttribute( hOut, 2 );
                                    cout << mapa_stolicy[i][j];
                                    SetConsoleTextAttribute( hOut, 8 );
                        }else{
                                    
                if(mapa_stolicy[i][j]==dom2){
                                     SetConsoleTextAttribute( hOut, 10 );
                                    cout << mapa_stolicy[i][j];
                                    SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa_stolicy[i][j]==woda){
                                     SetConsoleTextAttribute( hOut, 9  );
                                    cout << mapa_stolicy[i][j];
                                    SetConsoleTextAttribute( hOut, 8 );
                        }else{
                if(mapa_stolicy[i][j]==gora){
                                     SetConsoleTextAttribute( hOut, 7 | BACKGROUND_GREEN );
                                     cout << mapa_stolicy[i][j];
                                     SetConsoleTextAttribute( hOut, 8 );
                        }else{
                        	
                        	if(mapa_stolicy[i][j]==prosto_dol || mapa_stolicy[i][j]==prosto_bok || mapa_stolicy[i][j]==skret_lewo_gora || mapa_stolicy[i][j]==skret_lewo_dol || mapa_stolicy[i][j]==skret_prawo_gora
							|| mapa_stolicy[i][j]==skret_prawo_dol || mapa_stolicy[i][j]==skrzyzowanie || mapa_stolicy[i][j]==skrzyzowanie_gora || mapa_stolicy[i][j]==skrzyzowanie_lewo
							|| mapa_stolicy[i][j]==skrzyzowanie_prawo || mapa_stolicy[i][j]==skrzyzowanie_dol){
							SetConsoleTextAttribute( hOut, 7 | BACKGROUND_GREEN );
							cout << mapa_stolicy[i][j];
							SetConsoleTextAttribute( hOut, 8 );
							}else{
							
                cout << mapa_stolicy[i][j];
                
                } 
                }
            	}
            	}
            	}
            	}
            	}
                }
         
			
                
        cout << endl;
        }
    
    	
    	        cout << endl;
cout << "( " << y-21 <<" , "<<x-22<<" )   "; 

cout << endl << endl;
cout << "Jestes w miescie " << miasto[1].nazwa;
SetConsoleTextAttribute( hOut, 10 );
gotoxy(8,60);
cout << "Zywnosc: " << zywnosc<<"("<<miasto[1].przychod_zywnosc<<")" <<"  Drewno: " << drewno <<"("<<miasto[1].przychod_drewno<<")" <<
 "  Kamien: " << kamien<<"("<<miasto[1].przychod_kamien<<")" << "  Wiara: " << wiara <<"("<<miasto[1].przychod_wiara<<")" << "  Max. Zolnierzy: " << max_zolnierzy <<"("<<liczba_zolnierzy<<")"<< "  Zloto: " 
 << zloto << "("<<miasto[1].przychod_zloto<<")" <<"  Produckja: " << miasto[1].produkcja <<"("<<miasto[1].przychod_produkcja
 <<")" << "  Ludnosc: "<<miasto[1].ludnosc << "  Nauka: " << nauka<<"("<<miasto[1].przychod_nauka<<")"<<"  Obrona: "<<miasto[1].obrona;
SetConsoleTextAttribute( hOut, 8 );
	if(menu_budowy==true || rozbudowa==true){
gotoxy(55,1);
if(menu_budowy==true && rozbudowa==false)
cout << "MENU BUDOWY                    ";
if(rozbudowa==true){
cout << "MENU ROZBUDOWY                 ";
rozbudowlanka(x0);

}
gotoxy(45,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(45,4);
cout <<blok<< "                          "<<blok;
gotoxy(45,5);
if(x0==0){
cout<< blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Ratusz ("<<ratusz.lvl<<"/5)           ";
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else{
if(ratusz.budowa==true)
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Ratusz ("<<ratusz.lvl<<"/5)           "<<blok;
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Rynek ("<<rynek.lvl<<"/3)            "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else{
if(rynek.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Rynek ("<<rynek.lvl<<"/3)            "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"Dzielnica Mieszkalna ("<<mieszkalna.lvl<<"/3)"; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "Dzielnica Mieszkalna ("<<mieszkalna.lvl<<"/3)"<<blok; 
SetConsoleTextAttribute( hOut, 8 );

gotoxy(45,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<" Dzielnica Handlowa ("<<handlowa.lvl<<"/3) "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< " Dzielnica Handlowa ("<<handlowa.lvl<<"/3) "<<blok; 
SetConsoleTextAttribute( hOut, 8 );

gotoxy(45,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Dzielnica Naukowa ("<<naukowa.lvl<<"/3)"; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<<"   Dzielnica Naukowa ("<<naukowa.lvl<<"/3)"<<blok; 
SetConsoleTextAttribute( hOut, 8 );

gotoxy(45,10);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<" Dzielnica Wojskowa ("<<wojskowa.lvl<<"/3) "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<<" Dzielnica Wojskowa ("<<wojskowa.lvl<<"/3) "<<blok; 
SetConsoleTextAttribute( hOut, 8 );

gotoxy(45,11);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<" Dzielnica Religijna ("<<religijna.lvl<<"/3)"; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<<" Dzielnica Religijna ("<<religijna.lvl<<"/3)"<<blok; 
SetConsoleTextAttribute( hOut, 8 );

gotoxy(45,12);
if(x0==7){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"Dzielnica Rekreacyjna("<<rekreacyjna.lvl<<"/3)"; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<<"Dzielnica Rekreacyjna("<<rekreacyjna.lvl<<"/3)"<<blok; 
SetConsoleTextAttribute( hOut, 8 );

gotoxy(45,13);
if(x0==8){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Szkola ("<<szkola.lvl<<"/2)           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(szkola.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Szkola ("<<szkola.lvl<<"/2)           "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,14);
if(x0==9){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Akademia ("<<akademia.lvl<<"/2)         "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(akademia.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Akademia ("<<akademia.lvl<<"/2)         "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,15);
if(x0==10){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kapitol ("<<kapitol.lvl<<"/5)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(kapitol.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Kapitol ("<<kapitol.lvl<<"/5)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,16);
if(x0==11){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Mur ("<<mur.lvl<<"/3)              "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Mur ("<<mur.lvl<<"/3)              "<<blok; 
SetConsoleTextAttribute( hOut, 8 );

gotoxy(45,17);
if(x0==12){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Koszary ("<<koszary.lvl<<"/4)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(koszary.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Koszary ("<<koszary.lvl<<"/4)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,18);
if(x0==13){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Huta ("<<huta.lvl<<"/2)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(huta.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Huta ("<<huta.lvl<<"/2)             "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,19);
if(x0==14){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Oboz Najemnikow ("<<oboz.lvl<<"/3)  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(oboz.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Oboz Najemnikow ("<<oboz.lvl<<"/3)  "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,20);
if(x0==15){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Bank ("<<bank.lvl<<"/2)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(bank.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Bank ("<<bank.lvl<<"/2)             "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,21);
if(x0==16){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Gildia ("<<gildia.lvl<<"/3)           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(gildia.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Gildia ("<<gildia.lvl<<"/3)           "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,22);
if(x0==17){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Biblioteka ("<<biblioteka.lvl<<"/2)       "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(biblioteka.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Biblioteka ("<<biblioteka.lvl<<"/2)       "<<blok;
SetConsoleTextAttribute( hOut, 8 );
} 
gotoxy(45,23);
if(x0==18){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Park ("<<park.lvl<<"/3)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(park.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Park ("<<park.lvl<<"/3)             "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,24);
if(x0==19){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Pomnik ("<<pomnik.lvl<<"/3)           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(pomnik.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Pomnik ("<<pomnik.lvl<<"/3)           "<<blok;
SetConsoleTextAttribute( hOut, 8 );
} 
gotoxy(45,25);
if(x0==20){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ambasada ("<<ambasada.lvl<<"/3)         "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(ambasada.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Ambasada ("<<ambasada.lvl<<"/3)         "<<blok;
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,26);
if(x0==21){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Port ("<<port.lvl<<"/3)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(port.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Port ("<<port.lvl<<"/3)             "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
} 
gotoxy(45,27);
if(x0==22){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Teatr ("<<teatr.lvl<<"/2)            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(teatr.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Teatr ("<<teatr.lvl<<"/2)            "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,28);
if(x0==23){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Droga ("<<droga.lvl<<"/2)            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<<"   Droga ("<<droga.lvl<<"/2)            "<<blok; 
SetConsoleTextAttribute( hOut, 8 );

gotoxy(45,29);
if(x0==24){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Tawerna ("<<tawerna.lvl<<"/3)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(tawerna.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Tawerna ("<<tawerna.lvl<<"/3)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,30);
if(x0==25){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Magazyn ("<<magazyn.lvl<<"/4)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(magazyn.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Magazyn ("<<magazyn.lvl<<"/4)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,31);
if(x0==26){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Mlyn ("<<mlyn.lvl<<"/4)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(mlyn.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Mlyn ("<<mlyn.lvl<<"/4)             "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,32);
if(x0==27){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Plac ("<<plac.lvl<<"/1)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(plac.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Plac ("<<plac.lvl<<"/1)             "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,33);
if(x0==28){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Tartak ("<<tartakb.lvl<<"/4)           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(tartakb.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Tartak ("<<tartakb.lvl<<"/4)           "<<blok;
SetConsoleTextAttribute( hOut, 8 );
} 
gotoxy(45,34);
if(x0==29){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kamieniarz ("<<kamieniarz.lvl<<"/4)       "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(kamieniarz.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Kamieniarz ("<<kamieniarz.lvl<<"/4)       "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,35);
if(x0==30){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kolos ("<<kolos.lvl<<"/1)            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(kolos.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Kolos ("<<kolos.lvl<<"/1)            "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,36);
if(x0==31){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kosciol ("<<kosciol.lvl<<"/3)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(kosciol.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Kosciol ("<<kosciol.lvl<<"/3)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,37);
if(x0==32){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Katedra ("<<katedra.lvl<<"/3)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(katedra.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Katedra ("<<katedra.lvl<<"/3)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,38);
if(x0==33){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Skarbiec ("<<skarbiec.lvl<<"/3)         "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(skarbiec.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Skarbiec ("<<skarbiec.lvl<<"/3)         "<<blok;
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,39);
if(x0==34){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Fort ("<<fort.lvl<<"/4)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(fort.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Fort ("<<fort.lvl<<"/4)             "<<blok;  
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,40);
if(x0==35){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Weglarnia ("<<weglarnia.lvl<<"/2)        "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(weglarnia.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Weglarnia ("<<weglarnia.lvl<<"/2)        "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,41);
if(x0==36){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Warsztat ("<<warsztat.lvl<<"/2)         "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(warsztat.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Warsztat ("<<warsztat.lvl<<"/2)         "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,42);
if(x0==37){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Stajnia ("<<stajnia.lvl<<"/4)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(stajnia.budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Stajnia ("<<stajnia.lvl<<"/4)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(45,43);
if(x0==38){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Krzak                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Krzak                  "<<blok;

gotoxy(45,44);
if(x0==39){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Zburz Teren            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Zburz Teren            "<<blok;
gotoxy(45,45);
if(x0==40){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Woda                   "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Woda                   "<<blok;
gotoxy(45,46);
if(x0==41){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Powrot                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Powrot                 "<<blok;
gotoxy(45,47);
cout <<blok<< "                          "<<blok;
gotoxy(45,48);
for(int i=0;i<28;i++)cout << blok;
}


	if(menu_stolica==true){
gotoxy(55,1);
cout << "MENU MIASTA                    ";
gotoxy(45,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(45,4);
cout <<blok<< "                          "<<blok;
gotoxy(45,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Mapa Swiata            "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout << blok<<"   Mapa Swiata            "<<blok; 
gotoxy(45,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout << "   Buduj                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout <<blok<< "   Buduj                  "<<blok; 
gotoxy(45,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Rekrutuj               "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Rekrutuj               "<<blok; 

gotoxy(45,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Plac Manewrowy         "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Plac Manewrowy         "<<blok; 
gotoxy(45,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Najmij jednostki       "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Najmij jednostki       "<<blok; 
gotoxy(45,10);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Zmien nazwe            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Zmien nazwe            "<<blok; 

gotoxy(45,11);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Technologie            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Technologie            "<<blok; 
gotoxy(45,12);
if(x0==7){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Rozbudowa              "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Rozbudowa              "<<blok; 
gotoxy(45,13);
cout <<blok<< "                          "<<blok;
gotoxy(45,14);
for(int i=0;i<28;i++)cout << blok;
}

	if(rekrutacja==true){
gotoxy(55,1);
cout << "REKRUTACJA JEDNOSTEK                    ";
rekrutowanka(x0);
gotoxy(45,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(45,4);
cout <<blok<< "                          "<<blok;
gotoxy(45,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Robotnik               "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout << blok<<"   Robotnik               "<<blok; 
gotoxy(45,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout << "   Osadnik                "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout <<blok<< "   Osadnik                "<<blok; 
gotoxy(45,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Pikinier               "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Pikinier               "<<blok; 

gotoxy(45,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lucznik                "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lucznik                "<<blok; 
gotoxy(45,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kusznik                "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Kusznik                "<<blok; 
gotoxy(45,10);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezkozbrojny          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezkozbrojny          "<<blok; 

gotoxy(45,11);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lekka Jazda            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lekka Jazda            "<<blok; 
gotoxy(45,12);
if(x0==7){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezka Jazda           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezka Jazda           "<<blok;
gotoxy(45,13);
if(x0==8){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Taran                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Taran                  "<<blok;
gotoxy(45,14);
if(x0==9){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Elita                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Elita                  "<<blok; 
gotoxy(45,15);
if(x0==10){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Powrot                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Powrot                 "<<blok; 
gotoxy(45,16);
cout <<blok<< "                          "<<blok;
gotoxy(45,17);
for(int i=0;i<28;i++)cout << blok;
}

	if(bplac==true){
		gotoxy(50,1);
cout << "NAZWA/ILOSC POSIADANYCH/DO ARMII                    ";
rekrutowanka(x0);
pokaz_armie(armia[liczba_armii+1], xm);
gotoxy(45,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(45,4);
cout <<blok<< "                          "<<blok;
gotoxy(45,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Pikinier / "<<sjednostki[0][2].ilosc<<" / "<<armia[liczba_armii+1].pikinierzy<<"       "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Pikinier / "<<sjednostki[0][2].ilosc<<" / "<<armia[liczba_armii+1].pikinierzy<<"       "<<blok; 

gotoxy(45,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lucznik / "<<sjednostki[0][3].ilosc<<" / "<<armia[liczba_armii+1].lucznicy<<"        "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<<"   Lucznik / "<<sjednostki[0][3].ilosc<<" / "<<armia[liczba_armii+1].lucznicy<<"        ";
gotoxy(45,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kusznik / "<<sjednostki[0][4].ilosc<<" / "<<armia[liczba_armii+1].kusznicy<<"        "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Kusznik / "<<sjednostki[0][4].ilosc<<" / "<<armia[liczba_armii+1].kusznicy<<"        "<<blok; 
gotoxy(45,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezkozbrojny / "<<sjednostki[0][5].ilosc<<" / "<<armia[liczba_armii+1].ciezkozbrojni<<"  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezkozbrojny / "<<sjednostki[0][5].ilosc<<" / "<<armia[liczba_armii+1].ciezkozbrojni<<"  "<<blok; 

gotoxy(45,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lekka Jazda / "<<sjednostki[0][6].ilosc<<" / "<<armia[liczba_armii+1].lekka_jazda<<"    "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lekka Jazda / "<<sjednostki[0][6].ilosc<<" / "<<armia[liczba_armii+1].lekka_jazda<<"    "<<blok; 
gotoxy(45,10);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezka Jazda / "<<sjednostki[0][7].ilosc<<" / "<<armia[liczba_armii+1].ciezka_jazda<<"   "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezka Jazda / "<<sjednostki[0][7].ilosc<<" / "<<armia[liczba_armii+1].ciezka_jazda<<"   "<<blok;
gotoxy(45,11);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Taran / "<<sjednostki[0][8].ilosc<<" / "<<armia[liczba_armii+1].tarany<<"          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Taran / "<<sjednostki[0][8].ilosc<<" / "<<armia[liczba_armii+1].tarany<<"          "<<blok;
gotoxy(45,12);
if(x0==7){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Elita / "<<sjednostki[0][9].ilosc<<" / "<<armia[liczba_armii+1].elity<<"          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Elita / "<<sjednostki[0][9].ilosc<<" / "<<armia[liczba_armii+1].elity<<"          "<<blok; 
gotoxy(45,13);
if(x0==8){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Powrot                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Powrot                 "<<blok; 
gotoxy(45,14);
cout <<blok<< "                          "<<blok;
gotoxy(45,15);
for(int i=0;i<28;i++)cout << blok;
	}

	if(najmij==true){
		gotoxy(55,1);
cout << "REKRUTACJA JEDNOSTEK                    ";
najmowanka(x0);
gotoxy(45,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(45,4);
cout <<blok<< "                          "<<blok;
gotoxy(45,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Robotnik               "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout << blok<<"   Robotnik               "<<blok; 
gotoxy(45,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout << "   Osadnik                "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout <<blok<< "   Osadnik                "<<blok; 
gotoxy(45,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Pikinier               "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Pikinier               "<<blok; 

gotoxy(45,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lucznik                "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lucznik                "<<blok; 
gotoxy(45,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kusznik                "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Kusznik                "<<blok; 
gotoxy(45,10);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezkozbrojny          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezkozbrojny          "<<blok; 

gotoxy(45,11);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lekka Jazda            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lekka Jazda            "<<blok; 
gotoxy(45,12);
if(x0==7){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezka Jazda           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezka Jazda           "<<blok;
gotoxy(45,13);
if(x0==8){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Taran                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Taran                  "<<blok;
gotoxy(45,14);
if(x0==9){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Elita                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Elita                  "<<blok; 
gotoxy(45,15);
if(x0==10){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Powrot                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Powrot                 "<<blok; 
gotoxy(45,16);
cout <<blok<< "                          "<<blok;
gotoxy(45,17);
for(int i=0;i<28;i++)cout << blok;

	}

gotoxy(8,62);
		cout << "BUDOWA_MIASTO " << budowa_miasto << "  x0 " << x0 << "  bufor budowy " << bufor_budowa_miasto << "  ratuszlvl "<<ratusz.lvl;
    	
    	
    	ster=getch();
    			if(budowa_miasto==true){
		for(int i=0;i<80;i++){
			for(int j=0;j<150;j++){
		mapa_stolicy[i][j]=bufor_miasta[i][j];
				}
			}
			
		}
		
    	
if(ster==KEY_DOWN && x0!=7 && menu_stolica==true || ster==KEY_DOWN && x0!=41 && menu_budowy==true || ster==KEY_DOWN && x0!=41 && rozbudowa==true || ster==KEY_DOWN && x0!=10 && rekrutacja==true || ster==KEY_DOWN && x0!=10 && najmij==true|| ster==KEY_DOWN && x0!=8 && bplac==true){
	x0++;
	cls();
	continue;


}
if(ster==KEY_UP && x0!=0){
x0--;
cls();
continue;

}

    	
if(ster=='w' && mapa_stolicy[x-1][y]!='@' && mapa_stolicy[x-1][y]!=stolica){
              x--;
              }
 if(ster=='s' && mapa_stolicy[x+1][y]!='@'&& mapa_stolicy[x+1][y]!=stolica){
              x++;
              }
if(ster=='a' && mapa_stolicy[x][y-1]!='@'&& mapa_stolicy[x][y-1]!=stolica){
              y--;
              }
if(ster=='d' && mapa_stolicy[x][y+1]!='@'&& mapa_stolicy[x][y+1]!=stolica){
              y++;
              }
    	
    	if(ster=='.' && ksztalt<1000)ksztalt++;
    	if(ster==','){
    		if(ksztalt==0)ksztalt=1000;
    		else
    		ksztalt--;
		}
    

    	if(ster=='q' && x0==0 && menu_stolica==true){
    menu=true;
	mapa_glowna=true;
	bmapa_stolicy=false;
	x=xd;
	y=yd;
	system("CLS");
		}
		
		if(ster==27){
			menu_stolica=true;
			rozbudowa=false;
			menu_budowy=false;
			rekrutacja=false;
			bplac=false;
			najmij=false;
			x0=0;
			system("CLS");
		}
		
		if(ster=='q' && x0==2 && menu_stolica==true){
			menu_stolica=false;
			rekrutacja=true;
			x0=0;
			system("CLS");
			continue;
		}
		if(ster=='q' && x0==10 && rekrutacja==true){
			menu_stolica=true;
			rekrutacja=false;
			x0=0;
			system("CLS");
			continue;
		}
		
		if(ster=='q' && x0==7 && menu_stolica==true){
			menu_stolica=false;
			rozbudowa=true;
			system("CLS");
			x0=40;
			continue;
		}
		
		if(ster=='q' && x0==6 && menu_stolica==true){
			menu_stolica=false;
			technologie=true;
			system("CLS");
			x0=0;
		}
    	
    	if(ster=='q' && x0==5 && menu_stolica==true){

	gotoxy(54,25);
	for(int i=0;i<40;i++)cout << blok;
	gotoxy(54,26);
	cout << blok;
	for(int i=0;i<38;i++)cout<< " ";
	cout << blok;
	gotoxy(54,28);
	cout << blok;
	for(int i=0;i<38;i++)cout<< " ";
	cout << blok;
	gotoxy(54,29);
	for(int i=0;i<40;i++)cout << blok;
	gotoxy(90,27);
	cout << "   " << blok;
	gotoxy(54,27);
	cout <<blok<< "  Wpisz nazwe miasta: ";
	getline(cin, miasto[1].nazwa);

	gotoxy(54,27);
	for(int i=0;i<28;i++)cout << blok;

	system("CLS");
	continue;

		}
		
		if(ster=='q' && x0==1 && menu_stolica==true){
			menu_stolica=false;
			menu_budowy=true;
			system("CLS");
			x0=0;
			continue;
		}
		
		if(ster=='q' && x0==41 && menu_budowy==true){
			menu_stolica=true;
			menu_budowy=false;
			x0=0;
			budowa_miasto=false;
			system("CLS");
			continue;
		}
		
				
		if(ster=='q' && x0==41 && rozbudowa==true){
			menu_stolica=true;
			rozbudowa=false;
			x0=0;
			system("CLS");
			continue;
		}
		if(ster=='q' && x0==4 && menu_stolica==true && oboz.lvl>0){
			menu_stolica=false;
			najmij=true;
			x0=0;
			system("CLS");
			continue;
		}
		
				
		if(ster=='q' && x0==10 && najmij==true){
			menu_stolica=true;
			najmij=false;
			x0=0;
			system("CLS");
			continue;
		}
		if(ster=='q' && x0==3 && menu_stolica==true && plac.lvl==1){
			menu_stolica=false;
			bplac=true;
			x0=0;
			system("CLS");
			continue;
		}
		if(ster=='q' && x0==8 && bplac==true && plac.lvl==1){
			menu_stolica=true;
			bplac=false;
			x0=0;
			sjednostki[0][2].ilosc=sjednostki[0][2].ilosc+armia[liczba_armii+1].pikinierzy;
			liczba_zolnierzy=liczba_zolnierzy-armia[liczba_armii+1].pikinierzy*pikinier[xm].wielkosc;
			armia[liczba_armii+1].pikinierzy=0;
			sjednostki[0][3].ilosc=sjednostki[0][3].ilosc+armia[liczba_armii+1].lucznicy;
			liczba_zolnierzy=liczba_zolnierzy-armia[liczba_armii+1].lucznicy*lucznik[xm].wielkosc;
			armia[liczba_armii+1].lucznicy=0;
			sjednostki[0][4].ilosc=sjednostki[0][4].ilosc+armia[liczba_armii+1].kusznicy;
			liczba_zolnierzy=liczba_zolnierzy-armia[liczba_armii+1].kusznicy*kusznik[xm].wielkosc;
			armia[liczba_armii+1].kusznicy=0;
			sjednostki[0][5].ilosc=sjednostki[0][5].ilosc+armia[liczba_armii+1].ciezkozbrojni;
			liczba_zolnierzy=liczba_zolnierzy-armia[liczba_armii+1].ciezkozbrojni*ciezkozbrojny[xm].wielkosc;
			armia[liczba_armii+1].ciezkozbrojni=0;
			sjednostki[0][6].ilosc=sjednostki[0][6].ilosc+armia[liczba_armii+1].lekka_jazda;
			liczba_zolnierzy=liczba_zolnierzy-armia[liczba_armii+1].lekka_jazda*lekka_jazda[xm].wielkosc;
			armia[liczba_armii+1].lekka_jazda=0;
			sjednostki[0][7].ilosc=sjednostki[0][7].ilosc+armia[liczba_armii+1].ciezka_jazda;
			liczba_zolnierzy=liczba_zolnierzy-armia[liczba_armii+1].ciezka_jazda*ciezka_jazda[xm].wielkosc;
			armia[liczba_armii+1].ciezka_jazda=0;
			sjednostki[0][8].ilosc=sjednostki[0][8].ilosc+armia[liczba_armii+1].tarany;
			liczba_zolnierzy=liczba_zolnierzy-armia[liczba_armii+1].tarany*taran[xm].wielkosc;
			armia[liczba_armii+1].tarany=0;
			sjednostki[0][9].ilosc=sjednostki[0][9].ilosc+armia[liczba_armii+1].elity;
			liczba_zolnierzy=liczba_zolnierzy-armia[liczba_armii+1].elity*elita.wielkosc;
			armia[liczba_armii+1].elity=0;
			armia[liczba_armii+1].wielkosc-=pikinier[xm].wielkosc;
			armia[liczba_armii+1].wielkosc-=lucznik[xm].wielkosc;
			armia[liczba_armii+1].wielkosc-=kusznik[xm].wielkosc;
			armia[liczba_armii+1].wielkosc-=ciezkozbrojny[xm].wielkosc;
			armia[liczba_armii+1].wielkosc-=lekka_jazda[xm].wielkosc;
			armia[liczba_armii+1].wielkosc-=ciezka_jazda[xm].wielkosc;
			armia[liczba_armii+1].wielkosc-=taran[xm].wielkosc;
			armia[liczba_armii+1].wielkosc-=elita.wielkosc;
			
			system("CLS");
			continue;			
		}
		
		////////////////////////////////////budowanko////////////////////////////////////////////////////////////
		if(ster=='q' && x0==0 && menu_budowy==true && ratusz.lvl==0){
			budowlanka(ratusz,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto, x0, ksztalt);
			budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==0 && ratusz.lvl==0){
		
					
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=ratusz.wyglad[i-x][j-y];
				if(ratusz.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
		if(ster=='e' && budowa_miasto==true && bufor_budowa_miasto==0 && drewno>=ratusz.koszt_drewno && kamien>=ratusz.koszt_kamien && zywnosc>=ratusz.koszt_zywnosc && zloto>=ratusz.koszt_zloto && miasto[1].produkcja>=ratusz.koszt_produkcja && ratusz.lvl==0)
		{
		zbuduj(ratusz, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			ratusz.lvl=1;
			zwieksz_koszt(ratusz);
		}
		if(ster=='q' && x0==0 && rozbudowa==true && ratusz.lvl==1 && kapitol.lvl>=1 && drewno>=ratusz.koszt_drewno && kamien>=ratusz.koszt_kamien && zywnosc>=ratusz.koszt_zywnosc && zloto>=ratusz.koszt_zloto && miasto[1].produkcja>=ratusz.koszt_produkcja){
			ratusz.lvl++;
			rozbuduj(ratusz,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(ratusz);
			josadnik.koszt_produkcja-=50;
			jrobotnik[xm].koszt_produkcja-=25;
			zwieksz_przychod(ratusz,&przychod_nauka,&max_zolnierzy);
		}
		if(ster=='q' && x0==0 && rozbudowa==true && ratusz.lvl==2 && kapitol.lvl>=2 && drewno>=ratusz.koszt_drewno && kamien>=ratusz.koszt_kamien && zywnosc>=ratusz.koszt_zywnosc && zloto>=ratusz.koszt_zloto && miasto[1].produkcja>=ratusz.koszt_produkcja){
			ratusz.lvl++;
			rozbuduj(ratusz,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(ratusz);
			josadnik.koszt_produkcja-=50;
			jrobotnik[xm].koszt_produkcja-=25;
			zwieksz_przychod(ratusz,&przychod_nauka,&max_zolnierzy);
		}
				if(ster=='q' && x0==0 && rozbudowa==true && ratusz.lvl==3 && kapitol.lvl>=3 && drewno>=ratusz.koszt_drewno && kamien>=ratusz.koszt_kamien && zywnosc>=ratusz.koszt_zywnosc && zloto>=ratusz.koszt_zloto && miasto[1].produkcja>=ratusz.koszt_produkcja){
			ratusz.lvl++;
			rozbuduj(ratusz,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(ratusz);
			josadnik.koszt_produkcja-=50;
			jrobotnik[xm].koszt_produkcja-=25;
			zwieksz_przychod(ratusz,&przychod_nauka,&max_zolnierzy);
		}
				if(ster=='q' && x0==0 && rozbudowa==true && ratusz.lvl==4 && kapitol.lvl>=4 && drewno>=ratusz.koszt_drewno && kamien>=ratusz.koszt_kamien && zywnosc>=ratusz.koszt_zywnosc && zloto>=ratusz.koszt_zloto && miasto[1].produkcja>=ratusz.koszt_produkcja){
			ratusz.lvl++;
			rozbuduj(ratusz,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(ratusz);
			josadnik.koszt_produkcja-=50;
			jrobotnik[xm].koszt_produkcja-=25;
			zwieksz_przychod(ratusz,&przychod_nauka,&max_zolnierzy);
		}
		//////////////////
				if(ster=='q' && x0==1 && menu_budowy==true && rynek.lvl==0){
				budowlanka(rynek,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
			budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==1 && rynek.lvl==0&& ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=rynek.wyglad[i-x][j-y];
				if(rynek.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
		if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=1 && bufor_budowa_miasto==1 && drewno>=rynek.koszt_drewno && kamien>=rynek.koszt_kamien && zywnosc>=rynek.koszt_zywnosc && zloto>=rynek.koszt_zloto && miasto[1].produkcja>=rynek.koszt_produkcja && rynek.lvl==0)
		{
		zbuduj(rynek, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
		&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
		rynek.lvl=1;
		zwieksz_koszt(rynek);
		}
		if(ster=='q' && x0==1 && rozbudowa==true &&ratusz.lvl>=2 && rynek.lvl==1 && drewno>=rynek.koszt_drewno && kamien>=rynek.koszt_kamien && zywnosc>=rynek.koszt_zywnosc && zloto>=rynek.koszt_zloto && miasto[1].produkcja>=rynek.koszt_produkcja){
			rynek.lvl++;
			rozbuduj(rynek,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(rynek);
			zwieksz_przychod(rynek,&przychod_nauka,&max_zolnierzy);
		}
		if(ster=='q' && x0==1 && rozbudowa==true &&ratusz.lvl>=4 &&waluta==true && rynek.lvl==2 && drewno>=rynek.koszt_drewno && kamien>=rynek.koszt_kamien && zywnosc>=rynek.koszt_zywnosc && zloto>=rynek.koszt_zloto && miasto[1].produkcja>=rynek.koszt_produkcja){
			rynek.lvl++;
			rozbuduj(rynek,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(rynek);
		}
				//////////////////
				if(ster=='q' && x0==2 && menu_budowy==true){
						budowlanka(mieszkalna,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
			budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==2&& ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=mieszkalna.wyglad[i-x][j-y];
				if(mieszkalna.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=1 && bufor_budowa_miasto==2 && drewno>=mieszkalna.koszt_drewno && kamien>=mieszkalna.koszt_kamien && zywnosc>=mieszkalna.koszt_zywnosc && zloto>=mieszkalna.koszt_zloto && miasto[1].produkcja>=mieszkalna.koszt_produkcja)
		{
		zbuduj(mieszkalna, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			mieszkalna.lvl=1;
			zwieksz_koszt(mieszkalna);
		}	
		if(ster=='q' && rozbudowa==true && x0==2&& mieszkalna.lvl==1&&ratusz.lvl>=2 && drewno>=mieszkalna.koszt_drewno && kamien>=mieszkalna.koszt_kamien && zywnosc>=mieszkalna.koszt_zywnosc && zloto>=mieszkalna.koszt_zloto && miasto[1].produkcja>=mieszkalna.koszt_produkcja){
		
			mieszkalna.lvl++;
			rozbuduj(mieszkalna,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(mieszkalna);
			zwieksz_przychod(mieszkalna,&przychod_nauka,&max_zolnierzy);
		}
		if(ster=='q' && rozbudowa==true && x0==2&& mieszkalna.lvl==2&&ratusz.lvl>=3 && drewno>=mieszkalna.koszt_drewno && kamien>=mieszkalna.koszt_kamien && zywnosc>=mieszkalna.koszt_zywnosc && zloto>=mieszkalna.koszt_zloto && miasto[1].produkcja>=mieszkalna.koszt_produkcja){
		
			mieszkalna.lvl++;
			rozbuduj(mieszkalna,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(mieszkalna);
			zwieksz_przychod(mieszkalna,&przychod_nauka,&max_zolnierzy);
		}
			//////////////////
				if(ster=='q' && x0==3 && menu_budowy==true){
							budowlanka(handlowa,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==3&& ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=handlowa.wyglad[i-x][j-y];
				if(handlowa.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=2 && bufor_budowa_miasto==3 && drewno>=handlowa.koszt_drewno && kamien>=handlowa.koszt_kamien && zywnosc>=handlowa.koszt_zywnosc && zloto>=handlowa.koszt_zloto && miasto[1].produkcja>=handlowa.koszt_produkcja)
		{
		zbuduj(handlowa, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			handlowa.lvl=1;
			zwieksz_koszt(handlowa);
		}	
		if(ster=='q' && rozbudowa==true&& x0==3&& handlowa.lvl==1&&ratusz.lvl>=3 && drewno>=handlowa.koszt_drewno && kamien>=handlowa.koszt_kamien && zywnosc>=handlowa.koszt_zywnosc && zloto>=handlowa.koszt_zloto && miasto[1].produkcja>=handlowa.koszt_produkcja){
			handlowa.lvl++;
			rozbuduj(handlowa,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(handlowa);
			zwieksz_przychod(handlowa,&przychod_nauka,&max_zolnierzy);
		}
		if(ster=='q' && rozbudowa==true&& x0==3&& handlowa.lvl==2&&ratusz.lvl>=4 && drewno>=handlowa.koszt_drewno && kamien>=handlowa.koszt_kamien && zywnosc>=handlowa.koszt_zywnosc && zloto>=handlowa.koszt_zloto && miasto[1].produkcja>=handlowa.koszt_produkcja){
		
			handlowa.lvl++;
			rozbuduj(handlowa,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(handlowa);
			zwieksz_przychod(handlowa,&przychod_nauka,&max_zolnierzy);
    	}
			//////////////////
				if(ster=='q' && x0==4 && menu_budowy==true){

								budowlanka(naukowa,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
								budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==4&& ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=naukowa.wyglad[i-x][j-y];
				if(naukowa.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=2 && bufor_budowa_miasto==4 && drewno>=naukowa.koszt_drewno && kamien>=naukowa.koszt_kamien && zywnosc>=naukowa.koszt_zywnosc && zloto>=naukowa.koszt_zloto && miasto[1].produkcja>=naukowa.koszt_produkcja)
		{
		zbuduj(naukowa, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			naukowa.lvl=1;
			zwieksz_koszt(naukowa);
		}	
		if(ster=='q' && rozbudowa==true&& x0==4&& naukowa.lvl==1&&ratusz.lvl>=3 && drewno>=naukowa.koszt_drewno && kamien>=naukowa.koszt_kamien && zywnosc>=naukowa.koszt_zywnosc && zloto>=naukowa.koszt_zloto && miasto[1].produkcja>=naukowa.koszt_produkcja){
			naukowa.lvl++;
			rozbuduj(naukowa,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(naukowa);
			zwieksz_przychod(naukowa,&przychod_nauka,&max_zolnierzy);
		}
		if(ster=='q' && rozbudowa==true&& x0==4&& naukowa.lvl==2&&ratusz.lvl==5 && drewno>=naukowa.koszt_drewno && kamien>=naukowa.koszt_kamien && zywnosc>=naukowa.koszt_zywnosc && zloto>=naukowa.koszt_zloto && miasto[1].produkcja>=naukowa.koszt_produkcja){
		rozbuduj(naukowa,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			naukowa.lvl++;
			zwieksz_koszt(naukowa);
			zwieksz_przychod(naukowa,&przychod_nauka,&max_zolnierzy);
    	}
			//////////////////
				if(ster=='q' && x0==5 && menu_budowy==true){
						budowlanka(wojskowa,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==5&& ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=wojskowa.wyglad[i-x][j-y];
				if(wojskowa.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=2 && bufor_budowa_miasto==5 && drewno>=wojskowa.koszt_drewno && kamien>=wojskowa.koszt_kamien && zywnosc>=wojskowa.koszt_zywnosc && zloto>=wojskowa.koszt_zloto && miasto[1].produkcja>=wojskowa.koszt_produkcja)
		{
		zbuduj(wojskowa, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			wojskowa.lvl=1;
			zwieksz_koszt(wojskowa);
			miasto[1].obrona=miasto[1].obrona+5;
			
		}	
		if(ster=='q' && rozbudowa==true&& x0==5&& wojskowa.lvl==1&&ratusz.lvl>=3 && drewno>=wojskowa.koszt_drewno && kamien>=wojskowa.koszt_kamien && zywnosc>=wojskowa.koszt_zywnosc && zloto>=wojskowa.koszt_zloto && miasto[1].produkcja>=wojskowa.koszt_produkcja){
			wojskowa.lvl++;
			rozbuduj(wojskowa,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(wojskowa);
			zwieksz_przychod(wojskowa,&przychod_nauka,&max_zolnierzy);
			
			miasto[1].obrona=miasto[1].obrona+10;
    	}
    	if(ster=='q' && rozbudowa==true&& x0==5&& wojskowa.lvl==2&&ratusz.lvl>=5 && drewno>=wojskowa.koszt_drewno && kamien>=wojskowa.koszt_kamien && zywnosc>=wojskowa.koszt_zywnosc && zloto>=wojskowa.koszt_zloto && miasto[1].produkcja>=wojskowa.koszt_produkcja){
			wojskowa.lvl++;
			rozbuduj(wojskowa,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(wojskowa);
			zwieksz_przychod(wojskowa,&przychod_nauka,&max_zolnierzy);
			
			miasto[1].obrona=miasto[1].obrona+15;
    	}
			//////////////////
				if(ster=='q' && x0==6 && menu_budowy==true){
							budowlanka(religijna,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==6&& ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=religijna.wyglad[i-x][j-y];
				if(religijna.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=2 && bufor_budowa_miasto==6 && drewno>=religijna.koszt_drewno && kamien>=religijna.koszt_kamien && zywnosc>=religijna.koszt_zywnosc && zloto>=religijna.koszt_zloto && miasto[1].produkcja>=religijna.koszt_produkcja)
		{
		zbuduj(religijna, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			religijna.lvl=1;
			zwieksz_koszt(religijna);
		}	
		if(ster=='q' && rozbudowa==true&& x0==6&& religijna.lvl==2&&ratusz.lvl>=4 && drewno>=religijna.koszt_drewno && kamien>=religijna.koszt_kamien && zywnosc>=religijna.koszt_zywnosc && zloto>=religijna.koszt_zloto && miasto[1].produkcja>=religijna.koszt_produkcja){
			religijna.lvl++;
			rozbuduj(religijna,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(religijna);
			zwieksz_przychod(religijna,&przychod_nauka,&max_zolnierzy);
			

    	}
    	if(ster=='q' && rozbudowa==true&& x0==6&& religijna.lvl==2&&kapitol.lvl==5 && drewno>=religijna.koszt_drewno && kamien>=religijna.koszt_kamien && zywnosc>=religijna.koszt_zywnosc && zloto>=religijna.koszt_zloto && miasto[1].produkcja>=religijna.koszt_produkcja){
			religijna.lvl++;
				rozbuduj(religijna,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(religijna);
			zwieksz_przychod(religijna,&przychod_nauka,&max_zolnierzy);
		

    	}
			//////////////////
				if(ster=='q' && x0==7 && menu_budowy==true){
							budowlanka(rekreacyjna,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==7&& ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=rekreacyjna.wyglad[i-x][j-y];
				if(rekreacyjna.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1&& bufor_budowa_miasto==7 && drewno>=rekreacyjna.koszt_drewno && kamien>=rekreacyjna.koszt_kamien && zywnosc>=rekreacyjna.koszt_zywnosc && zloto>=rekreacyjna.koszt_zloto && miasto[1].produkcja>=rekreacyjna.koszt_produkcja )
		{
		zbuduj(rekreacyjna, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			rekreacyjna.lvl=1;
			zwieksz_koszt(rekreacyjna);
		}	
		if(ster=='q' && rozbudowa==true&& x0==7&& rekreacyjna.lvl==2&&ratusz.lvl>=2 && drewno>=rekreacyjna.koszt_drewno && kamien>=rekreacyjna.koszt_kamien && zywnosc>=rekreacyjna.koszt_zywnosc && zloto>=rekreacyjna.koszt_zloto && miasto[1].produkcja>=rekreacyjna.koszt_produkcja){
			rekreacyjna.lvl++;
			rozbuduj(rekreacyjna,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(rekreacyjna);
			zwieksz_przychod(rekreacyjna,&przychod_nauka,&max_zolnierzy);

    	}
    	if(ster=='q' && rozbudowa==true&& x0==7&& rekreacyjna.lvl==2&&ratusz.lvl>=4 && drewno>=rekreacyjna.koszt_drewno && kamien>=rekreacyjna.koszt_kamien && zywnosc>=rekreacyjna.koszt_zywnosc && zloto>=rekreacyjna.koszt_zloto && miasto[1].produkcja>=rekreacyjna.koszt_produkcja){
			rekreacyjna.lvl++;
			rozbuduj(rekreacyjna,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(rekreacyjna);
			zwieksz_przychod(rekreacyjna,&przychod_nauka,&max_zolnierzy);
			

    	}
			//////////////////
				if(ster=='q' && x0==8 && menu_budowy==true && szkola.lvl==0){
						budowlanka(szkola,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==8&& ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=szkola.wyglad[i-x][j-y];
				if(szkola.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=1 && bufor_budowa_miasto==8 && drewno>=szkola.koszt_drewno && kamien>=szkola.koszt_kamien && zywnosc>=szkola.koszt_zywnosc && zloto>=szkola.koszt_zloto && miasto[1].produkcja>=szkola.koszt_produkcja && szkola.lvl==0)
		{
		zbuduj(szkola, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			szkola.lvl=1;
			zwieksz_koszt(szkola);
		}	
		if(ster=='q' && rozbudowa==true&& x0==8&& szkola.lvl==2&&ratusz.lvl>=3 && drewno>=szkola.koszt_drewno && kamien>=szkola.koszt_kamien && zywnosc>=szkola.koszt_zywnosc && zloto>=szkola.koszt_zloto && miasto[1].produkcja>=szkola.koszt_produkcja){
			szkola.lvl++;
			rozbuduj(szkola,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(szkola);
			zwieksz_przychod(szkola,&przychod_nauka,&max_zolnierzy);
			
    	}
			//////////////////
				if(ster=='q' && x0==9 && menu_budowy==true && akademia.lvl==0){
						budowlanka(akademia,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==9&& ratusz.lvl>=4){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=akademia.wyglad[i-x][j-y];
				if(akademia.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=4 && bufor_budowa_miasto==9 && drewno>=akademia.koszt_drewno && kamien>=akademia.koszt_kamien && zywnosc>=akademia.koszt_zywnosc && zloto>=akademia.koszt_zloto && miasto[1].produkcja>=akademia.koszt_produkcja && akademia.lvl==0)
		{
		zbuduj(akademia, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			akademia.lvl=1;
			zwieksz_koszt(akademia);
		}	
			if(ster=='q' && rozbudowa==true&& x0==9&& akademia.lvl==2&&kapitol.lvl==5 && drewno>=akademia.koszt_drewno && kamien>=akademia.koszt_kamien && zywnosc>=akademia.koszt_zywnosc && zloto>=akademia.koszt_zloto && miasto[1].produkcja>=akademia.koszt_produkcja){
			akademia.lvl++;
			rozbuduj(akademia,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(akademia);
			zwieksz_przychod(akademia,&przychod_nauka,&max_zolnierzy);
			elita.koszt_produkcja-=100;
			elita.koszt_zloto-=50;
    	}
			//////////////////
						if(ster=='q' && x0==10 && menu_budowy==true && kapitol.lvl==0 ){
						budowlanka(kapitol,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==10 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=kapitol.wyglad[i-x][j-y];
				if(kapitol.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' &&ratusz.lvl>=1 && budowa_miasto==true && bufor_budowa_miasto==10 && drewno>=kapitol.koszt_drewno && kamien>=kapitol.koszt_kamien && zywnosc>=kapitol.koszt_zywnosc && zloto>=kapitol.koszt_zloto && miasto[1].produkcja>=kapitol.koszt_produkcja && kapitol.lvl==0)
		{
		zbuduj(kapitol, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			kapitol.lvl=1;
			zwieksz_koszt(kapitol);
		}	
				if(ster=='q'&& x0==10 && rozbudowa==true&& kapitol.lvl==1 && drewno>=kapitol.koszt_drewno && kamien>=kapitol.koszt_kamien && zywnosc>=kapitol.koszt_zywnosc && zloto>=kapitol.koszt_zloto && miasto[1].produkcja>=kapitol.koszt_produkcja){
			kapitol.lvl++;
			rozbuduj(kapitol,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(kapitol);
			zwieksz_przychod(kapitol,&przychod_nauka,&max_zolnierzy);
    	}
				if(ster=='q'&& x0==10 && rozbudowa==true&& kapitol.lvl==2 && drewno>=kapitol.koszt_drewno && kamien>=kapitol.koszt_kamien && zywnosc>=kapitol.koszt_zywnosc && zloto>=kapitol.koszt_zloto && miasto[1].produkcja>=kapitol.koszt_produkcja){
			kapitol.lvl++;
			rozbuduj(kapitol,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(kapitol);
			zwieksz_przychod(kapitol,&przychod_nauka,&max_zolnierzy);
    	}
				if(ster=='q'&& x0==10 && rozbudowa==true&& kapitol.lvl==3 && drewno>=kapitol.koszt_drewno && kamien>=kapitol.koszt_kamien && zywnosc>=kapitol.koszt_zywnosc && zloto>=kapitol.koszt_zloto && miasto[1].produkcja>=kapitol.koszt_produkcja){
			kapitol.lvl++;
			rozbuduj(kapitol,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(kapitol);
			zwieksz_przychod(kapitol,&przychod_nauka,&max_zolnierzy);
			
    	}
				if(ster=='q'&& x0==10 && rozbudowa==true&& kapitol.lvl==4 && drewno>=kapitol.koszt_drewno && kamien>=kapitol.koszt_kamien && zywnosc>=kapitol.koszt_zywnosc && zloto>=kapitol.koszt_zloto && miasto[1].produkcja>=kapitol.koszt_produkcja){
			kapitol.lvl++;
			rozbuduj(kapitol,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(kapitol);
			zwieksz_przychod(kapitol,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
		if(ster=='q' && x0==11 && menu_budowy==true){
							budowlanka(mur,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==11 && ratusz.lvl>=1){
				
			mapa_stolicy[x][y]=osada;
		}
		if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==11 && drewno>=mur.koszt_drewno && kamien>=mur.koszt_kamien && zywnosc>=mur.koszt_zywnosc && zloto>=mur.koszt_zloto && miasto[1].produkcja>=mur.koszt_produkcja && mapa_stolicy[x][y]!=254)
		{
			zloto=zloto-mur.koszt_zloto;
			drewno=drewno-mur.koszt_drewno;
			kamien=kamien-mur.koszt_kamien;
			zywnosc=zywnosc-mur.koszt_zywnosc;
			miasto[1].produkcja=miasto[1].produkcja-mur.koszt_produkcja;
			miasto[1].ludnosc=miasto[1].ludnosc+mur.ludnosc;

			mapa_stolicy[x][y]=osada;
			bufor_miasta[x][y]=mapa_stolicy[x][y];			
			mur.lvl=1;
		
		}	
			if(ster=='q' && budowa_miasto==true&& x0==11&& mur.lvl==1 && ratusz.lvl>=3 && drewno>=mur.koszt_drewno && kamien>=mur.koszt_kamien && zywnosc>=mur.koszt_zywnosc && zloto>=mur.koszt_zloto && miasto[1].produkcja>=mur.koszt_produkcja){
			mur.lvl++;
			rozbuduj(mur,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(mur);
			zwieksz_przychod(mur,&przychod_nauka,&max_zolnierzy);
			
    	}	
		if(ster=='q' && rozbudowa==true&& x0==11&& mur.lvl==2 && ratusz.lvl>=5 && drewno>=mur.koszt_drewno && kamien>=mur.koszt_kamien && zywnosc>=mur.koszt_zywnosc && zloto>=mur.koszt_zloto && miasto[1].produkcja>=mur.koszt_produkcja){
			mur.lvl++;
			rozbuduj(mur,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(mur);
			zwieksz_przychod(mur,&przychod_nauka,&max_zolnierzy);
			
    	}//////////////////
				if(ster=='q' && x0==12 && menu_budowy==true && koszary.lvl==0){
							budowlanka(koszary,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==12 && ratusz.lvl>=1 ){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=koszary.wyglad[i-x][j-y];
				if(koszary.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==12 && drewno>=koszary.koszt_drewno && kamien>=koszary.koszt_kamien && zywnosc>=koszary.koszt_zywnosc && zloto>=koszary.koszt_zloto && miasto[1].produkcja>=koszary.koszt_produkcja && koszary.lvl==0)
		{
		zbuduj(koszary, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			koszary.lvl=1;
			zwieksz_koszt(koszary);
			miasto[1].obrona=miasto[1].obrona+1;
		}	
		if(ster=='q' && rozbudowa==true && x0==12&& koszary.lvl==1 && ratusz.lvl>=2 && drewno>=koszary.koszt_drewno && kamien>=koszary.koszt_kamien && zywnosc>=koszary.koszt_zywnosc && zloto>=koszary.koszt_zloto && miasto[1].produkcja>=koszary.koszt_produkcja){
			koszary.lvl++;
			rozbuduj(koszary,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(koszary);
			zwieksz_przychod(koszary,&przychod_nauka,&max_zolnierzy);
			pikinier[xm].koszt_produkcja=pikinier[xm].koszt_produkcja-25;
    	}	
		if(ster=='q' && rozbudowa==true && x0==12&& koszary.lvl==2 && ratusz.lvl>=4 && drewno>=koszary.koszt_drewno && kamien>=koszary.koszt_kamien && zywnosc>=koszary.koszt_zywnosc && zloto>=koszary.koszt_zloto && miasto[1].produkcja>=koszary.koszt_produkcja){
			koszary.lvl++;
			rozbuduj(koszary,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(koszary);
			zwieksz_przychod(koszary,&przychod_nauka,&max_zolnierzy);
			pikinier[xm].koszt_produkcja=pikinier[xm].koszt_produkcja-25;
			
    	}
    	if(ster=='q' && rozbudowa==true && x0==12&& koszary.lvl==3 && ratusz.lvl>=5 && drewno>=koszary.koszt_drewno && kamien>=koszary.koszt_kamien && zywnosc>=koszary.koszt_zywnosc && zloto>=koszary.koszt_zloto && miasto[1].produkcja>=koszary.koszt_produkcja){
			koszary.lvl++;
			rozbuduj(koszary,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(koszary);
			zwieksz_przychod(koszary,&przychod_nauka,&max_zolnierzy);
			pikinier[xm].koszt_produkcja=pikinier[xm].koszt_produkcja-25;
			
    	}
			//////////////////
				if(ster=='q' && x0==13 && menu_budowy==true && huta.lvl==0){
							budowlanka(huta,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==13&& ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=huta.wyglad[i-x][j-y];
				if(huta.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && bufor_budowa_miasto==13&& ratusz.lvl>=2 && drewno>=huta.koszt_drewno && kamien>=huta.koszt_kamien && zywnosc>=huta.koszt_zywnosc && zloto>=huta.koszt_zloto && miasto[1].produkcja>=huta.koszt_produkcja && huta.lvl==0)
		{
		zbuduj(huta, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			huta.lvl=1;
			zwieksz_koszt(huta);
			
		}	
		if(ster=='q' && rozbudowa==true && x0==13&& huta.lvl==1 && ratusz.lvl>=4 && drewno>=huta.koszt_drewno && kamien>=huta.koszt_kamien && zywnosc>=huta.koszt_zywnosc && zloto>=huta.koszt_zloto && miasto[1].produkcja>=huta.koszt_produkcja){
			huta.lvl++;
			rozbuduj(huta,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(huta);
			zwieksz_przychod(huta,&przychod_nauka,&max_zolnierzy);
			pikinier[xm].koszt_produkcja=pikinier[xm].koszt_produkcja-25;
			
    	}	//////////////////
				if(ster=='q' && x0==14 && menu_budowy==true && oboz.lvl==0){
							budowlanka(oboz,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==14&& ratusz.lvl>=3){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=oboz.wyglad[i-x][j-y];
				if(oboz.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=3 && bufor_budowa_miasto==14 && drewno>=oboz.koszt_drewno && kamien>=oboz.koszt_kamien && zywnosc>=oboz.koszt_zywnosc && zloto>=oboz.koszt_zloto && miasto[1].produkcja>=oboz.koszt_produkcja && oboz.lvl==0)
		{
		zbuduj(oboz, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			oboz.lvl=1;
			pikinier[xm].koszt_zloto=pikinier[xm].koszt_zloto-50;
			lucznik[xm].koszt_zloto=lucznik[xm].koszt_zloto-50;
			kusznik[xm].koszt_zloto=kusznik[xm].koszt_zloto-50;	
			lekka_jazda[xm].koszt_zloto=lekka_jazda[xm].koszt_zloto-50;
			ciezka_jazda[xm].koszt_zloto=ciezka_jazda[xm].koszt_zloto-50;
			ciezkozbrojny[xm].koszt_zloto=ciezkozbrojny[xm].koszt_zloto-50;
			zwieksz_koszt(oboz);
		}	
		if(ster=='q' && rozbudowa==true&& x0==14&& oboz.lvl==1 && ratusz.lvl>=4 && drewno>=oboz.koszt_drewno && kamien>=oboz.koszt_kamien && zywnosc>=oboz.koszt_zywnosc && zloto>=oboz.koszt_zloto && miasto[1].produkcja>=oboz.koszt_produkcja){
			oboz.lvl++;
			rozbuduj(oboz,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(oboz);
			zwieksz_przychod(oboz,&przychod_nauka,&max_zolnierzy);
			pikinier[xm].koszt_zloto=pikinier[xm].koszt_zloto-25;
			lucznik[xm].koszt_zloto=lucznik[xm].koszt_zloto-25;
			kusznik[xm].koszt_zloto=kusznik[xm].koszt_zloto-25;	
			lekka_jazda[xm].koszt_zloto=lekka_jazda[xm].koszt_zloto-25;
			ciezka_jazda[xm].koszt_zloto=ciezka_jazda[xm].koszt_zloto-25;
			ciezkozbrojny[xm].koszt_zloto=ciezkozbrojny[xm].koszt_zloto-25;
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==14&& oboz.lvl==2 && ratusz.lvl>=5 && drewno>=oboz.koszt_drewno && kamien>=oboz.koszt_kamien && zywnosc>=oboz.koszt_zywnosc && zloto>=oboz.koszt_zloto && miasto[1].produkcja>=oboz.koszt_produkcja){
			oboz.lvl++;
			rozbuduj(oboz,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(oboz);
			zwieksz_przychod(oboz,&przychod_nauka,&max_zolnierzy);
			pikinier[xm].koszt_zloto=pikinier[xm].koszt_zloto-25;
			lucznik[xm].koszt_zloto=lucznik[xm].koszt_zloto-25;
			kusznik[xm].koszt_zloto=kusznik[xm].koszt_zloto-25;	
			lekka_jazda[xm].koszt_zloto=lekka_jazda[xm].koszt_zloto-25;
			ciezka_jazda[xm].koszt_zloto=ciezka_jazda[xm].koszt_zloto-25;
			ciezkozbrojny[xm].koszt_zloto=ciezkozbrojny[xm].koszt_zloto-25;
			
    	}	//////////////////
				if(ster=='q' && x0==15 && menu_budowy==true && bank.lvl==0){
						budowlanka(bank,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==15&& ratusz.lvl>=4){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=bank.wyglad[i-x][j-y];
				if(bank.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=4 && bufor_budowa_miasto==15 && drewno>=bank.koszt_drewno && kamien>=bank.koszt_kamien && zywnosc>=bank.koszt_zywnosc && zloto>=bank.koszt_zloto && miasto[1].produkcja>=bank.koszt_produkcja && bank.lvl==0)
		{
		zbuduj(bank, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			bank.lvl=1;
			zwieksz_koszt(bank);
		}	
		if(ster=='q' && rozbudowa==true&& x0==15&& bank.lvl==1 && ratusz.lvl>=5 && drewno>=bank.koszt_drewno && kamien>=bank.koszt_kamien && zywnosc>=bank.koszt_zywnosc && zloto>=bank.koszt_zloto && miasto[1].produkcja>=bank.koszt_produkcja){
			bank.lvl++;
			rozbuduj(bank,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(bank);
			zwieksz_przychod(bank,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==16 && menu_budowy==true && gildia.lvl==0){
							budowlanka(gildia,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==16 && gildie==true && ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=gildia.wyglad[i-x][j-y];
				if(gildia.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && bufor_budowa_miasto==16 && ratusz.lvl>=2 &&gildie==true&& drewno>=gildia.koszt_drewno && kamien>=gildia.koszt_kamien && zywnosc>=gildia.koszt_zywnosc && zloto>=gildia.koszt_zloto && miasto[1].produkcja>=gildia.koszt_produkcja && gildia.lvl==0)
		{
		zbuduj(gildia, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			gildia.lvl=1;
			josadnik.koszt_produkcja=josadnik.koszt_produkcja-50;
			zwieksz_koszt(gildia);
		}	
		if(ster=='q' && rozbudowa==true&& x0==16&& gildia.lvl==1 && ratusz.lvl>=4 && drewno>=gildia.koszt_drewno && kamien>=gildia.koszt_kamien && zywnosc>=gildia.koszt_zywnosc && zloto>=gildia.koszt_zloto && miasto[1].produkcja>=gildia.koszt_produkcja){
			gildia.lvl++;
			rozbuduj(gildia,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(gildia);
			zwieksz_przychod(gildia,&przychod_nauka,&max_zolnierzy);
			josadnik.koszt_produkcja=josadnik.koszt_produkcja-50;
			josadnik.koszt_zloto=josadnik.koszt_zloto-100;
			
    	}	
		if(ster=='q' && rozbudowa==true&& x0==16&& gildia.lvl==2 && kapitol.lvl==5 && drewno>=gildia.koszt_drewno && kamien>=gildia.koszt_kamien && zywnosc>=gildia.koszt_zywnosc && zloto>=gildia.koszt_zloto && miasto[1].produkcja>=gildia.koszt_produkcja){
			gildia.lvl++;
			rozbuduj(gildia,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(gildia);
			zwieksz_przychod(gildia,&przychod_nauka,&max_zolnierzy);
			josadnik.koszt_produkcja=josadnik.koszt_produkcja-50;
			josadnik.koszt_zywnosc=josadnik.koszt_zywnosc-100;
			
    	}//////////////////
				if(ster=='q' && x0==17 && menu_budowy==true && biblioteka.lvl==0){
							budowlanka(biblioteka,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==17&& ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=biblioteka.wyglad[i-x][j-y];
				if(biblioteka.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=2 && bufor_budowa_miasto==17 && drewno>=biblioteka.koszt_drewno && kamien>=biblioteka.koszt_kamien && zywnosc>=biblioteka.koszt_zywnosc && zloto>=biblioteka.koszt_zloto && miasto[1].produkcja>=biblioteka.koszt_produkcja && biblioteka.lvl==0)
		{
		zbuduj(biblioteka, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			biblioteka.lvl=1;
			zwieksz_koszt(biblioteka);
		}	
		if(ster=='q' && x0==17&& rozbudowa==true&& biblioteka.lvl==1 && ratusz.lvl>=4 && drewno>=biblioteka.koszt_drewno && kamien>=biblioteka.koszt_kamien && zywnosc>=biblioteka.koszt_zywnosc && zloto>=biblioteka.koszt_zloto && miasto[1].produkcja>=biblioteka.koszt_produkcja){
			biblioteka.lvl++;
			rozbuduj(biblioteka,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(biblioteka);
			zwieksz_przychod(biblioteka,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==18 && menu_budowy==true && park.lvl==0){
						budowlanka(park,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==18 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=park.wyglad[i-x][j-y];
				if(park.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==18 && drewno>=park.koszt_drewno && kamien>=park.koszt_kamien && zywnosc>=park.koszt_zywnosc && zloto>=park.koszt_zloto && miasto[1].produkcja>=park.koszt_produkcja && park.lvl==0)
		{
		zbuduj(park, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			park.lvl=1;
			zwieksz_koszt(park);
		}	
		if(ster=='q' && rozbudowa==true&& x0==18&& park.lvl==1 && ratusz.lvl>=3 && drewno>=park.koszt_drewno && kamien>=park.koszt_kamien && zywnosc>=park.koszt_zywnosc && zloto>=park.koszt_zloto && miasto[1].produkcja>=park.koszt_produkcja){
			park.lvl++;
			rozbuduj(park,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(park);
			zwieksz_przychod(park,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==18&& park.lvl==2 && ratusz.lvl>=5 && drewno>=park.koszt_drewno && kamien>=park.koszt_kamien && zywnosc>=park.koszt_zywnosc && zloto>=park.koszt_zloto && miasto[1].produkcja>=park.koszt_produkcja){
			park.lvl++;
			rozbuduj(park,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(park);
			zwieksz_przychod(park,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==19 && menu_budowy==true && pomnik.lvl==0){
							budowlanka(pomnik,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==19 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=pomnik.wyglad[i-x][j-y];
				if(pomnik.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true &&  ratusz.lvl>=1 &&bufor_budowa_miasto==19 && drewno>=pomnik.koszt_drewno && kamien>=pomnik.koszt_kamien && zywnosc>=pomnik.koszt_zywnosc && zloto>=pomnik.koszt_zloto && miasto[1].produkcja>=pomnik.koszt_produkcja && pomnik.lvl==0)
		{
		zbuduj(pomnik, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			pomnik.lvl=1;
			zwieksz_koszt(pomnik);
		}	
		if(ster=='q' && rozbudowa==true&& x0==19&& pomnik.lvl==1 && ratusz.lvl>=2 && drewno>=pomnik.koszt_drewno && kamien>=pomnik.koszt_kamien && zywnosc>=pomnik.koszt_zywnosc && zloto>=pomnik.koszt_zloto && miasto[1].produkcja>=pomnik.koszt_produkcja){
			pomnik.lvl++;
			rozbuduj(pomnik,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(pomnik);
			zwieksz_przychod(pomnik,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==19&& pomnik.lvl==2 && ratusz.lvl>=4 && drewno>=pomnik.koszt_drewno && kamien>=pomnik.koszt_kamien && zywnosc>=pomnik.koszt_zywnosc && zloto>=pomnik.koszt_zloto && miasto[1].produkcja>=pomnik.koszt_produkcja){
			pomnik.lvl++;
			rozbuduj(pomnik,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(pomnik);
			zwieksz_przychod(pomnik,&przychod_nauka,&max_zolnierzy);
		
    	}	//////////////////
				if(ster=='q' && x0==20 && menu_budowy==true && ambasada.lvl==0){
							budowlanka(ambasada,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true&& waluta==true && x0==20&& ratusz.lvl>=4){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=ambasada.wyglad[i-x][j-y];
				if(ambasada.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=4 && waluta==true && bufor_budowa_miasto==20 && drewno>=ambasada.koszt_drewno && kamien>=ambasada.koszt_kamien && zywnosc>=ambasada.koszt_zywnosc && zloto>=ambasada.koszt_zloto && miasto[1].produkcja>=ambasada.koszt_produkcja && ambasada.lvl==0)
		{
		zbuduj(ambasada, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			ambasada.lvl=1;
			zwieksz_koszt(ambasada);
		}	
		if(ster=='q' && rozbudowa==true&& x0==20&& ambasada.lvl==1 && ratusz.lvl>=5 && drewno>=ambasada.koszt_drewno && kamien>=ambasada.koszt_kamien && zywnosc>=ambasada.koszt_zywnosc && zloto>=ambasada.koszt_zloto && miasto[1].produkcja>=ambasada.koszt_produkcja){
			ambasada.lvl++;
			rozbuduj(ambasada,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(ambasada);
			zwieksz_przychod(ambasada,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==20&& ambasada.lvl==2 && kapitol.lvl==5 && drewno>=ambasada.koszt_drewno && kamien>=ambasada.koszt_kamien && zywnosc>=ambasada.koszt_zywnosc && zloto>=ambasada.koszt_zloto && miasto[1].produkcja>=ambasada.koszt_produkcja){
			ambasada.lvl++;
			rozbuduj(ambasada,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(ambasada);
			zwieksz_przychod(ambasada,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==21 && menu_budowy==true && port.lvl==0 && miasto[1].woda==true){
						budowlanka(port,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==21 && ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=port.wyglad[i-x][j-y];
				if(port.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=2 && bufor_budowa_miasto==21 && drewno>=port.koszt_drewno && kamien>=port.koszt_kamien && zywnosc>=port.koszt_zywnosc && zloto>=port.koszt_zloto && miasto[1].produkcja>=port.koszt_produkcja && port.lvl==0)
		{
		zbuduj(port, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			port.lvl=1;
			zwieksz_koszt(port);
		}	
		if(ster=='q' && rozbudowa==true&& x0==21&& port.lvl==1 && ratusz.lvl>=3 && drewno>=port.koszt_drewno && kamien>=port.koszt_kamien && zywnosc>=port.koszt_zywnosc && zloto>=port.koszt_zloto && miasto[1].produkcja>=port.koszt_produkcja){
			port.lvl++;
			rozbuduj(port,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(port);
			zwieksz_przychod(port,&przychod_nauka,&max_zolnierzy);
			
    	}
    	if(ster=='q' && rozbudowa==true&& x0==21&& port.lvl==2 && ratusz.lvl>=4 && nawigacja==true && drewno>=port.koszt_drewno && kamien>=port.koszt_kamien && zywnosc>=port.koszt_zywnosc && zloto>=port.koszt_zloto && miasto[1].produkcja>=port.koszt_produkcja){
			port.lvl++;
			rozbuduj(port,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(port);
			zwieksz_przychod(port,&przychod_nauka,&max_zolnierzy);
			
    	}
			//////////////////
				if(ster=='q' && x0==22 && menu_budowy==true && teatr.lvl==0){
							budowlanka(teatr,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==22 && sztuka==true&& ratusz.lvl>=4){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=teatr.wyglad[i-x][j-y];
				if(teatr.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true&& ratusz.lvl>=4 &&sztuka==true && bufor_budowa_miasto==22 && drewno>=teatr.koszt_drewno && kamien>=teatr.koszt_kamien && zywnosc>=teatr.koszt_zywnosc && zloto>=teatr.koszt_zloto && miasto[1].produkcja>=teatr.koszt_produkcja && teatr.lvl==0)
		{
		zbuduj(teatr, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			teatr.lvl=1;
			zwieksz_koszt(teatr);
		}	
		if(ster=='q' && rozbudowa==true&& x0==22&& teatr.lvl==1 && kapitol.lvl==5&&administracja==true && drewno>=teatr.koszt_drewno && kamien>=teatr.koszt_kamien && zywnosc>=teatr.koszt_zywnosc && zloto>=teatr.koszt_zloto && miasto[1].produkcja>=teatr.koszt_produkcja){
			teatr.lvl++;
			rozbuduj(teatr,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(teatr);
			zwieksz_przychod(teatr,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==23 && menu_budowy==true){
							budowlanka(droga,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==23 && ratusz.lvl>=1){
				
			if(ksztalt%10==0)mapa_stolicy[x][y]=prosto_dol;
			if(ksztalt%10==1)mapa_stolicy[x][y]=prosto_bok;
			if(ksztalt%10==2)mapa_stolicy[x][y]=skrzyzowanie;
			if(ksztalt%10==3)mapa_stolicy[x][y]=skret_lewo_dol;
			if(ksztalt%10==4)mapa_stolicy[x][y]=skret_lewo_gora;
			if(ksztalt%10==5)mapa_stolicy[x][y]=skret_prawo_dol;
			if(ksztalt%10==6)mapa_stolicy[x][y]=skret_prawo_gora;
			if(ksztalt%10==7)mapa_stolicy[x][y]=skrzyzowanie_dol;
			if(ksztalt%10==8)mapa_stolicy[x][y]=skrzyzowanie_gora;
			if(ksztalt%10==9)mapa_stolicy[x][y]=skrzyzowanie_lewo;
			if(ksztalt%10==10)mapa_stolicy[x][y]=skrzyzowanie_prawo;
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==23 && drewno>=droga.koszt_drewno && kamien>=droga.koszt_kamien && zywnosc>=droga.koszt_zywnosc && zloto>=droga.koszt_zloto && miasto[1].produkcja>=droga.koszt_produkcja)
		{
			zloto=zloto-droga.koszt_zloto;
			drewno=drewno-droga.koszt_drewno;
			kamien=kamien-droga.koszt_kamien;
			zywnosc=zywnosc-droga.koszt_zywnosc;
			miasto[1].produkcja=miasto[1].produkcja-droga.koszt_produkcja;
			miasto[1].ludnosc=miasto[1].ludnosc+droga.ludnosc;
			if(ksztalt%10==0)mapa_stolicy[x][y]=prosto_dol;
			if(ksztalt%10==1)mapa_stolicy[x][y]=prosto_bok;
			if(ksztalt%10==2)mapa_stolicy[x][y]=skrzyzowanie;
			if(ksztalt%10==3)mapa_stolicy[x][y]=skret_lewo_dol;
			if(ksztalt%10==4)mapa_stolicy[x][y]=skret_lewo_gora;
			if(ksztalt%10==5)mapa_stolicy[x][y]=skret_prawo_dol;
			if(ksztalt%10==6)mapa_stolicy[x][y]=skret_prawo_gora;
			if(ksztalt%10==7)mapa_stolicy[x][y]=skrzyzowanie_dol;
			if(ksztalt%10==8)mapa_stolicy[x][y]=skrzyzowanie_gora;
			if(ksztalt%10==9)mapa_stolicy[x][y]=skrzyzowanie_lewo;
			if(ksztalt%10==10)mapa_stolicy[x][y]=skrzyzowanie_prawo;
			
			for(int i=x-1;i<=x+1;i++){
				for(int j=y-1;j<y+1;j++){
					bufor_miasta[i][j]=mapa_stolicy[i][j];
				}
			}
			
			droga.lvl=1;
			
		}	
		if(ster=='q' && rozbudowa==true&& x0==23&& droga.lvl==1 && ratusz.lvl>=4 &&infrastruktura==true && drewno>=droga.koszt_drewno && kamien>=droga.koszt_kamien && zywnosc>=droga.koszt_zywnosc && zloto>=droga.koszt_zloto && miasto[1].produkcja>=droga.koszt_produkcja){
			droga.lvl++;
			rozbuduj(droga,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_przychod(droga,&przychod_nauka,&max_zolnierzy);
			pikinier[xm].koszt_produkcja-=25;
			lucznik[xm].koszt_produkcja-=25;
			kusznik[xm].koszt_produkcja-=25;
			ciezkozbrojny[xm].koszt_produkcja-=25;
			lekka_jazda[xm].koszt_produkcja-=25;
			ciezka_jazda[xm].koszt_produkcja-=25;
			elita.koszt_produkcja-=25;
			taran[xm].koszt_produkcja-=25;
    	}	//////////////////
				if(ster=='q' && x0==24 && menu_budowy==true && tawerna.lvl==0){
							budowlanka(tawerna,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==24 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=tawerna.wyglad[i-x][j-y];
				if(tawerna.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==24 && drewno>=tawerna.koszt_drewno && kamien>=tawerna.koszt_kamien && zywnosc>=tawerna.koszt_zywnosc && zloto>=tawerna.koszt_zloto && miasto[1].produkcja>=tawerna.koszt_produkcja && tawerna.lvl==0)
		{
		zbuduj(tawerna, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			tawerna.lvl=1;
			zwieksz_koszt(tawerna);
		}	
		if(ster=='q' && rozbudowa==true&& x0==24&& tawerna.lvl==1 && ratusz.lvl>=3 && drewno>=tawerna.koszt_drewno && kamien>=tawerna.koszt_kamien && zywnosc>=tawerna.koszt_zywnosc && zloto>=tawerna.koszt_zloto && miasto[1].produkcja>=tawerna.koszt_produkcja){
			tawerna.lvl++;
			rozbuduj(tawerna,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(tawerna);
			zwieksz_przychod(tawerna,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==24&& tawerna.lvl==2 && ratusz.lvl>=4&&browarnictwo==true && drewno>=tawerna.koszt_drewno && kamien>=tawerna.koszt_kamien && zywnosc>=tawerna.koszt_zywnosc && zloto>=tawerna.koszt_zloto && miasto[1].produkcja>=tawerna.koszt_produkcja){
			tawerna.lvl++;
			rozbuduj(tawerna,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(tawerna);
			zwieksz_przychod(tawerna,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==25 && menu_budowy==true && magazyn.lvl==0){
						budowlanka(magazyn,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==25 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=magazyn.wyglad[i-x][j-y];
				if(magazyn.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==25 && drewno>=magazyn.koszt_drewno && kamien>=magazyn.koszt_kamien && zywnosc>=magazyn.koszt_zywnosc && zloto>=magazyn.koszt_zloto && miasto[1].produkcja>=magazyn.koszt_produkcja && magazyn.lvl==0)
		{
		zbuduj(magazyn, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			magazyn.lvl=1;
			zwieksz_koszt(magazyn);
		}	
		if(ster=='q' && rozbudowa==true&& x0==25&& magazyn.lvl==1 && ratusz.lvl>=3 && drewno>=magazyn.koszt_drewno && kamien>=magazyn.koszt_kamien && zywnosc>=magazyn.koszt_zywnosc && zloto>=magazyn.koszt_zloto && miasto[1].produkcja>=magazyn.koszt_produkcja){
			magazyn.lvl++;
			rozbuduj(magazyn,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(magazyn);
			zwieksz_przychod(magazyn,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==25&& magazyn.lvl==2 && ratusz.lvl>=4 && hodowla==true && drewno>=magazyn.koszt_drewno && kamien>=magazyn.koszt_kamien && zywnosc>=magazyn.koszt_zywnosc && zloto>=magazyn.koszt_zloto && miasto[1].produkcja>=magazyn.koszt_produkcja){
			magazyn.lvl++;
			rozbuduj(magazyn,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(magazyn);
			zwieksz_przychod(magazyn,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==25&& magazyn.lvl==3 && kapitol.lvl==5 && drewno>=magazyn.koszt_drewno && kamien>=magazyn.koszt_kamien && zywnosc>=magazyn.koszt_zywnosc && zloto>=magazyn.koszt_zloto && miasto[1].produkcja>=magazyn.koszt_produkcja){
			magazyn.lvl++;
			rozbuduj(magazyn,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(magazyn);
			zwieksz_przychod(magazyn,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==26 && menu_budowy==true && mlyn.lvl==0){
						budowlanka(mlyn,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==26 && ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=mlyn.wyglad[i-x][j-y];
				if(mlyn.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=2 && bufor_budowa_miasto==26 && drewno>=mlyn.koszt_drewno && kamien>=mlyn.koszt_kamien && zywnosc>=mlyn.koszt_zywnosc && zloto>=mlyn.koszt_zloto && miasto[1].produkcja>=mlyn.koszt_produkcja && mlyn.lvl==0)
		{
		zbuduj(mlyn, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			mlyn.lvl=1;
			zwieksz_koszt(mlyn);
		}	
		if(ster=='q' && rozbudowa==true&& x0==26&& mlyn.lvl==1 && ratusz.lvl>=3 && drewno>=mlyn.koszt_drewno && kamien>=mlyn.koszt_kamien && zywnosc>=mlyn.koszt_zywnosc && zloto>=mlyn.koszt_zloto && miasto[1].produkcja>=mlyn.koszt_produkcja){
			mlyn.lvl++;
			rozbuduj(mlyn,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(mlyn);
			zwieksz_przychod(mlyn,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==26&& mlyn.lvl==2 && ratusz.lvl>=4 && drewno>=mlyn.koszt_drewno && kamien>=mlyn.koszt_kamien && zywnosc>=mlyn.koszt_zywnosc && zloto>=mlyn.koszt_zloto && miasto[1].produkcja>=mlyn.koszt_produkcja){
			mlyn.lvl++;
			rozbuduj(mlyn,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(mlyn);
			zwieksz_przychod(mlyn,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==26&& mlyn.lvl==3 && ratusz.lvl>=5 && drewno>=mlyn.koszt_drewno && kamien>=mlyn.koszt_kamien && zywnosc>=mlyn.koszt_zywnosc && zloto>=mlyn.koszt_zloto && miasto[1].produkcja>=mlyn.koszt_produkcja){
			mlyn.lvl++;
			rozbuduj(mlyn,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(mlyn);
			zwieksz_przychod(mlyn,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==27 && menu_budowy==true && plac.lvl==0){
							budowlanka(plac,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==27 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=plac.wyglad[i-x][j-y];
				if(plac.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==27 && drewno>=plac.koszt_drewno && kamien>=plac.koszt_kamien && zywnosc>=plac.koszt_zywnosc && zloto>=plac.koszt_zloto && miasto[1].produkcja>=plac.koszt_produkcja && plac.lvl==0)
		{
		zbuduj(plac, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			plac.lvl=1;
		}		//////////////////
				if(ster=='q' && x0==28 && menu_budowy==true && tartakb.lvl==0){
						budowlanka(tartakb,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==28 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=tartakb.wyglad[i-x][j-y];
				if(tartakb.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==28 && drewno>=tartakb.koszt_drewno && kamien>=tartakb.koszt_kamien && zywnosc>=tartakb.koszt_zywnosc && zloto>=tartakb.koszt_zloto && miasto[1].produkcja>=tartakb.koszt_produkcja && tartakb.lvl==0)
		{
		zbuduj(tartakb, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			tartakb.lvl=1;
			zwieksz_koszt(tartakb);
		}	
		if(ster=='q' && rozbudowa==true&& x0==28&& tartakb.lvl==1 && ratusz.lvl>=3 && drewno>=tartakb.koszt_drewno && kamien>=tartakb.koszt_kamien && zywnosc>=tartakb.koszt_zywnosc && zloto>=tartakb.koszt_zloto && miasto[1].produkcja>=tartakb.koszt_produkcja){
			tartakb.lvl++;
			rozbuduj(tartakb,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(tartakb);
			zwieksz_przychod(tartakb,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==28&& tartakb.lvl==2 && ratusz.lvl>=4 && drewno>=tartakb.koszt_drewno && kamien>=tartakb.koszt_kamien && zywnosc>=tartakb.koszt_zywnosc && zloto>=tartakb.koszt_zloto && miasto[1].produkcja>=tartakb.koszt_produkcja){
			tartakb.lvl++;
			rozbuduj(tartakb,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(tartakb);
			zwieksz_przychod(tartakb,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==28&& tartakb.lvl==3 && ratusz.lvl>=5 && drewno>=tartakb.koszt_drewno && kamien>=tartakb.koszt_kamien && zywnosc>=tartakb.koszt_zywnosc && zloto>=tartakb.koszt_zloto && miasto[1].produkcja>=tartakb.koszt_produkcja){
			tartakb.lvl++;
			rozbuduj(tartakb,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(tartakb);
			zwieksz_przychod(tartakb,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==29 && menu_budowy==true && kamieniarz.lvl==0){
						budowlanka(kamieniarz,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==29 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=kamieniarz.wyglad[i-x][j-y];
				if(kamieniarz.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==29 && drewno>=kamieniarz.koszt_drewno && kamien>=kamieniarz.koszt_kamien && zywnosc>=kamieniarz.koszt_zywnosc && zloto>=kamieniarz.koszt_zloto && miasto[1].produkcja>=kamieniarz.koszt_produkcja && kamieniarz.lvl==0)
		{
		zbuduj(kamieniarz, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			kamieniarz.lvl=1;
			zwieksz_koszt(kamieniarz);
		}	
		if(ster=='q' && rozbudowa==true&& x0==29&& kamieniarz.lvl==1 && ratusz.lvl>=3 && drewno>=kamieniarz.koszt_drewno && kamien>=kamieniarz.koszt_kamien && zywnosc>=kamieniarz.koszt_zywnosc && zloto>=kamieniarz.koszt_zloto && miasto[1].produkcja>=kamieniarz.koszt_produkcja){
			kamieniarz.lvl++;
			rozbuduj(kamieniarz,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(kamieniarz);
			zwieksz_przychod(kamieniarz,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==29&& kamieniarz.lvl==2 && ratusz.lvl>=4 && drewno>=kamieniarz.koszt_drewno && kamien>=kamieniarz.koszt_kamien && zywnosc>=kamieniarz.koszt_zywnosc && zloto>=kamieniarz.koszt_zloto && miasto[1].produkcja>=kamieniarz.koszt_produkcja){
			kamieniarz.lvl++;
			rozbuduj(kamieniarz,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(kamieniarz);
			zwieksz_przychod(kamieniarz,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==29&& kamieniarz.lvl==3 && ratusz.lvl>=5 && drewno>=kamieniarz.koszt_drewno && kamien>=kamieniarz.koszt_kamien && zywnosc>=kamieniarz.koszt_zywnosc && zloto>=kamieniarz.koszt_zloto && miasto[1].produkcja>=kamieniarz.koszt_produkcja){
			kamieniarz.lvl++;
			rozbuduj(kamieniarz,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(kamieniarz);
			zwieksz_przychod(kamieniarz,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==30 && menu_budowy==true && kolos.lvl==0){
						budowlanka(kolos,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==30 && sztuka==true && kapitol.lvl==5){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=kolos.wyglad[i-x][j-y];
				if(kolos.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && kapitol.lvl==5 && sztuka==true && bufor_budowa_miasto==30 && drewno>=kolos.koszt_drewno && kamien>=kolos.koszt_kamien && zywnosc>=kolos.koszt_zywnosc && zloto>=kolos.koszt_zloto && miasto[1].produkcja>=kolos.koszt_produkcja && kolos.lvl==0)
		{
		zbuduj(kolos, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			kolos.lvl=1;
		}		//////////////////
				if(ster=='q' && x0==31 && menu_budowy==true && kosciol.lvl==0){
						budowlanka(kosciol,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==31 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=kosciol.wyglad[i-x][j-y];
				if(kosciol.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==31 && drewno>=kosciol.koszt_drewno && kamien>=kosciol.koszt_kamien && zywnosc>=kosciol.koszt_zywnosc && zloto>=kosciol.koszt_zloto && miasto[1].produkcja>=kosciol.koszt_produkcja && kosciol.lvl==0)
		{
		zbuduj(kosciol, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			kosciol.lvl=1;
			zwieksz_koszt(kosciol);
		}
		if(ster=='q' && rozbudowa==true&& x0==31&& kosciol.lvl==1 && ratusz.lvl>=3 && drewno>=kosciol.koszt_drewno && kamien>=kosciol.koszt_kamien && zywnosc>=kosciol.koszt_zywnosc && zloto>=kosciol.koszt_zloto && miasto[1].produkcja>=kosciol.koszt_produkcja){
			kosciol.lvl++;
			rozbuduj(kosciol,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(kosciol);
			zwieksz_przychod(kosciol,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==31&& kosciol.lvl==2 && ratusz.lvl>=4 && drewno>=kosciol.koszt_drewno && kamien>=kosciol.koszt_kamien && zywnosc>=kosciol.koszt_zywnosc && zloto>=kosciol.koszt_zloto && miasto[1].produkcja>=kosciol.koszt_produkcja){
			kosciol.lvl++;
			rozbuduj(kosciol,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(kosciol);
			zwieksz_przychod(kosciol,&przychod_nauka,&max_zolnierzy);
			
    	}	
			//////////////////
				if(ster=='q' && x0==32 && menu_budowy==true && katedra.lvl==0){
							budowlanka(katedra,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
							budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==32&& ewangelizacja==true&& ratusz.lvl>=4){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=katedra.wyglad[i-x][j-y];
				if(katedra.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=4&& bufor_budowa_miasto==32&& ewangelizacja==true && drewno>=katedra.koszt_drewno && kamien>=katedra.koszt_kamien && zywnosc>=katedra.koszt_zywnosc && zloto>=katedra.koszt_zloto && miasto[1].produkcja>=katedra.koszt_produkcja && katedra.lvl==0)
		{
		zbuduj(katedra, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			katedra.lvl=1;
			zwieksz_koszt(katedra);
		}	
		if(ster=='q' && rozbudowa==true&& x0==32&& katedra.lvl==1 && ratusz.lvl>=5 && drewno>=katedra.koszt_drewno && kamien>=katedra.koszt_kamien && zywnosc>=katedra.koszt_zywnosc && zloto>=katedra.koszt_zloto && miasto[1].produkcja>=katedra.koszt_produkcja){
			katedra.lvl++;
			rozbuduj(katedra,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(katedra);
			zwieksz_przychod(katedra,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==32&& katedra.lvl==2 && kapitol.lvl==5 && drewno>=katedra.koszt_drewno && kamien>=katedra.koszt_kamien && zywnosc>=katedra.koszt_zywnosc && zloto>=katedra.koszt_zloto && miasto[1].produkcja>=katedra.koszt_produkcja){
			katedra.lvl++;
			rozbuduj(katedra,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(katedra);
			zwieksz_przychod(katedra,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==33 && menu_budowy==true && skarbiec.lvl==0){
						budowlanka(skarbiec,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==33 && ratusz.lvl>=3){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=skarbiec.wyglad[i-x][j-y];
				if(skarbiec.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=3 && bufor_budowa_miasto==33 && drewno>=skarbiec.koszt_drewno && kamien>=skarbiec.koszt_kamien && zywnosc>=skarbiec.koszt_zywnosc && zloto>=skarbiec.koszt_zloto && miasto[1].produkcja>=skarbiec.koszt_produkcja && skarbiec.lvl==0)
		{
		zbuduj(skarbiec, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
				&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			skarbiec.lvl=1;
			zwieksz_koszt(skarbiec);
		}	
		if(ster=='q' && rozbudowa==true&& x0==33&& skarbiec.lvl==1 && ratusz.lvl>=5 && drewno>=skarbiec.koszt_drewno && kamien>=skarbiec.koszt_kamien && zywnosc>=skarbiec.koszt_zywnosc && zloto>=skarbiec.koszt_zloto && miasto[1].produkcja>=skarbiec.koszt_produkcja){
			skarbiec.lvl++;
			rozbuduj(skarbiec,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(skarbiec);
			zwieksz_przychod(skarbiec,&przychod_nauka,&max_zolnierzy);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==33&& skarbiec.lvl==2 && kapitol.lvl==5 && drewno>=skarbiec.koszt_drewno && kamien>=skarbiec.koszt_kamien && zywnosc>=skarbiec.koszt_zywnosc && zloto>=skarbiec.koszt_zloto && miasto[1].produkcja>=skarbiec.koszt_produkcja){
			skarbiec.lvl++;
			rozbuduj(skarbiec,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(skarbiec);
			zwieksz_przychod(skarbiec,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==34 && menu_budowy==true && fort.lvl==0){
						budowlanka(fort,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==34 && ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=fort.wyglad[i-x][j-y];
				if(fort.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=2 && bufor_budowa_miasto==34 && drewno>=fort.koszt_drewno && kamien>=fort.koszt_kamien && zywnosc>=fort.koszt_zywnosc && zloto>=fort.koszt_zloto && miasto[1].produkcja>=fort.koszt_produkcja && fort.lvl==0)
		{
		zbuduj(fort, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			fort.lvl=1;
			zwieksz_koszt(fort);
			miasto[1].obrona=miasto[1].obrona+15;
		}	
		if(ster=='q' && rozbudowa==true&& x0==34&& fort.lvl==1 && ratusz.lvl>=3 && drewno>=fort.koszt_drewno && kamien>=fort.koszt_kamien && zywnosc>=fort.koszt_zywnosc && zloto>=fort.koszt_zloto && miasto[1].produkcja>=fort.koszt_produkcja){
			fort.lvl++;
			rozbuduj(fort,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(fort);
			zwieksz_przychod(fort,&przychod_nauka,&max_zolnierzy);
			miasto[1].obrona=miasto[1].obrona+15;
		
    	}
		if(ster=='q' && rozbudowa==true&& x0==34&& fort.lvl==2 && ratusz.lvl>=4 && drewno>=fort.koszt_drewno && kamien>=fort.koszt_kamien && zywnosc>=fort.koszt_zywnosc && zloto>=fort.koszt_zloto && miasto[1].produkcja>=fort.koszt_produkcja){
			fort.lvl++;
			rozbuduj(fort,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(fort);
			zwieksz_przychod(fort,&przychod_nauka,&max_zolnierzy);
			miasto[1].obrona=miasto[1].obrona+15;
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==34&& fort.lvl==3 && kapitol.lvl==5 && drewno>=fort.koszt_drewno && kamien>=fort.koszt_kamien && zywnosc>=fort.koszt_zywnosc && zloto>=fort.koszt_zloto && miasto[1].produkcja>=fort.koszt_produkcja){
			fort.lvl++;
			rozbuduj(fort,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(fort);
			miasto[1].obrona=miasto[1].obrona+15;
			zwieksz_przychod(fort,&przychod_nauka,&max_zolnierzy);
			
    	}	//////////////////
				if(ster=='q' && x0==35 && menu_budowy==true && weglarnia.lvl==0){
						budowlanka(weglarnia,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==35 && ratusz.lvl>=1){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=weglarnia.wyglad[i-x][j-y];
				if(weglarnia.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==35 && drewno>=weglarnia.koszt_drewno && kamien>=weglarnia.koszt_kamien && zywnosc>=weglarnia.koszt_zywnosc && zloto>=weglarnia.koszt_zloto && miasto[1].produkcja>=weglarnia.koszt_produkcja && weglarnia.lvl==0)
		{
		zbuduj(weglarnia, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			weglarnia.lvl=1;
			zwieksz_koszt(weglarnia);
		}
		if(ster=='q' && rozbudowa==true&& x0==35&& weglarnia.lvl==1 && ratusz.lvl>=3 && drewno>=weglarnia.koszt_drewno && kamien>=weglarnia.koszt_kamien && zywnosc>=weglarnia.koszt_zywnosc && zloto>=weglarnia.koszt_zloto && miasto[1].produkcja>=weglarnia.koszt_produkcja){
			weglarnia.lvl++;
			rozbuduj(weglarnia,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(weglarnia);
			zwieksz_przychod(weglarnia,&przychod_nauka,&max_zolnierzy);
			
    	}
				//////////////////
				if(ster=='q' && x0==36 && menu_budowy==true && warsztat.lvl==0){
						budowlanka(warsztat,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==36 && ratusz.lvl>=2){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=warsztat.wyglad[i-x][j-y];
				if(warsztat.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=2 && bufor_budowa_miasto==36 && drewno>=warsztat.koszt_drewno && kamien>=warsztat.koszt_kamien && zywnosc>=warsztat.koszt_zywnosc && zloto>=warsztat.koszt_zloto && miasto[1].produkcja>=warsztat.koszt_produkcja && warsztat.lvl==0)
		{
		zbuduj(warsztat, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			warsztat.lvl=1;
			kusznik[xm].koszt_produkcja=kusznik[xm].koszt_produkcja-50;
			zwieksz_koszt(warsztat);
			kusznik[xm].koszt_produkcja-=50;
		}
		if(ster=='q' && rozbudowa==true && x0==36&& warsztat.lvl==1 &&ratusz.lvl>=4 && mechanika==true && drewno>=warsztat.koszt_drewno && kamien>=warsztat.koszt_kamien && zywnosc>=warsztat.koszt_zywnosc && zloto>=warsztat.koszt_zloto && miasto[1].produkcja>=warsztat.koszt_produkcja){
			warsztat.lvl++;
			rozbuduj(warsztat,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(warsztat);
			zwieksz_przychod(warsztat,&przychod_nauka,&max_zolnierzy);
			kusznik[xm].koszt_produkcja-=50;
    	}
				//////////////////
				if(ster=='q' && x0==37 && menu_budowy==true && stajnia.lvl==0){
						budowlanka(stajnia,x,y,mapa_stolicy,bufor_miasta,&bufor_budowa_miasto,x0,ksztalt);
						budowa_miasto=true;
		}
		if(budowa_miasto==true && x0==37 && ratusz.lvl>=3){
		
					for(int i=x;i<x+9;i++){
				for(int j=y;j<y+21;j++){
	
				mapa_stolicy[i][j]=stajnia.wyglad[i-x][j-y];
				if(stajnia.wyglad[i-x][j-y]==' ')
				mapa_stolicy[i][j]=bufor_miasta[i][j];
		}
			}
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=2 && bufor_budowa_miasto==37 && drewno>=stajnia.koszt_drewno && kamien>=stajnia.koszt_kamien && zywnosc>=stajnia.koszt_zywnosc && zloto>=stajnia.koszt_zloto && miasto[1].produkcja>=stajnia.koszt_produkcja && stajnia.lvl==0)
		{
		zbuduj(stajnia, x,  y, mapa_stolicy, bufor_miasta, &drewno, &kamien, &zywnosc, 
			&zloto, &max_zolnierzy, &budowa_miasto, &menu_budowy, &menu_stolica, &przychod_nauka, &x0);
			stajnia.lvl=1;
			zwieksz_koszt(stajnia);
		}
		if(ster=='q' && rozbudowa==true&& x0==37&& stajnia.lvl==1 && ratusz.lvl>=3 && drewno>=stajnia.koszt_drewno && kamien>=stajnia.koszt_kamien && zywnosc>=stajnia.koszt_zywnosc && zloto>=stajnia.koszt_zloto && miasto[1].produkcja>=stajnia.koszt_produkcja){
			stajnia.lvl++;
			rozbuduj(stajnia,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(stajnia);
			zwieksz_przychod(stajnia,&przychod_nauka,&max_zolnierzy);
			lekka_jazda[xm].koszt_produkcja-=50;
			ciezka_jazda[xm].koszt_produkcja-=50;
    	}
    	if(ster=='q' && rozbudowa==true&& x0==37&& stajnia.lvl==2 && ratusz.lvl>=4 && drewno>=stajnia.koszt_drewno && kamien>=stajnia.koszt_kamien && zywnosc>=stajnia.koszt_zywnosc && zloto>=stajnia.koszt_zloto && miasto[1].produkcja>=stajnia.koszt_produkcja){
			stajnia.lvl++;
			rozbuduj(stajnia,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(stajnia);
			zwieksz_przychod(stajnia,&przychod_nauka,&max_zolnierzy);
			lekka_jazda[xm].koszt_produkcja-=50;
			ciezka_jazda[xm].koszt_produkcja-=50;
    	}
    	if(ster=='q' && rozbudowa==true&& x0==37&& stajnia.lvl==3 && ratusz.lvl>=5 && drewno>=stajnia.koszt_drewno && kamien>=stajnia.koszt_kamien && zywnosc>=stajnia.koszt_zywnosc && zloto>=stajnia.koszt_zloto && miasto[1].produkcja>=stajnia.koszt_produkcja){
			stajnia.lvl++;
			rozbuduj(stajnia,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_stolica,&przychod_nauka,&x0);
			zwieksz_koszt(stajnia);
			zwieksz_przychod(stajnia,&przychod_nauka,&max_zolnierzy);
			lekka_jazda[xm].koszt_produkcja-=50;
			ciezka_jazda[xm].koszt_produkcja-=50;
    	}
				//////////////////
				if(ster=='q' && x0==38 && menu_budowy==true && ratusz.lvl>=1){
				mapa_stolicy[x][y]=dom;
				budowa_miasto=true;
			system("CLS");
			gotoxy(90,27);

			cout << dom;
			bufor_budowa_miasto=38;
		}
		if(budowa_miasto==true && x0==38 && ratusz.lvl>=1){
	
				mapa_stolicy[x][y]=dom;	
		}
		if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==38 && drewno>=10 && zywnosc>=5 && zloto >=5 && miasto[1].produkcja>=10&& bufor_miasta[x][y]!='A'&&
		 bufor_miasta[x][y]!='B'&& bufor_miasta[x][y]!='C'&& bufor_miasta[x][y]!='D'&& bufor_miasta[x][y]!='E'&& bufor_miasta[x][y]!='F'&& bufor_miasta[x][y]!='G'&&
		  bufor_miasta[x][y]!='H'&& bufor_miasta[x][y]!='I'&& bufor_miasta[x][y]!='J'&& bufor_miasta[x][y]!='K'&& bufor_miasta[x][y]!='L'&& bufor_miasta[x][y]!='M'&&
		   bufor_miasta[x][y]!='N'&& bufor_miasta[x][y]!='O'&& bufor_miasta[x][y]!='P'&& bufor_miasta[x][y]!='R'&& bufor_miasta[x][y]!='S'&& bufor_miasta[x][y]!='T'&&
		    bufor_miasta[x][y]!='U'&& bufor_miasta[x][y]!='W'&& bufor_miasta[x][y]!='Y'&& bufor_miasta[x][y]!='Z'){
			bufor_miasta[x][y]=dom;
			mapa_stolicy[x][y]=dom;
			drewno=drewno-10;
			zywnosc=zywnosc-5;
			zloto=zloto-5;
			miasto[1].produkcja=miasto[1].produkcja-10;
			system("CLS");
			budowa_miasto=false;
		}
		///////////////////
				if(ster=='q' && x0==39 && menu_budowy==true && ratusz.lvl>=1){
				mapa_stolicy[x][y]=dom2;
				budowa_miasto=true;

			system("CLS");
			gotoxy(90,27);

			cout << dom2;
			bufor_budowa_miasto=39;
		}
		if(budowa_miasto==true && x0==39 && ratusz.lvl>=1){
	
				mapa_stolicy[x][y]=dom2;	
		}
		
		if(ster=='e' &&  budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==39 && drewno>=10 && zywnosc>=5 && zloto >=5 && miasto[1].produkcja>=10 && mapa_stolicy[x][y]!='A'&&
		 bufor_miasta[x][y]!='B'&& bufor_miasta[x][y]!='C'&& bufor_miasta[x][y]!='D'&& bufor_miasta[x][y]!='E'&& bufor_miasta[x][y]!='F'&& bufor_miasta[x][y]!='G'&&
		  bufor_miasta[x][y]!='H'&& bufor_miasta[x][y]!='I'&& bufor_miasta[x][y]!='J'&& bufor_miasta[x][y]!='K'&& bufor_miasta[x][y]!='L'&& bufor_miasta[x][y]!='M'&&
		   bufor_miasta[x][y]!='N'&& bufor_miasta[x][y]!='O'&& bufor_miasta[x][y]!='P'&& bufor_miasta[x][y]!='R'&& bufor_miasta[x][y]!='S'&& bufor_miasta[x][y]!='T'&&
		    bufor_miasta[x][y]!='U'&& bufor_miasta[x][y]!='W'&& bufor_miasta[x][y]!='Y'&& bufor_miasta[x][y]!='Z'){
			bufor_miasta[x][y]=dom2;
			mapa_stolicy[x][y]=dom2;
			drewno=drewno-10;
			zywnosc=zywnosc-5;
			zloto=zloto-5;
			miasto[1].produkcja=miasto[1].produkcja-10;
			system("CLS");
			budowa_miasto=false;
		}
		///////////////////
				if(ster=='q' && x0==40 && menu_budowy==true && ratusz.lvl>=1){
				mapa_stolicy[x][y]=woda;
				budowa_miasto=true;

			system("CLS");
			gotoxy(90,27);

			cout << woda;
			bufor_budowa_miasto=40;
		}
		if(budowa_miasto==true && x0==40 && ratusz.lvl>=1){
	
				mapa_stolicy[x][y]=woda;	
		}
				if(ster=='e' && budowa_miasto==true && ratusz.lvl>=1 && bufor_budowa_miasto==40 && drewno>=10 && zywnosc>=5 && zloto >=5 && miasto[1].produkcja>=10 && mapa_stolicy[x][y]!='A'&&
		 bufor_miasta[x][y]!='B'&& bufor_miasta[x][y]!='C'&& bufor_miasta[x][y]!='D'&& bufor_miasta[x][y]!='E'&& bufor_miasta[x][y]!='F'&& bufor_miasta[x][y]!='G'&&
		  bufor_miasta[x][y]!='H'&& bufor_miasta[x][y]!='I'&& bufor_miasta[x][y]!='J'&& bufor_miasta[x][y]!='K'&& bufor_miasta[x][y]!='L'&& bufor_miasta[x][y]!='M'&&
		   bufor_miasta[x][y]!='N'&& bufor_miasta[x][y]!='O'&& bufor_miasta[x][y]!='P'&& bufor_miasta[x][y]!='R'&& bufor_miasta[x][y]!='S'&& bufor_miasta[x][y]!='T'&&
		    bufor_miasta[x][y]!='U'&& bufor_miasta[x][y]!='W'&& bufor_miasta[x][y]!='Y'&& bufor_miasta[x][y]!='Z'){
			bufor_miasta[x][y]=woda;
			mapa_stolicy[x][y]=woda;
			drewno=drewno-10;
			zywnosc=zywnosc-5;
			zloto=zloto-5;
			miasto[1].produkcja=miasto[1].produkcja-10;
			system("CLS");
			budowa_miasto=false;
		}

		if(ster==KEY_UP && x0==0 && menu_budowy==true || ster==KEY_UP && x0==0 && rozbudowa==true)
		x0=41;
		
		if(ster==KEY_DOWN && x0==41 && menu_budowy==true || ster==KEY_DOWN && x0==41 && rozbudowa==true)
		x0=0;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	if(technologie==true){
		
		cls();
		
		if(x0==1){
			gotoxy(8,30);
			cout << "Koszt: 350pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna rekrutowac lucznikow";
		}
		if(x0==2){
			gotoxy(8,30);
			cout << "Koszt: 350pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna rozbudowac magazyn do 3 poziomu, zwieksza sie produkcja zywnosci w panstwie";
		}
		if(x0==3){
			gotoxy(8,30);
			cout << "Koszt: 400pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna zbudowac gildie oraz zwieksza sie panstwowy przychod nauki";
		}
		if(x0==4){
						gotoxy(8,30);
			cout << "Koszt: 400pkt. nauki";
			gotoxy(8,31);
			cout << "Mozliwosc rozbudowy tawerny do 3 poziomu oraz zwieksza sie ilosc ruchow na ture";
		}
		if(x0==5){
			gotoxy(8,30);
			cout << "Koszt: 450pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna budowac tarany i rozbudowac warsztat do 2 poziomu oraz zwieksza sie ilosc ruchow na ture ";
		}
		if(x0==6){
			gotoxy(8,30);
			cout << "Koszt: 450pkt. nauki";
			gotoxy(8,31);
			cout << "Zwieksza sie atak piechoty (+1) oraz mozna wybudowac hute";
		}
		if(x0==7){
			gotoxy(8,30);
			cout << "Koszt: 450pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna wybudowac ambasade, zwieksza sie przychod zlota w panstwie oraz mozna rozbudowac rynek do 3 poziomu";
		}
		if(x0==8){
			gotoxy(8,30);
			cout << "Koszt: 500pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna rekrutowac kusznikow i ciezkozbrojnych";
		}
		if(x0==9){
			gotoxy(8,30);
			cout << "Koszt: 500pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna ulepszyc drogi w stolicy";
		}
		if(x0==10){
			gotoxy(8,30);
			cout << "Koszt: 500pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna handlowac z drugim graczem oraz rozbudowac kapitol do poziomu 5 oraz zwieksza sie ilosc ruchow na ture";
		}
		if(x0==11){
			gotoxy(8,30);
			cout << "Koszt: 500pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna wybudowac katedre oraz zwieksza sie panstwowy przychod wiary";
		}
		if(x0==12){
			gotoxy(8,30);
			cout << "Koszt: 550pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna rekrutowac ciezka jazde oraz elity";
		}
		if(x0==13){
			gotoxy(8,30);
			cout << "Koszt: 550pkt. nauki";
			gotoxy(8,31);
			cout << "Zwieksza sie zasieg jednostek na mapie oraz mozna rozbudowac port do 3 poziomu";
		}
		if(x0==14){
			gotoxy(8,30);
			cout << "Koszt: 550pkt. nauki";
			gotoxy(8,31);
			cout << "Mozna zbudowac teatr oraz Kolosa";
		}
		
		/////////////////////////////////////////
		gotoxy(8,1);
		if(x0==0){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Powrot ";
			SetConsoleTextAttribute( hOut, 8 );
		}else
		cout << " Powrot ";
		
		if(kapitol.lvl>=1){
		
		gotoxy(8,3);
		if(x0==1){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Lowiectwo ";
			SetConsoleTextAttribute( hOut, 8 );
		}else{
		if(lowiectwo==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Lowiectwo ";
			SetConsoleTextAttribute( hOut, 8 );

		}else	
		cout << " Lowiectwo ";
		}
		for(int i=0;i<20;i++)cout << char(prosto_bok);
		if(x0==2){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Hodowla ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(hodowla==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Hodowla ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Hodowla ";
		}
	}
		if(kapitol.lvl>=2){
		gotoxy(8,7);
				if(x0==3){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Gildie ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(gildie==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Gildie ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Gildie ";
		}
		for(int i=0;i<20;i++)cout << char(prosto_bok);
		if(x0==4){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Browarnictwo ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(browarnictwo==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Browarnictwo ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Browarnictwo ";
		}
		}
		if(kapitol.lvl>=3){
		
		gotoxy(8,11);
				if(x0==5){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Mechanika ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(mechanika==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Mechanika ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Mechanika ";
		}
		for(int i=0;i<20;i++)cout << char(prosto_bok);
		if(x0==6){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Hutnictwo ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(hutnictwo==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Hutnictwo ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Hutnictwo ";
		}
		for(int i=0;i<20;i++)cout << char(prosto_bok);
				if(x0==7){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Waluta ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(waluta==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Waluta ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Waluta ";
		}
		}
		if(kapitol.lvl>=4){
		
		gotoxy(8,15);
				if(x0==8){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Obrobka zelaza ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(obrobka_zelaza==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Obrobka zelaza ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Obrobka zelaza ";
		}
		for(int i=0;i<20;i++)cout << char(prosto_bok);
		if(x0==9){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Infrastruktura ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(infrastruktura==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Infrastruktura ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Infrastruktura ";
		}
		for(int i=0;i<20;i++)cout << char(prosto_bok);
				if(x0==10){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Administracja ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(administracja==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Administracja ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Administracja ";
		}
		for(int i=0;i<20;i++)cout << char(prosto_bok);
				if(x0==11){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Ewangelizacja ";
			SetConsoleTextAttribute( hOut, 8 );

		}else{
		if(ewangelizacja==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Ewangelizacja ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Ewangelizacja ";
		}
	}
	if(kapitol.lvl>=5){
	
			gotoxy(8,19);
				if(x0==12){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Obrobka stali ";
			SetConsoleTextAttribute( hOut, 8 );

			
		}else{
		if(obrobka_stali==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Obrobka stali ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Obrobka stali ";
		}
		for(int i=0;i<20;i++)cout << char(prosto_bok);
		if(x0==13){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Nawigacja ";
			SetConsoleTextAttribute( hOut, 8 );

			
		}else{
		if(nawigacja==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Nawigacja ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Nawigacja ";
		}
			for(int i=0;i<20;i++)cout << char(prosto_bok);
		if(x0==14){
			SetConsoleTextAttribute( hOut, 2 );
			cout << " Sztuka ";
			SetConsoleTextAttribute( hOut, 8 );

			
		}else{
		if(sztuka==true){
			SetConsoleTextAttribute( hOut, 13 );
			cout << " Sztuka ";
			SetConsoleTextAttribute( hOut, 8 );
		}else	
		cout << " Sztuka ";
		}
	}
	SetConsoleTextAttribute( hOut, 10 );
		gotoxy(8,60);
		cout << "Zywnosc: " << zywnosc<<"("<<miasto[1].przychod_zywnosc<<")" <<"  Drewno: " << drewno <<"("<<miasto[1].przychod_drewno<<")" <<
 		"  Kamien: " << kamien<<"("<<miasto[1].przychod_kamien<<")" << "  Wiara: " << wiara <<"("<<miasto[1].przychod_wiara<<")" << "  Max. Zolnierzy: " << max_zolnierzy << "  Zloto: " 
 		<< zloto << "("<<miasto[1].przychod_zloto<<")" <<"  Produckja: " << miasto[1].produkcja <<"("<<miasto[1].przychod_produkcja
 		<<")" << "  Ludnosc: "<<miasto[1].ludnosc << "  Nauka: " << nauka<<"("<<miasto[1].przychod_nauka<<")"<<"  Obrona: "<<miasto[1].obrona;
		SetConsoleTextAttribute( hOut, 8 );

		ster=getch();
		
		if(ster==KEY_UP && x0!=0)x0--;
		if(ster==KEY_DOWN && x0!=2 && kapitol.lvl==1)x0++;
		if(ster==KEY_DOWN && x0!=4 && kapitol.lvl==2)x0++;
		if(ster==KEY_DOWN && x0!=7 && kapitol.lvl==3)x0++;
		if(ster==KEY_DOWN && x0!=11 && kapitol.lvl==4)x0++;
		if(ster==KEY_DOWN && x0!=14 && kapitol.lvl==5)x0++;
	
		if(ster=='q' && x0==0){
			gotoxy(0,0);
			menu_stolica=true;
			technologie=false;
			gotoxy(0,0);
			system("CLS");
			x0=0;
			continue;

		}
		
		if(ster=='q' && x0==1 && nauka>=350 && lowiectwo==false)odkryj(&lowiectwo,350,&nauka,"Lowiectwo");
		if(ster=='q' && x0==2 && nauka>=350 && hodowla==false)odkryj(&hodowla,350,&nauka,"Hodowla");
		if(ster=='q' && x0==3 && nauka>=400 && gildie==false)odkryj(&gildie,400,&nauka,"Gildie");
		if(ster=='q' && x0==4 && nauka>=400 && browarnictwo==false){
		odkryj(&browarnictwo,400,&nauka,"Browarnictwo");
		nastepna_tura_domyslnie++;
		}
		if(ster=='q' && x0==5 && nauka>=450 && mechanika==false){
		odkryj(&mechanika,450,&nauka,"Mechanika");
		nastepna_tura_domyslnie++;
	};
		if(ster=='q' && x0==6 && nauka>=450 && hutnictwo==false){
		odkryj(&hutnictwo,450,&nauka,"Hutnictwo");
		pikinier[xm].atak++;
		ciezkozbrojny[xm].atak++;
		elita.atak++;	
		};
		if(ster=='q' && x0==7 && nauka>=450 && waluta==false)odkryj(&waluta,450,&nauka,"Waluta");
		if(ster=='q' && x0==8 && nauka>=500 && obrobka_zelaza==false)odkryj(&obrobka_zelaza,500,&nauka,"Obrobka Zelaza");
		if(ster=='q' && x0==9 && nauka>=500 && infrastruktura==false)odkryj(&infrastruktura,500,&nauka,"Infrastruktura");
		if(ster=='q' && x0==10 && nauka>=500 && administracja==false){
		odkryj(&administracja,500,&nauka,"Administracja");
		nastepna_tura_domyslnie++;
		};
		if(ster=='q' && x0==11 && nauka>=500 && ewangelizacja==false)odkryj(&ewangelizacja,500,&nauka,"Ewangelizacja");
		if(ster=='q' && x0==12 && nauka>=550 && obrobka_stali==false)odkryj(&obrobka_stali,550,&nauka,"Obrobka Stali");
		if(ster=='q' && x0==13 && nauka>=550 && nawigacja==false)odkryj(&nawigacja,550,&nauka,"Nawigacja");
		if(ster=='q' && x0==14 && nauka>=550 && sztuka==false)odkryj(&sztuka,550,&nauka,"Sztuka");

	
	system("CLS");
		
	}
	
	if(rekrutacja==true){
		
		if(ster=='q' && x0==0 && drewno>=jrobotnik[xm].koszt_drewno && miasto[1].ludnosc>=jrobotnik[xm].wielkosc*100 && zloto>=jrobotnik[xm].koszt_zloto && zywnosc>=jrobotnik[xm].koszt_zywnosc && kamien>=jrobotnik[xm].koszt_kamien && miasto[1].produkcja>=jrobotnik[xm].koszt_produkcja){
			if(mapa[miasto[1].x1-1][miasto[1].y1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1]==dom2 || mapa[miasto[1].x1][miasto[1].y1-1]==dom2 || mapa[miasto[1].x1][miasto[1].y1+1]==dom2 || mapa[miasto[1].x1-1][miasto[1].y1-1]==dom2 
			|| mapa[miasto[1].x1-1][miasto[1].y1+1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1-1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1+1]==dom2 ||
			mapa[miasto[1].x1-1][miasto[1].y1]==dom || mapa[miasto[1].x1+1][miasto[1].y1]==dom || mapa[miasto[1].x1][miasto[1].y1-1]==dom || mapa[miasto[1].x1][miasto[1].y1+1]==dom || mapa[miasto[1].x1-1][miasto[1].y1-1]==dom 
			|| mapa[miasto[1].x1-1][miasto[1].y1+1]==dom || mapa[miasto[1].x1+1][miasto[1].y1-1]==dom || mapa[miasto[1].x1+1][miasto[1].y1+1]==dom){
				wystaw_armie(jrobotnik[xm],mapa,0, mapa_jednostek, 1);
				rekrutuj(jrobotnik[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
			}
		}
		if(ster=='q' && x0==1 && drewno>=josadnik.koszt_drewno&& miasto[1].ludnosc>=josadnik.wielkosc*100 && zloto>=josadnik.koszt_zloto && zywnosc>=josadnik.koszt_zywnosc && kamien>=josadnik.koszt_kamien && miasto[1].produkcja>=josadnik.koszt_produkcja){
			if(mapa[miasto[1].x1-1][miasto[1].y1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1]==dom2 || mapa[miasto[1].x1][miasto[1].y1-1]==dom2 || mapa[miasto[1].x1][miasto[1].y1+1]==dom2 || mapa[miasto[1].x1-1][miasto[1].y1-1]==dom2 
			|| mapa[miasto[1].x1-1][miasto[1].y1+1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1-1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1+1]==dom2 ||
			mapa[miasto[1].x1-1][miasto[1].y1]==dom || mapa[miasto[1].x1+1][miasto[1].y1]==dom || mapa[miasto[1].x1][miasto[1].y1-1]==dom || mapa[miasto[1].x1][miasto[1].y1+1]==dom || mapa[miasto[1].x1-1][miasto[1].y1-1]==dom 
			|| mapa[miasto[1].x1-1][miasto[1].y1+1]==dom || mapa[miasto[1].x1+1][miasto[1].y1-1]==dom || mapa[miasto[1].x1+1][miasto[1].y1+1]==dom){
				wystaw_armie(josadnik,mapa,1, mapa_jednostek, 1);
				rekrutuj(josadnik,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
			}
		}
		if(ster=='q' && x0==2 && drewno>=pikinier[xm].koszt_drewno&& miasto[1].ludnosc>=pikinier[xm].wielkosc*100 && zloto>=pikinier[xm].koszt_zloto && zywnosc>=pikinier[xm].koszt_zywnosc && sjednostki[0][2].ilosc<9 && kamien>=pikinier[xm].koszt_kamien && miasto[1].produkcja>=pikinier[xm].koszt_produkcja && koszary.lvl>=1){
				rekrutuj(pikinier[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[0][2].ilosc++;
		}
		if(ster=='q' && x0==3 && drewno>=lucznik[xm].koszt_drewno&& miasto[1].ludnosc>=lucznik[xm].wielkosc*100 && zloto>=lucznik[xm].koszt_zloto && zywnosc>=lucznik[xm].koszt_zywnosc&& sjednostki[0][3].ilosc<9 && kamien>=lucznik[xm].koszt_kamien && miasto[1].produkcja>=lucznik[xm].koszt_produkcja && koszary.lvl>=2 && lowiectwo==true){
				rekrutuj(lucznik[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[0][3].ilosc++;
		}
		if(ster=='q' && x0==4 && drewno>=kusznik[xm].koszt_drewno&& miasto[1].ludnosc>=kusznik[xm].wielkosc*100 && zloto>=kusznik[xm].koszt_zloto && zywnosc>=kusznik[xm].koszt_zywnosc&& sjednostki[0][4].ilosc<9 && kamien>=kusznik[xm].koszt_kamien && miasto[1].produkcja>=kusznik[xm].koszt_produkcja && koszary.lvl>=3 && lowiectwo==true && obrobka_zelaza==true){
				rekrutuj(kusznik[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[0][4].ilosc++;
		}
		if(ster=='q' && x0==5 && drewno>=ciezkozbrojny[xm].koszt_drewno&& miasto[1].ludnosc>=ciezkozbrojny[xm].wielkosc*100 && zloto>=ciezkozbrojny[xm].koszt_zloto && zywnosc>=ciezkozbrojny[xm].koszt_zywnosc&& sjednostki[0][5].ilosc<9 && kamien>=ciezkozbrojny[xm].koszt_kamien && miasto[1].produkcja>=ciezkozbrojny[xm].koszt_produkcja && koszary.lvl>=4 && obrobka_zelaza==true){
				rekrutuj(ciezkozbrojny[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[0][5].ilosc++;
		}
		if(ster=='q' && x0==6 && drewno>=lekka_jazda[xm].koszt_drewno&& miasto[1].ludnosc>=lekka_jazda[xm].wielkosc*100 && zloto>=lekka_jazda[xm].koszt_zloto && zywnosc>=lekka_jazda[xm].koszt_zywnosc&& sjednostki[0][6].ilosc<9 && kamien>=lekka_jazda[xm].koszt_kamien && miasto[1].produkcja>=lekka_jazda[xm].koszt_produkcja && stajnia.lvl>=1){
				rekrutuj(lekka_jazda[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[0][6].ilosc++;
		}
		if(ster=='q' && x0==7 && drewno>=ciezka_jazda[xm].koszt_drewno&& miasto[1].ludnosc>=ciezka_jazda[xm].wielkosc*100 && zloto>=ciezka_jazda[xm].koszt_zloto && zywnosc>=ciezka_jazda[xm].koszt_zywnosc&& sjednostki[0][7].ilosc<9 && kamien>=ciezka_jazda[xm].koszt_kamien && miasto[1].produkcja>=ciezka_jazda[xm].koszt_produkcja && stajnia.lvl>=3 && obrobka_stali==true){
				rekrutuj(ciezka_jazda[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[0][7].ilosc++;
		}
		if(ster=='q' && x0==8 && drewno>=taran[xm].koszt_drewno&& miasto[1].ludnosc>=taran[xm].wielkosc*100 && zloto>=taran[xm].koszt_zloto && zywnosc>=taran[xm].koszt_zywnosc && kamien>=taran[xm].koszt_kamien&& sjednostki[0][8].ilosc<9 && miasto[1].produkcja>=taran[xm].koszt_produkcja && warsztat.lvl>=2){
				rekrutuj(taran[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[0][8].ilosc++;
		}
		if(ster=='q' && x0==9 && drewno>=elita.koszt_drewno && miasto[1].ludnosc>=elita.wielkosc*100&& zloto>=elita.koszt_zloto && zywnosc>=elita.koszt_zywnosc && kamien>=elita.koszt_kamien&& sjednostki[0][9].ilosc<9 && miasto[1].produkcja>=elita.koszt_produkcja && akademia.lvl>=1 && obrobka_stali==true){
				rekrutuj(elita,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[0][9].ilosc++;
		}
		
	}
	
	if(bplac==true){
		
		if(ster==KEY_RIGHT && sjednostki[0][x0+2].ilosc>0 && liczba_zolnierzy+sjednostki[0][x0+2].wielkosc<=max_zolnierzy){
			if(x0==0){
			armia[liczba_armii+1].pikinierzy++;
			armia[liczba_armii+1].wielkosc+=pikinier[xm].wielkosc;
			sjednostki[0][2].ilosc--;
			liczba_zolnierzy+=pikinier[xm].wielkosc;
			}
			if(x0==1){
			armia[liczba_armii+1].lucznicy++;
			armia[liczba_armii+1].wielkosc+=lucznik[xm].wielkosc;
			sjednostki[0][3].ilosc--;
			liczba_zolnierzy+=lucznik[xm].wielkosc;
			}
			if(x0==2){
			armia[liczba_armii+1].kusznicy++;
			armia[liczba_armii+1].wielkosc+=kusznik[xm].wielkosc;
			sjednostki[0][4].ilosc--;
			liczba_zolnierzy+=kusznik[xm].wielkosc;
			}
			if(x0==3){
			armia[liczba_armii+1].ciezkozbrojni++;
			armia[liczba_armii+1].wielkosc+=ciezkozbrojny[xm].wielkosc;
			sjednostki[0][5].ilosc--;
			liczba_zolnierzy+=ciezkozbrojny[xm].wielkosc;
			}
			if(x0==4){
			armia[liczba_armii+1].lekka_jazda++;
			armia[liczba_armii+1].wielkosc+=lekka_jazda[xm].wielkosc;
			sjednostki[0][6].ilosc--;
			liczba_zolnierzy+=lekka_jazda[xm].wielkosc;
			}
			if(x0==5){
			armia[liczba_armii+1].ciezka_jazda++;
			armia[liczba_armii+1].wielkosc+=ciezka_jazda[xm].wielkosc;
			sjednostki[0][7].ilosc--;
			liczba_zolnierzy+=ciezka_jazda[xm].wielkosc;
			}
			if(x0==6){
			armia[liczba_armii+1].tarany++;
			armia[liczba_armii+1].wielkosc+=taran[xm].wielkosc;
			sjednostki[0][8].ilosc--;
			liczba_zolnierzy+=taran[xm].wielkosc;
			}
			if(x0==7){
			armia[liczba_armii+1].elity++;
			armia[liczba_armii+1].wielkosc+=elita.wielkosc;
			sjednostki[0][9].ilosc--;
			liczba_zolnierzy+=elita.wielkosc;
			}	
		}
		if(ster==KEY_LEFT && armia[liczba_armii+1].pikinierzy>0 && x0==0){
			armia[liczba_armii+1].pikinierzy--;
			armia[liczba_armii+1].wielkosc-=pikinier[xm].wielkosc;
			sjednostki[0][2].ilosc++;
			liczba_zolnierzy-=pikinier[xm].wielkosc;
		}
		if(ster==KEY_LEFT && armia[liczba_armii+1].lucznicy>0 && x0==1){
			armia[liczba_armii+1].lucznicy--;
			armia[liczba_armii+1].wielkosc-=lucznik[xm].wielkosc;
			sjednostki[0][3].ilosc++;
			liczba_zolnierzy-=lucznik[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].kusznicy>0 && x0==2){
			armia[liczba_armii+1].kusznicy--;
			armia[liczba_armii+1].wielkosc-=kusznik[xm].wielkosc;
			sjednostki[0][4].ilosc++;
			liczba_zolnierzy-=kusznik[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].ciezkozbrojni>0 && x0==3){
			armia[liczba_armii+1].ciezkozbrojni--;
			armia[liczba_armii+1].wielkosc-=ciezkozbrojny[xm].wielkosc;
			sjednostki[0][5].ilosc++;
			liczba_zolnierzy-=ciezkozbrojny[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].lekka_jazda>0 && x0==4){
			armia[liczba_armii+1].lekka_jazda--;
			armia[liczba_armii+1].wielkosc-=lekka_jazda[xm].wielkosc;
			sjednostki[0][6].ilosc++;
			liczba_zolnierzy-=lekka_jazda[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].ciezka_jazda>0 && x0==5){
			armia[liczba_armii+1].ciezka_jazda--;
			armia[liczba_armii+1].wielkosc-=ciezka_jazda[xm].wielkosc;
			sjednostki[0][7].ilosc++;
			liczba_zolnierzy-=ciezka_jazda[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].tarany>0 && x0==6){
			armia[liczba_armii+1].tarany--;
			armia[liczba_armii+1].wielkosc-=taran[xm].wielkosc;
			sjednostki[0][8].ilosc++;
			liczba_zolnierzy-=taran[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].elity>0 && x0==7){
			armia[liczba_armii+1].elity--;
			armia[liczba_armii+1].wielkosc-=elita.wielkosc;
			sjednostki[0][9].ilosc++;
			liczba_zolnierzy-=elita.wielkosc;
			}	
		
		if(ster=='e' && armia[liczba_armii+1].wielkosc>0 && liczba_armii<=50){
			
			liczba_armii++;
			wystaw_armie(jarmia,mapa,45,mapa_jednostek, 1);
			bplac=false;
			menu_stolica=true;
			system("CLS");
			continue;
		}
		
	}
	if(najmij==true){
				
		if(ster=='q' && x0==0  && zloto>=jrobotnik[xm].koszt_zloto*3 || ster=='q' && x0==0 && wiara>=jrobotnik[xm].koszt_wiara){
			if(mapa[miasto[1].x1-1][miasto[1].y1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1]==dom2 || mapa[miasto[1].x1][miasto[1].y1-1]==dom2 || mapa[miasto[1].x1][miasto[1].y1+1]==dom2 || mapa[miasto[1].x1-1][miasto[1].y1-1]==dom2 
			|| mapa[miasto[1].x1-1][miasto[1].y1+1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1-1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1+1]==dom2 ||
			mapa[miasto[1].x1-1][miasto[1].y1]==dom || mapa[miasto[1].x1+1][miasto[1].y1]==dom || mapa[miasto[1].x1][miasto[1].y1-1]==dom || mapa[miasto[1].x1][miasto[1].y1+1]==dom || mapa[miasto[1].x1-1][miasto[1].y1-1]==dom 
			|| mapa[miasto[1].x1-1][miasto[1].y1+1]==dom || mapa[miasto[1].x1+1][miasto[1].y1-1]==dom || mapa[miasto[1].x1+1][miasto[1].y1+1]==dom){
				najmijv(jrobotnik[xm],&wiara,&najmij,&zloto,&x0,&menu_stolica);
				wystaw_armie(jrobotnik[xm],mapa,0, mapa_jednostek,  1);
				
			}
		}
		if(ster=='q' && x0==1 && zloto>=josadnik.koszt_zloto*3 || ster=='q' && x0==1 && wiara>=josadnik.koszt_wiara){
			if(mapa[miasto[1].x1-1][miasto[1].y1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1]==dom2 || mapa[miasto[1].x1][miasto[1].y1-1]==dom2 || mapa[miasto[1].x1][miasto[1].y1+1]==dom2 || mapa[miasto[1].x1-1][miasto[1].y1-1]==dom2 
			|| mapa[miasto[1].x1-1][miasto[1].y1+1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1-1]==dom2 || mapa[miasto[1].x1+1][miasto[1].y1+1]==dom2 ||
			mapa[miasto[1].x1-1][miasto[1].y1]==dom || mapa[miasto[1].x1+1][miasto[1].y1]==dom || mapa[miasto[1].x1][miasto[1].y1-1]==dom || mapa[miasto[1].x1][miasto[1].y1+1]==dom || mapa[miasto[1].x1-1][miasto[1].y1-1]==dom 
			|| mapa[miasto[1].x1-1][miasto[1].y1+1]==dom || mapa[miasto[1].x1+1][miasto[1].y1-1]==dom || mapa[miasto[1].x1+1][miasto[1].y1+1]==dom){
				najmijv(josadnik,&wiara,&najmij,&zloto,&x0,&menu_stolica);
				rekrutuj(josadnik,&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
			}
		}
		if(ster=='q' && x0==2  && zloto>=pikinier[xm].koszt_zloto*3 || ster=='q' && x0==2 && wiara>=pikinier[xm].koszt_wiara){
				najmijv(pikinier[xm],&wiara,&najmij,&zloto,&x0,&menu_stolica);
				sjednostki[0][2].ilosc++;
		}
		if(ster=='q' && x0==3 && zloto>=lucznik[xm].koszt_zloto*3 || ster=='q' && x0==3 && wiara>=lucznik[xm].koszt_wiara){
				najmijv(lucznik[xm],&wiara,&najmij,&zloto,&x0,&menu_stolica);
				sjednostki[0][3].ilosc++;
		}
		if(ster=='q' && x0==4 && zloto>=kusznik[xm].koszt_zloto*3&& oboz.lvl>=2 || ster=='q' && x0==4 && wiara>=kusznik[xm].koszt_wiara && oboz.lvl>=2){
				najmijv(kusznik[xm],&wiara,&najmij,&zloto,&x0,&menu_stolica);
				sjednostki[0][4].ilosc++;
		}
		if(ster=='q' && x0==5 && zloto>=ciezkozbrojny[xm].koszt_zloto*3&& oboz.lvl>=2 || ster=='q' && x0==5 && wiara>=ciezkozbrojny[xm].koszt_wiara&& oboz.lvl>=2){
				najmijv(ciezkozbrojny[xm],&wiara,&najmij,&zloto,&x0,&menu_stolica);
				sjednostki[0][5].ilosc++;
		}
		if(ster=='q' && x0==6 && zloto>=lekka_jazda[xm].koszt_zloto*3 && oboz.lvl>=2|| ster=='q' && x0==6 && wiara>=lekka_jazda[xm].koszt_wiara&& oboz.lvl>=2){
						najmijv(lekka_jazda[xm],&wiara,&najmij,&zloto,&x0,&menu_stolica);
				sjednostki[0][6].ilosc++;
		}
		if(ster=='q' && x0==7 && zloto>=ciezka_jazda[xm].koszt_zloto*3 && oboz.lvl>=3|| ster=='q' && x0==7 && wiara>=ciezka_jazda[xm].koszt_wiara&& oboz.lvl>=3){
				najmijv(ciezka_jazda[xm],&wiara,&najmij,&zloto,&x0,&menu_stolica);
				sjednostki[0][7].ilosc++;
		}
		if(ster=='q' && x0==8 && zloto>=taran[xm].koszt_zloto*3 && oboz.lvl>=3|| ster=='q' && x0==8 && wiara>=taran[xm].koszt_wiara&& oboz.lvl>=3){
				najmijv(taran[xm],&wiara,&najmij,&zloto,&x0,&menu_stolica);
				sjednostki[0][8].ilosc++;
		}
		if(ster=='q' && x0==9 && zloto>=elita.koszt_zloto*3 && oboz.lvl>=3|| ster=='q' && x0==9 && wiara>=elita.koszt_wiara&& oboz.lvl>=3){
				najmijv(elita,&wiara,&najmij,&zloto,&x0,&menu_stolica);
				sjednostki[0][9].ilosc++;
		}
		
	}
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////



while(miasto[xm].menu_osady==true){

	
	if(x0==0)aktualna=rada_osady[xm];
	if(x0==1)aktualna=mieszkalna_osada[xm];
	if(x0==2)aktualna=handlowa_osada[xm];
	if(x0==3)aktualna=wojskowa_osada[xm];
	if(x0==4)aktualna=robotnicza_osada[xm];
	if(x0==5)aktualna=koszary_osada[xm];
	if(x0==6)aktualna=biblioteka_osada[xm];
	if(x0==7)aktualna=park_osada[xm];
	if(x0==8)aktualna=pomnik_osada[xm];
	if(x0==9)aktualna=port_osada[xm];
	if(x0==10)aktualna=tawerna_osada[xm];
	if(x0==11)aktualna=magazyn_osada[xm];
	if(x0==12)aktualna=mlyn_osada[xm];
	if(x0==13)aktualna=kamieniarz_osada[xm];
	if(x0==14)aktualna=kosciol_osada[xm];
	if(x0==15)aktualna=weglarz_osada[xm];
	if(x0==16)aktualna=warsztat_osada[xm];
	if(x0==17)aktualna=stajnia_osada[xm];

	
	
	gotoxy(3,3);
	cout << "Jestes w osadzie "<<miasto[xm].nazwa;
	
	SetConsoleTextAttribute( hOut, 10 );
gotoxy(8,60);
cout << "Zywnosc: " << zywnosc<<"("<<miasto[xm].przychod_zywnosc<<")" <<"  Drewno: " << drewno <<"("<<miasto[xm].przychod_drewno<<")" <<
 "  Kamien: " << kamien<<"("<<miasto[xm].przychod_kamien<<")" << "  Wiara: " << wiara <<"("<<miasto[xm].przychod_wiara<<")" << "  Max. Zolnierzy: " << max_zolnierzy <<"("<<liczba_zolnierzy<<")"<< "  Zloto: " 
 << zloto << "("<<miasto[xm].przychod_zloto<<")" <<"  Produckja: " << miasto[xm].produkcja <<"("<<miasto[xm].przychod_produkcja
 <<")" << "  Ludnosc: "<<miasto[xm].ludnosc << "  Nauka: " << nauka<<"("<<miasto[xm].przychod_nauka<<")"<<"  Obrona: "<<miasto[xm].obrona << "  Podatek: "<<miasto[xm].podatek;
SetConsoleTextAttribute( hOut, 8 );
	gotoxy(8,61);
	cout << xm <<"   "<< rada_osady[xm].lvl;

if(menu_osada==true){
	gotoxy(50,1);
cout << "MENU OSADY                    ";
gotoxy(40,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(40,4);
cout <<blok<< "                          "<<blok;
gotoxy(40,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Mapa Swiata            "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout << blok<<"   Mapa Swiata            "<<blok; 
gotoxy(40,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout << "   Buduj                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout <<blok<< "   Buduj                  "<<blok; 
gotoxy(40,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Rekrutuj               "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Rekrutuj               "<<blok; 

gotoxy(40,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Plac Manewrowy         "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Plac Manewrowy         "<<blok; 
gotoxy(40,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Zbierz Podatek         "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Zbierz Podatek         "<<blok; 
gotoxy(40,10);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Zmien nazwe            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Zmien nazwe            "<<blok; 

gotoxy(40,11);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Rozbudowa              "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Rozbudowa              "<<blok; 
gotoxy(40,12);
cout <<blok<< "                          "<<blok;
gotoxy(40,13);
for(int i=0;i<28;i++)cout << blok;
}

	if(menu_budowy==true || rozbudowa==true){
gotoxy(50,1);
if(menu_budowy==true && rozbudowa==false)
cout << "MENU BUDOWY                    ";
budowlanka_osada(aktualna);
if(rozbudowa==true){
cout << "MENU ROZBUDOWY                 ";
rozbudowlanka_osada(x0, aktualna);

}
gotoxy(40,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(40,4);
cout <<blok<< "                          "<<blok;
gotoxy(40,5);
if(x0==0){
cout<< blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"Rada Osady("<<rada_osady[xm].lvl<<"/4)           ";
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else{
if(rada_osady[xm].budowa==true)
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"Rada Osady("<<rada_osady[xm].lvl<<"/4)           "<<blok;
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"Dzielnica Mieszkalna ("<<mieszkalna_osada[xm].lvl<<"/2)"; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(mieszkalna_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "Dzielnica Mieszkalna ("<<mieszkalna_osada[xm].lvl<<"/2)"<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<" Dzielnica Handlowa ("<<handlowa_osada[xm].lvl<<"/2) "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(handlowa_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< " Dzielnica Handlowa ("<<handlowa_osada[xm].lvl<<"/2) "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<" Dzielnica Wojskowa ("<<wojskowa_osada[xm].lvl<<"/2) "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(wojskowa_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<" Dzielnica Wojskowa ("<<wojskowa_osada[xm].lvl<<"/2) "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"Dzielnica Robotnicza ("<<robotnicza_osada[xm].lvl<<"/2)"; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(robotnicza_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"Dzielnica Robotnicza ("<<robotnicza_osada[xm].lvl<<"/2)"<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,10);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Koszary ("<<koszary_osada[xm].lvl<<"/3)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(koszary_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Koszary ("<<koszary_osada[xm].lvl<<"/3)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}


gotoxy(40,11);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Biblioteka ("<<biblioteka_osada[xm].lvl<<"/2)       "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(biblioteka_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Biblioteka ("<<biblioteka_osada[xm].lvl<<"/2)       "<<blok;
SetConsoleTextAttribute( hOut, 8 );
} 
gotoxy(40,12);
if(x0==7){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Park ("<<park_osada[xm].lvl<<"/2)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(park_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Park ("<<park_osada[xm].lvl<<"/2)             "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,13);
if(x0==8){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Pomnik ("<<pomnik_osada[xm].lvl<<"/2)           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(pomnik_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Pomnik ("<<pomnik_osada[xm].lvl<<"/2)           "<<blok;
SetConsoleTextAttribute( hOut, 8 );
} 

gotoxy(40,14);
if(x0==9){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Port ("<<port_osada[xm].lvl<<"/2)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(port_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Port ("<<port_osada[xm].lvl<<"/2)             "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
} 


gotoxy(40,15);
if(x0==10){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Tawerna ("<<tawerna_osada[xm].lvl<<"/2)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(tawerna_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Tawerna ("<<tawerna_osada[xm].lvl<<"/2)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,16);
if(x0==11){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Magazyn ("<<magazyn_osada[xm].lvl<<"/3)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(magazyn_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Magazyn ("<<magazyn_osada[xm].lvl<<"/3)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,17);
if(x0==12){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Mlyn ("<<mlyn_osada[xm].lvl<<"/3)             "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(mlyn_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Mlyn ("<<mlyn_osada[xm].lvl<<"/3)             "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}

gotoxy(40,18);
if(x0==13){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kamieniarz ("<<kamieniarz_osada[xm].lvl<<"/3)       "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(kamieniarz_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Kamieniarz ("<<kamieniarz_osada[xm].lvl<<"/3)       "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}

gotoxy(40,19);
if(x0==14){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kosciol ("<<kosciol_osada[xm].lvl<<"/2)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(kosciol_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Kosciol ("<<kosciol_osada[xm].lvl<<"/2)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}

gotoxy(40,20);
if(x0==15){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Weglarnia ("<<weglarz_osada[xm].lvl<<"/2)        "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(weglarz_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Weglarnia ("<<weglarz_osada[xm].lvl<<"/2)        "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,21);
if(x0==16){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Warsztat ("<<warsztat_osada[xm].lvl<<"/2)         "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(warsztat_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<< "   Warsztat ("<<warsztat_osada[xm].lvl<<"/2)         "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,22);
if(x0==17){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Stajnia ("<<stajnia_osada[xm].lvl<<"/3)          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else{
if(stajnia_osada[xm].budowa==true)	
SetConsoleTextAttribute( hOut, 13 );
cout <<blok<<"   Stajnia ("<<stajnia_osada[xm].lvl<<"/3)          "<<blok; 
SetConsoleTextAttribute( hOut, 8 );
}
gotoxy(40,23);
if(x0==18){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Powrot                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Powrot                 "<<blok;
gotoxy(40,24);
cout <<blok<< "                          "<<blok;
gotoxy(40,25);
for(int i=0;i<28;i++)cout << blok;
}


if(nazwa==true){
	gotoxy(54,25);
	for(int i=0;i<40;i++)cout << blok;
	gotoxy(54,26);
	cout << blok;
	for(int i=0;i<38;i++)cout<< " ";
	cout << blok;
	gotoxy(54,28);
	cout << blok;
	for(int i=0;i<38;i++)cout<< " ";
	cout << blok;
	gotoxy(54,29);
	for(int i=0;i<40;i++)cout << blok;
	gotoxy(90,27);
	cout << "   " << blok;
	gotoxy(54,27);
	cout <<blok<< "  Wpisz nazwe miasta: ";
	getline(cin, miasto[xm].nazwa);

	gotoxy(54,27);
	for(int i=0;i<28;i++)cout << blok;
	nazwa=false;
	system("CLS");
	continue;
}

	if(bplac==true){
		gotoxy(50,1);
cout << "NAZWA/ILOSC POSIADANYCH/DO ARMII                    ";
rekrutowanka_osada(x0, xm);
pokaz_armie(armia[liczba_armii+1], xm);
gotoxy(40,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(40,4);
cout <<blok<< "                          "<<blok;
gotoxy(40,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Pikinier / "<<sjednostki[xm][2].ilosc<<" / "<<armia[liczba_armii+1].pikinierzy<<"       "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Pikinier / "<<sjednostki[xm][2].ilosc<<" / "<<armia[liczba_armii+1].pikinierzy<<"       "<<blok; 

gotoxy(40,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lucznik / "<<sjednostki[xm][3].ilosc<<" / "<<armia[liczba_armii+1].lucznicy<<"        "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<<"   Lucznik / "<<sjednostki[xm][3].ilosc<<" / "<<armia[liczba_armii+1].lucznicy<<"        ";
gotoxy(40,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kusznik / "<<sjednostki[xm][4].ilosc<<" / "<<armia[liczba_armii+1].kusznicy<<"        "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Kusznik / "<<sjednostki[xm][4].ilosc<<" / "<<armia[liczba_armii+1].kusznicy<<"        "<<blok; 
gotoxy(40,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezkozbrojny / "<<sjednostki[xm][5].ilosc<<" / "<<armia[liczba_armii+1].ciezkozbrojni<<"  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezkozbrojny / "<<sjednostki[xm][5].ilosc<<" / "<<armia[liczba_armii+1].ciezkozbrojni<<"  "<<blok; 

gotoxy(40,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lekka Jazda / "<<sjednostki[xm][6].ilosc<<" / "<<armia[liczba_armii+1].lekka_jazda<<"    "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lekka Jazda / "<<sjednostki[xm][6].ilosc<<" / "<<armia[liczba_armii+1].lekka_jazda<<"    "<<blok; 
gotoxy(40,10);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezka Jazda / "<<sjednostki[xm][7].ilosc<<" / "<<armia[liczba_armii+1].ciezka_jazda<<"   "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezka Jazda / "<<sjednostki[xm][7].ilosc<<" / "<<armia[liczba_armii+1].ciezka_jazda<<"   "<<blok;
gotoxy(40,11);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Taran / "<<sjednostki[xm][8].ilosc<<" / "<<armia[liczba_armii+1].tarany<<"          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Taran / "<<sjednostki[xm][8].ilosc<<" / "<<armia[liczba_armii+1].tarany<<"          "<<blok;
gotoxy(40,12);
if(x0==7){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Powrot                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Powrot                 "<<blok; 
gotoxy(40,13);
cout <<blok<< "                          "<<blok;
gotoxy(40,14);
for(int i=0;i<28;i++)cout << blok;
	}
	
		if(rekrutacja==true){
gotoxy(50,1);
cout << "REKRUTACJA JEDNOSTEK                    ";
rekrutowanka_osada(x0, xm);
gotoxy(40,3);
for(int i=0;i<28;i++)cout << blok;
gotoxy(40,4);
cout <<blok<< "                          "<<blok;
gotoxy(40,5);
if(x0==0){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout <<"   Robotnik               "; 
SetConsoleTextAttribute( hOut, 8 );
cout << blok;
}
else
cout << blok<<"   Robotnik               "<<blok; 
gotoxy(40,6);
if(x0==1){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Pikinier               "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Pikinier               "<<blok; 

gotoxy(40,7);
if(x0==2){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lucznik                "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lucznik                "<<blok; 
gotoxy(40,8);
if(x0==3){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Kusznik                "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Kusznik                "<<blok; 
gotoxy(40,9);
if(x0==4){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezkozbrojny          "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezkozbrojny          "<<blok; 

gotoxy(40,10);
if(x0==5){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Lekka Jazda            "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Lekka Jazda            "<<blok; 
gotoxy(40,11);
if(x0==6){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Ciezka Jazda           "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Ciezka Jazda           "<<blok;
gotoxy(40,12);
if(x0==7){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Taran                  "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Taran                  "<<blok;
gotoxy(40,13);
if(x0==8){
cout << blok;
SetConsoleTextAttribute( hOut, 2 );
cout<<"   Powrot                 "; 
SetConsoleTextAttribute( hOut, 8 );
cout<<blok;
}
else
cout <<blok<< "   Powrot                 "<<blok; 
gotoxy(40,14);
cout <<blok<< "                          "<<blok;
gotoxy(40,15);
for(int i=0;i<28;i++)cout << blok;
}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	
	ster=getch();
	
	if(ster==27){
		miasto[xm].menu_osady=false;
		menu_osada=false;
		rozbudowa=false;
		menu_budowy=false;
		rekrutacja=false;
		bplac=false;
		xm=0;
		mapa_glowna=true;
		menu=true;
		system("CLS");
	}
	
	if(ster=='q' && x0==0 && menu_osada==true){
		miasto[xm].menu_osady=false;
		menu_osada=false;
		xm=0;
		mapa_glowna=true;
		menu=true;
		system("CLS");
	}
	
if(ster==KEY_DOWN && x0!=6 && menu_osada==true || ster==KEY_DOWN && x0!=18 && menu_budowy==true || ster==KEY_DOWN && x0!=18 && rozbudowa==true || ster==KEY_DOWN && x0!=8 && rekrutacja==true || ster==KEY_DOWN && x0!=7 && bplac==true){
	x0++;
	cls();
	continue;
}
if(ster==KEY_UP && x0!=0){
	x0--;
	cls();
	continue;
}

if(ster=='q' && x0==4 && menu_osada==true){
	zloto+=miasto[xm].podatek;

	gotoxy(54,25);
	for(int i=0;i<70;i++)cout << blok;
	gotoxy(54,26);
	cout << blok;
	for(int i=0;i<68;i++)cout<< " ";
	cout << blok;
	gotoxy(54,28);
	cout << blok;
	for(int i=0;i<68;i++)cout<< " ";
	cout << blok;
	gotoxy(54,29);
	for(int i=0;i<70;i++)cout << blok;
	gotoxy(118,27);
	cout << "   " << blok;
	gotoxy(54,27);
	cout <<blok<< "  Zebrales podatek z miasta "<<miasto[xm].nazwa<<" w wysokosci "<<miasto[xm].podatek;
	Sleep(2000);
	miasto[xm].podatek=0;
	system("CLS");
	continue;
}

if(ster=='q' && x0==3 && menu_osada==true){
	menu_osada=false;
	bplac=true;
	x0=0;
	gotoxy(0,0);
	system("CLS");
	continue;

}
if(ster=='q' && x0==7 && bplac==true){
	menu_osada=true;
	bplac=false;
	x0=0;
	gotoxy(0,0);
	system("CLS");
	continue;
}

if(ster=='q' && x0==5 && menu_osada==true){
	nazwa=true;
	gotoxy(0,0);
	system("CLS");
	continue;
}
if(ster=='q' && x0==1 && menu_osada==true){
	menu_osada=false;
	menu_budowy=true;
	gotoxy(0,0);
	system("CLS");
	x0=0;
	continue;

}
if(ster=='q' && x0==18 && menu_budowy==true){
	menu_budowy=false;
	menu_osada=true;
	gotoxy(0,0);
	system("CLS");
	x0=0;
	continue;
}
if(ster=='q' && x0==6 && menu_osada==true){
	menu_osada=false;
	rozbudowa=true;
	gotoxy(0,0);
	system("CLS");
	x0=0;
	continue;

}
if(ster=='q' && x0==18 && rozbudowa==true){
	menu_osada=true;
	rozbudowa=false;
	gotoxy(0,0);
	system("CLS");
	x0=0;
	continue;
}
if(ster=='q' && x0==2 && menu_osada==true){
	menu_osada=false;
	rekrutacja=true;
	gotoxy(0,0);
	system("CLS");
	x0=0;
	continue;

}
if(ster=='q' && x0==8 && rekrutacja==true){
	menu_osada=true;
	rekrutacja=false;
	gotoxy(0,0);
	system("CLS");
	x0=0;
	continue;
}


	

	
	if(bplac==true){
		
		if(ster==KEY_RIGHT && sjednostki[xm][x0+2].ilosc>0 && liczba_zolnierzy+sjednostki[xm][x0+2].wielkosc<=max_zolnierzy){
			if(x0==0){
			armia[liczba_armii+1].pikinierzy++;
			armia[liczba_armii+1].wielkosc+=pikinier[xm].wielkosc;
			sjednostki[xm][2].ilosc--;
			liczba_zolnierzy+=pikinier[xm].wielkosc;
			}
			if(x0==1){
			armia[liczba_armii+1].lucznicy++;
			armia[liczba_armii+1].wielkosc+=lucznik[xm].wielkosc;
			sjednostki[xm][3].ilosc--;
			liczba_zolnierzy+=lucznik[xm].wielkosc;
			}
			if(x0==2){
			armia[liczba_armii+1].kusznicy++;
			armia[liczba_armii+1].wielkosc+=kusznik[xm].wielkosc;
			sjednostki[xm][4].ilosc--;
			liczba_zolnierzy+=kusznik[xm].wielkosc;
			}
			if(x0==3){
			armia[liczba_armii+1].ciezkozbrojni++;
			armia[liczba_armii+1].wielkosc+=ciezkozbrojny[xm].wielkosc;
			sjednostki[xm][5].ilosc--;
			liczba_zolnierzy+=ciezkozbrojny[xm].wielkosc;
			}
			if(x0==4){
			armia[liczba_armii+1].lekka_jazda++;
			armia[liczba_armii+1].wielkosc+=lekka_jazda[xm].wielkosc;
			sjednostki[xm][6].ilosc--;
			liczba_zolnierzy+=lekka_jazda[xm].wielkosc;
			}
			if(x0==5){
			armia[liczba_armii+1].ciezka_jazda++;
			armia[liczba_armii+1].wielkosc+=ciezka_jazda[xm].wielkosc;
			sjednostki[xm][7].ilosc--;
			liczba_zolnierzy+=ciezka_jazda[xm].wielkosc;
			}
			if(x0==6){
			armia[liczba_armii+1].tarany++;
			armia[liczba_armii+1].wielkosc+=taran[xm].wielkosc;
			sjednostki[xm][8].ilosc--;
			liczba_zolnierzy+=taran[xm].wielkosc;
			}
	
		}
		if(ster==KEY_LEFT && armia[liczba_armii+1].pikinierzy>0 && x0==0){
			armia[liczba_armii+1].pikinierzy--;
			armia[liczba_armii+1].wielkosc-=pikinier[xm].wielkosc;
			sjednostki[xm][2].ilosc++;
			liczba_zolnierzy-=pikinier[xm].wielkosc;
		}
		if(ster==KEY_LEFT && armia[liczba_armii+1].lucznicy>0 && x0==1){
			armia[liczba_armii+1].lucznicy--;
			armia[liczba_armii+1].wielkosc-=lucznik[xm].wielkosc;
			sjednostki[xm][3].ilosc++;
			liczba_zolnierzy-=lucznik[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].kusznicy>0 && x0==2){
			armia[liczba_armii+1].kusznicy--;
			armia[liczba_armii+1].wielkosc-=kusznik[xm].wielkosc;
			sjednostki[xm][4].ilosc++;
			liczba_zolnierzy-=kusznik[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].ciezkozbrojni>0 && x0==3){
			armia[liczba_armii+1].ciezkozbrojni--;
			armia[liczba_armii+1].wielkosc-=ciezkozbrojny[xm].wielkosc;
			sjednostki[xm][5].ilosc++;
			liczba_zolnierzy-=ciezkozbrojny[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].lekka_jazda>0 && x0==4){
			armia[liczba_armii+1].lekka_jazda--;
			armia[liczba_armii+1].wielkosc-=lekka_jazda[xm].wielkosc;
			sjednostki[xm][6].ilosc++;
			liczba_zolnierzy-=lekka_jazda[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].ciezka_jazda>0 && x0==5){
			armia[liczba_armii+1].ciezka_jazda--;
			armia[liczba_armii+1].wielkosc-=ciezka_jazda[xm].wielkosc;
			sjednostki[xm][7].ilosc++;
			liczba_zolnierzy-=ciezka_jazda[xm].wielkosc;
			}
		if(ster==KEY_LEFT && armia[liczba_armii+1].tarany>0 && x0==6){
			armia[liczba_armii+1].tarany--;
			armia[liczba_armii+1].wielkosc-=taran[xm].wielkosc;
			sjednostki[xm][8].ilosc++;
			liczba_zolnierzy-=taran[xm].wielkosc;
			}
	
		
		if(ster=='e' && armia[liczba_armii+1].wielkosc>0 &&liczba_armii<=50){
			
			liczba_armii++;
			wystaw_armie(jarmia,mapa,45,mapa_jednostek, xm);
			bplac=false;
			menu_osada=true;
			system("CLS");
			continue;
		}
		
	}
	
	if(rekrutacja==true){
		
		if(ster=='q' && x0==0 && drewno>=jrobotnik[xm].koszt_drewno && miasto[xm].ludnosc>=jrobotnik[xm].wielkosc*100 && zloto>=jrobotnik[xm].koszt_zloto && zywnosc>=jrobotnik[xm].koszt_zywnosc && kamien>=jrobotnik[xm].koszt_kamien && miasto[xm].produkcja>=jrobotnik[xm].koszt_produkcja){
			if(mapa[miasto[xm].x1-1][miasto[xm].y1]==dom2 || mapa[miasto[xm].x1+1][miasto[xm].y1]==dom2 || mapa[miasto[xm].x1][miasto[xm].y1-1]==dom2 || mapa[miasto[xm].x1][miasto[xm].y1+1]==dom2 || mapa[miasto[xm].x1-1][miasto[xm].y1-1]==dom2 
			|| mapa[miasto[xm].x1-1][miasto[xm].y1+1]==dom2 || mapa[miasto[xm].x1+1][miasto[xm].y1-1]==dom2 || mapa[miasto[xm].x1+1][miasto[xm].y1+1]==dom2 ||
			mapa[miasto[xm].x1-1][miasto[xm].y1]==dom || mapa[miasto[xm].x1+1][miasto[xm].y1]==dom || mapa[miasto[xm].x1][miasto[xm].y1-1]==dom || mapa[miasto[xm].x1][miasto[xm].y1+1]==dom || mapa[miasto[xm].x1-1][miasto[xm].y1-1]==dom 
			|| mapa[miasto[xm].x1-1][miasto[xm].y1+1]==dom || mapa[miasto[xm].x1+1][miasto[xm].y1-1]==dom || mapa[miasto[xm].x1+1][miasto[xm].y1+1]==dom){
				wystaw_armie(jrobotnik[xm],mapa,0, mapa_jednostek, xm);
				rekrutuj(jrobotnik[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				menu_osada=true;
			}
		}
		if(ster=='q' && x0==1 && drewno>=pikinier[xm].koszt_drewno&& miasto[xm].ludnosc>=pikinier[xm].wielkosc*100 && zloto>=pikinier[xm].koszt_zloto && zywnosc>=pikinier[xm].koszt_zywnosc && sjednostki[xm][2].ilosc<9 && kamien>=pikinier[xm].koszt_kamien && miasto[xm].produkcja>=pikinier[xm].koszt_produkcja && koszary.lvl>=1){
				rekrutuj(pikinier[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[xm][2].ilosc++;
				menu_osada=true;
		}
		if(ster=='q' && x0==2 && drewno>=lucznik[xm].koszt_drewno&& miasto[xm].ludnosc>=lucznik[xm].wielkosc*100 && zloto>=lucznik[xm].koszt_zloto && zywnosc>=lucznik[xm].koszt_zywnosc&& sjednostki[xm][3].ilosc<9 && kamien>=lucznik[xm].koszt_kamien && miasto[xm].produkcja>=lucznik[xm].koszt_produkcja && koszary.lvl>=2 && lowiectwo==true){
				rekrutuj(lucznik[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[xm][3].ilosc++;
				menu_osada=true;
		}
		if(ster=='q' && x0==3 && drewno>=kusznik[xm].koszt_drewno&& miasto[xm].ludnosc>=kusznik[xm].wielkosc*100 && zloto>=kusznik[xm].koszt_zloto && zywnosc>=kusznik[xm].koszt_zywnosc&& sjednostki[xm][4].ilosc<9 && kamien>=kusznik[xm].koszt_kamien && miasto[xm].produkcja>=kusznik[xm].koszt_produkcja && koszary.lvl>=3 && lowiectwo==true && obrobka_zelaza==true){
				rekrutuj(kusznik[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[xm][4].ilosc++;
				menu_osada=true;
		}
		if(ster=='q' && x0==4 && drewno>=ciezkozbrojny[xm].koszt_drewno&& miasto[xm].ludnosc>=ciezkozbrojny[xm].wielkosc*100 && zloto>=ciezkozbrojny[xm].koszt_zloto && zywnosc>=ciezkozbrojny[xm].koszt_zywnosc&& sjednostki[xm][5].ilosc<9 && kamien>=ciezkozbrojny[xm].koszt_kamien && miasto[xm].produkcja>=ciezkozbrojny[xm].koszt_produkcja && koszary.lvl>=4 && obrobka_zelaza==true){
				rekrutuj(ciezkozbrojny[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[xm][5].ilosc++;
				menu_osada=true;
		}
		if(ster=='q' && x0==5 && drewno>=lekka_jazda[xm].koszt_drewno&& miasto[xm].ludnosc>=lekka_jazda[xm].wielkosc*100 && zloto>=lekka_jazda[xm].koszt_zloto && zywnosc>=lekka_jazda[xm].koszt_zywnosc&& sjednostki[xm][6].ilosc<9 && kamien>=lekka_jazda[xm].koszt_kamien && miasto[xm].produkcja>=lekka_jazda[xm].koszt_produkcja && stajnia.lvl>=1){
				rekrutuj(lekka_jazda[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[xm][6].ilosc++;
				menu_osada=true;
		}
		if(ster=='q' && x0==6 && drewno>=ciezka_jazda[xm].koszt_drewno&& miasto[xm].ludnosc>=ciezka_jazda[xm].wielkosc*100 && zloto>=ciezka_jazda[xm].koszt_zloto && zywnosc>=ciezka_jazda[xm].koszt_zywnosc&& sjednostki[xm][7].ilosc<9 && kamien>=ciezka_jazda[xm].koszt_kamien && miasto[xm].produkcja>=ciezka_jazda[xm].koszt_produkcja && stajnia.lvl>=3 && obrobka_stali==true){
				rekrutuj(ciezka_jazda[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[xm][7].ilosc++;
				menu_osada=true;
		}
		if(ster=='q' && x0==7 && drewno>=taran[xm].koszt_drewno&& miasto[xm].ludnosc>=taran[xm].wielkosc*100 && zloto>=taran[xm].koszt_zloto && zywnosc>=taran[xm].koszt_zywnosc && kamien>=taran[xm].koszt_kamien&& sjednostki[xm][8].ilosc<9 && miasto[xm].produkcja>=taran[xm].koszt_produkcja && warsztat.lvl>=2){
				rekrutuj(taran[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rekrutacja,&menu_stolica,&x0);
				sjednostki[xm][8].ilosc++;
				menu_osada=true;
		}
	}
	
	////////////////////////buwodanko/////////////////////
	
	
		if(ster=='q' && x0==0 && rozbudowa==true && rada_osady[xm].lvl==1 && kapitol.lvl>=1 && drewno>=rada_osady[xm].koszt_drewno && kamien>=rada_osady[xm].koszt_kamien && zywnosc>=rada_osady[xm].koszt_zywnosc && zloto>=rada_osady[xm].koszt_zloto && miasto[xm].produkcja>=rada_osady[xm].koszt_produkcja){
			rada_osady[xm].lvl++;
			rozbuduj_osada(rada_osady[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(rada_osady[xm]);
			jrobotnik[xm].koszt_produkcja-=25;
			zwieksz_przychod_osada(rada_osady[xm],&przychod_nauka,&max_zolnierzy, xm);
		}
		if(ster=='q' && x0==0 && rozbudowa==true && rada_osady[xm].lvl==2 && kapitol.lvl>=2 && drewno>=rada_osady[xm].koszt_drewno && kamien>=rada_osady[xm].koszt_kamien && zywnosc>=rada_osady[xm].koszt_zywnosc && zloto>=rada_osady[xm].koszt_zloto && miasto[xm].produkcja>=rada_osady[xm].koszt_produkcja){
			rada_osady[xm].lvl++;
			rozbuduj_osada(rada_osady[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(rada_osady[xm]);
			jrobotnik[xm].koszt_produkcja-=25;
			zwieksz_przychod_osada(rada_osady[xm],&przychod_nauka,&max_zolnierzy, xm);
		}
				if(ster=='q' && x0==0 && rozbudowa==true && rada_osady[xm].lvl==3 && kapitol.lvl>=3 && drewno>=rada_osady[xm].koszt_drewno && kamien>=rada_osady[xm].koszt_kamien && zywnosc>=rada_osady[xm].koszt_zywnosc && zloto>=rada_osady[xm].koszt_zloto && miasto[xm].produkcja>=rada_osady[xm].koszt_produkcja){
			rada_osady[xm].lvl++;
			rozbuduj_osada(rada_osady[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(rada_osady[xm]);
			jrobotnik[xm].koszt_produkcja-=25;
			zwieksz_przychod_osada(rada_osady[xm],&przychod_nauka,&max_zolnierzy, xm);
		}

				//////////////////
				if(ster=='q' && x0==1 && menu_budowy==true && mieszkalna_osada[xm].lvl==0&&rada_osady[xm].lvl>=1 && drewno>=mieszkalna_osada[xm].koszt_drewno && kamien>=mieszkalna_osada[xm].koszt_kamien && zywnosc>=mieszkalna_osada[xm].koszt_zywnosc && zloto>=mieszkalna_osada[xm].koszt_zloto && miasto[xm].produkcja>=mieszkalna_osada[xm].koszt_produkcja){
					mieszkalna_osada[xm].lvl++;
					zbuduj_osada(mieszkalna_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0, xm);
					zwieksz_koszt_osada(mieszkalna_osada[xm]);
					zwieksz_przychod_osada(mieszkalna_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
				}
		if(ster=='q' && rozbudowa==true && x0==1&& mieszkalna_osada[xm].lvl==1&&rada_osady[xm].lvl>=2 && drewno>=mieszkalna_osada[xm].koszt_drewno && kamien>=mieszkalna_osada[xm].koszt_kamien && zywnosc>=mieszkalna_osada[xm].koszt_zywnosc && zloto>=mieszkalna_osada[xm].koszt_zloto && miasto[xm].produkcja>=mieszkalna_osada[xm].koszt_produkcja){
		
			mieszkalna_osada[xm].lvl++;
			rozbuduj_osada(mieszkalna_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(mieszkalna_osada[xm]);
			zwieksz_przychod_osada(mieszkalna_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
		}

			//////////////////
				if(ster=='q' && x0==2 && menu_budowy==true&& handlowa_osada[xm].lvl==0 &&rada_osady[xm].lvl>=2 && drewno>=handlowa_osada[xm].koszt_drewno && kamien>=handlowa_osada[xm].koszt_kamien && zywnosc>=handlowa_osada[xm].koszt_zywnosc && zloto>=handlowa_osada[xm].koszt_zloto && miasto[xm].produkcja>=handlowa_osada[xm].koszt_produkcja){
	
			handlowa_osada[xm].lvl++;
			zbuduj_osada(handlowa_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(handlowa_osada[xm]);
			zwieksz_przychod_osada(handlowa_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
	}
		if(ster=='q' && rozbudowa==true&& x0==2&& handlowa_osada[xm].lvl==1&&rada_osady[xm].lvl>=3 && drewno>=handlowa_osada[xm].koszt_drewno && kamien>=handlowa_osada[xm].koszt_kamien && zywnosc>=handlowa_osada[xm].koszt_zywnosc && zloto>=handlowa_osada[xm].koszt_zloto && miasto[xm].produkcja>=handlowa_osada[xm].koszt_produkcja){
		
			handlowa_osada[xm].lvl++;
			rozbuduj_osada(handlowa_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(handlowa_osada[xm]);
			zwieksz_przychod_osada(handlowa_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
    	}
			//////////////////

		if(ster=='q' && menu_budowy==true&& x0==3&& wojskowa_osada[xm].lvl==0&&rada_osady[xm].lvl>=2 && drewno>=wojskowa_osada[xm].koszt_drewno && kamien>=wojskowa_osada[xm].koszt_kamien && zywnosc>=wojskowa_osada[xm].koszt_zywnosc && zloto>=wojskowa_osada[xm].koszt_zloto && miasto[xm].produkcja>=wojskowa_osada[xm].koszt_produkcja){
			wojskowa_osada[xm].lvl++;
			zbuduj_osada(wojskowa_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(wojskowa_osada[xm]);
			zwieksz_przychod_osada(wojskowa_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
			miasto[xm].obrona=miasto[xm].obrona+10;
    	}
    	if(ster=='q' && rozbudowa==true&& x0==3&& wojskowa_osada[xm].lvl==1&&rada_osady[xm].lvl>=3&& drewno>=wojskowa_osada[xm].koszt_drewno && kamien>=wojskowa_osada[xm].koszt_kamien && zywnosc>=wojskowa_osada[xm].koszt_zywnosc && zloto>=wojskowa_osada[xm].koszt_zloto && miasto[xm].produkcja>=wojskowa_osada[xm].koszt_produkcja){
			wojskowa_osada[xm].lvl++;
			rozbuduj_osada(wojskowa_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(wojskowa_osada[xm]);
			zwieksz_przychod_osada(wojskowa_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			
			miasto[xm].obrona=miasto[xm].obrona+15;
    	}
			
			//////////////////

		if(ster=='q' && menu_budowy==true&& x0==4&& robotnicza_osada[xm].lvl==0&&rada_osady[xm].lvl>=1 && drewno>=robotnicza_osada[xm].koszt_drewno && kamien>=robotnicza_osada[xm].koszt_kamien && zywnosc>=robotnicza_osada[xm].koszt_zywnosc && zloto>=robotnicza_osada[xm].koszt_zloto && miasto[xm].produkcja>=robotnicza_osada[xm].koszt_produkcja){
			robotnicza_osada[xm].lvl++;
			zbuduj_osada(robotnicza_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(robotnicza_osada[xm]);
			zwieksz_przychod_osada(robotnicza_osada[xm],&przychod_nauka,&max_zolnierzy, xm);

    	}
    	if(ster=='q' && rozbudowa==true&& x0==4&& robotnicza_osada[xm].lvl==1&&rada_osady[xm].lvl>=2 && drewno>=robotnicza_osada[xm].koszt_drewno && kamien>=robotnicza_osada[xm].koszt_kamien && zywnosc>=robotnicza_osada[xm].koszt_zywnosc && zloto>=robotnicza_osada[xm].koszt_zloto && miasto[xm].produkcja>=robotnicza_osada[xm].koszt_produkcja){
			robotnicza_osada[xm].lvl++;
			rozbuduj_osada(robotnicza_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(robotnicza_osada[xm]);
			zwieksz_przychod_osada(robotnicza_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			

    	}
			
		///////////////////////
	
		if(ster=='q' && menu_budowy==true && x0==5&& koszary_osada[xm].lvl==0 && rada_osady[xm].lvl>=1 && drewno>=koszary_osada[xm].koszt_drewno && kamien>=koszary_osada[xm].koszt_kamien && zywnosc>=koszary_osada[xm].koszt_zywnosc && zloto>=koszary_osada[xm].koszt_zloto && miasto[xm].produkcja>=koszary_osada[xm].koszt_produkcja){
			koszary_osada[xm].lvl++;
			zbuduj_osada(koszary_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(koszary_osada[xm]);
			zwieksz_przychod_osada(koszary_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			pikinier[xm].koszt_produkcja=pikinier[xm].koszt_produkcja-25;
    	}	
		if(ster=='q' && rozbudowa==true && x0==5&& koszary_osada[xm].lvl==1 && rada_osady[xm].lvl>=2 && drewno>=koszary_osada[xm].koszt_drewno && kamien>=koszary_osada[xm].koszt_kamien && zywnosc>=koszary_osada[xm].koszt_zywnosc && zloto>=koszary_osada[xm].koszt_zloto && miasto[xm].produkcja>=koszary_osada[xm].koszt_produkcja){
			koszary_osada[xm].lvl++;
			rozbuduj_osada(koszary_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(koszary_osada[xm]);
			zwieksz_przychod_osada(koszary_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			pikinier[xm].koszt_produkcja=pikinier[xm].koszt_produkcja-25;
			
    	}
    	if(ster=='q' && rozbudowa==true && x0==5&& koszary_osada[xm].lvl==2 && rada_osady[xm].lvl>=4 && drewno>=koszary_osada[xm].koszt_drewno && kamien>=koszary_osada[xm].koszt_kamien && zywnosc>=koszary_osada[xm].koszt_zywnosc && zloto>=koszary_osada[xm].koszt_zloto && miasto[xm].produkcja>=koszary_osada[xm].koszt_produkcja){
			koszary_osada[xm].lvl++;
			rozbuduj_osada(koszary_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(koszary_osada[xm]);
			zwieksz_przychod_osada(koszary_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			pikinier[xm].koszt_produkcja=pikinier[xm].koszt_produkcja-25;
			
    	}
			//////////////////

		if(ster=='q' && x0==6&& menu_budowy==true&& biblioteka_osada[xm].lvl==0 && rada_osady[xm].lvl>=2 && drewno>=biblioteka_osada[xm].koszt_drewno && kamien>=biblioteka_osada[xm].koszt_kamien && zywnosc>=biblioteka_osada[xm].koszt_zywnosc && zloto>=biblioteka_osada[xm].koszt_zloto && miasto[xm].produkcja>=biblioteka_osada[xm].koszt_produkcja){
			biblioteka_osada[xm].lvl++;
			zbuduj_osada(biblioteka_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(biblioteka_osada[xm]);
			zwieksz_przychod_osada(biblioteka_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			
    	}
		if(ster=='q' && x0==6&& rozbudowa==true&& biblioteka_osada[xm].lvl==1 && rada_osady[xm].lvl>=4 && drewno>=biblioteka_osada[xm].koszt_drewno && kamien>=biblioteka_osada[xm].koszt_kamien && zywnosc>=biblioteka_osada[xm].koszt_zywnosc && zloto>=biblioteka_osada[xm].koszt_zloto && miasto[xm].produkcja>=biblioteka_osada[xm].koszt_produkcja){
			biblioteka_osada[xm].lvl++;
			rozbuduj_osada(biblioteka_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(biblioteka_osada[xm]);
			zwieksz_przychod_osada(biblioteka_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			
    	}	
			//////////////////
	
		if(ster=='q' && menu_budowy==true&& x0==7&& park_osada[xm].lvl==0 && rada_osady[xm].lvl>=1 && drewno>=park_osada[xm].koszt_drewno && kamien>=park_osada[xm].koszt_kamien && zywnosc>=park_osada[xm].koszt_zywnosc && zloto>=park_osada[xm].koszt_zloto && miasto[xm].produkcja>=park_osada[xm].koszt_produkcja){
			park_osada[xm].lvl++;
			zbuduj_osada(park_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(park_osada[xm]);
			zwieksz_przychod_osada(park_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==7&& park_osada[xm].lvl==1 && rada_osady[xm].lvl>=3 && drewno>=park_osada[xm].koszt_drewno && kamien>=park_osada[xm].koszt_kamien && zywnosc>=park_osada[xm].koszt_zywnosc && zloto>=park_osada[xm].koszt_zloto && miasto[xm].produkcja>=park_osada[xm].koszt_produkcja){
			park_osada[xm].lvl++;
			rozbuduj_osada(park_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0, xm);
			zwieksz_koszt_osada(park_osada[xm]);
			zwieksz_przychod_osada(park_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			
    	}	//////////////////
	
		if(ster=='q' && menu_budowy==true&& x0==8&& pomnik_osada[xm].lvl==0 && rada_osady[xm].lvl>=1 && drewno>=pomnik_osada[xm].koszt_drewno && kamien>=pomnik_osada[xm].koszt_kamien && zywnosc>=pomnik_osada[xm].koszt_zywnosc && zloto>=pomnik_osada[xm].koszt_zloto && miasto[xm].produkcja>=pomnik_osada[xm].koszt_produkcja){
			pomnik_osada[xm].lvl++;
			zbuduj_osada(pomnik_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(pomnik_osada[xm]);
			zwieksz_przychod_osada(pomnik_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==8&& pomnik_osada[xm].lvl==1 && rada_osady[xm].lvl>=2 && drewno>=pomnik_osada[xm].koszt_drewno && kamien>=pomnik_osada[xm].koszt_kamien && zywnosc>=pomnik_osada[xm].koszt_zywnosc && zloto>=pomnik_osada[xm].koszt_zloto && miasto[xm].produkcja>=pomnik_osada[xm].koszt_produkcja){
			pomnik_osada[xm].lvl++;
			rozbuduj_osada(pomnik_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(pomnik_osada[xm]);
			zwieksz_przychod_osada(pomnik_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}	
				//////////////////
	
		if(ster=='q' && menu_budowy==true&& x0==9&& port_osada[xm].lvl==0&&miasto[xm].woda==true && rada_osady[xm].lvl>=2 && drewno>=port_osada[xm].koszt_drewno && kamien>=port_osada[xm].koszt_kamien && zywnosc>=port_osada[xm].koszt_zywnosc && zloto>=port_osada[xm].koszt_zloto && miasto[xm].produkcja>=port_osada[xm].koszt_produkcja){
			port_osada[xm].lvl++;
			zbuduj_osada(port_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(port_osada[xm]);
			zwieksz_przychod_osada(port_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==9&& port_osada[xm].lvl==1 && rada_osady[xm].lvl>=3 && drewno>=port_osada[xm].koszt_drewno && kamien>=port_osada[xm].koszt_kamien && zywnosc>=port_osada[xm].koszt_zywnosc && zloto>=port_osada[xm].koszt_zloto && miasto[xm].produkcja>=port_osada[xm].koszt_produkcja){
			port_osada[xm].lvl++;
			rozbuduj_osada(port_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(port_osada[xm]);
			zwieksz_przychod_osada(port_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
			//////////////////

		if(ster=='q' && menu_budowy==true&& x0==10&& tawerna_osada[xm].lvl==0 && rada_osady[xm].lvl>=1 && drewno>=tawerna_osada[xm].koszt_drewno && kamien>=tawerna_osada[xm].koszt_kamien && zywnosc>=tawerna_osada[xm].koszt_zywnosc && zloto>=tawerna_osada[xm].koszt_zloto && miasto[xm].produkcja>=tawerna_osada[xm].koszt_produkcja){
			tawerna_osada[xm].lvl++;
			zbuduj_osada(tawerna_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(tawerna_osada[xm]);
			zwieksz_przychod_osada(tawerna_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==10&& tawerna_osada[xm].lvl==1 && rada_osady[xm].lvl>=3 && drewno>=tawerna_osada[xm].koszt_drewno && kamien>=tawerna_osada[xm].koszt_kamien && zywnosc>=tawerna_osada[xm].koszt_zywnosc && zloto>=tawerna_osada[xm].koszt_zloto && miasto[xm].produkcja>=tawerna_osada[xm].koszt_produkcja){
			tawerna_osada[xm].lvl++;
			rozbuduj_osada(tawerna_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(tawerna_osada[xm]);
			zwieksz_przychod_osada(tawerna_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			
    	}	//////////////////
		
		if(ster=='q' && menu_budowy==true&& x0==11&& magazyn_osada[xm].lvl==0 && rada_osady[xm].lvl>=1 && drewno>=magazyn_osada[xm].koszt_drewno && kamien>=magazyn_osada[xm].koszt_kamien && zywnosc>=magazyn_osada[xm].koszt_zywnosc && zloto>=magazyn_osada[xm].koszt_zloto && miasto[xm].produkcja>=magazyn_osada[xm].koszt_produkcja){
			magazyn_osada[xm].lvl++;
			zbuduj_osada(magazyn_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(magazyn_osada[xm]);
			zwieksz_przychod_osada(magazyn_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==11&& magazyn_osada[xm].lvl==1 && rada_osady[xm].lvl>=3 && drewno>=magazyn_osada[xm].koszt_drewno && kamien>=magazyn_osada[xm].koszt_kamien && zywnosc>=magazyn_osada[xm].koszt_zywnosc && zloto>=magazyn_osada[xm].koszt_zloto && miasto[xm].produkcja>=magazyn_osada[xm].koszt_produkcja){
			magazyn_osada[xm].lvl++;
			rozbuduj_osada(magazyn_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(magazyn_osada[xm]);
			zwieksz_przychod_osada(magazyn_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}	
    	if(ster=='q' && rozbudowa==true&& x0==11&& magazyn_osada[xm].lvl==2 && rada_osady[xm].lvl>=4 && drewno>=magazyn_osada[xm].koszt_drewno && kamien>=magazyn_osada[xm].koszt_kamien && zywnosc>=magazyn_osada[xm].koszt_zywnosc && zloto>=magazyn_osada[xm].koszt_zloto && miasto[xm].produkcja>=magazyn_osada[xm].koszt_produkcja){
			magazyn_osada[xm].lvl++;
			rozbuduj_osada(magazyn_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(magazyn_osada[xm]);
			zwieksz_przychod_osada(magazyn_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}	
			//////////////////
	
		if(ster=='q' && menu_budowy==true&& x0==12&& mlyn_osada[xm].lvl==0 && rada_osady[xm].lvl>=2 && drewno>=mlyn_osada[xm].koszt_drewno && kamien>=mlyn_osada[xm].koszt_kamien && zywnosc>=mlyn_osada[xm].koszt_zywnosc && zloto>=mlyn_osada[xm].koszt_zloto && miasto[xm].produkcja>=mlyn_osada[xm].koszt_produkcja){
			mlyn_osada[xm].lvl++;
			zbuduj_osada(mlyn_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(mlyn_osada[xm]);
			zwieksz_przychod_osada(mlyn_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
    	if(ster=='q' && rozbudowa==true&& x0==12&& mlyn_osada[xm].lvl==1 && rada_osady[xm].lvl>=3 && drewno>=mlyn_osada[xm].koszt_drewno && kamien>=mlyn_osada[xm].koszt_kamien && zywnosc>=mlyn_osada[xm].koszt_zywnosc && zloto>=mlyn_osada[xm].koszt_zloto && miasto[xm].produkcja>=mlyn_osada[xm].koszt_produkcja){
			mlyn_osada[xm].lvl++;
			rozbuduj_osada(mlyn_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(mlyn_osada[xm]);
			zwieksz_przychod_osada(mlyn_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
    	}
    	if(ster=='q' && rozbudowa==true&& x0==12&& mlyn_osada[xm].lvl==2 && rada_osady[xm].lvl>=4 && drewno>=mlyn_osada[xm].koszt_drewno && kamien>=mlyn_osada[xm].koszt_kamien && zywnosc>=mlyn_osada[xm].koszt_zywnosc && zloto>=mlyn_osada[xm].koszt_zloto && miasto[xm].produkcja>=mlyn_osada[xm].koszt_produkcja){
			mlyn_osada[xm].lvl++;
			rozbuduj_osada(mlyn_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(mlyn_osada[xm]);
			zwieksz_przychod_osada(mlyn_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
    	}

	//////////////////
				
		if(ster=='q' && menu_budowy==true&& x0==13&& kamieniarz_osada[xm].lvl==0 && rada_osady[xm].lvl>=1 && drewno>=kamieniarz_osada[xm].koszt_drewno && kamien>=kamieniarz_osada[xm].koszt_kamien && zywnosc>=kamieniarz_osada[xm].koszt_zywnosc && zloto>=kamieniarz_osada[xm].koszt_zloto && miasto[xm].produkcja>=kamieniarz_osada[xm].koszt_produkcja){
			kamieniarz_osada[xm].lvl++;
			zbuduj_osada(kamieniarz_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(kamieniarz_osada[xm]);
			zwieksz_przychod_osada(kamieniarz_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
    	if(ster=='q' && rozbudowa==true&& x0==13&& kamieniarz_osada[xm].lvl==1 && rada_osady[xm].lvl>=3 && drewno>=kamieniarz_osada[xm].koszt_drewno && kamien>=kamieniarz_osada[xm].koszt_kamien && zywnosc>=kamieniarz_osada[xm].koszt_zywnosc && zloto>=kamieniarz_osada[xm].koszt_zloto && miasto[xm].produkcja>=kamieniarz_osada[xm].koszt_produkcja){
			kamieniarz_osada[xm].lvl++;
			rozbuduj_osada(kamieniarz_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(kamieniarz_osada[xm]);
			zwieksz_przychod_osada(kamieniarz_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
    	if(ster=='q' && rozbudowa==true&& x0==13&& kamieniarz_osada[xm].lvl==2 && rada_osady[xm].lvl>=4 && drewno>=kamieniarz_osada[xm].koszt_drewno && kamien>=kamieniarz_osada[xm].koszt_kamien && zywnosc>=kamieniarz_osada[xm].koszt_zywnosc && zloto>=kamieniarz_osada[xm].koszt_zloto && miasto[xm].produkcja>=kamieniarz_osada[xm].koszt_produkcja){
			kamieniarz_osada[xm].lvl++;
			rozbuduj_osada(kamieniarz_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(kamieniarz_osada[xm]);
			zwieksz_przychod_osada(kamieniarz_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}

	//////////////////
			
		if(ster=='q' && menu_budowy==true&& x0==14&& kosciol_osada[xm].lvl==0 && rada_osady[xm].lvl>=1 && drewno>=kosciol_osada[xm].koszt_drewno && kamien>=kosciol_osada[xm].koszt_kamien && zywnosc>=kosciol_osada[xm].koszt_zywnosc && zloto>=kosciol_osada[xm].koszt_zloto && miasto[xm].produkcja>=kosciol_osada[xm].koszt_produkcja){
			kosciol_osada[xm].lvl++;
			zbuduj_osada(kosciol_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(kosciol_osada[xm]);
			zwieksz_przychod_osada(kosciol_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
		if(ster=='q' && rozbudowa==true&& x0==14&& kosciol_osada[xm].lvl==1 && rada_osady[xm].lvl>=3 && drewno>=kosciol_osada[xm].koszt_drewno && kamien>=kosciol_osada[xm].koszt_kamien && zywnosc>=kosciol_osada[xm].koszt_zywnosc && zloto>=kosciol_osada[xm].koszt_zloto && miasto[xm].produkcja>=kosciol_osada[xm].koszt_produkcja){
			kosciol_osada[xm].lvl++;
			rozbuduj_osada(kosciol_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(kosciol_osada[xm]);
			zwieksz_przychod_osada(kosciol_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}	
			//////////////////
			

		if(ster=='q' && menu_budowy==true&& x0==15&& weglarz_osada[xm].lvl==0 && rada_osady[xm].lvl>=1 && drewno>=weglarz_osada[xm].koszt_drewno && kamien>=weglarz_osada[xm].koszt_kamien && zywnosc>=weglarz_osada[xm].koszt_zywnosc && zloto>=weglarz_osada[xm].koszt_zloto && miasto[xm].produkcja>=weglarz_osada[xm].koszt_produkcja){
			weglarz_osada[xm].lvl++;
			zbuduj_osada(weglarz_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(weglarz_osada[xm]);
			zwieksz_przychod_osada(weglarz_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
    	if(ster=='q' && rozbudowa==true&& x0==15&& weglarz_osada[xm].lvl==1 && rada_osady[xm].lvl>=3 && drewno>=weglarz_osada[xm].koszt_drewno && kamien>=weglarz_osada[xm].koszt_kamien && zywnosc>=weglarz_osada[xm].koszt_zywnosc && zloto>=weglarz_osada[xm].koszt_zloto && miasto[xm].produkcja>=weglarz_osada[xm].koszt_produkcja){
			weglarz_osada[xm].lvl++;
			rozbuduj_osada(weglarz_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(weglarz_osada[xm]);
			zwieksz_przychod_osada(weglarz_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			
    	}
				//////////////////

		if(ster=='q' && menu_budowy==true && x0==16&& warsztat_osada[xm].lvl==0 &&rada_osady[xm].lvl>=2 && drewno>=warsztat_osada[xm].koszt_drewno && kamien>=warsztat_osada[xm].koszt_kamien && zywnosc>=warsztat_osada[xm].koszt_zywnosc && zloto>=warsztat_osada[xm].koszt_zloto && miasto[xm].produkcja>=warsztat_osada[xm].koszt_produkcja){
			warsztat_osada[xm].lvl++;
			zbuduj_osada(warsztat_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(warsztat_osada[xm]);
			zwieksz_przychod_osada(warsztat_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			kusznik[xm].koszt_produkcja-=50;
    	}
    	if(ster=='q' && rozbudowa==true && x0==16&& warsztat_osada[xm].lvl==1 && mechanika==true &&rada_osady[xm].lvl>=4 && drewno>=warsztat_osada[xm].koszt_drewno && kamien>=warsztat_osada[xm].koszt_kamien && zywnosc>=warsztat_osada[xm].koszt_zywnosc && zloto>=warsztat_osada[xm].koszt_zloto && miasto[xm].produkcja>=warsztat_osada[xm].koszt_produkcja){
			warsztat_osada[xm].lvl++;
			rozbuduj_osada(warsztat_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(warsztat_osada[xm]);
			zwieksz_przychod_osada(warsztat_osada[xm],&przychod_nauka,&max_zolnierzy, xm);
			kusznik[xm].koszt_produkcja-=50;
    	}
				//////////////////

		if(ster=='q' && menu_budowy==true&& x0==17&& stajnia_osada[xm].lvl==0 && rada_osady[xm].lvl>=2 && drewno>=stajnia_osada[xm].koszt_drewno && kamien>=stajnia_osada[xm].koszt_kamien && zywnosc>=stajnia_osada[xm].koszt_zywnosc && zloto>=stajnia_osada[xm].koszt_zloto && miasto[xm].produkcja>=stajnia_osada[xm].koszt_produkcja){
			stajnia_osada[xm].lvl++;
			zbuduj_osada(stajnia_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&menu_budowy,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(stajnia_osada[xm]);
			zwieksz_przychod_osada(stajnia_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			lekka_jazda[xm].koszt_produkcja-=50;

    	}
    	if(ster=='q' && rozbudowa==true&& x0==17&& stajnia_osada[xm].lvl==1 && rada_osady[xm].lvl>=3 && drewno>=stajnia_osada[xm].koszt_drewno && kamien>=stajnia_osada[xm].koszt_kamien && zywnosc>=stajnia_osada[xm].koszt_zywnosc && zloto>=stajnia_osada[xm].koszt_zloto && miasto[xm].produkcja>=stajnia_osada[xm].koszt_produkcja){
			stajnia_osada[xm].lvl++;
			rozbuduj_osada(stajnia_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(stajnia_osada[xm]);
			zwieksz_przychod_osada(stajnia_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			lekka_jazda[xm].koszt_produkcja-=50;
    	}
    	if(ster=='q' && rozbudowa==true&& x0==17&& stajnia_osada[xm].lvl==2 && rada_osady[xm].lvl>=4 && drewno>=stajnia_osada[xm].koszt_drewno && kamien>=stajnia_osada[xm].koszt_kamien && zywnosc>=stajnia_osada[xm].koszt_zywnosc && zloto>=stajnia_osada[xm].koszt_zloto && miasto[xm].produkcja>=stajnia_osada[xm].koszt_produkcja){
			stajnia_osada[xm].lvl++;
			rozbuduj_osada(stajnia_osada[xm],&drewno,&kamien,&zywnosc,&zloto,&max_zolnierzy,&rozbudowa,&menu_osada,&przychod_nauka,&x0,xm);
			zwieksz_koszt_osada(stajnia_osada[xm]);
			zwieksz_przychod_osada(stajnia_osada[xm],&przychod_nauka,&max_zolnierzy,xm);
			lekka_jazda[xm].koszt_produkcja-=50;

    	}
    	

		if(ster==KEY_UP && x0==0 && menu_budowy==true || ster==KEY_UP && x0==0 && rozbudowa==true)
		x0=18;
		
		if(ster==KEY_DOWN && x0==18 && menu_budowy==true || ster==KEY_DOWN && x0==18 && rozbudowa==true)
		x0=0;
	
}
}

////////////////////////////////////////////////////////
while(ruch_barbarzyncow==true){
 system("CLS");
 gotoxy(50,50);

 cout << "Trwa ruch barbarzyncow, prosze czekac";
 
	 if(ilosc_barbarzyncow<20){
	 	for(int i=ilosc_barbarzyncow;i<=20;i++){
	 		barbarzynca_x=(rand()%136);
	 		barbarzynca_y=(rand()%200);
	 		if(mapa[barbarzynca_x][barbarzynca_y]!=woda && mapa[barbarzynca_x][barbarzynca_y]!=gora &&mapa[barbarzynca_x][barbarzynca_y]!='@' && mapa[barbarzynca_x][barbarzynca_y]!=' '){
	 			for(int p=barbarzynca_x-5;p<=barbarzynca_x+5;p++){
	 				for(int o=barbarzynca_y-5;o<=barbarzynca_y+5;o++){
	 					if(mapa[p][o]==osada || mapa[p][o]==stolica ||mapa[p][o]==tartak ||mapa[p][o]==kopalnia ||mapa[p][o]==farma ||mapa[p][o]==wioska || mapa_jednostek[p][o]=='A'|| mapa_jednostek[p][o]=='R'|| mapa_jednostek[p][o]=='O'){
	 						barbarzynca_blad=true;
						 }
					 }
				 }
				 if(barbarzynca_blad==true){
				 	barbarzynca_blad=false;
				 	i--;
				 	continue;
				 }
				 mapa_jednostek[barbarzynca_x][barbarzynca_y]='B';
				 ilosc_barbarzyncow++;
			 }
		 }
	 }
	 
	 for(int i=0;i<137;i++){
	 	for(int j=0;j<201;j++){
	 			
	 			barbarzynca_blad=false;
				barbarzynca_atak=false;
	   			min_x=5;
	 			min_y=5;
	 			koniec_ruchu=false;

	 		if(mapa_jednostek[i][j]=='B'){
	 			for(int p=i-5;p<=i+5;p++){
	 				for(int o=j-5;o<=j+5;o++){
	 					if(mapa_jednostek[p][o]=='A')barbarzynca_blad=true;
	 					
					 }
				 }
				 

				 if(barbarzynca_blad==false){
				 for(int p=i-5;p<=i+5;p++){
	 				for(int o=j-5;o<=j+5;o++){
	 					if(mapa_jednostek[p][o]=='O' || mapa_jednostek[p][o]=='R' || mapa[p][o]==kopalnia|| mapa[p][o]==farma|| mapa[p][o]==tartak || mapa[p][o]==wioska){
						
					
				
					 	if(abs(i-p)<min_x){

						min_x=abs(i-p);
	 					min_y=abs(j-o);
	 					}
	 					if(abs(j-o)<min_y){
						min_x=abs(i-p);
	 					min_y=abs(j-o);
	 					}

	 					barbarzynca_atak=true;
	 					}
					 }
				
				 }
				}

				 if(barbarzynca_atak==false && koniec_ruchu==false && barbarzynca_blad==true){
				 	
				 		
						 
	 			szansa_ruch=(rand()%8);
	 			if(szansa_ruch==0)continue;
	 			if(szansa_ruch==1 && mapa[i-1][j-1]!=woda &&mapa[i-1][j-1]!=gora){
	 				bufor_barbarzyncow[i-1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				if(szansa_ruch==2&& mapa[i-1][j]!=woda &&mapa[i-1][j]!=gora){
	 				bufor_barbarzyncow[i-1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==3&& mapa[i-1][j+1]!=woda &&mapa[i-1][j+1]!=gora){
	 				bufor_barbarzyncow[i-1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==4&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==5&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==6&& mapa[i+1][j-1]!=woda &&mapa[i+1][j-1]!=gora){
	 				bufor_barbarzyncow[i+1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==7&& mapa[i+1][j]!=woda &&mapa[i+1][j]!=gora){
	 				bufor_barbarzyncow[i+1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==8&& mapa[i+1][j+1]!=woda &&mapa[i+1][j+1]!=gora){
	 				bufor_barbarzyncow[i+1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 barbarzynca_atak=false;
				
	 			}
	 			if(barbarzynca_atak==true){
	 				for(int p=i-min_x;p<=i+min_x;p++){
	 				for(int o=j-min_y;o<=j+min_y;o++){
	 					if(mapa_jednostek[p][o]=='O' || mapa_jednostek[p][o]=='R' || mapa[p][o]==kopalnia|| mapa[p][o]==farma|| mapa[p][o]==tartak || mapa[p][o]==wioska){
						if(i-p==1 && j-o==1&&koniec_ruchu==false){
						bufor_barbarzyncow[i-1][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					mapa_jednostek[i-1][j-1]=' ';
	 					mapa[i-1][j-1]=dom2;
	 					mapa_tartak[i-1][j-1]=0;
	 					mapa_farma[i-1][j-1]=0;
	 					mapa_wioska[i-1][j-1]=0;
	 					mapa_kopalnia[i-1][j-1]=0;
	 					koniec_ruchu=true;
	 				
						}
						if(i-p==1 && j-o==0&&koniec_ruchu==false){
						bufor_barbarzyncow[i-1][j]=1;
	 					mapa_jednostek[i][j]=' ';
	 					mapa_jednostek[i-1][j]=' ';
	 					mapa[i-1][j]=dom2;
	 					mapa_tartak[i-1][j]=0;
	 					mapa_farma[i-1][j]=0;
	 					mapa_wioska[i-1][j]=0;
	 					mapa_kopalnia[i-1][j]=0;
	 					koniec_ruchu=true;
	 					
						}
						if(i-p==1 && j-o==-1&&koniec_ruchu==false){
						bufor_barbarzyncow[i-1][j+1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					mapa_jednostek[i-1][j+1]=' ';
	 					mapa[i-1][j+1]=dom2;
	 					mapa_tartak[i-1][j+1]=0;
	 					mapa_farma[i-1][j+1]=0;
	 					mapa_wioska[i-1][j+1]=0;
	 					mapa_kopalnia[i-1][j+1]=0;
	 					koniec_ruchu=true;
	 				
						}
						if(i-p==0 && j-o==1&&koniec_ruchu==false){
						bufor_barbarzyncow[i][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					mapa_jednostek[i][j-1]=' ';
	 					mapa[i][j-1]=dom2;
	 					mapa_tartak[i][j-1]=0;
	 					mapa_farma[i][j-1]=0;
	 					mapa_wioska[i][j-1]=0;
	 					mapa_kopalnia[i][j-1]=0;
	 					koniec_ruchu=true;
	 					
						}
						if(i-p==0 && j-o==-1&&koniec_ruchu==false){
						bufor_barbarzyncow[i][j+1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					mapa_jednostek[i][j+1]=' ';
	 					mapa[i][j+1]=dom2;
	 					mapa_tartak[i][j+1]=0;
	 					mapa_farma[i][j+1]=0;
	 					mapa_wioska[i][j+1]=0;
	 					mapa_kopalnia[i][j+1]=0;
	 					koniec_ruchu=true;
	 				
						}
						if(i-p==-1 && j-o==1&&koniec_ruchu==false){
						bufor_barbarzyncow[i+1][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					mapa_jednostek[i+1][j-1]=' ';
	 					mapa[i+1][j-1]=dom2;
	 					mapa_tartak[i+1][j-1]=0;
	 					mapa_farma[i+1][j-1]=0;
	 					mapa_wioska[i+1][j-1]=0;
	 					mapa_kopalnia[i+1][j-1]=0;
	 					koniec_ruchu=true;
	 					
						}
						if(i-p==-1 && j-o==0&&koniec_ruchu==false){
						bufor_barbarzyncow[i+1][j]=1;
	 					mapa_jednostek[i][j]=' ';
	 					mapa_jednostek[i+1][j]=' ';
	 					mapa[i+1][j]=dom2;
	 					mapa_tartak[i+1][j]=0;
	 					mapa_farma[i+1][j]=0;
	 					mapa_wioska[i+1][j]=0;
	 					mapa_kopalnia[i+1][j]=0;
	 					koniec_ruchu=true;
	 				
						}
						if(i-p==-1 && j-o==-1 &&koniec_ruchu==false){
						bufor_barbarzyncow[i+1][j+1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					mapa_jednostek[i+1][j+1]=' ';
	 					mapa[i+1][j+1]=dom2;
	 					mapa_tartak[i+1][j+1]=0;
	 					mapa_farma[i+1][j+1]=0;
	 					mapa_wioska[i+1][j+1]=0;
	 					mapa_kopalnia[i+1][j+1]=0;
	 					koniec_ruchu=true;
	 				
						}
						if(p<i && o<j && mapa[i-1][j-1]!=gora&&koniec_ruchu==false&& mapa[i-1][j-1]!=woda){
						bufor_barbarzyncow[i-1][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 				
						}
						if(p<i && o<j && mapa[i-1][j-1]==gora&&koniec_ruchu==false&& mapa[i-1][j-1]==woda && mapa[i-1][j]!=gora&& mapa[i-1][j]!=woda){
						bufor_barbarzyncow[i-1][j]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 				
						}
						if(p<i && o<j && koniec_ruchu==false){
				 	
				 		
						 
	 			szansa_ruch=(rand()%8);
	 			if(szansa_ruch==0)continue;
	 			if(szansa_ruch==1 && mapa[i-1][j-1]!=woda &&mapa[i-1][j-1]!=gora){
	 				bufor_barbarzyncow[i-1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				if(szansa_ruch==2&& mapa[i-1][j]!=woda &&mapa[i-1][j]!=gora){
	 				bufor_barbarzyncow[i-1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==3&& mapa[i-1][j+1]!=woda &&mapa[i-1][j+1]!=gora){
	 				bufor_barbarzyncow[i-1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==4&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==5&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==6&& mapa[i+1][j-1]!=woda &&mapa[i+1][j-1]!=gora){
	 				bufor_barbarzyncow[i+1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==7&& mapa[i+1][j]!=woda &&mapa[i+1][j]!=gora){
	 				bufor_barbarzyncow[i+1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==8&& mapa[i+1][j+1]!=woda &&mapa[i+1][j+1]!=gora){
	 				bufor_barbarzyncow[i+1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 barbarzynca_atak=false;
				
	 			}
						/////////////////////////
						if(p<i && o==j && mapa[i-1][j]!=gora&&koniec_ruchu==false&& mapa[i-1][j]!=woda){
						bufor_barbarzyncow[i-1][j]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 				
						}
						if(p<i && o==j && mapa[i-1][j]==gora&&koniec_ruchu==false&& mapa[i-1][j]==woda && mapa[i-1][j-1]!=gora&& mapa[i-1][j-1]!=woda){
						bufor_barbarzyncow[i-1][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p<i && o==j && mapa[i-1][j]==gora&&koniec_ruchu==false&& mapa[i-1][j]==woda && mapa[i-1][j-1]==gora&& mapa[i-1][j-1]==woda&& mapa[i-1][j+1]!=gora&& mapa[i-1][j+1]!=woda){
						bufor_barbarzyncow[i-1][j+1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 				
						}
						if(p<i && o==j && koniec_ruchu==false){
				 	
				 		
						 
	 			szansa_ruch=(rand()%8);
	 			if(szansa_ruch==0)continue;
	 			if(szansa_ruch==1 && mapa[i-1][j-1]!=woda &&mapa[i-1][j-1]!=gora){
	 				bufor_barbarzyncow[i-1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				if(szansa_ruch==2&& mapa[i-1][j]!=woda &&mapa[i-1][j]!=gora){
	 				bufor_barbarzyncow[i-1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==3&& mapa[i-1][j+1]!=woda &&mapa[i-1][j+1]!=gora){
	 				bufor_barbarzyncow[i-1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==4&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==5&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==6&& mapa[i+1][j-1]!=woda &&mapa[i+1][j-1]!=gora){
	 				bufor_barbarzyncow[i+1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==7&& mapa[i+1][j]!=woda &&mapa[i+1][j]!=gora){
	 				bufor_barbarzyncow[i+1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==8&& mapa[i+1][j+1]!=woda &&mapa[i+1][j+1]!=gora){
	 				bufor_barbarzyncow[i+1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 barbarzynca_atak=false;
				
	 			}
						//////////////
						if(p<i && o>j && mapa[i-1][j+1]!=gora&&koniec_ruchu==false&& mapa[i-1][j+1]!=woda){
						bufor_barbarzyncow[i-1][j+1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p<i && o>j && mapa[i-1][j+1]==gora&&koniec_ruchu==false&& mapa[i-1][j+1]==woda && mapa[i-1][j]!=gora&& mapa[i-1][j]!=woda){
						bufor_barbarzyncow[i-1][j]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p<i && o>j && koniec_ruchu==false){
				 	
				 		
						 
	 			szansa_ruch=(rand()%8);
	 			if(szansa_ruch==0)continue;
	 			if(szansa_ruch==1 && mapa[i-1][j-1]!=woda &&mapa[i-1][j-1]!=gora){
	 				bufor_barbarzyncow[i-1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				if(szansa_ruch==2&& mapa[i-1][j]!=woda &&mapa[i-1][j]!=gora){
	 				bufor_barbarzyncow[i-1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==3&& mapa[i-1][j+1]!=woda &&mapa[i-1][j+1]!=gora){
	 				bufor_barbarzyncow[i-1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==4&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==5&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==6&& mapa[i+1][j-1]!=woda &&mapa[i+1][j-1]!=gora){
	 				bufor_barbarzyncow[i+1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==7&& mapa[i+1][j]!=woda &&mapa[i+1][j]!=gora){
	 				bufor_barbarzyncow[i+1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==8&& mapa[i+1][j+1]!=woda &&mapa[i+1][j+1]!=gora){
	 				bufor_barbarzyncow[i+1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 barbarzynca_atak=false;
				
	 			}
						///////////////////
						if(p==i && o<j && mapa[i][j-1]!=gora&&koniec_ruchu==false&& mapa[i][j-1]!=woda){
						bufor_barbarzyncow[i][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p==i && o<j && mapa[i][j-1]==gora&&koniec_ruchu==false&& mapa[i][j-1]==woda && mapa[i-1][j-1]!=gora&& mapa[i-1][j-1]!=woda){
						bufor_barbarzyncow[i-1][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p==i && o<j && mapa[i][j-1]==gora&&koniec_ruchu==false&& mapa[i][j-1]==woda && mapa[i-1][j-1]==gora&& mapa[i-1][j-1]==woda&& mapa[i-1][j-1]!=gora&& mapa[i-1][j-1]!=woda){
						bufor_barbarzyncow[i+1][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p==i && o<j && koniec_ruchu==false){
				 	
				 		
						 
	 			szansa_ruch=(rand()%8);
	 			if(szansa_ruch==0)continue;
	 			if(szansa_ruch==1 && mapa[i-1][j-1]!=woda &&mapa[i-1][j-1]!=gora){
	 				bufor_barbarzyncow[i-1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				if(szansa_ruch==2&& mapa[i-1][j]!=woda &&mapa[i-1][j]!=gora){
	 				bufor_barbarzyncow[i-1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==3&& mapa[i-1][j+1]!=woda &&mapa[i-1][j+1]!=gora){
	 				bufor_barbarzyncow[i-1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==4&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==5&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==6&& mapa[i+1][j-1]!=woda &&mapa[i+1][j-1]!=gora){
	 				bufor_barbarzyncow[i+1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==7&& mapa[i+1][j]!=woda &&mapa[i+1][j]!=gora){
	 				bufor_barbarzyncow[i+1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==8&& mapa[i+1][j+1]!=woda &&mapa[i+1][j+1]!=gora){
	 				bufor_barbarzyncow[i+1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 barbarzynca_atak=false;
				
	 			}
						//////////////
						if(p>i && o<j && mapa[i+1][j-1]!=gora&& mapa[i+1][j-1]!=woda){
						bufor_barbarzyncow[i+1][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;	
	 					
						}
						if(p>i && o<j && mapa[i+1][j-1]==gora&& mapa[i+1][j-1]==woda && mapa[i+1][j]!=gora&& mapa[i+1][j]!=woda){
						bufor_barbarzyncow[i+1][j]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p>i && o<j && koniec_ruchu==false){
				 	
				 		
						 
	 			szansa_ruch=(rand()%8);
	 			if(szansa_ruch==0)continue;
	 			if(szansa_ruch==1 && mapa[i-1][j-1]!=woda &&mapa[i-1][j-1]!=gora){
	 				bufor_barbarzyncow[i-1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				if(szansa_ruch==2&& mapa[i-1][j]!=woda &&mapa[i-1][j]!=gora){
	 				bufor_barbarzyncow[i-1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==3&& mapa[i-1][j+1]!=woda &&mapa[i-1][j+1]!=gora){
	 				bufor_barbarzyncow[i-1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==4&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==5&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==6&& mapa[i+1][j-1]!=woda &&mapa[i+1][j-1]!=gora){
	 				bufor_barbarzyncow[i+1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==7&& mapa[i+1][j]!=woda &&mapa[i+1][j]!=gora){
	 				bufor_barbarzyncow[i+1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==8&& mapa[i+1][j+1]!=woda &&mapa[i+1][j+1]!=gora){
	 				bufor_barbarzyncow[i+1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 barbarzynca_atak=false;
				
	 			}
						///////////////////
						if(p>i && o==j && mapa[i+1][j]!=gora&&koniec_ruchu==false&& mapa[i+1][j]!=woda){
						bufor_barbarzyncow[i+1][j]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p>i && o==j && mapa[i+1][j]==gora&&koniec_ruchu==false&& mapa[i+1][j]==woda && mapa[i+1][j-1]!=gora&& mapa[i+1][j-1]!=woda){
						bufor_barbarzyncow[i+1][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p>i && o==j && mapa[i+1][j]==gora&&koniec_ruchu==false&& mapa[i+1][j]==woda && mapa[i+1][j-1]==gora&& mapa[i+1][j-1]==woda&& mapa[i+1][j+1]!=gora&& mapa[i+1][j+1]!=woda){
						bufor_barbarzyncow[i+1][j+1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p>i && o==j && koniec_ruchu==false){
				 	
				 		
						 
	 			szansa_ruch=(rand()%8);
	 			if(szansa_ruch==0)continue;
	 			if(szansa_ruch==1 && mapa[i-1][j-1]!=woda &&mapa[i-1][j-1]!=gora){
	 				bufor_barbarzyncow[i-1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				if(szansa_ruch==2&& mapa[i-1][j]!=woda &&mapa[i-1][j]!=gora){
	 				bufor_barbarzyncow[i-1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==3&& mapa[i-1][j+1]!=woda &&mapa[i-1][j+1]!=gora){
	 				bufor_barbarzyncow[i-1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==4&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==5&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==6&& mapa[i+1][j-1]!=woda &&mapa[i+1][j-1]!=gora){
	 				bufor_barbarzyncow[i+1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==7&& mapa[i+1][j]!=woda &&mapa[i+1][j]!=gora){
	 				bufor_barbarzyncow[i+1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==8&& mapa[i+1][j+1]!=woda &&mapa[i+1][j+1]!=gora){
	 				bufor_barbarzyncow[i+1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 barbarzynca_atak=false;
				
	 			}
						//////////////
						if(p>i && o>j && mapa[i+1][j+1]!=gora&&koniec_ruchu==false&& mapa[i+1][j+1]!=woda){
						bufor_barbarzyncow[i+1][j+1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p>i && o>j && mapa[i+1][j+1]==gora&&koniec_ruchu==false&& mapa[i+1][j+1]==woda && mapa[i+1][j]!=gora&& mapa[i+1][j]!=woda){
						bufor_barbarzyncow[i+1][j]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p>i && o>j&& koniec_ruchu==false){
				 	
				 		
						 
	 			szansa_ruch=(rand()%8);
	 			if(szansa_ruch==0)continue;
	 			if(szansa_ruch==1 && mapa[i-1][j-1]!=woda &&mapa[i-1][j-1]!=gora){
	 				bufor_barbarzyncow[i-1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				if(szansa_ruch==2&& mapa[i-1][j]!=woda &&mapa[i-1][j]!=gora){
	 				bufor_barbarzyncow[i-1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==3&& mapa[i-1][j+1]!=woda &&mapa[i-1][j+1]!=gora){
	 				bufor_barbarzyncow[i-1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==4&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==5&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==6&& mapa[i+1][j-1]!=woda &&mapa[i+1][j-1]!=gora){
	 				bufor_barbarzyncow[i+1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==7&& mapa[i+1][j]!=woda &&mapa[i+1][j]!=gora){
	 				bufor_barbarzyncow[i+1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==8&& mapa[i+1][j+1]!=woda &&mapa[i+1][j+1]!=gora){
	 				bufor_barbarzyncow[i+1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 barbarzynca_atak=false;
				
	 			}
						///////////////////
						if(p==i && o>j && mapa[i][j+1]!=gora&& mapa[i][j+1]!=woda){
						bufor_barbarzyncow[i][j-1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p==i && o>j && mapa[i][j+1]==gora&& mapa[i][j+1]==woda && mapa[i-1][j+1]!=gora&& mapa[i-1][j+1]!=woda){
						bufor_barbarzyncow[i-1][j+1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p==i && o>j && mapa[i][j+1]==gora&& mapa[i][j+1]==woda && mapa[i-1][j+1]==gora&& mapa[i-1][j+1]==woda&& mapa[i-1][j+1]!=gora&& mapa[i-1][j+1]!=woda){
						bufor_barbarzyncow[i+1][j+1]=1;
	 					mapa_jednostek[i][j]=' ';
	 					koniec_ruchu=true;
	 					
						}
						if(p==i && o>j && koniec_ruchu==false){
				 	

	 			szansa_ruch=(rand()%8);
	 			if(szansa_ruch==0)continue;
	 			if(szansa_ruch==1 && mapa[i-1][j-1]!=woda &&mapa[i-1][j-1]!=gora){
	 				bufor_barbarzyncow[i-1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				if(szansa_ruch==2&& mapa[i-1][j]!=woda &&mapa[i-1][j]!=gora){
	 				bufor_barbarzyncow[i-1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==3&& mapa[i-1][j+1]!=woda &&mapa[i-1][j+1]!=gora){
	 				bufor_barbarzyncow[i-1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==4&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==5&& mapa[i][j-1]!=woda &&mapa[i][j-1]!=gora){
	 				bufor_barbarzyncow[i][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==6&& mapa[i+1][j-1]!=woda &&mapa[i+1][j-1]!=gora){
	 				bufor_barbarzyncow[i+1][j-1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==7&& mapa[i+1][j]!=woda &&mapa[i+1][j]!=gora){
	 				bufor_barbarzyncow[i+1][j]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 if(szansa_ruch==8&& mapa[i+1][j+1]!=woda &&mapa[i+1][j+1]!=gora){
	 				bufor_barbarzyncow[i+1][j+1]=1;
	 				mapa_jednostek[i][j]=' ';
				 }
				 barbarzynca_atak=false;
				
	 			}
						//////////////
				}
				}
				 }
				 }

				 
			 }
			 
		 }


	 }

	
	 for(int i=0;i<137;i++){
	 	for(int j=0;j<201;j++){
	 		if(bufor_barbarzyncow[i][j]==1){
	 			mapa_jednostek[i][j]='B';
	 			bufor_barbarzyncow[i][j]=0;
			 }
	 	}
	 }

	
	Sleep(3000);
	ruch_barbarzyncow=false;
	gracz1=true;
	system("CLS");
}

}while(e==1);
}
