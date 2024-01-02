//Libraries
#include <Servo.h>
#include <ros.h>

//Motor Controller Variables
#define enAR 4
#define in1R 5
#define in2R 6

#define enAL 7
#define in1L 8
#define in2L 9

//Motor Encoder Variables
#define ENCA_R 12
#define ENCB_R 13
int motorPosR = 0;

#define ENCA_L 10
#define ENCB_L 11
int motorPosL = 0;

//Servo Variables
#define servPin A0
Servo myservo;
int servPos = 0;

//Ultrasonic Sensor Variables
#define trigPin 2
#define echoPin 3
long duration;
int distance;

//Setup
void setup() {

  //Motor Controller Setup
  pinMode(enAR, OUTPUT);
  pinMode(in1R, OUTPUT);
  pinMode(in2R, OUTPUT);
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, LOW);

  pinMode(enAL, OUTPUT);
  pinMode(in1L, OUTPUT);
  pinMode(in2L, OUTPUT);
  digitalWrite(in1L, LOW);
  digitalWrite(in2L, LOW);

  //Motor Encoder Setup
  pinMode(ENCA_R, INPUT);
  pinMode(ENCB_R, INPUT);
  pinMode(ENCA_L, INPUT);
  pinMode(ENCB_L, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA_R), readEncoderR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_L), readEncoderL, RISING);

  //Servo Setup
  myservo.attach(servPin);

  //Ultrasonic Sensor Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Serial Communication
  Serial.begin(9600);
}
void loop() {

  //Motor Encoder Test Code
  Serial.println(motorPosR);
  Serial.println(motorPosL);

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

//Motor Controller Functions
void directionControl() {
  //Set Max Speed
  analogWrite(enAR, 255);
  analogWrite(enAL, 255);

  //Turn Motors On
  digitalWrite(in1R, HIGH);
  digitalWrite(in2R, LOW);

  digitalWrite(in1L, HIGH);
  digitalWrite(in2L, LOW);
  delay(2000);

  //Change Direction 
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, HIGH);

  digitalWrite(in1L, LOW);
  digitalWrite(in2L, HIGH);
  delay(2000);

  //Turn Off
  digitalWrite(in1R, LOW);
  digitalWrite(in2R, LOW);

  digitalWrite(in1L, LOW);
  digitalWrite(in2L, LOW);

}


//Encoder Functions
void readEncoderR(){
  int b = digitalRead(ENCB_R);
  if (b>0) {
    motorPosR++;
  }
  else{
    motorPosR--;
  }
}

void readEncoderL() {
  int b = digitalRead(ENCB_L);
  if (b>0) {
    motorPosL++;
  }
  else {
    motorPosL--;
  }
}