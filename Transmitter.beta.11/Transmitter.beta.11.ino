/* by Huy Hamada
 *  21 june 2019
 *  prosthetic . beta . Transmitter
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include "RF24.h"
#include "intro.h"
#include "mode.h"

#define OLED_MOSI  4
#define OLED_CLK   5
#define OLED_DC    2
#define OLED_CS    0
#define OLED_RESET 3

const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(9,10);

byte valtrans[3];

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

int musval;
int musvaldisplay;
int dpi = 0;
int vallimit = 0;
int detect_01;

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup()   {

  radio.begin();
  Serial.begin(9600);

  radio.setAutoAck(1);
  radio.setRetries(1,1);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(10);
  radio.openWritingPipe(pipe);

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  begining();
  display.display();
  delay(500);
}

void loop()
{
  
  // controlpanel();
  int musval = analogRead(A0);
  int btn1 = digitalRead(A1);
  int btn2 = digitalRead(A2);
  int btn3 = digitalRead(A3);
//  Serial.print(btn1);
//  Serial.print(btn2);
//  Serial.print(btn3);
//  Serial.print(" ");
   Serial.println(musval);

  if(btn1 == 1 and st1 ==0) {mode++;  st1 = 1;}
  if(btn1 == 1 and st1 ==1) {mode = mode; st1 = 1;}
  if(btn1 == 0 and st1 ==1) {mode = mode; st1 = 0;}
  if(mode == 4){mode = 0;}

  if(mode == 0) slicebar();
  if(mode == 1) linechart();
  if(mode == 2) controlpanel();
  if(mode == 3) test();

  

  
  
 Serial.println(mode);
//  display.display();
  delay(50);
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
    if (vallimit == 0)  {valtrans[0] = 0; radio.write(&valtrans, sizeof(valtrans)); }
    else { valtrans[0] = 1; radio.write(&valtrans, sizeof(valtrans)); display.fillRect(100,0,11,8,WHITE);}
  }
  else { valtrans[0] = 0; radio.write(&valtrans, sizeof(valtrans));}
  display.display();
}
void test()
{
  display.clearDisplay();
  definetext(0,0,1,WHITE);
  display.print("Signal Testing >>");
  int btn2 = digitalRead(A2);
  definetext(0,9,1,WHITE);
  display.print(btn2);
  valtrans[1] = btn2; radio.write(&valtrans, sizeof(valtrans));
  display.display();
}
void definetext(int cur1, int cur2, int textsize, char textcolor)
{
  display.setCursor(cur1, cur2);
  display.setTextSize(textsize);
  display.setTextColor(textcolor);
}
void detectsensor()
{
  detect_01 = digitalRead(A0);
  if(detect_01 == 0 & st4 == 0) display.print("");
  
}
