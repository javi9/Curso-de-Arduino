#include <LiquidCrystal.h>


LiquidCrystal lcd(12,11,5,4,3,2); 
float luz;
float temp;

int  p5=7;
int  p3=9;
int  p4=10;


int zumb=48;
int Tiempo=100;


void setup(){

  pinMode(p5,INPUT);
  pinMode(p3,INPUT);
  pinMode(p4,INPUT);
  
  
  lcd.begin(16,2);
  lcd.print("   Bienvenido");
  lcd.setCursor(0,1);
  lcd.print("Temp->0   LDR->1");
   
}

int modo=0;

void loop(){
  
  if(!digitalRead(p4)==HIGH){
    while(!digitalRead(p4)==HIGH);
    modo=1;
    lcd.begin(16,2);
  }
   
  if(!digitalRead(p3)==HIGH){
    while(!digitalRead(p3)==HIGH);
    modo=2;
    lcd.begin(16,2);
  }
  
  if(!digitalRead(p5)==HIGH){
    while(!digitalRead(p5)==HIGH);
    modo=3;
    lcd.begin(16,2);
  }
 
  if(modo==1){
     lcd.setCursor(0,0);
     lcd.print("Medida LDR");
     lcd.setCursor(0,1);
     luz=analogRead(A0);
     lcd.print(luz/10);
  }
  
  if(modo==2){
     lcd.setCursor(0,0);
     lcd.print("Medida TEMP");
     lcd.setCursor(0,1);
     temp=analogRead(A1);
     lcd.print(temp/10);  
  }
  
  if(modo==3){
    lcd.print("   Bienvenido");
    lcd.setCursor(0,1);
    lcd.print("Temp->0   LDR->1");
  
  }
  
 
}
