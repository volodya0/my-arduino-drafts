#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");

    lcd.init();
    lcd.backlight();

    dht.begin();
}

void loop()
{
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    String tempStr = "Temp: " + String(temperature) + "\"C";
    String humStr = "Humidity: " + String(humidity) + "%";

    Serial.print(tempStr);
    Serial.print("\t");
    Serial.print(humStr);
    Serial.println();

    lcd.setCursor(0, 0);
    lcd.print(tempStr);

    lcd.setCursor(0, 1);
    lcd.print(humStr);

    delay(2000);
}