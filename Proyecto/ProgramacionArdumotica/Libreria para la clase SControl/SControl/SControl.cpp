#include "SControl.h"



SControl::SControl(int NUM_MEDIDAS){
	num_medidas=NUM_MEDIDAS;
	Medidas = new double [num_medidas];
	for(int i=0; i<num_medidas; i++)
		Medidas[i]=valor_nulo; 
	posicion=-1;
}
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
		bool entra=false;
		for(int i=0; i<num_medidas; i++){
			if(Medidas[i]!=valor_nulo){
				media+=Medidas[i];
				medidas_validas++;
				entra=true;
			}
		}
		if(entra)
			media=media/medidas_validas;
		else 
			media=valor_nulo;
		//removeMedidas();
		
		return media;
}

int SControl::get_NumMedidas(){
	return num_medidas;
}

void SControl::removeMedidas(){
	for(int i=0; i<num_medidas; i++)
		Medidas[i]=valor_nulo;
}

bool SControl::MedidasCompletas(){
	bool vectorCompleto=false;
	if(posicion+1==num_medidas)
		vectorCompleto=true;
	return vectorCompleto;
}