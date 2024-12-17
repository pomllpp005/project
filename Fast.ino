void OPen_motor(){
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

}
void Forward(int speedL,int speedR,int time){
  motorcontrol(speedL,speedR);
  delay(time);
}

void motorcontrol(int speedA, int speedB) {
   

  // Motor A control
  if (speedA >= 0) {
    digitalWrite( 2 , HIGH );   // CW direction
    digitalWrite( 4 , LOW );
  } 
 
  else {
    digitalWrite( 2 , LOW );    // CCW direction
    digitalWrite( 4 , HIGH );
    speedA = -speedA;           // Convert to positive for PWM
  }
  analogWrite(3, speedA*2.55 );    // Set Motor A speed

  // Motor B control
  if (speedB >= 0) {
    digitalWrite( 7 , HIGH );   // CW direction
    digitalWrite( 8 , LOW );
  } 
   
  else {
    digitalWrite( 7 , LOW );    // CCW direction
    digitalWrite( 8 , HIGH );
    speedB  = -speedB ;           // Convert to positive for PWM
  }
  analogWrite(6, speedB*2.55 );    // Set Motor B speed
  
}

void motor(uint8_t select,int speed){
 // Motor A control
  if ((speed > 0)&&(select==1)) {
    digitalWrite( 2 , LOW );   // CW direction
    digitalWrite( 4 , HIGH );
     analogWrite(3, speed*2.55 );    // Set Motor A speed
  } 
   else if((speed == 0)&&(select==1)) {
    digitalWrite( 2 ,LOW );    // CCW direction
    digitalWrite( 4 , LOW );
    speed = -speed;           // Convert to positive for PWM
   
  }
  else if((speed < 0)&&(select==1)){
    digitalWrite( 2 , HIGH );    // CCW direction
    digitalWrite( 4 , LOW );
    speed = -speed;           // Convert to positive for PWM
    analogWrite(3, speed*2.55 );    // Set Motor A speed
  }
  

  // Motor B control
  if ((speed > 0)&&(select==2)) {
    digitalWrite( 7 , LOW );   // CW direction
    digitalWrite( 8 , HIGH );
    analogWrite(6, speed*2.55 );    // Set Motor A speed
  } 
   else if((speed == 0)&&(select==2)) {
    digitalWrite( 7 ,LOW );    // CCW direction
    digitalWrite( 8 , LOW );
    analogWrite(6, 0 );    // Set Motor A speed
  }
  else if((speed < 0)&&(select==2)) {
    digitalWrite( 7 , HIGH );    // CCW direction
    digitalWrite( 8 , LOW );
    speed  = -speed ;           // Convert to positive for PWM
    analogWrite(6, speed*2.55 );    // Set Motor B speed
  }
  
  


}

/*
void runMode(int16_t speedA, int16_t speedB) {
 
  digitalWrite(AIN1, HIGH);    // Set Motor A direction
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, speedA);   // Set Motor A speed
  
  digitalWrite(BIN1, HIGH);    // Set Motor B direction
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, speedB);   // Set Motor B speed
}

// Function to reverse motors
void reverseMode(int16_t speedA, int16_t speedB) {
 
  digitalWrite(AIN1, LOW);     // Reverse Motor A direction
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, speedA);   // Set Motor A speed
  
  digitalWrite(BIN1, LOW);     // Reverse Motor B direction
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, speedB);   // Set Motor B speed
}
*/
// Function to apply brakes to both motors
void brake() {
 
  digitalWrite(2, LOW);    // Apply brake to Motor A
  digitalWrite(4, LOW);
  analogWrite(3, 0);        // Motor A speed 0
  
  digitalWrite(7, LOW);    // Apply brake to Motor B
  digitalWrite(8, LOW);
  analogWrite(6, 0);        // Motor B speed 0
}

