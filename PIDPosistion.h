/*
 * PIDPosistion.h
 *
 *  Created on: Jun 29, 2014
 *      Author: TDNC
 */
#include "main.h"
/*
 *
 */
#define inv_sampling_time 	5
#define sampling_time		200
/*
 *
 */
void PIDPos(int32_t pos_l, int32_t pos_r);
void MotorController(int32_t spd_l, int32_t spd_r);
