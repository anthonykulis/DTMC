/*
 * MotorControl.cpp
 *
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 *
 *  Current state: Tested, but needs setting motor speeds and braking written, as well as implementation of acceleration and safety checks
 */
#include "MotorControl.h"
#include "Arduino.h"

using namespace std;

MotorControl::MotorControl(){

	_mode = -1;
	_r = &DataRegister;

	_rf = _r->open(RIGHT_FORWARD, REG_READ_ONLY);
	_lf = _r->open(LEFT_FORWARD, REG_READ_ONLY);
	_rr = _r->open(RIGHT_REVERSE, REG_READ_ONLY);
	_lr = _r->open(LEFT_REVERSE, REG_READ_ONLY);
	_br = _r->open(FULL_BRAKE, REG_READ_ONLY);
	_a = _r->open(USE_ACCELERATION, REG_READ_ONLY);
	
	_prev_left = _prev_right = _prev_left_dir = _prev_right_dir = 0;

}

void MotorControl::update(){

	//todo: perform any safety check
	
	switch(_r->read(SET_CONTROL_MODE)){

		case I2C_MODE: break;
		case RC_MODE: _read_rc(); break;
		case SERIAL_MODE: _read_serial(); break;
		default: return; //error getting mode
	}

	/*
	 * Get L & R speeds from registers
	 */
	_ld = MOTORCONTROL_FORWARD;
	_ls = _r->read(_lf);


	if(!_ls){
		_ls = _r->read(_lr);
		_ld = !_ld;
	}

	_rd = MOTORCONTROL_FORWARD;
	_rs = _r->read(_rf);

	if(!_rs){
		_rs = _r->read(_rr);
		_rd = !_rd;
	}


	if(!_ls && !_rs){
		_brake();
		return;
	}

	_set_direction((int) _ld, (int) _rd);
	_set_speed((int) _ls, (int) _rs);

	return;
}

void MotorControl::_set_speed(int left, int right){

	if(left == _prev_left && right == _prev_right) return;

	Serial.print("setting speed: ");
	Serial.print(left);
	Serial.print(":");
	Serial.println(right);

	_prev_left = left;
	_prev_right = right;

}
void MotorControl::_set_direction(int left, int right){

	if(left == _prev_left_dir && right == _prev_right_dir) return;

	Serial.print("setting direction: ");
	Serial.print(left);
	Serial.print(":");
	Serial.println(right);

	_prev_left_dir = left;
	_prev_right_dir = right;

}
void MotorControl::_brake(){

	if(_prev_left == 0 && _prev_right == 0) return;

	Serial.println("braking");
	_prev_left = _prev_right = 0;
}

void MotorControl::_read_rc(){}
void MotorControl::_read_serial(){}


