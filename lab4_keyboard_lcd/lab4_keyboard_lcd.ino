#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ROW_NUM = 4;    // four rows
const int COLUMN_NUM = 4; // four columns

const char RemoveKey = 'R';
const char ClearKey = 'C';
const char DivideKey = '/';
const char MultiplyKey = '*';
const char SubtractKey = '-';
const char AddKey = '+';

char keys[ROW_NUM][COLUMN_NUM] = {
    {ClearKey, '7', '4', '1'},
    {'0', '8', '5', '2'},
    {RemoveKey, '9', '6', '3'},
    {DivideKey, MultiplyKey, SubtractKey, AddKey}};

byte pin_rows[ROW_NUM] = {5, 4, 3, 2};      // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {6, 7, 8, 9}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

String expression = "";

void setup()
{
    lcd.init();
    lcd.backlight();

    Serial.begin(9600);
}

void loop()
{
    char key = keypad.getKey();

    if (!key)
        return;

    Serial.print(key);

    modifyExpression(key);
    long result = tryCalculateExpression();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(expression);

    lcd.setCursor(0, 1);
    lcd.print(result);
}

void modifyExpression(char key)
{
    if (key == RemoveKey)
        expression = expression.substring(0, expression.length() - 1);
    else if (key == ClearKey)
        expression = "";
    else
        expression += key;
}

long tryCalculateExpression()
{
    long result = 0;
    long operand = 0;
    char operation = AddKey;
    for (char c : expression)
    {
        if (isdigit(c))
        {
            operand = (operand * 10) + (c - '0');
        }
        else if (c == AddKey || c == SubtractKey || c == MultiplyKey || c == DivideKey)
        {
            switch (operation)
            {
            case AddKey:
                result += operand;
                break;
            case SubtractKey:
                result -= operand;
                break;
            case MultiplyKey:
                result *= operand;
                break;
            case DivideKey:
                result /= operand;
                break;
            }
            operation = c;
            operand = 0;
        }
    }
    switch (operation)
    {
    case AddKey:
        result += operand;
        break;
    case SubtractKey:
        result -= operand;
        break;
    case MultiplyKey:
        result *= operand;
        break;
    case DivideKey:
        result /= operand;
        break;
    }

    return result;
}