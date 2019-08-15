/*
 * lx16a.cpp
 *
 *  Created on: 2019/08/12
 *      Author: Moryu
 */

#include "lx16a.hpp"
#include "timecount.hpp"
#include <string.h>
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_usart.h"
#include "usbd_cdc_if.h"
#include "LED.hpp"
#include "dma.h"

void Lx16a::creat_packet_from_usbpacket(uint8_t* _usbpk, uint16_t _len){
	switch(_usbpk[4]){
	case LX16ACOMMAND::MOVE_TIME_READ.Value:						next_cmd_ = LX16ACOMMAND::MOVE_TIME_READ; break;
	case LX16ACOMMAND::MOVE_TIME_WAIT_READ.Value:				next_cmd_ = LX16ACOMMAND::MOVE_TIME_WAIT_READ; break;
	case LX16ACOMMAND::ID_READ.Value:										next_cmd_ = LX16ACOMMAND::ID_READ ; break;
	case LX16ACOMMAND::ANGLE_OFFSET_READ.Value:					next_cmd_ = LX16ACOMMAND::ANGLE_OFFSET_READ ; break;
	case LX16ACOMMAND::ANGLE_LIMIT_READ.Value:					next_cmd_ = LX16ACOMMAND::ANGLE_LIMIT_READ ; break;
	case LX16ACOMMAND::VIN_LIMIT_READ.Value:						next_cmd_ = LX16ACOMMAND:: VIN_LIMIT_READ; break;
	case LX16ACOMMAND::TEMP_MAX_LIMIT_READ.Value:				next_cmd_ = LX16ACOMMAND::TEMP_MAX_LIMIT_READ ; break;
	case LX16ACOMMAND::TEMP_READ.Value:									next_cmd_ = LX16ACOMMAND::TEMP_READ ; break;
	case LX16ACOMMAND::VIN_READ.Value:									next_cmd_ = LX16ACOMMAND::VIN_READ ; break;
	case LX16ACOMMAND::POS_READ.Value:									next_cmd_ = LX16ACOMMAND::POS_READ ; break;
	case LX16ACOMMAND::SERVO_OR_MOTOR_MODE_READ.Value:	next_cmd_ = LX16ACOMMAND::SERVO_OR_MOTOR_MODE_READ ; break;
	case LX16ACOMMAND::LOAD_OR_UNLOAD_READ.Value:			next_cmd_ = LX16ACOMMAND::LOAD_OR_UNLOAD_READ ; break;
	case LX16ACOMMAND::LED_CTRL_READ.Value:							next_cmd_ = LX16ACOMMAND::LED_CTRL_READ ; break;
	case LX16ACOMMAND::LED_ERROR_READ.Value:						next_cmd_ = LX16ACOMMAND::LED_ERROR_READ ; break;

	case LX16ACOMMAND::MOVE_TIME_WRITE.Value:						next_cmd_ = LX16ACOMMAND::MOVE_TIME_WRITE; break;
	case LX16ACOMMAND::MOVE_TIME_WAIT_WRITE.Value:			next_cmd_ = LX16ACOMMAND::MOVE_TIME_WAIT_WRITE; break;
	case LX16ACOMMAND::MOVE_START.Value:								next_cmd_ = LX16ACOMMAND::MOVE_START; break;
	case LX16ACOMMAND::MOVE_STOP.Value:								next_cmd_ = LX16ACOMMAND::MOVE_STOP; break;
	case LX16ACOMMAND::ID_WRITE.Value:									next_cmd_ = LX16ACOMMAND::ID_WRITE; break;
	case LX16ACOMMAND::ANGLE_OFFSET_ADJUST.Value:				next_cmd_ = LX16ACOMMAND::ANGLE_OFFSET_ADJUST; break;
	case LX16ACOMMAND::ANGLE_OFFSET_WRITE.Value:				next_cmd_ = LX16ACOMMAND::ANGLE_OFFSET_WRITE; break;
	case LX16ACOMMAND::ANGLE_LIMIT_WRITE.Value:					next_cmd_ = LX16ACOMMAND::ANGLE_LIMIT_WRITE; break;
	case LX16ACOMMAND::VIN_LIMIT_WRITE.Value:						next_cmd_ = LX16ACOMMAND::VIN_LIMIT_WRITE; break;
	case LX16ACOMMAND::TEMP_MAX_LIMIT_WRITE.Value:			next_cmd_ = LX16ACOMMAND::TEMP_MAX_LIMIT_WRITE; break;
	case LX16ACOMMAND::SERVO_OR_MOTOR_MODE_WRITE.Value:		next_cmd_ = LX16ACOMMAND::SERVO_OR_MOTOR_MODE_WRITE; break;
	case LX16ACOMMAND::LOAD_OR_UNLOAD_WRITE.Value:			next_cmd_ = LX16ACOMMAND::LOAD_OR_UNLOAD_WRITE; break;
	case LX16ACOMMAND::LED_CTRL_WRITE.Value:						next_cmd_ = LX16ACOMMAND::LED_CTRL_WRITE; break;
	case LX16ACOMMAND::LED_ERROR_WRITE.Value:						next_cmd_ = LX16ACOMMAND::LED_ERROR_WRITE; break;
	default:	next_cmd_ = LX16ACOMMAND::COMMAND_NONE;		break;
	}
	if(next_cmd_.Value != LX16ACOMMAND::COMMAND_NONE.Value){
		if(next_cmd_.rLen > 0) next_rx_flag_ = true;
		else next_rx_flag_ = false;
		memcpy(next_tx_packet_, _usbpk, _len);
		next_tx_packet_len_ = _len;
	}

}

void Lx16a::communication_with_servo(){
	if(next_tx_packet_len_ > 0){
		// 送信パケットがある場合
		//if(next_rx_flag_){
			//送るパケットが受信コマンドの場合

			//DMA完了フラグ待ち。タイムアウト処理追加
			TIMCNT::ResetCount();
			TIMCNT::StartCount(1000);
			while((!(TIMCNT::IsTimeOut())) &&
					(u8_DMA1CH6_isRunning || u8_DMA1CH7_isRunning));
			TIMCNT::ResetCount();
			//送信前にRXのDMAをセット。長さはTX+RX
			if(next_cmd_.rLen>0){
				LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, next_tx_packet_len_+next_cmd_.rLen+3);
			}else{
				LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, next_tx_packet_len_);
			}
			LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_6, (uint32_t)(&(this->rx_packet_[0])));
			LL_USART_EnableDMAReq_RX(USART2);
			u8_DMA1CH6_isRunning = 1;
			LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_6);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);
			//TXのDMAをセット
			LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_7, (uint32_t)(&(this->next_tx_packet_[0])));
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, next_tx_packet_len_);
			LL_USART_EnableDMAReq_TX(USART2);
			u8_DMA1CH7_isRunning = 1;
			LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_7);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_7);

			//受信待ち
			TIMCNT::ResetCount();
			TIMCNT::StartCount(1000);
			while((!(TIMCNT::IsTimeOut())) && u8_DMA1CH6_isRunning);
			if(TIMCNT::IsTimeOut()){
				//タイムアウトならば
				rx_packet_len_ = 0;
			}else{
				if(next_cmd_.rLen > 0){
					rx_packet_len_ = rx_packet_[next_tx_packet_len_+3] + 3;
					//RX前半のTXpacketは削除
					for(int i=0; i<rx_packet_len_;i++){
						rx_packet_[i] = rx_packet_[next_tx_packet_len_+i];
					}
				}else{
					rx_packet_len_ = 0;
				}
			}
			TIMCNT::ResetCount();
			//LL_DMA_ClearFlag_TC6(DMA1);

			next_tx_packet_len_ = 0;
			next_rx_flag_ = false;
		/*}else{
			//送るパケットが送信コマンドの場合
			//DMA完了フラグ待ち。タイムアウト処理追加
			TIMCNT::ResetCount();
			TIMCNT::StartCount(1000);
			while((!(TIMCNT::IsTimeOut())) &&
					(u8_DMA1CH6_isRunning || u8_DMA1CH7_isRunning));
			TIMCNT::ResetCount();

			//送信前にRXのDMAを念のため無効化
			//LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_6);

			//TXのDMAをセット
			LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_7, (uint32_t)(&(this->next_tx_packet_[0])));
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, next_tx_packet_len_);
			LL_USART_EnableDMAReq_TX(USART2);
			u8_DMA1CH7_isRunning = 1;
			LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_7);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_7);

			next_tx_packet_len_ = 0;
			next_rx_flag_ = false;
		}*/
	}

}

void Lx16a::get_rx_packet(uint8_t* _rxpk, uint16_t &_len){
	if(rx_packet_len_ > 0)	memcpy(_rxpk, rx_packet_, rx_packet_len_);
	_len = rx_packet_len_;
	rx_packet_len_ = 0;
}
