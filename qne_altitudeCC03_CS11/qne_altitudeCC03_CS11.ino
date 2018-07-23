#include <xCore.h>  //add core library
#include <xSW01.h>  //add weather sensor library
#include <xOD01.h>  //add OLED screen library

#if defined(ESP8266)
#define RED   RED
#define GREEN GREEN
#define BLUE  BLUE
#include <ESP8266WiFi.h>
#define Serial Serial

#elif defined(ARDUINO_SAMD_ZERO)
#define RED   CC03_RED
#define GREEN CC03_GREEN
#define BLUE  CC03_BLUE
#define Serial SerialUSB

#elif defined(ARDUINO_AVR_PRO)
#define RED   CC01_RED
#define GREEN CC01_GREEN
#define BLUE  CC01_BLUE
#define Serial Serial

#elif defined(ESP32)
#define RED   CW02_RED
#define GREEN CW02_GREEN
#define BLUE  CW02_BLUE
#define Serial Serial
#endif

xSW01 SW01;

const int DelayTime = 500; //Defining set delay time that could be used elsewhere in the code

//Create a variable to store the data read from SW01
float altitude;
float QNE;

void setup() {

  #if defined(ESP8266)
  WiFi.forceSleepBegin();
  Wire.begin(2, 14);
  Wire.setClockStretchLimit(15000);

#elif defined(ARDUINO_SAMD_ZERO)
  Wire.begin();

#elif defined(ARDUINO_AVR_PRO)
  Wire.begin();

#elif defined(ESP32)
  Wire.begin();

#endif

  //Initialise variable to zero
  altitude = 0;
  QNE = 0;

  //Start I2C Communication
  Wire.begin();
  
  //Start OLED screen
  OLED.begin();

  //Start I2C communication
  Wire.begin();

  pinMode(CC01_RED, OUTPUT);

  //Start SW01 Sensor
  if (!SW01.begin()) {
    OD01.println("SW01 Sensor not found");
    OD01.println("Check your connector");
    while (1) {
      digitalWrite(CC01_RED, OUTPUT);
    }
  }

  //String intro for project
  OD01.println("Altitude Experiment");
  OD01.println("____________________________");

  delay(5000);

  //Delay for sensor to normalise
  delay(3000);

  //Send command to clear screen
  OD01.clear();

  delay (DelayTime);

}

void loop() {

  //Read and calculate data from SW01
  SW01.poll();

  //Request to get QNE data then store in the variable
  QNE = SW01.getQNE();

  //Request to get Altitude data then input the variable in Pascals(Google value of pressure in your area)
  altitude = SW01.getAltitude(100700);


  //Display recorded data over the Serial Monitor

  OD01.print("Altitude:");
  OD01.print(altitude);
  OD01.println("m ");

  OD01.print("QNE:");
  OD01.print(QNE);
  OD01.println("m");

  delay(5000);

}
