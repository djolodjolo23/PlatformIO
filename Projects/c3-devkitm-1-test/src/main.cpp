#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int result = myFunction(2, 3);
}

void loop() {
  // print the result to the serial monitor
  Serial.println("Hello World!");
  delay(1000);

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}