/*
 * servo.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: Moryu
 */


#include "servo.hpp"


void Servo::set_tgt_angle(float _tgt){
	if(_tgt > fl_upper_limit_angle_deg_) 	  _tgt = fl_upper_limit_angle_deg_;
	else if(_tgt < fl_lower_limit_angle_deg_) _tgt = fl_lower_limit_angle_deg_;

	fl_tgt_angle_deg_ = _tgt;

}
