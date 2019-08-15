/*
 * timecount.cpp
 *
 *  Created on: Aug 15, 2019
 *      Author: Moryu
 */

#include "timecount.hpp"

static TIM_TypeDef* p_TIMER = TIM16;
uint16_t TimeOutCount = 0;

void TIMCNT::ResetCount(){
	LL_TIM_DisableCounter(p_TIMER);
	TIM16->CNT = 0;
	TimeOutCount = 0;
}

void TIMCNT::StartCount(uint16_t _cnt){
	TimeOutCount = _cnt;
	LL_TIM_EnableCounter(p_TIMER);
}

void TIMCNT::StopCount(){
	LL_TIM_DisableCounter(p_TIMER);
}

bool TIMCNT::IsTimeOut(){
	return (TimeOutCount <= p_TIMER->CNT) ? true : false;
}
