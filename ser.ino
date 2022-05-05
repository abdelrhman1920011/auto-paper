#include <Servo.h>
#define M1 30
#define M2 31
#define Dist 1
Servo servo1;
Servo servo2;

//IR Sensor
int analogPin = A0;
float sensorVal = 0;
float sensorVolt = 0;
float Vr=5.0;
float sum=0;
float k1=16.7647563;
float k2=-0.85803107;
float distance=0;
void setup() {
  // put your setup code here, to run once:
  //DC motor
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  //Water Servo motor
  servo1.attach(8);
  servo2.attach(9);
    // reseting the position of the servo motor
//    servo1.write(0);
//    delay(2000);
//    //forward
//    for (int i = 0; i <= 150; i++){
//      delay(50);
//      servo1.write(i);
//    }
//    delay(1500);
//    //backward
//    for (int j = 150; j >= 0; j--){
//      delay(50);
//      servo1.write(j);
//    }
//    delay(2500);
    //DC motor
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    delay(5000);
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
//      delay(1500);
//      servo2.write(0);
//      delay(2000);
//      servo2.write(75);
//      delay(5000);
//      servo2.write(87);
//      delay(600);
//      servo2.write(90);
    //    servo2.write(65);
    //    delay(1600);
    //    servo2.write(90);
    //    delay(3000);
    //    servo2.write(110);
    //    delay(800);
    //    servo2.write(90);
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
      }
     
    
}
