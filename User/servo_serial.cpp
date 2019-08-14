/*
 * servo_serial.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: Moryu
 */


#include "servo_serial.hpp"


KRS_servo Servo_Serial::Shoulder_Yaw_Servo(u8_SHOULDER_YAW_SERVO_ID);
Lx16a Servo_Serial::Shoulder_Pitch_Servo(u8_SHOULDER_PITCH_SERVO_ID);
Lx16a Servo_Serial::Shoulder_Pitch_Servo_sub(u8_SHOULDER_PITCH_SERVO_SUB_ID);
Lx16a Servo_Serial::Elbow_Pitch_Servo(u8_ELBOW_PITCH_SERVO_ID);
Lx16a Servo_Serial::Wrist_Yaw_Servo(u8_WRIST_YAW_SERVO_ID);
Lx16a Servo_Serial::Wrist_Pitch_Servo(u8_WRIST_PITCH_SERVO_IO);

/**
 *
 * @param _pk : packet from USB
 * @param _len : packet length
 */
void Servo_Serial::USBRXpacketprocess(uint8_t* _pk, uint16_t _len){
	switch(_pk[3]){
	case u8_SHOULDER_YAW_SERVO_ID:
		break;
	case u8_SHOULDER_PITCH_SERVO_ID:
		break;

	}
}
