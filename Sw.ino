void switch1(){
  while(1){
   if(analogRead(A7)<100)break;
  }
}
void switchd(){
  while(1){
   if(digitalRead(2)==1)break;
  }
}
void switch2(){
  while(1){
   if(analogRead(A6)<100)break;
  }
}