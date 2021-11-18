#ifndef LAYOUT_H 
#define LAYOUT_H
/*
;--------------------------------------
;Motor Layouts
;
;Dev by: Nahu
;Coments lang: Spanish
;--------------------------------------
;	No se pueden hacer mas de 4 recuadros
;
;--------------------------------------
*/
//librerias
#include "Text.h"
//variables

//funciones
void Draw_Border(int Xstart,int Xend,int Ystart, int Yend) {
		for (int i =Xstart ; i < Xend ; i++) {//Barra Superior
			text(i, Ystart, 13, Default, Default,false , false, "#");
		}
		for (int i = Ystart ; i < Yend ; i++) {//Barra Izquierda
			text(Xstart, i, 13, Default, Default, false, false, "#");
		}
		for (int i = Ystart ; i < Yend ; i++) {//Barra Derecha
			text(Xend, i, 13, Default, Default, false, false, "#");
		}
		for (int i = Xstart; i < Xend ; i++) {//Barra Inferior
			text(i, Yend-1, 13,Default, Default, false, false, "#");
		}
		mov(Xend,Yend+1);
}
//void Set_Border(int Border_cant,int Xstart[],int Xend[],int Ystart[], int Yend[]) {
//	border_cant=Border_cant;
//		for(int i=0;i<border_cant&&i>=4;i++){
//			tmp->xstart[i]=Xstart[i];
//			tmp->xend[i]=Xend[i];
//			tmp->ystart[i]=Ystart[i];
//			tmp->yend[i]=Yend[i];
//		}
		//delete tmp;
//}

#endif/*Layout.h */
