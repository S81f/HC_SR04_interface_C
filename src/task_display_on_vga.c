/*
 * task_display_on_vga.c display the measured distance on vga-monitor
 *
 *  Created on: Oct 14, 2020
 *      Author: Saif
 *
 *
 ************ pseudo code *******************
 *      initiate function period time;
 *
 *		while(1){
 *
 *			write_to_vga();
 *
 *		}
 *
 *****************************************************************************************************************/

#include <altera_avalon_sierra_ker.h>
#include <altera_avalon_sierra_io.h>
#include <altera_avalon_sierra_regs.h>
#include <altera_avalon_sierra_name.h>
#include <stdio.h>
#include <alt_types.h>
#include <draw_vga.h>
#include "task_display_on_vga.h"


alt_u16 measured_distance;
/*********************************************************************************************************
* 
* *********************************************************************************************************/
void task_display_on_vga_code(void){


	/*Argument (hera 50) Specifies the period time, in number of ticks, for calling task.
	* 50*0.02= 1sec
	*/
	init_period_time(50); // one second period time

	// test to check if there is deadline miss
	//task_periodic_start_union test;


	while(1)
	{

		wait_for_next_period();

/*		test=wait_for_next_period();
		if(test.periodic_start_integer & 0x01)
			alt_printf("deadline miss, display_on_vga\n");*/


		sem_take(SEMAPHORE);
		write_to_vga();
		sem_release(SEMAPHORE);

	}
}

void write_to_vga(){

	tty_print((SCREEN_WIDTH/3)-50,(SCREEN_HIGHT/4)-10,"The measured distance (cm) is: ", 0xfff, 0x000);
	int_print((SCREEN_WIDTH)+40,(SCREEN_HIGHT/4)-10, measured_distance, 3, 0xfff, 0x000);


}

