/*
 * I2C.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 *
 *  Current state: Not tested.
 */

#include "Register.h"

I2C::I2C(Register *r){

	_is_wire_active = false;
	_r = r;
	_i2c = _r->open(SET_I2C_ADDRESS, REG_MASTER_MODE);


}

void I2C::resetI2C(){

	_i2c_add = _r.read(_i2c);
	Wire.begin(_i2c_add);
	Wire.onReceive(_receiveHandler);
	Wire.onRequest(_requestHandler);
	_is_wire_active = true;

}

void _receiveHandler(int numBytes){

	//loop thru the request statement
	for(int i = 0; i < numBytes; i++){

		regd_t reg;
		unsigned char c = Wire.read();
		unsigned char val;

		//if control register, eg set speed, need next byte and increment i
		if(Wire.available() > 1 && _r->is_control_register(c)){
			val = Wire.read();
			i++;
			reg = _r->open(c, REG_MASTER_MODE);
			val = Wire.read();
			_r->write(reg, val);
			_r->close();
		}

		//if read register, send back value
		else if(_r->is_read_register(c)){
			reg = _r->open(c, REG_MASTER_MODE);
			Wire.write(_r->read(reg));
			_r->close();
		}

	}
}

void _requestHandler(){
	//intentionally left blank. might implement a default behavior later
}
