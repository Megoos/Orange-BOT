
//US up
//int Trig1 = 2;
int Echo1 = 3;

int but_L = 11; // левый бампер
int but_R = A5; // правый бампер

int USensor (int Trig, int Echo){
  digitalWrite(Trig, HIGH); 
  /* Подаем импульс на вход trig дальномера */
  delayMicroseconds(10); // равный 10 микросекундам 
  digitalWrite(Trig, LOW); // Отключаем  
  return (pulseIn(Echo, HIGH)/58); // Выводим на порт   
}

void setup() {
  Serial.begin(9600);

  pinMode(Echo1, INPUT); //инициируем как вход 
  pinMode(but_L, INPUT); //инициируем как вход     
  pinMode(but_R, INPUT); //инициируем как вход      
  pinMode(11, INPUT);  // 1350 - 1670
}

int ch2;
void loop() {
ch2 = pulseIn(11, HIGH); // each channel
      Serial.print("Chanel_2:");
      Serial.println(ch2);
}
