/*
 * DT_Battery.c
 *
 *  Created on: Apr 3, 2013
 *      Author: akulis
 */

#include "DT_Battery.h"


/*
 * Simply populates the battery_state struct
 */
void do_battery_diagnostics(){

	//get basic stats
	battery.last_sample_time = millis();
	battery.volts = analogRead(ANALOG_BATTERY_INPUT);

	//to be used later in for automatically setting nominal voltage
	if(battery.volts > battery.known_highest_voltage)
		battery.known_highest_voltage = battery.volts;

	//get the status of the motors draw
	battery.left_motor_current_draw = analogRead(ANALOG_LEFT_MOTOR_CURRENT_INPUT);
	battery.right_motor_current_draw = analogRead(ANALOG_RIGHT_MOTOR_CURRENT_INPUT);

	//set error if recharing issue arises
	if(battery.is_recharging && battery._initial_recharging_time + CHARGER_TIME_OUT > battery.last_sample_time){
		battery.recharing_error = 1;
		_disable_charging();
	}
}

/*
 * Simply checks to see if either motor draw is exceeding maximum
 */
int is_battery_in_dangerous_state(){
	return battery.right_motor_current_draw > MAX_CURRENT_DRAW ||
		   battery.left_motor_current_draw > MAX_CURRENT_DRAW ||
		   battery._in_overload_cooldown;
}


/*
 * A bit more tricky. Has dual purpose. If the
 * battery is not re-charging, but needs to, starts
 * the re-charge process and returns 1. Else, if it
 * is currently re-charging, returns a 1. Finally, if
 * not re-charging, returns a 0
 */
int is_batter_recharging(){

	//check for already re-charing
	if(battery.is_recharging) return CHARGING;

	//check if it needs to re-charge
	if(battery.volts < LOW_BATTERY_VOLTAGE){
		_start_charger();
		return 1;
	}

	//battery is recharged, resume normal operations
	if(battery.is_recharging && battery.volts >= NOMINAL_BATTERY_VOLTAGE){
		_disable_charger();
	}

	return NOT_CHARGING;

}

/*
 * Simply returns the struct value
 */
int has_recharging_error(){ return battery.recharing_error;}

/*
 * Manages overload timeouts
 */
void set_overload_timeout(){

	//overload timeout has not started
	if(!battery._overload_timeout_start){
		battery._overload_timeout_start = millis();
		battery._in_overload_cooldown = 1;
	}

	//overload timeout has expired
	if(battery._overload_timeout_start + OVERLOAD_TIME_OUT > millis()){
		battery._overload_timeout_start = 0;
		battery._in_overload_cooldown = 0;
	}

}

/*
 * Simply removes the charging status
 */
void _disable_charger(){

	pinMode(CHARGER, OUTPUT);
	digitalWrite(CHARGER, 1);
	battery.is_recharging = NOT_CHARGING;

}

/*
 * Simply initializes the charging status
 */
void _start_charger(){

	//init re-charge info used in checking for re-charge issues
	battery._initial_recharging_time = millis();
	battery._starting_voltage = battery.volts;

	pinMode(CHARGER, OUTPUT);
	digitalWrite(CHARGER, 0);

	battery.is_recharging = CHARGING;
}

