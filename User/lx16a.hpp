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


class Lx16a : Servo{
public:
	Lx16a(){};
	Lx16a(uint8_t _id) : Servo(_id){};


	void creat_packet_move(float _tgt_pos_deg, uint16_t _move_time_ms);
	void creat_packet_read(LX16ACOMMAND::COMMAND _cmd);


private:



public:

};







#endif /* LX16A_HPP_ */
