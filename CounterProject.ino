#include<LiquidCrystal.h>
const int echo1 = 11; // Echo Pin of Ultrasonic Sensor 1
const int echo2 = 12; // Echo Pin of Ultrasonic Sensor 2
long t1, t2, cm1, cm2, u1=0, u2=0;
long state=0, count=0, h=240, lim=50;
LiquidCrystallcd(1,2,4,5,6,7);
long readDuration(int triggerPin, int echoPin)
{ 
pinMode(triggerPin, OUTPUT); // Clear the trigger 
digitalWrite(triggerPin, LOW);
delayMicroseconds(2);
 // Sets the trigger pin to HIGH state for 10 microseconds
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(triggerPin, LOW);
pinMode(echoPin, INPUT);
/* Reads the echo pin, and returns the sound wave travel time 
in microseconds*/
 return pulseIn(echoPin, HIGH);
} 
long dist(long microS) 
{ 
 return microS*0.017;
} 
void display()
{ 
lcd.begin(16,2);
lcd.clear();
 if (count<lim)
 { 
lcd.print("No. of people in the room");
lcd.setCursor(0,1);
lcd.print(count);
 } 
 else
 { 
lcd.print("MAXIMUM CAPACITY");
 } 
} 
20
void State()
{ 
if(u1==1 && u2==0)
{ 
 if(state!=13) //13 is exit motion, 31 is entry motion
 state=31;
 if(state==13)
 { 
 state=0;
 count--; 
delay(1000);
 } 
} 
if(u1==0 && u2==1)
 { 
 if(state!=31)
 state=13;
 if(state==31)
 { 
 state=0;
 count++;
delay(1000);
 } 
 } 
} 
void setup()
{ 
 //Serial.begin(9600);
} 
void loop() 
{ 
 t1 = readDuration(echo1, echo1);
 t2 = readDuration(echo2, echo2);
 cm1 = dist(t1);
 cm2 = dist(t2);
 if(cm1<(0.75*h))
 u1=1;
 else 
 u1=0;
 if(cm2<(0.75*h))
 u2=1;
 else
 u2=0;
State();
display();
delay(500);
}
