#include "main.h"
#include "PIDPosistion.h"
/*
 * System Function
 */
/*
 * User Function
 */
//*****************************************************************************
//
// The System Variables
//
//*****************************************************************************
//int32_t	pol 	= 0;
//int32_t	por 	= 0;
int32_t	pol 	= 13682;
int32_t	por 	= 13682;
int32_t	count 	= 10;
int dk0 = 0;
int dk1 = 0;
//*****************************************************************************
//
// Main Function
//
//*****************************************************************************
//48clk/r
int mycount=0;
int mode=1;
void main(void) {
	init();
	//MotorController(1000, 1000);
	while (1) {
//		MotorController(4000, 4000);
//		SysCtlDelay(SysCtlClockGet()/2);
//		MotorController(-4000, -4000);
//		SysCtlDelay(SysCtlClockGet()/2);
//
	//	UARTprintf("\r%8d%8d",  QEIPositionGet(QEI0_BASE), QEIPositionGet(QEI1_BASE));
		if(++mycount < 1000)
		{
		    //mode=1;
	      // pos = 0;
//	       PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 0);
//	         PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 0);
		}
		else if(mycount < 2000)
		{
		 //   mode=0;
		   // pos = 13682;
		  //  PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, 4990);
//		    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 4990);
//		      PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 4990);
		}
		else
		{
		    mycount = 0;
		}


		SysCtlDelay(SysCtlClockGet()/1000);
	}
}
//*****************************************************************************
//
// The Interrupt Vector
//
//*****************************************************************************
// Vector Timer 0
void Timer0IntHandler(void){
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    PIDPos(pol, por);
}
// Vector Timer 1
void Timer1IntHandler(void){
    ROM_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

}
// Vector Timer 2
void Timer2IntHandler(void){
	ROM_TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

}
void Timer3IntHandler(void){
    ROM_TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

}
void Timer4IntHandler(void){
    ROM_TimerIntClear(TIMER4_BASE, TIMER_TIMA_TIMEOUT);

}
void Timer5IntHandler(void){
    ROM_TimerIntClear(TIMER5_BASE, TIMER_TIMA_TIMEOUT);

}
void SysTickIntHandler(void){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
}
// Vector UART0
void UART0IntHandler(void){
	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3));
	UARTIntClear(UART0_BASE, UART_INT_RX);
}
// Vector PORT F
void PortFIntHandler(void){
	uint32_t PortFmask = GPIOIntStatus(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
	if(PortFmask & GPIO_PIN_0){
		/////////////////////////////////////////////////////////////////////////////////////////////
		UARTprintf("\nButton 2 !");
		pol += 200 ;
		por += 200 ;
		//TimerEnable(TIMER0_BASE, TIMER_A);
		/////////////////////////////////////////////////////////////////////////////////////////////
		SysCtlDelay(SysCtlClockGet()/100);
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
	}
	if(PortFmask & GPIO_PIN_4){
		pol -= 200 ;
		por -= 200 ;
		/////////////////////////////////////////////////////////////////////////////////////////////
		UARTprintf("\nButton 1 !");
		/////////////////////////////////////////////////////////////////////////////////////////////
		SysCtlDelay(SysCtlClockGet()/100);
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
	}
}
// Vector PORT B
void PortDIntHandler(void){
	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
	uint32_t PortDmask = GPIOIntStatus(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	if(PortDmask & GPIO_PIN_0 && dk0 == 0){
		/////////////////////////////////////////////////////////////////////////////////////////////
		UARTprintf("\nD0 !");
		pol = -500 ;
		dk0 = 1;
		QEIPositionSet(QEI1_BASE, 0);
		//TimerEnable(TIMER0_BASE, TIMER_A);
		/////////////////////////////////////////////////////////////////////////////////////////////
		//SysCtlDelay(SysCtlClockGet()/0100);
		GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_0);
	}
	if(PortDmask & GPIO_PIN_1 && dk1 == 0){

		/////////////////////////////////////////////////////////////////////////////////////////////
		UARTprintf("\nD1 !");
		QEIPositionSet(QEI0_BASE, 0);
		por = -500 ;
		dk1 = 1;
		/////////////////////////////////////////////////////////////////////////////////////////////
		//SysCtlDelay(SysCtlClockGet()/1000);
		GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_1);
	}
}

