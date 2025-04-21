#include <ESP8266WiFi.h>
extern "C" {
#include "user_interface.h"
}

int ratioDepaquetes = 0;
int ch = 0;
int datosCanales[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};

void sniffer(uint8_t *buf, uint16_t len) {
  if (!buf || len < 28) return;
  byte TipoDePaquete = buf[12];
  if (TipoDePaquete == 0xA0 || TipoDePaquete == 0xC0) {
    ++ratioDepaquetes;
  }
  datosCanales[ch] = ratioDepaquetes;
}

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  wifi_set_promiscuous_rx_cb(sniffer);
  wifi_promiscuous_enable(true);
}

void loop() {
  ++ch;
  if(ch == 14){
  ch = 1;
  }
  wifi_set_channel(ch);
  delay(500);
  Serial.print("Canal:");
  Serial.print(ch);
  Serial.print("Paquetes/s:");
  Serial.println(datosCanales[ch]);
  ratioDepaquetes = 0;
  datosCanales[ch] = 0;

}
