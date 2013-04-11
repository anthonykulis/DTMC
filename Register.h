/*
 * Register.h
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */

#ifndef Register_H_
#define Register_H_


//#include "Arduino.h"

//some _reg_vals values
#define NULL_VALUE					0x00
#define DEFAULT_I2C_ADDRESS			0x25
#define I2C_MODE					0x00
#define SERIAL_MODE					0x01
#define RC_MODE						0x02
#define ACCELERATION_ON				0x01
#define ACCELERATION_OFF			0x00


//control values for read function
#define LEFT_FORWARD 				0x04
#define LEFT_REVERSE 				0x05
#define RIGHT_FORWARD 				0x06
#define RIGHT_REVERSE				0x07
#define FULL_BRAKE					0x08

#define SET_I2C_ADDRESS				0x10
#define USE_ACCELERATION			0x11
#define SET_CONTROL_MODE			0x12

#define READ_BATTERY_LEVEL			0x20
#define READ_LEFT_MOTOR_CURRENT		0x22
#define READ_RIGHT_MOTOR_CURRENT	0x23

#define _REG_SIZE 256

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

	regd_t open(unsigned char reg, int open_flag);
	unsigned char read(regd_t reg_descriptor);
	int write(int reg_descriptor, unsigned char value);
	regd_t close(regd_t reg_descriptor);
    bool is_control_reg(unsigned char REGISTER);
    bool is_read_reg(unsigned char REGISTER);

private:

	unsigned char _reg_vals[_REG_SIZE];

	//high value regs are for master mode hook
	regd_t _allocated_regs[_REG_SIZE * 2];

	void _populate();
	unsigned char _is_allowed_reg(unsigned char REGISTER);
	int _is_rw_reg(unsigned char REGISTER);
};

#endif /* REGISTER_H_ */
