/*
 * task_display_on_vga.h
 *
 *  Created on: Oct 14, 2020
 *      Author: Saif
 */

#ifndef TASK_DISPLAY_ON_VGA_H_
#define TASK_DISPLAY_ON_VGA_H_

#define SCREEN_HIGHT 320
#define SCREEN_WIDTH 240

#define SEMAPHORE 1

void task_display_on_vga_code(void);
void write_to_vga();


#endif /*TASK_DISPLAY_ON_VGA_H_*/
