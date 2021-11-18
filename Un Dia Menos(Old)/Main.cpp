#include "Text.h"
#include "Chapter 1.cpp"
#define Default (1)
using namespace std;
/*
; ----------------------------------------------------------------------------------------
; 								     Un Dia Menos
; -Developed by:Nahu
;
; -Descripcion:Juego
;
; 
;	
; 
;*DeV cOmmENts*
;*Agregar el al menu contextual el cuadro de respuestas* *Agregar menu inferior, o no agregar y extender el menu*
;*PROBLEMA TOTAL CON LA LECTURA DE DATOS*
; ----------------------------------------------------------------------------------------
*/
//capitulos

void chapter_one();

//capitulos
//otras funciones

void clear_screen();

//otras funciones
int main(int argc, char** argv) {//main
	//Ajustes pre compilado

		::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);//Pantalla Completa

	//Ajustes pre compilado
	//Variables


	//Variables
	//Juego

		//Menu Principal
		
		//Menu principal

		//Capitulos
			
		chapter_one();

		//Capitulos

			_getch();
	//juego
}
//funciones de uso en el main
void clear_screen(){//Limpiador de pantalla, escribiendo caracteres vacios
	DWORD n;                         
	DWORD size;                      
	COORD coord = { 0 };               
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(h, &csbi);


	size = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n);
	GetConsoleScreenBufferInfo(h, &csbi);
	FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);


	SetConsoleCursorPosition(h, coord);
}





