#include "MeMegaPi.h"
#include <MeLEDMatrix.h>
#include <MePort.h>
#include <SoftwareSerial.h>

MeBluetooth bluetooth(PORT_3);

uint8_t motorSpeed = 150;
uint8_t turnSpeed = 100;
char val;
float dist;

void face(char emotion);
void testMotor();

MeMegaPiDCMotor motor1(PORT1B); //Back left wheel
MeMegaPiDCMotor motor2(PORT2B); //Back right wheel

//MeUltrasonicSensor ultraSensor(PORT_6);

MeLEDMatrix Matrix_1(PORT_5);

uint8_t Heart[16]= {0x00,0x38,0x3c,0x1e,0x3c,0x38,0x00,0x00,0x00,0x00,0x38,0x3c,0x1e,0x3c,0x38,0x00}; 
uint8_t Happy[16] = {0x00,0x08,0x10,0x20,0x10,0x08,0x00,0x00,0x00,0x00,0x08,0x10,0x20,0x10,0x08,0x00}; 
uint8_t Sad[16] = {0x00,0x04,0x08,0x08,0x18,0x00,0x00, 0x00,0x00,0x00,0x00,0x18,0x08,0x08,0x04,0x00}; 
uint8_t Mad[16] = {0x00,0x20,0x10,0x08,0x04,0x00,0x00,0x00, 0x00, 0x00,0x00,0x04,0x08,0x10,0x20,0x00}; 
uint8_t Dead[16] = {0x00,0x22,0x14,0x08,0x14,0x22,0x00,0x00,0x00,0x00,0x22,0x14,0x08,0x14,0x22,0x00};
uint8_t RIP[16] = {0x00,0x7e,0x48,0x4c,0x32,0x00,0x00,0x7e,0x00,0x00,0x7e,0x48,0x48,0x48,0x30,0x00};
uint8_t RestL[16] = {0x00,0x1c,0x2e,0x2e,0x22,0x1c,0x00,0x00,0x00,0x00,0x1c,0x2e,0x2e,0x22,0x1c,0x00};
uint8_t RestR[16] = {0x00,0x1c,0x22,0x2e,0x2e,0x1c,0x00,0x00,0x00,0x00,0x1c,0x22,0x2e,0x2e,0x1c,0x00};

void setup()
{
 Matrix_1.setBrightness(Brightness_4);//
 Serial.begin(115200);
}

void loop()
{
  face('1');
    
  if (Serial.available()){
    val = Serial.read();
    Serial.println(val);
  }

  //Patrol Perimter: move forward, turn right
  if (val== 'r') {    
    motor1.run(motorSpeed);
    motor2.run(-turnSpeed);
  }
  
  //Patrol Perimter: move forward, turn left
  else if (val == 'l'){
    motor1.run(turnSpeed);
    motor2.run(-motorSpeed);    
  }
  
  //Move forward
  else if (val == 'f'){
    motor1.run(motorSpeed);
    motor2.run(-motorSpeed); 
  }  

  //Move backward
  else if (val == 'b'){
    motor1.run(-motorSpeed);
    motor2.run(motorSpeed); 
  }   
   
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
  //Stop
  else if (val == 's'){
    motor1.stop();
    motor2.stop();  
  }  
  /*
  if (val== 'x') { //move forwards
      motor1.run(motorSpeed);
      motor2.run(-motorSpeed);
      delay(1000); 
      motor2.stop();
      motor1.stop(); 
    }
    
  else if (val== 'y') { // move backwards

    motor1.run(-motorSpeed);
    motor2.run(motorSpeed);
    delay(1000); 
    motor2.stop();
    motor1.stop(); 
  }
  
  else if (val== 'q') { //turn left and move forward
    motor1.run(-motorSpeed);
    motor2.run(-motorSpeed);
    delay(2200);
    motor2.stop();
    motor1.stop();
    motor1.run(motorSpeed);
    motor2.run(-motorSpeed);
    delay(1000); 
    motor2.stop();
    motor1.stop(); 
  }

  face('1');
  */
}

void testMotor(){
  
    face('p');
    //turn left
    motor1.run(-motorSpeed);
    motor2.run(motorSpeed);
    delay(1000);
    motor1.stop();  
    motor2.stop();
    delay(500);
    
    //move forwards
    motor1.run(motorSpeed);
    motor2.run(-motorSpeed);
    delay(1000);
    motor1.stop();
    motor2.stop();
    delay(500);

    //turn right
    motor1.run(motorSpeed);
    motor2.run(motorSpeed);
    delay(550);
    motor1.stop();
    motor2.stop();
    delay(500);

    //turn left
    motor1.run(-motorSpeed);
    motor2.run(-motorSpeed);
    delay(750);
    motor1.stop();
    motor2.stop();
    delay(500);

   //stop the demo
   int x = 1;
   while(x){
    continue;
   }

}

void face(char emotion){
  /*case : 1 = rest, 2 = happy, 3 = mad, 4 = sad, 5 = dead, 6 = love*/
  switch(emotion){
    case '1': Matrix_1.drawBitmap(0,0,sizeof(RestL), RestL);
              delay(500);
              Matrix_1.drawBitmap(0,0,sizeof(RestR), RestR); 
              delay(500); 
              break;
    case '2': Matrix_1.drawBitmap(0,0,sizeof(Happy), Happy);
              break;
    case '3': Matrix_1.drawBitmap(0,0,sizeof(Mad), Mad);
              break;
    case 'p': Matrix_1.drawBitmap(0,0,sizeof(Sad), Sad);
              break;
    case '5': Matrix_1.drawBitmap(0,0,sizeof(Dead), Dead);
              delay(1000);
              Matrix_1.drawBitmap(0,0,sizeof(RIP), RIP);
              delay(1000);
              Matrix_1.drawBitmap(0,0,sizeof(Dead), Dead);
              delay(1000);
              Matrix_1.drawBitmap(0,0,sizeof(RIP), RIP);
              delay(1000);
              break;
    case 'h': Matrix_1.drawBitmap(0,0,sizeof(Heart), Heart);
              break;
    default:  break;
    
      }
  }

void blink(){
    
  for(uint8_t i=4;i>0;i--)
  {
    Matrix_1.setBrightness(i);
    delay(50);
  }
  
  for(uint8_t i=0;i<4;i++)
  {
    Matrix_1.setBrightness(i);
    delay(50);
  }
}
