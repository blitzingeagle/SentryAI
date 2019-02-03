#include "MeMegaPi.h"
#include <MeLEDMatrix.h>
#include <MePort.h>
#include <SoftwareSerial.h>

//Timer variables
long currMillis = 0;
long prevMillis = 0;
long currFaceTime = 0;
long prevFaceTime = 0;

//Motor settings
uint8_t motorSpeed = 120;
uint8_t turnSpeedSlow = 40;
uint8_t turnSpeedFast = 100;
uint8_t curServoPos = 20;
uint8_t servoSpeedSlow = 25;
uint8_t servoSpeedFast = 5;
uint8_t laserPin = 2;

//Other
char val;
float dist;
float threshold = 15.00;

void face(char emotion);
void laser(int stat);

Servo servo;  // create servo object to control a servo 
MeMegaPiDCMotor motor1(PORT1B); //Back left wheel
MeMegaPiDCMotor motor2(PORT2B); //Back right wheel

MeUltrasonicSensor ultraSensor(PORT_6);

MeLEDMatrix Matrix_1(PORT_5);

uint8_t Heart[16]= {0x00,0x38,0x3c,0x1e,0x3c,0x38,0x00,0x00,0x00,0x00,0x38,0x3c,0x1e,0x3c,0x38,0x00}; 
uint8_t Happy[16] = {0x00,0x08,0x10,0x20,0x10,0x08,0x00,0x00,0x00,0x00,0x08,0x10,0x20,0x10,0x08,0x00};  
uint8_t Mad[16] = {0x00,0x20,0x10,0x08,0x04,0x00,0x00,0x00, 0x00, 0x00,0x00,0x04,0x08,0x10,0x20,0x00}; 
uint8_t RestL[16] = {0x00,0x1c,0x2e,0x2e,0x22,0x1c,0x00,0x00,0x00,0x00,0x1c,0x2e,0x2e,0x22,0x1c,0x00};
uint8_t RestR[16] = {0x00,0x1c,0x22,0x2e,0x2e,0x1c,0x00,0x00,0x00,0x00,0x1c,0x22,0x2e,0x2e,0x1c,0x00};
uint8_t RestB[16] =
{
  B00000000,
  B00000000,
  B00000000,
  B01000010,
  B00100100,
  B00011000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B01000010,
  B00000000,
  B00000000,
  B00000000
};

void setup()
{
 Matrix_1.setBrightness(Brightness_4);
 Serial.begin(9600);
 Serial.println(val);
 servo.attach(A1);  // attaches the servo on A1
 pinMode(laserPin, OUTPUT);
 
}

void loop()
{
  //Check for input instructions
  if (Serial.available() > 0){
    val = Serial.read();
    Serial.print("Incoming Value: ");
    Serial.println(val);
  }

  //Check to make sure patrol will not run into an obstacle
  dist = ultraSensor.distanceCm();
  if(dist < threshold && val != 's'){
    Serial.println("Yikes! Gotta stop NOW.");
    motor1.stop();
    motor2.stop(); 
    delay(100);
  }
    
  //Set up the neutral mode
  currFaceTime = millis();
  if(currFaceTime - prevFaceTime > 6500){
   prevFaceTime = currFaceTime;
  }
  face('b', currFaceTime, prevFaceTime);

  //Initialize everything upon boot
  if (val == 'i'){
    motor1.run(motorSpeed);
    motor2.run(-motorSpeed); 
    servo.write(curServoPos);
    digitalWrite(laserPin, HIGH);
    delay(10);
    val = 'x';
    digitalWrite(laserPin, LOW);
    face('b', currFaceTime, prevFaceTime);
    delay(50);
  }   

  //Move backward
  else if (val == 's'){
    motor1.run(-motorSpeed);
    motor2.run(motorSpeed); 
  } 
    
  //Patrol Perimter: move forward, turn right
  else if (val== 'd') {    
    motor1.run(turnSpeedFast);
    motor2.run(-turnSpeedSlow);
  }
  
  //Patrol Perimter: move forward, turn left
  else if (val == 'a'){
    motor1.run(turnSpeedSlow);
    motor2.run(-turnSpeedFast);    
  }
  
  //Move forward
  else if (val == 'w'){
    motor1.run(motorSpeed);
    motor2.run(-motorSpeed); 
  }    

  //Pan to the left slowly
  else if (val == 'q'){
    currMillis = millis();
    if (currMillis - prevMillis >= servoSpeedSlow){
      if (curServoPos < 160){
        curServoPos += 1;
        servo.write(curServoPos); 
        prevMillis = currMillis;     
      }      
    }
  }          
  
  //Pan to the right slowly
  else if (val == 'e'){
    currMillis = millis();
    if (currMillis - prevMillis >= servoSpeedSlow){
      if (curServoPos > 20){
        curServoPos -= 1;
        servo.write(curServoPos); 
        prevMillis = currMillis;     
      }      
    }    
  } 

  //Pan to the left quickly
  else if (val == 't'){
    currMillis = millis();
    if (currMillis - prevMillis >= servoSpeedFast){
      if (curServoPos < 160){
        curServoPos += 1;
        servo.write(curServoPos); 
        prevMillis = currMillis;     
      }      
    }
  }          
  
  //Pan to the right quickly
  else if (val == 'y'){
    currMillis = millis();
    if (currMillis - prevMillis >= servoSpeedFast){
      if (curServoPos > 20){
        curServoPos -= 1;
        servo.write(curServoPos); 
        prevMillis = currMillis;     
      }      
    }    
  }

/*
  //Patrol Perimter: move backward, turn right
  if (val== 'o') {    
    motor1.run(-motorSpeed);
    motor2.run(turnSpeed);  
  }
  
  //Patrol Perimter: move backward, turn left
  else if (val == 'p'){
    motor1.run(-turnSpeed);
    motor2.run(motorSpeed);  
  }  
*/

  //Stop
  else if (val == 'x'){
    motor1.stop();
    motor2.stop();  
  }  

  //Threat detected
  else if (val == 'm'){
    face(val, currFaceTime, prevFaceTime);
    digitalWrite(laserPin, HIGH);
    while(val == 'm'){
      currMillis = millis();
      if (currMillis - prevMillis > 200){
        digitalWrite(laserPin, HIGH);
      }
      if (currMillis - prevMillis > 400){
        digitalWrite(laserPin, LOW);
        prevMillis = currMillis;
      }      
      if (Serial.available() > 0){
        val = Serial.read();
        Serial.print("Incoming Value: ");
        Serial.println(val);
      }                 
    }
    digitalWrite(laserPin, LOW);
  }
}

void face(char emotion, long curr, long prev){
  /*case : 1 = rest, 2 = happy, 3 = mad, 4 = sad, 5 = dead, 6 = love*/
  switch(emotion){
    case 'b': if (curr - prev < 3000){Matrix_1.drawBitmap(0,0,sizeof(RestL), RestL);}
              else if (curr - prev < 3250){Matrix_1.drawBitmap(0,0,sizeof(RestB), RestB);}
              else if (curr - prev < 6250){Matrix_1.drawBitmap(0,0,sizeof(RestR), RestR);}
              else if (curr - prev < 6500){Matrix_1.drawBitmap(0,0,sizeof(RestB), RestB);}
              break;
    case 'm': Matrix_1.drawBitmap(0,0,sizeof(Mad), Mad);
              break;
    case 'h': Matrix_1.drawBitmap(0,0,sizeof(Heart), Heart);
              break;
    default:  break;
    
  }
}
