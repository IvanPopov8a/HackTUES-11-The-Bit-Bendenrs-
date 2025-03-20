#include <Ultrasonic.h>
int Buzzer = 12;
int trig_pin=8;
int echo_pin=9;
int distance=0;
Ultrasonic ultrasonic(8, 9);
int wait_Up(){
  for(int i=1;i<=5;i++){
      delay(1000); 
      distance = ultrasonic.read();
      	if(distance<=10){
        	return 1;
        }
  } 
  return 0;
}
void setup()
{
  pinMode(Buzzer, OUTPUT);
  pinMode(echo_pin,INPUT);
  pinMode(trig_pin,OUTPUT);
  digitalWrite(trig_pin,LOW);
}
void loop()
{
  distance = ultrasonic.read();
  delay(1000);
  if(distance<10){
    if(wait_Up() == 0)
    {
      do{
  		tone(Buzzer, 300);
    	delay(500);
    	distance = ultrasonic.read();
      }while(distance<=10);
      noTone(Buzzer);
    }
  }
}