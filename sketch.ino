#define BLYNK_TEMPLATE_ID "Youridhere"
#define BLYNK_TEMPLATE_NAME "health monitor"
#define BLYNK_AUTH_TOKEN "your Token here"


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// WiFi Credentials for Wokwi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define DHTPIN 23          
#define DHTTYPE DHT22       
#define POT_PIN 34         
#define LED_ALARM 2        

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer; // Timer to send data every 2 seconds

// --- IoT Data Sending Function ---
void sendSensorData() {
  float t = dht.readTemperature();
  int curr = map(analogRead(34), 0, 4095, 0, 1000);
  
  // Calculate Health logic (same as before)
  int health = 100;
  String status = "HEALTHY";
  if (t > 50) { health -= 30; status = "HOT"; }
  if (curr > 700) { health -= 40; status = "OVERLOAD"; }

  // Send to Blynk
  Blynk.virtualWrite(V1, health);
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, curr);
  Blynk.virtualWrite(V4, status);

  // Update LCD locally
  lcd.setCursor(0, 0);
  lcd.print("H:"); lcd.print(health); lcd.print("% ");
  lcd.print(status); lcd.print("   ");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_ALARM, OUTPUT);
  lcd.init();
  lcd.backlight();
  dht.begin();

  // Start Blynk
  Blynk.begin(auth, ssid, pass);
  
  // Setup a function to be called every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run(); // Keep Blynk connection alive
  timer.run(); // Run the timer for data sending
}