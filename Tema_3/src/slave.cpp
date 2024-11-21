#include <Wire.h>
#include <Arduino.h>

#define PLAYER1_RGB_RED 8
#define PLAYER1_RGB_GREEN 7
#define PLAYER1_RGB_BLUE 9

#define PLAYER2_RGB_RED 2
#define PLAYER2_RGB_GREEN 3
#define PLAYER2_RGB_BLUE 13

#define PLAYER1_LED_RED 5
#define PLAYER1_LED_GREEN 6
#define PLAYER1_LED_BLUE 4

#define PLAYER2_LED_RED 11
#define PLAYER2_LED_GREEN 12
#define PLAYER2_LED_BLUE 10

#define BUTTON_PLAYER1 A0
#define BUTTON_PLAYER2 A1

int activePlayer = 0;
int codeColor = 0;
bool waitInput = false;
unsigned long reactionTime = 0;

void RGBColor(int red, int green, int blue, int player)
{
    if (player == 1)
    {
        digitalWrite(PLAYER1_RGB_RED, red);
        digitalWrite(PLAYER1_RGB_GREEN, green);
        digitalWrite(PLAYER1_RGB_BLUE, blue);
    }
    else if (player == 2)
    {
        digitalWrite(PLAYER2_RGB_RED, red);
        digitalWrite(PLAYER2_RGB_GREEN, green);
        digitalWrite(PLAYER2_RGB_BLUE, blue);
    }
}

void setLED(int red, int green, int blue, int player)
{
    if (player == 1)
    {
        digitalWrite(PLAYER1_LED_RED, red);
        digitalWrite(PLAYER1_LED_GREEN, green);
        digitalWrite(PLAYER1_LED_BLUE, blue);
    }
    else if (player == 2)
    {
        digitalWrite(PLAYER2_LED_RED, red);
        digitalWrite(PLAYER2_LED_GREEN, green);
        digitalWrite(PLAYER2_LED_BLUE, blue);
    }
}

void debugButtonFrequency()
{
    int player1Value = analogRead(BUTTON_PLAYER1);
    int player2Value = analogRead(BUTTON_PLAYER2);

    Serial.print("Player 1: ");
    Serial.println(player1Value);
    Serial.print("Player 2: ");
    Serial.println(player2Value);

    delay(500);
}

void resetRGB()
{
    RGBColor(LOW, LOW, LOW, 1);
    RGBColor(LOW, LOW, LOW, 2);
}

void resetIndividualLEDs()
{
    setLED(LOW, LOW, LOW, 1);
    setLED(LOW, LOW, LOW, 2);
}

int readButton(int analogPin)
{
    int value = analogRead(analogPin);
    Serial.print("Analog Read on Pin ");
    Serial.print(analogPin);
    Serial.println(value);

    if (value > 945)
        return 3; // Butonul albastru
    if (value > 70 && value < 85)
        return 2; // Butonul verde
    if (value < 70)
        return 1; // Butonul roșu
    return 0;
}

void masterCommand(int numBytes)
{
    while (Wire.available() >= 2)
    {
        char comm = Wire.read();
        int value = Wire.read();

        if (comm == 'P')
        {
            resetRGB();
            resetIndividualLEDs();
            activePlayer = value;
            Serial.print("Active Player: ");
            Serial.println(activePlayer);
        }
        else if (comm == 'C')
        {
            codeColor = value;
            reactionTime = millis();
            waitInput = true;
            Serial.print("Color: ");
            Serial.println(codeColor);

            if (codeColor == 1)
                RGBColor(HIGH, LOW, LOW, activePlayer); // Roșu
            if (codeColor == 2)
                RGBColor(LOW, HIGH, LOW, activePlayer); // Verde
            if (codeColor == 3)
                RGBColor(LOW, LOW, HIGH, activePlayer); // Albastru
        }
        else if (comm == 'R')
        {
            resetRGB();
            resetIndividualLEDs();
        }
    }
}

void sendCommandToMaster()
{
    int points = 0;
    int correctness = 0;

    if (waitInput)
    {
        int pressedButton = (activePlayer == 1) ? readButton(BUTTON_PLAYER1) : readButton(BUTTON_PLAYER2);

        Serial.print("Pressed Button: ");
        Serial.println(pressedButton);

        if (pressedButton == 1)
            setLED(HIGH, LOW, LOW, activePlayer); // Roșu
        if (pressedButton == 3)
            setLED(LOW, HIGH, LOW, activePlayer); // Verde
        if (pressedButton == 2)
            setLED(LOW, LOW, HIGH, activePlayer); // Albastru

        if (pressedButton == codeColor)
        {
            correctness = 1;
            points = max(0, 1000 - (millis() - reactionTime) / 10);
            waitInput = false;
        }
    }

    Wire.write(points);
    Wire.write(correctness);

    if (!waitInput)
    {
        resetRGB();
        resetIndividualLEDs();
    }
}

void setup()
{
    Serial.begin(9600);

    pinMode(PLAYER1_RGB_RED, OUTPUT);
    pinMode(PLAYER1_RGB_GREEN, OUTPUT);
    pinMode(PLAYER1_RGB_BLUE, OUTPUT);

    pinMode(PLAYER2_RGB_RED, OUTPUT);
    pinMode(PLAYER2_RGB_GREEN, OUTPUT);
    pinMode(PLAYER2_RGB_BLUE, OUTPUT);

    pinMode(PLAYER1_LED_RED, OUTPUT);
    pinMode(PLAYER1_LED_GREEN, OUTPUT);
    pinMode(PLAYER1_LED_BLUE, OUTPUT);

    pinMode(PLAYER2_LED_RED, OUTPUT);
    pinMode(PLAYER2_LED_GREEN, OUTPUT);
    pinMode(PLAYER2_LED_BLUE, OUTPUT);

    setLED(HIGH, HIGH, HIGH, 1);
    setLED(HIGH, HIGH, HIGH, 2);

    Wire.begin(8);
    Wire.onReceive(masterCommand);
    Wire.onRequest(sendCommandToMaster);
}

void loop() {}
