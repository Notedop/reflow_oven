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

void customInputBox::increment() {

    _currentValue = _currentValue + _changeByValue;

}

void customInputBox::decrement() {
    _currentValue = _currentValue - _changeByValue;
}

int customInputBox::getChangeByValue() const {
    return _changeByValue;
}

void customInputBox::setChangeByValue(int changeByValue) {
    _changeByValue = changeByValue;
}

void customInputBox::nextChangeByValue() {

    if (_changeByValue == 1 ) {
        _changeByValue = 10;
    } else if (_changeByValue == 10 ) {
        _changeByValue = 100;
    } else if (_changeByValue == 100) {
        _changeByValue = 1;
    }

}

