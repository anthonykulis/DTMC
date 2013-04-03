/*
 * DT_MotorControl.h
 *
 *  Created on: Apr 3, 2013
 *      Author: akulis
 */

#ifndef DT_MOTORCONTROL_H_
#define DT_MOTORCONTROL_H_

#include "DT_Serial.h"
#include "DT_I2C.h"
#include "DT_RC.h"


#define LEFT_MOTOR_INPUT_A 3
#define LEFT_MOTOR_INPUT_B 11
#define RIGHT_MOTOR_INPUT_A 5
#define RIGHT_MOTOR_INPUT_B 6

//use for tuning differential motors. Ignore if your DT has no issue with drifting to one side(mine does!).
#define RIGHT_MOTOR_MAX_SPEED 255
#define LEFT_MOTOR_MAX_SPEED 255

//set to 0 if you wish to jump to speed instead of accelerate smoothly
#define USE_ACCELERATION 1

//number of milliseconds between acceleration ticks
#define ACCELERATION_RATE 10

static int current_left_speed = 0;
static int current_right_speed = 0;
static double differential_multiplier = RIGHT_MOTOR_MAX_SPEED / LEFT_MOTOR_MAX_SPEED;

void motors_shutdown();
void handle_rc();
void handle_serial();
void handle_i2c();
void accelerate(int target);

#endif /* DT_MOTORCONTROL_H_ */
