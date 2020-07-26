/////////////////////
// MenuSystem
// version: 1.0
// 22.12.2013
// CLASS
/////////////////////
#include <avr/pgmspace.h>
#include "MenuSystem.h"
#include "MenuDisplay.h"

MenuSystem::MenuSystem() {};

MenuSystem::MenuSystem(SSD1306AsciiSoftSpi *disp) {
    qmd = MenuDisplay(disp);
    _inputBox = customInputBox(NULL, 1,255);
    _selectedIndex = 0;
    _itemCount = 0;
    _firstVisible = 1;

}

void MenuSystem::InitMenu(const char *const *page, int itemCount, int selectedIndex) {
    CurrentMenu = page;
    _selectedIndex = selectedIndex;
    _itemCount = itemCount;
//  ProcessMenu(ACTION_NONE);
    ShowMenu();
}


int MenuSystem::ProcessMenu(int action) {

    //Serial.print("Waiting for input: ");
   // Serial.println(_inputBox.isWaitingForInput());

    if (!_inputBox.isWaitingForInput()) {
        if (action == ACTION_DOWN)
            _selectedIndex++;
        if (action == ACTION_UP)
            _selectedIndex--;

        if (_selectedIndex > _itemCount)
            _selectedIndex = 1;
        if (_selectedIndex < 1)
            _selectedIndex = _itemCount;

        if (action == ACTION_SELECT)
            return _selectedIndex;

        ShowMenu();

    } else {
        if (action == ACTION_DOWN)
            if (_inputBox.getCurrentValue() < _inputBox.getMaxValue()) {
                _inputBox.setCurrentValue(_inputBox.getCurrentValue() + 1);
                ShowInputBox();
            }
        if (action == ACTION_UP)
            if (_inputBox.getCurrentValue() > _inputBox.getMinValue()) {
                _inputBox.setCurrentValue(_inputBox.getCurrentValue() - 1);;
                ShowInputBox();
            }
        if (action == ACTION_SELECT) {
            //we are done waiting for input and it's availble now.
            _inputBox.setWaitingForInput(false);
            _inputBox.setInputAvailable(true);
            //return selected index, so that we return to previous selected menu.
            return _selectedIndex;
        }
    }
    return 0;
}

void MenuSystem::ShowMenu() {
    if (_selectedIndex > _firstVisible + 5) //TODO: Make macro to define the 5 value using TOTAL_DISPLAYED_ITEMS
        _firstVisible = _selectedIndex - 5;
    else if (_selectedIndex < _firstVisible)
        _firstVisible = _selectedIndex;

    qmd.Start();

    // display title
    strcpy_P(tempBuffer, (char *) pgm_read_word(&(CurrentMenu[0])));
    //Serial.println(tempBuffer);
    qmd.Title(tempBuffer);

    // display items
    int p = 6; //TODO: Make this a configurable constant TOTAL_DISPLAYED_ITEMS
    if (p > (_itemCount - _firstVisible + 1))
        p = _itemCount - _firstVisible + 1;
    for (int i = 0; i < p; i++) {
        strcpy_P(tempBuffer, (char *) pgm_read_word(&(CurrentMenu[i + _firstVisible])));
        qmd.Item(i, tempBuffer);
    }

    strcpy_P(tempBuffer, (char *) pgm_read_word(&(CurrentMenu[_selectedIndex])));

    // display selection
    qmd.Highlight(_selectedIndex - _firstVisible, tempBuffer);

    qmd.Finish();
}

void MenuSystem::ShowInputBox(const char *title, byte &minValue, byte &maxValue, byte &currentValue) {
    _inputBox.setWaitingForInput(true);
    _inputBox.setTitle(title);
    _inputBox.setMinValue(minValue);
    _inputBox.setMaxValue(maxValue);
    _inputBox.setCurrentValue(currentValue);

    ShowInputBox();
}

bool MenuSystem::inputAvailable() {
    //Should NOT be waiting for input and input should be available from inputbox.
    return (!_inputBox.isWaitingForInput() && _inputBox.isInputAvailable());
}

int MenuSystem::getInput() {
    //As input is retrieved, don't make it available anymore after that.
    _inputBox.setInputAvailable(false);
    return _inputBox.getCurrentValue();
}

void MenuSystem::ShowInputBox() {

    qmd.Start();
    qmd.ShowInputBox(_inputBox);
    qmd.Finish();

}

int MenuSystem::getPreviousSelectedIndex() const {
    return _previousSelectedIndex;
}

int MenuSystem::getPreviousItemCount() const {
    return _previousItemCount;
}

void MenuSystem::setPreviousSelectedIndex(int previousSelectedIndex) {
    _previousSelectedIndex = previousSelectedIndex;
}

void MenuSystem::setPreviousItemCount(int previousItemCount) {
    _previousItemCount = previousItemCount;
}
