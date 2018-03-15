// library for stm32 gpio
// 5 Feb 2018
// author : Navendu Shekhar Choudhary


#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include "stm32f446xx.h"

// macros for GPIO pins

#ifndef GPIO_PIN_0
#define GPIO_PIN_0		((uint16_t)0x0001)
#define GPIO_PIN_1		((uint16_t)0x0002)
#define GPIO_PIN_2		((uint16_t)0x0004)
#define GPIO_PIN_3		((uint16_t)0x0008)
#define GPIO_PIN_4		((uint16_t)0x0010)
#define GPIO_PIN_5		((uint16_t)0x0020)
#define GPIO_PIN_6		((uint16_t)0x0040)
#define GPIO_PIN_7		((uint16_t)0x0080)
#define GPIO_PIN_8		((uint16_t)0x0100)
#define GPIO_PIN_9		((uint16_t)0x0200)
#define GPIO_PIN_10		((uint16_t)0x0400)
#define GPIO_PIN_11		((uint16_t)0x0800)
#define GPIO_PIN_12		((uint16_t)0x1000)
#define GPIO_PIN_13		((uint16_t)0x2000)
#define GPIO_PIN_14		((uint16_t)0x4000)
#define GPIO_PIN_15		((uint16_t)0x8000)
#define GPIO_PIN_ALL	((uint16_t)0xFFFF)
#endif

// gpio typedefs

typedef enum {
  
  GPIO_mode_IN  = 0x00,   // GPIO PIN AS INPUT
  GPIO_mode_OUT = 0x01,   // GPIO PIN AS OUTPUT
  GPIO_mode_AF  = 0x02,   // GPIO PIN AS ALTERNATE FUNCTION
  GPIO_mode_AN  = 0x03,   // GPIO PIN AS ANALOG

}GPIO_mode_t ;  // gpio typedef for mode setting


typedef enum {

 GPIO_otype_PP = 0x00,    // OUTPUT TYPE PUSH-PULL
 GPIO_otype_OD = 0x01,    // OUTPUT TYPE OPEN DRAIN

}GPIO_otype_t;


typedef enum {
  
  GPIO_pupd_NOPULL   = 0x00,  // FLOATING INPUT
  GPIO_pupd_PULLUP   = 0x01,  // INPUT INTERNAL PULL UP
  GPIO_pupd_PULLDOWN = 0x02,  // INPUT INTERNAL PULL DOWN 

}GPIO_pupd_t;

typedef enum{

	GPIO_speed_LOW     = 0x00,   // GPIO SPEED SELECTION
	GPIO_speed_MEDIUM  = 0x01,
	GPIO_speed_FAST    = 0x02,
	GPIO_speed_HIGH    = 0x03,

}GPIO_speed_t;


    // gpio initialisation functions 

/*
   >> It initialises the gpio pin .
   >> It provides the clock to the gpio port
   >> Pin or Pins can be initialised using the bitwise or
*/
void GPIO_init(GPIO_TypeDef* GPIOx , uint16_t pin , GPIO_mode_t mode , GPIO_otype_t otype , GPIO_pupd_t pupd , GPIO_speed_t speed ) ;

 
// >> it initialise the gpio pin as alternate function 
// >> it also enable the clock
// >> no. of pins can be initialised at a time

void GPIO_init_alt_func(GPIO_TypeDef* GPIOx , uint16_t pin , GPIO_mode_t mode , GPIO_otype_t otype , GPIO_pupd_t pupd , GPIO_speed_t speed , uint8_t alt ) ;


// >> it locks the gpio initialisation

void GPIO_lock(GPIO_TypeDef* GPIOx , uint16_t pin) ;

// returns port no.

uint16_t GPIO_get_port_source(GPIO_TypeDef* GPIOx);


// returns pin no.

uint16_t GPIO_get_pin_source(uint16_t pin) ;

// some more macros 

#define GPIO_set_pin_low(GPIOx , pin)              ((GPIOx)->BSRR  = (uint32_t)((uint32_t)pin << 16))

#define GPIO_set_pin_high(GPIOx , pin)             ((GPIOx)->BSRR  = (uint32_t)pin )



#endif