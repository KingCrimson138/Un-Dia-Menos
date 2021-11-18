#ifndef TEXT_H //texth
#define TEXT_H //texth
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
#include <string>
//definiciones
#define Default (1)
HANDLE handle;
CONSOLE_SCREEN_BUFFER_INFO csbi;
CONSOLE_CURSOR_INFO cci;
CONSOLE_FONT_INFOEX Font;
COORD coord;
int posY,posX;
using namespace std;
//variables 
//funciones internas
void init(){
	handle=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle,&csbi);
}

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

	FillConsoleOutputCharacter(handle, TEXT(' '), size, coord, &n);
	GetConsoleScreenBufferInfo(handle, &csbi);
	FillConsoleOutputAttribute(handle, csbi.wAttributes, size, coord, &n);


	SetConsoleCursorPosition(handle, coord);
}

void fullscreen(){//Comprueba si se puede hacer pantalla completa y lo hace
	int so = check_so();
	
	if (so == 10){
		::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);//Pantalla Completa
	}
}

void mov(int x, int y){//Movimiento del cursor de texto
		
			coord.Y=y;coord.X=x;

			SetConsoleCursorPosition(handle, coord);
}
		
void color(int color){//Color Para el texto
	SetConsoleTextAttribute(handle, color);
}
void cursor(bool curs){//Apagar Cursor de texto	 
	GetConsoleCursorInfo(handle, &cci);
	cci.bVisible = curs;
	SetConsoleCursorInfo(handle, &cci);
}
void text_type(int X,int Y){//Tamaño para el texto
		int x,y;
		if(X == 1|| Y == 1){
			x=8;y=16;
		}
		else {
			x = X;y = Y;
		}
		Font.cbSize = sizeof(Font);			
		Font.nFont = 0;						
		Font.dwFontSize.X = x;              
		Font.dwFontSize.Y = y;              
		Font.FontFamily = FF_DONTCARE;		
		Font.FontWeight = FW_NORMAL;
		wcscpy(Font.FaceName, L"Consolas"); // seleccion de fuente
		SetCurrentConsoleFontEx(handle, FALSE, &Font);
}
//funciones compuestas
void text(int PosX,int PosY,int Color,int fontX,int fontY,bool Curs,bool wait,string Word){
		int width = Word.length();//Variable con el largo del string Word
		posY=PosY;
		posX=PosX;
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

		
void text(int PosX, int PosY, int Color, int fontX, int fontY, bool Curs, bool wait, char Word) {
		posY=PosY;
		posX=PosX;
		mov(PosX, PosY);
		color(Color);
		cursor(Curs);
		text_type(fontX, fontY);
		ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
		cout << Word;
}

#endif /* Text.h */
