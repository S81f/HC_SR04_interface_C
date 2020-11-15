/*
 * task_idle.c will execute when there is no other task ready to execute.
 *If no idle-task would exist the system behavior would be undefined.
 *The idle-task shall not make any system calls to the Sierra., lowest priority and taskid 0
 *
 *  Created on: Oct 14, 2020
 *      Author: Saif
 *
 **************************************************************************************************/

#include <stdio.h>

void idle_task_code(void){


  while(1)
   {
	  ;
  }
}

