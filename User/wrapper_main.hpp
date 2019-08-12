/*
 * wrapper_main.hpp
 *
 *  Created on: 2019/08/10
 *      Author: Moryu
 */

#ifndef WRAPPER_MAIN_HPP_
#define WRAPPER_MAIN_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"


void maintask_cpp(void);

void USBCtrltask_cpp(void);
void ServoCtrltask_cpp(void);

#ifdef __cplusplus
}
#endif



#endif /* WRAPPER_MAIN_HPP_ */
