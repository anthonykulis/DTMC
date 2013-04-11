/*
 * I2C.h
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */

#ifndef I2C_H_
#define I2C_H_
#include "Arduino.h"

class I2C {

public:
	I2C(Register r);

private:

	Register *_r;
	void _resetI2C();
	regd_t _i2c;
	unsigned char _i2c_add;
	void _receiveHandler(int numBytes);
	void _requestHandler();
	bool _is_wire_active;

};

#endif /* I2C_H_ */
