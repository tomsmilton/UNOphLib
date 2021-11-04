#ifndef UNOphLib_h
#define UNOphLib_h

#include <Arduino.h>


class UNOphLib
{
public:

    void    calibrate_a();
    void    calibrate_b(); 
    float    read_ph();
    void    begin(int address_a, float ph_a, int address_b, float ph_b, int voltage_pin);   //adress a and b are where the calib data is stored in eeprom.

private:
    int _address_a;
    int _address_b;
    float _ph_a;
    float _ph_b;
    float _voltage;
    int _voltage_pin;
    float _ph;
    float _a_voltage;
    float _b_voltage;


};






#endif