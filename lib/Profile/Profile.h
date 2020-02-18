//
// Created by Raoul on 18/02/2020.
//

#ifndef REFLOW_OVEN_PROFILE_H
#define REFLOW_OVEN_PROFILE_H

class Profile {
public:
    Profile(unsigned char profileNumber, unsigned char preHeatTargetTemp, unsigned char preHeatMaxTime, unsigned char preHeatHeaters,
            unsigned char soakTargetTemp, unsigned char soakMaxTime, unsigned char soakHeaters,
            unsigned char reflowTargetTemp, unsigned char reflowMaxTime, unsigned char reflowHeaters,
            unsigned char coolDownTargetTemp);

    unsigned char getProfileNumber() const;\

    void setProfileNumber(unsigned char profileNumber);

    unsigned char getPreHeatTargetTemp() const;

    void setPreHeatTargetTemp(unsigned char preHeatTargetTemp);

    unsigned char getPreHeatMaxTime() const;

    void setPreHeatMaxTime(unsigned char preHeatMaxTime);

    unsigned char getPreHeatHeaters() const;

    void setPreHeatHeaters(unsigned char preHeatHeaters);

    unsigned char getSoakTargetTemp() const;

    void setSoakTargetTemp(unsigned char soakTargetTemp);

    unsigned char getSoakMaxTime() const;

    void setSoakMaxTime(unsigned char soakMaxTime);

    unsigned char getSoakHeaters() const;

    void setSoakHeaters(unsigned char soakHeaters);

    unsigned char getReflowTargetTemp() const;

    void setReflowTargetTemp(unsigned char reflowTargetTemp);

    unsigned char getReflowMaxTime() const;

    void setReflowMaxTime(unsigned char reflowMaxTime);

    unsigned char getReflowHeaters() const;

    void setReflowHeaters(unsigned char reflowHeaters);

    unsigned char getCoolDownTargetTemp() const;

    void setCoolDownTargetTemp(unsigned char coolDownTargetTemp);

private:
    Profile() {};
    unsigned char profileNumber;
    unsigned char preHeatTargetTemp;
    unsigned char preHeatMaxTime;
    unsigned char preHeatHeaters;

    unsigned char soakTargetTemp;
    unsigned char soakMaxTime;
    unsigned char soakHeaters;

    unsigned char reflowTargetTemp;
    unsigned char reflowMaxTime;
    unsigned char reflowHeaters;

    unsigned char coolDownTargetTemp;
};



#endif //REFLOW_OVEN_PROFILE_H
