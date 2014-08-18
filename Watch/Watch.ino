#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int hour, minute, second;
void setup() {
  lcd.begin(16, 2);
  lcd.print("Assutech Inc."); 
  delay(5000);
  lcd.clear();
  delay(100);
  hour = 16;
  minute = 21;
  second = 0;
}

void loop() {
  
  lcd.print(hour);
  lcd.print(":");
  lcd.print(minute);
  lcd.print(":");
  lcd.print(second);
  if(second < 10)
    lcd.print(" ");
  if(second == 59) {
    minute++;
    second = 0;  
  }
  if(minute == 59) {
    hour++;  
  }
  if(hour == 23) {
     hour = 00;
     minute = 00;
     second = 00;
  }
  lcd.setCursor(0,0);
  second++;
  delay(999); 
}
