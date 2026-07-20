#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- Ultrasonic ----------------
#define TRIG_PIN 5
#define ECHO_PIN 18

// ---------------- LEDs ----------------
#define BLUE_LED 26
#define YELLOW_LED 25
#define RED_LED 33

// ---------------- Buzzer ----------------
#define BUZZER 27

// ---------------- Variables ----------------
unsigned long lastBeep = 0;
unsigned long lastSerial = 0;

float distance = 0;
String zone = "SAFE";

int beepInterval = 0;
bool buzzerState = false;

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  // OLED
  Wire.begin(21,22);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
  {
    Serial.println("OLED Failed");
    while(true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(8,18);
  display.println("Parking");

  display.setCursor(15,42);
  display.println("Assist");

  display.display();

  delay(2000);
}
// ---------- Measure Distance ----------
float measureDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
    return 400;

  return duration * 0.0343 / 2.0;
}

// ---------- Average of 5 Readings ----------
float getAverageDistance() {

  float sum = 0;

  for (int i = 0; i < 5; i++) {

    sum += measureDistance();
    delay(10);      // Small delay only between measurements

  }

  return sum / 5.0;
}

// ---------- Parking Zone ----------
void updateParkingStatus() {

  if (distance > 60) {

    zone = "SAFE";

    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);

    digitalWrite(BUZZER, LOW);
    beepInterval = 0;
  }

  else if (distance > 30) {

    zone = "CAUTION";

    digitalWrite(BLUE_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    beepInterval = 800;
  }

  else if (distance > 15) {

    zone = "CLOSE";

    digitalWrite(BLUE_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, HIGH);

    beepInterval = 300;
  }

  else {

    zone = "DANGER";

    digitalWrite(BLUE_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    digitalWrite(BUZZER, HIGH);
    beepInterval = -1;
  }

  // Non-blocking buzzer
  if (beepInterval > 0) {

    if (millis() - lastBeep >= (unsigned long)beepInterval) {

      lastBeep = millis();

      buzzerState = !buzzerState;
      digitalWrite(BUZZER, buzzerState);

    }

  }

  else if (beepInterval == 0) {

    digitalWrite(BUZZER, LOW);

  }

}
void loop() {

  // Get average distance
  distance = getAverageDistance();

  // Update LEDs & buzzer
  updateParkingStatus();

  // ---------------- OLED ----------------
  display.clearDisplay();

  // Distance
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(distance, 1);
  display.print(" cm");

  // Zone
  display.setTextSize(2);
  display.setCursor(0, 24);
  display.print(zone);

  // Proximity Bar
  display.drawRect(0, 52, 128, 10, SSD1306_WHITE);

  int barLength = map((int)constrain(distance, 0, 100), 100, 0, 0, 126);

  display.fillRect(1, 53, barLength, 8, SSD1306_WHITE);

  display.display();

  // ---------------- Serial Monitor ----------------
  if (millis() - lastSerial >= 500) {

    lastSerial = millis();

    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.print(" cm");

    Serial.print("   Zone: ");
    Serial.println(zone);

  }

}
