/*
 * I2C.h
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */

#ifndef I2C_H_
#define I2C_H_
#include "Arduino.h"
#include "Register.h"
#include "Wire.h"


class I2C {

public:
	I2C();
	friend void receiveHandler(int numBytes);
	friend void requestHandler();


private:

	void _resetI2C();
	regd_t _i2c;	
	bool _is_wire_active;
	unsigned char _i2c_add;

};

extern I2C DT_Wire;
#endif /* I2C_H_ */
