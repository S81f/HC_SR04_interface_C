/*
 * processing_data.c  get echo_signal_length from task_trigging_and_getting_data.c.
 * convert echo_signal_length to time in us
 * calculate the measured distance by dividing the time in us by 58 according to data sheet in link below:
 * https://components101.com/sites/default/files/component_datasheet/HCSR04%20Datasheet.pdf
 * update the extern variable measured_distance
 *
 *  Created on: Oct 14, 2020
 *      Author: Saif Saadaldin
 *
 * ************ pseudo code *******************
 *
 * 		initiate function period time;
 *
 * 		while(1){
 *
 * 			calculate_measured_distance();
 *
 * 		}
 *
 * **************************************************************************************************************/

#include <altera_avalon_sierra_ker.h>
#include <altera_avalon_sierra_io.h>
#include <altera_avalon_sierra_regs.h>
#include <altera_avalon_sierra_name.h>
#include <stdio.h>
#include <alt_types.h>
#include "task_processing_data.h"



alt_u32 echo_signal_length;
alt_u16 measured_distance;


void task_processing_data_code(void){

	init_period_time(50);//1 sec
	//task_periodic_start_union test;


while(1)
	{
		wait_for_next_period();
		/*This function Let current task wait for next period.*/
		/*test=wait_for_next_period();
		if(test.periodic_start_integer & 0x01)
			alt_printf("deadline miss, processing_data\n");*/

		sem_take(SEMAPHORE);
		calculate_measured_distance();
		sem_release(SEMAPHORE);

	}

}

void calculate_measured_distance(){

	measured_distance = echo_signal_length * CONST;

}
