/*
 * DT_Battery.h
 *
 *  Created on: Apr 3, 2013
 *      Author: akulis
 */

#ifndef DT_BATTERY_H_
#define DT_BATTERY_H_

#include "Arduino.h"

#define CHARGER 13
enum CHARGER_STATE { NOT_CHARGING, CHARGING };

#define ANALOG_BATTERY_INPUT 0
#define ANALOG_RIGHT_MOTOR_CURRENT_INPUT 6
#define ANALOG_LEFT_MOTOR_CURRENT_INPUT 7

/*
 * Working on making this adaptive
 */
#define NOMINAL_BATTERY_VOLTAGE 487
#define LOW_BATTERY_VOLTAGE 410

//time out charging after 5 minutes if voltage does not change
#define CHARGER_TIME_OUT 300000

//overload current for motors
#define MAX_CURRENT_DRAW 800

//time in millis that the motor will be shutdown before it is re-enabled
#define OVERLOAD_TIME_OUT 100



typedef struct {

	int last_sample_time;
	int known_highest_voltage;
	int volts;
	int left_motor_current_draw;
	int right_motor_current_draw;
	int is_recharging;
	int recharing_error;
	int _initial_recharging_time;
	int _starting_voltage;
	int _overload_timeout_start;
	int _in_overload_cooldown;

} battery_state;

static battery_state battery;


void do_battery_diagnostics();
int is_battery_in_dangerous_state();
int is_battery_recharing();
int has_recharging_error();
void set_overload_timeout();

void _disable_charger();
void _start_charger();

#endif /* DT_BATTERY_H_ */
