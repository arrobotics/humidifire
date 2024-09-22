///////main////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#define DHTPIN 0

// Define pins
#define DHTPIN 3       // DHT11 sensor pin
#define RELAY_PIN 11    // Relay or fan control pin
#define LED_PIN 2       // Green LED pin


// Initialize DHT sensor
DHT dht(DHTPIN, DHT11);

// Initialize OLED display with I2C address 0x3C and resolution 128x64
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize DHT sensor
  dht.begin();

  // Initialize OLED display
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  delay(500);
  display.clearDisplay();
  display.display();

  // Initialize relay and LED pin
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Start with relay and LED off
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read humidity from DHT11 sensor
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early
  if (isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Display humidity data on OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15,0);
  display.print(F("Humidity: "));
  display.setTextSize(2);
  display.setCursor(25,40);
  display.print(humidity);
  display.println(F("%"));
  display.display();

  // Control relay/fan and LED based on humidity levels
  if (humidity > 60.0) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn on relay/fan
    digitalWrite(LED_PIN, LOW);     // Turn off green LED
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn off relay/fan
    digitalWrite(LED_PIN, HIGH);    // Turn on green LED
  }

  // Wait for a bit before the next loop
  delay(2000);
}
