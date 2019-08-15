/*
 * servo_serial.hpp
 *
 *  Created on: 2019/08/14
 *      Author: Moryu
 */

#ifndef SERVO_SERIAL_HPP_
#define SERVO_SERIAL_HPP_

#include "stm32l4xx_hal.h"
#include "krs_servo.hpp"
#include "lx16a.hpp"
#include "const_param_sys.hpp"

class Servo_Serial{
private:
	static KRS_servo Shoulder_Yaw_Servo;
	static Lx16a Shoulder_Pitch_Servo;
	static Lx16a Shoulder_Pitch_Servo_sub;
	static Lx16a Elbow_Pitch_Servo;
	static Lx16a Wrist_Yaw_Servo;
	static Lx16a Wrist_Pitch_Servo;



public:
	Servo_Serial(){};
	~Servo_Serial(){};


	void USBRXpacketprocess(uint8_t* _pk, uint16_t _len);
	void Communication_with_usart2();
	void getAllServoRXPacket(uint8_t* _pk, uint16_t &_len);

};




#endif /* SERVO_SERIAL_HPP_ */
