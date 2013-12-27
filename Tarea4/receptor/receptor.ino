#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 53
#define CSN_PIN 26

const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN);
int ValorRecibido=1;
int pinLed=7;
bool enciende=false;

void setup(){
  Serial.begin(9600);
  delay(1000);
  pinMode(pinLed,OUTPUT);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop()
{
  if ( radio.available() ) {
     
     bool done = false;
     while (!done){
     	done = radio.read( &ValorRecibido, sizeof(ValorRecibido) );
	
      	if(ValorRecibido==1)
        		enciende=false;
      	else
        		enciende=true;
    }
 }else{   
      
      if(enciende)       
        digitalWrite(pinLed,HIGH);
      else
        digitalWrite(pinLed,LOW);  
   
      Serial.println("No radio disponible");
  }

}

