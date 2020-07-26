#ifndef _CUSTOMINPUTBOX_H
#define _CUSTOMINPUTBOX_H

class customInputBox {

public:
    customInputBox() {    };

    customInputBox(char *input, int minValue, int maxValue) : _minValue(minValue), _maxValue(maxValue),
                                                              _currentValue(minValue), _waitingForInput(false),
                                                              _inputAvailable(false), _title(input) {};

    int getMinValue() const;

    void setMinValue(int minValue);

    int getMaxValue() const;

    void setMaxValue(int maxValue);

    int getCurrentValue() const;

    void setCurrentValue(int currentValue);

    bool isWaitingForInput();

    void setWaitingForInput(bool waitingForInput);

    const char *getTitle() const;

    void setTitle(const char* string);

    bool isInputAvailable() const;

    void setInputAvailable(bool inputAvailable);

    void increment();

    void decrement();

    int getChangeByValue() const;

    void setChangeByValue(int changeByValue);

    void nextChangeByValue();

private:

    int _minValue;
    int _maxValue;
    int _currentValue;
    int _changeByValue = 1;
    bool _waitingForInput;
    bool _inputAvailable;
    const char* _title;
};

#endif //TESTPROJECT_INPUTBOX_H
