
#include "nsc_exti.h"


EXTI_result_t Attach_exti(GPIO_TypeDef* GPIOx , uint16_t pin , EXTI_trigger_t edge)
{
  GPIO_pupd_t pupd;  //enum variable for pull register
  uint8_t port_source , pin_source ; 
  IRQn_Type irq;  // enum is present in controller specefic header file , this enum contains all the interrupts.

  if (pin && (pin&(pin-1)))
  {
  	
  }


}