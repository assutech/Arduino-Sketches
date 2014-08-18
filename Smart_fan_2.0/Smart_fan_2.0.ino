#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int powerSwitch = 13;
const int piezoPin = 7;
const int standbyLed = 9;
const int activeLed = 8;
const int fanPin = 10;
bool deviceActive;
//Sensor variables
const int sensorPin = A0;
float baseTemp = 0.0;
float voltage = 0.0;
float temperature = 0.0;
int sensorVal = 0.0;
bool fanOn = false;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Assutech Inc.");
  delay(5000);
  deviceActive = true;
  Serial.begin(9600);//begin communication with serial port
  pinMode(activeLed, OUTPUT);
  pinMode(standbyLed, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(powerSwitch, INPUT);
  baseTemp = getTemperature();
  Serial.println("Base temperature: ");
  Serial.println(baseTemp);
  lcd.clear();
  delay(100);
  lcd.print("Base temp: ");
  lcd.print(baseTemp);
  lcd.setCursor(0, 1);
  lcd.print("Fan off");
  doubleBeep(piezoPin, 1000, 100, 20);
  delay(1000);//give some interval between beeps incase of fanOn
}

void loop() {
  if(digitalRead(powerSwitch) == HIGH && deviceActive) {
    deviceActive = false;
    shutdown();
  } else if(digitalRead(powerSwitch) == HIGH && deviceActive == false) {
    deviceActive = true;
    setup(); 
  }
  if(deviceActive) {
    temperature = getTemperature();
    if (temperature < baseTemp-.50) {
      if(fanOn) {
        lcd.setCursor(4, 1);
        lcd.print("off");
        beep(piezoPin, 1000, 800);
        fanOn = false; 
      }
      digitalWrite(activeLed, LOW);
      digitalWrite(fanPin, LOW);
      blinkLed(standbyLed, 500);      
      Serial.print("Fan Off, Led Blinking. Temperature: ");
      Serial.print(temperature);
      Serial.println();
    } else if (temperature > baseTemp+.50){
      if(fanOn == false) {
        lcd.setCursor(4, 1);
        lcd.print("on ");
        beep(piezoPin, 1000, 200);
        fanOn = true;
      } 
      digitalWrite(activeLed, HIGH);
      digitalWrite(fanPin, HIGH);
      Serial.print("Fan On, Active Led activeted. Temperature: ");
      Serial.print(temperature);
      Serial.println();
    } else {
      blinkLed(standbyLed, 500);
      Serial.print("Approaching threshold. Temperature: ");
      Serial.print(temperature);
      Serial.println();
    }
  }
}

//returns voltage f
float getVoltage() {
   int sensorVal = getSensorVal(sensorPin);
   return ((sensorVal / 1024.0) * 5.0); 
}

//returns the temperature from a sensor
float getTemperature() {
   return ((getVoltage() - .5) * 100); 
}

//reads from a sensor returns the read value
int getSensorVal(int pinNum) {
   int val = analogRead(pinNum);
   delay(10);//give the analog pin time to read
   return val; 
}

/**
 * Blinks and LED
 * @param pin the led's pin
 * @param interval the interval between the blinks
 */
void blinkLed(int pin, int interval) {
  digitalWrite(pin, HIGH);
  delay(interval);
  digitalWrite(pin, LOW);  
  delay(interval);
}

void beep(int pin, int freq, int duration) {
  tone(pin, freq);
  delay(duration);
  noTone(pin); 
}

void doubleBeep(int pin, int freq, int beepDelay, int interval) {
  beep(piezoPin, freq, beepDelay);
  delay(interval);
  beep(piezoPin, freq, beepDelay); 
}

void disableAllDigitalPins() {
  for(int pin = 0; pin < 14; pin++) {
    digitalWrite(pin, LOW);
  }  
}

void shutdown() {
    beep(piezoPin, 2000, 1000);
     
    lcd.clear();
    delay(10);
    disableAllDigitalPins();
    lcd.print("Shutting down");
    delay(1000);
    lcd.print(".");
    delay(1000);
    lcd.print(".");
    delay(1000);
    lcd.print(".");
    delay(1000);
    lcd.print(".");
    delay(100);
    lcd.clear();
    lcd.print("Goodbye :)");
    delay(300);
    lcd.clear(); 
}
