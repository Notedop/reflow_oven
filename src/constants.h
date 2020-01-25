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

//Screen chart
#define numberOfReads 16
#define screenWidth 128
#define xWidth screenWidth/numberOfReads

#define OFF "L"
#define ON  "H"