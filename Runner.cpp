/*
 * Runner.cpp
 *
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */
#include "Runner.h"
#include <iostream>

using namespace std;

Runner::Runner(Register *r){

	_mode = -1;
	_r = r;

	_rf = _r->open(RIGHT_FORWARD, REG_READ_ONLY);
	_lf = _r->open(LEFT_FORWARD, REG_READ_ONLY);
	_rr = _r->open(RIGHT_REVERSE, REG_READ_ONLY);
	_lr = _r->open(LEFT_REVERSE, REG_READ_ONLY);
	_br = _r->open(FULL_BRAKE, REG_READ_ONLY);
	_a = _r->open(USE_ACCELERATION, REG_READ_ONLY);


}

void Runner::update(){

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
	_ld = RUNNER_FORWARD;
	_ls = _r->read(_lf);


	if(_ls == 0x00){
		_ls = _r->read(_lr);
		_ld = !_ld;
	}

	_rd = RUNNER_FORWARD;
	_rs = _r->read(_rf);

	if(_rs == 0x00){
		_rs = _r->read(_rr);
		_rd = !_rd;
	}


	if(_ls == 0x00 && _rs == 0x00){
		_brake();
		return;
	}

	_set_direction((int) _ld, (int) _rd);
	_set_speed((int) _ls, (int) _rs);

	return;
}

void Runner::_set_speed(int left, int right){
	cout << "Left Speed: " << left << " Right Speed: " << right << endl;
}
void Runner::_set_direction(int left, int right){
	cout << "Left Direction: " << left << " Right Direction: " << right << endl;
}
void Runner::_brake(){
	cout << "Braking" << endl;
}

void Runner::_read_rc(){}
void Runner::_read_serial(){}


