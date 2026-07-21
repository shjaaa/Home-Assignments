// Gas & Fire Alert System
// Arduino UNO

const int gasPin = A0;
const int flamePin = 7;

const int greenLED = 10;
const int yellowLED = 11;
const int redLED = 12;

const int buzzer = 9;

unsigned long previousMillis = 0;
unsigned long serialMillis = 0;

bool buzzerState = false;

void setup() {
  pinMode(flamePin, INPUT_PULLUP);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  Serial.println("Gas & Fire Alert System");
  Serial.println("System Ready");
}

void loop() {

  int gasValue = analogRead(gasPin);
  int gasPercent = map(gasValue, 0, 1023, 0, 100);

  // Slide switch:
  // OFF = HIGH = No Flame
  // ON  = LOW  = Flame
  bool flameDetected = !digitalRead(flamePin);

  unsigned long currentMillis = millis();

  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  // GAS + FIRE
  if (gasPercent > 60 && flameDetected) {

    digitalWrite(redLED, HIGH);
    tone(buzzer, 2000);

  }

  // FIRE ONLY
  else if (flameDetected) {

    digitalWrite(redLED, HIGH);

    if (currentMillis - previousMillis >= 250) {
      previousMillis = currentMillis;
      buzzerState = !buzzerState;

      if (buzzerState)
        tone(buzzer, 1800);
      else
        noTone(buzzer);
    }

  }

  // GAS DANGER
  else if (gasPercent > 60) {

    digitalWrite(redLED, HIGH);
    tone(buzzer, 1000);

  }

  // WARNING
  else if (gasPercent >= 30) {

    digitalWrite(yellowLED, HIGH);

    if (currentMillis - previousMillis >= 500) {
      previousMillis = currentMillis;
      buzzerState = !buzzerState;

      if (buzzerState)
        tone(buzzer, 800);
      else
        noTone(buzzer);
    }

  }

  // SAFE
  else {

    digitalWrite(greenLED, HIGH);
    noTone(buzzer);

  }

  // Print every second
  if (currentMillis - serialMillis >= 1000) {

    serialMillis = currentMillis;

    Serial.print("Gas = ");
    Serial.print(gasPercent);
    Serial.print("% | Flame = ");

    if (flameDetected)
      Serial.print("YES");
    else
      Serial.print("NO");

    Serial.print(" | Status = ");

    if (gasPercent > 60 && flameDetected)
      Serial.println("GAS + FIRE DANGER");
    else if (flameDetected)
      Serial.println("FIRE DANGER");
    else if (gasPercent > 60)
      Serial.println("GAS DANGER");
    else if (gasPercent >= 30)
      Serial.println("WARNING");
    else
      Serial.println("SAFE");
  }
}
