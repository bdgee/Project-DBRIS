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
//Has to be interrupt pin
Encoder rightEnc(2, 10);
// #define ENCA_R 10
// #define ENCB_R 11
// volatile int posiR = 0;
long motorPosR = 0;

//Has to be interrupt pin
Encoder leftEnc(3, 11);
// #define ENCA_L 12
// #define ENCB_L 13
// volatile int posiL = 0;
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

  // //Motor Encoder Setup
  // pinMode(ENCA_R, INPUT);
  // pinMode(ENCB_R, INPUT);
  // pinMode(ENCA_L, INPUT);
  // pinMode(ENCB_L, INPUT);
  // attachInterrupt(digitalPinToInterrupt(ENCA_R), readEncoderR, RISING);
  // attachInterrupt(digitalPinToInterrupt(ENCA_L), readEncoderL, RISING);

  //Servo Setup
  myservo.attach(servPin);
  myservo.write(servPos);

  //Ultrasonic Sensor Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Serial Communication
  Serial.begin(115200);
}

void loop() {
  
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

// // //Encoder Functions
// void readEncoderR(){
//   int b = digitalRead(ENCB_R);
//   if (b>0) {
//     motorPosR++;
//   }
//   else{
//     motorPosR--;
//   }
// }

// void readEncoderL() {
//   int b = digitalRead(ENCB_L);
//   if (b>0) {
//     motorPosL++;
//   }
//   else {
//     motorPosL--;
//   }
// }