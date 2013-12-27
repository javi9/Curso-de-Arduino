#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 4
#define CSN_PIN 3

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

RF24 radio(CE_PIN, CSN_PIN); 

int Valor0=0;
int Valor1=1;
int p1=20;
int p2 =21;

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  pinMode(p1,INPUT);
  pinMode(p2,INPUT);
}

void loop(){

  if(digitalRead(p1)==HIGH)
  	radio.write( &Valor1, sizeof(Valor1) );
   else if (digitalRead(p2)==HIGH)
		radio.write(&Valor0,sizeof(Valor0));
}

