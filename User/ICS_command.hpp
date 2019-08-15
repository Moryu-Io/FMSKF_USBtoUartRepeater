/*
 * ICS_command.hpp
 *
 *  Created on: Aug 15, 2019
 *      Author: Moryu
 */

#ifndef ICS_COMMAND_HPP_
#define ICS_COMMAND_HPP_

#include "stm32l4xx_hal.h"

namespace ICS_COMMAND{

struct COMMAND{
	uint8_t Cmd;
	uint8_t SCmd;			// 0xFFはサブコマンドnull
	uint8_t TXnum;			// 送信パケット数
	uint8_t RXnum;			// 受信パケット数
};

static constexpr COMMAND COMMAND_NONE 		= {0, 0, 0, 0};

static constexpr COMMAND MOVE_POS_WRITE 	= {0b10000000, 0xFF, 3, 3};
static constexpr COMMAND TORQUE_OFF_WRITE 	= {0b10000000, 0xFF, 3, 3};

static constexpr COMMAND NOW_POS_READ		= {0b10100000, 0x05, 2, 4};



}



#endif /* ICS_COMMAND_HPP_ */
