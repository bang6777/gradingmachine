// ledPin refers to ESP32 GPIO 26
const int ledPin = 12;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  Serial.begin(115200);
  Serial.println("Battery Level Indicator - BLE");
  pinMode(ledPin, INPUT_PULLUP);
  int pinState = 0;
  pinState = digitalRead(ledPin);
  
}

// the loop function runs over and over again forever
void loop() {
  int pinState = 1;
  pinState = digitalRead(ledPin);
  if(pinState == 0){
    Serial.println("0");
  }
  
//  digitalWrite(ledPin, ! pinState);
  delay(100);              // wait for a second
}
