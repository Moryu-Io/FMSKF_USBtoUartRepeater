/*
 * LED.hpp
 *
 *  Created on: 2019/05/06
 *      Author: Moryu
 */

#ifndef LED_HPP_
#define LED_HPP_

#include "stm32l4xx_hal.h"
#include "stm32l4xx_ll_tim.h"


namespace LED{

enum COLOR{
	RED,
	GREEN,
	ALL
};

void StartBlink(COLOR _c, float _freq);
void StopBlink(COLOR _c);

void TurnOn(COLOR _c);
void TurnOff(COLOR _c);




}



#endif /* LED_HPP_ */
