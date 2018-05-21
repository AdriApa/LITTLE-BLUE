//LM35(SENSOR TEMPERATURA)
int lectura;
float volt;
int temp;
//SERVO MOTOR
int pos=60;
int distancia;
//LIBRERIAS
#include<NewPing.h>
#include<Servo.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>
 NewPing sonar(8,9);//trigger=8,echo=9
 Servo servo;
 LiquidCrystal lcd (12,11,5,4,3,2);
  #if defined(ARDUINO_ARCH_SAMD)
  #define Serial SerialUSB
  #endif

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setup () {
   servo.attach(13);

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  lcd.begin(16,2);
  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
 
//LM35 CONFIGURACIÓN TEMPERATURA

  lectura =analogRead(A0);
  volt=(lectura/1024.0)*5.0;
  temp = (volt) * 100; 
  lcd.setCursor(11,1);
  lcd.print(temp);
  lcd.print("\337"); 
  lcd.print ("C");
  delay(50);
/DS 1307
    DateTime now = rtc.now();
    lcd.setCursor(0,0);
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    
    //lcd.print("   <--");
    delay(1000);
    lcd.setCursor(11,0);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.setCursor(0,1);
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
    lcd.print("  ");
  //SERVO MOTOR
       distancia=sonar.ping_cm();
  if(distancia<=20){
    servo.write(110);
    delay(1000);
    distancia=sonar.ping_cm();
    
  }
  if(distancia>20){
    servo.write(60);
    
  }
}
