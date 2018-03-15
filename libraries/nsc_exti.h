#ifndef
#define NSC_EXTI_H

//it is an header file for external interrupt. For external interrupt a rising or falling edge is detected on gpio pin
//there are 23 channels of exti from which 16 are for GPIO.
//for 16 external interrupt ther are 7 handlers
//for 0 to 4 there are seperate handler and  5 to 9 share same handler. 10 to 15 also share same handler.
//same pin no. cannot initialised for different gpio's for external interrupt.
// eg- pin 0 cannot initialised for GPIOA as well as GPIOB simultaneously.
//SYSCFG_EXTICRx register is used for selecting the port for a specefic pin .

// macros

#include "stm32f446.h"
#include "stm32_GPIO.h"

typeDef enum 
{
  EXTI_result_ok = 0x00 , //this enum will be used  to know that the exti is connected to the line properly or not.
  EXTI_result_error ,	
}EXTI_result_t;

typeDef enum
{
 
  EXTI_trigger_rising = 0x00 ,  // this enum will be used to set the edge triggering
  EXTI_trigger_falling ,
  EXTI_trigger_rising_falling ,

}EXTI_trigger_t;

 // functions


// this function is used to attach the external interrupt to the gpio 
// we can attach only one gpio for a specefic pin
// this function will return  EXTI_result_ok if everything gets correct.
// this function also enables clock for the  gpio peripheral.

 EXTI_result_t Attach_exti( GPIO_TypeDef* GPIOx , uint16_t pin , EXTI_trigger_t edge) ;

//this function will detach the exti from the gpio line
// if everthing gets correct , EXTI_result_ok  will be returned by the function

 EXTI_result_t Detach_exti(uint16_t pin);

 // this function will detach all gpio pins from 0-15 from exti line

 void Deinit_exti(uint16_t pin);

 // it will enable software interrupt
 // we can also interrupt the exti from software  by writing one to the specefic bit of SWIER register.

 #define  EXTI_software_interrupt(pin)        ( EXTI->SWIER |= (pin) )




#endif