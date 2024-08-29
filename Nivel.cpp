//Paola Alba Bugar�n 
//Paulo Antonio Benard Olvera
//Carlos Alberto S�nchez Rodr�guez
//F�tima Natalia Mart�nez Esparza

#include <iostream>
#include "Nivel.h"

using namespace std;

Nivel::Nivel(int level){
	this->level=level;
	if(level==1){ 			//Modo f�cil
		this->filas=8;
		this->columnas=8;
	}
	if(level==2){ 			//Modo intermedio
		this->filas=16;
		this->columnas=16;
	}
	if(level==3){			//Modo dif�cil similar al nivel 2 pero con m�s minas
		this->filas=16;
		this->columnas=16; 
	}
}
