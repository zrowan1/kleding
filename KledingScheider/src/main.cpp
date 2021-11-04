#include <Arduino.h>
#include <Servo.h>

#define S0 9
#define S1 8
#define S2 10
#define S3 11
#define sensorOut 12
#define buzzer 4

Servo servoOne;
Servo servoTwo;

int redValue;
int greenValue;
int blueValue;

enum washColor {Dark, White, Color};

washColor sortedWash;

void chooseColor() 
{
  int frequency = 0;
  // Rode diodes aanzetten om afgelezdn te worden
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Frequency aflezen
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,72,255,0);
  // Printing the value on the serial monitor
//  Serial.print("R= ");//printing name
//  Serial.print(frequency);//printing RED color frequency
//  Serial.print("  ");


    redValue = frequency;

  delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 30,90,255,0);
  // Printing the value on the serial monitor
 // Serial.print("G= ");//printing name
 // Serial.print(frequency);//printing RED color frequency
//  Serial.print("  ");


    greenValue = frequency;
 
  delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 25,70,255,0);
  // Printing the value on the serial monitor
 // Serial.print("B= ");//printing name
 // Serial.print(frequency);//printing RED color frequency
 // Serial.println("  ");

    blueValue = frequency;
 
  delay(100);

}

void chooseWash()
{
  if (redValue < 20 && greenValue < 20 && blueValue < 20)
  {
    sortedWash = Dark;
    Serial.println("Dit hoort bij de donkere was");
    delay(1000);
  }
  else if (redValue > 240 && greenValue > 240 && blueValue > 240)
  {
    sortedWash = White;
    Serial.println("Dit hoort bij de witte was");
    delay(1000);
  }
  else
  {
    sortedWash = Color;
    Serial.println("Dit hoort bij de gekleurde was");
    delay(1000);
  }
}


void setup() {
  // put your setup code here, to run once:

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(buzzer, OUTPUT);


  // frequency-scaling van de kleurensensor op 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // attach de servo's
  servoOne.attach(3);
  servoTwo.attach(2);

  servoOne.write(0);
  servoTwo.write(0);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  chooseColor();

  Serial.print(redValue);
  Serial.print(", ");
  Serial.print(greenValue);
  Serial.print(", ");
  Serial.println(blueValue);

  chooseWash();

  if (sortedWash == White)
  {
    servoOne.write(90);
    servoTwo.write(90);
    delay(2000);
    servoOne.write(0);
    servoTwo.write(0);
    tone(buzzer, 500);
    delay(1500);
    noTone(buzzer);
    delay(1000);

  

  }
  else if (sortedWash == Dark)
  {
    servoOne.write(140);
    servoTwo.write(50);
    delay(2000);
    servoOne.write(0);
    servoTwo.write(0);
    tone(buzzer, 500);
    delay(1500);
    noTone(buzzer);



  }
  else if (sortedWash == Color)
  {
    servoOne.write(30);
    servoTwo.write(170);
    delay(2000);
    servoOne.write(0);
    servoOne.write(0);
    tone(buzzer, 500);
    delay(1500);
    noTone(buzzer);

  }
 

}