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

    String status;

    if (temp > 38 || hum > 80) {

      status = "DANGER";

      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);

      digitalWrite(BUZZER, HIGH);
      delay(1000);
      digitalWrite(BUZZER, LOW);

    }
    else if (temp > 32 || hum > 70) {

      status = "HOT";

      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);

    }
    else if (temp < 25 && hum < 60) {

      status = "COOL";

      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);

    }
    else {

      status = "COMFORT";

      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }

    // OLED Display
    display.clearDisplay();

    display.setTextSize(2);

    display.setCursor(0,0);
    display.print("T:");
    display.print(temp);
    display.print("C");

    display.setCursor(0,25);
    display.print("H:");
    display.print(hum);
    display.print("%");

    display.setTextSize(1);
    display.setCursor(0,55);
    display.print(status);

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
