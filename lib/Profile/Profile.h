//
// Created by Raoul on 18/02/2020.
//

#ifndef REFLOW_OVEN_PROFILE_H
#define REFLOW_OVEN_PROFILE_H

#include <Arduino.h>

class Profile {
public:
    Profile(byte profileNumber, byte preHeatTargetTemp, byte preHeatMaxTime, byte preHeatHeaters,
            byte soakTargetTemp, byte soakMaxTime, byte soakHeaters,
            byte reflowTargetTemp, byte reflowMaxTime, byte reflowHeaters,
            byte coolDownTargetTemp);

    byte getProfileNumber() const;\

    void setProfileNumber(byte number);

    byte getPreHeatTargetTemp() const;

    void setPreHeatTargetTemp(byte targetTemp);

    byte getPreHeatMaxTime() const;

    void setPreHeatMaxTime(byte maxTime);

    byte getPreHeatHeaters() const;

    void setPreHeatHeaters(byte heaters);

    byte getSoakTargetTemp() const;

    void setSoakTargetTemp(byte targetTemp);

    byte getSoakMaxTime() const;

    void setSoakMaxTime(byte maxTime);

    byte getSoakHeaters() const;

    void setSoakHeaters(byte heaters);

    byte getReflowTargetTemp() const;

    void setReflowTargetTemp(byte targetTemp);

    byte getReflowMaxTime() const;

    void setReflowMaxTime(byte maxTime);

    byte getReflowHeaters() const;

    void setReflowHeaters(byte heaters);

    byte getCoolDownTargetTemp() const;

    void setCoolDownTargetTemp(byte targetTemp);

    void save();

    void loadProfile(byte profileNumber);

private:
    Profile() {};

    const static byte totalProfileValues = 11;

    byte profileNumber;
    byte preHeatTargetTemp;
    byte preHeatMaxTime;
    byte preHeatHeaters;
    byte soakTargetTemp;
    byte soakMaxTime;
    byte soakHeaters;
    byte reflowTargetTemp;
    byte reflowMaxTime;
    byte reflowHeaters;
    byte coolDownTargetTemp;

};



#endif //REFLOW_OVEN_PROFILE_H
