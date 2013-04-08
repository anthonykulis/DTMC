/*
 * Main.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: kulis
 */

#include "Runner.h"
#include "Register.h"



Register r;
Runner runner(r);
regd_t mrd;


void setup(){

}

void loop(){

	runner.update();
	delay(10);
}
