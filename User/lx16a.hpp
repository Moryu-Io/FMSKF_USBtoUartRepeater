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

class Lx16a : Servo{
public:
	Lx16a();


	void creat_packet_move(float _tgt_pos_deg, uint16_t _move_time_ms);
	void creat_packet_read(LX16ACOMMAND::COMMAND _cmd);


private:



public:

};



namespace LX16ACOMMAND{

struct COMMAND{
	uint8_t Value;
	uint8_t Length;
};

static constexpr COMMAND MOVE_TIME_WRITE		= {1, 7};
static constexpr COMMAND MOVE_TIME_READ 		= {2, 3};
static constexpr COMMAND MOVE_TIME_WAIT_WRITE	= {7, 7};
static constexpr COMMAND MOVE_TIME_WAIT_READ	= {8, 3};

static constexpr COMMAND MOVE_START				= {11, 3};
static constexpr COMMAND MOVE_STOP		 		= {12, 3};

static constexpr COMMAND ID_WRITE				= {13, 4};
static constexpr COMMAND ID_READ		 		= {14, 3};

static constexpr COMMAND ANGLE_OFFSET_ADJUST	= {17, 4};
static constexpr COMMAND ANGLE_OFFSET_WRITE		= {18, 3};
static constexpr COMMAND ANGLE_OFFSET_READ		= {19, 3};

static constexpr COMMAND ANGLE_LIMIT_WRITE		= {20, 7};
static constexpr COMMAND ANGLE_LIMIT_READ		= {21, 3};

static constexpr COMMAND VIN_LIMIT_WRITE		= {22, 7};
static constexpr COMMAND VIN_LIMIT_READ			= {23, 3};

static constexpr COMMAND TEMP_MAX_LIMIT_WRITE	= {24, 4};
static constexpr COMMAND TEMP_MAX_LIMIT_READ	= {25, 3};

static constexpr COMMAND TEMP_READ				= {26, 3};
static constexpr COMMAND VIN_READ				= {27, 3};
static constexpr COMMAND POS_READ				= {28, 3};

static constexpr COMMAND SERVO_OR_MOTOR_MODE_WRITE	= {29, 7};
static constexpr COMMAND SERVO_OR_MOTOR_MODE_READ	= {30, 3};

static constexpr COMMAND LOAD_OR_UNLOAD_WRITE	= {31, 4};
static constexpr COMMAND LOAD_OR_UNLOAD_READ	= {32, 3};

static constexpr COMMAND LED_CTRL_WRITE			= {33, 4};
static constexpr COMMAND LED_CTRL_READ			= {34, 3};

static constexpr COMMAND LED_ERROR_WRITE		= {35, 4};
static constexpr COMMAND LED_ERROR_READ			= {36, 3};


}




#endif /* LX16A_HPP_ */
