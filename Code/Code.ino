//Libraries
#include <Servo.h>
#include <util/atomic.h>
#include <Encoder.h>
#include <NewPing.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

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
#define maxDistance 100
// long duration;
// int distance;

//Accelerometer Variables
MPU6050_tockn mpu6050(Wire);
long timer = 0;

NewPing sonar(trigPin, echoPin, maxDistance);

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
  // pinMode(trigPin, OUTPUT);
  // pinMode(echoPin, INPUT);

  //Accelerometer
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  //Serial Communication
  Serial.begin(115200);
  while(!Serial) {}
}

void loop() {
  delay(50);
  
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

  // //Ultrasonic Sensor Test Code
  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // // Sets the trigPin on HIGH state for 10 micro seconds
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  // // Reads the echoPin, returns the sound wave travel time in microseconds
  // duration = pulseIn(echoPin, HIGH);
  // // Calculating the distance
  // distance = duration * 0.034 / 2;

  unsigned int uS = sonar.ping();
  Serial.println(sonar.convert_cm(uS));
  
  //Prints data to serial monitor
  //Serial.println(data);

  mpu6050.update();

  if(millis() - timer > 1000){
    
    Serial.println("=======================================================");
    Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    Serial.print("	accY : ");Serial.print(mpu6050.getAccY());
    Serial.print("	accZ : ");Serial.println(mpu6050.getAccZ());
  
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("	gyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("	gyroZ : ");Serial.println(mpu6050.getGyroZ());
  
    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    Serial.print("	accAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
    Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
    Serial.print("	gyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
    Serial.print("	gyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
    
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("	angleY : ");Serial.print(mpu6050.getAngleY());
    Serial.print("	angleZ : ");Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================");
    timer = millis();

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