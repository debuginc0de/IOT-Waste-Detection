#include <Servo.h>

// Define pins
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 5;
const int echoPin2 = 4;
const int ledPin = 6;
const int thresholdDistance = 10;
const int binFullDistance = 7;    

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ledPin, OUTPUT);

  servoMotor.attach(13);
  servoMotor.write(0); 
}

long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1; 
  return distance;
}

void loop() {
  long distance1 = getDistance(trigPin1, echoPin1); 
  long distance2 = getDistance(trigPin2, echoPin2); 

  Serial.print("Lid Distance: ");
  Serial.print(distance1);
  Serial.print(" cm, Waste Level Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");

  if (distance1 <= thresholdDistance) {
    servoMotor.write(180); 
  } else {
    servoMotor.write(0);  
  }

  if (distance2 <= binFullDistance) {
    digitalWrite(ledPin, HIGH); 
  } else {
    digitalWrite(ledPin, LOW);  
  }

  delay(500);
}

