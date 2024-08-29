//Paola Alba Bugarín 
//Paulo Antonio Benard Olvera
//Carlos Alberto Sánchez Rodríguez
//Fátima Natalia Martínez Esparza

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "Mapeo.h"

using namespace std;

//Constructor
Mapeo::Mapeo(int level):Nivel(level){
	this->numMinas=0;
	this->col=Nivel::getcolumnas(); 
	this->fil=Nivel::getfilas(); 
	this->partidaActiva=true;
	int i, j;
	//Se crea la matriz dinámica que contendrá las minas
    this->matrizJuego=new char*[this->fil];
	for(i=0; i<this->fil; i++){
		this->matrizJuego[i]=new char[this->col];
    }
    
    //Se crea la matriz que servirá para destapar
    this->tablero=new int*[this->fil];
    for(i=0; i<this->fil; i++){
		this->tablero[i]=new int[this->col];
    }
    
    //Se crea la matriz que servirá para guardar las banderas
    this->banderas=new int*[this->fil];
	for(i=0; i<this->fil; i++){
		this->banderas[i]=new int[this->col];
    }
    
    //Inicializar las matrices dinámica en 0
    for(i=0; i<this->fil; i++){
    	for(j=0; j<this->col; j++){
     	   this->matrizJuego[i][j]='0';
     	   this->tablero[i][j]=0;
     	   this->banderas[i][j]=0;
    	}
    }
}

void Mapeo::setnumMinas(){
	int nivel;
	nivel=Nivel::getlevel();
	if(nivel==1){			//Modo fácil
		this->numMinas=10;
	}
	if(nivel==2){			//Modo intermedio
		this->numMinas=40;
	}
	if(nivel==3){			//Modo difícil
		this->numMinas=70;
	}
}

int Mapeo::getnumMinas(){
	return this->numMinas;
}

//En la matriz Juego se colocan la cantidad de minas previamente guardadas en la variable numMinas 
//y estas se ponen aleatoriamente
void Mapeo::preparaMatrizJuego(){
	int filas, columnas, i, j, aux1, aux2;
	filas=Nivel::getfilas();
	columnas=Nivel::getcolumnas();
    //Inserta minas aleatoriamente comprobando que no se agregen minas en un mismo lugar
	srand(time(NULL));
	for(i=0; i<this->numMinas; i++){
		do{
			aux1=rand()%filas;
			aux2=rand()%columnas;
		}while(this->matrizJuego[aux1][aux2]=='*');
		this->matrizJuego[aux1][aux2]='*';
	}
}

//Se colocan los números en la matriz que contiene las minas, estos numeros se colocan en casillas que no tengan * (minas)
void Mapeo::ponerNumeros(){
	int i, j, numero, aux;
	for(i=0; i<this->fil; i++){
    	for(j=0; j<this->col; j++){
             if(this->matrizJuego[i][j]!='*'){ //Si la casilla no tiene minas se le agrega el número de minas que tiene cerca
            	aux=j-1;
                numero=0;
                //Se recorre alrededor de la casilla para detectar minas y así contabilizarlas en la variable (numero)
                //Se evita recorrer posiciones negativas o fuera del alcance de la matriz dinámica
                while(aux<=j+1){ 
                    if(aux>=0){
                    	if((i-1)>=0){
                    		if(this->matrizJuego[i-1][aux]=='*'){
                    			numero++;
							}
                		}
                		if((i+1)!=this->fil){
                   			if(this->matrizJuego[i+1][aux]=='*'){
                       			numero++;
                    		}
						}
						if(this->matrizJuego[i][aux]=='*' && aux!=j){
                        	numero++;
                   		}
					}
                	aux++;
            	} 
            	//Si el número es igual a 0 no se tiene que agregar a la matriz ya que originalmente la matriz se inicializó en ceros
                if(numero!=0){ 
                	Mapeo::preparaMatrizJuego(i,j,numero);
                }
            }
        }
    }
} 

//Coloca el número de minas que tiene alrededor, una casilla que no tiene mina
void Mapeo::preparaMatrizJuego(int i, int j, int num){
	if(num==1){
        this->matrizJuego[i][j]='1';
    }
    else if(num==2){
        this->matrizJuego[i][j]='2';
    }
	else if(num==3){
        this->matrizJuego[i][j]='3';
    }
	else if(num==4){
        this->matrizJuego[i][j]='4';
    }
	else if(num==5){
        this->matrizJuego[i][j]='5';
    }
	else if(num==6){
        this->matrizJuego[i][j]='6';
    }
	else if(num==7){
        this->matrizJuego[i][j]='7';
	}
	else if(num==8){
    	this->matrizJuego[i][j]='8';
    }
}

void Mapeo::destapa(){ //"constructor" para la matriz tablero 
	int aux=0;
    for(int i=0; i<this->fil; i++){
        for(int j=0; j<this->col; j++){
            if(this->matrizJuego[i][j]=='0'){ //si no tienen una mina
				aux=j-1;
                while(aux<=j+1){
                	if(0<=aux && aux<this->col && i<(this->fil-1)){ //
                        this->tablero[i+1][aux]=-1;
                    }
                	if(0<=aux && aux<this->col){
                        this->tablero[i][aux]=-1;
                    }
                    if(0<=aux && 0<i && aux<this->col){
                    	this->tablero[i-1][aux]=-1;
                    }
                    aux++;
            	}  
            }else{ 
                if(this->tablero[i][j]!=-1){
                    this->tablero[i][j]=1;
                }
            }          
        }
    }
}

void Mapeo::destapa(int x, int y){ //Cambia el estado de una casilla a 0 para ser destapada, ya sea una casilla o varias
    if(this->tablero[x][y]==-1 && this->matrizJuego[x][y]=='0'){
    	setCasillasAdyacentes(x,y);
	}else{
		this->tablero[x][y]=0;
	}
	if(this->matrizJuego[x][y]=='*'){ //si encuentra una mina se desactiva la partida activa para después mostrar que perdió
		this->partidaActiva=false;
		this->tablero[x][y]=0;
		this->matrizJuego[x][y]='X';
	}
}

//Método recursivo que permite condicionar las posiciones sin minas para facilitar el destape de casillas.
//En vez de destapar una por una se pueden destapar las casillas adyacentes si estas no cuentan con minas.
void Mapeo::setCasillasAdyacentes(int i, int j){ 
    this->tablero[i][j]=0;
    for(int x=i-1; x<=i+1; x++){
    	for(int y=j-1; y<=j+1; y++){
    		if((x>=0) && (y>=0) && (y<this->col) && (x<this->fil) && ((x!=i)||(y!=j))){
    			if(this->tablero[x][y]!=0){
    				this->tablero[x][y]=0;
    				if(this->matrizJuego[x][y]=='0'){
    					setCasillasAdyacentes(x, y);
					}
				}
			}
		}
	}
}

//Se comprueba si aún quedan banderas disponibles para utilizar
bool Mapeo::checaBanderas(){
	int cont=0;
	for(int i=0; i<this->fil; i++){
		for(int j=0; j<this->col; j++){
			if(this->banderas[i][j]==2){
				cont++;
			}
		} 
	}
	if(cont<this->numMinas){
		return true;
	}else{
		return false;
	}
}

void Mapeo::insertaBandera(int x, int y){
	int band=this->numMinas;
	if(Mapeo::checaBanderas()==true && this->banderas[x][y]!=2 && this->tablero[x][y]!=0){
		this->banderas[x][y]=2;
	}
	if(Mapeo::checaBanderas()==false){
		cout<<"Ya no hay mas banderas :c";
	}
}

void Mapeo::quitaBandera(int x, int y){
	if(this->banderas[x][y]==2){
		this->banderas[x][y]=0;
	}
}

bool Mapeo::detectaGanador(){
	int cont=0, cont2=0, minas;
	minas=this->numMinas;
	for(int i=0; i<this->fil; i++){
		for(int j=0; j<this->col; j++){
			if(this->tablero[i][j]!=0){
				cont++; //cuenta cuantas casillas están sin destapar
			}
			if(this->banderas[i][j]==2 && this->matrizJuego[i][j]=='*'){
				cont2++;
			}
		}
	}
	
	if(cont==minas || cont2==minas){
		return true;
	}else{
		return false;
	}
}

void Mapeo::imprimeMatrizJuego(){
    printf("       ");
    for(int n=0; n<this->col; n++){
		if (n<9)
			cout<<n<<"   ";
		else
			cout<<n<<"  ";
	}
	cout << endl;
	printf("     ");
	char tab;
    for(int n=0; n<this->col*4; n++){
    	if(n%4 == 0)
    		tab = 203;
    	else
    		tab = 205;
		if (n==0)
			{
				tab = 201;
				cout<<tab;
				tab=205;
			}
		else
			cout<<tab;
	}
	tab = 187;
	cout<<tab<<endl;
	
    for(int i=0; i<this->fil; i++){
    	tab = 186;
    	if(i<10)
			cout<<"  "<<i<<"  "<< tab << " ";
		else
			cout<<" "<<i<<"  "<<tab<<" ";
        for(int j=0; j<this->col; j++){
        	if(this->tablero[i][j]==0){
        		cout<<this->matrizJuego[i][j]<<" "<<tab<<" ";
			}
			else if(this->banderas[i][j]==2) {
				cout<<"M "<< tab<<" ";	
			}else{
				cout<<"  "<<tab<<" ";
			}
        }
        cout << endl;
        if(!((i+1) == this->fil))
        	{
        		if(i<10)
					cout<<"     ";
				else
					cout<<"     ";
		        for(int j=0; j<this->col*4; j++){
		        	if(j%4 == 0)
		        		tab = 206;
		        	else
		        		tab = 205;
		        	if(j==0)
		        		tab = 204;
		        	cout << tab;
				}
			tab = 185;
			cout << tab << endl;
			}
    }
    cout<<"     ";
    for(int x=0; x<this->fil*4; x++){
    		if(x%4 == 0)
    			tab = 202;
    		else
    			tab = 205;
	    	if(x==0)
	    		tab=200;
	    	cout << tab;
		}
	tab = 188;
	cout << tab << endl;
    }

void Mapeo::imprimeMatrizJuego(bool win){
	if(win!=true){
		printf("       ");
	    for(int n=0; n<this->col; n++){
			if (n<9)
				cout<<n<<"   ";
			else
				cout<<n<<"  ";
		}
		cout << endl;
		printf("     ");
		char tab;
	    for(int n=0; n<this->col*4; n++){
	    	if(n%4 == 0)
	    		tab = 203;
	    	else
	    		tab = 205;
			if (n==0)
				{
					tab = 201;
					cout<<tab;
					tab=205;
				}
			else
				cout<<tab;
		}
		tab = 187;
		cout<<tab<<endl;
		
	    for(int i=0; i<this->fil; i++){
	    	tab = 186;
	    	if(i<10)
				cout<<"  "<<i<<"  "<< tab << " ";
			else
				cout<<" "<<i<<"  "<<tab<<" ";
	        for(int j=0; j<this->col; j++){
	        	tab = 186;
	        	cout<<this->matrizJuego[i][j]<<" "<<tab<<" ";
	        }
	        cout << endl;
	        if(!((i+1) == this->fil))
	        	{
	        		if(i<10)
						cout<<"     ";
					else
						cout<<"     ";
			        for(int j=0; j<this->col*4; j++){
			        	if(j%4 == 0)
			        		tab = 206;
			        	else
			        		tab = 205;
			        	if(j==0)
			        		tab = 204;
			        	cout << tab;
					}
				tab = 185;
				cout << tab << endl;
				}
	    }
	    cout<<"     ";
	    for(int x=0; x<this->fil*4; x++){
	    		if(x%4 == 0)
	    			tab = 202;
	    		else
	    			tab = 205;
		    	if(x==0)
		    		tab=200;
		    	cout << tab;
			}
		tab = 188;
		cout << tab << endl;
	    }
	/*	cout<<"      ";
    	for(int n=0; n<this->col; n++){
			if (n<9)
				cout<<n<<"   ";
			else
				cout<<n<<"  ";
		}
		cout<<endl;
   	 	for(int i=0; i<this->fil; i++){
    		if(i<10)
				cout<<"  "<<i<<"  | ";
			else
				cout<<" "<<i<<"  | ";
    	    for(int j=0; j<this->col; j++){
       	 		cout<<this->matrizJuego[i][j]<<" | ";
      	  	}
      	  	cout<<endl;
  	  	}
	}*/
}

void Mapeo::liberarMemoria(){
	//Se borran las matrices dinámicas 
	for(int i=0; i<this->fil; i++){
		delete[] this->matrizJuego[i]; 
		delete[] this->tablero[i];
		delete[] this->banderas[i];
	}
	//Borra el último vector de la matriz
	delete[] this->matrizJuego; 
	delete[] this->tablero;
	delete[] this->banderas;
}
