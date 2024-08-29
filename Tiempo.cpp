//Paola Alba Bugarín 
//Paulo Antonio Benard Olvera
//Carlos Alberto Sánchez Rodríguez
//Fátima Natalia Martínez Esparza

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <ctime>
#include "Tiempo.h"

using namespace std;

//constructor
Tiempo::Tiempo(int hora, int min, int seg){
	this->hora=hora;
	this->min=min;
	this->seg=seg;
}

Tiempo::Tiempo(const Tiempo &obj){
	this->hora=obj.hora;
	this->min=obj.min;
	this->seg=obj.seg;
}

Tiempo& Tiempo::operator-(const Tiempo& obj){
	int totalSeg;

	totalSeg=(this->hora*3600 + this->min*60 + this->seg - (obj.hora*3600 + obj.min*60 + obj.seg)); //segundos en total

	totalSeg = -totalSeg;
	this->hora = (totalSeg/3600);
    this->min = ((totalSeg%3600)/60);
    this->seg = (totalSeg%60);
    return *this;
}

Tiempo& Tiempo::operator=(const Tiempo& obj){
	//Se comprueba que no se guarde un obj en sí mismo
	if(this != &obj){
		this->hora=obj.hora;
		this->min=obj.min;
		this->seg=obj.seg;
	}
	return *this;
}

ostream& operator<<(ostream &out, const Tiempo& obj){
	if(obj.hora>=10 && obj.min>=10 && obj.seg>=10){
		out<<"["<<obj.hora<<":"<<obj.min<<":"<<obj.seg<<"]";
	}
	else if(obj.hora<10 && obj.min>=10 && obj.seg>=10){
		out<<"[0"<<obj.hora<<":"<<obj.min<<":"<<obj.seg<<"]";
	}
	else if(obj.hora<10 && obj.min<10 && obj.seg>=10){
		out<<"[0"<<obj.hora<<":0"<<obj.min<<":"<<obj.seg<<"]";
	}
	else if(obj.hora<10 && obj.min<10 && obj.seg<10){
		out<<"[0"<<obj.hora<<":0"<<obj.min<<":0"<<obj.seg<<"]";
	}
}

void Tiempo::texto(){
	ofstream tiempo;
	tiempo.open("Marcadores.txt", ios::out); //abre archivo
	
	if (tiempo.fail()){
		cout << "Necesitas jugar para crear marcador de tiempo";
		exit(1);
	}
	
	tiempo << "[" << this->hora << ":" << this->min << ":" << this->seg << "]" << endl;
	//cout<<"Tiempo de la partida guardado";

	tiempo.close();
}
