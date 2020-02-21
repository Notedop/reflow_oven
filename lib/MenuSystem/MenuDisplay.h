#define _Digole_Serial_SPI_
#ifndef Q_MENU_DISPLAY_H
#define Q_MENU_DISPLAY_H

#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSoftSpi.h"
#include "customInputBox/customInputBox.h"

class MenuDisplay {
public:

    explicit MenuDisplay(SSD1306AsciiSoftSpi *disp);

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
    SSD1306AsciiSoftSpi *disp;
};


#endif