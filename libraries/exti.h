// header file for exteernal interrupt.
/*for interrupts there is NVIC which present close to the core.It handles the interrupt
>>for external interrupt there is extra unit which is known as EXTI(external interrupt controller) 

>>It has 23 lines and each lines has some registers.
    >> IMR(interrupt mask register) - it has 23 bit associated 1 bit to every line.It enables the interrupt request for corresponding line.
    
    >> PR(Pending Register)- It get set when interrupt is requested. It is also 23 bit and 1 bit for one line .It is reseted by writing 1 to corresponding bit.
    
    >>FTSR , RTSR-both this register are used to set the triggering .

>> There are 16 pins in a port therefore from 23 lines only 16 lines are used for GPIO external interrupt.

>>at a time only one 0th bit from different GPIO can generate interrupt request. It is not possible that pin0 of gpioa and pin0 of gpiob 
 generating interrupt request simultaneously. Different pin can generate  IRQ simultaneously.

>>For multiplexing of pin we use syscfg registers EXTICRx .
*/

#ifndef EXTI_H
#define EXTI_H

#include "stm32f446xx.h" 
#include "nsc_gpio.h"

typedef enum{
	EXTI_Result_OK ,
	EXTI_Result_error,
}EXTI_Result_t ;  


typedef enum{
	EXTI_trigger_rising,
	EXTI_trigger_falling,
	EXTI_trigger_rising_falling,
 }EXTI_trigger_t; 


// this function will attach interrupt to the  gpio pin. If everything will be ok then EXTI_Result_OK will be returned by the function.

EXTI_Result_t EXTI_Attach_GPIO(GPIO_TypeDef* GPIOx , uint16_t Pin , EXTI_trigger_t trigger  ); 



EXTI_Result_t EXTI_Detach_GPIO( uint16_t Pin );


// it will deinitialise the gpio from external interrupt.
void EXTI_Deinit(void);
