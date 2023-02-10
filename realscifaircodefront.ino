// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int TrigPin1 = 0;
int EchoPin1 = 1;
int TrigPin2 = 3;
int EchoPin2 = 4;
int TrigPin3 = 5;
int EchoPin3 = 6;
int TrigPin4 = 7;
int EchoPin4 = 8;
int TrigPin5 = 9;
int EchoPin5 = 10;
int TrigPin6 = 11;
int EchoPin6 = 12;
int BuzzerPin = 2;
int TrigPin7 = A0;
int EchoPin7 = A1;
long duration1;
long duration2;
long duration3;
long duration4;
long duration5;
long duration6;
long duration7;
int distance1;
int distance2;
int distance3;
int distance4;
int distance5;
int distance6;
int distance7;
long duration1b;
long duration2b;
long duration6b;
long duration7b;
int distance1b;
int distance2b;
int distance6b;
int distance7b;
int elapsed1;
int elapsed2;
int elapsed6;
int elapsed7;
int elapsedb;
int elapsed;
int maindist;
int objspeed;
int time2impact;
int maindist2;
int impact;
int sx;
int csx;
int time1;
int time2;
int timing;

int16_t accelerometer_x, accelerometer_x1; // variables for accelerometer raw data
char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(TrigPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(TrigPin3, OUTPUT);
  pinMode(EchoPin3, INPUT);
  pinMode(TrigPin4, OUTPUT);
  pinMode(EchoPin4, INPUT);
  pinMode(TrigPin5, OUTPUT);
  pinMode(EchoPin5, INPUT);
  pinMode(TrigPin6, OUTPUT);
  pinMode(EchoPin6, INPUT);
  pinMode(TrigPin7, OUTPUT);
  pinMode(EchoPin7, INPUT);
  pinMode(BuzzerPin, OUTPUT);
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_x = (accelerometer_x * 0.59820565/521);
  time2=millis();
  accelerometer_x1 = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_x1 = (accelerometer_x1 * 0.59820565/521);
  timing = (time2-time1);
  Serial.print(timing);
  csx = (((accelerometer_x + accelerometer_x1)/2)*timing);
  sx = (sx + csx);
  time1=millis();
  /*
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  */
  // print out data
  Serial.println("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  //Serial.println(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]

  elapsed1 = millis();
        digitalWrite(TrigPin1, LOW);
        delayMicroseconds(5);
        digitalWrite(TrigPin1, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin1, LOW);
        duration1 = pulseIn(EchoPin1, HIGH);
        distance1 = duration1 * 0.034/2; //cm
        elapsed2 = millis();
        digitalWrite(TrigPin2, LOW);
        delayMicroseconds(5);
        digitalWrite(TrigPin2, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin2, LOW);
        duration2 = pulseIn(EchoPin2, HIGH);
        distance2 = duration2 * 0.034/2; //cm

        digitalWrite(TrigPin3, LOW);
        delayMicroseconds(5);
        digitalWrite(TrigPin3, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin3, LOW);
        duration3 = pulseIn(EchoPin3, HIGH);
        distance3 = duration3 * 0.034/2 ;//cm

        digitalWrite(TrigPin4, LOW);
        delayMicroseconds(5);
        digitalWrite(TrigPin4, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin4, LOW);
        duration4 = pulseIn(EchoPin4, HIGH);
        distance4 = duration4 * 0.034/2; //cm

        digitalWrite(TrigPin5, LOW);
        delayMicroseconds(5);
        digitalWrite(TrigPin5, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin5, LOW);
        duration5 = pulseIn(EchoPin5, HIGH);
        distance5 = duration5 * 0.034/2 ;//cm
        elapsed6 = millis();
        digitalWrite(TrigPin6, LOW);
        delayMicroseconds(5);
        digitalWrite(TrigPin6, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin6, LOW);
        duration6 = pulseIn(EchoPin6, HIGH);
        distance6 = duration6 * 0.034/2; //cm
        elapsed7 = millis();
        digitalWrite(TrigPin7, LOW);
        delayMicroseconds(5);
        digitalWrite(TrigPin7, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin7, LOW);
        duration7 = pulseIn(EchoPin7, HIGH);
        distance7 = duration7 * 0.034/2 ;//cm   
        // THIS IS THE START OF FINDING OBJECTS USING THE SONAR SENSOR
        if (distance3 < 399||distance4 < 399||distance5 < 399) {
          tone(BuzzerPin, 1000); // Send 1KHz sound signal...
          delay(1000);        // ...for 1 sec
          noTone(BuzzerPin);     // Stop sound...
          delay(1000);        // ...for 1sec
        }
        objspeed = 0;
        if (distance1 < 399) {
          elapsedb = millis();
          digitalWrite(TrigPin1, LOW);
          delayMicroseconds(5);
          digitalWrite(TrigPin1, HIGH);
          delayMicroseconds(10);
          digitalWrite(TrigPin1, LOW);
          duration1b = pulseIn(EchoPin1, HIGH);
          distance1b = duration1 * 0.034/2; //cm
            if (distance1b < distance1) {
              elapsed = (elapsedb - elapsed1);
              maindist = (distance1 - distance1b);
              objspeed = (maindist/elapsed);
              maindist2 = (distance1b);
            }
        }
        if (distance2 < 399) {
          elapsedb = millis();
          digitalWrite(TrigPin2, LOW);
          delayMicroseconds(5);
          digitalWrite(TrigPin2, HIGH);
          delayMicroseconds(10);
          digitalWrite(TrigPin2, LOW);
          duration2b = pulseIn(EchoPin2, HIGH);
          distance2b = duration2 * 0.034/2; //cm
            if (distance2b < distance2) {
              elapsed = (elapsedb - elapsed2);
              maindist = (distance2 - distance2b);
              objspeed = (maindist/elapsed);
              maindist2 = (distance2b);
            }
        }
        if (distance6 < 399) {
          elapsedb = millis();
          digitalWrite(TrigPin6, LOW);
          delayMicroseconds(5);
          digitalWrite(TrigPin6, HIGH);
          delayMicroseconds(10);
          digitalWrite(TrigPin6, LOW);
          duration6b = pulseIn(EchoPin6, HIGH);
          distance6b = duration6 * 0.034/2; //cm
            if (distance6b < distance6) {
              elapsed = (elapsedb - elapsed6);
              maindist = (distance6 - distance6b);
              objspeed = (maindist/elapsed);
              maindist2 = (distance6b);
            }
        }
        if (distance7 < 399) {
          elapsedb = millis();
          digitalWrite(TrigPin7, LOW);
          delayMicroseconds(5);
          digitalWrite(TrigPin7, HIGH);
          delayMicroseconds(10);
          digitalWrite(TrigPin7, LOW);
          duration7b = pulseIn(EchoPin6, HIGH);
          distance7b = duration7 * 0.034/2; //cm
            if (distance7b < distance7) {
              elapsed = (elapsedb - elapsed7);
              maindist = (distance7 - distance7b);
              objspeed = (maindist/elapsed);
              maindist2 = (distance7b);
            }
        }
        if (objspeed > 100) {
          time2impact = (maindist2/objspeed);
          impact = ((sx*time2impact)-100);
          if (impact > maindist2) {
            tone(BuzzerPin, 1000); // Send 1KHz sound signal...
            delay(1000);        // ...for 1 sec
            noTone(BuzzerPin);     // Stop sound...
            delay(1000);        // ...for 1sec
          }
          // THIS IS THE END OF FINDING OBJECTS USING THE SONAR SENSOR
        }
}