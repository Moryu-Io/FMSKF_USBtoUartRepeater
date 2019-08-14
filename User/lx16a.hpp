/*
 * lx16a.hpp
 *
 *  Created on: 2019/08/12
 *      Author: Moryu
 */

#ifndef LX16A_HPP_
#define LX16A_HPP_

#include "stm32l4xx_hal.h"
#include "servo.hpp"
#include "lx16a_command.hpp"
#include "const_param_sys.hpp"

class Lx16a : Servo{
public:
	Lx16a(){};
	Lx16a(uint8_t _id, USART_TypeDef* _pusart) : Servo(_id, _pusart),
			next_tx_packet_(),rx_packet_(), next_tx_packet_len_(0),rx_packet_len_(0),next_rx_flag_(false){};

	void creat_packet_move(float _tgt_pos_deg, uint16_t _move_time_ms);
	void creat_packet_read(LX16ACOMMAND::COMMAND _cmd);

	void creat_packet_from_usbpacket(uint8_t* _usbpk, uint16_t _len);

	void communication_with_servo();

	void get_rx_packet(uint8_t* _rxpk, uint16_t &_len);


private:
	uint8_t next_tx_packet_[u16_LX16ATX_PACKET_MAX_LENGTH];
	uint8_t rx_packet_[u16_LX16ARX_PACKET_MAX_LENGTH];
	uint16_t next_tx_packet_len_;
	uint16_t rx_packet_len_;
	bool next_rx_flag_;


public:

};







#endif /* LX16A_HPP_ */
