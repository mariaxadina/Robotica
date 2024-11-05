#include <Arduino.h>
#define BTN_1 2 // Button 1: Used to select the difficulty level
#define BTN_2 3 // Button 2: Used to start or stop the game
#define RGB_B 4
#define RGB_G 5
#define RGB_R 6

// Variables needed for debouncing
const unsigned long debounceDelay = 50;

int buttonState_1;
int lastButtonState_1 = HIGH;
unsigned long lastDebounceTime_1 = 0;

int buttonState_2;
int lastButtonState_2 = HIGH;
unsigned long lastDebounceTime_2 = 0;

// Debouncing function for buttons
int debounceButton(int buttonPin, int &lastButtonState, unsigned long &lastDebounceTime, int &buttonState) { 
    int reading = digitalRead(buttonPin); // Read current button state (LOW or HIGH)

    if (reading != lastButtonState) { // If current state is different from the last recorded state (change from HIGH to LOW or vice versa)
        lastDebounceTime = millis(); // Start timing
    }

    if ((millis() - lastDebounceTime) > debounceDelay) { // If the signal persists beyond 50 ms, it means the button was pressed and not due to noise
        if (reading != buttonState) { // If the button state differs from its last stable state
            buttonState = reading; // Save the stable state of the button
        }
    }

    lastButtonState = reading; // Record the current state as the last one
    return buttonState;        // Return the current button state (LOW or HIGH)
}

// Variables needed for the function that sets the difficulty
int key = -1;
int difficulty = -1;
const char *msg1 = "Easy mode on!\n";
const char *msg2 = "Medium mode on!\n";
const char *msg3 = "Hard mode on!\n";

// Function to cycle through difficulty levels
int selectDifficulty() {
    key = (key + 1) % 3;
    switch (key) {
    case 0:
        Serial.print(msg1);
        delay(500);
        break;
    case 1:
        Serial.print(msg2);
        delay(500);
        break;
    case 2:
        Serial.print(msg3);
        delay(500);
        break;
    default:
        break;
    }
    return key;
}

const unsigned long roundTime = 30000;  // Total time allocated per round
unsigned long timePerWord = 0;          // Time allocated per word based on difficulty
unsigned long timePassed = 0;
volatile bool gameRunning = false;

// Function to start the game with the selected difficulty and time per word
void StartGameWithChosenDifficulty(int difficulty, unsigned long &timePerWord) {
    unsigned long previousMillis = millis();   // Initial time
    bool ledState = false;                     // Track the LED state (on or off)
    int blinkCount = 0;                        // Count the number of toggles (6 toggles for 3 blinks)

    while (blinkCount < 6) {                   // Loop until 6 toggles (3 blinks)
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= 500) {
            previousMillis = currentMillis;    // Save the last toggle time
            ledState = !ledState;              // Toggle LED state

            // Set RGB LED color based on ledState
            if (ledState) {
                digitalWrite(RGB_G, LOW);
                digitalWrite(RGB_R, LOW);
                digitalWrite(RGB_B, LOW);
            } else {
                digitalWrite(RGB_G, HIGH);
                digitalWrite(RGB_R, HIGH);
                digitalWrite(RGB_B, HIGH);
            }

            blinkCount++; // Increment blink count after each toggle
        }
    }

    // Set time per word based on difficulty level
    if (difficulty == 0)
        timePerWord = 7000;
    else if (difficulty == 1)
        timePerWord = 6000;
    else if (difficulty == 2)
        timePerWord = 5000;

    timePassed = millis(); // Start timing for the round
    gameRunning = true;
}

// Word dictionary
String words[] = {"apple", "cherry", "honey", "peach", "coconut", "vanilla", "mint", "mango", "chocolate", "cinnamon", "caramel", "rose", "lavander", "peonies"};

int index = 0, score = 0;
unsigned long time = 0;
String userInput = "";

void runGame() {
    if (millis() - timePassed < roundTime) {    // Check if round time hasn't expired

            if (millis() - time >= timePerWord) {
                // Word timed out, update to a new word
                time = millis();        // Reset word timer
                userInput = "";         // Clear user input for new word

                // Randomly select a new word
                index = random(0, 14); 
                Serial.print("\nNew word: ");
                Serial.println(words[index]);
            }

            // Handle serial input and backspace functionality
            if (Serial.available()) {
                char letter = Serial.read();
                if (letter == 8 && userInput.length() > 0) {
                    userInput.remove(userInput.length() - 1);
                }
                else if (letter != 8) {
                    userInput += letter;
                    //Serial.print("Current input: ");
                    //Serial.println(userInput);
                }
            }

            // Check if the current user input partially matches the word
            bool correctWord = (words[index].substring(0, userInput.length()) == userInput);

            // Update LED indicators based on match status
            if (correctWord) {
                digitalWrite(RGB_G, HIGH);      // Green LED on for correct input
                digitalWrite(RGB_R, LOW);       // Red LED off
                digitalWrite(RGB_B, LOW);       // Blue LED off
            } else { 
                digitalWrite(RGB_G, LOW);       // Green LED off
                digitalWrite(RGB_R, HIGH);      // Red LED on for incorrect input
                digitalWrite(RGB_B, LOW);       // Blue LED off
            }

            // Check if the word is fully and correctly typed
            if (userInput == words[index]) {
                score++; // Increment score for correct word
                userInput = ""; // Reset input for new word
                time = millis(); // Reset word timer
                index = random(0, 14); // Get a new word
                Serial.println();
                Serial.print("\nNew word: ");
                Serial.println(words[index]);
            }
        } else {
            // Round ended, display score and end game
            Serial.print("\nGame Over! Your score is: ");
            Serial.println(score);
            gameRunning = false;
            score = 0;

            // Initialize RGB LED in initial state, white color
            digitalWrite(RGB_G, HIGH); 
            digitalWrite(RGB_R, HIGH);
            digitalWrite(RGB_B, HIGH);
        }
}

void startGame() {
    StartGameWithChosenDifficulty(difficulty, timePerWord);
    gameRunning = true;
    Serial.println("Game Started.");
}

void stopGame() {
    gameRunning = false;
    score = 0;                    // Optionally reset score
    userInput = "";                // Clear any current input
    digitalWrite(RGB_G, HIGH);     // Turn off the RGB LED
    digitalWrite(RGB_R, HIGH);
    digitalWrite(RGB_B, HIGH);
    Serial.println("Game Stopped.");
}

volatile bool toggleGameState = false;
unsigned long lastInterruptTime = 0;

void toggleGame() {
    unsigned long currentTime = millis();

    if (currentTime - lastInterruptTime > debounceDelay) {
        toggleGameState = true;  
        lastInterruptTime = currentTime;
    }
}

void setup() {
    // Set RGB LED mode as output
    pinMode(RGB_G, OUTPUT); 
    pinMode(RGB_B, OUTPUT);
    pinMode(RGB_R, OUTPUT);

    // Set buttons as input and enable pull-up resistor
    pinMode(BTN_1, INPUT_PULLUP); 
    pinMode(BTN_2, INPUT_PULLUP);

    // Initialize RGB LED in initial state, white color
    digitalWrite(RGB_G, HIGH); 
    digitalWrite(RGB_R, HIGH);
    digitalWrite(RGB_B, HIGH);

    Serial.begin(28800);
    randomSeed(analogRead(0));
    attachInterrupt(digitalPinToInterrupt(BTN_2), toggleGame, FALLING);
}


bool gameStarted = false;

void loop() {
    /* Button 1 (BTN_1) cycles through difficulty levels each time it's pressed.
       Difficulty levels are: Easy, Medium, and Hard.
       Difficulty affects the speed of the game (i.e., the time allowed per word). */

    if (digitalRead(BTN_1) == LOW && debounceButton(BTN_1, lastButtonState_1, lastDebounceTime_1, buttonState_1) == LOW) {
        difficulty = selectDifficulty();
        gameStarted = false;
    }

    /* Button 2 (BTN_2) is used to start or stop the game. 
       When Button 2 is pressed it interrups the process and triggers the StartGame function with the selected difficulty level and time per word.
       This begins a new game session. If pressed again, it stops the game.*/

    if (toggleGameState) {
        toggleGameState = false;  // Clear the toggle flag

        // Toggle game state and call startGame() or stopGame() based on the gameRunning flag
        if (!gameRunning) {
            Serial.println("Starting game...");  
            startGame();
        } else {
            stopGame();
        }
    }

    if (gameRunning) {
        runGame();
    }
}