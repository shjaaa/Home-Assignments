#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo servo;

// ---------------- Pins ----------------
#define SERVO_PIN   18
#define CW_BUTTON   13
#define CCW_BUTTON  14
#define HOME_BUTTON 27
#define LED_PIN     4

// ---------------- Variables ----------------
int currentAngle = 0;
String direction = "STOP";
long simulatedSteps = 0;

bool lastCW = HIGH;
bool lastCCW = HIGH;
bool lastHOME = HIGH;

void setup() {

  Serial.begin(115200);

  pinMode(CW_BUTTON, INPUT_PULLUP);
  pinMode(CCW_BUTTON, INPUT_PULLUP);
  pinMode(HOME_BUTTON, INPUT_PULLUP);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  servo.attach(SERVO_PIN);
  servo.write(0);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("Stepper");

  display.setCursor(15, 45);
  display.println("Demo");

  display.display();

  delay(2000);

  display.clearDisplay();
}
void loop() {

  // ---------- CW Button ----------
  if (digitalRead(CW_BUTTON) == LOW && lastCW == HIGH) {

    direction = "CW";

    currentAngle += 45;

    if (currentAngle > 180)
      currentAngle = 180;

    servo.write(currentAngle);

    simulatedSteps = currentAngle * 2048L / 180;

    digitalWrite(LED_PIN, HIGH);

    delay(200);

    digitalWrite(LED_PIN, LOW);
  }

  lastCW = digitalRead(CW_BUTTON);

  // ---------- CCW Button ----------
  if (digitalRead(CCW_BUTTON) == LOW && lastCCW == HIGH) {

    direction = "CCW";

    currentAngle -= 45;

    if (currentAngle < 0)
      currentAngle = 0;

    servo.write(currentAngle);

    simulatedSteps = currentAngle * 2048L / 180;

    digitalWrite(LED_PIN, HIGH);

    delay(200);

    digitalWrite(LED_PIN, LOW);
  }

  lastCCW = digitalRead(CCW_BUTTON);

  // ---------- HOME Button ----------
  if (digitalRead(HOME_BUTTON) == LOW && lastHOME == HIGH) {

    direction = "HOME";

    currentAngle = 0;

    simulatedSteps = 0;

    servo.write(0);

    digitalWrite(LED_PIN, HIGH);

    delay(300);

    digitalWrite(LED_PIN, LOW);
  }

  lastHOME = digitalRead(HOME_BUTTON);

  // ---------- OLED ----------
  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("Current: ");
  display.print(currentAngle);
  display.println((char)247);   // degree symbol

  display.setCursor(0, 18);
  display.print("Dir: ");
  display.println(direction);

  display.setCursor(0, 36);
  display.print("Steps: ");
  display.println(simulatedSteps);

  display.display();

  // ---------- Serial Monitor ----------
  Serial.print("Angle: ");
  Serial.print(currentAngle);
  Serial.print("  Direction: ");
  Serial.print(direction);
  Serial.print("  Steps: ");
  Serial.println(simulatedSteps);

  delay(100);
}
