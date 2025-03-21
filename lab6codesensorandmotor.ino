// Motor A (Right Motor) Pins
const int AIN1 = 13;
const int AIN2 = 12;
const int PWMA = 11;

// Motor B (Left Motor) Pins
const int PWMB = 10;
const int BIN2 = 9;
const int BIN1 = 8;

const int driveTime = 30;  // Time (ms) per inch
const int turnTime = 30;    // Time (ms) per degree

const int trigPin = 7;  
const int echoPin = 6; 
float duration, distance; 


String botDirection;  // Stores direction command
String speedLevel;    // Stores speed level (slow, medium, fast)
int speedValue;       // Stores corresponding speed value

/********************************************************************************/
void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  


  Serial.begin(9600);
  Serial.println("Enter a direction and speed.");
  Serial.println("f = forward, b = backward, r = turn right, l = turn left");
  Serial.println("Speed options: slow, medium, fast");
  Serial.println("Example: f slow");
}

/********************************************************************************/
void loop() {

  if (true) {  // If switch is ON
    if (Serial.available() > 0) {
      botDirection = Serial.readStringUntil(' ');  // Read direction command
      speedLevel = Serial.readStringUntil('\n');  // Read speed level

      // Convert speed level to corresponding speed value
      if (speedLevel == "slow") {
        speedValue = 50;
        Serial.println("Speed is slow");
      } else if (speedLevel == "medium") {
        speedValue = 150;
      } else if (speedLevel == "fast") {
        speedValue = 250;
      } else {
        Serial.println("Invalid speed. Use 'slow', 'medium', or 'fast'.");
        return;  // Exit the loop and wait for a valid input
      }

      Serial.print("Direction: ");
      Serial.print(botDirection);
      delay(2000);
      Serial.print(" | Speed: ");
      Serial.println(speedLevel);

      if (botDirection == "f") {  // Forward
        rightMotor(speedValue);
        leftMotor(speedValue);
       // delay(driveTime * 10);
       
      } 
      else if (botDirection == "b") {  // Backward
        rightMotor(speedValue);
        leftMotor(speedValue);
        //delay(driveTime * 10);
        
      } 
      else if (botDirection == "r") {  // Turn Right
        rightMotor(-speedValue);
        leftMotor(speedValue);
        //delay(turnTime * 90);
        
      } 
      else if (botDirection == "l") {  // Turn Left
        rightMotor(-speedValue);
        leftMotor(speedValue);
        //delay(turnTime * 90);
       
      }
    }
  }
  
  sensor();
}

void sensor() {
   // make sure pin is in low first
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(10);  
  // send out 8 cycle sonic burst from transmitter
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);  

  duration = pulseIn(echoPin, HIGH); 


  distance = (duration*.0343)/2;   

  Serial.print("Distance: ");  
  Serial.println(distance);  

  if (distance < 10)
  {
     rightMotor(0);
     leftMotor(0);
  }  
  delay(2);

}
/********************************************************************************/
void rightMotor(int speed) {
  if (speed > 0) {  // Forward
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else if (speed < 0) {  // Backward
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    speed = -speed;  // Convert to positive for PWM
  } else {  // Stop
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }
  analogWrite(PWMA, speed);
}

/********************************************************************************/
void leftMotor(int speed) {
  if (speed > 0) {  // Forward
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else if (speed < 0) {  // Backward
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    speed = -speed;  // Convert to positive for PWM
  } else {  // Stop
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  analogWrite(PWMB, speed);
}

/********************************************************************************/




