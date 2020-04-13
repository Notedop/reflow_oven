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


void Profile::save() {

    byte startPosition = (profileNumber-1)*totalProfileValues;
    EEPROM.write(startPosition, profileNumber);

    EEPROM.write(++startPosition, preHeatTargetTemp);
    EEPROM.write(++startPosition, preHeatMaxTime);
    EEPROM.write(++startPosition, preHeatHeaters);
    EEPROM.write(++startPosition, preHeatPidP);
    EEPROM.write(++startPosition, preHeatPidI);
    EEPROM.write(++startPosition, preHeatPidD);

    EEPROM.write(++startPosition, soakTargetTemp);
    EEPROM.write(++startPosition, soakMaxTime);
    EEPROM.write(++startPosition, soakHeaters);
    EEPROM.write(++startPosition, soakPidP);
    EEPROM.write(++startPosition, soakPidI);
    EEPROM.write(++startPosition, soakPidD);

    EEPROM.write(++startPosition, reflowTargetTemp);
    EEPROM.write(++startPosition, reflowMaxTime);
    EEPROM.write(++startPosition, reflowHeaters);
    EEPROM.write(++startPosition, reflowPidP);
    EEPROM.write(++startPosition, reflowPidI);
    EEPROM.write(++startPosition, reflowPidD);


    EEPROM.write(++startPosition, coolDownTargetTemp);

}

void Profile::loadProfile(byte profileNumber) {

    byte startPosition = (profileNumber - 1) * totalProfileValues;
    Profile::profileNumber = EEPROM.read(startPosition);

    Profile::preHeatTargetTemp = EEPROM.read(++startPosition);
    Profile::preHeatMaxTime = EEPROM.read(++startPosition);
    Profile::preHeatHeaters = EEPROM.read(++startPosition);
    Profile::preHeatPidP = EEPROM.read(++startPosition);
    Profile::preHeatPidI = EEPROM.read(++startPosition);
    Profile::preHeatPidD = EEPROM.read(++startPosition);

    Profile::soakTargetTemp = EEPROM.read(++startPosition);
    Profile::soakMaxTime = EEPROM.read(++startPosition);
    Profile::soakHeaters = EEPROM.read(++startPosition);
    Profile::soakPidP = EEPROM.read(++startPosition);
    Profile::soakPidI = EEPROM.read(++startPosition);
    Profile::soakPidD = EEPROM.read(++startPosition);

    Profile::reflowTargetTemp = EEPROM.read(++startPosition);
    Profile::reflowMaxTime = EEPROM.read(++startPosition);
    Profile::reflowHeaters = EEPROM.read(++startPosition);
    Profile::reflowPidP = EEPROM.read(++startPosition);
    Profile::reflowPidI = EEPROM.read(++startPosition);
    Profile::reflowPidD = EEPROM.read(++startPosition);

    Profile::coolDownTargetTemp = EEPROM.read(++startPosition);

}

byte Profile::getPreHeatPidP() const {
    return preHeatPidP;
}

void Profile::setPreHeatPidP(byte preHeatPidP) {
    Profile::preHeatPidP = preHeatPidP;
}

byte Profile::getPreHeatPidI() const {
    return preHeatPidI;
}

void Profile::setPreHeatPidI(byte preHeatPidI) {
    Profile::preHeatPidI = preHeatPidI;
}

byte Profile::getPreHeatPidD() const {
    return preHeatPidD;
}

void Profile::setPreHeatPidD(byte preHeatPidD) {
    Profile::preHeatPidD = preHeatPidD;
}

byte Profile::getSoakPidP() const {
    return soakPidP;
}

void Profile::setSoakPidP(byte soakPidP) {
    Profile::soakPidP = soakPidP;
}

byte Profile::getSoakPidI() const {
    return soakPidI;
}

void Profile::setSoakPidI(byte soakPidI) {
    Profile::soakPidI = soakPidI;
}

byte Profile::getSoakPidD() const {
    return soakPidD;
}

void Profile::setSoakPidD(byte soakPidD) {
    Profile::soakPidD = soakPidD;
}

byte Profile::getReflowPidP() const {
    return reflowPidP;
}

void Profile::setReflowPidP(byte reflowPidP) {
    Profile::reflowPidP = reflowPidP;
}

byte Profile::getReflowPidI() const {
    return reflowPidI;
}

void Profile::setReflowPidI(byte reflowPidI) {
    Profile::reflowPidI = reflowPidI;
}

byte Profile::getReflowPidD() const {
    return reflowPidD;
}

void Profile::setReflowPidD(byte reflowPidD) {
    Profile::reflowPidD = reflowPidD;
}

