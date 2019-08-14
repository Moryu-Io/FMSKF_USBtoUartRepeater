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

class KRS_servo : Servo{
public:
	KRS_servo(){};
	KRS_servo(uint8_t _id, USART_TypeDef* _pusart) : Servo(_id, _pusart){};

private:

};



#endif /* KRS_SERVO_HPP_ */
