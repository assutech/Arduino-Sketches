

void setup() {
  
}

void loop() {
  
}


void blinkLed(int pin, int duration) {
  digitalWrite(pin, HIGH);
  delay(duration)
  digitalWrite(pin, LOW);  
  delay(duration);
}

void beep(int pin, int freq, int duration) {
  tone(pin, freq);
  delay(duration);
  noTone(pin);
}

void doubleBeep(int pin, int freq, int beepDelay, int interval) {
  beep(pin, freq, beepDelay);
  delay(interval);
  beep(pin, freq, beepDelay);
}

void disableAllDigitalPins() {
  for(int pin = 0; pin < 14; pin++) {
    digitalWrite(pin, LOW); 
  } 
}


void getSensorVoltage(int sensorVal) {
  return (sensorVal / 1024.0) * 5.0);
}

void getSensorVal(int sensorPin) {
  return digitalRead(sensorPin); 
}
