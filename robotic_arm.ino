
#include <Servo.h>
//Define the pins where the servo motors are attached
#define Base_Servo 8
#define Elbow_Servo 10
#define Shoulder_Servo 9
#define Claw_Servo 11
//Define the variables to control the servo motors
Servo elbow_servo, shoulder_servo, claw_servo, base_servo;
void setup()
{
  //This is the first chunk of code that runs when the program starts
  pinMode(Elbow_Servo, OUTPUT);
  pinMode(Shoulder_Servo, OUTPUT);
  pinMode(Claw_Servo, OUTPUT);
  pinMode(Base_Servo, OUTPUT);
  base_servo.attach(Base_Servo);
  shoulder_servo.attach(Shoulder_Servo);
  elbow_servo.attach(Elbow_Servo);
  claw_servo.attach(Claw_Servo);
  //The code below set the starter position of the arm
  claw_servo.write(30);
  delay(50);
  shoulder_servo.write(30);
  delay(50);
  elbow_servo.write(30);
  delay(50);
  base_servo.write(90);
  delay(50);
  claw_servo.write(70);

  //shoulder_servo.write(0);
  Serial.begin(9600);

  

}

boolean ClawState = true;
int BasePosition = 90, ShoulderPosition = 30, ElbowPosition = 30;
char read;
void BaseRotate();
void Shoulder();
void Elbow();
void Claw();

void loop()
{
  while (!Serial.available());
  read = Serial.read();
  Serial.println(read);
  if (read == 'L' || read == 'R') {
    //When L or R is received, the base will rotate to the left or to the right depending on what was received
    BaseRotate();
  }
  else if (read == 'F' || read == 'B') {
    //When F or B is received, the shoulder will move back and forward depending on what was received
    Shoulder();

  }
  else if (read == 'G' || read == 'H') {
    //When G or H is received, the elbow will move up and down depending on what was received
    Elbow();

  }
  else if (read == 'x' || read == 'X') {
    //When x or X is received, the claw will open or close depending on the state of the claw
    //The "X" character will just toggle the state
    Claw();
  }
  

}
void BaseRotate() {

  if (read == 'R') {

    BasePosition--; //Decrement one the base position
    if (BasePosition < 0) {
      //To avoid negative values
      BasePosition = 0;
    }

    base_servo.write(BasePosition);
    Serial.println(BasePosition);


  }

  else if (read == 'L') {
    BasePosition++; //Increment one the base position
    if (BasePosition > 180) {
      //To avoid an angle bigger than 180 degrees
      BasePosition = 180;

    }
    base_servo.write(BasePosition);

    Serial.println(BasePosition);
  }
}
void Shoulder() {

  if (read == 'F') {
    ShoulderPosition--;
    if (ShoulderPosition < 30) {
      //The smallest shoulder angle to not harm the arm is 30 degrees
      ShoulderPosition = 30;
    }
    shoulder_servo.write(ShoulderPosition);
    Serial.println(ShoulderPosition);
  }
  else if (read == 'B') {
    //The biggest shoulder angle is 120 degrees
    ShoulderPosition++;
    if (ShoulderPosition > 120) {
      ShoulderPosition = 120;
    }
    shoulder_servo.write(ShoulderPosition);
    Serial.println(ShoulderPosition);
  }

}

void Elbow() {
  if (read == 'G') {
    ElbowPosition++;
    if (ElbowPosition > 150) {
      //The biggest Elbow angle to not harm the arm is 150 degrees
      ElbowPosition = 150;
    }
    elbow_servo.write(ElbowPosition);
    Serial.println(ElbowPosition);
  }
  else if (read == 'H') {
    ElbowPosition--;
    if (ElbowPosition < 30) {
      //The smallest Elbow angle to not harm the arm is 30 degrees
      ElbowPosition = 30;
    }
    elbow_servo.write(ElbowPosition);
    Serial.println(ElbowPosition);
  }

}
void Claw() {
  //This function just changes the claw state. If it's closed it will open and vice versa
  ClawState = !ClawState;
  if (ClawState == true) {
    claw_servo.write(30);

  }
  else
    claw_servo.write(70);

}

