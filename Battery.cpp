/*
 * Battery.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: kulis
 */


#include "Battery.h"

Battery::Battery(){

	_initial_recharging_time = _starting_voltage = -1;
	_last_sample_time = millis();
	_known_highest_voltage = _volts =  analogRead(ANALOG_BATTERY_INPUT);
	_is_recharging = false;
	_has_recharging_error = false;

}

/**
 * Checks the state of the battery. Updates best known voltage (in re-charge),
 * checks for a lack of re-charge (sets flag and disables charging)
 *
 */
void Battery::do_battery_diagnostics(){

	_last_sample_time = millis();
	_volts = analogRead(ANALOG_BATTERY_INPUT);

	//update best known voltage
	if(_is_recharging && _volts > _known_highest_voltage) _known_highest_voltage = _volts;

	/**
	 * NOTE: NEED TO CHECK FOR LACK OF VOLTAGE CHANGE IN THIS TOO. NOT QUITE SURE WHAT TO CHECK, A RANGE (EG 10%) OR EXACT VAL
	 */
	//check for re-charging error
	if(_is_recharging && _initial_recharging_time + CHARGER_TIMEOUT > _last_sample_time){
		_has_recharging_error = true;
		end_charging();
	}

}

/**
 * Enables battery re-charging
 */
void Battery::start_charging(){

	_initial_recharging_time = millis();
	_starting_voltage = analogRead(ANALOG_BATTERY_INPUT);
	pinMode(CHARGER_PORT, OUTPUT);
	digitalWrite(CHARGER_PORT, 0);
	_is_recharging = true;

}

/**
 * Disables battery re-charging
 */
void Battery::end_charging(){

	_initial_recharging_time = _starting_voltage = -1;
	pinMode(CHARGER_PORT, OUTPUT);
	digitalWrite(CHARGER_PORT, 1);
	_is_recharging = false;

}
