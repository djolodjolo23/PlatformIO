#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);
}

void loop() {
  int result = myFunction(2, 3);
  Serial.println(result);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}