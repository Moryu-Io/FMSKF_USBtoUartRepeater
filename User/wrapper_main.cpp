/*
 * wrapper_main.cpp
 *
 *  Created on: 2019/08/10
 *      Author: Moryu
 */

#include "wrapper_main.hpp"
#include "const_param_sys.hpp"
#include "cmsis_os.h"
#include "usb_packet_controller.hpp"
#include "LED.hpp"
#include "usbd_cdc_if.h"


USBPacketController usb_packet_ctrl;

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
		//LED::TurnOn(LED::RED);
		// 新たな受信バッファが追加されたとき
		if(usb_packet_ctrl.checkFlagUSBRXbuf() == true){
			LED::TurnOn(LED::RED);
			usb_packet_ctrl.USBRXdataprocess();

		}else{

		}

		// 新たな送信バッファが追加されたとき
		if(usb_packet_ctrl.checkFlagUSBTXbuf() == true){

		}else{

		}


	}

}



void ServoCtrltask_cpp(void){
	TickType_t _xLastExecutionTime = xTaskGetTickCount();

	while(1){
		osDelayUntil(&_xLastExecutionTime, u16_SERVOCTRL_TASK_PERIOD_MS);

	}

}
