

#include "customInputBox.h"

customInputBox::customInputBox( char* input, int minValue, int maxValue) {
    _minValue = minValue;
    _maxValue = maxValue;
    _currentValue = minValue;
    _waitingForInput = false;
    _title = input;
}

customInputBox::customInputBox() {
};

int customInputBox::getMinValue() const {
    return _minValue;
}

void customInputBox::setMinValue(int minValue) {
    _minValue = minValue;
}

int customInputBox::getMaxValue() const {
    return _maxValue;
}

void customInputBox::setMaxValue(int maxValue) {
    _maxValue = maxValue;
}

int customInputBox::getCurrentValue() const {
    return _currentValue;
}

void customInputBox::setCurrentValue(int currentValue) {
    _currentValue = currentValue;
}

bool customInputBox::isWaitingForInput()  {
    return false;
}

void customInputBox::setWaitingForInput(bool waitingForInput) {
    _waitingForInput = waitingForInput;
}

void customInputBox::setTitle(char *string) {

    _title=string;

}

