#define _Digole_Serial_SPI_
#ifndef qMenuDisplay_h
#define qMenuDisplay_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class MenuDisplay
{
  public:
    MenuDisplay(Adafruit_SSD1306 disp);
    MenuDisplay();
    void Start();
    void Finish();
    void Title(const char text[]);
    void Item(int index,const char text[]);
    void Highlight(int index,const char text[]);
    // void MessageBox(const char text[]);
  private:
//    char tempBuffer[32];
};




#endif