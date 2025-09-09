#include <SoftwareSerial.h>

SoftwareSerial bluetooth(0, 1);

const int ledVermelho = 2;
const int ledVerde = 3;

char comando;

void setup() {
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  bluetooth.begin(9600);  
  Serial.begin(9600);

  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, LOW);

  Serial.println("Sistema iniciado. Envie R, G ou A via Bluetooth.");
}

void loop() {
  if (bluetooth.available() > 0) {
    comando = bluetooth.read();

    if (comando == '\n' || comando == '\r') return;

    if (comando == 'R') {
      digitalWrite(ledVermelho, HIGH);
      digitalWrite(ledVerde, LOW);
      bluetooth.println("Farol VERMELHO ligado");
    }
    else if (comando == 'G') {
      digitalWrite(ledVermelho, LOW);
      digitalWrite(ledVerde, HIGH);
      bluetooth.println("Farol VERDE ligado");
    }
    else if (comando == 'A') {
      bluetooth.println("Modo automático iniciado");
      while (true) {
        digitalWrite(ledVermelho, HIGH);
        digitalWrite(ledVerde, LOW);
        delay(3000);
        digitalWrite(ledVermelho, LOW);
        digitalWrite(ledVerde, HIGH);
        delay(3000);
        if (bluetooth.available() > 0) {
          comando = bluetooth.read();
          if (comando != '\n' && comando != '\r') break;
        }
      }
    }
  }
}
