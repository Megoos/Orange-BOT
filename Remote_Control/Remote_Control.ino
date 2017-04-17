//Standard PWM DC control
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control

int but = 10; // кнопка пуска
int but_L = 11; // левый бампер
int but_R = 2; // правый бампер

int Trig1 = 3;
int Echo1 = 12;

int USensor (int Trig, int Echo){
  digitalWrite(Trig, HIGH); 
  /* Подаем импульс на вход trig дальномера */
  delayMicroseconds(10); // равный 10 микросекундам 
  digitalWrite(Trig, LOW); // Отключаем  
  return (pulseIn(Echo, HIGH)/58); // Выводим на порт   
}

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
  for(int i = 4;i <= 7;i++)
    pinMode(i, OUTPUT);  
  Serial.begin(19200);      //Set Baud Rate
  Serial.println("Run keyboard control");
  pinMode(but, OUTPUT); 
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(Trig1, OUTPUT); //инициируем как выход 
  pinMode(Echo1, INPUT); //инициируем как вход   
  pinMode(but_L, INPUT); //инициируем как выход 
  pinMode(but_R, INPUT); //инициируем как вход  
} 
void loop(void) 
{
  bool flag = true;
  int mosh = 0;
  int mosh1 = 0;
  int mosh2 = 0;
  int left = 0;
  int right = 0;
  
  int ch3;//kurok left_ (up_down) min = 1240 ; max = 2050 ; avr = (1672-1693) // (1622-1743)
  int ch1;//kurok right (left_right) min = 1200 ; max = 2050 ; avr = (1682-1700) // (1632-1750)
   
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
      
      if ((ch3 > 1743) && (USensor(Trig1,Echo1) > 40) && (digitalRead(but_L)==1 && digitalRead(but_R)==1)){
        mosh = map(ch3,1744,2050,0,300);
        mosh = constrain(mosh, 0, 255);
       flag = false;
        mosh1 = mosh+right-left;
         mosh1 = constrain(mosh1, 0, 255);
         mosh2 = mosh-right+left;
         mosh2 = constrain(mosh2, 0, 255);        
        advance(mosh1,mosh2);
        } else if(ch3 < 1622)  {
            mosh = map(ch3,1240,1621,-300,0);
            mosh *=-1;
            mosh = constrain(mosh, 0, 255);
           flag = false;
             mosh2 = mosh+right-left;
             mosh2 = constrain(mosh2, 0, 255);
             mosh1 = mosh-right+left;
             mosh1 = constrain(mosh1, 0, 255);
            back_off (mosh1,mosh2);
          }  else {
            if ((USensor(Trig1,Echo1) > 15)){
              if (right > 0){
                turn_R(10+right, 10+right); 
                }else if(left > 0){
                  turn_L(10+left, 10+left);
                  }else stop();    
              }        
            }

      if(ch1 > 1750) {
        right = map(ch1,1751,2050,0,300);
        right = constrain(right, 0, 200);
        left = 0;
        }else if(ch1 < 1632){
          left = map(ch1,1200,1631,-300,0);
          left *=-1;
          left = constrain(left, 0, 200); 
          right = 0;         
         } else {
          left = 0;
          right = 0;
          }
  }
Serial.println("End!");
}
