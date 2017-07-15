#include <Servo.h>

Servo myServoHead, myServoLeft, myServoRight;     //Instances of the three servos

int headServoPin = 10;        //Servo for rotating the cannon head
int leftServoPin = 5;         //Servo of left wheel
int rightServoPin = 6;        //Servo of right wheel

int pos;                      //store current angle
int headPos = 90;             //store current head servo angle 

int LEFT = 12;                //PINs for shooter machine's left motor
int LEFTBRAKE = 9;            
int LEFT_SPEED = 3;           
int RIGHT = 13;               //PINs for shooter machine's right motor
int RIGHTBRAKE = 8;
int RIGHT_SPEED = 11;

int rightSpeed = 100;         //Speed of shooter machine's motor
int leftSpeed = 100;

int IR_LEFT = A2;             //PINs foor IR Sensor
int IR_RIGHT = A3;

int leftValue;                //Store IR Sensor Value
int rightValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServoHead.attach(headServoPin);
  myServoLeft.attach(leftServoPin);
  myServoRight.attach(rightServoPin);
  myServoHead.write(90);
  myServoLeft.write(90);
  myServoRight.write(90);
  
  //pinMode(IR_LEFT, INPUT);
  //pinMode(IR_RIGHT, INPUT);
  
  pinMode(RIGHT, OUTPUT);
  pinMode(RIGHTBRAKE, OUTPUT);

  pinMode(LEFT, OUTPUT);
  pinMode(LEFTBRAKE, OUTPUT);
}

void loop() {

  digitalWrite(LEFT, LOW);                      //Run motors for the shooting machine
  digitalWrite(LEFTBRAKE, LOW);
  analogWrite(LEFT_SPEED, leftSpeed);
  
  digitalWrite(RIGHT, HIGH);
  digitalWrite(RIGHTBRAKE, LOW);
  analogWrite(RIGHT_SPEED, rightSpeed);

                                                //Read IR Value to calculate RPM of shooting machine
  //leftValue = analogRead(IR_LEFT);
  //rightValue = analogRead(IR_RIGHT);

                                                //Print IR Value
  //delay(50);
  //Serial.println(rightValue);
  //Serial.println("Right IR Read: "+ leftValue);
  
  
                                                /*Robot Controls: 
                                                a: rotate left
                                                d: rotate right
                                                w: move forward
                                                s: move backward
                                                l: rotate cannon head left
                                                r: rotate cannon head right
                                                c: resets cannon head to centre*/
  
  if(Serial.available() > 0){
    //String str = Serial.readString();
    char str = Serial.read();
    switch(str){
      case 'a':
        for (pos = 0; pos <= 180; pos += 1) {
          myServoLeft.write(pos);
          myServoRight.write(pos);
          delayMicroseconds(15);
        }
        break;
      case 'd':
        for (pos = 180; pos >= 0; pos -= 1) {
          myServoLeft.write(pos);
          myServoRight.write(pos);
          delayMicroseconds(15);
        }
        break;
      case 'w':
        for (pos = 0; pos <= 180; pos += 1) {
          myServoRight.write(pos);
          delayMicroseconds(15);
        }
        for (pos = 180; pos >= 0; pos -= 1) {
          myServoLeft.write(pos);
          delayMicroseconds(15);
        }
        break;
      case 's':
        for (pos = 0; pos <= 180; pos += 1) {
          myServoLeft.write(pos);
          delayMicroseconds(15);
        }
        for (pos = 180; pos >= 0; pos -= 1) {
          myServoRight.write(pos);
          delayMicroseconds(15);
        }
        break;
      case 'l':
        for (; headPos >= 10; headPos -= 1) {
          myServoHead.write(headPos);
          delayMicroseconds(15);
        }
        break;
     case 'r':
        for (; headPos <= 170; headPos += 1) {
          myServoHead.write(headPos);
          delayMicroseconds(15);
        }
        break;
      case 'c':
        myServoHead.write(90);
        break;
      default:
        myServoLeft.write(0);
        myServoRight.write(0);
        myServoHead.write(headPos);
        break;
    }
    //rightSpeed = str.toInt();
    //leftSpeed = str.toInt();
  }

   //myservo.write(0); 
   //delayMicroseconds(1000);
   //myservo.write(90); 
   //delayMicroseconds(1000); 


  
}
