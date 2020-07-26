/////////////////////
// MenuSystem
// version: 1.0
// 22.12.2013
// HEADER
/////////////////////


#ifndef MenuSystem_h
#define MenuSystem_h

#include <SSD1306Ascii.h>
#include "MenuDisplay.h"
#include "customInputBox/customInputBox.h"

#define ACTION_NONE    0
#define ACTION_UP      1
#define ACTION_DOWN    2
#define ACTION_SELECT  3
#define ACTION_BACK    4
#define ACTION_LONG    5


class MenuSystem {
public:
    MenuSystem();

    //explicit MenuSystem(Adafruit_SSD1306 *disp);

    explicit MenuSystem(SSD1306AsciiSoftSpi *disp);

    void InitMenu(const char *const *page, int itemCount, int selectedIndex);

    int ProcessMenu(int action);

    void ShowMenu();

    // void MessageBox(const char text[]) { qmd.MessageBox(text); };
    const char *const *CurrentMenu;
    const char *const *PreviousMenu;

    bool inputAvailable();

    int getInput();

    void ShowInputBox(const char *title, byte &minValue, byte &maxValue, byte &currentValue);

    int getPreviousSelectedIndex() const;

    int getPreviousItemCount() const;

    void setPreviousSelectedIndex(int previousSelectedIndex);

    void setPreviousItemCount(int previousItemCount);

private:
    void ShowInputBox();

    int _selectedIndex;
    int _itemCount;
    int _previousSelectedIndex;
    int _previousItemCount;
    int _firstVisible;
    char tempBuffer[32];
    MenuDisplay qmd;
    customInputBox _inputBox;

};

#endif