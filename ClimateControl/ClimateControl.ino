#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 8     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);
float humidity ;
float temperature;
int motorPin = 3;
int t1 = 23;
int h1 = 50;
int photoPin = A0;
int light;
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
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
  pinMode(motorPin, OUTPUT);
  pinMode(photoPin, INPUT);
  Serial.begin(9600);
  Serial.println("DHT test");
  dht.begin();
  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
}

void loop() {
  // put your main code here, to run repeatedly:
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  light = analogRead(photoPin);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Light: ");
  if (light> 150){
    Serial.println("Sunny");

  }
  else{
    Serial.println("Dark");
  }
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
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  if (light> 150){
   lcd.print("Sunny");
  }
  else{
    lcd.print("Dark");
  }
  delay(3000);
}

