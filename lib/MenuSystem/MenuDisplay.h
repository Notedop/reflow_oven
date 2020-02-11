#define _Digole_Serial_SPI_
#ifndef Q_MENU_DISPLAY_H
#define Q_MENU_DISPLAY_H

#ifndef _ADAFRUIT_GFX_H
    #include <Adafruit_SSD1306.h>
    #include <Adafruit_GFX.h>
#endif

#include "customInputBox/customInputBox.h"

class MenuDisplay {
public:
    explicit MenuDisplay(Adafruit_SSD1306 *disp);

    MenuDisplay();

    void Start();

    void Finish();

    void Title(const char text[]);

    void Item(int index, const char text[]);

    void Highlight(int index, const char text[]);

    // void MessageBox(const char text[]);
    //    char tempBuffer[32];
    void ShowInputBox(customInputBox inputBox);

private:
    Adafruit_SSD1306 * disp;
};


#endif