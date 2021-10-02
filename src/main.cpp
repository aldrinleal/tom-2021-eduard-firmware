#include <Arduino.h>
#include <analogWrite.h>
#include <WiFi.h>

const char* ssid = "motorola one fusion 1789";
const char* password = "4e8c86864633";



/*
#ifdef LEONARDO
#include <stdint-gcc.h>
#endif

#define LED_PIN 13
#define OUTPUT_PIN 3

uint8_t level = 0;

void displayLevel() {
  Serial.print("Level: ");
  Serial.println(level);
}

void setup() {
  Serial.begin(115200);

  while (!Serial);


  pinMode(LED_PIN, OUTPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, 1);
    delay(2000);
    digitalWrite(LED_PIN, 0);
    delay(1000);
  }

  displayLevel();
}

void loop() {
  analogWrite(LED_PIN, level);
  analogWrite(OUTPUT_PIN, level);

  delay(1000);

  while (true) {
    while (Serial.available()) {
      uint8_t ch = Serial.read();

      bool bModified = false;

      switch (ch) {
        case 'd':
        case '+': {
          level += 16;
          bModified = true;
          break;
        }
        case '0': {
          level = 0;
          bModified = true;
          break;
        }
        case 'a':
        case '-': {
          level -= 16;
          bModified = true;
          break;
        }
      }

      if (bModified) {
        displayLevel();
        return;
      }
    }
  }
}
*/