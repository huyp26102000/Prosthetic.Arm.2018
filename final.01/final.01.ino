#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "intro.h"
#include "mode.h"

#define OLED_MOSI  4
#define OLED_CLK   5
#define OLED_DC    2
#define OLED_CS    0
#define OLED_RESET 3

int mode = 0;
int valbtn2 = 0;
int valbtn3 = 0;
int st1 = 0;
int st2 = 0;
int st3 = 0;
int st4 = 0;
int btn1;
int btn2;
int btn3;

int a1;
int a2;
int a3;
int a4;
int a5;
int a6;
int a7;
int a8;
int a9;
int a10;

int musval;
int musvaldisplay;
int dpi = 0;
int vallimit = 0;
int detect_01;
byte va[3];

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup()
{
  Serial.begin(9600);
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(35,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(37,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(39,OUTPUT);

  pinMode(41,INPUT);
  pinMode(40,INPUT);
  pinMode(42,INPUT);
  pinMode(43,INPUT);
  pinMode(44,INPUT);
  pinMode(45,INPUT);
  pinMode(46,INPUT);
  pinMode(47,INPUT);
  pinMode(48,INPUT);
  pinMode(49,INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  begining();
  display.display();
  delay(100);
  
}
void loop()
{
  btn1 = digitalRead(8);
  btn2 = digitalRead(9);
  btn3 = digitalRead(10);

  a1 = digitalRead(40);
  a2 = digitalRead(41);
  a3 = digitalRead(42);
  a4 = digitalRead(43);
  a5 = digitalRead(44);
  a6 = digitalRead(45);
  a7 = digitalRead(46);
  a8 = digitalRead(47);
  a9 = digitalRead(48);
  a10 = digitalRead(49);

  if(btn1 == 1 and st1 ==0) {mode++;  st1 = 1;}
  if(btn1 == 1 and st1 ==1) {mode = mode; st1 = 1;}
  if(btn1 == 0 and st1 ==1) {mode = mode; st1 = 0;}
  if(mode == 4){mode = 0;}

  if(mode == 0) slicebar();
  if(mode == 1) linechart();
  if(mode == 2) controlpanel();
  if(mode == 3) test();

  

  Serial.println(mode);
//  
//  Serial.print(btn1);
//  Serial.print(btn2);
//  Serial.print(btn3);
//  Serial.print(" ");
//  Serial.print(a1);
//  Serial.print(" ");
//  Serial.print(a2);
//  Serial.print(" ");
//  Serial.print(a3);
//  Serial.print(" ");
//  Serial.print(a4);
//  Serial.print(" ");
//  Serial.print(a5);
//  Serial.print(" ");
//  Serial.print(a6);
//  Serial.print(" ");
//  Serial.print(a7);
//  Serial.print(" ");
//  Serial.print(a8);
//  Serial.print(" ");
//  Serial.print(a9);
//  Serial.print(" ");
//  Serial.println(a10);

}
void begining()
{
  display.clearDisplay();
  display.drawBitmap(0,8,intro1,128,32,WHITE);
  display.drawRect(0,0,128,8,WHITE);
  display.display();
  for(int i = 0;i<=128;i++) { display.fillRect(0,0,i,8,WHITE);  display.display(); }
}
void slicebar()
{
  musval = analogRead(A0);
  musvaldisplay = map(musval, 1023, 0, 700, 0);
  if(musvaldisplay > 122) musvaldisplay = 122;
  display.clearDisplay();
  display.drawBitmap(0,0,mode01,128,32,WHITE);
  display.drawRect(0,8,128,24,WHITE);
  display.drawRect(4,10,120,10,WHITE);
  display.setCursor(30,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Muscle Status");
  display.fillRect(3,10,musvaldisplay,10,WHITE);
  definetext(75,22,1,WHITE);
  display.print(musval);
  definetext(30,22,1,WHITE);
  display.print("value : ");
  display.display();
}
void linechart()
{
  display.clearDisplay();
  display.drawRect(0,8,128,24,WHITE);
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("Muscle Status");
  display.display();
}
void controlpanel()
{
  musval = analogRead(A0);
  if(btn2 == 1 and st2 ==0) {dpi = dpi + 5;  st2 = 1;}
  if(btn2 == 1 and st2 ==1) {dpi = dpi; st2 = 1;}
  if(btn2 == 0 and st2 ==1) {dpi = dpi; st2 = 0;}

  if(btn3 == 1 and st3 ==0) {vallimit = dpi + musval;  st3 = 1;}
  if(btn3 == 1 and st3 ==1) {vallimit = vallimit; st3 = 1;}
  if(btn3 == 0 and st3 ==1) {vallimit = vallimit; st3 = 0;}

  if(btn2 == 1 and btn3 ==1) {vallimit = 0; dpi = 0;}

  musvaldisplay = map(musval, 1023, 0, 700, 0);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("Control Panel");
  display.drawRect(0,8,128,16,WHITE);
  display.drawRect(0,23,128,9,WHITE);
  display.fillRect(0,8,128,6,WHITE);
  display.drawRect(0,11,45,13,WHITE);
  display.fillRect(0,23,(musvaldisplay+30),11,WHITE);
  definetext(2,24,1,BLACK);
  display.print(musval);
  definetext(3,15,1,WHITE);
  display.print("DPI: ");
  definetext(30,15,1,WHITE);
  display.print(dpi);
  definetext(48,15,1,WHITE);
  display.print("Limit:");
  definetext(90,15,1,WHITE);
  display.print(vallimit);

  if(musval >= vallimit)
  {
    if (vallimit == 0)  {va[0] = 0; }
    else { va[0] = 1;  display.fillRect(100,0,11,8,WHITE);}
  }
  else { va[0] = 0; }
  display.display();
}
void test()
{
  display.clearDisplay();
  definetext(0,0,1,WHITE);
  display.print("Signal Testing >>");
  int btn2 = digitalRead(9);
  definetext(0,9,1,WHITE);
  display.print(btn2);
  va[1] = btn2; 

  if(va[1]==0 and a7==0){moving(30,1,31,0);}
  if(va[1]==0 and a7==1){moving(30,0,31,0);}
  if(va[1]==1 and a8==0){moving(31,1,20,0);}
  if(va[1]==1 and a8==1){moving(31,0,20,0);}



  
  display.display();
}
void definetext(int cur1, int cur2, int textsize, char textcolor)
{
  display.setCursor(cur1, cur2);
  display.setTextSize(textsize);
  display.setTextColor(textcolor);
}
void moving(int pin1, int st1, int pin2, int st2)
{
  digitalWrite(pin1,st1); digitalWrite(pin2,st2);
}
