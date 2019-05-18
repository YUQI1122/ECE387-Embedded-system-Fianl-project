#include <Servo.h>
int TrgPin = A0;
int EcoPin = A1;
int dist;
//Threshold for servo motor control with muscle sensor. 
//My threshold value is 600 because my munimum value is around 500 and my maximun value is around 1023 
//When I am relax, my value is close to 500 and when my muscle works,my value will start to increase to 1023
#define THRESHOLD 600

//Pin number where the sensor is connected. (Analog pin 5)
#define EMG_PIN 5

//Pin number where the servo motor is connected. (Digital PWM 3)
#define SERVO_PIN 3

//Define Servo motor
Servo SERVO_1;

void setup(){
  Serial.begin(9600);
  pinMode(TrgPin, OUTPUT);
  pinMode(EcoPin, INPUT);
  //BAUDRATE set to 115200
  //Used this Baud Rate and "NL&CR" option to visualize the values correctly.
  Serial.begin(115200);
  
  //Set servo motor to digital pin 3
  SERVO_1.attach(3);
}


void loop(){

  //The "Value" variable reads the value from the analog pin to which the sensor is connected.
  int value = analogRead(EMG_PIN);

  //If the sensor value is smaller than the THRESHOLD which means I am trying to work but not reach to the top and I might need a help the servo motor will 
  //turn to the 170 degree and devided into 4 step because people need to feel the muscle work
  if(value < THRESHOLD){
    SERVO_1.write(100);
    delay(2000);
    SERVO_1.write(120);
    delay(2000);
    SERVO_1.write(150);
    delay(2000);
    SERVO_1.write(170);
    delay(2000);
  }

  //If the sensor is greater than the THRESHOLD, the servo motor will turn back to 10 degrees because when reach the top, the muscle does not need help.
  //The reason why not go back to 0 is for the safety of the people using this equipment.
  else{
    SERVO_1.write(20);
  }
  //You can use serial monitor to set THRESHOLD properly, comparing the values shown when you open and close your hand.
  Serial.println(value);

  digitalWrite(TrgPin, LOW);
  delayMicroseconds(8);
  digitalWrite(TrgPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrgPin, LOW);
  dist = pulseIn(EcoPin, HIGH) / 58.00;
  Serial.print("Distance:");
  Serial.print(dist);
  Serial.println("cm");
  delay(200);
  if (dist < 5){
    SERVO_1.write(40);
    }
  }



  
