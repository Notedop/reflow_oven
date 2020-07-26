// required for "PROGMEM const char " and "PROGMEM"
#include <avr/pgmspace.h>

// texts for menus

const char itmSave[] PROGMEM = "Save";
const char itmEdit[] PROGMEM = "Edit";
const char itmStart[] PROGMEM = "Start";
const char itmBack[] PROGMEM = "< Back";
const char itmTarget[] PROGMEM = "Target Temp:";
const char itmMaxTime[] PROGMEM = "Max Time:";
const char itmRisePerSeconds[] PROGMEM = "C/Sec:";
const char itmOn[] PROGMEM = "ON";
const char itmOff[] PROGMEM = "OFF";
const char itmHeaters[] PROGMEM = "Heaters";
const char itmTop[] PROGMEM = "Top";
const char itmBottom[] PROGMEM = "Bottom";
const char itmBoth[] PROGMEM = "Both";

const char itmPreheat[] PROGMEM = "Pre-heat";
const char itmSoak[] PROGMEM = "Soak";
const char itmReflow[] PROGMEM = "Reflow";
const char itmCool[] PROGMEM = "Cool";
const char itmDoor[] PROGMEM = "Door";


const char itmPID[] PROGMEM = "PID settings";
const char itmProportional[] PROGMEM = "Proportional";
const char itmIntegral[] PROGMEM = "Integral";
const char itmDerivative[] PROGMEM = "Derivative";

const char itmRoot[] PROGMEM = "Reflow Oven Menu";
const char itmSubmenuProfiles[] PROGMEM = "Profiles";
const char itmNewProfile[] PROGMEM = "New profile";
const char itmProfileX[] PROGMEM = "Profile";

const char itmProfile1[] PROGMEM = "Profile 1";
const char itmProfile2[] PROGMEM = "Profile 2";
const char itmProfile3[] PROGMEM = "Profile 3";

const char itmSubmenuSettings[] PROGMEM = "Settings";
const char itmCalibrate[] PROGMEM = "Calibrate";


////////////////////////////////////////////////////////////////
// menus - first item is menu title and it does not count toward cnt

const char *const mnuRoot[] PROGMEM = {itmRoot, itmSubmenuProfiles, itmSubmenuSettings};
const int cntRoot PROGMEM = 2;

//select existing or new profile
const char *const mnuSubProfiles[] PROGMEM = {itmSubmenuProfiles, itmNewProfile, itmProfile1, itmProfile2, itmProfile3, itmBack};
const int cntSubProfiles = 5;

    //new/edit profile menu:
    const char *const mnuSubEditProfile[] PROGMEM = {itmNewProfile, itmProfileX, itmPreheat, itmSoak, itmReflow, itmCool, itmSave, itmStart, itmBack};
    const int cntSubEditProfile = 8;

        const char *const mnuSubPreheat[] PROGMEM = {itmPreheat, itmTarget, itmMaxTime, itmRisePerSeconds, itmHeaters, itmPID, itmBack};
        const int cntSubPreheat = 6;
        const char *const mnuSubSoak[] PROGMEM = {itmSoak, itmTarget, itmMaxTime, itmHeaters, itmPID, itmBack};
        const int cntSubSoak = 5;
        const char *const mnuSubReflow[] PROGMEM = {itmPreheat, itmTarget, itmMaxTime, itmRisePerSeconds, itmHeaters, itmPID, itmBack};
        const int cntSubReflow = 6;
        const char *const mnuSubCool[] PROGMEM = {itmCool, itmTarget, itmBack};
        const int cntSubCool = 2;

const char *const mnuSubProfile1[] PROGMEM = {itmProfile1, itmEdit, itmStart, itmBack};
const int cntSubProfile1 = 3;
const char *const mnuSubProfile2[] PROGMEM = {itmProfile2, itmEdit, itmStart, itmBack};
const int cntSubProfile2 = 3;
const char *const mnuSubProfile3[] PROGMEM = {itmProfile3, itmEdit, itmStart, itmBack};
const int cntSubProfile3 = 3;

const char *const mnuSubPID[] PROGMEM = {itmPID, itmProportional, itmIntegral, itmDerivative, itmBack};
const int cntSubPID = 4;


