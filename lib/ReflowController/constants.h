//
// Created by Raoul on 19/02/2020.
//

#ifndef REFLOW_OVEN_CONSTANTS_H
#define REFLOW_OVEN_CONSTANTS_H


// ***** TYPE DEFINITIONS *****
typedef enum REFLOW_STATE {
    REFLOW_STATE_IDLE,
    REFLOW_STATE_PREHEAT,
    REFLOW_STATE_SOAK,
    REFLOW_STATE_REFLOW,
    REFLOW_STATE_COOL,
    REFLOW_STATE_COMPLETE,
    REFLOW_STATE_TOO_HOT,
    REFLOW_STATE_ERROR
} reflowState_t;

typedef enum REFLOW_STATUS {
    REFLOW_STATUS_OFF,
    REFLOW_STATUS_ON
} reflowStatus_t;

typedef enum SWITCH {
    SWITCH_NONE,
    SWITCH_1,
    SWITCH_2
} switch_t;

typedef enum DEBOUNCE_STATE {
    DEBOUNCE_STATE_IDLE,
    DEBOUNCE_STATE_CHECK,
    DEBOUNCE_STATE_RELEASE
} debounceState_t;

// ***** CONSTANTS *****
#define TEMPERATURE_ROOM 50
#define TEMPERATURE_SOAK_MIN 150
#define TEMPERATURE_SOAK_MAX 200
#define TEMPERATURE_REFLOW_MAX 250
#define TEMPERATURE_COOL_MIN 100
#define SENSOR_SAMPLING_TIME 1000
#define SOAK_TEMPERATURE_STEP 5
#define SOAK_MICRO_PERIOD 9000
#define DEBOUNCE_PERIOD_MIN 50

// ***** PID PARAMETERS *****
// ***** PRE-HEAT STAGE *****
#define PID_KP_PREHEAT 100
#define PID_KI_PREHEAT 0.025
#define PID_KD_PREHEAT 20
// ***** SOAKING STAGE *****
#define PID_KP_SOAK 300
#define PID_KI_SOAK 0.05
#define PID_KD_SOAK 250
// ***** REFLOW STAGE *****
#define PID_KP_REFLOW 300
#define PID_KI_REFLOW 0.05
#define PID_KD_REFLOW 350
#define PID_SAMPLE_TIME 1000

// ***** LCD MESSAGES *****
//const char *lcdMessagesReflowStatus[] = {
//        "Ready",
//        "Pre-heat",
//        "Soak",
//        "Reflow",
//        "Cool",
//        "Complete",
//        "Wait,hot",
//        "Error"
//};

#endif //REFLOW_OVEN_CONSTANTS_H
