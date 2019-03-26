/*Program to use GATT service on ESP32 to send Battery Level
 * ESP32 works as server - Mobile as client
 * Program by: B.Aswinth Raj
 * Dated on: 13-10-2018
 * Website: www.circuitdigest.com
 */

 
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h> //Library to use BLE as server
#include <BLE2902.h> 

 

bool _BLEClientConnected = false;
const int ledPin = 12;

#define BatteryService BLEUUID((uint16_t)0x180F) 
BLECharacteristic BatteryLevelCharacteristic(BLEUUID((uint16_t)0x2A19), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor BatteryLevelDescriptor(BLEUUID((uint16_t)0x2901));

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      _BLEClientConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      _BLEClientConnected = false;
    }
};

void InitBLE() {
  BLEDevice::init("BLE Battery");
  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pBattery = pServer->createService(BatteryService);

  pBattery->addCharacteristic(&BatteryLevelCharacteristic);
  BatteryLevelDescriptor.setValue("Percentage 0 - 100");
  BatteryLevelCharacteristic.addDescriptor(&BatteryLevelDescriptor);
  BatteryLevelCharacteristic.addDescriptor(new BLE2902());

  pServer->getAdvertising()->addServiceUUID(BatteryService);

  pBattery->start();
  // Start advertising
  pServer->getAdvertising()->start();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Battery Level Indicator - BLE");
  InitBLE();
  pinMode(ledPin, INPUT_PULLUP);
}

  uint8_t level = 57;
  
void loop() {
  uint8_t pinState = 1;
  
  pinState = digitalRead(ledPin);
  if(pinState == 0){
    Serial.println("0");
  }
  
//  digitalWrite(ledPin, ! pinState);
  delay(100);
  BatteryLevelCharacteristic.setValue(&pinState, 1);
  BatteryLevelCharacteristic.notify();

}
