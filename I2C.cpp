/*
 * I2C.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 *
 *  Current state: Tested. Ready.
 */

#include "I2C.h"
#include "Register.h"
#include "Arduino.h"
#include "Wire.h"


void receiveHandler(int numBytes){

	//loop thru the request statement
	for(int i = 0; i < numBytes; i++){

		regd_t reg;
		unsigned char c = Wire.read();
		unsigned char val;


		//if control register, eg set speed, need next byte and increment i
		if(Wire.available() >= 1 && DataRegister.is_control_register(c)){
			val = Wire.read();
			i++;
			reg = DataRegister.open(c, REG_MASTER_MODE);
			DataRegister.write(reg, val);

		}

		//if read register, send back value
		else if(DataRegister.is_read_register(c)){
			reg = DataRegister.open(c, REG_MASTER_MODE);
			Wire.write(DataRegister.read(reg));
			
		}

		DataRegister.close(reg);
	}
}

void requestHandler(){
	//intentionally left blank. might implement a default behavior later
}

I2C::I2C(){
	
	_resetI2C();

}

void I2C::_resetI2C(){

	_i2c = DataRegister.open(SET_I2C_ADDRESS, REG_MASTER_MODE);
	_i2c_add = DataRegister.read(_i2c);
	Wire.begin(_i2c_add);
	Wire.onReceive(receiveHandler);
	Wire.onRequest(requestHandler);
	_is_wire_active = true;

}

I2C DT_Wire = I2C();

