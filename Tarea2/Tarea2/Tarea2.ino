#include <SControl.h>
#include <TimerOne.h>


//Interrupcion, utilizare el timer1
// Objetivo -> Cada 8 minutos tome la temperatura correspondiente en ese instante de tiempo.

volatile bool cerrojo=false;
volatile int cont=0;
int Segundos=480; // Variable para indicar cada cuantos segundos quiero que me tome medidas. Los segundos deben ser multiplos de 8 para que sea exacto.
                  // Con segundos=480 tomará medidas cada 8 minutos.
int TiempoInterrupcion=Segundos/8; // El 8 indica cada cuantos segundos se ejecuta la interrupcion.

int temp=0, MediaTemp; // Variables donde guardo la lectura analogica y la media de las variables.
int NumMedidas=10; // Cada diez medidas, el programa calculará media.

SControl SC_temp(NumMedidas); //Objeto de la clase SControl, para llevar en este caso el control de temperatura.

void setup(){
   Serial.begin(9600);
   Timer1.initialize(8388480); // maximo valor -> 8388480, equivale a 8 segundos. 
   Timer1.attachInterrupt(interrupcion);
   Serial.println("Sistema de Control de Temperatura.. \n\n ");
}



void loop(){
   if(cerrojo){  // Entrara en el if cada 8 minutos.
     cerrojo=false; // Pongo la varible cerrojo a false, para evitar que en la siguiente iteracion
                    // entrara otra vez en el bucle.
     temp=analogRead(A0); // Leo la temperatura del pin analogico 0.
    
     SC_temp.RellenarMedidas(temp); // Relleno el vector con la medida tomada.
     Serial.print("Temperatura "); // La muestro por puerto serie.
     Serial.println(temp, DEC);    
     if(SC_temp.MedidasCompletas()){ // Con este metodo compruebo si se han tomado todas las medidas que indicamos en el constructor.
                                     // Tambien podriamos realizar la media de las medidas tomadas hasta un instante de tiempo determinado, pero así llevamos un control más preciso.
       MediaTemp=SC_temp.CalcularMedia(); 
       Serial.print("Media de Temperatura ");
       Serial.println(MediaTemp, DEC);
     }    
   }
   // Aqui podriamos ejecutar otro codigo 
}

void interrupcion(){  // La interrupcion se ejecuta cada 8 segundos, pero no pone el cerrojo a true hasta que
                      // se haya ejecutado el numero de veces correspondiente hasta llegar a los 8 minutos.
    cont++;
    if(cont==TiempoInterrupcion){
      cerrojo=true;
      cont=0;
    }
  
}


