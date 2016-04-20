/* 
 *  Garden water controller with Light and Moisture Sensor.
 *  
 *  The light sensor with 1K resistor
 *  https://learn.adafruit.com/photocells/using-a-photocell
 *  
 *  http://www.seeedstudio.com/wiki/Relay_Shield_V2.0#How_Relay_works
 *  
 *  Digital 4 – controls RELAY4’s COM4 pin (located in J4)
 *  Digital 5 – controls RELAY3’s COM3 pin (located in J3)
 *  Digital 6 – controls RELAY2’s COM2 pin (located in J2)
 *  Digital 7 – controls RELAY1’s COM1 pin (located in J1)
 *  
 */
#include <SoftwareSerial.h>

int ledPin = 12;
bool isDebugEnabled;    // enable or disable debug in this example

int moisturePin = 1;    // Analog Pin 1

int moistureValue;
#define MINMOISTURE 200
 
/**
 * Setup the board
 */
void setup()  {
  isDebugEnabled = true;
  
  pinMode(ledPin, OUTPUT);
  
  // For debugging
  if (isDebugEnabled) { // setup debug serial port
    Serial.begin(115200);         // setup serial with a baud rate of 9600
    Serial.println("setup..");  // print out 'setup..' on start
  }
  
}
 
/**
 * Main loop. This runs forever, well until the batteries run out.
 */
void loop()  {
  sensorsLoop();

  delay(1000);
}

/**
 * Sensors Loop
 */
void sensorsLoop() {
    moistureValue = readMoisture();
    Serial.print("Moisture reading = ");
    Serial.println(moistureValue);
     
    // If the ground is too dry, water it
    if (moistureValue < MINMOISTURE) {
      setLedOn();
    } else {
      setLedOff();
    }

  delay(500);
}

/**
 * Turn the LED ON
 */
 void setLedOn() {
   Serial.print("LED On");
  
   digitalWrite(ledPin, HIGH);  
 }
 
/**
 * Turn the LED OFF
 */
 void setLedOff() {
   Serial.print("LED Off");

   digitalWrite(ledPin, LOW);  
 }

/**
 * Read the value from the analog pin connected to the moisture sensor
 */
int readMoisture() {
  return analogRead(moisturePin);
}

