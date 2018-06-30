/*
 * PIDPosistion.c
 *
 *  Created on: Jun 29, 2014
 *      Author: TDNC
 */
#include "PIDPosistion.h"
/*
 *
 */
int32_t rPos_l, Err_l, pre_err_l, pPart_l, dPart_l, iPart_l, output_l;
int32_t kp_l = 10;
int32_t ki_l = 3;
int32_t kd_l = 0;
// 100 10 15
// 110 20 15
// 110 40 20 100sps
// 110 00 80 200sps
// 100 00 80 200sps

int32_t rPos_r, Err_r, pre_err_r, pPart_r, dPart_r, iPart_r, output_r;
int32_t kp_r = 10;
int32_t ki_r = 3;
int32_t kd_r = 0;

/*
 *
 */
__inline void PIDPos(int32_t pos_l, int32_t pos_r){
	rPos_l 	= 	QEIPositionGet(QEI1_BASE);
	Err_l 	= 	pos_l-rPos_l;
	pPart_l 	= 	kp_l*Err_l;
	dPart_l 	= 	kd_l*(Err_l-pre_err_l)*inv_sampling_time;
	//iPart_l 	+= 	(ki_l*sampling_time*Err_l)/1000;

	output_l 	= 	pPart_l + dPart_l + iPart_l;

	rPos_r 	= 	QEIPositionGet(QEI0_BASE);
		Err_r 	= 	pos_r-rPos_r;
		pPart_r 	= 	kp_r*Err_r;
		dPart_r 	= 	kd_r*(Err_r-pre_err_r)*inv_sampling_time;
		//iPart_l 	+= 	(ki_l*sampling_time*Err_l)/1000;

		output_r 	= 	pPart_r + dPart_r + iPart_r;





	if(output_l >= 4990){
		output_l = 4990;
	}
	if(output_l <= -4990){
		output_l = -4990;
	}
		if(output_r >= 4990){
		output_r = 4990;
	}
	if(output_r <= -4990){
		output_r = -4990;
	}





	MotorController(output_l, output_r);
	pre_err_l = Err_l;
	pre_err_r = Err_r;
//	if(!UARTBusy(UART0_BASE)){
//		UARTprintf("\npPart : %5d iPart : %5d dPart : %5d Output : %5d Pos : %5d", Err_l, iPart_l, dPart_l, output_l, rPos_l);
//	}
			//UARTprintf(" Outputl : %5d ", Err_l );
///////////////////////////////////////////////////////////////






}
void MotorController(int32_t output_l, int32_t output_r) {
//	int dir_l = 1;
//	int dir_r = 4;
	if (output_l < 0) {
//		dir_l <<=1;
//		spd_l *= -1;
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, 0);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, output_l*-1);
	}else if(output_l > 0) {
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,  output_l);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, 0);
	}else {
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, 0);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, 0);
	//UARTprintf(" ok : %5d ",  output_l);
	}

	if (output_r < 0) {
//		dir_l <<=1;
//		spd_l *= -1;
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 0);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, output_r*-1);
	}else if(output_r > 0) {
			PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,  output_r);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 0);
	}else {
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 0);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 0);
	//UARTprintf(" ok : %5d ",  output_l);
	}


//	if (spd_r < 0){
////		dir_r <<=1;
////		spd_r *= -1;
//
//	}
//	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1, dir_l);
//	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2 | GPIO_PIN_3, dir_r);

}
