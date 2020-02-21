//
// Created by Raoul on 18/02/2020.
//

#include <EEPROM.h>
#include "Profile.h"

byte Profile::getPreHeatTargetTemp() const {
    return preHeatTargetTemp;
}

void Profile::setPreHeatTargetTemp(byte targetTemp) {
    Profile::preHeatTargetTemp = targetTemp;
}

byte Profile::getPreHeatMaxTime() const {
    return preHeatMaxTime;
}

void Profile::setPreHeatMaxTime(byte maxTime) {
    Profile::preHeatMaxTime = maxTime;
}

byte Profile::getPreHeatHeaters() const {
    return preHeatHeaters;
}

void Profile::setPreHeatHeaters(byte heaters) {
    Profile::preHeatHeaters = heaters;
}

byte Profile::getSoakTargetTemp() const {
    return soakTargetTemp;
}

void Profile::setSoakTargetTemp(byte targetTemp) {
    Profile::soakTargetTemp = targetTemp;
}

byte Profile::getSoakMaxTime() const {
    return soakMaxTime;
}

void Profile::setSoakMaxTime(byte maxTime) {
    Profile::soakMaxTime = maxTime;
}

byte Profile::getSoakHeaters() const {
    return soakHeaters;
}

void Profile::setSoakHeaters(byte heaters) {
    Profile::soakHeaters = heaters;
}

byte Profile::getReflowTargetTemp() const {
    return reflowTargetTemp;
}

void Profile::setReflowTargetTemp(byte targetTemp) {
    Profile::reflowTargetTemp = targetTemp;
}

byte Profile::getReflowMaxTime() const {
    return reflowMaxTime;
}

void Profile::setReflowMaxTime(byte maxTime) {
    Profile::reflowMaxTime = maxTime;
}

byte Profile::getReflowHeaters() const {
    return reflowHeaters;
}

void Profile::setReflowHeaters(byte heaters) {
    Profile::reflowHeaters = heaters;
}

byte Profile::getCoolDownTargetTemp() const {
    return coolDownTargetTemp;
}

void Profile::setCoolDownTargetTemp(byte targetTemp) {
    Profile::coolDownTargetTemp = targetTemp;
}

byte Profile::getProfileNumber() const {
    return profileNumber;
}

void Profile::setProfileNumber(byte number) {
    Profile::profileNumber = number;
}


Profile::Profile(byte profileNumber, byte preHeatTargetTemp, byte preHeatMaxTime, byte preHeatHeaters,
                 byte soakTargetTemp, byte soakMaxTime, byte soakHeaters,
                 byte reflowTargetTemp, byte reflowMaxTime, byte reflowHeaters,
                 byte coolDownTargetTemp) : profileNumber(profileNumber), preHeatTargetTemp(preHeatTargetTemp),
                                                     preHeatMaxTime(preHeatMaxTime), preHeatHeaters(preHeatHeaters),
                                                     soakTargetTemp(soakTargetTemp), soakMaxTime(soakMaxTime),
                                                     soakHeaters(soakHeaters), reflowTargetTemp(reflowTargetTemp),
                                                     reflowMaxTime(reflowMaxTime), reflowHeaters(reflowHeaters),
                                                     coolDownTargetTemp(coolDownTargetTemp) {}

void Profile::save() {

    byte startPosition = (profileNumber-1)*totalProfileValues;
    EEPROM.write(startPosition, profileNumber);
    EEPROM.write(++startPosition, preHeatTargetTemp);
    EEPROM.write(++startPosition, preHeatMaxTime);
    EEPROM.write(++startPosition, preHeatHeaters);
    EEPROM.write(++startPosition, soakTargetTemp);
    EEPROM.write(++startPosition, soakMaxTime);
    EEPROM.write(++startPosition, soakHeaters);
    EEPROM.write(++startPosition, reflowTargetTemp);
    EEPROM.write(++startPosition, reflowMaxTime);
    EEPROM.write(++startPosition, reflowHeaters);
    EEPROM.write(++startPosition, coolDownTargetTemp);

}

void Profile::loadProfile(byte profileNumber) {

    byte startPosition = (profileNumber - 1) * totalProfileValues;
    Profile::profileNumber = EEPROM.read(startPosition);
    Profile::preHeatTargetTemp = EEPROM.read(++startPosition);
    Profile::preHeatMaxTime = EEPROM.read(++startPosition);
    Profile::preHeatHeaters = EEPROM.read(++startPosition);
    Profile::soakTargetTemp = EEPROM.read(++startPosition);
    Profile::soakMaxTime = EEPROM.read(++startPosition);
    Profile::soakHeaters = EEPROM.read(++startPosition);
    Profile::reflowTargetTemp = EEPROM.read(++startPosition);
    Profile::reflowMaxTime = EEPROM.read(++startPosition);
    Profile::reflowHeaters = EEPROM.read(++startPosition);
    Profile::coolDownTargetTemp = EEPROM.read(++startPosition);

}