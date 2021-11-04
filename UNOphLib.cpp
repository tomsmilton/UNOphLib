/*
File: UNOphLib.cpp https://github.com/unicorntom/UNOphLib/

Written by Thomas Milton, some code taken from: https://github.com/DFRobot/DFRobot_PH

v1.0
04-Nov-2021


** Notes **
Project requires EEPROMex.h to be installed in order to function.
*/

#include <Arduino.h>
#include <EEPROMex.h> // This library  is needed for the library to run.
#include <UNOphLib.h>

void UNOphLib::begin(int address_a, float ph_a, int address_b, float ph_b, int voltage_pin)
{ // This begin function sets key variables that will then be used later
    // This could be removed by directly writing to the private variables in the function call.
    _address_a = address_a;
    _address_b = address_b;
    _ph_a = ph_a;
    _ph_b = ph_b;
    _voltage_pin = voltage_pin;
    _a_voltage = EEPROM.readFloat(_address_a);
    _b_voltage = EEPROM.readFloat(_address_b);
}

void UNOphLib::calibrate_a()
{
    _voltage = analogRead(_voltage_pin) / 1024.0 * 5000;
    _a_voltage = _voltage;
    EEPROM.updateFloat(_address_a, _voltage);
    Serial.println("Voltage saved to EEPROM");
    delay(2000); // 2 second delay to prevent writing too frequently to EEPROM
}

void UNOphLib::calibrate_b()
{
    _voltage = analogRead(_voltage_pin) / 1024.0 * 5000;
    _b_voltage = _voltage;
    EEPROM.updateFloat(_address_b, _voltage);
    Serial.println("Voltage saved to EEPROM");
    delay(2000); // 2 second delay to prevent writing too frequently to EEPROM
}

float UNOphLib::read_ph()
{
    _voltage = analogRead(_voltage_pin) / 1024.0 * 5000;
    if (_ph_a > _ph_b)
    {
        float slope = (_ph_a - _ph_b) / ((_a_voltage - 1500.0) / 3.0 - (_b_voltage - 1500.0) / 3.0); // two points on the slope.
        float intercept = _ph_a - slope * (_a_voltage - 1500.0) / 3.0;
        _ph = slope * (_voltage - 1500.0) / 3.0 + intercept;
    }
    else if (_ph_a < _ph_b)
    {
        float slope = (_ph_b - _ph_a) / ((_b_voltage - 1500.0) / 3.0 - (_a_voltage - 1500.0) / 3.0); // two points on the slope.
        float intercept = _ph_b - slope * (_b_voltage - 1500.0) / 3.0;
        _ph = slope * (_voltage - 1500.0) / 3.0 + intercept;
    }

    return _ph;
}
