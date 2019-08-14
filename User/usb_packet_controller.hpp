/*
 * usb_packet_controller.hpp
 *
 *  Created on: 2019/08/14
 *      Author: Moryu
 */

#ifndef USB_PACKET_CONTROLLER_HPP_
#define USB_PACKET_CONTROLLER_HPP_

#include "DKS_CircularBuffer.h"
#include "stm32l4xx_hal.h"
#include "const_param_sys.hpp"
#include "servo_serial.hpp"

class USBPacketController{
public:
	USBPacketController():
		p_servoserial_(),flag_USBRXbuf(false),flag_USBTXbuf(false),rx_packet_() {}
	~USBPacketController(){}

	//void setFlagUSBRXbuf(bool _f) { flag_USBRXbuf = _f; };
	//void setFlagUSBTXbuf(bool _f) { flag_USBTXbuf = _f; };
	bool checkFlagUSBRXbuf(){ return flag_USBRXbuf; };
	bool checkFlagUSBTXbuf(){ return flag_USBTXbuf; };

	void USBRXringbuf_push(uint8_t* _buf, uint16_t* len);

	void USBRXdataprocess();

	void setpointer_servo_serial(Servo_Serial* _p){ p_servoserial_ = _p; };

private:
	DKS::CircularBuffer<uint8_t, 64> USBRXringbuf;
	Servo_Serial* p_servoserial_;

	bool flag_USBRXbuf;
	bool flag_USBTXbuf;

	uint8_t rx_packet_[u16_USBRX_PACKET_MAX_LENGTH];

};



#endif /* USB_PACKET_CONTROLLER_HPP_ */
