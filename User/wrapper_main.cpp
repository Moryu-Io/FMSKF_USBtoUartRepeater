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
#include "servo_serial.hpp"

USBPacketController usb_packet_ctrl;
Servo_Serial servo_serial_ctrl;

void maintask_cpp(void){
	TickType_t _xLastExecutionTime = xTaskGetTickCount();
	usb_packet_ctrl.setpointer_servo_serial(&servo_serial_ctrl);

	while(1){
		osDelayUntil(&_xLastExecutionTime, u16_MAIN_TASK_PERIOD_MS);

	}
}


void USBCtrltask_cpp(void){
	TickType_t _xLastExecutionTime = xTaskGetTickCount();

	while(1){
		osDelayUntil(&_xLastExecutionTime, u16_USBCTRL_TASK_PERIOD_MS);
		// 新たな受信バッファが追加されたとき
		if(usb_packet_ctrl.checkFlagUSBRXbuf() == true){
			usb_packet_ctrl.USBRXdataprocess();

		}else{

		}

		// 新たな送信バッファが追加されたとき
		if(usb_packet_ctrl.checkFlagUSBTXbuf() == true){
			usb_packet_ctrl.USBTXdataprocess();
		}else{

		}


	}

}



void ServoCtrltask_cpp(void){
	TickType_t _xLastExecutionTime = xTaskGetTickCount();
	uint8_t _servosRXpackets[u16_USBTX_PACKET_MAX_LENGTH] = {};
	uint16_t _servosRXpackets_len = 0;

	while(1){
		osDelayUntil(&_xLastExecutionTime, u16_SERVOCTRL_TASK_PERIOD_MS);
		servo_serial_ctrl.Communication_with_usart2();
		servo_serial_ctrl.getAllServoRXPacket(_servosRXpackets, _servosRXpackets_len);
		if(_servosRXpackets_len > 0){
			//サーボからの受信データ有
			usb_packet_ctrl.USBTXbuf_push(_servosRXpackets, _servosRXpackets_len);
		}
	}

}
