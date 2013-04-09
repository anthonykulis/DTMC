/*
 * DT_MotorControl.c
 *
 *  Created on: Apr 3, 2013
 *      Author: akulis
 */

#include "DT_MotorControl.h"

void motors_shutdown(){

	analogWrite(LEFT_MOTOR_INPUT_A, 0);
	analogWrite(LEFT_MOTOR_INPUT_B, 0);
	analogWrite(RIGHT_MOTOR_INPUT_A, 0);
	analogWrite(RIGHT_MOTOR_INPUT_B, 0);

}

void handle_rc(){}

void handle_serial(){}

void handle_i2c(){}

/*
 * Follows sigmoid function of time/sqrt(1 + time^2)
 */
void accelerate(int target){


	int old_t = millis();
	int t = old_t;

	while(current_left_speed < LEFT_MOTOR_MAX_SPEED || current_right_speed);
}
