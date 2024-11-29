#include <Arduino.h>
#include <AvgSender.hpp> 
#include <RunningAvgSender.hpp>
#include <ExpMovAvgSender.hpp>


const int intervalMs = 100;
const int durationSeconds = 3;
const int samples = (durationSeconds * 1000) / intervalMs;


float xRaw[samples], yRaw[samples];
float xFiltered[samples], yFiltered[samples];

//AvgSender* avgSender;
//RunningAvgSender* runningAvgSender;
ExpMovAvgSender* expMovAvgSender;


void setup() {
  Serial.begin(115200);
  //avgSender = new AvgSender(xRaw, yRaw, xFiltered, yFiltered, samples, intervalMs);
  //runningAvgSender = new RunningAvgSender(xRaw, yRaw, xFiltered, yFiltered, samples, intervalMs);
  expMovAvgSender = new ExpMovAvgSender(xRaw, yRaw, xFiltered, yFiltered, samples, intervalMs);
}

void loop() {
  Serial.println("Starting data capture in:");
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);
  Serial.println("Go!");
  expMovAvgSender->fillUpBuffers();
  expMovAvgSender->print();
  while(1);
}