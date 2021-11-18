/*
	Text.h Es el maniobrador de la consola para el programa un dia menos

*/
#ifndef TEXT_H //protector de definicion
#define TEXT_H
#include <iostream> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include<sys/stat.h>
#include <string>
#include <vector>

#define Default (1)

using namespace std;

class Console {
	private:
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//Variable Handle de ventanas 

		void mov(int x, int y){//Movimiento del cursor de texto

			COORD coord;//Variable de coordenadas en la consola
			coord.Y=y;coord.X=x;//La variable toma las posiciones del eje X e Y y les da los valores que quiero

			SetConsoleCursorPosition(handle, coord);//Posiciona el cursor de escritura en la posicion que quiero
		}

		void color(int color){//Color Para el texto

			SetConsoleTextAttribute(handle, color);//Se le pasa un numero como argumento el cual es el color {Ver tabla de colores}
		}

		void cursor(bool curs){//Apagar Cursor de texto
			CONSOLE_CURSOR_INFO cursor_info;//Estructura de datos del cursor de texto
			 
			GetConsoleCursorInfo(handle, &cursor_info);//Tomo los valores del cursor de texto
    		cursor_info.bVisible = curs;//Le paso un bit que determina si esta encendido o no
    		SetConsoleCursorInfo(handle, &cursor_info );//Añado los cambios a la variable
		}
		void text_type(int X,int Y){//Tamaño para las letras
		int x,y;// Variable que va a contener los valores de los argumentos
		CONSOLE_FONT_INFOEX Font;//Estructura de datos de los caracteres de la consola
		if(X == 1|| Y == 1){//Si el tamaño es Macro"Default"
			x=8;y=16;//Numeros standar del font
		}
		else {//Caso contrario se pasa el valor de los argumentos
			x = X;y = Y;
		}
		Font.cbSize = sizeof(Font);			
		Font.nFont = 0;						//indice de fuente
		Font.dwFontSize.X = x;              // Ancho de cada carácter en la fuente
		Font.dwFontSize.Y = y;              // Altura
		Font.FontFamily = FF_DONTCARE;		//Caracteristicas de la fuente
		Font.FontWeight = FW_NORMAL;		//

		wcscpy(Font.FaceName, L"Consolas"); // seleccion de fuente
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &Font);
		}

	public:
		void text(int PosX,int PosY,int Color,int fontX,int fontY,bool Curs,bool wait,string Word){//Escritura en pantalla por strning
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
		void text(int PosX, int PosY, int Color, int fontX, int fontY, bool Curs, bool wait, char* Word) {//Escrutura en pantalla por char dinamico
			mov(PosX, PosY);
			color(Color);
			cursor(Curs);
			text_type(fontX, fontY);
			ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
			cout << Word;
			delete Word;
		}
		void text(int PosX, int PosY, int Color, int fontX, int fontY, bool Curs, bool wait, char Word) {//Escrutura en pantalla por char
			mov(PosX, PosY);
			color(Color);
			cursor(Curs);
			text_type(fontX, fontY);
			ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
			cout << Word;
		}
		void game_layout_bar_border() {//Contenerdor superior de el juego
			HANDLE handle;//contiene el HANDLE de la consola
			CONSOLE_SCREEN_BUFFER_INFO csbi;//es una estructura que contiene las propiedades de la consola

			handle = GetStdHandle(STD_OUTPUT_HANDLE);//obtiene el HANDLE de la consola
			GetConsoleScreenBufferInfo(handle, &csbi);//toma los atributos de la consola y los guarda en csbi

			int maxX = csbi.srWindow.Right;//Borde derecho de la barra
			int maxY = csbi.srWindow.Bottom;//Borde inferior de la barra
			int CenterX = maxX / 2;
			int CenterY = maxY / 2;
			for (int i = 4; i < maxX; i++) {//Barra Superior
				text(i, 0, 13, Default, Default,false , false, "#");
			}
			for (int k = 4; k < maxX; k++) {//Barra Inferior
				text(k, maxY/3, 13,Default, Default, false, false, "#");
			}
			for (int a = 1; a < maxY/3; a++) {//Barra Izquierda
				text(4, a, 13, Default, Default, false, false, "#");
			}
			for (int j = 1; j < maxY/3; j++) {//Barra Derecha
				text(maxX-1, j, 13, Default, Default, false, false, "#");
			}
		}
		void game_layaut_narration() {//caracteres disponibles x78-x152, y16-43
			HANDLE handle;
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			handle = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(handle, &csbi);

			int maxX = csbi.srWindow.Right;
			int maxY = csbi.srWindow.Bottom;
			int CenterX = maxX / 2;
			int CenterY = maxY / 2;
			for (int i = maxX/2; i < maxX-1; i++) {//Barra Superior
				text(i, maxY/3+1, 2, Default, Default, false, false, "#");
			}
			for (int k = maxX/2; k < maxX; k++) {//Barra Inferior
				text(k, maxY-2, 2, Default, Default, false, false, "#");
			}
			for (int a = maxY/3+1; a < maxY-2; a++) {//Barra Izquierda
				text(maxX/2, a, 2, Default, Default, false, false, "#");
			}
			for (int j = maxY/3+1; j < maxY-2; j++) {//Barra Derecha
				text(maxX-1, j, 2, Default, Default, false, false, "#");
			}
		}
		void game_layout_answer() {//caracteres disponibles x5-x74, y16-27
			HANDLE handle;//contiene el HANDLE de la consola
			handle = GetStdHandle(STD_OUTPUT_HANDLE);//obtiene el HANDLE de la consola
			CONSOLE_SCREEN_BUFFER_INFO csbi;//es una estructura que contiene las propiedades de la consola
			GetConsoleScreenBufferInfo(handle, &csbi);//toma los atributos de la consola y los guarda en csbi
			int maxX = csbi.srWindow.Right;
			int maxY = csbi.srWindow.Bottom;
			int CenterX = maxX / 2;
			int CenterY = maxY / 2;
			for (int i = 4; i < maxX / 2 - 1; i++) {//Barra Superior
				text(i, maxY / 3 + 1, 11, Default, Default, false, false, "#");
			}
			for (int k = 4; k < maxX / 2; k++) {//Barra Inferior
				text(k, maxY - 2, 11, Default, Default, false, false, "#");
			}
			for (int a = maxY / 3 + 1; a < maxY - 2; a++) {//Barra Izquierda
				text(4, a, 11, Default, Default, false, false, "#");
			}
			for (int j = maxY / 3 + 1; j < maxY - 2; j++) {//Barra Derecha
				text(maxX / 2 - 1, j, 11, Default, Default, false, false, "#");
			}
		}
		
};
class Game {//Manejar textos y datos del usuario
private:
	Console console;
	int result, j = 0, maxcount = 73,i = 0;
	int checkIfFileExists(const char* filename) {
		struct stat buffer;
		int exist = stat(filename, &buffer);
		if (exist == 0)
			return 1;
		else
			return 0;
		delete filename;
	}
	void narration(string nar) {
		HANDLE handle;//contiene el HANDLE de la consola
		handle = GetStdHandle(STD_OUTPUT_HANDLE);//obtiene el HANDLE de la consola
		CONSOLE_SCREEN_BUFFER_INFO csbi;//es una estructura que contiene las propiedades de la consola
		GetConsoleScreenBufferInfo(handle, &csbi);//toma los atributos de la consola y los guarda en csbi


		int chars = nar.length(),k=0;//caracteres de la narracion
		string tmp[12];
		int lines,res;
		int TOP = csbi.srWindow.Bottom / 3 + 2;
		int BOT = csbi.srWindow.Bottom - 2;
		int LEFT = csbi.srWindow.Right / 2 + 1;
		int Right = csbi.srWindow.Right;
		j = 0;
		while (j != chars) {
			console.text(LEFT+k, TOP + i, 15, Default, Default, false, true, nar[j]);
			if (k >= 74) {	
				k = -1;
				i++;
			}
			j++;
			k++;
		}
	}
	int answer(int num, string answers[5]) {

		int limit_minX = 5, limit_maxX = 74, limit_minY = 16, limit_maxY = 27, result = 0, key = 0, a = 0;
		for (int i = 0; i < num; i++) {
			console.text(limit_minX, limit_minY + i, 15, Default, Default, false, true, answers[i]);
		}
		console.text(limit_minX, limit_maxY - 1, 10, Default, Default, false, false, "Selecione el numero con las ");
		console.text(limit_minX, limit_maxY, 10, Default, Default, false, false, "flechas y precione enterpara aceptar");
		do {
			console.text(limit_minX, limit_minY + a, 159, Default, Default, false, false, answers[a]);
			switch (_getch()) {
			case 80: {
				if (a < num - 1) {
					console.text(limit_minX, limit_minY + a, 15, Default, Default, false, false, answers[a]);
					a++;
				}
				break;
			}
			case 72: {
				if (a >= 1) {
					console.text(limit_minX, limit_minY + a, 15, Default, Default, false, false, answers[a]);
					a--;
				}
				break;
			}
			case 13: {
				result = a + 1;
				key = 1;
				break;
			}
			}

		} while (key != 1);
		return result;
	}
	string log_read_last() {
		string content;
		ifstream file("save.txt");
		if (file.good()) {
			file.open("save.txt", ios::in);
			if (file.fail()) {
				return content;
			}
			while (!file.eof()) {
				getline(file, content);
			}
			file.close();
		}
		return content;
	}
	void log_write(int _answer, string before) {
		ofstream file;
		if (checkIfFileExists("save.txt")) {
			file.open("save.txt", ios::app);
			file << before << endl << _answer;
			file.close();
		}
		else {
			file.open("save.txt", ios::out);
			file << _answer << endl;
			file.close();
		}
	}
public:
	void answer_write(int num_answers, string _answers[5]) {
		string temp_content;//contenido previo
		result = answer(num_answers, _answers);//guarda el resultado
		temp_content = log_read_last();//guarda el contenido previo
		log_write(result, temp_content);//escribe el resultado y el anterior contenido	
	}
	void narration_handle(string nar) {
		narration(nar);
	}
	void ENDL() {
		i++;
	}
	void answer_read(int _recive) {//not working
		ifstream read;
		string out;
		char tmp[90];
		if (read.good()) {
			read.open("save.txt", ios::in);
				if (read.fail()) {
					//return -1;
				}
				int i = 0;
				while (read.eof()) {
					read >> tmp;

				}
		}
		cout << "momento";
		system("pause");
		
	}
};
 
#endif /* Text.h */
