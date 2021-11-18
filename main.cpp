#include "UnDiaMenosHandle.h"
#include "Text.h"
#include "Layout.h"
int CenterX,CenterY;
void centrarXY();

int main(){
init();
fullscreen();
centrarXY();
		text(CenterX-7, CenterY, 11, Default, Default, false, true, "-Un Dia Menos-");
		text(CenterX-15,CenterY+1, 10, Default, Default, true,true , "Precione tecla para comenzar...");
		_getch();
		clear_screen();

		Draw_Border(2,CenterX*2,4,26);
}

void centrarXY(){
	HANDLE handle;//contiene el HANDLE de la consola
	CONSOLE_SCREEN_BUFFER_INFO csbi;//es una estructura que contiene las propiedades de la consola
	
	handle = GetStdHandle(STD_OUTPUT_HANDLE);//obtiene el HANDLE de la consola
	GetConsoleScreenBufferInfo(handle, &csbi);//toma los atributos de la consola y los guarda en csbi
	
	CenterX = csbi.srWindow.Right / 2;		
	CenterY = csbi.srWindow.Bottom / 2;
}
