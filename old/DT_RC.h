/*
 * DT_RC.h
 *
 *  Created on: Apr 3, 2013
 *      Author: akulis
 */

#ifndef DT_RC_H_
#define DT_RC_H_

// Set to 1 if L/R and F/R signals from RC need to be mixed
#define MIX 1

// when RC inputs are centered then input should be 1.5mS
#define LEFT_CENTER 1500
#define RIGHT_CENTER 1500

// inputs do not have to be perfectly centered to stop motors
#define DEADBAND

// scale factor for RC signal to PWM
#define SCALE 12

#define RC_LEFT 0
#define RC_RIGHT 1

#endif /* DT_RC_H_ */
