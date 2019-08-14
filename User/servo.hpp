/*
 * servo.hpp
 *
 *  Created on: 2019/08/12
 *      Author: Moryu
 */

#ifndef SERVO_HPP_
#define SERVO_HPP_

#include "stm32l4xx_hal.h"


class Servo{
public:
	Servo(){};
	Servo(uint8_t _id):
		u8_ID_(_id){};

	enum MotionStatus{
		INITIALIZE,
		FREE,
		STANDBY,
		MOVE,
		ERROR
	};

	enum ErrorStatus{
		NO_ERROR,
		OVER_TEMP,
		OVER_LOAD,
		OVER_ANGLE,
		OTHER
	};


	void set_tgt_angle(float _tgt);
	void set_upper_limit_angle(float _uplim){ fl_upper_limit_angle_deg_ = _uplim; };
	void set_lower_limit_angle(float _lwlim){ fl_lower_limit_angle_deg_ = _lwlim; };

	float get_now_angle() {return fl_now_angle_deg_;};
	float get_tgt_angle() {return fl_tgt_angle_deg_;};


private:
	uint8_t u8_ID_;

	MotionStatus Motion_Status_ = INITIALIZE;
	ErrorStatus  Error_Status_  = NO_ERROR;


	float fl_now_angle_deg_;
	float fl_tgt_angle_deg_;

	float fl_upper_limit_angle_deg_ =  360.0f;
	float fl_lower_limit_angle_deg_ = -360.0f;


};


#endif /* SERVO_HPP_ */
