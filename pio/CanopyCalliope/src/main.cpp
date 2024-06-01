#include <Arduino.h>
#include <Keyboard.h>

struct Switch
{
  int pin;
  char character;
  int state;
  int debounceState;
  unsigned long debounceTime;
};

Switch switches[] = {
    {0, 'a', HIGH, HIGH, 0},
    {1, 'z', HIGH, HIGH, 0},
    {2, 's', HIGH, HIGH, 0},
    {3, 'x', HIGH, HIGH, 0},
    {4, 'd', HIGH, HIGH, 0},
    {5, 'c', HIGH, HIGH, 0},
    {6, 'f', HIGH, HIGH, 0},
    {7, 'v', HIGH, HIGH, 0},
    {8, 'g', HIGH, HIGH, 0},
    {9, 'b', HIGH, HIGH, 0},
    {10, 'h', HIGH, HIGH, 0},
    {11, 'n', HIGH, HIGH, 0},
    {12, 'j', HIGH, HIGH, 0},
    {13, 'm', HIGH, HIGH, 0},
    {14, 'k', HIGH, HIGH, 0},
    {15, ',', HIGH, HIGH, 0}};

const int switchCount = sizeof(switches) / sizeof(switches[0]);
const int debounceDelay = 50;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Keyboard.begin();

  for (int i = 0; i < switchCount; i++)
  {
    pinMode(switches[i].pin, INPUT_PULLUP);
  }
}

void loop()
{
  unsigned long currentTime = millis();
  int pressCount = 0;

  for (int i = 0; i < switchCount; i++)
  {
    int newState = digitalRead(switches[i].pin);

    // Check for state change.
    if (newState != switches[i].debounceState)
    {
      switches[i].debounceTime = currentTime;
    }

    // Check for debounce delay.
    if ((currentTime - switches[i].debounceTime) > debounceDelay && newState != switches[i].state)
    {
      switches[i].state = newState;

      Serial.print("Pin: ");
      Serial.print(switches[i].pin);
      Serial.print(", Character: ");
      Serial.print(switches[i].character);
      Serial.print(", State: ");
      Serial.println(newState);

      if (newState == HIGH)
      {
        Keyboard.release(switches[i].character);
      }
      else if (newState == LOW)
      {
        Keyboard.press(switches[i].character);
      }
    }

    if (switches[i].state == LOW)
      pressCount++;

    // Save state.
    switches[i].debounceState = newState;
  }

  // Handle indicator.
  if (pressCount > 0)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
