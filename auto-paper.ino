#include <Servo.h>
#define M1 30
#define M2 31
#define Dist 1
Servo servo1;
Servo servo2;

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
  // put your setup code here, to run once:
  //DC motor
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  //Water Servo motor
  servo1.attach(8);
  servo2.attach(9);
  servo2.write(180);
    // reseting the position of the servo motor
    servo1.write(0);
    delay(2000);
    //forward
    for (int i = 0; i <= 150; i++){
      delay(50);
      servo1.write(i);
    }
    delay(1500);
    //backward
    for (int j = 150; j >= 0; j--){
      delay(50);
      servo1.write(j);
    }
    delay(2500);
    //DC motor
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    delay(5000);
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
      delay(1500);
      servo2.write(100);
      delay(2000);
      servo2.write(90);
      delay(5000);
      servo2.write(80);
      delay(2000);
     servo2.write(90);
        servo2.write(65);
        delay(1600);
        servo2.write(90);
        delay(3000);
        servo2.write(110);
        delay(800);
        servo2.write(90);
        //forward
    for (int i = 0; i <= 150; i++){
      delay(50);
      servo2.write(i);
    }
    delay(2500);
    //backward
    for (int j = 150; j >= 0; j--){
      delay(50);
      servo2.write(j);
    }

//color sensor
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
  // put your main code here, to run repeatedly:
      char in = Serial.read();
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
          Serial.println(distance-1);
          delay(500);
//          if (distance > x){Serial.print ("increase volume of water")}
//          else if(distance =< x) {Serial.print ("decrease volume of water")}
          //colorsensor

          {
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
      }
    
    
}
