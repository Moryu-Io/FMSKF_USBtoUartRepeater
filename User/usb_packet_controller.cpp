/*
 * usb_packet_controller.cpp
 *
 *  Created on: 2019/08/14
 *      Author: Moryu
 */

#include "usb_packet_controller.hpp"
#include "usbd_cdc_if.h"

#include "LED.hpp"
#include <string.h>




/**
 *
 * @param _buf
 * @param len
 */
void USBPacketController::USBRXringbuf_push(uint8_t* _buf, uint16_t* len){
	USBRXringbuf.push_back((const uint8_t*)_buf, *len);
	flag_USBRXbuf = 1;
}

void USBPacketController::USBTXbuf_push(uint8_t* _buf, uint16_t &_len){
	if(_len>0) memcpy(&(this->tx_packet_[0]), _buf, _len);
	tx_packet_len_ = _len;
	_len = 0;
	flag_USBTXbuf = true;
}


/**
 *
 */
void USBPacketController::USBRXdataprocess(){
	if(flag_USBRXbuf == true){
		int _buf_index = 0;
		while(_buf_index < (int16_t)USBRXringbuf.size()-3){
			if((USBRXringbuf[_buf_index] == 0x55) && (USBRXringbuf[_buf_index+1] == 0x55)){
				// 0x55二連続の場合、Lx16a仕様のサーボパケットと判断
				// 更に、全パケット存在するか確認。
				uint8_t _pklength = USBRXringbuf[_buf_index+3]+3;		//コマンドパケットの長さ
				if(_buf_index+_pklength <= USBRXringbuf.size()){
					// 全パケット存在する場合
					USBRXringbuf.pop_front(_buf_index);		//パケットの始まりまでバッファを削除

					for(int i=0;i<_pklength;i++){
						rx_packet_[i] = USBRXringbuf.pull();
					}
					// debug用
					//CDC_Transmit_FS(rx_packet_, _pklength);
					p_servoserial_->USBRXpacketprocess(rx_packet_, _pklength);

				}else{
					// ヘッダーは存在したが、全パケットなかった場合、受信途中のためprocessを終了する
					break;
				}

			}else{

			}
			_buf_index++;
		}

		flag_USBRXbuf = false;
	}else{

	}

}



void USBPacketController::USBTXdataprocess(){
	if(flag_USBTXbuf == true){
		if(CDC_Transmit_FS(&(this->tx_packet_[0]),tx_packet_len_ ) == USBD_BUSY){

		}else{
			flag_USBTXbuf = false;
		}
	}else{

	}
}
