/*
 * wrapper_main.cpp
 *
 *  Created on: 2019/08/10
 *      Author: Moryu
 */

#include "wrapper_main.hpp"
#include "const_param_sys.hpp"
#include "cmsis_os.h"


void maintask_cpp(void){
	TickType_t _xLastExecutionTime = xTaskGetTickCount();

	while(1){
		osDelayUntil(&_xLastExecutionTime, u16_MAIN_TASK_PERIOD_MS);

	}
}


void USBCtrltask_cpp(void){
	TickType_t _xLastExecutionTime = xTaskGetTickCount();

	while(1){
		osDelayUntil(&_xLastExecutionTime, u16_USBCTRL_TASK_PERIOD_MS);
	}

}



void ServoCtrltask_cpp(void){
	TickType_t _xLastExecutionTime = xTaskGetTickCount();

	while(1){
		osDelayUntil(&_xLastExecutionTime, u16_SERVOCTRL_TASK_PERIOD_MS);

	}

}
