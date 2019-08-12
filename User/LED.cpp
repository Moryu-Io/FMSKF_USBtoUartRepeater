/*
 * LED.cpp
 *
 *  Created on: 2019/05/06
 *      Author: Moryu
 */


#include "LED.hpp"


/**
 * @fn LED::StartBlink
 * @param (_c)      LEDの色
 * @param (_freq)   LED点滅の周期(0.1Hz - 1kHz)
 * @detail
 */
void LED::StartBlink(LED::COLOR _c, float _freq){
	if(_freq > 1000.0f)		TIM2->PSC = 0;
	else if(_freq < 0.1f) 	TIM2->PSC = 9999;
	else 					TIM2->PSC = (uint32_t)(1000.0f/_freq - 1);

	// LED駆動用PWMのタイマー起動
	LL_TIM_EnableCounter(TIM2);

	switch(_c){
	case RED:
		LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
		TIM2->CCR1 = 40000;
		break;
	case GREEN:
		LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH2);
		TIM2->CCR2 = 40000;
		break;
	case ALL:
		LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1|LL_TIM_CHANNEL_CH2);
		TIM2->CCR1 = 40000;
		TIM2->CCR2 = 40000;
		break;
	}

}

void LED::StopBlink(LED::COLOR _c){
	switch(_c){
	case RED:
		LL_TIM_CC_DisableChannel(TIM2, LL_TIM_CHANNEL_CH1);
		TIM2->CCR1 = 0;
		break;
	case GREEN:
		LL_TIM_CC_DisableChannel(TIM2, LL_TIM_CHANNEL_CH2);
		TIM2->CCR2 = 0;
		break;
	case ALL:
		LL_TIM_CC_DisableChannel(TIM2, LL_TIM_CHANNEL_CH1|LL_TIM_CHANNEL_CH2);
		TIM2->CCR1 = 0;
		TIM2->CCR2 = 0;
		break;
	}
}


void LED::TurnOn(COLOR _c){
	LL_TIM_EnableCounter(TIM2);

	switch(_c){
	case RED:
		LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
		TIM2->CCR1 = 79999;
		break;
	case GREEN:
		LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH2);
		TIM2->CCR2 = 79999;
		break;
	case ALL:
		LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1|LL_TIM_CHANNEL_CH2);
		TIM2->CCR1 = 79999;
		TIM2->CCR2 = 79999;
		break;
	}

}


void LED::TurnOff(COLOR _c){
	StopBlink(_c);
}
