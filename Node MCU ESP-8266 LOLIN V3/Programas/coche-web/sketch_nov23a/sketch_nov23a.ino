#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//configuracion wifi
const char* ssid = "SANTILLAN";
const char* password = "39998882";
ESP8266WebServer server(80);

//configuracion L298N
int IN1 = 5;
int IN2 = 4;
int IN3 = 14;
int IN4 = 12;
int luz = 15;

int velocidad = 512;
int vel_giro = 256;
//de 60 ya los motores no se mueven, desde 70 ya si
#define ENA 0
#define ENB 13


void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(luz,OUTPUT);
  
  Serial.begin(115200);

  // Conectar a la red Wi-Fi  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a la red Wi-Fi");

    

  // Configurar las rutas de los comandos
  server.on("/izquierda", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    izquierda();
    server.send(200, "text/plain", "Moviendo Izquierda");
  });

  server.on("/derecha", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    derecha();
    server.send(200, "text/plain", "Moviendo Derecha");
  });

  server.on("/abajo", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
     atras();
    server.send(200, "text/plain", "Moviendo Abajo");
  });

  server.on("/arriba", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    adelante();
    server.send(200, "text/plain", "Moviendo Arriba");
  });

    server.on("/parar", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    parar();
    server.send(200, "text/plain", "Moviendo Arriba");
  });

    server.on("/encender", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    encender();
    server.send(200, "text/plain", "encender luz");
  });

   server.on("/apagar", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    apagar();
    server.send(200, "text/plain", "apagar luza");
  });
  

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor iniciado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

  void atras(){
      digitalWrite(IN1,HIGH);    
      digitalWrite(IN2,LOW); 
      analogWrite(ENA, velocidad); // PWM: 50% de velocidad (rango 0-1023)    

      digitalWrite(IN3,HIGH);    
      digitalWrite(IN4,LOW);     
      analogWrite(ENB, velocidad);
   }

   void adelante(){
      digitalWrite(IN1,LOW);    
      digitalWrite(IN2,HIGH);
      analogWrite(ENA, velocidad);     

      digitalWrite(IN3,LOW);    
      digitalWrite(IN4,HIGH); 
      analogWrite(ENB, velocidad);    
   }

   void izquierda(){
    
     digitalWrite(IN1,LOW);    
     digitalWrite(IN2,HIGH);     
     analogWrite(ENA,vel_giro);

      digitalWrite(IN3,HIGH);    
      digitalWrite(IN4,LOW);
      analogWrite(ENB, vel_giro);
    }
    void derecha(){
     
     digitalWrite(IN1,HIGH);    
     digitalWrite(IN2,LOW);     
     analogWrite(ENA,vel_giro);

      digitalWrite(IN3,LOW);    
      digitalWrite(IN4,HIGH);
      analogWrite(ENB, vel_giro);
    }

    void parar(){
       analogWrite(ENA, 0);
       analogWrite(ENB, 0);
   }

   void encender(){
     digitalWrite(luz,HIGH); 
    }
  void apagar(){
     digitalWrite(luz,LOW); 
    }
   
    

void loop() {
  // Mantener el servidor en funcionamiento
  server.handleClient();
  delay(15);
}
