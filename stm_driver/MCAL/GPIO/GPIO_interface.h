#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H


#include <stdint.h>
#include "LIB/STM_CONFIG.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "GPIO_private.h"

void GPIO_void_PIN_MODE (GPIO_ID* GPIO,u8 PIN,GPIO_STATE_ID GPIO_STATE);

void GPIO_void_PIN_WRITE(GPIO_ID* GPIO,u8 PIN , GPIO_VALUE_ID GPIO_VALUE);

void GPIO_void_PIN_SETSPEED(GPIO_ID* GPIO,u8 PIN ,GPIO_SPEED_ID GPIO_SPEED);

u8 GPIO_u8_PIN_READ(GPIO_ID* GPIO,u8 PIN);

void GPIO_void_AF_MODE(GPIO_ID* GPIO,u8 PIN,GPIO_AF_TYPE_ID GPIO_AF_TYPE);


#endif
