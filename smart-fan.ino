#include <LiquidCrystal.h>
 
const int tempPin = A0;
const int motorPin = 9;
 
// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup() {
 Serial.begin(9600);
 pinMode(motorPin, OUTPUT);
 lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
 lcd.print("Temp: ");
}
 
void loop() {
 // Read temperature from TMP36
 int sensorValue = analogRead(tempPin);
 float voltage = (sensorValue / 1024.0) * 5.0;
 float temperatureC = (voltage - 0.5) * 100;
 
 // Print temperature to Serial Monitor
 Serial.print("Temperature: ");
 Serial.print(temperatureC);
 Serial.println(" °C");
 
 // Control fan speed based on temperature
 int fanSpeed = 0;
 if (temperatureC < 20) {
   analogWrite(motorPin, 0); // Fan off
   fanSpeed = 0;
 } else if (temperatureC >= 20 && temperatureC < 25) {
   analogWrite(motorPin, 100); // Slow speed
   fanSpeed = 1;
 } else if (temperatureC >= 25 && temperatureC < 30) {
   analogWrite(motorPin, 180); // Medium speed
   fanSpeed = 2;
 } else {
   analogWrite(motorPin, 255); // Full speed
   fanSpeed = 3;
 }
 
 // Display temperature and fan speed on LCD
 lcd.setCursor(0, 0); // Set cursor to the first row, first column
 lcd.print("Temp: ");
 lcd.print(temperatureC);
 lcd.print(" C");
 
 lcd.setCursor(0, 1); // Set cursor to the second row, first column
 lcd.print("Fan: ");
 if (fanSpeed == 0){
   lcd.print("Off");
 } else if (fanSpeed == 1){
   lcd.print("Slow");
 } else if (fanSpeed == 2){
   lcd.print("Med ");
 } else {
   lcd.print("Fast");
 }
 
 delay(1000); // Wait for 1 second
}
