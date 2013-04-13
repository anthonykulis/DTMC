/*
 * Battery.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: kulis
 */


#include "Battery.h"
#include "Register.h"

Battery::Battery(){

	_initial_recharging_time = _starting_voltage = -1;
	_last_sample_time = millis();
	_known_highest_voltage = _volts =  analogRead(ANALOG_BATTERY_INPUT);
	_is_recharging = false;
	_has_recharging_error = false;
	_r = &DataRegister;
	_auto_recharge = false;
}

/**
 * Checks the state of the battery. Updates best known voltage (in re-charge),
 * checks for a lack of re-charge (sets flag and disables charging)
 *
 */
void Battery::do_battery_diagnostics(){

	_last_sample_time = millis();
	_volts = analogRead(ANALOG_BATTERY_INPUT);
	Serial.print("_volts: ");
	Serial.println(_volts);

	//naive auto recharge -- needs expansion?
	_update_ac();
	if(_auto_recharge){
		if(_volts < LOW_BATTERY_VOLTAGE){
			Serial.println("auto recharge started");			
			start_charging();
		}
		else if(_volts >= NOMINAL_BATTERY_VOLTAGE) end_charging();
	}

	//update best known voltage - was for something about learning the battery, but not sure what anymore
	if(_is_recharging && _volts > _known_highest_voltage) _known_highest_voltage = _volts;

	/**
	 * NOTE: NEED TO CHECK FOR LACK OF VOLTAGE CHANGE IN THIS TOO. NOT QUITE SURE WHAT TO CHECK, A RANGE (EG 10%) OR EXACT VAL
	 */
	//check for re-charging error
	if(_is_recharging && _initial_recharging_time + CHARGER_TIMEOUT > _last_sample_time && _volts <= _starting_voltage){
		
		_has_recharging_error = true;
		
		//place in reg for i2c
		regd_t r = _r->open(RECHARGING_ERROR, REG_MASTER_MODE);
		_r->write(r, 0x01);
		_r->close(r);

		end_charging();
	}


	unsigned char high = _volts >> 8;
	unsigned char low = _volts & 0x00FF;
	
 
	//write the voltage of the battery
	regd_t d = _r->open(READ_BATTERY_LEVEL_HIGH, REG_MASTER_MODE);
	_r->write(d, high);
	_r->close(d);
	d = _r->open(READ_BATTERY_LEVEL_LOW, REG_MASTER_MODE);
	_r->write(d, low);
	_r->close(d);


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

	//update register
	regd_t r = _r->open(RECHARGING, REG_MASTER_MODE);
	_r->write(r, 0x01);
	_r->close(r);

}

/**
 * Disables battery re-charging
 */
void Battery::end_charging(){

	_initial_recharging_time = _starting_voltage = -1;
	pinMode(CHARGER_PORT, OUTPUT);
	digitalWrite(CHARGER_PORT, 1);
	_is_recharging = false;

	//update register
	regd_t r = _r->open(RECHARGING, REG_MASTER_MODE);
	_r->write(r, 0x00);
	_r->close(r);

}

void Battery::_update_ac(){

	regd_t r = _r->open(SET_AUTO_RECHARGE, REG_READ_ONLY);
	int ac = _r->read(r);
	_r->close(r);

	_auto_recharge = ac > 0;

}

Battery SystemBattery = Battery();

