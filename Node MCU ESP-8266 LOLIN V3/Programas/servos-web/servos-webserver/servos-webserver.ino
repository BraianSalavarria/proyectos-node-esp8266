#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "SANTILLAN";
const char* password = "39998882";

ESP8266WebServer server(80);

Servo servoHorizontal;
Servo servoVertical;

// Establecer los ángulos iniciales y límites
int posHorizontal = 90;  // Posición inicial del servo horizontal
int posVertical = 90;    // Posición inicial del servo vertical
const int minAngle = 0;
const int maxAngle = 180;
const int stepSize = 10; // Tamaño de los pasos de movimiento

void setup() {
  Serial.begin(115200);

  // Conectar a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a la red Wi-Fi");

  // Configurar los servos en los pines GPIO
  servoHorizontal.attach(14); // GPIO14 (D5 en algunos modelos)
  servoVertical.attach(12);   // GPIO12 (D6 en algunos modelos)

  // Configurar las rutas de los comandos
  server.on("/izquierda", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    posHorizontal = max(minAngle, posHorizontal - stepSize);
    servoHorizontal.write(posHorizontal);
    server.send(200, "text/plain", "Moviendo Izquierda");
  });

  server.on("/derecha", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    posHorizontal = min(maxAngle, posHorizontal + stepSize);
    servoHorizontal.write(posHorizontal);
    server.send(200, "text/plain", "Moviendo Derecha");
  });

  server.on("/abajo", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    posVertical = max(minAngle, posVertical - stepSize);
    servoVertical.write(posVertical);
    server.send(200, "text/plain", "Moviendo Abajo");
  });

  server.on("/arriba", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*"); // Permitir acceso desde cualquier origen
    posVertical = min(maxAngle, posVertical + stepSize);
    servoVertical.write(posVertical);
    server.send(200, "text/plain", "Moviendo Arriba");
  });

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor iniciado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Mantener el servidor en funcionamiento
  server.handleClient();
}
