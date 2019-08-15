/*
 * krs_servo.hpp
 *
 *  Created on: 2019/08/12
 *      Author: Moryu
 */

#ifndef KRS_SERVO_HPP_
#define KRS_SERVO_HPP_

#include "servo.hpp"
#include "stm32l4xx_hal.h"
#include "lx16a_command.hpp"
#include "ICS_command.hpp"
#include "const_param_sys.hpp"

class KRS_servo : Servo{
public:
	KRS_servo(){};
	KRS_servo(uint8_t _id, USART_TypeDef* _pusart) : Servo(_id, _pusart),
			next_tx_packet_(),rx_packet_(), next_tx_packet_len_(0),rx_packet_len_(0),next_rx_flag_(false),
			next_cmd_(ICS_COMMAND::COMMAND_NONE){};

	void creat_packet_from_usbpacket(uint8_t* _usbpk, uint16_t _len);

	void communication_with_servo();

	void get_rx_packet(uint8_t* _rxpk, uint16_t &_len);

private:
	uint8_t next_tx_packet_[u16_KRSTX_PACKET_MAX_LENGTH];
	uint8_t rx_packet_[u16_KRSRX_PACKET_MAX_LENGTH];
	uint16_t next_tx_packet_len_;
	uint16_t rx_packet_len_;
	bool next_rx_flag_;

	ICS_COMMAND::COMMAND next_cmd_;

	void conv_LX16AtoICS36_MOVE_TIME_WRITE(uint8_t* _usbpk);
	void conv_LX16AtoICS36_LOAD_OR_UNLOAD_WRITE(uint8_t* _usbpk);
	void conv_LX16AtoICS36_POS_READ(uint8_t* _usbpk);

};



#endif /* KRS_SERVO_HPP_ */
