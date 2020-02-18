#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <max6675.h>
#include <Encoder.h>
#include <constants.h>

#include <MenuDisplay.h>
#include <MenuSystem.h>
#include "menu.h"
#include <Profile.h>

MAX6675 temp_sensor;
Adafruit_SSD1306 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
MenuSystem menu;
Encoder encoder(encoder0PinA, encoder0PinB, encoder0Button);
Profile activeProfile(0,0,0,0,0,0,0,0,0,0,0);

char Celsius_C[8];
double Celcius_d;

uint8_t temperatureHistory[numberOfReads] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
uint8_t chartPos = 0;

unsigned long lastRead = 0;
unsigned long debounceDelay = 50;

uint16_t intervalSensorRead = 10000;
uint32_t tempMillis = 0;


void doEncoderScroll() {
    encoder.update();
    //Serial.println(encoder.getPosition());
}

void doEncoderClick() {
    if ((millis() - lastRead) > debounceDelay) {
        encoder.setClicked(true);
        //Serial.println(encoder.getClicked());
        lastRead = millis();
    }
}

void setup() {

    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, HIGH);
    pinMode(HEAT_PIN, OUTPUT);
    digitalWrite(HEAT_PIN, LOW);

    Serial.begin(9600);
    Serial.println("start");
    temp_sensor.begin(thermoCLK, thermoCS, thermoDO);

    attachInterrupt(1, doEncoderScroll, CHANGE);  // encoder pin on interrupt 1 - pin 3
    attachInterrupt(0, doEncoderClick, LOW); //
    menu = MenuSystem(&display);
    menu.InitMenu(mnuRoot, cntRoot, 1);
    Serial.println("end");

}

void setTopText(const char *value, uint8_t x, uint8_t y, uint8_t size) {
    display.setCursor(x, y);
    display.setTextSize(size);
    display.println(value);
}

void drawChart() {

    for (int8_t i = 0; i < (numberOfReads - 1); i++) {
        display.writeLine(
                i * xWidth, map(temperatureHistory[i], 0, 255, 64, 16),
                (i + 1) * xWidth, map(temperatureHistory[i + 1], 0, 255, 64, 16),
                WHITE
        );
    }
}

void addNewValue(uint8_t value) {

    for (int8_t i = 0; i < (numberOfReads - 1); i++) {
        temperatureHistory[i] = temperatureHistory[i + 1];
    }

    temperatureHistory[numberOfReads - 1] = value;
}

void loop() {

    int clickedItem = 0;

    if (encoder.getPosition() >= 2) {
        Serial.println(F("ACTON_DOWN"));
        menu.ProcessMenu(ACTION_DOWN);
        encoder.setPosition(0); //reset the position

    } else if (encoder.getPosition() <= -2) {
        Serial.println(F("ACTION_UP"));
        menu.ProcessMenu(ACTION_UP);
        encoder.setPosition(0); //reset the position
    } else if (encoder.getClicked()) {
        Serial.println(F("ACTION_SELECT"));
        clickedItem = menu.ProcessMenu(ACTION_SELECT);
        Serial.print(F("ClickedItem:"));
        Serial.println(clickedItem);
        encoder.resetClicked(); //reset the position
    }

    if (clickedItem > 0) {
        // Logic for Root menu
        if (menu.CurrentMenu == mnuRoot)
            switch (clickedItem) {
                case 1: //Profiles
                    menu.InitMenu(mnuSubProfiles, cntSubProfiles, 1);
                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:
                    // menu.MessageBox("Some message!");
                    break;
            }
            // Logic for Profiles submenu
        else if (menu.CurrentMenu == mnuSubProfiles) // Root --> Profiles
            switch (clickedItem) {
                case 1: //Root --> Profiles --> New profile
                    activeProfile = Profile(0,150,80,B00001000,180,60,B00101010,205,60,B00100010,50);
                    menu.InitMenu(mnuSubNewProfile, cntSubNewProfile, 1);
                    break;
                case 2: //Root --> Profiles -->Existing profile
                    break;
                case 3: //Root --> Profiles -->Back
                    menu.InitMenu(mnuRoot, cntRoot, 1);
                    break;
            }
        else if (menu.CurrentMenu == mnuSubNewProfile) //Root --> Profiles --> New profile
            switch (clickedItem) {
                case 1: //Root --> Profiles --> New profile --> Profile #
                    //logic for inputbox call:
                    if (menu.inputAvailable()) {
                        Serial.print(F("received following input"));
                        activeProfile.setProfileNumber(menu.getInput());
                        Serial.println(activeProfile.getProfileNumber());
                        menu.InitMenu(mnuSubNewProfile, cntSubNewProfile, 1);
                    } else {
                        menu.ShowInputBox("Input 1", 0, 255);
                    }
                    break;
                case 2: //Pre-heat
                    menu.InitMenu(mnuSubPreheat, cntSubPreheat, 1);
                    break;
                case 3: //Soak
                    menu.InitMenu(mnuSubSoak, cntSubSoak, 1);
                    break;
                case 4: //Reflow
                    menu.InitMenu(mnuSubReflow, cntSubReflow, 1);
                    break;
                case 5: //Cool
                    menu.InitMenu(mnuSubCool, cntSubCool, 1);
                    break;
                case 6: //Save
                    break;
                case 7: //Start
                    break;
                case 8: //Back to mnuSubProfiles
                    menu.InitMenu(mnuSubProfiles, cntSubProfiles, 1);
                    break;
            }
        else if (menu.CurrentMenu == mnuSubPreheat) //Root --> Profiles --> New profile --> Preheat
            switch (clickedItem) {
                case 1: //target temp

                    break;
                case 2: //Max time

                    break;
                case 3: //Celcius/Second
                    break;
                case 4: // Heaters
                    break;
                case 5: // back to mnuSubNewProfile
                    menu.InitMenu(mnuSubNewProfile, cntSubNewProfile, 1);
                    break;
            }
        else if (menu.CurrentMenu == mnuSubSoak) //Root --> Profiles --> New profile --> Soak
            switch (clickedItem) {
                case 1: //target temp

                    break;
                case 2: //Max time

                    break;
                case 3: //Heaters

                    break;
                case 4: // back to mnuSubNewProfile
                    menu.InitMenu(mnuSubNewProfile, cntSubNewProfile, 1);
                    break;
            }
        else if (menu.CurrentMenu == mnuSubReflow) //Root --> Profiles --> New profile --> Profile
            switch (clickedItem) {
                case 1: //target temp

                    break;
                case 2: //Max time

                    break;
                case 3: //Celcius/Second
                    break;
                case 4: // Heaters
                    break;
                case 5: // back to mnuSubNewProfile
                    menu.InitMenu(mnuSubNewProfile, cntSubNewProfile, 1);
                    break;
            }
        else if (menu.CurrentMenu == mnuSubCool) //Root --> Profiles --> New profile --> Cooldown
            switch (clickedItem) {
                case 1: //target temp
                    break;
                case 2: // back to mnuSubNewProfile
                    menu.InitMenu(mnuSubNewProfile, cntSubNewProfile, 1);
                    break;
            }


        //logic for inputbox call:
        //        if (menu.inputAvailable()) {
        //            Serial.print(F("received following input"));
        //            Serial.println(menu.getInput());
        //            menu.InitMenu(mnuSubProfiles, cntSubProfiles, 1);
        //        } else {
        //            menu.ShowInputBox("Input 1", 0, 255);
        //        }
        //        break;

    }
}

void doChart() {
    Celcius_d = temp_sensor.readCelsius();
    dtostrf(Celcius_d, 4, 2, Celsius_C);
    Serial.println(Celsius_C);
    display.clearDisplay();

    if (Celcius_d > 235.0) {
        digitalWrite(HEAT_PIN, LOW);
        setTopText(OFF, 112, 0, 2);
    } else if (Celcius_d == 235.0) {
        digitalWrite(HEAT_PIN, LOW);
        setTopText("-", 112, 0, 2);
    } else if (Celcius_d < 235.0) {
        digitalWrite(HEAT_PIN, HIGH);
        setTopText(ON, 112, 0, 2);
    }

    setTopText(Celsius_C, 0, 0, 2);
    drawChart();
    display.display();
    display.clearDisplay();

    if ((millis() - tempMillis) > intervalSensorRead) {
        addNewValue((uint8_t) Celcius_d);
        tempMillis = millis();
    }
    //chartPos=rand();
    delay(1000);
}