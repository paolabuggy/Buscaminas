//Paola Alba Bugarín 
//Paulo Antonio Benard Olvera
//Carlos Alberto Sánchez Rodríguez
//Fátima Natalia Martínez Esparza

#ifndef Nivel_h
#define Nivel_h

class Nivel{
	private:
		int level;
		int filas;
		int columnas;
	public:
		Nivel(){}
		Nivel(int level);
		int getlevel()const{
			return this->level;
		}
		int getfilas()const{
			return this->filas;	
		}
		int getcolumnas()const{
			return this->columnas;
		}
};

#endif
