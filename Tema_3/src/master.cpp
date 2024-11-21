#include <Wire.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define LCD_PIN_RS 8
#define LCD_PIN_EN 6
#define LCD_PIN_D4 5
#define LCD_PIN_D5 4
#define LCD_PIN_D6 3
#define LCD_PIN_D7 2
#define BUTTON_PIN_START 7
#define PIN_SERVO 9

int scorePlayer1 = 0;
int scorePlayer2 = 0;
int currentPlayer = 1;
int roundNumber = 0;
int maxRounds = 5;
bool isGameActive = false;
String playerName1 = "";
String playerName2 = "";

LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_EN, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
Servo servo;

void displayPlayerScores()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1: ");
    lcd.print(scorePlayer1);
    lcd.setCursor(8, 0);
    lcd.print("2: ");
    lcd.print(scorePlayer2);
}

void updateServoPositionForRound()
{
    int position = map(roundNumber, 0, maxRounds, 0, 180);

    servo.write(position);
    delay(500);
}

void startNewGame()
{
    lcd.clear();
    lcd.print("Game Started!");
    delay(1000);
    lcd.clear();
    displayPlayerScores();
    isGameActive = true;
    Serial.println("Game Started");
}

void sendCommandToSlave(char comm, int value)
{
    Wire.beginTransmission(8);
    Wire.write(comm);
    Wire.write(value);
    Wire.endTransmission();
}

void endCurrentGame()
{
    lcd.clear();
    lcd.print("Game Over!");
    delay(1000);
    lcd.clear();
    if (scorePlayer1 > scorePlayer2)
    {
        lcd.setCursor(0, 0);
        lcd.print("Winner:");
        lcd.setCursor(0, 1);
        lcd.print(playerName1);
    }
    else if (scorePlayer2 > scorePlayer1)
    {
        lcd.setCursor(0, 0);
        lcd.print("Winner:");
        lcd.setCursor(0, 1);
        lcd.print(playerName2);
    }
    else
    {
        lcd.print("Tie!");
    }
    delay(3000);

    sendCommandToSlave('R', 0);

    isGameActive = false;
    roundNumber = 0;
    scorePlayer1 = 0;
    scorePlayer2 = 0;
    servo.write(0);
    lcd.clear();
    lcd.print("Press to start!");
}

void playCurrentRound()
{
    sendCommandToSlave('P', currentPlayer);
    int codeColor = random(1, 4);
    sendCommandToSlave('C', codeColor);
    delay(100);

    unsigned long startTime = millis();
    bool correctPress = false;

    while (!correctPress && (millis() - startTime < 3000))
    {
        Wire.requestFrom(8, 2);
        if (Wire.available() >= 2)
        {
            int points = Wire.read();
            int correctness = Wire.read();
            Serial.print("Received Points: ");
            Serial.print(points);
            Serial.print(", Correctness: ");
            Serial.println(correctness);
            if (correctness == 1)
            {
                correctPress = true;
                if (currentPlayer == 1)
                    scorePlayer1 += points;
                else
                    scorePlayer2 += points;
            }
        }
    }

    displayPlayerScores();
    updateServoPositionForRound();
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
    roundNumber++;

    if (roundNumber >= maxRounds)
    {
        endCurrentGame();
    }
}

void loadingAnimation()
{
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Loading...");

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            lcd.setCursor(j, 1);
            lcd.print("**");
            delay(100);
            lcd.setCursor(j, 1);
            lcd.print("  ");
        }
    }

    for (int i = 0; i < 16; i++)
    {
        lcd.setCursor(i, 1);
        lcd.print("*");
        delay(100);
        lcd.setCursor(i, 1);
        lcd.print(" ");
    }

    for (int i = 0; i < 5; i++)
    {
        lcd.clear();
        delay(100);
        lcd.setCursor(4, 0);
        lcd.print("Loading...");
        delay(100);
    }
}

String getPlayerNameInput(String &player, const char *msg)
{
    player = "";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg);
    Serial.println(msg);

    while (true)
    {
        if (Serial.available())
        {
            char letter = Serial.read();

            if (letter == '\n')
            {
                break;
            }
            else if (letter == 8 && player.length() > 0)
            {
                player.remove(player.length() - 1);
                lcd.setCursor(0, 1);
                lcd.print(player + " ");
            }
            else if (letter != 8)
            {
                player += letter;
                lcd.setCursor(0, 1);
                lcd.print(player);
            }
        }
    }
    return player;
}

void setup()
{
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Quick Game");
    lcd.setCursor(0, 1);
    lcd.print("Press to start");
    pinMode(BUTTON_PIN_START, INPUT_PULLUP);
    servo.attach(PIN_SERVO);
    servo.write(0);

    Wire.begin();
    Serial.begin(9600);
}

void loop()
{
    if (!isGameActive)
    {
        if (digitalRead(BUTTON_PIN_START) == LOW)
        {
            delay(100);
            if (digitalRead(BUTTON_PIN_START) == LOW)
            {
                loadingAnimation();
                playerName1 = getPlayerNameInput(playerName1, "Player 1 name:");
                playerName2 = getPlayerNameInput(playerName2, "Player 2 name:");
                startNewGame();
            }
        }
    }
    else
        playCurrentRound();
}
