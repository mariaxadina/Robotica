#include <Arduino.h>
#define BTN_1 2 // start
#define BTN_2 3 // stop
#define RGB_B 4
#define RGB_G 5
#define RGB_R 6
#define LED_1 7
#define LED_2 8
#define LED_3 9
#define LED_4 10

void setup()
{
  pinMode(LED_1, OUTPUT); // setez modul de functionare al LED-urilor ca iesire
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  pinMode(RGB_G, OUTPUT); // setez modul de functionare al LED-ului RGB ca iesire
  pinMode(RGB_B, OUTPUT);
  pinMode(RGB_R, OUTPUT);

  pinMode(BTN_1, INPUT_PULLUP); // configurez butoanele ca intrare si activez pull-up
  pinMode(BTN_2, INPUT_PULLUP);

  digitalWrite(RGB_G, HIGH); // las doar led-ul rgb pe culoarea verde aprins, semnificand ca statia este libera
  digitalWrite(RGB_R, LOW);
  digitalWrite(RGB_B, LOW);

  digitalWrite(LED_1, LOW); // pun starea initiala a LED-urilor pentru incarcare pe LOW(LED-urile sunt stinse)
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
}

//functie ce contine animatia de final
void stopIncarcare()
{
  digitalWrite(LED_1, LOW);   // toate LED-urile care reprezinta procentul de incarcare se sting
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);

  for (int i = 0; i <= 3; i++)
  { // led urile clipesc de 3 ori
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    delay(500);

    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    delay(500);
  }

  digitalWrite(RGB_R, LOW);   // statia se elibereaza, LED-ul rosu se stinge si se face verde
  digitalWrite(RGB_G, HIGH);
}

// variabile necesare pentru debouncing
const unsigned long debounceDelay = 50;
int buttonState_1;
int lastButtonState_1 = HIGH;
unsigned long lastDebounceTime_1 = 0;

int buttonState_2;
int lastButtonState_2 = HIGH;
unsigned long lastDebounceTime_2 = 0;

// variabile pentru a calcula timpul pentru care butoanele sunt apasate
const unsigned long longPressTime = 1000;
unsigned long pressTime_1 = 0;
unsigned long pressTime_2 = 0;

//functie ce face debouncing
int debounceButton(int buttonPin, int &lastButtonState, unsigned long &lastDebounceTime, int &buttonState, unsigned long &time)
{
  int reading = digitalRead(buttonPin); // citeste starea actuala a butonului (LOW sau HIGH)

  if (reading != lastButtonState) // daca starea actuala este diferita de ultima stare inregistrata (schimbare de la HIGH la LOW sau invers)
  {
    lastDebounceTime = millis(); // cronometram timpul
  }

  if ((millis() - lastDebounceTime) > debounceDelay)  // daca semnalul depaseste de 50 ms, inseamna ca a fost apasat si nu este din cauza zgomotului
  {
    if (reading != buttonState) // daca starea butonului este diferita de ultima stare stabila a acestuia
    {
      buttonState = reading; // retin starea stabila a butonului
      if (buttonState == LOW) // daca butonul a fost apasat (starea este LOW)
      {
        time = millis(); // cronometrez cate ms este tinut apasat
      }
    }
  }

  lastButtonState = reading; // retin starea acestuia ca fiind ultima
  return buttonState; // starea curenta a butonului (LOW sau HIGH)
}

void loop()
{
top: //eticheta la inceput de program

  if (digitalRead(BTN_1) == LOW && debounceButton(BTN_1, lastButtonState_1, lastDebounceTime_1, buttonState_1, pressTime_1) == LOW) // daca butonul este apasat si starea este stabila
  {
    digitalWrite(RGB_G, LOW); // sting verde, aprind rosu
    digitalWrite(RGB_R, HIGH);

    // 25%
    digitalWrite(LED_1, HIGH);
    delay(750);
    // verific daca intre timp butonul de stop a fost apasat cel putin o secunda
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare(); // daca incarcarea a fost oprita, se efectueaza animatia de final
      goto top;  // programul nu se mai continua, merge inapoi la inceput de program
    }
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    digitalWrite(LED_1, LOW);
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    digitalWrite(LED_1, HIGH);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }

    // 50%
    digitalWrite(LED_2, HIGH);
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    digitalWrite(LED_2, LOW);
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    digitalWrite(LED_2, HIGH);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }

    // 75%
    digitalWrite(LED_3, HIGH);
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    digitalWrite(LED_3, LOW);
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    digitalWrite(LED_3, HIGH);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }

    // 100%
    digitalWrite(LED_4, HIGH);
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    digitalWrite(LED_4, LOW);
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    delay(750);
    if (digitalRead(BTN_2) == LOW && debounceButton(BTN_2, lastButtonState_2, lastDebounceTime_2, buttonState_2, pressTime_2) == LOW && (millis() - pressTime_2) >= 1000)
    {
      stopIncarcare();
      goto top;
    }
    digitalWrite(LED_4, HIGH);

    stopIncarcare(); // la final de incarcare se efecueaza animatia
  }
}
