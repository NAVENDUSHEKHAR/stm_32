// c file for exti

#include"exti.h"

EXTI_Result_t EXTI_Attach_GPIO(GPIO_TypeDef* GPIOx , uint16_t Pin , EXTI_trigger_t trigger  )
{  
    IRQn_Type irqchannel;  // IRQn_Type is a enum for exceptions
    gpio_pupd_t  pupd;
    uint8_t pinsource,portsource;

	// check theer is more than one gpio initialise at a time
	if(!(Pin&(Pin-1)))
	{
		for (uint8_t i = 0; i < 0x10; ++i)
		{
		    if((Pin)&(1<<i))
		    {
		    	if(EXTI_Attach_GPIO(G GPIOx , 1<<i ,  trigger  )!=EXTI_Result_OK)
		    	{
		    		return EXTI_Result_error;
		    	}
		    }
		}

	return	EXTI_Result_OK;  // if every pin get passed
	
	}

  if((EXTI->IMR)&(Pin))                    // exti is a pointer to exti_TypeDef
  	{
  		return EXTI_Result_error;
  	}

  switch(Pin){
   case Pin_0: 
        irqchannel=EXTI0_IRQn;
        break;

   case Pin_1: 
        irqchannel=EXTI1_IRQn;
        break;	

   case Pin_2: 
        irqchannel=EXTI2_IRQn;
        break;

   case Pin_3: 
        irqchannel=EXTI3_IRQn;
        break;	

   case Pin_4: 
        irqchannel=EXTI4_IRQn;
        break;

   case Pin_5:
   case Pin_6:
   case Pin_7:
   case Pin_8:
   case Pin_9:
   		irqchannel=EXTI9_5_IRQn;
   		break;

   case Pin_10:
   case Pin_11:
   case Pin_12:
   case Pin_13:
   case Pin_14:
   case Pin_15:
   		irqchannel=EXTI15_10_IRQn;
   		break;

   default:	

    	return EXTI_Result_error;
        
        					
     } 

if (trigger==EXTI_trigger_rising)         // selection of pull up and pull down register according to the trigger 
{
	pupd = gpio_pd;
}
else if (trigger==EXTI_trigger_falling)
{
	pupd = gpio_pu ;
}

else pupd = gpio_no_pupd;

nsc_GPIO_init(GPIOX , pin , gpio_mode_in , gpio_push_pull , gpio_speed_low , pupd);  // gpio initialisation

// providing clock to syscfg
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;  //  RCC_APB2ENR_SYSCFGEN is prdefined macro defined in  stm32f4xx header file. as syscfg is present on 
                                        // apb2 bus so we are enabling the clock on apb2 bus.

pisource = get_pin(GPIOx);

portsource= get_port(GPIOx);


//              [divided by 4]                                                     [we need only lower bits]           
SYSCFG->EXTICR[pinsource >> 2 ] = (SYSCFG->EXTICR[pinsource >> 2 ] & ~(0x000f<<(0x04*(pinsource & 0x03)))) | ((uint16_t)(portsource)<<(0x04*(pinsource & 0x03)));

    // reset the IMR 

    EXTI->IMR &= ~Pin;
	
	/* Select interrupt mode */
	EXTI->IMR |= Pin;
	
	/* Clear first */
	EXTI->FTSR &= ~Pin;
	EXTI->RTSR &= ~Pin;

if (trigger==EXTI_trigger_rising)         // selection of pull up and pull down register according to the trigger 
	{
		EXTI->FTSR |= Pin;
	}
else if (trigger==EXTI_trigger_falling)
	{
		EXTI->RTSR |= Pin ;
	}

	else 
		{
			EXTI->FTSR |= Pin;
			EXTI->RTSR |= Pin
		}

__NVIC_EnableIRQ(irqchannel);

return EXTI_Result_OK;

} 