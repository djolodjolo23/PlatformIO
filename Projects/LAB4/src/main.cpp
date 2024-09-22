/*
 * Arduino nano RP2040 Connect exercise:
 * as BLE Peripheral
 *
 * reference:
 * ArduinoBLE library-
 * https://www.arduino.cc/en/Reference/ArduinoBLE
 *
 * In my implementation:
 * BLEByteCharacteristic written event checked by polling.
 * BLEStringCharacteristic/BLEIntCharacteristic using event haandler.
 *
 */
#include <Arduino.h>
#include <ArduinoBLE.h>
#include <SPI.h>

/*  Visit Online GUID / UUID Generator
 *  (https://www.guidgenerator.com/)
 *  to generate your uuid
 */

const char* serviceUUID =    "9d56cea8-9cec-4575-b85e-7b7ade85fdcd";
const char* byteCharUUID =   "1f09eb27-22bc-4931-b12b-22444e9f03cd";
const char* stringCharUUID = "697bab7f-78c1-4f8b-8787-4c2cf075a37a";
const char* intCharUUID =    "b22f5b00-331b-4acf-9138-7597f617f3ce";

const char* myLocalName = "Djordje's NANO";

BLEService myBLEService(serviceUUID);
BLEByteCharacteristic myBLEByteCharacteristic(byteCharUUID,
                              BLERead|BLEWrite);

BLEStringCharacteristic myBLEStringCharacteristic(stringCharUUID,
                              BLERead|BLEWrite, 10);  //max length = 10

BLEIntCharacteristic myBLEIntCharacteristic(intCharUUID,
                              BLERead|BLEWrite);

void myBLEString_Written_Hndl(BLEDevice central, BLECharacteristic characteristic);
void myBLEInt_Written_Hndl(BLEDevice central, BLECharacteristic characteristic);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);

  //Started, connect Serial to begin
  while(!Serial);

  Serial.println("\n---Start ---");
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("Initialize BLE...");

  if(!BLE.begin()){
    Serial.println("Starting BLE failed!");
    while(1);
  }

  Serial.println("BLE initialized.");
  Serial.print("MAC: ");
  Serial.println(BLE.address());
  Serial.println("Service UUIID: \t\t\t" + String(serviceUUID));
  Serial.println("Byte Characteristic UUIID: \t" + String(byteCharUUID));
  Serial.println("String Characteristic UUIID: \t" + String(stringCharUUID));
  Serial.println("Int Characteristic UUIID: \t" + String(intCharUUID));

  Serial.println();

  BLE.setLocalName(myLocalName);
  BLE.setAdvertisedService(myBLEService);
  myBLEService.addCharacteristic(myBLEByteCharacteristic);
  myBLEService.addCharacteristic(myBLEStringCharacteristic);
  myBLEService.addCharacteristic(myBLEIntCharacteristic);

  BLE.addService(myBLEService);

  myBLEStringCharacteristic.setEventHandler(BLEWritten, myBLEString_Written_Hndl);
  myBLEIntCharacteristic.setEventHandler(BLEWritten, myBLEInt_Written_Hndl);

  BLE.advertise();

}

void loop() {

  BLEDevice central = BLE.central();

  if(central){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Connected: ");
    Serial.println(central.address());
    while(central.connected()){

      if(myBLEByteCharacteristic.written()){
        byte valByte = myBLEByteCharacteristic.value();
        Serial.print("myBLEByteCharacteristic received: ");
        Serial.println(valByte, HEX);
      }
    }

    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Disconnected.");
  }
}

// Event Handler for myBLEStringCharacteristic Written
// Print received Sring, and write back in upper case.
void myBLEString_Written_Hndl(BLEDevice central, BLECharacteristic characteristic) {
  Serial.print("BLEStringCharacteristic event, written: ");

  Serial.println("myBLEStringCharacteristic received: len=" +
                  String(myBLEStringCharacteristic.valueLength()));

  String valString = myBLEStringCharacteristic.value();
  Serial.println(valString);
  valString.toUpperCase();
  Serial.println(valString);

  myBLEStringCharacteristic.setValue(valString);
}
// Event Handler for myBLEIntCharacteristic Written
void myBLEInt_Written_Hndl(BLEDevice central, BLECharacteristic characteristic) {

  Serial.print("BLEIntCharacteristic event, written: ");
  int valInt = myBLEIntCharacteristic.value();
  Serial.println(valInt);

}