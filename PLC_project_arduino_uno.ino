// arduino uno

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int OUT_PIN = 11; 
const int HALF_PIN = 8;
void setup() {
  Serial.begin(4800);
  delay(50);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(OUT_PIN, OUTPUT);
  pinMode(HALF_PIN, OUTPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = (duration * 0.0343) / 2; 
  distance = constrain(distance, 0, 255);
  if(distance <= 5){
    digitalWrite(OUT_PIN, LOW);
    digitalWrite(HALF_PIN, HIGH);
    Serial.println("container full"); 
  }
  else if(distance <= 15){
    digitalWrite(HALF_PIN, LOW);
    digitalWrite(OUT_PIN, LOW);
    Serial.println("container half full"); 
  }
  else{
    digitalWrite(OUT_PIN, HIGH);
    digitalWrite(HALF_PIN, HIGH);
    Serial.println("container almost empty");
  }
  delay(1000); 
}
