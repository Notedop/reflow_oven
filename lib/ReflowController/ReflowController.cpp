//
// Created by Raoul on 19/02/2020.
//

#include "ReflowController.h"

ReflowController::ReflowController(MenuSystem &menu, MAX6675 &thermocouple, Profile &profile, Encoder *encoder,
                                   byte &heatPin1,
                                   byte &heatPin2) {

    ReflowController::menu = menu;
    ReflowController::thermocouple = thermocouple;
    ReflowController::profile = profile;
    ReflowController::encoder = encoder;
    ReflowController::heatPin1 = heatPin1;
    ReflowController::heatPin2 = heatPin2;

}

void ReflowController::Start() {

    //check if initialized
    if (heatPin1 == 0 || heatPin2 == 0)
        return;

    reflowState = REFLOW_STATE_IDLE;

    // Set window size
    windowSize = 2000;
    // Initialize time keeping variable
    nextCheck = millis();
    // Initialize thermocouple reading variable
    nextRead = millis();

    while (true) {
        // Current time
        unsigned long now;
        // Time to read thermocouple?
        if (millis() > nextRead) {
            // Read thermocouple next sampling period
            nextRead += SENSOR_SAMPLING_TIME;
            // Read current temperature
            input = thermocouple.readCelsius();

            // If thermocouple problem detected
            if (isnan(input)) {
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
//                digitalWrite(ledRedPin, !(digitalRead(ledRedPin)));
                // Increase seconds timer for reflow curve analysis
                timerSeconds++;
                // Send temperature and time stamp to serial
                Serial.print(timerSeconds);
                Serial.print(" ");
                Serial.print(setpoint);
                Serial.print(" ");
                Serial.print(input);
                Serial.print(" ");
                Serial.println(output);
            }
//            else {
//                // Turn off red LED
//                digitalWrite(ledRedPin, HIGH);
//            }

            // Clear LCD
//            lcd.clear();
            // Print current system state
            //Serial.println(reflowState);
//            lcd.print(lcdMessagesReflowStatus[reflowState]);
//            // Move the cursor to the 2 line
//            lcd.setCursor(0, 1);

            // If currently in error state
            if (reflowState == REFLOW_STATE_ERROR) {
                // No thermocouple wire connected
                Serial.println("TC Error!");
            } else {
                // Print current temperature
                //Serial.println(input);

                // Print degree Celsius symbol
                //Serial.println("C ");
            }
        }

        // Reflow oven controller state machine
        switch (reflowState) {
            case REFLOW_STATE_IDLE:
                // If oven temperature is still above room temperature
                if (input >= TEMPERATURE_ROOM) {
                    reflowState = REFLOW_STATE_TOO_HOT;
                } else {
                    // If switch is pressed to start reflow process
                    if (encoder->getClicked()) {
                        // Send header for CSV file
                        Serial.println("Time Setpoint Input Output");
                        // Intialize seconds timer for serial debug information
                        timerSeconds = 0;
                        // Initialize PID control window starting time
                        windowStartTime = millis();
                        // Ramp up to minimum soaking temperature
                        setpoint = TEMPERATURE_SOAK_MIN;
                        // Tell the PID to range between 0 and the full window size
                        reflowOvenPID.SetOutputLimits(0, windowSize);
                        reflowOvenPID.SetSampleTime(PID_SAMPLE_TIME);
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
                if (input >= TEMPERATURE_SOAK_MIN) {
                    // Chop soaking period into smaller sub-period
                    timerSoak = millis() + SOAK_MICRO_PERIOD;
                    // Set less agressive PID parameters for soaking ramp
                    reflowOvenPID.SetTunings(PID_KP_SOAK, PID_KI_SOAK, PID_KD_SOAK);
                    // Ramp up to first section of soaking temperature
                    setpoint = TEMPERATURE_SOAK_MIN + SOAK_TEMPERATURE_STEP;
                    // Proceed to soaking state
                    reflowState = REFLOW_STATE_SOAK;
                }
                break;

            case REFLOW_STATE_SOAK:
                // If micro soak temperature is achieved
                if (millis() > timerSoak) {
                    timerSoak = millis() + SOAK_MICRO_PERIOD;
                    // Increment micro setpoint
                    setpoint += SOAK_TEMPERATURE_STEP;
                    if (setpoint > TEMPERATURE_SOAK_MAX) {
                        // Set agressive PID parameters for reflow ramp
                        reflowOvenPID.SetTunings(PID_KP_REFLOW, PID_KI_REFLOW, PID_KD_REFLOW);
                        // Ramp up to first section of soaking temperature
                        setpoint = TEMPERATURE_REFLOW_MAX;
                        // Proceed to reflowing state
                        reflowState = REFLOW_STATE_REFLOW;
                    }
                }
                break;

            case REFLOW_STATE_REFLOW:
                // We need to avoid hovering at peak temperature for too long
                // Crude method that works like a charm and safe for the components
                if (input >= (TEMPERATURE_REFLOW_MAX - 5)) {
                    // Set PID parameters for cooling ramp
                    reflowOvenPID.SetTunings(PID_KP_REFLOW, PID_KI_REFLOW, PID_KD_REFLOW);
                    // Ramp down to minimum cooling temperature
                    setpoint = TEMPERATURE_COOL_MIN;
                    // Proceed to cooling state
                    reflowState = REFLOW_STATE_COOL;
                }
                break;

            case REFLOW_STATE_COOL:
                // If minimum cool temperature is achieve
                if (input <= TEMPERATURE_COOL_MIN) {
                    // Retrieve current time for buzzer usage
                    buzzerPeriod = millis() + 1000;
                    // Turn on buzzer and green LED to indicate completion
//                    digitalWrite(ledGreenPin, LOW);
//                    digitalWrite(buzzerPin, HIGH);
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

        if (encoder->getClicked()) {
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
