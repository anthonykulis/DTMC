/*
 * MotorControl.h
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */

#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#include "Register.h"


#define MOTORCONTROL_FORWARD 0
#define MOTORCONTROL_REVERSE 1

class MotorControl {


public:

	MotorControl(Register *r);
	void update();

	inline void setMode(int MODE){ _mode = MODE; }
	inline unsigned char getMode(){ return _mode; }

private:

	int _mode;

	Register *_r;
	regd_t _rf, _lf, _lr, _rr, _br, _a;

	unsigned char _ls, _rs;
	int _ld, _rd;
	void _set_speed(int left, int right);
	void _set_direction(int left, int right);
	void _brake();
	void _read_rc();
	void _read_serial();

};

#endif /* MOTORCONTROL_H_ */
