
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <max6675.h>

// Oled SPI interface 3.3volts!
#define OLED_MOSI   9 //D1 - PIN 15
#define OLED_CLK   10 //D0 - PIN 16
#define OLED_DC    11 //DC - PIN 17
#define OLED_CS    12 //CS - PIN 18
#define OLED_RESET 13 //RES - PIN 19

//MAX6675 3.3volts!
#define thermoDO 4 //SO - PIN 6
#define thermoCS 5 //CS - PIN 11
#define thermoCLK 6 //SCK - PIN 12

//SOLID STATE RELAYS
#define HEAT_PIN 14 // PIN 23
#define FAN_PIN 15 // PIN 24

//ROTARY ENCODER
#define BUTTON 
#define encoder0PinA 2  
#define encoder0PinB 3


MAX6675 temp_sensor;
Adafruit_SSD1306 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const uint8_t numberOfReads = 16;
const uint8_t screenWidth = 128;
const uint8_t xWidth = screenWidth/numberOfReads;

const char* OFF = "L";
const char* ON = "H";

char Celsius_C[8];
double Celcius_d;

uint8_t temperatureHistory[numberOfReads] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
uint8_t chartPos = 0;

uint16_t intervalSensorRead = 10000; 
uint32_t tempMillis = 0;

void setup() {
  
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, HIGH);
  pinMode(HEAT_PIN, OUTPUT);  
  digitalWrite(HEAT_PIN, LOW);
  
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin();
  // init done
  //display configurations
  display.setFont();
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  
  temp_sensor.begin(thermoCLK, thermoCS, thermoDO);

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

  Celcius_d = temp_sensor.readCelsius();
  dtostrf(Celcius_d, 4,2, Celsius_C);
  Serial.println(Celsius_C);
  display.clearDisplay();
  
  while (Serial.available() > 0)
  {
    Serial.read();
  }


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