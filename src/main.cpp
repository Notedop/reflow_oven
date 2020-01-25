#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <max6675.h>
#include <Encoder.h>
#include <constants.h>

MAX6675 temp_sensor;
Adafruit_SSD1306 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Encoder encoder(encoder0PinA, encoder0PinB);

char Celsius_C[8];
double Celcius_d;

uint8_t temperatureHistory[numberOfReads] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
uint8_t chartPos = 0;

uint16_t intervalSensorRead = 10000; 
uint32_t tempMillis = 0;

void doEncoder(){
    encoder.update();
    Serial.println( encoder.getPosition() );
}

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

  attachInterrupt(0, doEncoder , CHANGE);  // encoder pin on interrupt 0 - pin 2

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