#include <IRremote.h>
#include <LiquidCrystal.h>
#include <SD.h>

LiquidCrystal lcd(12,11,5,4,3,2);   // Pines de conexion de la pantalla LCD 
float luz;                          // variable donde almaceno el valor del sensor LDR
float temp;                         // variable donde almaceno el valor de la resistenca nfc

// Pin donde conecto Receptor de códigos IR
int RECV_PIN=7;                      
IRrecv irrecv(RECV_PIN);
decode_results results;

// Pin donde conecto el Zumbador
int zumb=48;

int Tiempo=100;                    // Tiempo en el que suena el zumbador
int lectura=0;                     // variable que utilizo para leer el codigo que recibe el receptor IR
bool  dos=false;                   // booleano para controlar el menu. Con ella pretendo que no se acceda a crear y editar ficheros sin antes inicializar la tarjetaSD
bool  SDini=true;
void setup(){
 
  pinMode(zumb,OUTPUT);            // zumbador de salida
  lcd.begin(16,2);                 // Inicializo la pantalla
  // MENU
  lcd.print("   Bienvenidos");

  delay(3500);
  lcd.begin(16,2);
  lcd.print("1 Medidas");      
  lcd.setCursor(0,1);
  lcd.print("2 Grabar en SD");
  
  // Inicializo puerto serie para poder ver por la consola del ordenador.
  // Lo utilice para saber el código asociado a cada boton del mando.
  Serial.begin(9600);
  
  irrecv.enableIRIn();
 
}

void loop(){
  
  if(lectura==12495){            // Si pulso boton 1, me muestra el valor del sensor LDR y el valor del sensor NFC
    luz=analogRead(A0);          // Esta parte la saco fuera del "switch case" para que me actualice los valores en tiempo real.
    temp=analogRead(A1);
    lcd.setCursor(6,0);
    lcd.print(luz/10);
    lcd.setCursor(6,1);
    lcd.print(temp/10);
  }
  
  if(irrecv.decode(&results)){  // Cada vez que pulso un boton entra en la función, y el zumbador se pone en alta durante un determinado tiempo.
   
   lectura=results.value; // Lectura pasa a valer el codigo asociado al boton pulsado.
   
   if(lectura!=-1){  // No es muy eficiente, pero bueno, no se me ocurre forma de obviar el -1 que aparece de vez en cuando en el receptorIR 
    digitalWrite(zumb,HIGH);    
    delay(Tiempo);
    digitalWrite(zumb,LOW);
   }
    
    
    switch(lectura){
      case 12495:  // Codigo asociado al boton 1
          lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("LDR");
          lcd.setCursor(0,1);
          lcd.print("NFC");
        break;
        
      case 6375: // Codigo asociado al boton 2
          if(!SD.begin(53) && SDini){ 
             Serial.println("Error inicializando SD");
             lcd.begin(16,2);
             lcd.setCursor(0,0);
             lcd.print("Error en SD");  
          }else{
             Serial.println("SD inicializada");
             lcd.begin(16,2);
             lcd.setCursor(0,0);
             lcd.print("SD inicializada");
             delay(2000);
             lcd.begin(16,2);
             lcd.setCursor(0,0);
             lcd.print("3 AlmacenarLDR");
             lcd.setCursor(0,1);
             lcd.print("4 AlmacenarNFC");
             SDini=false;
             dos=true;
          }
          break;
     
       case 31365: // Codigo asociado al boton 3
        if(dos){
         //almaceno LDR en un fichero
            File myFile;
            Serial.println("\nCreando fichero LDR.txt...");
            myFile = SD.open("LDR.txt", FILE_WRITE);
            if (myFile) {
               Serial.print("Escribiendo en LDR.txt...");        
               myFile.print("Medida LDR ");
               myFile.print(luz/10);
              
               Serial.println("Escritura hecha, y fichero cerrado.");
               lcd.begin(16,2);
               lcd.println("Escritura hecha");
               lcd.setCursor(0,1);
               lcd.println("Fichero Creado");
            }else {
              Serial.println("Error al crear y el abrir fichero.txt");
              lcd.begin(16,2);
              lcd.println(" Error creacion ");
              lcd.setCursor(0,1); 
              lcd.println(" fichero LDR.txt");
            }
             myFile.close();  
            dos=false;
         }
         break;
      case 4335: //  Codigo asociado al boton 4
         if(dos){
         //almaceno NFC en un fichero
            File myFile;
            Serial.println("\nCreando fichero NFC.txt...");
            myFile = SD.open("NFC.txt", FILE_WRITE);
            if (myFile) {
               Serial.print("Escribiendo en NFC.txt...");        
               myFile.print("Medida NFC ");
               myFile.print(temp/10);
             
               Serial.println("Escritura hecha, y fichero cerrado.");
               lcd.begin(16,2);
               lcd.println("Escritura hecha");
               lcd.setCursor(0,1);
               lcd.println("Fichero Creado");
            }else {
              Serial.println("Error al crear y el abrir fichero.txt");
              lcd.begin(16,2);
              lcd.println(" Error creacion ");
              lcd.setCursor(0,1); 
              lcd.println(" fichero NFC.txt");
            } 
            myFile.close(); 
            dos=false;          
         }
         break;  
        
      case -1: // Muchas veces el receptor lee -1 sin que pulsemos boton, este case lo hago para que cuando aparezca, no haga nada.
        break;
      
      default : // Para cualquier boton del mando, exceptuando los mencionados, saltaría al menu de inicio.
           lcd.begin(16,2);
           lcd.print("1 Medidas");      
           lcd.setCursor(0,1);
           lcd.print("2 Grabar en SD");
           dos=false;
           break;
    } 
    irrecv.resume(); 
  }
   delay(200);
}
