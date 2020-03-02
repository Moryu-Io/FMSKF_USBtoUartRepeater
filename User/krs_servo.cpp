/*
 * krs_servo.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: Moryu
 */

#include "krs_servo.hpp"
#include "timecount.hpp"
#include <string.h>
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_usart.h"
#include "usbd_cdc_if.h"
#include "LED.hpp"
#include "dma.h"
#include "const_param_sys.hpp"


void KRS_servo::creat_packet_from_usbpacket(uint8_t* _usbpk, uint16_t _len){
	switch(_usbpk[4]){
	case LX16ACOMMAND::POS_READ.Value:
		next_cmd_ = ICS_COMMAND::NOW_POS_READ ;
		conv_LX16AtoICS36_POS_READ(_usbpk);
		break;
	case LX16ACOMMAND::MOVE_TIME_WRITE.Value:
		next_cmd_ = ICS_COMMAND::MOVE_POS_WRITE;
		conv_LX16AtoICS36_MOVE_TIME_WRITE(_usbpk);
		break;
	case LX16ACOMMAND::LOAD_OR_UNLOAD_WRITE.Value:
		LED::TurnOn(LED::RED);
		next_cmd_ = ICS_COMMAND::TORQUE_OFF_WRITE;
		conv_LX16AtoICS36_LOAD_OR_UNLOAD_WRITE(_usbpk);
		break;
	default:
		next_cmd_ = ICS_COMMAND::COMMAND_NONE;
		next_rx_flag_ = false;
		break;
	}

}

void KRS_servo::communication_with_servo(){
	if(next_tx_packet_len_ > 0){
		//DMA完了フラグ待ち。タイムアウト処理追加
		TIMCNT::ResetCount();
		TIMCNT::StartCount(1000);
		while((!(TIMCNT::IsTimeOut())) &&
				(u8_DMA1CH4_isRunning || u8_DMA1CH5_isRunning));
		TIMCNT::ResetCount();
		//送信前にRXのDMAをセット。長さはTX+RX
		if(next_cmd_.RXnum>0){
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, next_cmd_.TXnum+next_cmd_.RXnum);
		}else{
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, next_cmd_.TXnum);
		}
		LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_5, (uint32_t)(&(this->rx_packet_[0])));
		LL_USART_EnableDMAReq_RX(USART1);
		u8_DMA1CH5_isRunning = 1;
		LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_5);
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);
		//TXのDMAをセット
		LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)(&(this->next_tx_packet_[0])));
		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, next_tx_packet_len_);
		LL_USART_EnableDMAReq_TX(USART1);
		u8_DMA1CH4_isRunning = 1;
		LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);

		//受信待ち
		TIMCNT::ResetCount();
		TIMCNT::StartCount(1000);
		while((!(TIMCNT::IsTimeOut())) && u8_DMA1CH5_isRunning);
		if(TIMCNT::IsTimeOut()){
			//タイムアウトならば
			rx_packet_len_ = 0;
		}else{
			if(next_cmd_.RXnum > 0){
				rx_packet_len_ = next_cmd_.RXnum;
				//RX前半のTXpacketは削除
				for(int i=0; i<rx_packet_len_;i++){
					rx_packet_[i] = rx_packet_[next_tx_packet_len_+i];
				}
			}else{
				rx_packet_len_ = 0;
			}
		}
		TIMCNT::ResetCount();

		next_tx_packet_len_ = 0;
		next_rx_flag_ = false;


	}else{

	}
}

void KRS_servo::get_rx_packet(uint8_t* _rxpk, uint16_t &_len){
	if(rx_packet_len_ > 0)	memcpy(_rxpk, rx_packet_, rx_packet_len_);
	_len = rx_packet_len_;
	rx_packet_len_ = 0;
}


void KRS_servo::conv_LX16AtoICS36_MOVE_TIME_WRITE(uint8_t* _usbpk){
	uint16_t _pos = (uint16_t)_usbpk[5] | ((uint16_t)_usbpk[6] << 8);
	int16_t _s16_pos = (int16_t)_pos - 500;
	_pos = (uint16_t) ((float)_s16_pos * LX16AtoICS36_POS_RATIO +7500.0f);

	next_tx_packet_[0] =  ICS_COMMAND::MOVE_POS_WRITE.Cmd | u8_ID_;
	next_tx_packet_[1] = (uint8_t)((_pos >> 7)&0x7F);
	next_tx_packet_[2] = (uint8_t)(_pos&0x7F);

	next_tx_packet_len_ = 3;
	next_rx_flag_ = true;
}

void KRS_servo::conv_LX16AtoICS36_LOAD_OR_UNLOAD_WRITE(uint8_t* _usbpk){
	if(_usbpk[5] == 0){
		next_tx_packet_[0] = ICS_COMMAND::TORQUE_OFF_WRITE.Cmd | u8_ID_;
		next_tx_packet_[1] = 0x00;
		next_tx_packet_[2] = 0x00;
		next_tx_packet_len_ = 3;
		next_rx_flag_ = true;
	}
}

void KRS_servo::conv_LX16AtoICS36_POS_READ(uint8_t* _usbpk){
	next_tx_packet_[0] =  ICS_COMMAND::NOW_POS_READ.Cmd | u8_ID_;
	next_tx_packet_[1] =  ICS_COMMAND::NOW_POS_READ.SCmd;

	next_tx_packet_len_ = 2;
	next_rx_flag_ = true;
}
