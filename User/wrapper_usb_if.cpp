/*
 * wrapper_usb_if.cpp
 *
 *  Created on: 2019/08/14
 *      Author: Moryu
 */

#include "wrapper_usb_if.hpp"
#include "DKS_CircularBuffer.h"
#include "usb_packet_controller.hpp"

extern USBPacketController usb_packet_ctrl;

void toRingBufPush(uint8_t* _buf, uint16_t* len){
	usb_packet_ctrl.USBRXringbuf_push(_buf, len);
}
