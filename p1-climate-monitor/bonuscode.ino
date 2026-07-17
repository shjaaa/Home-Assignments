#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- DHT11 ----------------
DHTesp dht;

// ---------------- Pins ----------------
#define DHT_PIN 4

#define RED_LED 25
#define GREEN_LED 26
#define BUZZER 27

unsigned long lastSensorRead = 0;
unsigned long lastSerialPrint = 0;

float maxTemp = -100;
float minTemp = 100;

unsigned long screenTimer = 0;
int currentScreen = 0;

void setup() {

  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER, LOW);

  dht.setup(DHT_PIN, DHTesp::DHT11);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 20);
  display.println("Climate Monitor");
  display.display();

  delay(2000);
}

void loop() {

  if (millis() - lastSensorRead >= 2000) {

    lastSensorRead = millis();

    TempAndHumidity data = dht.getTempAndHumidity();

    float temp = data.temperature;
    float hum = data.humidity;

    if (temp > maxTemp)
      maxTemp = temp;

    if (temp < minTemp)
        minTemp = temp;
    if (isnan(temp) || isnan(hum)) {
      Serial.println("Failed to read DHT11!");
      return;
}

    String status;
    // ---------- STATUS LOGIC ----------
    if (temp >= 36.8|| hum > 80) {

    status = "DANGER";
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);


}
else if (temp >= 36|| hum > 70) {

    status = "HOT";
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, LOW);

}
else if (temp >= 35.6) {

    status = "COMFORT";
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, LOW);

}
else if(temp<=35.6) {

    status = "COOL";
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, LOW);


}
  if (millis() - screenTimer >= 5000) {

  screenTimer = millis();

  currentScreen++;

  if (currentScreen > 2)
    currentScreen = 0;
}

    display.clearDisplay();

if (currentScreen == 0) {

  display.setTextSize(2);

  display.setCursor(0,0);
  display.print("T:");
  display.print(temp,1);
  display.print("C");

  display.setCursor(0,22);
  display.print("H:");
  display.print(hum,0);
  display.print("%");

  display.setTextSize(1);
  display.setCursor(0,52);
  display.print("Status: ");
  display.print(status);

}

else if (currentScreen == 1) {

  display.setTextSize(2);

  display.setCursor(10,15);
  display.println("Climate");

  display.setCursor(10,40);
  display.println("Monitor");

}

else {

  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("Daily Max");

  display.setTextSize(2);
  display.print(maxTemp,1);
  display.println(" C");

  display.setTextSize(1);
  display.println();

  display.println("Daily Min");

  display.setTextSize(2);
  display.print(minTemp,1);
  display.println(" C");

}

display.display();
  


    // CSV Serial Output every 5 sec
    if (millis() - lastSerialPrint >= 5000) {

      lastSerialPrint = millis();

      Serial.print(millis());
      Serial.print(",");

      Serial.print(temp);
      Serial.print(",");

      Serial.print(hum);
      Serial.print(",");

      Serial.println(status);
    }
  }
}
