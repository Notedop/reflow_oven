#include "MenuDisplay.h"
//#include <constants.h>

MenuDisplay::MenuDisplay()
{
}

MenuDisplay::MenuDisplay(Adafruit_SSD1306 *disp) {
    //Serial.begin(9600);
    //Serial.println(F("constructor menudisplay"));
    this->disp = disp;
    disp->begin();
    disp->setTextColor(WHITE);
    disp->setTextWrap(true);
    disp->clearDisplay();
    disp->setCursor(0, 0);
    disp->setTextSize(1); //TODO: Make this a configurable constant. Or maybe even better; configurable via menu itself
    // Serial.println("end menudisplay");
}

void MenuDisplay::Start()
{
    disp->clearDisplay();
}

void MenuDisplay::Finish()
{
    disp->display();
    delay(1);
}

void MenuDisplay::Title(const char text[])
{
  disp->setTextColor(SSD1306_WHITE);
  disp->setCursor(0, 0);
  disp->print(text);
}

void MenuDisplay::Item(int index,const char text[])
{
  disp->setTextColor(SSD1306_WHITE);
  disp->setCursor(5, (index * 8) + 16); //TODO: Create constants for pixel offset and char pixel height. Height of char with textsize 1 is 8
  disp->print(text);
}

void MenuDisplay::Highlight(int index,const char text[])
{
  disp->setCursor(5, (index * 8) + 16); //TODO: Create constants for pixel offset and char pixel height. Height of char with textsize 1 is 8
  disp->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  disp->print(text);
}

void MenuDisplay::ShowInputBox(customInputBox inputBox) {


    this->Title(inputBox.getTitle());
    disp->setCursor(55, 20);
    disp->setTextSize(3);
    disp->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    //todo: center the value based on screen size and value size (depends on fontheight[pixels]*chars/2 etc etc
    disp->print(inputBox.getCurrentValue());
    disp->drawRect(1, 16, 127, 48, SSD1306_WHITE);
    disp->setTextSize(1);

}

// void MenuDisplay::MessageBox(const char text[])
// {
//   int textWidth=strlen(text)*9;
//   int x=64-(textWidth/2);
//   int y=32;

//   disp->setMode('&');
//   disp->setColor(0);
//   disp->drawBox(x-5,y-12,textWidth+9,21+3);
//   disp->setMode('~');
//   disp->setColor(1);
//   disp->drawFrame(x-3,y-10,textWidth+5,17+3);

//   disp->setTextPosAbs(x,y+5);
//   disp->print(text);
// }