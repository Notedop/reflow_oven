#include "customInputBox.h"

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
    return _waitingForInput;
}

void customInputBox::setWaitingForInput(bool waitingForInput) {
    _waitingForInput = waitingForInput;
}

void customInputBox::setTitle(const char *string) {

    _title=string;

}

bool customInputBox::isInputAvailable() const {
    return _inputAvailable;
}

void customInputBox::setInputAvailable(bool inputAvailable) {
    _inputAvailable = inputAvailable;
}

const char *customInputBox::getTitle() const {
    return _title;
}

