//Paola Alba Bugar�n 
//Paulo Antonio Benard Olvera
//Carlos Alberto S�nchez Rodr�guez
//F�tima Natalia Mart�nez Esparza

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
