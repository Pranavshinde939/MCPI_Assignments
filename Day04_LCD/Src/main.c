/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "lcd.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	int c = 150;
	//char str[6]="PRANAV          ";
	SystemInit();
	LcdInit();
	LcdPuts(LCD_LINE1, "PRANAV");
	for(int i = 0; i<=6; i++)
	{
		LcdWrite(LCD_CMD, 0x1C);
		DelayMs(c);
	}
	/*while(1)
	{
		LcdPuts(LCD_LINE1, "PRANAV");
		for(int i = 0; i<=6; i++)
		{
			LcdWrite(LCD_CMD, LCD_LINE_SHIFT);
			DelayMs(c);
		}

		uint32_t cusel = 0x80;


		for(cusel = 0x80; cusel<= 0x96; cusel++)
		{
			LcdPuts(cusel-1, " ");
			LcdPuts(cusel, "PRANAV");	DelayMs(c);
		}
	}*/
	return 0;
}






