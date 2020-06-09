
bool willTheBallGoTowardsPlayerTwo = true;
bool isInputAllowed = true;
bool ONorOFF = false;

int stateNow = 0;
int stateBefore = 0;
int i=0;
int j=0;
const int button = 2;
const int buzzer = 13;

const int playerOne = 11;
const int goalPlayerOne = 12;
const int buttonPlayerOne = 4;

const int playerTwo = 6;
const int goalPlayerTwo = 5;
const int buttonPlayerTwo = 3;

const unsigned long initialMillisecondsPerLED = 500;
const unsigned long initialDeltaMillisecondsPerLED = 50;
unsigned long millisecondsPerLED = initialMillisecondsPerLED;
unsigned long deltaMillisecondsPerLED = initialDeltaMillisecondsPerLED;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

int currentPosition = playerOne;
int previousPosition = playerOne + 1;
int deltaPosition = 0;

int buttonStatePlayerOne = 0;
int lastButtonStatePlayerOne = 0;
int buttonStatePlayerTwo = 0;
int lastButtonStatePlayerTwo = 0;

void setup() {
  pinMode(5, 1);
  pinMode(6, 1);
  pinMode(7, 1);
  pinMode(8, 1);
  pinMode(9, 1);
  pinMode(10, 1);
  pinMode(11, 1);
  pinMode(12, 1);

  pinMode(2,0);
  pinMode(3, 0);   
  pinMode(4, 0);   

  pinMode(13,1);
}

void loop()
{
  ListenForButton();
  if(ONorOFF==true){
  ListenForInput();
  currentMillis = millis();
  if (currentMillis - previousMillis >= millisecondsPerLED) 
  {
    CheckGoalConditions();
    DetermineNextPosition();
    MoveBallToNextPosition();

    previousMillis = currentMillis;
  }
}
}
void ListenForButton(){
 stateNow = digitalRead(button);
if (stateNow != stateBefore) {
if (stateNow==HIGH and i==0) {
ONorOFF=true;
j=1;
}
else if (stateNow==LOW and j==1) {
i=1;
}
else if (stateNow==HIGH and i==1) {
ONorOFF=false;
j=0;
}
else if (stateNow==LOW and j==0) {
i=0;
}
}
stateBefore=stateNow;
}
void ListenForInput() 
{
  buttonStatePlayerOne = digitalRead(buttonPlayerOne);
  buttonStatePlayerTwo = digitalRead(buttonPlayerTwo);

  if (buttonStatePlayerOne != lastButtonStatePlayerOne && isInputAllowed)
  {
    if (buttonStatePlayerOne == 1)
    {
      if (currentPosition == playerOne)
      {
        ToggleBallDirection();
        IncreaseSpeed();
      }
      else
      {
        ScoreForPlayer(2);
      }
    }
    lastButtonStatePlayerOne = buttonStatePlayerOne;
  }
  if (buttonStatePlayerTwo != lastButtonStatePlayerTwo && isInputAllowed)
  {
    if (buttonStatePlayerTwo == 1)
    {
      if (currentPosition == playerTwo)
      {
        ToggleBallDirection();
        IncreaseSpeed();
      }
      else
      {
        ScoreForPlayer(1);
      }
    }
    lastButtonStatePlayerTwo = buttonStatePlayerTwo;
  }
}

void ToggleBallDirection()
{
  willTheBallGoTowardsPlayerTwo = !willTheBallGoTowardsPlayerTwo;
  isInputAllowed = false;   
}

void IncreaseSpeed()
{
  millisecondsPerLED -= deltaMillisecondsPerLED;
  if (deltaMillisecondsPerLED > 0) 
  {
    deltaMillisecondsPerLED -= 5; 
  }
}

void MoveBallToNextPosition()     
{
  previousPosition = currentPosition;
  digitalWrite(previousPosition, 0);
  currentPosition = currentPosition + deltaPosition;
  digitalWrite(currentPosition, 1);
  isInputAllowed = true;
}

void DetermineNextPosition()
{
  if (willTheBallGoTowardsPlayerTwo)
  {
    deltaPosition = -1;
  }
  else
  {
    deltaPosition = 1;
  }
}

void CheckGoalConditions()
{
  if (currentPosition == goalPlayerTwo)
  {
    ScoreForPlayer(1);
  }
  else if (currentPosition == goalPlayerOne)
  {
    ScoreForPlayer(2);
  }
}

void ScoreForPlayer(int player)
{
  if(player==1){
    
  isInputAllowed = false;
  FlashAllLEDs(1);
  currentPosition = playerOne;
  willTheBallGoTowardsPlayerTwo = true;
  ResetValuesForNextRound();
  music();
  }
  if(player==2){
  isInputAllowed = false;
  FlashAllLEDs(2);
  currentPosition = playerOne;
  willTheBallGoTowardsPlayerTwo = true;
  ResetValuesForNextRound(); 
  music();
    
  }
}
void ResetValuesForNextRound() 
{
  millisecondsPerLED = initialMillisecondsPerLED;            
  deltaMillisecondsPerLED = initialDeltaMillisecondsPerLED;  
}

void FlashAllLEDs(int player)  
{
  if(player==2){
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(5,1);
    digitalWrite(6,1);
    delay(500);
    digitalWrite(5,0);
    digitalWrite(6,0);
    digitalWrite(7,0);
    digitalWrite(8,0);
    digitalWrite(9,0);
    digitalWrite(10,0);
    digitalWrite(11,0);
    digitalWrite(12,0);
    delay(500);
  }
  }
  if(player==1){
    digitalWrite(11,1);
    digitalWrite(12,1);
    delay(500);
    digitalWrite(5,0);
    digitalWrite(6,0);
    digitalWrite(7,0);
    digitalWrite(8,0);
    digitalWrite(9,0);
    digitalWrite(10,0);
    digitalWrite(11,0);
    digitalWrite(12,0);
    delay(500);
  }
}
void music(){
  tone(buzzer,329);
  delay(250);
  tone(buzzer,250);
  delay(250);
  tone(buzzer,500);
  delay(250);
  tone(buzzer,880);
  delay(250);
  tone(buzzer,620);
  delay(250);
  tone(buzzer,250);
  delay(250);
  tone(buzzer,500);
  delay(250);
  noTone(buzzer);
}
