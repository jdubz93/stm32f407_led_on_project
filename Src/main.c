/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Josh Williams
 * @brief          : Blinky application for stm32f407G MCU
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

//Testing of bits (&)
//Setting of bits (|)
//Clearing of bits (~ and &)
//Toggling of bits (^)

void delayFunc(void);
void ledOff(uint32_t* pGPIO_D_OutData, uint32_t* pGPIO_D_ModeReg);
void ledOn(uint32_t* pGPIO_D_ModeReg, uint32_t* pGPIO_D_OutData);

int main(void)
{
	printf("Enable led on PD12");
	uint32_t *pClockCtrlReg			= (uint32_t*)0x40023830;
	uint32_t *pGpiodModeReg 		= (uint32_t*)0x40020C00;
	uint32_t *pGpiodOutputDataReg	= (uint32_t*)0x40020C14;

	// enable the clock for GPIOD peripheral in the AHB1ENR
	*pClockCtrlReg |= (1 << 3);

	ledOn(pGpiodModeReg, pGpiodOutputDataReg);
	for(int i = 0; i < 10; i++) {
		if (i % 2) {
			ledOn(pGpiodModeReg, pGpiodOutputDataReg);
			delayFunc();
		} else {
			ledOff(pGpiodModeReg, pGpiodOutputDataReg);
			delayFunc();
		}
	}

	ledOff(pGpiodModeReg, pGpiodOutputDataReg);
    /* Loop forever */
	for(;;);
}

void delayFunc(void) {
	for(uint64_t i = 0; i < 1000000; i++) {
		// do nothing
	}
}

void ledOff(uint32_t* pGPIO_D_OutData, uint32_t* pGPIO_D_ModeReg) {
	// turn off led
	*pGPIO_D_OutData	&= 0xFFFFFFFF;
	*pGPIO_D_ModeReg	&= 0x0000;
}

void ledOn(uint32_t* pGPIO_D_ModeReg, uint32_t* pGPIO_D_OutData) {
	// clear the bits using mask
	*pGPIO_D_ModeReg	&= ~(3 << 10);
	*pGPIO_D_ModeReg	|= (1 << 10);
	// set the 5th pin
	*pGPIO_D_OutData	|= (1 << 5);
}
