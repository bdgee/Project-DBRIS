//Libraries
#include <Servo.h>
#include <util/atomic.h>
#include <Encoder.h>

//Motor Controller Variables
#define in1R 4
#define in2R 5
//Has to be PWM pin
#define enAR 6

#define in1L 8
#define in2L 9
//Has to be PWM pin
#define enAL 7

//Motor Encoder Variables
//Has to have some interrupt pins (2,3)

#define ENCA_R 2
#define ENCB_R 10
Encoder rightEnc(ENCA_R, ENCB_R);
long motorPosR = 0;

#define ENCA_L 3
#define ENCB_L 11
Encoder leftEnc(ENCA_L, ENCB_L);
long motorPosL = 0;

//Servo Variables
#define servPin A0
Servo myservo;
int servPos = 0;

//Ultrasonic Sensor Variables
#define trigPin 12
#define echoPin 13
long duration;
int distance;

//Output to the serial Monitor
String data[3];

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

  //Servo Setup
  myservo.attach(servPin);
  myservo.write(servPos);

  //Ultrasonic Sensor Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Serial Communication
  Serial.begin(115200);
  while(!Serial) {}
}

void loop() {
  
  //Checks for commands in serail monitor
  if (Serial.available()>0) {
    String commands = Serial.readStringUntil('\n');
  }

  //Motor Controller Test Code
  setMotor(1, 200, enAR, in1R, in2R);
  setMotor(1, 200, enAL, in1L, in2L);

  //Motor Encoder Test Code 
  long newRight, newLeft;
  newRight = rightEnc.read();
  newLeft = leftEnc.read();

  if (newLeft != motorPosL || newRight != motorPosR) {
    motorPosR = newRight;
    motorPosL = newLeft;
  }

  Serial.println(motorPosR);
  Serial.println(motorPosL);

  //Servo Test Code
  servPos =  (servPos+1)%120;
  myservo.write(servPos);

  //Ultrasonic Sensor Test Code
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
  Serial.println("Distance: " + String(distance));
}

//Motor Controller Functions
void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm, pwmVal);
  if (dir == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if (dir == -1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}