//Standard PWM DC control
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control

int but = 10;
///For previous Romeo, please use these pins.
//int E1 = 6;     //M1 Speed Control
//int E2 = 9;     //M2 Speed Control
//int M1 = 7;    //M1 Direction Control
//int M2 = 8;    //M1 Direction Control


void stop(void)                    //Stop
{
  digitalWrite(E1,LOW);   
  digitalWrite(E2,LOW);      
}   
void advance(char a,char b)          //Move forward
{
  analogWrite (E1,a);      //PWM Speed Control
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}  
void back_off (char a,char b)          //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);   
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}
void turn_L (char a,char b)             //Turn Left
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}
void turn_R (char a,char b)             //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}
void setup(void) 
{ 
  int i;
  for(i=4;i<=7;i++)
    pinMode(i, OUTPUT);  
  Serial.begin(19200);      //Set Baud Rate
  Serial.println("Run keyboard control");
  pinMode(but, OUTPUT); 
  pinMode(8, INPUT);
  pinMode(9, INPUT);
} 
void loop(void) 
{
  bool flag = true;
  int mosh = 0;
  int mosh1 = 0;
  int mosh2 = 0;
  int left = 0;
  int right = 0;
  
  int ch3;//kurok left_ (up_down) min = 1240 ; max = 2050 ; avr = (1672-1693) (1622-1743)
  int ch1;//kurok right (left_right) min = 1200 ; max = 2050 ; avr = (1682-1700) (1632-1750)
   
   digitalWrite(but, HIGH); 
 while (digitalRead(but) == 1) {
  }
  Serial.println("knopka");
  delay(2000);
  Serial.println("Start!!!");
  while(digitalRead(but) == 1){
      ch3 = pulseIn(8, HIGH); // up_down 
      ch1 = pulseIn(9, HIGH); // each channel
      Serial.print("Chanel_3:");
      Serial.println(ch3);
      Serial.print("Chanel_1:");
      Serial.println(ch1);
      
      if (ch3 > 1743){
        mosh = map(ch3,1744,2050,0,300);
        mosh = constrain(mosh, 0, 255);
       
        mosh1 = mosh+right-left;
         mosh1 = constrain(mosh1, 0, 255);
         mosh2 = mosh-right+left;
         mosh2 = constrain(mosh2, 0, 255);        
        advance(mosh1,mosh2);
        } else if(ch3 < 1622)  {
            mosh = map(ch3,1240,1621,-300,0);
            mosh *=-1;
            mosh = constrain(mosh, 0, 255);
           
             mosh2 = mosh+right-left;
             mosh2 = constrain(mosh2, 0, 255);
             mosh1 = mosh-right+left;
             mosh1 = constrain(mosh1, 0, 255);
            back_off (mosh1,mosh2);
          }  else {
            stop();
            }

      if(ch1 > 1750) {
        right = map(ch1,1751,2050,0,400);
        right = constrain(right, 0, 200);
        left = 0;
        }else if(ch1 < 1632){
          left = map(ch1,1200,1631,-400,0);
          left *=-1;
          left = constrain(left, 0, 200); 
          right = 0;         
         } else {
          left = 0;
          right = 0;
          }
                                
//  if(Serial.available()){
//    char val = Serial.read();
//    if(val != -1)
//    {
//      switch(val)
//      {
//      case 'w'://Move Forward
//        advance (255,255);   //move forward in max speed
//        break;
//      case 's'://Move Backward
//        back_off (255,255);   //move back in max speed
//        break;
//      case 'a'://Turn Left
//        turn_L (100,100);
//        break;
//      case 'd'://Turn Right
//        turn_R (100,100);
//        break;
//      case 'z':
//        Serial.println("Hello");
//        break;
//      case 'x':
//        stop();
//        break;
//      }
//    }
//    else stop();  
//  }
  }
Serial.println("End!");
}
