/*
 * This program is a sensore interaface for HC-SR04 ultra sound distance measurement sensor.
 * The program start with printing the engineer's name, date of the project.
 * When a user push button key_0 on the DE10-Lite board the RTOS Sierra starts to execute four different tasks.
 * the tasks will initiate the sensorn to start measuring distance to an obsticle and showing the result on vga-monitor.
 *
 * The memory footprint of this hosted application is ~30 kbytes with the optimizations that was done on the system.
 *
 *********************** pseudo code *******************
 
 *		initiate Sierra;
 *
 *		clear screen();
 *
 *		while(!is_key0_pressed){
 *			init_vga();
 *		}
 *
 *		clear screen();
 *
 *		set Sierra time base;
 *		declare all tasks;
 *		start scheduler;
 *
 *		while(some fault occur){
 *			show error massage;
 *		}
 *
 *
 ***************************************************************/

#include <altera_avalon_sierra_ker.h>
#include <altera_avalon_sierra_io.h>
#include <altera_avalon_sierra_regs.h>
#include <altera_avalon_sierra_name.h>
#include <altera_avalon_timer_regs.h> //for TIMER_HW_IP
#include <draw_vga.h>
#include <system.h> //for use of SOPC base-address definitons
#include <stdio.h>
#include <io.h> //for the HAL functions
#include <alt_types.h>
#include "task_trigging_and_getting_data.h"
#include "task_idle.h"
#include "task_display_on_vga.h"
#include "task_processing_data.h"
#include "init_vga.h"
#include "is_key_pressed.h"
#include "main.h"


//tasks in the system
#define Task_trigging_and_getting_data 3	//Highest priority. Runs every second
#define Task_processing_data 2			//Runs every second
#define Task_display_on_vga 1			//Runs every second
#define Task_idle 0    				//Priority 0. Not allowed to be in blocked state.

// define global variables
extern alt_u32 echo_signal_length;
extern alt_u16 measured_distance;


alt_u32 timer_value;


// TASK STACKS. Every task has its own stack.
#define STACK_SIZE 800
char idle_stack[STACK_SIZE];
char trigging_and_getting_data_stack[STACK_SIZE];
char processing_data_stack[STACK_SIZE];
char display_on_vga_stack[STACK_SIZE];

/*----------------------------Main---------------------------------------*/
int main (void){


	//Sierra initiation hardware, variables, interrupt and TCB (Task control Block).
	Sierra_Initiation_HW_and_SW();


	/*while(1){
	TIMER_RESET();
	TIMER_START();

	timer_value = TIMER_READ();
	printf("TIMER VALUE = %d\n",timer_value );
	TIMER_STOP();}*/

	clear_screen(0x000);

	while(!is_key0_pressed()){
		init_vga();
	}

	clear_screen(0x000);


  /*********************************************************************
   * Define the clock tick in the system.
   * A register is used to set-up internal clock tick period for all timing queues in the Sierra
   * Sierra time base register value = time tick * system frequency/1000
   * Initialize time base register.
   * This example     : 50 MHz system-clock
   * Wanted tick time : 20 ms (50Hz)// The Sierra has it clock period every 20ms
   * Formula gives    : 20 ms x 50 MHx / 1000 => 1000(dec)
   * ******************************************************************/
	//Sets the internal clock-tick timebase for the Sierra.
	set_timebase(1000);
	//set_timebase(1); gives us tick time of 20us

	/* task_create() 	TaskID, priority, taskState, taskPtr,        stackPtr,  stackSize */
	task_create(Task_idle, 0, READY_TASK_STATE, idle_task_code, idle_stack, STACK_SIZE);

	task_create(Task_trigging_and_getting_data, 4, READY_TASK_STATE, task_trigging_and_getting_data_code, trigging_and_getting_data_stack, STACK_SIZE);

	task_create(Task_processing_data, 3, READY_TASK_STATE, task_processing_data_code, processing_data_stack, STACK_SIZE);

	task_create(Task_display_on_vga, 2, READY_TASK_STATE, task_display_on_vga_code, display_on_vga_stack, STACK_SIZE);

	// Start the Sierra scheduler
	tsw_on(); // enable CPU irq from Sierran and now at least idle will give a irq.

	while(1) {
		// Should never end up here...!
		alt_printf("* ERROR! SYSTEM FAILED *\n ");
	}
}
