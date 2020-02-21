
#include "MenuDisplay.h"

MenuDisplay::MenuDisplay() = default;

MenuDisplay::MenuDisplay(SSD1306AsciiSoftSpi *disp) {

    this->disp = disp;
    disp->setFont(Adafruit5x7);
    disp->clear();
    disp->setCursor(0, 0);
    disp->setContrast(50);

}
void MenuDisplay::Start() {
    disp->clear();
}

void MenuDisplay::Finish() {
    //delay(1);
}

void MenuDisplay::Title(const char text[]) {
    disp->setInvertMode(false);
    disp->setCursor(0, 0);
    disp->println(text);
}

void MenuDisplay::Item(int index, const char text[]) {
    disp->setInvertMode(false);
//    Serial.print("fontHeight:");
//    Serial.println(disp->fontHeight());
//    Serial.print("index:");
//    Serial.println(index);
//    Serial.print("row:");
//    Serial.println((index * disp->fontHeight()) + 16);

    disp->setCursor(disp->fontWidth(), (index * disp->fontRows()) + disp->fontRows()*2);
    disp->println(text);
}

void MenuDisplay::Highlight(int index, const char text[]) {
    disp->setCursor(5, (index * disp->fontRows()+disp->fontRows()*2));
    disp->setInvertMode(true);
    disp->println(text);
}

void MenuDisplay::ShowInputBox(customInputBox inputBox) {

    int number = inputBox.getCurrentValue();
    int digits = 0;
    do { number /= 10; digits++; } while (number != 0);

    this->Title(inputBox.getTitle());
    disp->set2X();
    disp->setCursor((disp->displayWidth()/2)-((disp->fontWidth()*digits)/2),(disp->displayRows()/2)-(disp->fontRows()/2));
    disp->setInvertMode(true);
    disp->println(inputBox.getCurrentValue());
    disp->set1X();

}


// void MenuDisplay::MessageBox(const char text[])
// {
//   int textWidth=strlen(text)*9;
//   int x=64-(textWidth/2);
//   int y=32;

//   disp->setMode('&');
//   disp->setColor(0);
//   disp->drawBox(x-5,y-12,textWidth+9,21+3);
//   disp->setMode('~');
//   disp->setColor(1);
//   disp->drawFrame(x-3,y-10,textWidth+5,17+3);

//   disp->setTextPosAbs(x,y+5);
//   disp->print(text);
// }