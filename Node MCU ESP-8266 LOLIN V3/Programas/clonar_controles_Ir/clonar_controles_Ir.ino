#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t emisorPin = 4; // Pin para enviar señal IR (D2 en NodeMCU)
IRsend irsend(emisorPin);

void setup() {
  Serial.begin(115200);
  irsend.begin();
  Serial.println("Enviando señal IR...");
}

void loop() {
  // Reemplaza con tus datos en bruto para probar
  uint16_t rawData1[] = {1, 2200, 2216, 268, 839, 254, 295, 254, 842, 253, 840, 254, 294, 254, 294, 254, 840, 254, 296, 253, 296, 253, 842, 254, 294, 254, 295, 254, 840, 254, 840, 254, 295, 253, 843, 253, 296, 254, 839, 254, 840, 254, 840, 253, 840, 254, 294, 254, 842, 254, 840, 254, 843, 253, 295, 253, 295, 254, 295, 254, 295, 254, 840, 254, 295, 254, 296, 254, 842, 254, 840, 253, 840, 254, 294, 254, 295, 254, 295, 253, 295, 254, 296, 254, 296, 254, 295, 253, 295, 254, 841, 254, 840, 254, 840, 254, 839, 254, 840, 240};  
  irsend.sendRaw(rawData1, sizeof(rawData1) / sizeof(rawData1[0]), 38);  // Envía a 38 kHz

  uint16_t rawData2[] = {1, 254, 840, 254, 294, 254, 842, 254, 841, 254, 842, 254, 294, 254, 294, 254, 295, 253, 295, 254, 839, 254, 294, 254, 295, 254, 842, 254, 839, 254, 839, 254, 294, 254, 294, 254, 295, 254, 295, 254, 296, 254, 295, 254, 294, 254, 284, 265, 830, 265, 840, 254, 840, 253, 827, 266, 828, 265};  
  irsend.sendRaw(rawData2, sizeof(rawData2) / sizeof(rawData2[0]), 38);  // Envía a 38 kHz

  delay(5000);  // Espera antes de enviar de nuevo
}
