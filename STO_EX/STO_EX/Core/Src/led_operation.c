/*
 * led_operation.c
 *
 *  Created on: Jul 27, 2023
 *      Author: wkania
 */

#include "gpio.h"
#include "stdbool.h"



void ConfigurationModeIsOn(bool led)
{
	if(led == true)
	{
		HAL_GPIO_WritePin(SWITCH_LED_GPIO_Port, SWITCH_LED_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(CHOICE_LED_GPIO_Port, CHOICE_LED_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(SWITCH_LED_GPIO_Port, SWITCH_LED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(CHOICE_LED_GPIO_Port, CHOICE_LED_Pin, GPIO_PIN_RESET);
	}
}
