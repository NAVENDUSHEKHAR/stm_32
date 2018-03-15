#include "stm32_GPIO.h"

// private functions

void init(GPIO_TypeDef* GPIOx , uint16_t pin , GPIO_mode_t mode , GPIO_otype_t otype , GPIO_pupd_t pupd , GPIO_speed_t speed);

void GPIO_enable_clock(GPIO_TypeDef* GPIOx) ;

void GPIO_init(GPIO_TypeDef* GPIOx , uint16_t pin , GPIO_mode_t mode , GPIO_otype_t otype , GPIO_pupd_t pupd , GPIO_speed_t speed)
{
	if (pin==0x00)
	{
		return ;
	}

  GPIO_enable_clock(GPIOx)	;

  init( GPIOx ,  pin ,  mode ,  otype , pupd ,  speed);

}

void GPIO_init_alt_func(GPIO_TypeDef* GPIOx , uint16_t pin , GPIO_mode_t mode , GPIO_otype_t otype , GPIO_pupd_t pupd , GPIO_speed_t speed , uint8_t alt)
{
	if (pin==0x00)
	{
		return ;
	}

	for (int i = 0; i < 0x10; i++)
	{
		if((pin & (1<< i))==0)
		{
			continue ;
		}

     GPIOx->AFR[i>>0x03] = (GPIOx->AFR[i>>0x03] & ~(0x0f << (4*(i & 0x07)))) | (alt << (4*(i & 0x07))) ;

	}
 
 init( GPIOx ,  pin ,  mode ,  otype ,  pupd ,  speed);

}


void GPIO_lock(GPIO_TypeDef* GPIOx , uint16_t pin)
{
	uint32_t l = 0x00010000 | pin ;

//sequence to lock the pin
   
    GPIOx->LCKR = l;
    GPIOx->LCKR = pin;
    GPIOx->LCKR = l;

  (void)GPIOx->LCKR;
  (void)GPIOx->LCKR;  // READ TWICE

}

uint16_t GPIO_get_port_source(GPIO_TypeDef* GPIOx)
{
	return ((uint32_t)(GPIOx)- (GPIOA_BASE))/((GPIOB_BASE) - (GPIOA_BASE)) ;

}

uint16_t GPIO_get_pin_source(uint16_t pin)
{
	uint16_t number=0;

	while(pin > 1)
	{
		number++ ;
		pin >>=1;

	}
return number;	
}

void GPIO_enable_clock(GPIO_TypeDef* GPIOx)
{
	RCC->AHB1ENR |= (1<<(GPIO_get_port_source(GPIOx)));
}

void init(GPIO_TypeDef* GPIOx , uint16_t pin , GPIO_mode_t mode , GPIO_otype_t otype , GPIO_pupd_t pupd , GPIO_speed_t speed)
{
	if (pin==0x00)
	{
		return ;
	}

	for (int i = 0; i < 0x10; ++i)
	{
		if (((pin & (1<<i))==0))
		{
			continue;
		}

	  GPIOx->MODER = ( GPIOx->MODER & ~((uint32_t)(0x03<<(2*i))) ) | ((uint32_t)(mode<<(2*i))) ; 	
	  GPIOx->PUPDR = ( GPIOx->PUPDR & ~((uint32_t)(0x03<<(2*i))) ) | ((uint32_t)(pupd<<(2*i))) ; 

	  if(mode==GPIO_mode_OUT)
	  {
	  	GPIOx->OTYPER = ( GPIOx->OTYPER & ~((uint32_t)(0x01<<(i))) ) | ((uint32_t)(otype<<(i)));

	  	GPIOx->OSPEEDR = ( GPIOx->OSPEEDR & ~((uint32_t)(0x03<<(2*i))) ) | ((uint32_t)(speed<<(2*i)));
	  }
	}
}