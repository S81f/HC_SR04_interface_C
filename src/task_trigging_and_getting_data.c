/*
 * task_trigging_and_getting_data.c Sends 10us(500 clock cycls) pulse to the ultrasonic sound sensor to
 *  activate it and then process the echo pulse coming back from sensor
 *
 *  Created on: Oct 13, 2020
 *      Author: Saif
 *
 *
 * ***************** pseudo code ******************************
 *
 *		initiate function period time;
 *		set pin 13 as output;
 *		set pin 11 as input;
 *
 *		while(1){
 *
 *			delay_60ms();
 *			trigg_hcsr04_sensor();
 *			process_incoming_echo_signals();
 *
 *		}
 ************************************************************/

#include <altera_avalon_sierra_ker.h>
#include <altera_avalon_sierra_io.h>
#include <altera_avalon_sierra_regs.h>
#include <altera_avalon_sierra_name.h>
#include <alt_types.h>
#include <altera_avalon_timer_regs.h> //for TIMER_HW_IP
#include <DE10_Lite_Arduino_Driver.h>
#include <stdio.h>
#include "task_trigging_and_getting_data.h"



//global vari can be optimize by using volatile
alt_u32 echo_signal_length;//save total clock cycles during higt echo signal


void task_trigging_and_getting_data_code(void){


	/*This function initializes the period time for the calling task. The period time = 50 which gives 1s.
	Inititialize period time for current task.*/
	init_period_time(50);
	//task_periodic_start_union test; //for deadline miss tests
		
	//initiating pin modes for Arduino headers. Should one set all the othe unused input and outputs to unused mode?
	//should these initiations be in the main func??
	arduino_pin_mode(PIN_D13, PIN_OUTPUT); //set output pin mode (trig pin)
	arduino_pin_mode(PIN_D11, PIN_INPUT); //set input pin mode (echo pin)
	
	while(1)
	{
		wait_for_next_period();

		/*This function suspends the calling task until the start of next period time. Let current task wait for next period.*/
		/*test=wait_for_next_period(); //Every second. If there is deadline miss test=1
		if(test.periodic_start_integer & 0x01)
			alt_printf("deadline miss, trigging_and_getting_data\n");*/
		
		delay_60ms();

		trigg_hcsr04_sensor();

		sem_take(SEMAPHORE); //semaphores for protecting critical tasks
		process_incoming_echo_signals();
		sem_release(SEMAPHORE);

	}

}

void trigg_hcsr04_sensor(){

	
	arduino_digital_write(PIN_D13,SIGNAL_LOW);//to clear the pin
	TIMER_RESET();
	TIMER_START();
	
	/*
	*500 is the number of clock cycle in 10us ==> 20ns = 0.02us
	* 0.02us * x = 10us ==> x = 500
	*/
	while(TIMER_READ() < 500){
	
		/* Write to digital pin specified as output
		void arduino_digital_write(alt_u8 pin,alt_u8 signal) {
		IOWR_32DIRECT(DE10_LITE_ARDUINO_IP_0_BASE,4,((pin<<1)|signal));
		}*/
		arduino_digital_write(PIN_D13,SIGNAL_HIGH);
	}
	arduino_digital_write(PIN_D13,SIGNAL_LOW);
	TIMER_RESET();
}

/*
* function to detect incoming echo from sensor and calculate the
* number of clock cycle during high echo signal
*/

void process_incoming_echo_signals(){

	TIMER_RESET();
	
	//no echo
	while(arduino_digital_read(PIN_D11) == SIGNAL_LOW){
	//if the total time the program spending here is long maybe indicate out of range
		;
	}
 
	//echo detected
	while(arduino_digital_read(PIN_D11) == SIGNAL_HIGH){
		TIMER_START();
	}

	TIMER_STOP();

	echo_signal_length = TIMER_READ();

	//printf("echo signal length= %lu\n", echo_signal_length);// %lu to print long unsigned

}

void delay_60ms(){
	
	TIMER_RESET();
	TIMER_START();
	
	while(TIMER_READ() < TRIG_DELAY)
		;
	
	TIMER_RESET();
}

