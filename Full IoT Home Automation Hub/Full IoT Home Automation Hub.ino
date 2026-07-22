#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "J/20073-2.4G";
const char* password = "qwerty12";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "ece/shobhit/homeautomation2026";

WebServer server(80);

// ---------------- DHT ----------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---------------- Pins ----------------
#define LDR_PIN 34

#define RELAY_LIGHT 27
#define RELAY_FAN   26

#define WHITE_LED   18
#define YELLOW_LED  19
#define RED_LED     23

#define BUZZER 25

#define GAS_BUTTON    13
#define MOTION_BUTTON 14

// ---------------- Variables ----------------
float temperature = 0;
float humidity = 0;

int lightValue = 0;

bool lightState = false;
bool fanState = false;

bool gasDetected = false;
bool motionDetected = false;

// ---------------- HTML Page ----------------
String webpage() {

String html="<!DOCTYPE html><html>";

html+="<head>";

html+="<meta http-equiv='refresh' content='2'>";

html+="<title>ESP32 Home Automation Hub</title>";

html+="<style>";

html+="body{font-family:Arial;background:#ECECEC;text-align:center;}";

html+="table{margin:auto;border-collapse:collapse;}";

html+="th,td{padding:12px;border:1px solid black;font-size:20px;}";

html+="th{background:#0077B6;color:white;}";

html+="h2{color:#023E8A;}";

html+="</style>";

html+="</head>";

html+="<body>";

html+="<h2>ESP32 Home Automation Hub</h2>";

html+="<table>";

html+="<tr><th>Parameter</th><th>Status</th></tr>";

html+="<tr><td>Temperature</td><td>";
html+=String(temperature,1);
html+=" C</td></tr>";

html+="<tr><td>Humidity</td><td>";
html+=String(humidity,0);
html+=" %</td></tr>";

html+="<tr><td>LDR</td><td>";
html+=String(lightValue);
html+="</td></tr>";

html+="<tr><td>Light</td><td>";
html+=(lightState?"ON":"OFF");
html+="</td></tr>";

html+="<tr><td>Fan</td><td>";
html+=(fanState?"ON":"OFF");
html+="</td></tr>";

html+="<tr><td>Gas</td><td>";
html+=(gasDetected?"ALERT":"SAFE");
html+="</td></tr>";

html+="<tr><td>Motion</td><td>";
html+=(motionDetected?"YES":"NO");
html+="</td></tr>";

html+="</table>";

html+="<br>";

html+="<h3>Summer Training Project</h3>";

html+="</body></html>";

return html;

}
void connectMQTT() {

  while (!mqttClient.connected()) {

    Serial.print("Connecting to MQTT...");

    String clientId = "ESP32HomeHub-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str())) {

      Serial.println("Connected");

    } else {

      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retry in 5 sec");

      delay(5000);
    }
  }
}
void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("ESP32 Home Automation Hub");
  Serial.println("--------------------------");


  // ---------------- DHT ----------------
  dht.begin();

  // ---------------- I2C OLED ----------------
  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed!");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(18, 18);
  display.println("HOME");
  display.setCursor(25, 42);
  display.println("HUB");
  display.display();

  delay(2000);

  display.clearDisplay();

  // ---------------- Pin Modes ----------------
  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);

  pinMode(WHITE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(GAS_BUTTON, INPUT_PULLUP);
  pinMode(MOTION_BUTTON, INPUT_PULLUP);

  // Active LOW relay modules
  digitalWrite(RELAY_LIGHT, HIGH);
  digitalWrite(RELAY_FAN, HIGH);

  digitalWrite(WHITE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  noTone(BUZZER);

  // ---------------- WiFi ----------------
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  mqttClient.setServer(mqttServer, mqttPort);
  connectMQTT();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // ---------------- Web Server ----------------
  server.on("/", []() {
    server.send(200, "text/html", webpage());
  });

  server.begin();

  Serial.println("Web Server Started");
  Serial.println("--------------------------");
}
void loop() {

  // ----------- Read Sensors -----------
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temperature)) temperature = 0;
  if (isnan(humidity)) humidity = 0;

  lightValue = analogRead(LDR_PIN);

  gasDetected = (digitalRead(GAS_BUTTON) == LOW);
  motionDetected = (digitalRead(MOTION_BUTTON) == LOW);

  // ----------- Automation -----------

  // Light Control
  if (lightValue < 1800)
    lightState = true;
  else
    lightState = false;

  // Fan Control
  if (temperature >= 30)
    fanState = true;
  else
    fanState = false;

  // ----------- Relay Control (Active LOW) -----------
  digitalWrite(RELAY_LIGHT, !lightState);
  digitalWrite(RELAY_FAN, !fanState);

  // ----------- LEDs & Buzzer -----------

  digitalWrite(WHITE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  noTone(BUZZER);

  if (gasDetected) {

    digitalWrite(RED_LED, HIGH);

    tone(BUZZER, 2000);

  }

  else if (motionDetected) {

    digitalWrite(YELLOW_LED, HIGH);

    tone(BUZZER, 1000);

  }

  else {

    digitalWrite(WHITE_LED, HIGH);

  }

  // ----------- OLED Display -----------

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("Temp : ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 10);
  display.print("Hum  : ");
  display.print(humidity, 0);
  display.println("%");

  display.setCursor(0, 20);
  display.print("LDR  : ");
  display.print(lightValue);

  display.setCursor(0, 30);
  display.print("Light: ");
  display.println(lightState ? "ON" : "OFF");

  display.setCursor(70, 30);
  display.print("Fan:");
  display.print(fanState ? "ON" : "OFF");

  display.setCursor(0, 40);
  display.print("Gas  : ");
  display.println(gasDetected ? "ALERT" : "SAFE");

  display.setCursor(0, 50);
  display.print("Motion:");
  display.println(motionDetected ? "YES" : "NO");

  display.display();

  // ----------- Serial Monitor -----------

  Serial.print("Temp=");
  Serial.print(temperature, 1);

  Serial.print("  Hum=");
  Serial.print(humidity, 0);

  Serial.print("  LDR=");
  Serial.print(lightValue);

  Serial.print("  Light=");
  Serial.print(lightState ? "ON" : "OFF");

  Serial.print("  Fan=");
  Serial.print(fanState ? "ON" : "OFF");

  Serial.print("  Gas=");
  Serial.print(gasDetected ? "ALERT" : "SAFE");

  Serial.print("  Motion=");
  Serial.println(motionDetected ? "YES" : "NO");

  if (!mqttClient.connected()) {
  connectMQTT();
}

mqttClient.loop();

String json = "{";
json += "\"temperature\":" + String(temperature,1) + ",";
json += "\"humidity\":" + String(humidity,0) + ",";
json += "\"ldr\":" + String(lightValue) + ",";
json += "\"light\":\"" + String(lightState ? "ON" : "OFF") + "\",";
json += "\"fan\":\"" + String(fanState ? "ON" : "OFF") + "\",";
json += "\"gas\":\"" + String(gasDetected ? "ALERT" : "SAFE") + "\",";
json += "\"motion\":\"" + String(motionDetected ? "YES" : "NO") + "\"";
json += "}";

boolean success = mqttClient.publish(mqttTopic, json.c_str());

if (success) {
  Serial.println("MQTT Publish SUCCESS");
} else {
  Serial.println("MQTT Publish FAILED");
}

Serial.println(json);
  // ----------- Web Server -----------
  server.handleClient();

  delay(500);
}
