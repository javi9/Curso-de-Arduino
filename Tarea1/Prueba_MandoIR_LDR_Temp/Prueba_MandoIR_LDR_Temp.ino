#include <IRremote.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(12,11,5,4,3,2);   
float luz;
float temp;
int RECV_PIN=7;
IRrecv irrecv(RECV_PIN);
decode_results results;
int zumb=48;
int Tiempo=100;
int lectura=0;

void setup(){
  pinMode(zumb,OUTPUT);
  lcd.begin(16,2);
  lcd.print("   Bienvenido");
  lcd.setCursor(0,1);
  lcd.print("Temp->0   LDR->1");
  Serial.begin(9600);
  irrecv.enableIRIn();
 
}

void loop(){
  if(lectura==12495){
    luz=analogRead(A0);
    lcd.setCursor(0,1);
    lcd.print(luz/10);
  }
  if(lectura==26775){
     lcd.setCursor(0,1);
     lcd.print(temp/10);
     temp=analogRead(A1);
  }
  
  if(irrecv.decode(&results)){
    digitalWrite(zumb,HIGH);
    delay(Tiempo);
    digitalWrite(zumb,LOW);
 
    lectura=results.value;
    Serial.println(lectura,DEC);
     
    if(lectura==12495){
     lcd.begin(16,2);
     lcd.setCursor(0,0);
     lcd.print("Medida LDR");
    
    }
    if(lectura==26775){
      lcd.begin(16,2);
      lcd.setCursor(0,0);
      lcd.print("Medida Temp");
      
    }
    if(lectura !=12495 && lectura !=26775){
      lcd.display();
      lcd.setCursor(0,0);
      lcd.print("   Bienvenido");
      lcd.setCursor(0,1);
      lcd.print("Temp->0   LDR->1");
    }
    irrecv.resume(); 
  }
   delay(200);
}
