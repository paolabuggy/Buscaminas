//Paola Alba Bugarín 
//Paulo Antonio Benard Olvera
//Carlos Alberto Sánchez Rodríguez
//Fátima Natalia Martínez Esparza

#ifndef Tiempo_h
#define Tiempo_h
using namespace std;

class Tiempo{
	private:
		int hora;
		int min;
		int seg;
	public:
		Tiempo(): hora(0),min(0),seg(0){} //Constructor por default
		Tiempo(int,int,int); //Constructor con parámetros
		Tiempo(const Tiempo &obj); //Constructor utilizando un objeto Tiempo (copia) 
		int gethora(){return this->hora;}
		int getmin(){return this->min;}
		int getseg(){return this->seg;}
		void texto(); //Guardar tiempo en archivo de texto
		Tiempo& operator-(const Tiempo&);
		Tiempo& operator=(const Tiempo&);
		friend ostream& operator<<(ostream &out, const Tiempo& obj);
};

#endif
