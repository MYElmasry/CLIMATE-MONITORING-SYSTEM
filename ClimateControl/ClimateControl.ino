#include "DHT.h"       //DHT11 Sensor Library
#define DHTPIN 8       // what pin we're connected to
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);
#include <Adafruit_BMP280.h>  //BMP280 Sensor Library
#define BMP280_ADDRESS 0x76
Adafruit_BMP280 bmp;        // I2C
#include <LiquidCrystal.h>  //LCD Sensor Library
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int photoPin = A0;
int airQualityPin = A1;
float humidity;
float temperature;
float pressure;
int light;
int gasValue;
byte customChar[] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
void setup() {
  // put your setup code here, to run once:
  pinMode(photoPin, INPUT);
  pinMode(airQualityPin, INPUT);
  Serial.begin(9600);
  dht.begin();
  bmp.begin(BMP280_ADDRESS);
  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
}

void loop() {
  // put your main code here, to run repeatedly:
  humidity = dht.readHumidity();         //Humidiyt Read
  temperature = dht.readTemperature();   //Temperature Read
  pressure = bmp.readPressure();         //Pressure Read
  light = analogRead(photoPin);          //Light Read
  gasValue = analogRead(airQualityPin);  //CO2 Read
  // Print Values in Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Light: ");
  if (light > 60) {
    Serial.print("Sunny\t");

  } else {
    Serial.print("Dark\t");
  }
  Serial.print("The amount of CO2 (in PPM): ");
  Serial.print(gasValue);
  Serial.print("\tPressure: ");
  Serial.println(pressure);
  // Print Values On LCD
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" ");
  lcd.write(byte(0));
  lcd.print("C");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  if (light > 60) {
    lcd.print("Sunny");
  } else {
    lcd.print("Dark");
  }
  lcd.setCursor(0, 1);
  lcd.print("CO2: ");
  lcd.print(gasValue);
  lcd.print(" PPM");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pres: ");
  lcd.print(int(pressure));
  lcd.print(" Pa");
  delay(3000);
}