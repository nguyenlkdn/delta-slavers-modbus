/*
 * systemctl.h
 *
 *  Created on: Jan 4, 2014
 *      Author: TDNC
 */

#ifndef SYSTEMCTL_H_
#define SYSTEMCTL_H_

//*****************************************************************************
//
// Function System
//
//*****************************************************************************
void cfg_uart(void);
void cfg_clock(void);
void cfg_timer(void);
void cfg_interrupt(void);
void cfg_port(void);
void cfg_peripheral(void);
void cfg_pwm(void);
void cfg_systick(void);
void cfg_qei(void);
void init(void);
void DisableTimer(uint8_t timer_number);
void EnableTimer(uint8_t timer_number);
void PrintBinary(unsigned short data);
#endif /* SYSTEMCTL_H_ */
