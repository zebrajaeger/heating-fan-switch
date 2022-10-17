#include <Arduino.h>

#define THERMISTOR_PIN 0
#define SWITCH_PIN 1
#define LED_PIN LED_BUILTIN
#define SWITCH_TEMPARATURE_C 25
#define TEMPARATURE_HYSTERESIS 1
#define LOOP_DELAY 1000

bool switchState = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, OUTPUT);
}

float readTemperature() {
  // This code has been modified, but is basically from
  // https://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/
  float R1 = 10000;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
  float Vo = analogRead(THERMISTOR_PIN);
  float R2 = R1 * (1023.0 / (float)Vo - 1.0);
  float logR2 = log(R2);
  float T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  return T - 273.15;
}

void loop() {
  float t = readTemperature();

  // switch on or of, considering the hysteresis
  if (switchState) {
    if (t <= (SWITCH_TEMPARATURE_C - TEMPARATURE_HYSTERESIS)) {
      switchState = false;
      Serial.println("Switch OFF");
    }
  } else {
    if (t >= (SWITCH_TEMPARATURE_C + TEMPARATURE_HYSTERESIS)) {
      switchState = true;
      Serial.println("Switch ON");
    }
  }

  // Debug output: print current temperature
  Serial.print(t);
  Serial.println(" C");

  // control the switch
  digitalWrite(SWITCH_PIN, switchState);

  // Delay and LED control
  if (switchState) {
    digitalWrite(LED_BUILTIN, true);
    delay(LOOP_DELAY * 0.5);
    digitalWrite(LED_BUILTIN, false);
    delay(LOOP_DELAY * 0.5);
  } else {
    digitalWrite(LED_BUILTIN, true);
    delay(LOOP_DELAY * 0.1);
    digitalWrite(LED_BUILTIN, false);
    delay(LOOP_DELAY * 0.9);
  }
}