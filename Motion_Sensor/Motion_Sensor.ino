
const int sensorPin = A0;
const int led1 = 13;
const int led2 = 12;
const int led3 = 8;
const int piezoPin = 7;

int sensorValue;
int sensorHigh = 0;
int sensorLow = 1023;
bool lightOn = false;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, HIGH);
  Serial.begin(9600);
  
  while(millis() < 5000) {
    sensorValue = analogRead(sensorPin);
    if(sensorValue > sensorHigh) {
      sensorHigh = sensorValue;  
    }
    if(sensorValue < sensorLow) {
      sensorLow = sensorValue;  
    }
  }
  Serial.print("Sensor High = ");
  Serial.print(sensorHigh);
  Serial.println();
  Serial.print("Sensor Low = ");
  Serial.print(sensorLow);
  digitalWrite(led1, LOW);  
  digitalWrite(led2, HIGH);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  delay(10);
  if(sensorValue > sensorLow+1) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    noTone(piezoPin);
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW); 
    tone(piezoPin, 500);
  }
}

void beep(int pin, int freq, int duration) {
  tone(pin, freq);
  delay(duration);
  noTone(pin);  
}
