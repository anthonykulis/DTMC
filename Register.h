/*
 * Register.h
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */

#ifndef Register_H_
#define Register_H_


#include "Arduino.h"

//some _reg_vals values
#define NULL_VALUE				0x00
#define DEFAULT_I2C_ADDRESS			0x25
#define I2C_MODE				0x00
#define SERIAL_MODE				0x01
#define RC_MODE					0x02
#define ACCELERATION_ON				0x01
#define ACCELERATION_OFF			0x00


//control values for read function
#define LEFT_FORWARD 				0x00
#define LEFT_REVERSE 				0x01
#define RIGHT_FORWARD 				0x02
#define RIGHT_REVERSE				0x03
#define FULL_BRAKE				0x04

#define SET_I2C_ADDRESS				0x05
#define USE_ACCELERATION			0x06
#define SET_CONTROL_MODE			0x07

#define READ_BATTERY_LEVEL_HIGH			0x08
#define READ_BATTERY_LEVEL_LOW			0x09
#define READ_LEFT_MOTOR_CURRENT			0x0A
#define READ_RIGHT_MOTOR_CURRENT		0x0B
#define RECHARGING				0x0C
#define RECHARGING_ERROR			0X0D

#define SET_AUTO_RECHARGE			0x0E

#define _REG_SIZE 				11

typedef int regd_t;
enum {REG_READ_ONLY, REG_READ_WRITE, REG_MASTER_MODE};

/*
 * Notes on usage:
 *
 * When opening a register, you have 3 modes of operation.
 * 1) READ_ONLY - the register cannot be overwritten.
 * 2) READ_WRITE - the register can be overwritten, but only those allowing writes
 * 3) MASTER_MODE - allows overwriting of all registers. Do not use unless you have a reason too.
 * 					Primarily for debugging and library development. May become deprecated in future.
 */
class Register {

public:

	Register(unsigned char ADDRESS = 0x00, int MODE = 0);

	int open(unsigned char reg, int open_flag);
	unsigned char read(int reg_descriptor);
	int write(int reg_descriptor, unsigned char value);
	int close(int reg_descriptor);
	bool is_control_register(unsigned char REGISTER);
    	bool is_read_register(unsigned char REGISTER);


private:

	unsigned char _reg_vals[_REG_SIZE];

	//high value regs are for master mode hook
	int _allocated_regs[_REG_SIZE * 2];
	void _populate();
	unsigned char _is_allowed_reg(unsigned char REGISTER);
	int _is_rw_reg(unsigned char REGISTER);

};

extern Register DataRegister;
#endif /* REGISTER_H_ */
