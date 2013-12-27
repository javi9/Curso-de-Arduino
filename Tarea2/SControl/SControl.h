#ifndef	SCONTROL_H
#define	SCONTROL_H
#include <iostream>

#define valor_nulo 1000000 // Valores por defecto del vector Medidas.

using namespace std;

class SControl {
	
	private:
		double *Medidas;	// Vector donde almaceno las medidas tomadas.
		int num_medidas;	// Variable que indica la capacidad del vector medidas.
		int posicion;		// Variable que utilizo para controlar las inserciones en el vector Medidas.
		void removeMedidas() // Funcion que borra las medidas e inicializa el vector a valor nulo. El usuario no puede llamarla al estar dentro de private.
		

	public:	
		SControl(){};		// Constructor por defecto
		SControl(int NUM_MEDIDAS);	// Constructor que inicializa las posiciones del vector Medidas a valor nulo con capacidad NUM_MEDIDAS
		//~SControl(){};	// Destructor
		void RellenarMedidas(double temp); // Metemos un valor en el vector.
		double CalcularMedia();	// Calculamos la media de los valores no nulos que haya en el vector Medidas.
		int get_NumMedidas();	// Funcion para obtener Numero de medidas
		bool MedidasCompletas(); // Funcion que indica si se ha llenado el vector de medidas no nulas.
};



#endif
