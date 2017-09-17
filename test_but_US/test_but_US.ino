#include <Servo.h> //используем библиотеку для работы с сервоприводом
Servo servo; 

int USensor (int Trig, int Echo){
  digitalWrite(Trig, HIGH); 
  /* Подаем импульс на вход trig дальномера */
  delayMicroseconds(10); // равный 10 микросекундам 
  digitalWrite(Trig, LOW); // Отключаем  
  return (pulseIn(Echo, HIGH)/58); // Выводим на порт   
}

void setup() {
  Serial.begin(9600);    
  pinMode(3, INPUT);  // 1350 - 1670
   servo.attach(12); //привязываем привод к порту 2
}
//1310-1680 // 88-
int ch2, ch2_old;
void loop() {
ch2 = pulseIn(3, HIGH); // each channel
      Serial.print("Chanel_2:");
      Serial.println(ch2);
       ch2 = constrain(ch2,1310,1680);  
      if ( abs(ch2-ch2_old) > 12){
      ch2_old = ch2;
      ch2 = map(ch2,1310,1680,85,108);
      if (ch2 <=108 && ch2 >= 85){
      servo.write(ch2);}
      } 
}

