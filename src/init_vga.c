/*
 * init_vga.c
 *
 *  Created on: Oct 15, 2020
 *      Author: Saif
 */

#include "init_vga.h"

void init_vga(){

	tty_print((SCREEN_WIDTH/3),(SCREEN_HIGHT/3),"HCSR04 sensor interface", 0xfff, 0x000);
	tty_print((SCREEN_WIDTH/3)+10,(SCREEN_HIGHT/3)+10,"By: Saif Saadaldin", 0xfff, 0x000);
	tty_print((SCREEN_WIDTH/3)+30,(SCREEN_HIGHT/3)+20,"08-Nov-2020", 0xfff, 0x000);

}
