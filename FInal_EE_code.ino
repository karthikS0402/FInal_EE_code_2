#include <MeMCore.h>

MeLineFollower LF(PORT_1);
MeUltrasonicSensor US(PORT_3);
MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

#define IR_input 9
#define force_input A0
#define LEDpin 10

int distance; 
int line_status;
int count = 1;
int obstacle_count = 0;

void LineFollower() {
  // Serial.println(line_status);
  //   switch (line_status) {
  //       case 0: //both white
  //           motorLeft.run(-100);
  //           motorRight.run(105);
  //           break;
  //       case 1: //left turn 
  //           motorLeft.stop();
  //           motorRight.run(105);
  //           break;
  //       case 2: //right turn
  //           motorRight.stop();
  //           motorLeft.run(-150);
  //           break;
  //       case 3: //both black
  //           motorLeft.run(150);
  //           motorRight.run(155);
  //           break;
  //   }
  } 

void moveForward() {
  motorLeft.run(170);
  motorRight.run(-170);
}

void stopMotors(){
  motorLeft.stop();
  motorRight.stop();
}

void slow_left_turn(){
  while(line_status == 1 || line_status == 2){
    line_status = LF.readSensors();
    motorLeft.run(150);
    motorRight.run(150);
  }
  
}

void slow_right_turn() {
  while(line_status == 1 || line_status == 2){
    line_status = LF.readSensors();
    motorLeft.run(-150);
    motorRight.run(-150);
  }
}

void leftTurn() {
  motorLeft.run(500);
  motorRight.run(500);
  delay(300);
  stopMotors();
  delay(290);
  moveForward();
}

void leftTurn2() {
  motorLeft.run(500);
  motorRight.run(500);
  delay(350);
  stopMotors();
  delay(300);
  moveForward();
}

void rightTurn() {
  motorLeft.run(-500);
  motorRight.run(-500);
  delay(300);
  stopMotors();
  delay(290);
  moveForward();
}

void  rightTurn2() {
  motorLeft.run(-500);
  motorRight.run(-500);
  delay(300);
  stopMotors();
  delay(300);
  moveForward();

}

void evenObstacle() {
  leftTurn();
  moveForward();
  delay(400);
  rightTurn();
  moveForward();
}

void oddObstacle() {
  rightTurn();
  moveForward();
  delay(400);
  leftTurn();
  moveForward();
}

void lawnmower() {
  line_status = LF.readSensors();
  distance = US.distanceCm();
  if (distance < 5){
    return;
  }
  moveForward();
  if (line_status == 0) {
    if (count < 7){
      if (count%2 == 1) {
      leftTurn();
      delay(100);
      moveForward();
      delay(200);
      leftTurn2();
      count ++;
      Serial.println(count);
    } else if (count%2 == 0){
      rightTurn();
      delay(100);
      moveForward();
      delay(200);
      rightTurn2();
      count ++;
      Serial.println(count);
    }  

  }
    
  else{
    while (count >= 7){
    int Line_Status = LF.readSensors();
    int LED_status = digitalRead(LEDpin);
    Serial.println(Line_Status);
    switch (Line_Status) {
        case 0: //both black
        
          Serial.println("Case 0");
            motorLeft.run(100);
            motorRight.run(-105);
            if (LED_status == 0){
              stopMotors();
              break;
            }
            break;
        case 1: //left turn 
          Serial.println("Case 1");
            motorLeft.stop();
            motorRight.run(105);
            break;
        case 2: //right turn
        Serial.println("Case 2");
            motorRight.stop();
            motorLeft.run(-150);
            break;
        case 3: //both white
        Serial.println("Case 3");
            motorLeft.run(150);
            motorRight.run(155);
            break;  
    }
  }
  delay(10000);
  stopMotors();

  }
    
}
}

    
//}


void setup() {
  Serial.begin(9600);
  pinMode(force_input,INPUT);
  pinMode(LEDpin, INPUT);
  

}

void loop() {
  //lawnmower();
  distance = US.distanceCm();
  Serial.println(distance);
  while (distance > 5) {
    lawnmower();
  }  
  if (distance < 7 && obstacle_count != 0){
    leftTurn();
    count++;
  } else if (distance < 5 && obstacle_count == 0){
    if (count%2 == 0){
      evenObstacle();
      obstacle_count++;    
    } else {
      oddObstacle();
      obstacle_count++;
    }
       
   //}
}
}
  // line_status = LF.readSensors();

  // if (line_status != 0) {
  //   moveForward();
  // } else {
  //   if (count%2 == 1) {
  //     leftTurn();
  //     delay(200);
  //     moveForward();
  //     delay(100);
  //     leftTurn2();
  //     count ++;
  //     } else {
  //       LineFollower();
  //     }
  
  //   // } else {
  //   //   if (count !=5) {
  //   //   rightTurn();
  //   //   delay(200);
  //   //   moveForward();
  //   //   delay(100);
  //   //   rightTurn2();
  //   //   count ++;
  //   //   } else {
  //   //     LineFollower();
  //   //   }
      
   //}
    

   //}

//}




  
  
  



