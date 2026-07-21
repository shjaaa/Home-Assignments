#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// ---------------- Pins ----------------
#define RELAY1     26
#define RELAY2     27

#define LED1       25
#define LED2       33

#define BUZZER     32

#define BUTTON1    13

#define BT_LED     2       // Built-in LED

// ---------------- Variables ----------------
bool light1 = false;
bool light2 = false;

bool lastButton1 = HIGH;

unsigned long lastBTCommand = 0;
const unsigned long timeout = 1800000;   // 30 minutes

void beep() {

  digitalWrite(BUZZER, HIGH);
  delay(50);
  digitalWrite(BUZZER, LOW);

}

void sendStatus() {

  SerialBT.print("L1:");
  SerialBT.print(light1 ? "ON" : "OFF");

  SerialBT.print("  L2:");
  SerialBT.println(light2 ? "ON" : "OFF");

}

void setup() {

  Serial.begin(115200);

  // Bluetooth
  SerialBT.begin("IIT_IoT_HomeCtrl");

  Serial.println("Bluetooth Started");

  // Relays
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);

  // LEDs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  // Buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  // Buttons
  pinMode(BUTTON1, INPUT_PULLUP);
  

  // Built-in LED
  pinMode(BT_LED, OUTPUT);
  digitalWrite(BT_LED, LOW);

  lastBTCommand = millis();

}
// ---------------- Update Outputs ----------------
void updateOutputs() {

  // Relay is Active LOW
  digitalWrite(RELAY1, light1 ? LOW : HIGH);
  digitalWrite(RELAY2, light2 ? LOW : HIGH);

  // LEDs indicate light status
  digitalWrite(LED1, light1);
  digitalWrite(LED2, light2);

}

// ---------------- Bluetooth Commands ----------------
void processBluetooth() {

  if (SerialBT.available()) {

    char cmd = SerialBT.read();

    lastBTCommand = millis();

    digitalWrite(BT_LED, HIGH);

    switch(cmd) {

      case '1':
        light1 = true;
        break;

      case '2':
        light1 = false;
        break;

      case '3':
        light2 = true;
        break;

      case '4':
        light2 = false;
        break;

      case '5':
        light1 = true;
        light2 = true;
        break;

      case '6':
        light1 = false;
        light2 = false;
        break;

      case '?':
        sendStatus();
        return;

      default:
        SerialBT.println("Invalid Command");
        return;
    }

    updateOutputs();

    beep();

    sendStatus();

  }

}
// ---------------- Manual Button Control ----------------
void checkButtons() {

  bool b1 = digitalRead(BUTTON1);

  if (lastButton1 == HIGH && b1 == LOW) {

    bool newState = !(light1 && light2);

    light1 = newState;
    light2 = newState;

    updateOutputs();

    beep();

    sendStatus();

    delay(200);   // Debounce

  }

  lastButton1 = b1;
}
void loop() {

  // Bluetooth Commands
  processBluetooth();

  // Manual Buttons
  checkButtons();

  // Auto OFF after 30 minutes
  if (millis() - lastBTCommand >= timeout) {

    light1 = false;
    light2 = false;

    updateOutputs();

  }

  // Bluetooth Indicator LED
  if (SerialBT.hasClient()) {

    digitalWrite(BT_LED, HIGH);

  }
  else {

    digitalWrite(BT_LED, LOW);

  }

}
