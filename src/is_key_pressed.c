/*
 * is_key_pressed.c
 *
 * The register PIO_BUTTONS_IN_BASE which has address memory 0x8091680 has value of 0x03 if
 * no button is pressed. If key0 is pressed the register's value become 0x02 and if key1 is
 * pressed the register value become 0x01
 *
 * 	if key0 is pressed PIO_BUTTONS_IN_BASE = 0010 & 0001 gives 0000
 *	  0010  key
 *	& 0001 mask
 *	  0000  ans
 *
 *
 *  Created on: Oct 13, 2020
 *      Author: Saif
 *****************************************************************************************************************/

#include <io.h> //for the HAL functions t.ex. PIO_BUTTONS_IN_BASE
#include <system.h> // for use of SOPC base-address definitons
#include <stdbool.h>
#include "is_key_pressed.h"

 /* returns false if the push button 0 is not pressed and true if pressed*/
bool is_key0_pressed(){

	if(IORD_8DIRECT(PIO_BUTTONS_IN_BASE, 0) & 0x01)
		return false;
	else
		return true;
}

/* returns false if the push button 1 is not pressed and true if pressed*/
bool is_key1_pressed(){

	if(IORD_8DIRECT(PIO_BUTTONS_IN_BASE, 0) & 0x02)
		return false;
	else
		return true;
}

//bool is_some_key_pressed(){
//
//	if(IORD_8DIRECT(PIO_BUTTONS_IN_BASE, 0) != 0x03)
//		return true;
//	else
//		return false;
//}

