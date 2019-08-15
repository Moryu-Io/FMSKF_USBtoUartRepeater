/*
 * timecount.hpp
 *
 *  Created on: Aug 15, 2019
 *      Author: Moryu
 */

#ifndef TIMECOUNT_HPP_
#define TIMECOUNT_HPP_

#include "stm32l4xx_hal.h"
#include "stm32l4xx_ll_tim.h"

namespace TIMCNT {



void ResetCount();
void StartCount(uint16_t);
void StopCount();
bool IsTimeOut();


}  // namespace TIMCNT



#endif /* TIMECOUNT_HPP_ */
