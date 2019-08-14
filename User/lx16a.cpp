/*
 * lx16a.cpp
 *
 *  Created on: 2019/08/12
 *      Author: Moryu
 */

#include "lx16a.hpp"
#include <string.h>

void Lx16a::creat_packet_from_usbpacket(uint8_t* _usbpk, uint16_t _len){
	switch(_usbpk[4]){
	case LX16ACOMMAND::MOVE_TIME_READ.Value:
	case LX16ACOMMAND::MOVE_TIME_WAIT_READ.Value:
	case LX16ACOMMAND::ID_READ.Value:
	case LX16ACOMMAND::ANGLE_OFFSET_READ.Value:
	case LX16ACOMMAND::ANGLE_LIMIT_READ.Value:
	case LX16ACOMMAND::VIN_LIMIT_READ.Value:
	case LX16ACOMMAND::TEMP_MAX_LIMIT_READ.Value:
	case LX16ACOMMAND::TEMP_READ.Value:
	case LX16ACOMMAND::VIN_READ.Value:
	case LX16ACOMMAND::POS_READ.Value:
	case LX16ACOMMAND::SERVO_OR_MOTOR_MODE_READ.Value:
	case LX16ACOMMAND::LOAD_OR_UNLOAD_READ.Value:
	case LX16ACOMMAND::LED_CTRL_READ.Value:
	case LX16ACOMMAND::LED_ERROR_READ.Value:
		next_rx_flag_ = true;
		memcpy(next_tx_packet_, _usbpk, _len);
		next_tx_packet_len_ = _len;
		break;
	case LX16ACOMMAND::MOVE_TIME_WRITE.Value:
	case LX16ACOMMAND::MOVE_TIME_WAIT_WRITE.Value:
	case LX16ACOMMAND::MOVE_START.Value:
	case LX16ACOMMAND::MOVE_STOP.Value:
	case LX16ACOMMAND::ID_WRITE.Value:
	case LX16ACOMMAND::ANGLE_OFFSET_ADJUST.Value:
	case LX16ACOMMAND::ANGLE_OFFSET_WRITE.Value:
	case LX16ACOMMAND::ANGLE_LIMIT_WRITE.Value:
	case LX16ACOMMAND::VIN_LIMIT_WRITE.Value:
	case LX16ACOMMAND::TEMP_MAX_LIMIT_WRITE.Value:
	case LX16ACOMMAND::SERVO_OR_MOTOR_MODE_WRITE.Value:
	case LX16ACOMMAND::LOAD_OR_UNLOAD_WRITE.Value:
	case LX16ACOMMAND::LED_CTRL_WRITE.Value:
	case LX16ACOMMAND::LED_ERROR_WRITE.Value:
		memcpy(next_tx_packet_, _usbpk, _len);
		next_tx_packet_len_ = _len;
		break;
	default:
		break;

	}
}

void Lx16a::communication_with_servo(){
	if(next_tx_packet_len_ > 0){
		// 送信パケットがある場合
		if(next_rx_flag_){
			//送るパケットが受信コマンドの場合

			//DMA完了フラグ待ち。タイムアウト処理追加

			//送信前にRXのDMAをセット。長さはTX+RX

			//TXのDMAをセット

			//RX前半のTXは削除


			next_tx_packet_len_ = 0;
			next_rx_flag_ = false;
		}
	}

}

void Lx16a::get_rx_packet(uint8_t* _rxpk, uint16_t &_len){
	if(rx_packet_len_ > 0)	memcpy(_rxpk, rx_packet_, rx_packet_len_);
	_len = rx_packet_len_;
	rx_packet_len_ = 0;
}
