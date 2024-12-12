#include <Arduino.h>

// Pin assignments
//const int irLedPin = 2;      // Pin for the IR LED
const int irReceiverPin = 3; // Pin for the TSOP receiver output
const int greednLedPin = 2;

void setup() {
  // Set the IR LED pin as output
  //pinMode(irLedPin, OUTPUT);

  // Set the IR receiver pin as input
  pinMode(irReceiverPin, INPUT);
  pinMode(greednLedPin, OUTPUT);

  // Start the Serial Monitor
  Serial.begin(9600);
  Serial.println("ESP32 IR Test Started");
}

void loop() {
  // Generate a 38kHz modulated signal on the IR LED
  //tone(irLedPin, 38000); // Start 38kHz signal

  // Read the TSOP receiver
  int receiverState = digitalRead(irReceiverPin);
  Serial.print("IR Receiver Output: ");
  Serial.println(receiverState);
  if (receiverState == HIGH) {
    digitalWrite(greednLedPin, LOW);
  } else {
    digitalWrite(greednLedPin, HIGH);
  }

  delay(100); // Wait for 1 second

  // Stop the IR signal
  //noTone(irLedPin);
}
