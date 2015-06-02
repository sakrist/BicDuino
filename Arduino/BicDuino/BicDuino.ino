
#include <RFduinoBLE.h>

// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L_RFD.h>

// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

int LEDpin = 4; 

float strengthInGauss;

// Out setup routine, here we will configure the microcontroller and compass.
void setup()
{
  
  RFduinoBLE.advertisementData = "BicDuino";
  RFduinoBLE.txPowerLevel = -20;
  RFduinoBLE.begin();
  
  // Initialize the serial port.
//  Serial.begin(9600);
  Wire.begin(); // Start the I2C interface.

  Serial.println("Constructing new HMC5883L");
  compass = HMC5883L(); // Construct a new HMC5883 compass.
    
    
  error = compass.SetScale(7); // Set the scale of the compass.
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.GetErrorText(error));

  error = compass.SetRate(6);
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.GetErrorText(error));

  
  Serial.println("Setting measurement mode to continous.");
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.GetErrorText(error));
    
  pinMode(LEDpin, OUTPUT);
}


void readCompassStreaght() {
    // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  
  strengthInGauss = sqrt(scaled.XAxis * scaled.XAxis +
               scaled.YAxis * scaled.YAxis +
               scaled.ZAxis * scaled.ZAxis)/230;               
}

void sleepMode() {
  compass.SetMeasurementMode(Measurement_Idle);
  RFduino_ULPDelay(INFINITE);
}

// Our main program loop.
void loop()
{
  
  readCompassStreaght();
  Serial.println(strengthInGauss);
  
  if (strengthInGauss > 5) {
    digitalWrite(LEDpin, HIGH);
  } else {
    digitalWrite(LEDpin, LOW);
  }
  
  // Normally we would delay the application by 66ms to allow the loop
  // to run at 15Hz (default bandwidth for the HMC5883L).
  // However since we have a long serial out (104ms at 9600) we will let
  // it run at its natural speed.
   delay(200);
   
   RFduinoBLE.sendFloat(strengthInGauss);
}


void RFduinoBLE_onAdvertisement(bool start)
{

}

void RFduinoBLE_onConnect()
{

}

void RFduinoBLE_onDisconnect()
{

}


void RFduinoBLE_onReceive(char *data, int len)
{

}

