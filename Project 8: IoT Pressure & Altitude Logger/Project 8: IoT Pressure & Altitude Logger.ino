#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LEDs
#define GREEN_LED 25
#define RED_LED   26

// Circular buffer
float pressureLog[24];
int logIndex = 0;
bool bufferFilled = false;

// Timers
unsigned long sensorTimer = 0;
unsigned long pageTimer = 0;

bool page = 0;

// Simulated pressure
float pressure = 1013.25;

// Variables
float temperature = 0;
float humidity = 0;

String trend = "STABLE";
String arrow = "->";

void setup() {

  Serial.begin(115200);

  dht.begin();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Wire.begin(21,22);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println("OLED Failed");
    while(true);
  }

  display.clearDisplay();
  display.display();

  randomSeed(analogRead(34));

  for(int i=0;i<24;i++)
    pressureLog[i]=pressure;
}

void loop() {

  // Read every 30 seconds
  if(millis()-sensorTimer>=20000 || sensorTimer==0){

    sensorTimer=millis();

    humidity=dht.readHumidity();
    temperature=dht.readTemperature();

    if(isnan(humidity) || isnan(temperature)){
      humidity=0;
      temperature=0;
    }

    // Simulate pressure
    pressure += random(-20,21)/10.0;

    if(pressure<995) pressure=995;
    if(pressure>1030) pressure=1030;

    pressureLog[logIndex]=pressure;

    logIndex++;

    if(logIndex>=24){
      logIndex=0;
      bufferFilled=true;
    }

    calculateTrend();

    printSerial();
  }

  // Change OLED page every 5 sec
  if(millis()-pageTimer>=5000){

    pageTimer=millis();

    page=!page;
  }

  displayOLED();
}

void calculateTrend() {

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // Number of valid readings collected
  int count = bufferFilled ? 24 : logIndex;

  if (count < 2) {
    trend = "COLLECTING";
    arrow = "...";
    return;
  }

  // Compare the latest reading with the previous one
  int newestIndex = (logIndex - 1 + 24) % 24;
  int previousIndex = (logIndex - 2 + 24) % 24;

  float newest = pressureLog[newestIndex];
  float previous = pressureLog[previousIndex];

  float diff = newest - previous;

  if (diff > 0.2) {
    trend = "RISING";
    arrow = "^";
    digitalWrite(GREEN_LED, HIGH);
  }
  else if (diff < -0.2) {
    trend = "FALLING";
    arrow = "v";
    digitalWrite(RED_LED, HIGH);
  }
  else {
    trend = "STABLE";
    arrow = "->";
    digitalWrite(GREEN_LED, HIGH);
  }
}

void displayOLED(){

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if(page==0){

    display.setCursor(0,0);
    display.println("Pressure Logger");

    display.print("Pressure:");
    display.print(pressure,1);
    display.println(" hPa");

    display.print("Temp:");
    display.print(temperature,1);
    display.println(" C");

    display.print("Humidity:");
    display.print(humidity,0);
    display.println("%");

  }
  else{

    display.setCursor(0,0);
    display.println("Weather Trend");

    display.setTextSize(2);
    display.setCursor(35,20);
    display.println(arrow);

    display.setTextSize(1);
    display.setCursor(20,50);
    display.println(trend);

  }

  display.display();
}

void printSerial(){

  Serial.println("---------------------------------------------");
  Serial.print("Pressure    : ");
  Serial.print(pressure,1);
  Serial.println(" hPa");

  Serial.print("Temperature : ");
  Serial.print(temperature,1);
  Serial.println(" C");

  Serial.print("Humidity    : ");
  Serial.print(humidity,0);
  Serial.println(" %");

  Serial.print("Trend       : ");
  Serial.println(trend);

  Serial.println("---------------------------------------------");
}
