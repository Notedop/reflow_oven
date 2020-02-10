#ifndef customInputBox_h
#define customInputBox_h

class customInputBox {

public:
    customInputBox();
    customInputBox( char* input, int minValue, int maxValue);

    int getMinValue() const;

    void setMinValue(int minValue);

    int getMaxValue() const;

    void setMaxValue(int maxValue);

    int getCurrentValue() const;

    void setCurrentValue(int currentValue);

    bool isWaitingForInput() ;

    void setWaitingForInput(bool waitingForInput);

    void setTitle(char *string);

private:

    int _minValue;
    int _maxValue;
    int _currentValue;
    bool _waitingForInput;
    char* _title;
};

#endif //TESTPROJECT_INPUTBOX_H
