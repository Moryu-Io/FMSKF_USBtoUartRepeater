/*
 * const_param_sys.hpp
 *
 *  Created on: 2019/08/10
 *      Author: Moryu
 */

#ifndef CONST_PARAM_SYS_HPP_
#define CONST_PARAM_SYS_HPP_



static constexpr uint16_t u16_MAIN_TASK_PERIOD_MS 		= 10;
static constexpr uint16_t u16_USBCTRL_TASK_PERIOD_MS 	= 1;
static constexpr uint16_t u16_SERVOCTRL_TASK_PERIOD_MS 	= 1;

static constexpr uint16_t u16_USBRX_PACKET_MAX_LENGTH		= 16;
static constexpr uint16_t u16_LX16ATX_PACKET_MAX_LENGTH	  = u16_USBRX_PACKET_MAX_LENGTH;
static constexpr uint16_t u16_LX16ARX_PACKET_MAX_LENGTH  = u16_LX16ATX_PACKET_MAX_LENGTH*2;

static constexpr uint8_t u8_SHOULDER_YAW_SERVO_ID  			= 1;
static constexpr uint8_t u8_SHOULDER_PITCH_SERVO_ID 			= 2;
static constexpr uint8_t u8_SHOULDER_PITCH_SERVO_SUB_ID	= 3;
static constexpr uint8_t u8_ELBOW_PITCH_SERVO_ID					= 4;
static constexpr uint8_t u8_WRIST_YAW_SERVO_ID						= 5;
static constexpr uint8_t u8_WRIST_PITCH_SERVO_ID					= 6;






#endif /* CONST_PARAM_SYS_HPP_ */
