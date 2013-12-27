#include <SControl.h>
#include <SPI.h>
#include <Ethernet.h>
#include <WString.h>
#include <TimerOne.h>


//Comunicacion Radio
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 53
#define CSN_PIN 26
//Canal de comunicacion por radio
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);

//interrupcion
volatile int cont=0;
int Segundos=80; // Variable para indicar cada cuantos segundos quiero que me tome medidas. Los segundos deben ser multiplos de 8 para que sea exacto.
                  // Con segundos=480 tomará medidas cada 8 minutos.
int TiempoInterrupcion=Segundos/8; // El 8 indica cada cuantos segundos se ejecuta la interrupcion.

double MediaTemp=0; // Variables donde guardo la lectura analogica y la media de las variables.
int NumMedidas=100; // Cada diez medidas, el programa calculará media.
int Regleta=0, pin30=30;// variable con la que controlo el estado de la regleta

// Estructura de datos con la que controlo las mediciones.
SControl SC_temp(NumMedidas);


byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1, 50);
double Temp=0,Ldr=0;
int Analogico[]={0,1};
String url= String (100);
EthernetServer server(80);

void setup() {
  
  Serial.begin(9600);
  pinMode(pin30,OUTPUT);
 //interrupcion para medida de valores
  Timer1.initialize(8388480); // maximo valor -> 8388480, equivale a 8 segundos.  
  Timer1.attachInterrupt(interrupcion);
  //ethernet
  Ethernet.begin(mac, ip);
  server.begin();
  
  //Radio
  radio.begin();
  radio.openWritingPipe(pipe);
   
}

  EthernetClient client,cliente;
  byte server_[] = { 10, 0, 0, 5 }; 
  void loop() {
    url="";  
   client = server.available();
   if (client) {
    while (client.connected()) {
      if (client.available()) {
               
          char c = client.read();
          url=url+c;
        
          if (c == '\n' ) {
          
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<meta http-equiv=\"refresh\" content=\"15\">");
            client.println("<title>index.htm</title>");
            client.println("<span bold="" font-weight:="">");
            client.println("<br>");  
            client.println("SERVIDOR WEB BARRIADA LA PAZ NUMERO 5</span>");
            client.println("<br>");  
            client.println("================================");
            client.println("<br>");  
            client.println("Autor:   Javi9rl");
            client.println("<br>");  
            client.println("Fecha:   06/12/2013");
            client.println("<br>");
            client.println("<br>");  
            client.println("================================");
            client.println("<br>");
            client.println("<br>");
          
            Temp=analogRead(Analogico[0]);
            Ldr=analogRead(Analogico[1]);
          
            client.print("Temperatura del salon en grados ---> ");
            client.print(Temp/10);
            client.println("<br>");  
            client.print("Sensor de Luminosidad ---> ");
            client.print(Ldr/10);
            client.println("<br>");
            client.println("<br>");
      
            client.print("<form method=get><input type=hidden name=CalcularMediaTemp");
            client.println(" value=1><input type=submit value=CalcularMediaTemp></form>");
            client.println("</html>");
          
            if(url.lastIndexOf("CalcularMediaTemp") > -1){
             MediaTemp=SC_temp.CalcularMedia();
             client.print("<p>");
             client.print("  La media de temperatura en este instante es ---> ");
             client.print(MediaTemp);
             client.print("</p>");
            }
          
            client.print("<form method=get><input type=hidden name=NoMostrar");
            client.println(" value=0><input type=submit value=NoMostrar></form>");
            client.println("</html>");
          
            if(url.lastIndexOf("dig") > -1){
             Regleta=nivelElegido(url);
             digitalWrite(pin30,Regleta);// Conecto un led para saber desde el servidor si la regleta esta encendida o apagada.
             radio.write(&Regleta, sizeof(Regleta) );
            }
            client.println("<br>");  
            client.println("================================");
            client.println("<br>");  
          
            client.print("Encender Regleta ");
            if(Regleta==1){
                client.println("<font color='green'>ON</font>");
                client.print("<form method=get><input type=hidden name=dig");
                client.print(" value=0><input type=submit value=OFF></form>");
            }
            if(Regleta==0){
                client.println("<font color='grey'>OFF</font>");
                client.print("<form method=get>");
                client.print("<input type=hidden name=dig");
                client.print(" value=1>");
                client.print("<input type=submit value=ON>");
                client.print("</form>");  
            }
          
            break;
          
         }
        }
      }
      delay(1);
      client.stop();
     
   }
}

// FUNCIONES

void interrupcion(){  
    cont++;
    if(cont==TiempoInterrupcion){
      SC_temp.RellenarMedidas(Temp/10); // Relleno el vector con la medida tomada.
      cont=0;
    }            
}

int nivelElegido(String cad)
{
  int pos_igual =  cad.lastIndexOf("=");
  char v = cad.charAt(pos_igual+1) - 48;
  if (v == 0) return 0;
  if (v == 1) return 1;
}
  
