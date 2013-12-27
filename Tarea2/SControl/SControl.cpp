#include "SControl.h"


// Constructor por defecto
SControl::SControl(){
	num_medidas=5;
	Medidas = new double [num_medidas];
	for(int i=0; i<num_medidas; i++)
		Medidas[i]=valor_nulo;
	posicion=-1;
}

// Constructor en el que indicamos el numero de medidas
SControl::SControl(int NUM_MEDIDAS){
	num_medidas=NUM_MEDIDAS;
	Medidas = new double [num_medidas];
	for(int i=0; i<num_medidas; i++)
		Medidas[i]=valor_nulo; 
	posicion=-1;
}

// Destructor
/*
SControl::~SControl(){
	delete Medidas;
}
*/

void SControl::RellenarMedidas(double temp){
	posicion++;
	if(posicion<num_medidas){
		Medidas[posicion]=temp;
	}else{
		posicion=0;
		Medidas[posicion]=temp;
	}
	
}

double SControl::CalcularMedia(){
		
		double media=0;
		int medidas_validas=0;
		for(int i=0; i<num_medidas; i++){
			if(Medidas[i]!=valor_nulo)
				media+=Medidas[i];
				medidas_validas++;
		}
		media=media/medidas_validas;
		return media;
}

int SControl::get_NumMedidas(){
	return num_medidas;
}

void SControl::removeMedidas(){
    for(int i=0; i<num_medidas; i++)
        Medidas=valor_nulo;
}

// Devuelve true si el vector esta lleno.
bool SControl::MedidasCompletas(){
	bool vectorCompleto=false;
	if(posicion+1==num_medidas)
		vectorCompleto=true;
	return vectorCompleto;
}