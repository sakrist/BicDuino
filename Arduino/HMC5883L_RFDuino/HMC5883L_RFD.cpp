/*
HMC5883L.cpp - Class file for the HMC5883L Triple Axis Magnetometer Arduino Library.
Copyright (C) 2011 Love Electronics (loveelectronics.co.uk)/ 2012 bildr.org (Arduino 1.0 compatible)
 
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

#include <Arduino.h> 
#include <Wire.h>
#include "HMC5883L_RFD.h"

HMC5883L::HMC5883L()
{
    m_Scale = 1;
    i2c_address = HMC5883L_Address;
}

MagnetometerRaw HMC5883L::ReadRawAxis()
{
  byte* buffer = Read(DataRegisterBegin, 6);
  MagnetometerRaw raw = MagnetometerRaw();
  raw.XAxis = (int16_t)(buffer[0] << 8) | buffer[1];
  raw.ZAxis = (int16_t)(buffer[2] << 8) | buffer[3];
  raw.YAxis = (int16_t)(buffer[4] << 8) | buffer[5];
  return raw;
}

MagnetometerScaled HMC5883L::ReadScaledAxis()
{
  MagnetometerRaw raw = ReadRawAxis();
  MagnetometerScaled scaled = MagnetometerScaled();
  scaled.XAxis = raw.XAxis * m_Scale;
  scaled.ZAxis = raw.ZAxis * m_Scale;
  scaled.YAxis = raw.YAxis * m_Scale;
  return scaled;
}


int HMC5883L::SetRate(int option)
{
    byte regValue = 0x00;
    
    switch (option) {
        case 0:
            regValue = 0x00;
            break;
        case 1:
            regValue = 0x01;
            break;
        case 2: //
            regValue = 0x02;
            break;
        case 3: //
            regValue = 0x03;
            break;
        case 4: // 15Hz - Default
            regValue = 0x04;
            break;
        case 5: // 4.7
            regValue = 0x05;
            break;
        case 6: // 5.6
            regValue = 0x06;
            break;
        default:
            return ErrorCode_2_Num;
    }
    
    // Setting is in the top after 2 bits of the register.
    regValue = regValue << 2;
    Write(ConfigurationRegisterA, regValue);
    return 0;
}


int HMC5883L::SetScale(int option)
{
	byte regValue = 0x00;
    
    switch (option) {
        case 0: // 0.88
            regValue = 0x00;
            m_Scale = 0.73;
            break;
            
        case 1: // 1.3
            regValue = 0x01;
            m_Scale = 0.92;
            break;
        case 2: // 1.9
            regValue = 0x02;
            m_Scale = 1.22;
            break;
        case 3: // 2.5
            regValue = 0x03;
            m_Scale = 1.52;
            break;
        case 4: // 4.0
            regValue = 0x04;
            m_Scale = 2.27;
            break;
        case 5: // 4.7
            regValue = 0x05;
            m_Scale = 2.56;
            break;
        case 6: // 5.6
            regValue = 0x06;
            m_Scale = 3.03;
            break;
        case 7: // 8.1
            regValue = 0x07;
            m_Scale = 4.35;
            break;
        default:
            return ErrorCode_1_Num;
            
    }
	
	// Setting is in the top 3 bits of the register.
	regValue = regValue << 5;
	Write(ConfigurationRegisterB, regValue);
    return 0;
}

int HMC5883L::SetMeasurementMode(byte mode)
{
	Write(ModeRegister, mode);
}

void HMC5883L::Write(byte address, byte data)
{
  Wire.beginTransmission(i2c_address);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t* HMC5883L::Read(byte address, byte length)
{
  Wire.beginTransmission(i2c_address);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.beginTransmission(i2c_address);
  Wire.requestFrom(i2c_address, length);

  byte buffer[length];
  if(Wire.available() == length)
  {
	  for(byte i = 0; i < length; i++)
	  {
		  buffer[i] = Wire.read();
	  }
  }
  Wire.endTransmission();

  return buffer;
}

char* HMC5883L::GetErrorText(int errorCode)
{
	if(ErrorCode_1_Num == errorCode)
		return ErrorCode_1;
    if(ErrorCode_2_Num == errorCode)
        return ErrorCode_2;
	
	return "Error not defined.";
}