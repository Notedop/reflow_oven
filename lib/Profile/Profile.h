//
// Created by Raoul on 18/02/2020.
//

#ifndef REFLOW_OVEN_PROFILE_H
#define REFLOW_OVEN_PROFILE_H

#include <Arduino.h>

class Profile {
public:

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

    byte getPreHeatPidP() const;

    void setPreHeatPidP(byte preHeatPidP);

    byte getPreHeatPidI() const;

    void setPreHeatPidI(byte preHeatPidI);

    byte getPreHeatPidD() const;

    void setPreHeatPidD(byte preHeatPidD);

    byte getSoakPidP() const;

    void setSoakPidP(byte soakPidP);

    byte getSoakPidI() const;

    void setSoakPidI(byte soakPidI);

    byte getSoakPidD() const;

    void setSoakPidD(byte soakPidD);

    byte getReflowPidP() const;

    void setReflowPidP(byte reflowPidP);

    byte getReflowPidI() const;

    void setReflowPidI(byte reflowPidI);

    byte getReflowPidD() const;

    void setReflowPidD(byte reflowPidD);

    void save();

    void loadProfile(byte profileNumber);

    Profile() = default;

private:

    const static byte totalProfileValues = 19;

    byte profileNumber=0;
    byte preHeatTargetTemp=0;
    byte preHeatMaxTime=0;
    byte preHeatHeaters=0;
    byte preHeatPidP=0;
    byte preHeatPidI=0;
    byte preHeatPidD=0;
    byte soakTargetTemp=0;
    byte soakMaxTime=0;
    byte soakHeaters=0;
    byte soakPidP=0;
    byte soakPidI=0;
    byte soakPidD=0;
    byte reflowTargetTemp=0;
    byte reflowMaxTime=0;
    byte reflowHeaters=0;
    byte reflowPidP=0;
    byte reflowPidI=0;
    byte reflowPidD=0;

    byte coolDownTargetTemp=0;

};



#endif //REFLOW_OVEN_PROFILE_H
