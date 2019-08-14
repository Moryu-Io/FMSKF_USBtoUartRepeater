/*
 * wrapper_usb_if.hpp
 *
 *  Created on: 2019/08/14
 *      Author: Moryu
 */

#ifndef WRAPPER_USB_IF_HPP_
#define WRAPPER_USB_IF_HPP_

#include "stm32l4xx_hal.h"


#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32l4xx_hal.h"

void toRingBufPush(uint8_t* _buf, uint16_t* len);

#ifdef __cplusplus
 }
#endif






#endif /* WRAPPER_USB_IF_HPP_ */
