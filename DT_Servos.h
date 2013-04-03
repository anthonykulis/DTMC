/*
 * DT_Servos.h
 *
 *  Created on: Apr 3, 2013
 *      Author: akulis
 */

#ifndef DT_SERVOS_H_
#define DT_SERVOS_H_

#include <Servo.h>

#define NUM_SERVOS 7
#define DEFAULT_SERVO_POSITION 1500


#define S0 2
#define S1 4
#define S2 7
#define S3 8
#define S4 9
#define S5 10
#define S6 12

static servo_attached[NUM_SERVOS] = {0,};

Servo servos[NUM_SERVOS];

void attach_servos(int* servos_to_start);
void write_to_servo(int position, int value);

#endif /* DT_SERVOS_H_ */
