#ifndef TEXT_H 
#define TEXT_H 
/*
;--------------------------------------
;Motor text
;
;Dev by: Nahu
;Coments lang: Spanish
*/
//librerias
#include <iostream> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include<sys/stat.h>
#include <string>
#include <vector>
//definiciones
#define Default (1)

using std::cout;
//variables 
typedef struct{
	HANDLE handle;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO cci;
	CONSOLE_FONT_INFOEX Font;
	COORD coord;
	
}ConsoleValue;

ConsoleValue *cv;
//funciones internas

int check_so(){//comprobador de version del sistema operativo
	int osver= 0;

	NTSTATUS(WINAPI *RtlGetVersion)(LPOSVERSIONINFOEXW);

	OSVERSIONINFOEXW osInfo;

	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");

	if (NULL != RtlGetVersion){	
		osInfo.dwOSVersionInfoSize = sizeof(osInfo);
		RtlGetVersion(&osInfo);
		osver = osInfo.dwMajorVersion;
	}
	return osver;
}

void clear_screen(){//Limpiador de pantalla, escribiendo caracteres vacios
	DWORD n;                         
	DWORD size;                      
	COORD coord = { 0 };

	size = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n);
	GetConsoleScreenBufferInfo(h, &csbi);
	FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);


	SetConsoleCursorPosition(h, coord);
}

void fullscreen(){//Comprueba si se puede hacer pantalla completa y lo hace
	int so = check_so();
	
	if (so == 10){
		::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);//Pantalla Completa
	}
}

void mov(int x, int y){//Movimiento del cursor de texto
		
			cv->coord.Y=y;cv->coord.X=x;

			SetConsoleCursorPosition(cv->handle, cv->coord);
}
		
void color(int color){//Color Para el texto
	SetConsoleTextAttribute(cv->handle, color);
}
void cursor(bool curs){//Apagar Cursor de texto	 
	GetConsoleCursorInfo(cv->handle, &cv->cci);
	cv->cci.bVisible = curs;
	SetConsoleCursorInfo(cv->handle, &cv->cci);
}
void text_type(int X,int Y){//Tamaño para el texto
		int x,y;
		if(X == Default|| Y == Default){
			x=8;y=16;
		}
		else {
			x = X;y = Y;
		}
		cv->Font.cbSize = sizeof(cv->Font);			
		cv->Font.nFont = 0;						
		cv->Font.dwFontSize.X = x;              
		cv->Font.dwFontSize.Y = y;              
		cv->Font.FontFamily = FF_DONTCARE;		
		cv->Font.FontWeight = FW_NORMAL;
		wcscpy(cv->Font.FaceName, L"Consolas"); // seleccion de fuente
		SetCurrentConsoleFontEx(cv->handle, FALSE, &cv->Font);
}
//funciones compuestas

void text(int PosX,int PosY,int Color,int fontX,int fontY,bool Curs,bool wait,string Word){
			int width = Word.length();//Variable con el largo del string Word

			mov(PosX,PosY);//Mueve el cursor a la posicion xy
			color(Color);//Asigna el color
			text_type(fontX,fontY);//Cambia los tamaños de la fuente xy
			cursor(Curs);//Activa o desactiva la señalacion del cursor
			ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);//Apaga la barra de desplazamiento
			if (wait) {//Comprueba si se quiere esperar entre cada letra
				for (int i = 0; i < width; i++) {//Se espera 5ms entre cada letra
					Sleep(5);//Esperar 5ms
					cout << Word[i];//Escribir la letra
				}
			}
			else {//Caso contrario se escribe todo el string
				cout << Word;
			}
		}
void text(int PosX, int PosY, int Color, int fontX, int fontY, bool Curs, bool wait, char* Word) {
			mov(PosX, PosY);
			color(Color);
			cursor(Curs);
			text_type(fontX, fontY);
			ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
			cout << Word;
			delete Word;
		}
void text(int PosX, int PosY, int Color, int fontX, int fontY, bool Curs, bool wait, char Word) {
			mov(PosX, PosY);
			color(Color);
			cursor(Curs);
			text_type(fontX, fontY);
			ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
			cout << Word;
		}

#endif /* Text.h */
