/*
 * servo_serial.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: Moryu
 */


#include "servo_serial.hpp"
#include "LED.hpp"

KRS_servo Servo_Serial::Shoulder_Yaw_Servo(u8_SHOULDER_YAW_SERVO_ID, USART1);
Lx16a Servo_Serial::Shoulder_Pitch_Servo(u8_SHOULDER_PITCH_SERVO_ID, USART2);
Lx16a Servo_Serial::Shoulder_Pitch_Servo_sub(u8_SHOULDER_PITCH_SERVO_SUB_ID, USART2);
Lx16a Servo_Serial::Elbow_Pitch_Servo(u8_ELBOW_PITCH_SERVO_ID, USART2);
Lx16a Servo_Serial::Wrist_Yaw_Servo(u8_WRIST_YAW_SERVO_ID, USART2);
Lx16a Servo_Serial::Wrist_Pitch_Servo(u8_WRIST_PITCH_SERVO_ID, USART2);

/**
 *
 * @param _pk : packet from USB
 * @param _len : packet length
 */
void Servo_Serial::USBRXpacketprocess(uint8_t* _pk, uint16_t _len){
	switch(_pk[2]){
	case u8_SHOULDER_YAW_SERVO_ID:
		Shoulder_Yaw_Servo.creat_packet_from_usbpacket(_pk, _len);
		break;
	case u8_SHOULDER_PITCH_SERVO_ID:
		Shoulder_Pitch_Servo.creat_packet_from_usbpacket(_pk, _len);
		break;
	case u8_SHOULDER_PITCH_SERVO_SUB_ID:
		Shoulder_Pitch_Servo_sub.creat_packet_from_usbpacket(_pk, _len);
		break;
	case u8_ELBOW_PITCH_SERVO_ID:
		Elbow_Pitch_Servo.creat_packet_from_usbpacket(_pk, _len);
		break;
	case u8_WRIST_YAW_SERVO_ID:
		Wrist_Yaw_Servo.creat_packet_from_usbpacket(_pk, _len);
		break;
	case u8_WRIST_PITCH_SERVO_ID:
		Wrist_Pitch_Servo.creat_packet_from_usbpacket(_pk, _len);
		break;



	}
}

void Servo_Serial::Communication_with_usart2(){
	Shoulder_Yaw_Servo.communication_with_servo();
	Shoulder_Pitch_Servo.communication_with_servo();
	Shoulder_Pitch_Servo_sub.communication_with_servo();
	Elbow_Pitch_Servo.communication_with_servo();
	Wrist_Yaw_Servo.communication_with_servo();
	Wrist_Pitch_Servo.communication_with_servo();
}


void Servo_Serial::getAllServoRXPacket(uint8_t* _pk, uint16_t &_len){
	uint16_t _onepk_length = 0;

	Shoulder_Yaw_Servo.get_rx_packet(&_pk[0], _onepk_length);
	_len = _onepk_length;

	Shoulder_Pitch_Servo.get_rx_packet(&_pk[0], _onepk_length);
	_len += _onepk_length;

	Shoulder_Pitch_Servo_sub.get_rx_packet(&_pk[_len], _onepk_length);
	_len += _onepk_length;

	Elbow_Pitch_Servo.get_rx_packet(&_pk[_len], _onepk_length);
	_len += _onepk_length;

	Wrist_Yaw_Servo.get_rx_packet(&_pk[_len], _onepk_length);
	_len += _onepk_length;

	Wrist_Pitch_Servo.get_rx_packet(&_pk[_len], _onepk_length);
	_len += _onepk_length;


}
