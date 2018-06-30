/*
 * main.h
 *
 *  Created on: Apr 10, 2014
 *      Author: TDNC
 */

#ifndef MAIN_H_
#define MAIN_H_
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/ssi.h"
#include "driverlib/flash.h"
#include "driverlib/systick.h"
#include "driverlib/qei.h"
#include "System.h"
#include "PIDPosistion.h"
/*
 *
 */
/*
 *
 */
#endif /* MAIN_H_ */
#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80
extern uint32_t	enc3;

