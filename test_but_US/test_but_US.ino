
//US up
int Trig1 = 2;
int Echo1 = 3;

int but_L = 11; // левый бампер
int but_R = 13; // правый бампер


int USensor (int Trig, int Echo){
  digitalWrite(Trig, HIGH); 
  /* Подаем импульс на вход trig дальномера */
  delayMicroseconds(10); // равный 10 микросекундам 
  digitalWrite(Trig, LOW); // Отключаем  
  return (pulseIn(Echo, HIGH)/58); // Выводим на порт   
}

void setup() {
  Serial.begin(9600);
  pinMode(Trig1, OUTPUT); //инициируем как выход 
  pinMode(Echo1, INPUT); //инициируем как вход 
  pinMode(but_L, INPUT); //инициируем как вход     
  pinMode(but_R, INPUT); //инициируем как вход         
}

void loop() {

  Serial.println(digitalRead(but_R));
 
}
