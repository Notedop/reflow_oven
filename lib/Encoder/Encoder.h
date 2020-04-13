#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <Arduino.h>

class Encoder {
  public:
   // constructor : sets pins as inputs and turns on pullup resistors

    Encoder( int8_t PinA, int8_t PinB, int8_t PinC) : pin_a ( PinA), pin_b( PinB ), pin_c( PinC ) {
      // set pin a and b to be input
      pinMode(pin_a, INPUT_PULLUP);
      pinMode(pin_b, INPUT_PULLUP);
      pinMode(pin_c, INPUT_PULLUP);
    };

    // call this from your interrupt function (from http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html)
    void update () {

      //static int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};     // 2 interrupts
      static int8_t lookup_table[] = {0,0,0,-1,0,0,1,0,0,1,0,0,-1,0,0,0};         // 1 interrupt, will loose 50% resolution.
      static uint8_t enc_val = 0;
      
      enc_val = enc_val << 2;
      //enc_val = enc_val | ((PIND & 0b1100) >> 2)                                //2 interrupts: attached to arduino pin 2 and 3
      enc_val = enc_val | ((PIND & 0b11000) >> 3);                                //1 interrupt: attached to arduino pin 3 and 4 where 3 is interrupt!
  
      position = position + lookup_table[enc_val & 0b1111];
    };

    // returns current position

    char getPosition () {
      return position;
    };

    // set the position value

    void setPosition ( char p) {
      position = p;
    };

    bool getClicked (){
      return clicked;
    }

    void setClicked (bool c){
      clicked=c;
    }

    void resetClicked() {
      clicked=false;
    }

  private:

    char position = 0;

    int8_t pin_a;

    int8_t pin_b;

    int8_t pin_c;

    bool clicked = false;

};

#endif // __ENCODER_H__