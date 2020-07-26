//
// Created by Raoul on 19/02/2020.
//

#include "ReflowController.h"

// ***** LCD MESSAGES *****
const char *lcdMessagesReflowStatus[] = {
        "Ready",
        "Pre-heat",
        "Soak",
        "Reflow",
        "Cool",
        "Complete",
        "Wait,hot",
        "Error"
};

ReflowController::ReflowController(MenuSystem &menu, Profile &profile, Encoder *encoder,
                                   byte &heatPin1,
                                   byte &heatPin2) {

    ReflowController::menu = menu;
    ReflowController::profile = profile;
    ReflowController::encoder = encoder;
    ReflowController::heatPin1 = heatPin1;
    ReflowController::heatPin2 = heatPin2;

}

void ReflowController::Start() {

    MAX6675 thermocouple(6,5,7);
    delay(500);

    //check if initialized
    if (heatPin1 == 0 || heatPin2 == 0)
        return;

    reflowState = REFLOW_STATE_IDLE;

    // Initialize time keeping variable
    nextCheck = millis();
    // Initialize thermocouple reading variable
    nextRead = millis();

    double previousTemp = 0.0;
    double currentTemp = 0.0;

    while (true) {
        // Current time
        unsigned long now;

        // Time to read thermocouple?
        if (millis() > nextRead) {
            // Read thermocouple next sampling period
            nextRead += SENSOR_SAMPLING_TIME;

            // Set rise temp based on current versus previously measured temp.
            // take PID_SAMPLE_TIME in account. 1000.0 = 1 second. If we sample every 250MS
            // then we need to divide the rise temperature through 1000.0/PID_SAMPLE_TIME so we can calculate
            // the average rise per second and correct if needed.
            currentTemp = thermocouple.readCelsius();
            input = (currentTemp-previousTemp) / (1000.0/PID_SAMPLE_TIME);
            previousTemp = currentTemp;

            // If thermocouple problem detected
            if (isnan(previousTemp)) {
                // Illegal operation
                reflowState = REFLOW_STATE_ERROR;
                reflowStatus = REFLOW_STATUS_OFF;
            }
        }

        if (millis() > nextCheck) {
            // Check input in the next seconds
            nextCheck += 1000;
            // If reflow process is on going
            if (reflowStatus == REFLOW_STATUS_ON) {
                // Toggle red LED as system heart beat
//               digitalWrite(ledRedPin, !(digitalRead(ledRedPin)));
                // Increase seconds timer for reflow curve analysis
                timerSeconds++;
                // Send temperature and time stamp to serial
                Serial.print(timerSeconds);
                Serial.print(" ");
                Serial.print(setpoint);
                Serial.print(" ");
                Serial.print(input);
                Serial.print(" ");
                Serial.print(output);
                Serial.print(" ");
                Serial.print(previousTemp);
                Serial.print(" ");
                Serial.println(lcdMessagesReflowStatus[reflowState]);

            }

            //do screen updates here
            byte minValue = 1;
            byte maxValue = 250;
            byte inputValue = currentTemp;
            menu.ShowInputBox(lcdMessagesReflowStatus[reflowState], minValue, maxValue,
                              inputValue);

            // If currently in error state
            if (reflowState == REFLOW_STATE_ERROR) {
                // No thermocouple wire connected
                Serial.println("TC Error!");
            }
        }

        // Reflow oven controller state machine
        switch (reflowState) {
            case REFLOW_STATE_IDLE:
                // If oven temperature is still above room temperature
                if (previousTemp >= TEMPERATURE_ROOM) {
                    reflowState = REFLOW_STATE_TOO_HOT;
                } else {
                    // If switch is pressed to start reflow process
                    if (encoder->isClicked()) {
                        // Send header for CSV file
                        Serial.println("Time Setpoint Input Output Temp reflowState");
                        // Intialize seconds timer for serial debug information
                        timerSeconds = 0;
                        // Initialize PID control window starting time
                        windowStartTime = millis();
                        // Ramp up to minimum soaking temperature using calculated rise temp.
                        setpoint = ((double (profile.getPreHeatTargetTemp()) - double (TEMPERATURE_ROOM))/profile.getPreHeatMaxTime()) / (1000.0/PID_SAMPLE_TIME) ;
                        // Tell the PID to range between 0 and the full window size
                        reflowOvenPID.SetOutputLimits(0, windowSize);
                        reflowOvenPID.SetSampleTime(PID_SAMPLE_TIME);
                        reflowOvenPID.SetTunings(profile.getPreHeatPidP(), profile.getPreHeatPidI(), profile.getPreHeatPidD());
                        // Turn the PID on
                        reflowOvenPID.SetMode(AUTOMATIC);
                        // Proceed to preheat stage
                        reflowState = REFLOW_STATE_PREHEAT;
                        encoder->resetClicked();
                    }
                }
                break;

            case REFLOW_STATE_PREHEAT:
                reflowStatus = REFLOW_STATUS_ON;
                // If minimum soak temperature is achieve
                if (previousTemp >= profile.getPreHeatTargetTemp()) {
                    // Chop soaking period into smaller sub-period
                    //timerSoak = millis() + SOAK_MICRO_PERIOD;
                    // Set less agressive PID parameters for soaking ramp
                    reflowOvenPID.SetTunings(profile.getSoakPidP(), profile.getSoakPidI(), profile.getSoakPidD());
                    // Ramp up to first section of soaking temperature
                    setpoint =  (double(profile.getSoakTargetTemp())- double(profile.getPreHeatTargetTemp()))/profile.getSoakMaxTime() / (1000.0/PID_SAMPLE_TIME) ;
                    // Proceed to soaking state
                    reflowState = REFLOW_STATE_SOAK;
                }
                break;

            case REFLOW_STATE_SOAK:
                // If micro soak temperature is achieved
                if (previousTemp >= profile.getSoakTargetTemp()) {
                    //timerSoak = millis() + SOAK_MICRO_PERIOD;
//                    // Increment micro setpoint
//                    setpoint += SOAK_TEMPERATURE_STEP;
//                    if (setpoint > TEMPERATURE_SOAK_MAX) {
                    // Set agressive PID parameters for reflow ramp
                    reflowOvenPID.SetTunings(profile.getReflowPidP(), profile.getReflowPidI(), profile.getReflowPidD());
                    // Ramp up to first section of soaking temperature
                    setpoint =  (double(profile.getReflowTargetTemp())- double(profile.getSoakTargetTemp()))/profile.getReflowMaxTime() / (1000.0/PID_SAMPLE_TIME) ;
                    // Proceed to reflowing state
                    reflowState = REFLOW_STATE_REFLOW;

                }
                break;

            case REFLOW_STATE_REFLOW:
                if (previousTemp >= profile.getReflowTargetTemp()) {
                    // Ramp down to minimum cooling temperature
                    setpoint = -1000.0;
                    // Proceed to cooling state
                    reflowState = REFLOW_STATE_COOL;
                }
                break;

            case REFLOW_STATE_COOL:
                // If minimum cool temperature is achieve
                if (previousTemp <= profile.getCoolDownTargetTemp()) {
                    // Turn off reflow process
                    reflowStatus = REFLOW_STATUS_OFF;
                    // Proceed to reflow Completion state
                    reflowState = REFLOW_STATE_COMPLETE;
                }
                break;

            case REFLOW_STATE_COMPLETE:
                if (millis() > buzzerPeriod) {
                    // Turn off buzzer and green LED
//                    digitalWrite(buzzerPin, LOW);
//                    digitalWrite(ledGreenPin, HIGH);
                    // Reflow process ended
                    reflowState = REFLOW_STATE_IDLE;
                }
                break;

            case REFLOW_STATE_TOO_HOT:
                // If oven temperature drops below room temperature
                Serial.print("TOO HOT: ");
                Serial.println(currentTemp);
                if (input < TEMPERATURE_ROOM) {
                    // Ready to reflow
                    reflowState = REFLOW_STATE_IDLE;
                }
                break;

            case REFLOW_STATE_ERROR:
                // If thermocouple problem is still present

                if (isnan(input)) {
                    // Wait until thermocouple wire is connected
                    reflowState = REFLOW_STATE_ERROR;
                } else {
                    // Clear to perform reflow process
                    reflowState = REFLOW_STATE_IDLE;
                }
                break;
        }

        // If switch 1 is pressed
        if (switchStatus == SWITCH_1) {
            // If currently reflow process is on going
            if (reflowStatus == REFLOW_STATUS_ON) {
                // Button press is for cancelling
                // Turn off reflow process
                reflowStatus = REFLOW_STATUS_OFF;
                // Reinitialize state machine
                reflowState = REFLOW_STATE_COMPLETE;
            }
        }

        if (encoder->isClicked()) {
            switchStatus = SWITCH_1;
        } else {
            switchStatus = SWITCH_NONE;
        }

        // PID computation and SSR control
        if (reflowStatus == REFLOW_STATUS_ON) {
            now = millis();
            reflowOvenPID.Compute();
            if ((now - windowStartTime) > windowSize) {
                // Time to shift the Relay Window
                windowStartTime += windowSize;
            }
            if (output > (now - windowStartTime)) {
                digitalWrite(heatPin1, HIGH);
                digitalWrite(heatPin2, HIGH);
            } else {
                digitalWrite(heatPin1, LOW);
                digitalWrite(heatPin2, LOW);
            }
        }
            // Reflow oven process is off, ensure oven is off
        else {
            digitalWrite(heatPin1, LOW);
            digitalWrite(heatPin2, LOW);
        }

        if (reflowState == REFLOW_STATE_COMPLETE)
            break;
    }
}
