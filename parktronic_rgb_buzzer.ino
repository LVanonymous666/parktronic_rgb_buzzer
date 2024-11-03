#include <NanitLib.h>

#define TRIGGER P5_1
#define ECHO P5_4
#define RED_LED P4_4
#define GREEN_LED P4_3
#define BUZZER P4_2

void setup() {
  Nanit_Base_Start();
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop(){
  int distance = measureDistance();
  Serial.println(distance);
  if (distance >= 50) {
    changeLeds(0, 0);
    noTone(BUZZER);
  } else if (distance <= 10) {
    changeLeds(1, 0);
    tone(BUZZER, 880);
  } else {
    changeLeds(0, 1);
    tone(BUZZER, 880);
    delay(distance * 5);
    changeLeds(0, 0);
    noTone(BUZZER);
  }
  delay(100);
}

int measureDistance(){
  digitalWrite(TRIGGER, 1);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, 0);

  return pulseIn(ECHO, 1) / 58;
}

void changeLeds(bool redLedValue, bool greenLedValue){
  digitalWrite(RED_LED, redLedValue);
  digitalWrite(GREEN_LED, greenLedValue);
}