/*
 * Register.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 *
 *  Current state: Pretty fully tested. Added two public bool functions that still need to be tested.
 */
#include "Arduino.h"
#include "Register.h"



/*
 * Constructor
 *
 * @param if ADDRESS is passed, you will need to
 * call read/write/close with the address instead of reg_descriptor. Note,
 * the ADDRESS is the unsigned char version of the regd_t value anyways,
 * so either way of calling is acceptable
 */
Register::Register(unsigned char ADDRESS, int MODE){

	_populate();

	if(ADDRESS) open(ADDRESS, MODE);
}


/*
 * Allows a user to open a register descriptor for one of the
 * enumerated types: READ_ONLY, READ_WRITE, MASTER_MODE
 *
 * @param reg the register address to access
 * @param open_flag the enumerated type of the registers permissions
 * @return the register descriptor to be used in read/write/close actions
 */


regd_t Register::open(unsigned char reg, int open_flag){

	/*
	 * unknown open flag -
	 * allowed to be 0 to 2
	 * 0 + 1 => 1 >> 2 = 0;
	 * 1 + 1 => 2 >> 2 = 0;
	 * 2 + 1 => 3 >> 2 = 0;
	 * 3 + 1 => 4 >> 2 = 1;
	 * ...
	 * ...
	 * ...
	 */
	int of = open_flag;
	if((++of) >> 2) return -1;
	
	//dont care in this mode. assumes developer knows what they are doing
	if(open_flag == REG_MASTER_MODE){
		_allocated_regs[reg + _REG_SIZE] = open_flag;
		return (int) reg + _REG_SIZE;
	}

	//cant open same register twice or more at a time
	if(_allocated_regs[reg] != -1) return -1;
	
	//cout << "is allowed(" << (int) reg << ") " << (int)_is_allowed_reg(reg) << endl;
	//make sure it is a register we will look at in the control loop
	if(!_is_allowed_reg(reg)){
		//cout << "Not allowed " << (int)reg << endl;
		return -1;
	}
	
	//make sure if rw then its a rw register
	if((open_flag == REG_READ_WRITE) && !_is_rw_reg(reg)) _allocated_regs[(int) reg] = -1;

	_allocated_regs[reg] = open_flag;

	return (int) reg;

}

/*
 * Allows a user to read the value from a register
 *
 * @param reg_descriptor the register the user is wishing to access
 * @return the value of that register
 */
unsigned char Register::read(regd_t reg_descriptor){


	int rd = reg_descriptor % _REG_SIZE;

	//not opened yet
	if(_allocated_regs[rd] == -1 && _allocated_regs[reg_descriptor] == -1) return 0x00;

	return _reg_vals[rd];

}

/*
 * Allows a user to write to a register with write permissions. If in MASTER_MODE,
 * the user can write to any register
 */
int Register::write(regd_t reg_descriptor, unsigned char value){


	int rd = reg_descriptor;
	
	//not opened
	if(_allocated_regs[rd] == -1) return 0;
	
	//set up size check for byte value passed
	unsigned char sc = value >> 16;

	//restrict read only registers and 2 byte size limits
	if(_allocated_regs[rd] == REG_READ_ONLY || sc) return 0;
	

	_reg_vals[rd % _REG_SIZE] = value;

	return 1;

}

/*
 * Allows the user to close a register (possibly reopening under different permissions)
 *
 * @param the regd_t of the register to close
 * @return the regd_t of the register just closed
 */
regd_t Register::close(regd_t reg_descriptor){

	int rd = reg_descriptor;

	//yikes, not open!
	if(_allocated_regs[rd] == -1) return -1;

	//close it
	_allocated_regs[rd] = -1;

	//be nice
	return rd;

}

bool Register::is_control_register(unsigned char REGISTER){
	return _is_allowed_reg(REGISTER) > 0;
}

bool Register::is_read_register(unsigned char REGISTER){
	return !_is_rw_reg(REGISTER) && _is_allowed_reg(REGISTER);
}

//be sure to define default values as you populate control values
void Register::_populate(){

	for(int i = 0; i < _REG_SIZE; i++){

		switch(i){
			case (int)SET_I2C_ADDRESS: 			_reg_vals[i] = DEFAULT_I2C_ADDRESS; break;
			case (int)USE_ACCELERATION:			_reg_vals[i] = ACCELERATION_ON; break;
			case (int)SET_CONTROL_MODE:			_reg_vals[i] = I2C_MODE; break;
			default: 					_reg_vals[i] = NULL_VALUE;
		}

		_allocated_regs[i] = -1;
	}

}

//be sure to populate as you populate control values
unsigned char Register::_is_allowed_reg(unsigned char REGISTER){

	return 	(LEFT_FORWARD == REGISTER) ||
			(LEFT_REVERSE == REGISTER) ||
			(RIGHT_FORWARD == REGISTER) ||
			(RIGHT_REVERSE == REGISTER) ||
			(FULL_BRAKE == REGISTER) ||
			(SET_I2C_ADDRESS == REGISTER) ||
			(USE_ACCELERATION == REGISTER) ||
			(SET_CONTROL_MODE == REGISTER) ||
			(READ_BATTERY_LEVEL == REGISTER) ||
			(READ_LEFT_MOTOR_CURRENT == REGISTER) ||
			(READ_RIGHT_MOTOR_CURRENT == REGISTER);
}


//be sure to populate as you populate r/w registers
int Register::_is_rw_reg(unsigned char REGISTER){

	return 	LEFT_FORWARD == REGISTER ||
			LEFT_REVERSE == REGISTER ||
			RIGHT_FORWARD == REGISTER ||
			RIGHT_REVERSE == REGISTER |
			FULL_BRAKE == REGISTER ||
			SET_I2C_ADDRESS == REGISTER ||
			USE_ACCELERATION == REGISTER ||
			SET_CONTROL_MODE == REGISTER;
}


Register DataRegister = Register();
