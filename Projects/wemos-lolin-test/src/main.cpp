#include <Arduino.h>
#define LED_RED 19
#define LED_YELLOW 21
#define LED_GREEN 18

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop() {
  // put your main code here, to run repeatedly:

  // turn on the red LED
  Serial.println("Red LED ON");
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  // delay 
  delay(1000);
  
  // turn on the yellow LED
  Serial.println("Yellow LED ON");
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, LOW);

  delay(1000);


  // turn on the green LED
  Serial.println("Green LED ON");
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, HIGH);

  delay(1000);
}
