#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include "Temp.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
virtuabotixRTC myRTC(6, 7, 8);
Temp temp(2);

void setup()
{
    Serial.begin(9610);
    Serial.println("Start");

    lcd.init();
    lcd.backlight();
    temp.init();

    // myRTC.setDS1302Time(4, 34, 1, 2, 27, 3, 2023);
}

void loop()
{
    lcd.clear();

    float t = temp.GetTempC();
    lcd.setCursor(0, 1);

    if (!isnan(t))
    {
        lcd.print("Temp: ");
        lcd.print(t);
        lcd.print(" \"C");
    }

    myRTC.updateTime();
    // Serial.print("Current Date / Time: ");
    // Serial.print(myRTC.dayofmonth);
    // Serial.print("/");
    // Serial.print(myRTC.month);
    // Serial.print("/");
    // Serial.print(myRTC.year);
    // Serial.print("  ");
    // Serial.print(myRTC.hours);
    // Serial.print(":");
    // Serial.print(myRTC.minutes);
    // Serial.print(":");
    // Serial.println(myRTC.seconds);

    lcd.setCursor(0, 0);

    lcd.print(myRTC.hours);
    lcd.print(":");

    lcd.print(myRTC.minutes);
    lcd.print(":");
    lcd.print(myRTC.seconds);

    delay(1000);
}
