#include <SoftWire.h>

#define K2230_ADDR 0x68
SoftWire mywire(2, 3); // Ensure to use the same variable name as defined above
int Buzzer = 12;
int touch_pin=5;
int state;
int angle(int16_t &gyroX, int16_t &gyroY, int16_t &gyroZ) {  // Pass by reference
    if (mywire.available() == 6) {  // Use 'mywire', not 'myWire'
        gyroX = mywire.read() | (mywire.read() << 8);
      //  gyroY = mywire.read() | (mywire.read() << 8);
        gyroZ = mywire.read() | (mywire.read() << 8);
    }

    float angleX = gyroX * 0.00875;
   // float angleY = gyroY * 0.00875;
    float angleZ = gyroZ * 0.00875;

    for(int i=1;i<=10;i++)
    {
      delay(1000);
      mywire.beginTransmission(K2230_ADDR);
      mywire.write(0x28 | 0x80);
      mywire.endTransmission();
      mywire.requestFrom(K2230_ADDR, 6);
      if (mywire.available() == 6) 
      {
        gyroX = mywire.read() | (mywire.read() << 8);
        //gyroY = mywire.read() | (mywire.read() << 8);
        gyroZ = mywire.read() | (mywire.read() << 8);
      }

      float angleX = gyroX * 0.00875;
     // float angleY = gyroY * 0.00875;
      float angleZ = gyroZ * 0.00875;
        if (angleX <10 && (angleZ<-10 || angleZ>10)) 
          {
            return 0;
          }
    }
    return 1;
}

void setup() {
    pinMode(touch_pin, INPUT);
    mywire.begin();  // Correct the usage to 'mywire'
    mywire.beginTransmission(K2230_ADDR);
    mywire.write(0x20);
    mywire.write(0x0F);
    mywire.endTransmission();

    pinMode(Buzzer, OUTPUT);
}

void loop() {
    int16_t gyroX, /*gyroY, */gyroZ;
    state=digitalRead(touch_pin);
    if(state==HIGH){
      mywire.beginTransmission(K2230_ADDR);
      mywire.write(0x28 | 0x80);
      mywire.endTransmission();
      mywire.requestFrom(K2230_ADDR, 6);
      while (angle(gyroX, /*gyroY,*/ gyroZ) == 0) {
          tone(Buzzer, 300);
          delay(500);
          angle(gyroX, gyroY, gyroZ); 
      }
      noTone(Buzzer);
    }
}
