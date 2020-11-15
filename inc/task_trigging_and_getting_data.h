/*
 * task_trigging_and_getting_data.h
 *
 *  Created on: Oct 13, 2020
 *      Author: Saif
 */

#ifndef TASK_TRIGGING_AND_GETTING_DATA_H_
#define TASK_TRIGGING_AND_GETTING_DATA_H_

#define SEMAPHORE 1

#define TRIG_DELAY 3000000

void delay_60ms();
void trigg_hcsr04_sensor();
void process_incoming_echo_signals();
void task_trigging_and_getting_data_code(void);


#endif /* TASK_TRIGGING_AND_GETTING_DATA_H_ */
