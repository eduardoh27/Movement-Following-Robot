
//include the library code:
//#include<NewPing.h>           
#include<Servo.h>             
#include<AFMotor.h>             

/*
#define RIGHT A2              // Right IR sensor connected to analog pin A2 of Arduino Uno:
#define LEFT A3               // Left IR sensor connected to analog pin A3 of Arduino Uno:
#define TRIGGER_PIN A1        // Trigger pin connected to analog pin A1 of Arduino Uno:
#define ECHO_PIN A0           // Echo pin connected to analog pin A0 of Arduino Uno:
#define MAX_DISTANCE 200      // Maximum ping distance:

unsigned int distance = 0;    //Variable to store ultrasonic sensor distance:
unsigned int Right_Value = 0; //Variable to store Right IR sensor value:
unsigned int Left_Value = 0;  //Variable to store Left IR sensor value:
*/

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //NewPing setup of pins and maximum distance:

//create motor objects
AF_DCMotor Motor1(1,MOTOR12_1KHZ); // delantera derecha / negro esquina
AF_DCMotor Motor2(2,MOTOR12_1KHZ); // trasera derecha / negro esquina
//AF_DCMotor Motor3(3,MOTOR34_1KHZ); // delantera izquierda / amarillo esquina
AF_DCMotor Motor4(4,MOTOR34_1KHZ); // trasera izquierda


Servo myservo; //create servo object to control the servo:
int pos=0;     //variable to store the servo position:


void setup() { // the setup function runs only once when power on the board or reset the board:
  
   Serial.begin(9600); //initailize serial communication at 9600 bits per second:

   myservo.attach(10); // servo attached to pin 10 of Arduino UNO
   
  {
  for(pos = 90; pos <= 180; pos += 1){    // goes from 90 degrees to 180 degrees:
    myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
    delay(15);                            //wait 15ms for the servo to reach the position:
    } 
  for(pos = 180; pos >= 0; pos-= 1) {     // goes from 180 degrees to 0 degrees:
    myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
    delay(15);                            //wait 15ms for the servo to reach the position:
    }
  for(pos = 0; pos<=90; pos += 1) {       //goes from 180 degrees to 0 degrees:
    myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
    delay(15);                            //wait 15ms for the servo to reach the position:
    }
  }

  }





void loop() {

  //Serial.println("initial 3 secs delay");
  //delay(1000);

  Serial.println("forward:");
  //delay(1000);
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(FORWARD);   //rotate motor1 clockwise:
  Motor2.setSpeed(150);  //define motor1 speed:
  Motor2.run(FORWARD);   //rotate motor1 clockwise:
  //Motor3.setSpeed(150);  //define motor1 speed:
  //Motor3.run(FORWARD); 
  Motor4.setSpeed(150);  //define motor1 speed:
  Motor4.run(FORWARD); 

  Serial.println("5 secs delay");
  
  delay(1000);

  Serial.println("\n");
  
}



