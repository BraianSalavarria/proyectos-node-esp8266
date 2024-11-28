#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

//configuracion de wifi
const char* ssid = "SANTILLAN";
const char* password = "39998882";

//creamos una instancia del servidor
ESP8266WebServer server(80);

//pin de salida a led
const int ledpin = 14;

//funcion para encender led
void ledOn(){
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    digitalWrite(ledpin,HIGH);
    server.send(200,"text/plain","LED Encendido");
  }

void ledOff(){
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    digitalWrite(ledpin,LOW);
    server.send(200,"text/plain","LED Apagado");
  }

//funcion para manejar errores 404
void error(){
    server.send(404,"text/plain","pagina no encontrada");
  }



void setup() {
  Serial.begin(115200);
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin,LOW);

  //nos conectamos al wifi
  WiFi.begin(ssid,password);
  Serial.print("Conectando al Wifi...");
  while (WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }

    Serial.println("Conectado a WIFI");
    Serial.print("Direccion IP:");
    Serial.println(WiFi.localIP());

    //condiguramos las rutas del servidor
    server.on("/encender",ledOn);
    server.on("/apagar",ledOff);
    server.onNotFound(error);

    server.begin(); //iniciamos el servidor
    Serial.println("servidor iniciado");

  
}

void loop() {
  
server.handleClient();
}
