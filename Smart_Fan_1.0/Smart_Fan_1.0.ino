
const int activeLed = 4;//fan is on indicator
const int standbyLed = 2;//fan on standby indicator
const int fanPin = 9;
const int piezoPin = 10;
//sensor variables
const int sensorPin = A0;
float baseTemp = 0.0; //base line temperature
float voltage = 0.0;
float temperature = 0.0;
int sensorVal = 0;
bool fanOn = false;

void setup() {
  Serial.begin(9600);//begin communication with serial port
  pinMode(activeLed, OUTPUT);
  pinMode(standbyLed, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  baseTemp = getTemperature();
  Serial.println("Base temperature: ");
  Serial.println(baseTemp);
  doubleBeep(piezoPin, 1000, 100, 20);
}

void loop() {
  temperature = getTemperature();
  if (temperature < baseTemp-.50) {
    digitalWrite(activeLed, LOW);
    digitalWrite(fanPin, LOW);
    blinkLed(standbyLed, 500);
    if(fanOn) {
      beep(piezoPin, 1000, 800);
      fanOn = false; 
    }
    Serial.print("Fan Off, Led Blinking. Temperature: ");
    Serial.print(temperature);
    Serial.println();
  } else if (temperature > baseTemp+.50){
    digitalWrite(activeLed, HIGH);
    digitalWrite(fanPin, HIGH);
    if(fanOn == false) {
      beep(piezoPin, 1000, 200);
      fanOn = true;
    } 
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
