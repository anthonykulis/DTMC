/*
 * RegTest.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */



#include <iostream>

#include "Register.h"

using namespace std;

int main(){

	Register r;
	regd_t i2c = r.open(SET_I2C_ADDRESS, REG_READ_WRITE);
	regd_t bad = r.open(LEFT_FORWARD, REG_READ_ONLY);
	regd_t bad_open = r.open(0x2a, REG_READ_WRITE);

	cout << "RD of bad open: " << bad_open << " and " << i2c << endl;

	cout << "Read: " << (int) r.read(i2c) << endl;

	r.write(SET_I2C_ADDRESS, 0x12);

	cout << "Read: " << (int) r.read(SET_I2C_ADDRESS) << endl;


	r.close(i2c);

	cout << "Read i2c after close: " << (int) r.read(i2c) << endl;

	cout << "Write to ro reg: " << (int) r.write(bad, 0x01) << endl;
	cout << "Read from that ro reg: " << (int) r.read(bad) << endl;

	Register a(SET_I2C_ADDRESS, REG_MASTER_MODE);
	cout << "read a: " << (int) a.read(SET_I2C_ADDRESS) << endl;
}
