/////////////////////
// MenuSystem
// version: 1.0
// 22.12.2013
// HEADER
/////////////////////


#ifndef MenuSystem_h
#define MenuSystem_h

#include "MenuDisplay.h"
#include "customInputBox/customInputBox.h"

#define ACTION_NONE    0
#define ACTION_UP      1
#define ACTION_DOWN    2
#define ACTION_SELECT  3
#define ACTION_BACK    4


class MenuSystem
{
  public:
    MenuSystem();
    MenuSystem(Adafruit_SSD1306* disp);
    void InitMenu(const char * const * page, int itemCount, int selectedIndex);
    int ProcessMenu(int action);
    void ShowMenu();
    // void MessageBox(const char text[]) { qmd.MessageBox(text); };
    const char * const * CurrentMenu;
    bool inputAvailable();
    int getInput();
    void ShowInputBox(const char *title, int &minValue, int &maxValue, int &currentValue);

private:
    void ShowInputBox();
    int _selectedIndex;
    int _itemCount;
    int _firstVisible;
    char tempBuffer[32];
    MenuDisplay qmd;
    customInputBox _inputBox;

};

#endif