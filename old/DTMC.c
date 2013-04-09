/*
 * DTMC.c
 *
 *  Created on: Apr 3, 2013
 *      Author: akulis
 */


#include "DT_Servos.h"
#include "DT_Battery.h"
#include "DT_MotorControl.h"

/*
 * If you wish to use SoftSerial to debug,
 * uncomment and set your ports for rx and tx
 */
//#define DEBUG_VIA_SOFT_SERIAL
#ifdef DEBUG_VIA_SOFT_SERIAL
#define SS_RX 10
#define SS_TX 11
#include <SoftwareSerial.h>
SoftwareSerial debugger(SS_RX, SS_TX)
#endif

/*
 * Set to 0 each of the debugging messages
 * you don't need/want. Setting DEBUGGING_ENABLED to 0
 * turns off all messaging
 */
#define DEBUGGING_ENABLED 1
#define DEBUGGING_SERIAL_INPUT_CONTROL 1
#define DEBUGGING_I2C_INPUT_CONTROL 1
#define DEBUGGING_RC_INPUT_CONTROL 1
#define DEBUGGING_BATTERY_DIAGNOSTICS 1
#define DEBUGGING_CHARGING_CONTROL 1
#define DEBUGGING_MOTOR_CONTROL 1
#define DEBUGGING_SERVO_CONTROL 1

//enum { RC, SERIAL, I2C } MODE;
int SERIAL = 0;
/*
 * Set your desired mode to above enumeration
 */
static int control_mode = SERIAL;

/*
 * Set your desired loop delay
 */
static int loop_delay = 0;


void setup(){

	/*
	 * Change to set your desired pinouts to PWM
	 */
	int attach_these[NUM_SERVOS] = {1, 0, 0, 0, 0, 0, 1};
	attach_servos(attach_these);

	/*
	 * Initially disable charging mode. Will be caught
	 * in runtime loop
	 */
	_disable_charger();

	if(control_mode == SERIAL) init_serial();

}

void loop(){

	/*
	 * Check battery status
	 */
	do_battery_diagnostics();

	/*
	 * Check for danger status (draw or re-charge issues)
	 */
	if(has_recharging_error() || is_battery_in_dangerous_state()){

		motors_shutdown();

		if(is_battery_in_dangerous_state()) set_overload_timeout();
		return;
	}

	/*
	 * Does the battery need to be recharged?
	 */
	if(is_battery_recharing()) return;

	/*
	 * Now that we pass all those checks, send off control
	 */
	switch(control_mode){

		case RC: handle_rc(); break;
		case SERIAL: handle_serial(); break;
		case I2C: handle_i2c(); break;
		DEFAULT: motors_shutdown();

	}

	//if(DEBUGGING_ENABLED) debugger();

	//delay(loop_delay);

}

