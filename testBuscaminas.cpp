//Paola Alba Bugarín 
//Paulo Antonio Benard Olvera
//Carlos Alberto Sánchez Rodríguez
//Fátima Natalia Martínez Esparza

//JUEGO DEL BUSCAMINAS 

#include <iostream>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <limits>

#include "Nivel.h"
#include "Mapeo.h"
#include "Tiempo.h"

using namespace std;

struct THoraA{ 
	int horas;
	int mins;
	int segs;
};

void gotoxy(int x, int y){
	HANDLE hcon;
	hcon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon, dwPos);
}

//Funciones
THoraA obtenerHoraActual();
void validacion(int m, int n, int opc);

int main(){
	int opcion, posi, posj, valido, auxgoto, menu;
	THoraA horaAct; //Variable para guardar la hora actual
	bool win;
	system("color 3F");
	system("mode con: cols=160 lines=43"); 
	do{
		int lvl=0;
		do{
			gotoxy(34,2);
			cout<<"BIENVENIDO AL BUSCAMINAS";
			gotoxy(30,3);
			cout<<"Facil (1), Medio (2), Dificil (3)";
			gotoxy(30,4);
			cout<<"Ingrese el nivel del buscaminas: ";
			cin>>lvl;
			validacion(1, 3, lvl);
		}while(lvl!=1 && lvl!=2 && lvl!=3);
		
		//Para el gotoxy y acomodar los elementos del juego según el nivel
		if(lvl==2 || lvl==3){
			auxgoto=10;
		}else{
			auxgoto=0;
		}
		//Se inicializa el juego
		Mapeo game(lvl);
		game.setnumMinas();
		game.preparaMatrizJuego();
		game.ponerNumeros();
		game.destapa();
		//Se toma la hora en la que inicia el juego
		horaAct=obtenerHoraActual();
		Tiempo inicio(horaAct.horas, horaAct.mins, horaAct.segs);
		Tiempo total;
		do{
			system("cls");
			valido=1;
			gotoxy(30,2);
			cout<<"BUSCAMINAS";
			gotoxy(29,3);
			cout<<"HAY "<<game.getnumMinas()<<" MINAS";
			gotoxy(0, 6);
			game.imprimeMatrizJuego();
			//Pequeño menú para las opciones de las casillas
			gotoxy(auxgoto+68, 15);
			cout<<"1...Destapar casilla";
			gotoxy(auxgoto+68, 16);
			cout<<"2...Agregar bandera a casilla";
			gotoxy(auxgoto+68, 17);
			cout<<"3...Eliminar una bandera";
			do{
				gotoxy(auxgoto+68, 18);
				cout<<"Seleccione una opcion: ";
				cin>>menu;
				validacion(1, 3, menu);
			}while(menu!=1 && menu!=2 && menu!=3);
			//Se solicitan las coordenadas
			int aux;
			aux=game.getfilas();
			do{
				gotoxy(auxgoto+68, 8);
				cout<<"Ingrese la posicion de la fila (horizontal): ";
				cin>>posi;
				validacion(0, aux-1, posi);
			}while(!(posi>=0 && posi<=aux));
			aux=game.getcolumnas();
			do{
				gotoxy(auxgoto+68, 10);
				cout<<"Ingrese la posicion de la columna (vertical): ";
				cin>>posj;
				validacion(0, aux-1, posi);
			}while(!(posi>=0 && posi<=aux));
			/*
			while(valido==1){
				gotoxy(auxgoto+68, 10);
				cout<<"Ingrese la posicion de la columna (vertical): ";
				cin>>posj;
				if(posi<0 || posj<0 || posi>=game.getfilas() || posj>=game.getcolumnas()){
					gotoxy(auxgoto+68, 12);
					cout<<"Posicion invalida, intente de nuevo";
					valido=1;
				}else{
					valido=0;
				}
			}
			*/
			//Según la opción seleccionada del menú se destapan las casillas o se les pone una bandera
			switch(menu){
				case 1:
					game.destapa(posi,posj);
					break;
				case 2:
					game.insertaBandera(posi,posj);
					break;
				case 3:
					game.quitaBandera(posi,posj);
					break;
			}
			gotoxy(0, 6);
			//Se vuelve a imprimir el tablero con los cambios
			game.imprimeMatrizJuego();
			//Se checa si ha ganado
			win=game.detectaGanador();
		}while(game.getpartidaActiva()==true && win==false);
		//Se obtiene el tiempo actual en el que acabó el juego para restarlo al tiempo que se tomó al iniciar la partida
		//para imprimir en pantalla lo que tardó el usuario 
		horaAct=obtenerHoraActual();
		Tiempo fin(horaAct.horas, horaAct.mins, horaAct.segs);
		total=inicio-fin;
	
		//Se le informa al usuario si ganó o perdió
		if(win==true){
			gotoxy(78, 5);
			cout<<"FELICIDADES GANASTE!!!";
		}else{
			gotoxy(0, 6);
			game.imprimeMatrizJuego(win);
			gotoxy(78, 5);
			cout<<"PERDISTE :(";
		}
		gotoxy(78, 6);
		cout<<"Tiempo: ";
		cout<<total;
		total.texto();
		//Se le pregunta al usuario si desea volver a jugar
		do{
			gotoxy(auxgoto+68, 21);
			printf("%cDesea jugar de nuevo? Si(1)/No(2): ", 168);
			cin>>opcion;
			validacion(1, 2, opcion);
		}while(opcion!=1 && opcion!=2);
		//Se libera el espacio de la memoria dinámica utilizada para las matrices dinámicas
		game.liberarMemoria();
		system("cls");
	}while(opcion==1);
	//Mensaje que se muestra al acabar el juego
	gotoxy(30,5);
	cout<<"HASTA LUEGO!!! :)"<<endl<<endl<<endl;
	
	system("pause");
	return 0;
}

THoraA obtenerHoraActual(){
	THoraA hora;
	time_t tSac=time(NULL); 			//Función para conocer
	struct tm* tmP=localtime(&tSac); 	//la hora actual
	hora.horas=tmP->tm_hour;
	hora.mins=tmP->tm_min;
	hora.segs=tmP->tm_sec;
	return (hora); //La hora actual se guarda en una variable tipo estructura y la retorna 
}

//Función que evita que se cicle o truene el programa :)
void validacion(int m, int n, int opc){ 
	if(!cin || !(opc>=m && opc<=n)){
		cin.clear(); //Borra el indicador de error
		cin.ignore(numeric_limits<int>::max(), '\n'); //Ignora el parámetro y borra el buffer de cin
	}
}
