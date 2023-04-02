#include <LiquidCrystal_I2C.h>

#define joyX A2
#define joyY A3

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte symbol[] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111};

int x = 0, y = 0;

void setup()
{
    Serial.begin(9610);
    Serial.println("Start");

    lcd.init();
    lcd.backlight();
}

void loop()
{
    lcd.clear();

    float xValue = analogRead(joyX);
    float yValue = analogRead(joyY);

    if (xValue > 700)
    {
        x += 1;
    }

    if (xValue < 300)
    {
        x -= 1;
    }

    if (yValue > 700)
    {
        y -= 1;
    }

    if (yValue < 300)
    {
        y += 1;
    }

    x = (x + 2) % 2;
    y = (y + 16) % 16;

    lcd.createChar(0, symbol);
    lcd.setCursor(y, x);
    lcd.write(0);
    Serial.print(x);
    Serial.print(y);
    Serial.print("\n");

    delay(150);
}
