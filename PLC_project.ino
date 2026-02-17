// arduino opta

// PLC button
int lastButtonState = HIGH;
int currentButtonState;
bool isRunning = false;

//valve
enum ValveState {
  CLOSED,
  OPENING,
  OPENED,
  CLOSING
};
ValveState currentValveState = CLOSED;
unsigned long valveStartTime = 0;
const long valveDuration = 5000;

// "weight"
const int weightButtonPin = A3;
int weight;

// limit switch         
const int limitSwitchPin = A2;
int switchState;

// ultrasonic motion sensor
const int distancePin = A1;
const int distanceHalfPin = A0;
int distance = LOW;
int distanceHalf = LOW;




void setup() {
  // PLC button
  pinMode(BTN_USER, INPUT);
  
  // LEDs
  pinMode(LED_D0, OUTPUT); // initial container full
  pinMode(LED_D1, OUTPUT); // initial container half full
  pinMode(LED_D2, OUTPUT); // initial container empty
  pinMode(LED_D3, OUTPUT); // second container being loaded

  // outputs
  pinMode(D0, OUTPUT); //solenoid

  // inputs
  pinMode(limitSwitchPin, INPUT);
  pinMode(weightButtonPin, INPUT);
  pinMode(distancePin, INPUT);
  pinMode(distanceHalfPin, INPUT);

  Serial.begin(9600);
  analogReadResolution(12);
}

void loop() {
  
  currentButtonState = digitalRead(BTN_USER);
  if(lastButtonState == HIGH && currentButtonState == LOW){
    isRunning = !isRunning;

    if (!isRunning) {
        currentValveState = CLOSED;
        digitalWrite(D0, LOW);
        digitalWrite(LED_D0, LOW);
        digitalWrite(LED_D1, LOW);
        digitalWrite(LED_D2, LOW);
        digitalWrite(LED_D3, LOW);
        Serial.println("System STOPPED by button.");
    }
  }
  lastButtonState = currentButtonState;
  if(isRunning){
    howFull();
    delay(1000);
  }
}

void weightSensor(){
  weight = digitalRead(weightButtonPin);
  if(weight){
    solenoidValve();  
    Serial.println("Car is being loaded");
  }
  else{
    Serial.println("There is no car");
  }
}


void solenoidValve(){
  switchState = digitalRead(limitSwitchPin);
  if(switchState == LOW && weight == HIGH){
    digitalWrite(D0, HIGH);      
    digitalWrite(LED_D3, HIGH); 
    valveStartTime = millis();   
    Serial.println("valve opening - car loading");
    if (switchState == LOW) {
      Serial.println("ERROR: valve still closed ");
    }
    else{
      if (millis() - valveStartTime >= valveDuration) {
        digitalWrite(D0, LOW);       
        digitalWrite(LED_D3, LOW);   
      }
      if (switchState == HIGH) {
        Serial.println("ERROR: valve still open");
      } else {
        Serial.println("valve closing");
      }
    }
  }
  else if(switchState == HIGH && weight == HIGH){
    Serial.println("Error: the valve is not closed");
  }
}


void howFull(){
  distance = digitalRead(distancePin);
  distanceHalf = digitalRead(distanceHalfPin);
  
  if(distance == HIGH && distanceHalf == LOW){
    digitalWrite(LED_D0, HIGH);
    digitalWrite(LED_D1, LOW);
    digitalWrite(LED_D2, LOW);
    Serial.println("container full");
    weightSensor();
  }
  else if(distanceHalf == HIGH){
    digitalWrite(LED_D1, HIGH);
    digitalWrite(LED_D0, LOW);
    digitalWrite(LED_D2, LOW);
    Serial.println("container half full");
    weightSensor();
  }
  else{
    digitalWrite(LED_D2, HIGH);
    digitalWrite(LED_D0, LOW);
    digitalWrite(LED_D1, LOW);
    Serial.println("container almost empty");
  }
}