/*
 * MotorControl.h
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */

#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#include "Register.h"
#include "Arduino.h"
#include "Battery.h"

#define MOTORCONTROL_FORWARD 0
#define MOTORCONTROL_REVERSE 1

class MotorControl {


public:

	MotorControl();
	void update();

	inline void setMode(int MODE){ _mode = MODE; }
	inline unsigned char getMode(){ return _mode; }

private:

	int _mode;

	Register *_r;
	Battery *_b;

	regd_t _rf, _lf, _lr, _rr, _br, _a;

	unsigned char _ls, _rs;
	int _ld, _rd;
	void _set_speed(int left, int right);
	void _set_direction(int left, int right);
	void _brake();
	void _read_rc();
	void _read_serial();
	
	int _prev_left, _prev_right, _prev_left_dir, _prev_right_dir;

};

#endif /* MOTORCONTROL_H_ */
