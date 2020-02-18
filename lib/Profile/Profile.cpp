//
// Created by Raoul on 18/02/2020.
//

#include "Profile.h"

unsigned char Profile::getPreHeatTargetTemp() const {
    return preHeatTargetTemp;
}

void Profile::setPreHeatTargetTemp(unsigned char preHeatTargetTemp) {
    Profile::preHeatTargetTemp = preHeatTargetTemp;
}

unsigned char Profile::getPreHeatMaxTime() const {
    return preHeatMaxTime;
}

void Profile::setPreHeatMaxTime(unsigned char preHeatMaxTime) {
    Profile::preHeatMaxTime = preHeatMaxTime;
}

unsigned char Profile::getPreHeatHeaters() const {
    return preHeatHeaters;
}

void Profile::setPreHeatHeaters(unsigned char preHeatHeaters) {
    Profile::preHeatHeaters = preHeatHeaters;
}

unsigned char Profile::getSoakTargetTemp() const {
    return soakTargetTemp;
}

void Profile::setSoakTargetTemp(unsigned char soakTargetTemp) {
    Profile::soakTargetTemp = soakTargetTemp;
}

unsigned char Profile::getSoakMaxTime() const {
    return soakMaxTime;
}

void Profile::setSoakMaxTime(unsigned char soakMaxTime) {
    Profile::soakMaxTime = soakMaxTime;
}

unsigned char Profile::getSoakHeaters() const {
    return soakHeaters;
}

void Profile::setSoakHeaters(unsigned char soakHeaters) {
    Profile::soakHeaters = soakHeaters;
}

unsigned char Profile::getReflowTargetTemp() const {
    return reflowTargetTemp;
}

void Profile::setReflowTargetTemp(unsigned char reflowTargetTemp) {
    Profile::reflowTargetTemp = reflowTargetTemp;
}

unsigned char Profile::getReflowMaxTime() const {
    return reflowMaxTime;
}

void Profile::setReflowMaxTime(unsigned char reflowMaxTime) {
    Profile::reflowMaxTime = reflowMaxTime;
}

unsigned char Profile::getReflowHeaters() const {
    return reflowHeaters;
}

void Profile::setReflowHeaters(unsigned char reflowHeaters) {
    Profile::reflowHeaters = reflowHeaters;
}

unsigned char Profile::getCoolDownTargetTemp() const {
    return coolDownTargetTemp;
}

void Profile::setCoolDownTargetTemp(unsigned char coolDownTargetTemp) {
    Profile::coolDownTargetTemp = coolDownTargetTemp;
}

unsigned char Profile::getProfileNumber() const {
    return profileNumber;
}

void Profile::setProfileNumber(unsigned char profileNumber) {
    Profile::profileNumber = profileNumber;
}


Profile::Profile(unsigned char profileNumber, unsigned char preHeatTargetTemp, unsigned char preHeatMaxTime, unsigned char preHeatHeaters,
                 unsigned char soakTargetTemp, unsigned char soakMaxTime, unsigned char soakHeaters,
                 unsigned char reflowTargetTemp, unsigned char reflowMaxTime, unsigned char reflowHeaters,
                 unsigned char coolDownTargetTemp) : profileNumber(profileNumber), preHeatTargetTemp(preHeatTargetTemp),
                                                     preHeatMaxTime(preHeatMaxTime), preHeatHeaters(preHeatHeaters),
                                                     soakTargetTemp(soakTargetTemp), soakMaxTime(soakMaxTime),
                                                     soakHeaters(soakHeaters), reflowTargetTemp(reflowTargetTemp),
                                                     reflowMaxTime(reflowMaxTime), reflowHeaters(reflowHeaters),
                                                     coolDownTargetTemp(coolDownTargetTemp) {}

