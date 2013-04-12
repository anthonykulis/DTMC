/*
 * Battery.h
 *
 *  Created on: Apr 10, 2013
 *      Author: kulis
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include "Arduino.h"
#include "Register.h"

#define CHARGER_PORT 13
#define CHARGER_TIMEOUT 300000

//deprecated from port?
enum { NOT_CHARGING, CHARGING };

#define ANALOG_BATTERY_INPUT 0

//these values are those present by original authors,
//not sure how they come to them. When supply is about 6.3v (my sla batteries)
//I have a nominal value of around 360ish. On a 10 bit ADC, and a voltage
//divide of 1 to 1, I should be at 512ish. With a voltage divide such that
//7.2v -> 5v gives a resistor ratio of .44 and a decimal value of 6.3v of
//649. so, anyways, if my math is correct, its best to just set this to
//your system.
#define NOMINAL_BATTERY_VOLTAGE 487
#define LOW_BATTERY_VOLTAGE 410

class Battery {

public:
	Battery();
	void do_battery_diagnostics();
	inline int get_battery_voltage(){ return _volts; }
	inline bool is_battery_recharging(){ return _is_recharging; }
	inline bool has_recharging_error(){ return _has_recharging_error; }
	void start_charging();
	void end_charging();

private:
	Register *_r;
	int _last_sample_time;
	int _known_highest_voltage;
	int _volts;
	bool _is_recharging;
	bool _has_recharging_error;
	int _initial_recharging_time;
	int _starting_voltage;
	bool _auto_recharge;
	void _update_ac();

};

extern Battery SystemBattery;
#endif /* BATTERY_H_ */
