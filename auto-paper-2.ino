#include <Servo.h>
Servo servo1;
Servo servo2;

//Blender DC motor and locomotion
#define M1pin1 30
#define M1pin2 31
#define M2pin1 32
#define M2pin2 33
#define M3pin1 34
#define M3pin2 35

//color sensor defines
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define LED 3
#define sensorOut 2


//IR Sensor
int analogPin = A0;
float sensorVal = 0;
float sensorVolt = 0;
float Vr=5.0;
float sum=0;
float k1=16.7647563;
float k2=-0.85803107;
float distance=0;


//TCS3200
// Calibration Values
// *Get these from Calibration Sketch
int redMin = 460; // Red minimum value
int redMax = 69; // Red maximum value
int greenMin = 520; // Green minimum value
int greenMax = 89; // Green maximum value
int blueMin = 445; // Blue minimum value
int blueMax = 79; // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

void setup() {
  //water container
  servo1.attach(24);
  
  //paper container
  servo2.attach(11);
  servo2.write(180);

  waterPouring();
  
  //blender DC motor
  pinMode(M1pin1, OUTPUT);
  pinMode(M1pin2, OUTPUT);
  BlenderDCMotor();
  
  mainContainer();

  //locomotion of the net
  pinMode(M2pin1, OUTPUT);
  pinMode(M2pin2, OUTPUT);
  Locomotion();

  //color sensor pinmodes 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(LED, OUTPUT);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(LED, HIGH);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void loop() {
  char in = Serial.read();
  //taking input from the user. d is for measuring thickness, while c is for measuring color RGB.
      switch(in){
        case 'd':
          sum=0;
          for (int i=0; i<100; i++)
          {
            sum=sum+float(analogRead(analogPin));  
          }
          sensorVal=sum/100;
          sensorVolt=sensorVal*Vr/1024;
         
          distance = pow(sensorVolt*(1/k1), 1/k2);
          int distance1 = 13 - distance; 
          Serial.println(distance1);
          delay(500);
          if (distance1 > 1.2){Serial.print ("increase volume of water");}
          else if(distance < 0.8) {Serial.print ("decrease volume of water");}
          break;
          //colorsensor
        case 'c':
          // Read Red value
          redPW = getRedPW();
          // Map to value from 0-255
          redValue = map(redPW, redMax,redMin,255,0);
          // Delay to stabilize sensor
          delay(200);
        
          // Read Green value
          greenPW = getGreenPW();
          // Map to value from 0-255
          greenValue = map(greenPW, greenMax,greenMin,255,0);
          // Delay to stabilize sensor
          delay(200);
        
          // Read Blue value
          bluePW = getBluePW();
          // Map to value from 0-255
          blueValue = map(bluePW, blueMax,blueMin,255,0);
          // Delay to stabilize sensor
          delay(200);
        
          // Print output to Serial Monitor
          Serial.print("Red = ");
          Serial.print(redPW);
          Serial.print(" - Green = ");
          Serial.print(greenPW);
          Serial.print(" - Blue = ");
          Serial.println(bluePW);
          break;
        }  
}

//for the servo that pours the water into the main container
void waterPouring(){
  // reseting the position of the servo motor
    servo1.write(180);
    delay(2000);
    //pouring the water in the container of the paper, waiting 5 seconds and then returnin back
    for (int i =180; i >= 75; i--){
      delay(60);
      servo1.write(i);
    }
    delay(5000);
    for (int j = 75; j <= 180; j++){
      delay(60);
      servo1.write(j);
    }
    delay(2500);
}

void BlenderDCMotor(){
    delay(3000);
    //rotating the blender motor in order to blend the water within the water.
    digitalWrite(M1pin1, HIGH);
    digitalWrite(M1pin2, LOW);
    delay(3000);
    //delay(1800000);
    digitalWrite(M1pin1, LOW);
    digitalWrite(M1pin2, LOW);
}

void mainContainer(){
    servo2.write(0); 
    //forward
    for (int i = 180; i >= 70; i--){
      delay(50);
      servo2.write(i);
    }
    delay(2500);
    for (int j = 70; j <= 180; j++){
      delay(60);
      servo2.write(j);
    }
    delay(2500);
}
void Locomotion(){
  // to the box
  digitalWrite(M2pin1, LOW);
  digitalWrite(M2pin2, HIGH);
  digitalWrite(M3pin1, LOW);
  digitalWrite(M3pin2, HIGH);
  delay(3200);
  digitalWrite(M2pin1, LOW);
  digitalWrite(M2pin2, LOW);
  digitalWrite(M3pin1, LOW);
  digitalWrite(M3pin2, LOW);
  //1 hour delay for the process of paper drying, where 1 hour contains 3.6*10^6 milliseconds. 
  delay(3600000);
  // out of the box
  digitalWrite(M2pin1, LOW);
  digitalWrite(M2pin2, HIGH);
  digitalWrite(M3pin1, HIGH);
  digitalWrite(M3pin2, LOW);
  delay(3200);
  digitalWrite(M2pin1, LOW);
  digitalWrite(M2pin2, LOW);
  digitalWrite(M3pin1, LOW);
  digitalWrite(M3pin2, LOW);
}

// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}
