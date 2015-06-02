/*
HMC5883L.h - Header file for the HMC5883L Triple Axis Magnetometer Arduino Library.
Copyright (C) 2011 Love Electronics (loveelectronics.co.uk) / 2012 bildr.org (Arduino 1.0 compatible)

Modified for RFDuino patform by Volodymyr Boichentsov, Twitter: @sakrist

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

 WARNING: THE HMC5883L IS NOT IDENTICAL TO THE HMC5883!
 Datasheet for HMC5883L:
 http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/HMC5883L_3-Axis_Digital_Compass_IC.pdf

*/

#ifndef HMC5883L_h
#define HMC5883L_h

#include <Arduino.h>
#include <Wire.h>


#define HMC5883L_Address  0x3C >> 1

#define ConfigurationRegisterA 0x00 // setup rate
#define ConfigurationRegisterB 0x01 // setup scale
#define ModeRegister 0x02
#define DataRegisterBegin 0x03

#define Measurement_Continuous 0x00
#define Measurement_SingleShot 0x01
#define Measurement_Idle 0x03

#define ErrorCode_1_Num 1
#define ErrorCode_1 "Entered scale option was not valid, valid gauss values are: 0 = 0.88, 1 = 1.3, 2 = 1.9, 3 = 2.5, 4 = 4.0, 5 = 4.7, 6 = 5.6, 7 = 8.1  Ga"
#define ErrorCode_2_Num 2
#define ErrorCode_2 "Entered rate option was not valid"

struct MagnetometerScaled
{
	float XAxis;
	float YAxis;
	float ZAxis;
};

struct MagnetometerRaw
{
	int XAxis;
	int YAxis;
	int ZAxis;
};

class HMC5883L
{
public:
    HMC5883L();
    
    MagnetometerRaw ReadRawAxis();
    MagnetometerScaled ReadScaledAxis();
    
    // Measurement_Continuous
    // Measurement_SingleShot   - Default
    // Measurement_Idle
    int SetMeasurementMode(byte mode);
    
    // opt  Field       Gain    Digital
    //      Range               Resolution
    // 0 - 0.88 Ga      1370    0.73
    // 1 - 1.3 Ga       1090    0.92    - Default
    // 2 - 1.9 Ga       820     1.22
    // 3 - 2.5 Ga       660     1.52
    // 4 - 4.0 Ga       440     2.27
    // 5 - 4.7 Ga       390     2.56
    // 6 - 5.6 Ga       330     3.03
    // 7 - 8.1 Ga       230     4.35
    int SetScale(int option);
    
    // 0 - 0.75 Hz
    // 1 - 1.5 Hz
    // 2 - 3 Hz
    // 3 - 7.5 Hz
    // 4 - 15 Hz  - Default
    // 5 - 30 Hz
    // 6 - 75 Hz
    int SetRate(int option);
    
    char* GetErrorText(int errorCode);
    
protected:
    void Write(byte address, byte byte);
    byte* Read(byte address, byte length);
    
private:
    float m_Scale;
    uint8_t i2c_address;
};
#endif