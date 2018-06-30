/*
 * systemctl.c
 *
 *  Created on: Jan 4, 2014
 *      Author: TDNC
 */
#include "main.h"
//*****************************************************************************
//
// System Function Details
//
//*****************************************************************************
void init(void){
	ROM_IntMasterDisable();
    ROM_FPULazyStackingEnable();
    cfg_clock();
    cfg_peripheral();
    cfg_port();
    cfg_uart();
    cfg_pwm();
    cfg_qei();
    cfg_timer();
    cfg_interrupt();
    cfg_systick();
    SysCtlDelay(16);
    ROM_IntMasterEnable();
}
void cfg_qei(void){
	//Set Pins to be PHA0 and PHB0 and Index
	GPIOPinConfigure(GPIO_PD6_PHA0);
	GPIOPinConfigure(GPIO_PD7_PHB0);
	GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_3 | GPIO_PIN_6 | GPIO_PIN_7);

	GPIOPinConfigure(GPIO_PC5_PHA1);
	GPIOPinConfigure(GPIO_PC6_PHB1);
	GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);

	//DISable peripheral and int before configuration
	QEIDisable(QEI0_BASE);
	QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, SysCtlClockGet()/20);
	QEIVelocityEnable(QEI0_BASE);

	QEIDisable(QEI1_BASE);
	QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, SysCtlClockGet()/20);
	QEIVelocityEnable(QEI1_BASE);
	// Configure quadrature encoder, use an arbitrary top limit of 1000
	QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B  | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 0xffffffff);
	QEIPositionSet(QEI0_BASE, 0);

	QEIConfigure(QEI1_BASE, (QEI_CONFIG_CAPTURE_A_B  | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 0xffffffff);
	QEIPositionSet(QEI1_BASE, 0);
	// Enable the quadrature encoder.
	QEIEnable(QEI0_BASE);
	QEIEnable(QEI1_BASE);



}
void EnableTimer(uint8_t timer_number){
	switch(timer_number){
	case 0 :
		ROM_TimerEnable(TIMER0_BASE, TIMER_A);
		break;
	case 1 :
		ROM_TimerEnable(TIMER1_BASE, TIMER_A);
		break;
	case 2 :
		ROM_TimerEnable(TIMER2_BASE, TIMER_A);
		break;
	case 3 :
		ROM_TimerEnable(TIMER3_BASE, TIMER_A);
		break;
	case 4 :
		ROM_TimerEnable(TIMER4_BASE, TIMER_A);
		break;
	case 5 :
		ROM_TimerEnable(TIMER5_BASE, TIMER_A);
		break;
	}
}
void DisableTimer(uint8_t timer_number){
	switch(timer_number){
	case 0 :
		ROM_TimerDisable(TIMER0_BASE, TIMER_A);
		break;
	case 1 :
		ROM_TimerDisable(TIMER1_BASE, TIMER_A);
		break;
	case 2 :
		ROM_TimerDisable(TIMER2_BASE, TIMER_A);
		break;
	case 3 :
		ROM_TimerDisable(TIMER3_BASE, TIMER_A);
		break;
	case 4 :
		ROM_TimerDisable(TIMER4_BASE, TIMER_A);
		break;
	case 5 :
		ROM_TimerDisable(TIMER5_BASE, TIMER_A);
		break;
	}
}
void PrintBinary(unsigned short data){
	unsigned short mask = 128;
	int i;
	for(i=0;i<8;i++){
		if(data & mask)
			UARTprintf("1");
		else{
			UARTprintf("0");
		}
		mask>>=1;
	}
}
void cfg_ssi0(void){
	GPIOPinConfigure(GPIO_PA2_SSI0CLK);
	GPIOPinConfigure(GPIO_PA3_SSI0FSS);
	GPIOPinConfigure(GPIO_PA5_SSI0TX);
	GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_2);

	SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 10000, 9);
	SSIEnable(SSI0_BASE);
}
void cfg_pwm(void){
	//Configure PWM Clock to match system
	GPIOPinConfigure(GPIO_PB6_M0PWM0);
	GPIOPinConfigure(GPIO_PB7_M0PWM1);
	GPIOPinConfigure(GPIO_PB4_M0PWM2);
	GPIOPinConfigure(GPIO_PB5_M0PWM3);
	GPIOPinConfigure(GPIO_PE4_M0PWM4);
	GPIOPinConfigure(GPIO_PE5_M0PWM5);
	GPIOPinConfigure(GPIO_PD0_M0PWM6);
	GPIOPinConfigure(GPIO_PD1_M0PWM7);
	GPIOPinConfigure(GPIO_PF2_M1PWM6);
	GPIOPinConfigure(GPIO_PF3_M1PWM7);

	GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
	GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);

	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    //Set the Period (expressed in clock ticks)
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, SysCtlClockGet()/10000);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, SysCtlClockGet()/10000);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, SysCtlClockGet()/10000);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, SysCtlClockGet()/10000);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, SysCtlClockGet()/10000);

    //Set PWM duty-50% (Period /2)
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 0);
      PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 0);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 0);

    // Enable the PWM generator
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);

    // Turn on the Output pins
    PWMOutputState(PWM1_BASE,   PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);

    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT | PWM_OUT_2_BIT | PWM_OUT_3_BIT | PWM_OUT_4_BIT | PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);
}
void cfg_interrupt(void){
	// Interrupt PORTF.0 & PORTF.4
	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_RISING_EDGE);
	IntEnable(INT_GPIOF);
	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
	// Interrupt PORTB.4 & PORTB.5
	GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 );
	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_FALLING_EDGE);
	IntEnable(INT_GPIOD);
	GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
}
void cfg_port(void) {
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	//Unlock GPIOD7 - Like PF0 its used for NMI - Without this step it doesn't work
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; //In Tiva include this is the same as "_DD" in older versions (0x4C4F434B)
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= GPIO_PIN_7;
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
	// Config Resistor for Interupt PORTC
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
			GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3);
	// Config Resistor for Interupt PORTC
	HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTC_BASE + GPIO_O_CR) = (GPIO_PIN_5);
	// Resistor Pull up for PORTF.0 & PORTF.4 with 8mA

	//GPIO For PORTF.0 & PORTF.4
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = GPIO_PIN_0;

	// Resistor Pull up for PORTF.0 & PORTF.4 with 8mA
	ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,
			GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
	ROM_GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 , GPIO_STRENGTH_8MA,
			GPIO_PIN_TYPE_STD_WPU);

}
void cfg_uart(void){
	// UART 0
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);
    //UARTIntEnable(UART0_BASE, UART_INT_RX);
    //IntEnable(INT_UART0);

    UARTprintf("\n***Thong Tin He Thong*******************");
    UARTprintf("\n***        CPU Clock %3d (Mhz)       ***", SysCtlClockGet()/1000000);
    UARTprintf("\n***        Timer 0 Enable            ***");
    UARTprintf("\n***        Timer 1 Enable            ***");
    UARTprintf("\n***        Timer 2 Enable            ***");
    UARTprintf("\n***        Timer 3 Enable            ***");
    UARTprintf("\n***        Timer 4 Enable            ***");
    UARTprintf("\n***        Timer 5 Enable            ***");
    UARTprintf("\n****************************************\n");

}
void cfg_peripheral(void){
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
}
void cfg_clock(void){
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}
void cfg_timer(void){
	// Timer 0
	TimerClockSourceSet(TIMER0_BASE, TIMER_CLOCK_PIOSC);
    ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, ROM_SysCtlClockGet()/100);
    ROM_IntEnable(INT_TIMER0A);
    ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    ROM_TimerEnable(TIMER0_BASE, TIMER_A);

    // Timer 1
	TimerClockSourceSet(TIMER1_BASE, TIMER_CLOCK_PIOSC);
    ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER1_BASE, TIMER_A, ROM_SysCtlClockGet()/20);
    ROM_IntEnable(INT_TIMER1A);
    ROM_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    ROM_TimerEnable(TIMER1_BASE, TIMER_A);

    // Timer 2
	TimerClockSourceSet(TIMER2_BASE, TIMER_CLOCK_PIOSC);
    ROM_TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER2_BASE, TIMER_A, ROM_SysCtlClockGet()/100);
    ROM_IntEnable(INT_TIMER2A);
    ROM_TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    //ROM_TimerEnable(TIMER2_BASE, TIMER_A);

    // Timer 3
	TimerClockSourceSet(TIMER3_BASE, TIMER_CLOCK_PIOSC);
    ROM_TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER3_BASE, TIMER_A, ROM_SysCtlClockGet()/100);
    ROM_IntEnable(INT_TIMER3A);
    ROM_TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    //ROM_TimerEnable(TIMER3_BASE, TIMER_A);

    // Timer 4
	TimerClockSourceSet(TIMER4_BASE, TIMER_CLOCK_PIOSC);
    ROM_TimerConfigure(TIMER4_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER4_BASE, TIMER_A, ROM_SysCtlClockGet()/50);
    ROM_IntEnable(INT_TIMER4A);
    ROM_TimerIntEnable(TIMER4_BASE, TIMER_TIMA_TIMEOUT);
    //ROM_TimerEnable(TIMER4_BASE, TIMER_A);

    // Timer 5
	TimerClockSourceSet(TIMER5_BASE, TIMER_CLOCK_PIOSC);
    ROM_TimerConfigure(TIMER5_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER5_BASE, TIMER_A, ROM_SysCtlClockGet()/2);
    ROM_IntEnable(INT_TIMER5A);
    ROM_TimerIntEnable(TIMER5_BASE, TIMER_TIMA_TIMEOUT);
    //ROM_TimerEnable(TIMER5_BASE, TIMER_A);

}
void cfg_systick(void){
	SysTickPeriodSet(SysCtlClockGet()/2);
	SysTickIntEnable();
	SysTickEnable();
}
