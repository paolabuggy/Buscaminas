//Paola Alba Bugarín 
//Paulo Antonio Benard Olvera
//Carlos Alberto Sánchez Rodríguez
//Fátima Natalia Martínez Esparza

#ifndef Mapeo_h
#define Mapeo_h
#include "Nivel.h"

class Mapeo : public Nivel{
	private:
		int numMinas;
		bool partidaActiva;
		int fil;
		int col;
		char **matrizJuego;	//guarda minas y números
		int **tablero; 		//para el tablero que se mostrará al usuario
		int **banderas; 	//para guardar las banderas que agrega el usuario
	public:
		Mapeo(){}
		Mapeo(int level);
		void setnumMinas();
		int getnumMinas();
		inline char** getmatrizJuego(){return this->matrizJuego;}
		bool getpartidaActiva(){return this->partidaActiva;}
		void preparaMatrizJuego(); //
		void preparaMatrizJuego(int i, int j, int num); //
		void ponerNumeros(); //
		void imprimeMatrizJuego();
		void imprimeMatrizJuego(bool win);
		void destapa(); //
		void destapa(int x, int y); //
		void setCasillasAdyacentes(int i, int j);
		bool checaBanderas();
		void insertaBandera(int x, int y);
		void quitaBandera(int x, int y);
		bool detectaGanador();
		void operator delete [](void* memoria){}
		void liberarMemoria();
};

#endif
