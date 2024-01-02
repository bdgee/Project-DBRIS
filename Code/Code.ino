//Libraries
#include <Servo.h>

//Motor Encoder Variables
#define ENCA_R 12
#define ENCB_R 13
#define ENCA_L 10
#define ENCB_L 11
int motorPosR = 0;
int motorPosL = 0;


//Servo Variables
Servo myservo;
const int servPin = 3;
int servPos = 0;

//Ultrasonic Sensor Variables
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

//Setup
void setup() {

  //Motor Encoder Setup
  pinMode(ENCA_R, INPUT);
  pinMode(ENCB_R, INPUT);
  pinMode(ENCA_L, INPUT);
  pinMode(ENCB_L, INPUT);


  //Servo Setup
  myservo.attach(servPin);

  //Ultrasonic Sensor Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Serial Communication
  Serial.begin(9600);
}
void loop() {

  //Servo Test Code
  for (servPos = 0; servPos <= 180; servPos += 1) {
    myservo.write(servPos);
    Serial.println(servPos);
    delay(15);
  }
  for (servPos = 180; servPos >= 0; servPos -= 1) { 
    myservo.write(servPos);
    Serial.println(servPos);
    delay(15);
  }

  //Ultrasonic Sensor Test Code
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);



}