#define trigPin 8
#define echoPin 7
#define buzzer 12
#define buttonPin 2

int buttonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 100;
int lastButtonState = LOW;

long lastBeepTime = 0;
long beepDelay = 500;

int maxRange = 30; // distancia máxima inicial no qual o aparelho começa a detectar objetos

void setup()
{
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
}

void sight()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if ((millis() - lastBeepTime) > beepDelay)
  {
    if (distance > 30 and distance < maxRange)
    {
      tone(buzzer, 100, 50);
      lastBeepTime = millis();
    }
    else if (distance > 0 and distance <= 30)
    {
      tone(buzzer, 100);
      lastBeepTime = millis();
    }
  }
}

void increaseRange()
{
  maxRange += 30;
  if (maxRange > 150)
    maxRange = 30;

  Serial.println(" MAX RANGE: ");
  Serial.print(maxRange);
  Serial.println(" cm");
}

void loop()
{

  sight();

  buttonState = digitalRead(buttonPin);

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (lastButtonState == buttonState)
      return;

    lastButtonState = buttonState;
    if ((buttonState == HIGH))
    {
      increaseRange();
      lastDebounceTime = millis(); // set the current time]
    }
    else if ((buttonState == HIGH))
    {
      increaseRange();
      lastDebounceTime = millis(); // set the current time
    }
  }
}
