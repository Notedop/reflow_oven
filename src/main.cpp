#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <max6675.h>
#include <Encoder.h>
#include <constants.h>

#include <MenuDisplay.h>
#include <MenuSystem.h>
#include "menu.h"

MAX6675 temp_sensor;
Adafruit_SSD1306 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Encoder encoder(encoder0PinA, encoder0PinB, encoder0Button);

char Celsius_C[8];
double Celcius_d;

uint8_t temperatureHistory[numberOfReads] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
uint8_t chartPos = 0;

unsigned long lastRead = 0;
unsigned long debounceDelay = 50;

uint16_t intervalSensorRead = 10000; 
uint32_t tempMillis = 0;

MenuSystem menu;

void doEncoderScroll(){
    encoder.update();
    Serial.println(encoder.getPosition());
    lastRead = millis();
}

void doEncoderClick(){
    if((millis() - lastRead)>debounceDelay) {
      encoder.setClicked(true);
      Serial.println(encoder.getClicked());
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
 
  // init done
  //display configurations
  // display.setFont();
  // display.setTextColor(WHITE);
  // display.setTextWrap(false);
  // display.clearDisplay();
  // display.setCursor(0,0);
  // display.setTextSize(2);
  // display.println("blabla");
  // display.display();
  
  attachInterrupt(0, doEncoderScroll , CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(1, doEncoderClick , LOW); // 
  menu=MenuSystem(display);
  menu.InitMenu(mnuRoot,cntRoot,1);
  Serial.println("end");

}

void setTopText(const char* value, uint8_t x, uint8_t y, uint8_t size ) {
  display.setCursor(x,y);
  display.setTextSize(size);
  display.println(value);
}

void drawChart() {
  
  for (int8_t i=0; i<(numberOfReads-1); i++) {
    display.writeLine(
      i*xWidth,     map(temperatureHistory[i],  0,255,64,16), 
      (i+1)*xWidth, map(temperatureHistory[i+1],0,255,64,16),
      WHITE
    );
  }
}

void addNewValue(uint8_t value) {

  for (int8_t i=0; i<(numberOfReads-1); i++) {
    temperatureHistory[i] = temperatureHistory[i+1];
  }

  temperatureHistory[numberOfReads-1] = value;
}

void loop() {

  int clickedItem=0; 

  if (encoder.getPosition() >= 2 ) {
    Serial.println("ACTON_DOWN");
    menu.ProcessMenu(ACTION_DOWN);
    encoder.setPosition(0); //reset the position

  } else if (encoder.getPosition() <= -2) {
    Serial.println("ACTION_UP");
    menu.ProcessMenu(ACTION_UP);
    encoder.setPosition(0); //reset the position
  } else if (encoder.getClicked()) {
    Serial.println("ACTION_SELECT");
    clickedItem=menu.ProcessMenu(ACTION_SELECT);
    encoder.resetClicked(); //reset the position
  }

  if (clickedItem>0)
  {
    // Logic for Root menu
    if (menu.CurrentMenu==mnuRoot)
      switch (clickedItem)
      {
        case 1:
          menu.InitMenu(mnuSubmenu1,cntSubmenu1,1);
          break;
        case 2:
          menu.InitMenu(mnuSubmenu2,cntSubmenu2,1);
          break;
        case 3:
          menu.InitMenu(mnuSubmenu3,cntSubmenu3,1);
          break;
        case 4:
          // menu.MessageBox("Some message!");
          break; 
      }
    // Logic for Submenu 1
    else if (menu.CurrentMenu==mnuSubmenu1)
      switch (clickedItem)
      {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
          // menu.MessageBox("Item clicked");
          break;
        case 6:
          menu.InitMenu(mnuRoot,cntRoot,1);
          break;
      }
    // Logic for Submenu 2
    else if (menu.CurrentMenu==mnuSubmenu2)
      switch (clickedItem)
      {
        case 1:
          // menu.MessageBox("On");
          break;
        case 2:
          // menu.MessageBox("Off");
          break;
        case 3:
          menu.InitMenu(mnuRoot,cntRoot,2);
          break;
      }
    // Logic for Submenu 3
    else if (menu.CurrentMenu==mnuSubmenu3)
      switch (clickedItem)
      {
        case 1:
          // menu.MessageBox("Enabled");
          break;
        case 2:
          //menu.MessageBox("Disabled");
          break;
        case 3:
          menu.InitMenu(mnuRoot,cntRoot,3);
          break;
      }

  }
}

  void doChart() {
    Celcius_d = temp_sensor.readCelsius();
    dtostrf(Celcius_d, 4,2, Celsius_C);
    Serial.println(Celsius_C);
    display.clearDisplay();

    if (Celcius_d > 235.0)
    {
      digitalWrite(HEAT_PIN, LOW);
      setTopText(OFF, 112, 0, 2);
    }
    else if (Celcius_d == 235.0)
    {
      digitalWrite(HEAT_PIN, LOW);  
      setTopText("-", 112, 0, 2);
    }
    else if (Celcius_d < 235.0)
    {
      digitalWrite(HEAT_PIN, HIGH);
      setTopText(ON, 112, 0, 2);
    }

    setTopText(Celsius_C,0,0,2);
    drawChart();
    display.display();
    display.clearDisplay();

    if ((millis()-tempMillis) > intervalSensorRead) {
      addNewValue((uint8_t) Celcius_d);
      tempMillis=millis();
    }
    //chartPos=rand();
    delay(1000);
  }