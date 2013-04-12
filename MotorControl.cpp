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
#include "Battery.h"

using namespace std;

MotorControl::MotorControl(){

	_mode = -1;
	_r = &DataRegister;
	_b = &SystemBattery;

	//i2c only needs read only, but serial and rc will need writes
	//if only using i2c, you may wish to change this to read only
	//if you wish to use these registers in you loop() event, do not
	//call this class if possible or modifiy it so that these are 
	//opened only when needed and closed otherwise
	_rf = _r->open(RIGHT_FORWARD, REG_READ_WRITE);
	_lf = _r->open(LEFT_FORWARD, REG_READ_WRITE);
	_rr = _r->open(RIGHT_REVERSE, REG_READ_WRITE);
	_lr = _r->open(LEFT_REVERSE, REG_READ_WRITE);
	_br = _r->open(FULL_BRAKE, REG_READ_WRITE);
	_a = _r->open(USE_ACCELERATION, REG_READ_WRITE);
	
	_prev_left = _prev_right = _prev_left_dir = _prev_right_dir = 0;

}

/**
 * This function provides the basics of the loop() event. 
 * It is intended to handle all the major features of motor control
 * while allowing the user to use their loop() event to handle 
 * other uC features. If wanting to control the motor themselves,
 * a user should not call this function
 */ 
void MotorControl::update(){

	_b->do_battery_diagnostics();
	
	if(_b->is_battery_recharging()) return _brake();

	//todo: perform any safety check
	
	//how to handle control messages - note, even if not using i2c, user still can access read registers from i2c
	switch(_r->read(SET_CONTROL_MODE)){

		//do nothing, handled on interupts
		case I2C_MODE: break;

		//to implement
		case RC_MODE: _read_rc(); break;

		//to implement
		case SERIAL_MODE: _read_serial(); break;

		//error getting mode
		default: return; 
	}

	//first check for full break
	int b = _r->read(_br);	
	if(b){
		Serial.print("Read FULL_BRAKE ");
		Serial.println(b);		
		return _brake();
	}
	
	//get left forward speed
	_ld = MOTORCONTROL_FORWARD;
	_ls = _r->read(_lf);

	//no left forward speed? check left reverse then
	if(!_ls){
		_ls = _r->read(_lr);
		_ld = !_ld;
	}
	
	//get right forward speed
	_rd = MOTORCONTROL_FORWARD;
	_rs = _r->read(_rf);

	//no right forward? get right reverse then
	if(!_rs){
		_rs = _r->read(_rr);
		_rd = !_rd;
	}
		
	//set the direction and speed of each motor
	_set_direction((int) _ld, (int) _rd);
	_set_speed((int) _ls, (int) _rs);
	
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


