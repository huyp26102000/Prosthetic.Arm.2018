#include <SPI.h>
#include "RF24.h"
int pos = 1;
int cc = 1;
const uint64_t pipe = 0xE8E8F0F0E1LL; // адрес канала передачи
RF24 radio(7,8);
byte va[3];

void setup(){
  Serial.begin(9600);
  //============================================================Модуль NRF24
  radio.begin();                      // Включение модуля
  radio.setAutoAck(1);                // Установка режима подтверждения приема;
  radio.setDataRate(RF24_250KBPS);    // Устанавливаем скорость
  radio.setChannel(10);               // Устанавливаем канал
  radio.openReadingPipe(1,pipe);      // Открываем 1 канал приема
  radio.startListening();             // Начинаем слушать эфир
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop(){
  int check1 = digitalRead(A0);
  int check2 = digitalRead(A1);
  int check3 = digitalRead(A2);
  int check4 = digitalRead(A3);
  int check5 = digitalRead(A4);
  int check6 = digitalRead(A5);
  int check7 = digitalRead(A6);
  int check8 = digitalRead(A7);
  if (radio.available()){
    while (radio.available()){
      radio.read(&va, sizeof(va));

    }
  }
  Serial.print(check1);
  Serial.print(check2);
  Serial.print(check3);
  Serial.print(check4);
  Serial.println(va[1]);
  if(va[1]==0 and check2==0){moving(2,1,3,0);}
  if(va[1]==0 and check2==1){moving(2,0,3,0);}
  if(va[1]==1 and check1==0){moving(3,1,2,0);}
  if(va[1]==1 and check1==1){moving(3,0,2,0);}

  if(va[1]==0 and check3==0){moving(5,1,4,0);}
  if(va[1]==0 and check3==1){moving(5,0,4,0);}
  if(va[1]==1 and check4==0){moving(4,1,5,0);}
  if(va[1]==1 and check4==1){moving(4,0,5,0);}

  if(va[1]==0 and check6==0){moving(9,1,6,0);}
  if(va[1]==0 and check6==1){moving(9,0,6,0);}
  if(va[1]==1 and check5==0){moving(6,1,9,0);}
  if(va[1]==1 and check5==1){moving(6,0,9,0);}

  if(va[1]==0 and check8==0){moving(10,1,11,0);}
  if(va[1]==0 and check8==1){moving(10,0,11,0);}
  if(va[1]==1 and check7==0){moving(11,1,10,0);}
  if(va[1]==1 and check7==1){moving(11,0,10,0);}
}
void moving(int pin1, int st1, int pin2, int st2)
{
  digitalWrite(pin1,st1); digitalWrite(pin2,st2);
}
