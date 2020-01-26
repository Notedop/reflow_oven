#include "MenuDisplay.h"
//#include <constants.h>

Adafruit_SSD1306 _disp;

MenuDisplay::MenuDisplay()
{
}

MenuDisplay::MenuDisplay( Adafruit_SSD1306 disp)
{
     Serial.begin(9600);
     Serial.println("constructor menudisplay");
    _disp=disp;
    _disp.begin();
    _disp.setTextColor(WHITE);
    _disp.setTextWrap(false);
    _disp.clearDisplay();
     _disp.setCursor(0,0);
     _disp.setTextSize(2);
     _disp.println("menudisplay");
     _disp.display();
     delay(500);
     _disp.clearDisplay();
     _disp.setCursor(0,0);
     _disp.println("constructor");
     _disp.display();
    // Serial.println("end menudisplay");

}

void MenuDisplay::Start()
{
    _disp.clearDisplay();
}

void MenuDisplay::Finish()
{
    _disp.display();
}

void MenuDisplay::Title(const char text[])
{
  _disp.setTextColor(SSD1306_WHITE);
  _disp.setCursor(0,0);
  _disp.println(text);
}

void MenuDisplay::Item(int index,const char text[])
{
  _disp.setTextColor(SSD1306_WHITE);
  _disp.setCursor(5,(index*16)+16);
  _disp.println(text);
}

void MenuDisplay::Highlight(int index,const char text[])
{
  _disp.setCursor(5,(index*16)+16);
  _disp.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  _disp.println(text);
}

// void MenuDisplay::MessageBox(const char text[])
// {
//   int textWidth=strlen(text)*9;
//   int x=64-(textWidth/2);
//   int y=32;

//   _disp.setMode('&');
//   _disp.setColor(0);
//   _disp.drawBox(x-5,y-12,textWidth+9,21+3);
//   _disp.setMode('~');
//   _disp.setColor(1);
//   _disp.drawFrame(x-3,y-10,textWidth+5,17+3);

//   _disp.setTextPosAbs(x,y+5);
//   _disp.print(text);
// }