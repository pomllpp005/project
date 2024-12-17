#include <Servo.h>
#include <CD74HC4067.h>

Servo esc; 
CD74HC4067 my_mux(9, 10, 11, 12); 

int16_t value = 0;

int Last_value ;
int error ;
int integral ;
int differencial ;
int Last_error ;
float KP;
float KD;


int MaxspeedL=0;
int MaxspeedR=0;
int BasespeedL=0;
int BasespeedR=0 ;
int16_t MotorL , MotorR ;

void setup() {
  OPen_motor();
  // pinMode(common_pin,INPUT);
  Serial.begin(9600);
  
  
  ESCReady();

  switch1();




}
void loop() {



}
 
void StopESC(){
  delay(2000);
  esc.writeMicroseconds(1000);
  delay(1000);
}
void StartESC(int SpeedESC){
  for(uint32_t i=1000;i<SpeedESC;i++){

  
  esc.writeMicroseconds(i);  // ส่งค่า throttle ไปยัง ESC
  delay(3);
  }
  esc.writeMicroseconds(SpeedESC);
  delay(1500);
}
void ESCReady(){
  delay(500);
  esc.attach(5);  // กำหนดพิน 5 เป็นพินสัญญาณสำหรับ ESC
  esc.writeMicroseconds(1000);  // ส่งสัญญาณเริ่มต้นไปยัง ESC
  delay(1000);   
  esc.writeMicroseconds(1100);  // ส่งค่า throttle ไปยัง ESC
  delay(100);
  
}


  



void PID2()
{
 
    
    differencial = (error * KP) + ((error - Last_error) *KD );
    Last_error = error;
    MotorL = BasespeedL + differencial;
    MotorR = BasespeedR - differencial;   

    if(MotorL > MaxspeedL) MotorL = MaxspeedL ;  
    else if(MotorR < -MaxspeedL ) MotorR = -MaxspeedL;

    if(MotorR > MaxspeedR) MotorR = MaxspeedR ;
    else if(MotorR < -MaxspeedR ) MotorR = -MaxspeedR;
    
    motorcontrol(MotorL,MotorR);

   

}

void PID()
{
 
    
    if(abs(error)<1000) esc.writeMicroseconds(1450); 
    if(abs(error)>=1000&&abs(error)<3350) esc.writeMicroseconds(1480); 
    else esc.writeMicroseconds(1530); 
  
 
    differencial = (error * KP) + ((error - Last_error) *KD );
    Last_error = error;
    MotorL = BasespeedL + differencial;
    MotorR = BasespeedR - differencial;   

    if(MotorL > MaxspeedL) MotorL = MaxspeedL ;  
    else if(MotorR < -MaxspeedL ) MotorR = -MaxspeedL;

    if(MotorR > MaxspeedR) MotorR = MaxspeedR ;
    else if(MotorR < -MaxspeedR ) MotorR = -MaxspeedR;
    
    motorcontrol(MotorL,MotorR);


}

void PidTimer(unsigned int Time , int speedL, int speedR){
  
 MaxspeedL=97;
 MaxspeedR=98;
 BasespeedL=speedL;
 BasespeedR=speedR ;
KP=0.03;
KD=0.25;
unsigned long ReadTime = millis();
while(millis()-ReadTime < Time){
 PID2();
}

}
void selectChannel(int channel) {
    digitalWrite(S0, bitRead(channel, 0));
    digitalWrite(S1, bitRead(channel, 1));
    digitalWrite(S2, bitRead(channel, 2));
    digitalWrite(S3, bitRead(channel, 3));
}
void readCalibrated(uint16_t *sensorValues) {
    for (int sensor = 0; sensor < 16; sensor++) {
        selectChannel(sensor);
        int value = analogRead(A0);

        uint16_t calmin = calibration.minimum[sensor];
        uint16_t calmax = calibration.maximum[sensor];
        uint16_t denominator = calmax - calmin;
        int16_t calibratedValue = 0;

        // คำนวณค่าที่ปรับเทียบแล้ว
        if (denominator != 0) {
            calibratedValue = (((int32_t)value) - calmin) * 1000 / denominator;
        }

        // จำกัดค่าให้อยู่ในช่วง 0–1000
        if (calibratedValue < 0) {
            calibratedValue = 0;
        } else if (calibratedValue > 1000) {
            calibratedValue = 1000;
        }

        sensorValues[sensor] = calibratedValue;
    }
}
