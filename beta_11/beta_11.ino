/* by Huy Hamada 
 *  11 june 2019
 *  prosthetic . beta . Transmitter
 */
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

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
//  begining();
  display.display();
//  delay(500);
}

void loop()
{
  controlpanel();
  int musval = analogRead(A0);
  int btn1 = digitalRead(A1);
  int btn2 = digitalRead(A2);
  int btn3 = digitalRead(A3);
//  
//  
//  if(btn1 == 1 and st1 ==0) {mode++;  st1 = 1;}
//  if(btn1 == 1 and st1 ==1) {mode = mode; st1 = 1;}
//  if(btn1 == 0 and st1 ==1) {mode = mode; st1 = 0;}
//  if(mode == 3){mode = 0;}
//  
//  if(mode == 0) slicebar();
//  if(mode == 1) linechart();
//  if(mode == 2) controlpanel();
//  
//  Serial.println(mode);
////  display.display();
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
  display.clearDisplay();
  display.drawBitmap(0,0,mode01,128,32,WHITE);
  display.drawRect(0,8,128,24,WHITE);
  display.drawRect(4,10,120,10,WHITE);
  display.setCursor(30,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Muscle Status");
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
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("Control Panel");
  display.drawRect(0,8,128,12,WHITE);
  display.drawRect(0,19,128,13,WHITE);
  
  display.display();
}
