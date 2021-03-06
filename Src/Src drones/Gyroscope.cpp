#include <Arduino.h>
#include <SPI.h> // Included for SFE_LSM9DS0 library
#include <Wire.h>
#include <SFE_LSM9DS0.h>

// SDO_XM and SDO_G are both grounded, so our addresses are:
#define LSM9DS0_XM  0x1D // Would be 0x1E if SDO_XM is LOW
#define LSM9DS0_G   0x6B // Would be 0x6A if SDO_G is LOW
// Create an instance of the LSM9DS0 library called `gyroData` the
// parameters for this constructor are:
// [SPI or I2C Mode declaration],[gyro I2C address],[xm I2C add.]
LSM9DS0 gyroData(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

void printOrientation(float x, float y, float z);
void setupGyro();
void loopGyro();

void setupGyro()
{
  gyroData.begin();
}

void loopGyro()
{
  gyroData.readAccel();
  printOrientation(gyroData.calcAccel(gyroData.ax), gyroData.calcAccel(gyroData.ay), 
                   gyroData.calcAccel(gyroData.az));
  Serial.println();
}

float pitch, roll;

void printOrientation(float x, float y, float z)
{
  pitch = atan2(x, sqrt(y * y) + (z * z));
  roll = atan2(y, sqrt(x * x) + (z * z));
  pitch *= 180.0 / PI;
  roll *= 180.0 / PI;
  
  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
}

void setup()
{
  Serial.begin(115200);
  setupGyro();
}

void loop()
{
  loopGyro();
}