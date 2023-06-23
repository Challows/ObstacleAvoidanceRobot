

#include <HCSR04.h> //Library for the Ultrasonic sensor
#include <AFMotor.h> //Motor library
#include <Servo.h>  //Servo motor library

//Code

int trigPin = 52;      // trig pin of HC-SR04 (for signal transmission)
int echoPin = 53;     // Echo pin of HC-SR04 (for signal reception)

long duration;
#define maximum_distance 200
int distance;
int distance1;
int pos = 0;
int distanceRight;
int distanceLeft;
Servo myservo;

HCSR04 sonar(trigPin, echoPin, maximum_distance); //sensor function

AF_DCMotor motor1(3, MOTOR34_64KHZ);
AF_DCMotor motor2(4, MOTOR34_64KHZ);


void setup() {
  
  delay(random(500,2000));   // delay for random time
  Serial.begin(9600);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
  pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT);          //set echo pin as input to capture reflected waves

  myservo.attach(10); //servo pin
  myservo.write(90);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;  

//   
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  Serial.println(duration);
  Serial.println(duration);
  distance = duration / 58.2;
//  distance = readPing();
  Serial.println(distance);
   // convert to distance
  delay(10);
    // If you dont get proper movements of your robot then alter the pin numbers
  if (distance > 18)            
  {
  Serial.println("moving forward");
  motor1.run(FORWARD); //move forward
  motor2.run(FORWARD);                                                       
  }

  else if (distance<19)
  {  
    Serial.println("obstacle detected");
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(500);

    distanceRight = lookRight();
    Serial.println(distanceRight);
   
    delay(300);
    distanceLeft = lookLeft();
    Serial.println(distanceRight);
    delay(300);

    if (distanceRight >= distanceLeft){
      Serial.println("turning right");
      turnLeft();
      delay(200);
      
      moveForward();
    }
    else{
      
      Serial.println("turning left");
      turnRight();
      delay(200);
    }
  }

}

// left and right coding
void turnRight(){
    motor1.run(RELEASE);
    motor2.run(FORWARD);
    delay(1000);

    motor1.run(RELEASE);
    motor2.run(RELEASE);

}

void turnLeft (){
    motor2.run(RELEASE);
    motor1.run(FORWARD);
    delay(1000);
    
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    
  
}
void moveStop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
}
void moveForward(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
void moveBackward(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}
int readPing(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  Serial.println("readping works");
  distance1 = duration / 58.2;
  return distance1;
}
int lookRight(){
  myservo.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(90);
  
  return distance;
  delay(100);
}
int lookLeft(){
  myservo.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(90);
  return distance;
  delay(100);
}
