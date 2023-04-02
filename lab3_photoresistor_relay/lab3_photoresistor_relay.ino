#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

const int brightnessLimit = 350;
const int photoResistorPin = A0;
const int relayPin = 3;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

bool relayState = false;

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");

    lcd.init();
    lcd.backlight();

    dht.begin();

    pinMode(relayPin, OUTPUT);
    pinMode(photoResistorPin, INPUT);
}

void loop()
{
    int brightness = analogRead(photoResistorPin);

    bool newRelayState = brightness < brightnessLimit;

    if (relayState != newRelayState)
    {
        digitalWrite(relayPin, newRelayState ? HIGH : LOW);
        relayState = newRelayState;
        Serial.println("Relay state changed to " + String(relayState));
    }

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    String tempStr = "Temp: " + String(temperature) + "\"C";
    String humStr = "Humidity: " + String(humidity) + "%";
    String brightStr = "Brightness: " + String(brightness);

    Serial.print(tempStr + "\t" + humStr + "\t" + brightStr);
    Serial.println();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(brightStr);
    lcd.setCursor(0, 1);
    lcd.print("Relay state:  " + String(relayState));

    delay(500);
}