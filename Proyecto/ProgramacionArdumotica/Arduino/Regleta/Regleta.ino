#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//SPI
#define CE_PIN 4
#define CSN_PIN 3
//radio
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);

int confirmacion=0;
int ValorRegleta=1;
int pinRegleta=7;
bool enciende=false;
void setup()   
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  pinMode(pinRegleta,OUTPUT);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop()  
{
  if ( radio.available() )
  {
   
    bool done = false;
    while (!done){
   
      done = radio.read( &ValorRegleta, sizeof(ValorRegleta) );
     // Serial.print("Valor de manta = ");
     // Serial.println(ValorRegleta);
      if(ValorRegleta==1)
        enciende=false;
      else
        enciende=true;
    }
 }
 else
 {   
      if(enciende)       
        digitalWrite(pinRegleta,HIGH);
      else
        digitalWrite(pinRegleta,LOW);  
      
     // Serial.println("No radio disponible");
  }

}
