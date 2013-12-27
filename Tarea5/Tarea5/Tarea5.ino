#include <SControl.h>
#include <SPI.h>
#include <Ethernet.h>
#include <WString.h>
#include <TimerOne.h>

//variables globales para la interrupcion

volatile int cont=0;
//Variables para calcular cada cuanto tiempo introducimos las medidas de temperatura en la clase SControl
int Segundos=480; // Variable para indicar cada cuantos segundos quiero que me tome medidas. Los segundos deben ser multiplos de 8 para que sea exacto.
                  // Con segundos=480 tomará medidas cada 8 minutos.
int TiempoInterrupcion=Segundos/8; // El 8 indica cada cuantos segundos se ejecuta la interrupcion.

double MediaTemp=0; // Variables donde guardo la lectura analogica y la media de las variables.
int NumMedidas=100; // El programa como maximo calcula las ultimas 100 medidas.

SControl SC_temp(NumMedidas);


byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1, 50);

double Temp=0,Ldr=0;
//analogico[1]-> temperatura
//analogico[2]-> ldr
int Analogico[]={0,1};


String url= String (100);
EthernetServer server(80);
EthernetClient client;

void setup() {

  Serial.begin(9600);
   
  Timer1.initialize(8388480); // maximo valor -> 8388480, equivale a 8 segundos. 
  Timer1.attachInterrupt(interrupcion);
  Ethernet.begin(mac, ip);
  server.begin();
  
}

 
 
  
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
          
            client.println("<br>");  
            client.println("================================");
            client.println("<br>");  
          
            client.print("Mandar Correo Electronico");
          
            client.print("<form method=get><input type=hidden name=Correo");
            client.println(" value=1><input type=submit value=Correo></form>");
            client.println("</html>");
            
            if(url.lastIndexOf("Correo") > -1){
              Serial.print(Temp/10);
              Serial.println("º");
              Serial.println("MandarCorreo");         
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

