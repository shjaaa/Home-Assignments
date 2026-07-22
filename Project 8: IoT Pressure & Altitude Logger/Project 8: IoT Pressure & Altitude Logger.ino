#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);


// BMP180 Sensor
Adafruit_BMP085 bmp;


// Pins
#define POT_PIN 34

#define GREEN_LED 25
#define RED_LED 26


// Variables

float pressureLog[24];

int logIndex = 0;

float pressure;
float temperature;
float altitude;

String trend = "STABLE";


unsigned long lastSensorRead = 0;
unsigned long lastDisplayChange = 0;


int screen = 0;



void setup() {

  Serial.begin(115200);


  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);


  Wire.begin(21,22);


  // BMP180 Start

  if(!bmp.begin())
  {
    Serial.println("BMP180 not detected!");
    while(1);
  }


  // OLED Start

  if(!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C))
  {
    Serial.println("OLED not detected!");
    while(1);
  }


  display.clearDisplay();
  display.setTextColor(WHITE);


  for(int i=0;i<24;i++)
  {
    pressureLog[i]=0;
  }


  Serial.println("IoT Pressure Logger Started");

}



void loop() {


  // Read sensors every 30 seconds

  if(millis()-lastSensorRead > 30000)
  {

    readSensors();

    calculateTrend();

    printSerial();


    lastSensorRead = millis();

  }



  // Change OLED page every 5 seconds

  if(millis()-lastDisplayChange > 5000)
  {

    screen++;

    if(screen>1)
      screen=0;


    showOLED();


    lastDisplayChange = millis();

  }

}



// ---------------- SENSOR READING ----------------


void readSensors()
{

  temperature = bmp.readTemperature();


  pressure = bmp.readPressure()/100.0F;


  // Potentiometer altitude

  int potValue = analogRead(POT_PIN);


  float setAltitude =
  map(potValue,0,4095,0,2000);



  altitude = bmp.readAltitude(1013.25);



  pressureLog[logIndex % 24] = pressure;


  logIndex++;


}



// ---------------- TREND CALCULATION ----------------


void calculateTrend()
{

  int oldestIndex;


  if(logIndex >= 24)
    oldestIndex = logIndex % 24;

  else
    oldestIndex = 0;



  float difference =
  pressure - pressureLog[oldestIndex];



  if(difference > 0.5)
  {

    trend="RISING";

    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(RED_LED,LOW);

  }


  else if(difference < -0.5)
  {

    trend="FALLING";

    digitalWrite(RED_LED,HIGH);
    digitalWrite(GREEN_LED,LOW);

  }


  else
  {

    trend="STABLE";

    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(RED_LED,HIGH);

  }


}



// ---------------- OLED DISPLAY ----------------


void showOLED()
{

  display.clearDisplay();

  display.setTextSize(1);


  if(screen==0)
  {

    display.setCursor(0,0);

    display.println("Pressure Logger");


    display.print("Pressure: ");
    display.print(pressure);
    display.println(" hPa");


    display.print("Temp: ");
    display.print(temperature);
    display.println(" C");


    display.print("Altitude: ");
    display.print(altitude);
    display.println(" m");


  }


  else
  {

    display.setCursor(0,0);


    display.println("Weather Trend");


    display.setTextSize(2);


    display.println(trend);



    if(trend=="RISING")
      display.println("^");


    else if(trend=="FALLING")
      display.println("v");


    else
      display.println(">");


  }


  display.display();


}



// ---------------- SERIAL MONITOR ----------------


void printSerial()
{

  Serial.println("----------------------");


  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");


  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");


  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");


  Serial.print("Trend: ");
  Serial.println(trend);


  Serial.println("----------------------");

}
