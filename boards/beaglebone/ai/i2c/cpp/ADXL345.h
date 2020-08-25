#ifndef ADXL345_H_
#define ADXL345_H_
#include"I2CDevice.h"

/// The ADXL345 has 0x40 registers (0x01 to 0x1C are reserved and should not be accessed)
#define BUFFER_SIZE 0x40

namespace exploringBB {

/**
 * @class ADXL345
 * @brief Specific class for the ADXL345 Accelerometer that is a child of the I2CDevice class
 * Protected inheritance means that the public I2CDevice methods are not publicly accessible
 * by an object of the ADXL345 class.
 */
class ADXL345:protected I2CDevice{

public:

	/// An enumeration to define the gravity range of the sensor
	enum RANGE {
		PLUSMINUS_2_G 		= 0,//!< plus/minus 2g
		PLUSMINUS_4_G 		= 1,//!< plus/minus 4g
		PLUSMINUS_8_G 		= 2,//!< plus/minus 8g
		PLUSMINUS_16_G 		= 3 //!< plus/minus 16g
	};
	/// The resolution of the sensor. High is only available in +/- 16g range.
	enum RESOLUTION {
		NORMAL = 0,//!< NORMAL 10-bit resolution
		HIGH = 1   //!< HIGH 13-bit resolution
	};

private:
	unsigned int I2CBus, I2CAddress;
	unsigned char *registers;
	ADXL345::RANGE range;
	ADXL345::RESOLUTION resolution;
	short accelerationX, accelerationY, accelerationZ; // raw 2's complement values
	float pitch, roll;                                 // in degrees
	short combineRegisters(unsigned char msb, unsigned char lsb);
	void calculatePitchAndRoll();
	virtual int updateRegisters();

public:
	ADXL345(unsigned int I2CBus, unsigned int I2CAddress=0x53);
	virtual int readSensorState();

	virtual void setRange(ADXL345::RANGE range);
	virtual ADXL345::RANGE getRange() { return this->range; }
	virtual void setResolution(ADXL345::RESOLUTION resolution);
	virtual ADXL345::RESOLUTION getResolution() { return this->resolution; }

	virtual short getAccelerationX() { return accelerationX; }
	virtual short getAccelerationY() { return accelerationY; }
	virtual short getAccelerationZ() { return accelerationZ; }
	virtual float getPitch() { return pitch; }
	virtual float getRoll() { return roll; }

	// Debugging method to display and update the pitch/roll on the one line
	virtual void displayPitchAndRoll(int iterations = 600);
	virtual ~ADXL345();
};

} /* namespace exploringBB */

#endif /* ADXL345_H_ */
