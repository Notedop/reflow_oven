#define _Digole_Serial_SPI_
#ifndef Q_MENU_DISPLAY_H
#define Q_MENU_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../customInputBox/customInputBox.h"

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
};


#endif