/*
 * runner_test.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */


#include <iostream>
#include "MotorControl.h"
#include "Register.h"

using namespace std;


int main(){

	Register r;
	regd_t lf, rf, lr, rr, fb;

	lf = r.open(LEFT_FORWARD, REG_MASTER_MODE);
	rf = r.open(RIGHT_FORWARD, REG_MASTER_MODE);
	lr = r.open(LEFT_REVERSE, REG_MASTER_MODE);
	rr = r.open(RIGHT_REVERSE, REG_MASTER_MODE);
	fb = r.open(FULL_BRAKE, REG_MASTER_MODE);

	MotorControl mc(&r);

	mc.update();

	//set speed full forward
	r.write(lf, 0xFF);
	r.write(rf, 0Xff);
	mc.update();

	r.write(lf, 0x00);
	r.write(rf, 0x00);
	r.write(lr, 0xFF);
	r.write(rr, 0xFF);
	mc.update();

	r.write(lr, 0x00);
	r.write(rr, 0x00);
	mc.update();

}
