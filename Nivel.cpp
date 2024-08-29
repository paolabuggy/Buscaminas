//Paola Alba Bugarín 
//Paulo Antonio Benard Olvera
//Carlos Alberto Sánchez Rodríguez
//Fátima Natalia Martínez Esparza

#include <iostream>
#include "Nivel.h"

using namespace std;

Nivel::Nivel(int level){
	this->level=level;
	if(level==1){ 			//Modo fácil
		this->filas=8;
		this->columnas=8;
	}
	if(level==2){ 			//Modo intermedio
		this->filas=16;
		this->columnas=16;
	}
	if(level==3){			//Modo difícil similar al nivel 2 pero con más minas
		this->filas=16;
		this->columnas=16; 
	}
}
