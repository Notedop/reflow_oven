/*******************************************************************************
* Title: Reflow Oven Controller
* Version: 2.00
* Date: 19-02-2020
* Company: Rocket Scream Electronics
* Author: Lim Phang Moh
* Website: www.rocketscream.com
*
 *Adjusted by: Raoul van Hal
 *
* Brief
* =====
* This is an example firmware for our Arduino compatible reflow oven controller.
* The reflow curve used in this firmware is meant for lead-free profile
* (it's even easier for leaded process!). You'll need to use the MAX31855
* library for Arduino if you are having a shield of v1.60 & above which can be
* downloaded from our GitHub repository. Please check our wiki
* (www.rocketscream.com/wiki) for more information on using this piece of code
* together with the reflow oven controller shield.
*
* Temperature (Degree Celcius)                 Magic Happens Here!
* 245-|                                               x  x
*     |                                            x        x
*     |                                         x              x
*     |                                      x                    x
* 200-|                                   x                          x
*     |                              x    |                          |   x
*     |                         x         |                          |       x
*     |                    x              |                          |
* 150-|               x                   |                          |
*     |             x |                   |                          |
*     |           x   |                   |                          |
*     |         x     |                   |                          |
*     |       x       |                   |                          |
*     |     x         |                   |                          |
*     |   x           |                   |                          |
* 30 -| x             |                   |                          |
*     |<  60 - 90 s  >|<    90 - 120 s   >|<       90 - 120 s       >|
*     | Preheat Stage |   Soaking Stage   |       Reflow Stage       | Cool
*  0  |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*                                                                Time (Seconds)
*
* This firmware owed very much on the works of other talented individuals as
* follows:
* ==========================================
* Brett Beauregard (www.brettbeauregard.com)
* ==========================================
* Author of Arduino PID library. On top of providing industry standard PID
* implementation, he gave a lot of help in making this reflow oven controller
* possible using his awesome library.
*
* ==========================================
* Limor Fried of Adafruit (www.adafruit.com)
* ==========================================
* Author of Arduino MAX6675 library. Adafruit has been the source of tonnes of
* tutorials, examples, and libraries for everyone to learn.
*
* Disclaimer
* ==========
* Dealing with high voltage is a very dangerous act! Please make sure you know
* what you are dealing with and have proper knowledge before hand. Your use of
* any information or materials on this reflow oven controller is entirely at
* your own risk, for which we shall not be liable.
*
* Licences
* ========
* This reflow oven controller hardware and firmware are released under the
* Creative Commons Share Alike v3.0 license
* http://creativecommons.org/licenses/by-sa/3.0/
* You are free to take this piece of code, use it and modify it.
* All we ask is attribution including the supporting libraries used in this
* firmware.
*
* Required Libraries
* ==================
* - Arduino PID Library:
*   >> https://github.com/br3ttb/Arduino-PID-Library
* - MAX31855 Library (for board v1.60 & above):
*   >> https://github.com/rocketscream/MAX31855
* - MAX6675 Library (for board v1.50 & below):
*   >> https://github.com/adafruit/MAX6675-library
*
* Revision  Description
* ========  ===========
* 1.20			Adds supports for v1.60 (and above) of Reflow Oven Controller
*           Shield:
*					  - Uses MAX31855KASA+ chip and pin reassign (allowing A4 & A5 (I2C)
*             to be used for user application).
*					  - Uses analog based switch (allowing D2 & D3 to be used for user
*						  application).
*						Adds waiting state when temperature too hot to start reflow process.
*						Corrected thermocouple disconnect error interpretation (MAX6675).
* 1.10      Arduino IDE 1.0 compatible.
* 1.00      Initial public release.
*******************************************************************************/
#ifndef REFLOW_OVEN_REFLOWCONTROLLER_H
#define REFLOW_OVEN_REFLOWCONTROLLER_H
// ***** INCLUDES *****
#include <max6675.h>
#include <PID_v1.h>
#include <MenuSystem.h>
#include <Profile.h>
#include "constants.h"

class ReflowController {
public:
    //ReflowController() : profile(Profile(0,0,0,0,0,0,0,0,0,0,0)){};
    ReflowController(MenuSystem &menu, MAX6675 &thermocouple, Profile &profile) : menu(menu), thermocouple(thermocouple),
                                                                                 profile(profile) {

    }

    void Start();

private:

    MenuSystem menu;
    MAX6675 thermocouple;
    Profile profile;

    // ***** DEGREE SYMBOL FOR LCD *****
    byte degree[8] = { 140, 146, 146, 140, 128, 128, 128, 128};

    // ***** PID CONTROL VARIABLES *****
    short setpoint = 0.0;
    short input  = 0.0;
    short output  = 0.0;
    double kp = PID_KP_PREHEAT;
    double ki = PID_KI_PREHEAT;
    double kd = PID_KD_PREHEAT;
    byte windowSize  = 0;
    unsigned long windowStartTime =0;
    unsigned long nextCheck =0;
    unsigned long nextRead =0;
    unsigned long timerSoak =0;
    unsigned long buzzerPeriod =0;

    // Reflow oven controller state machine state variable
    reflowState_t reflowState = REFLOW_STATE_IDLE;

    // Reflow oven controller status
    reflowStatus_t reflowStatus =  REFLOW_STATUS_OFF;
    ;

    // Switch debounce state machine state variable
    debounceState_t debounceState = DEBOUNCE_STATE_IDLE;

    // Switch debounce timer
    long lastDebounceTime = 0;

    // Switch press status
    switch_t switchStatus = SWITCH_NONE;

    // Seconds timer
    int timerSeconds = 0;

    //PID reflowOvenPID = PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);



};


#endif //REFLOW_OVEN_REFLOWCONTROLLER_H
