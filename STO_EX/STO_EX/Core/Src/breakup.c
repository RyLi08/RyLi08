/*
 * breakup.c
 *
 *  Created on: Aug 8, 2023
 *      Author: wkania
 */
#include "adc.h"
#include <stdbool.h>

#include <breakup.h>
#include <counter.h>
#include <sdcard.h>
#include <extinguisher.h>
#include <gpio.h>
#include <configuration.h>

BreakUp breakup;
bool is_fault = false;

static void CheckSystem();

void BreakupProcess()
{
	breakup.value = value[5];

	if(breakup.value <= BREAKUP_TRIGGER && breakup.triggered == false)
	{
		if(startMillisCounter(BREAKUP_TIMER_TRIG_1) >= BREAKUP_TIMER_TRIG_2)
		{
			ToSdCard(MANUALNE_WYZWOLENIE);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_SET);
			if(startSecondsCounter(BREAKUP_TIMER_TRIG_CONFIG_1) >= config.time_breakup_trigger)
			{
				for(uint8_t i = 1; i <= EXTINGUISHER_COUNT_2; i++)
				{
					WchichExtinguisher(i);
				}
				stopMillisCounter(BREAKUP_TIMER_TRIG_1);
				stopSecondsCounter(BREAKUP_TIMER_TRIG_CONFIG_1);
				breakup.triggered = true;
			}
		}
	}
	else
		restartMillisCounter(BREAKUP_TIMER_TRIG_1);

	CheckSystem();

}


static void CheckSystem()
{
	static bool check_on;

	if(breakup.value >= BREAKUP_CHECK && breakup.triggered == false && is_fault == false)
	{
		if(startMillisCounter(BREAKUP_TIMER_CHECK_1) >= BREAKUP_TIMER_CHECK_2)
		{
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_SET);
			check_on = true;
		}
	}
	else if(check_on == true)
	{
		stopSecondsCounter(BREAKUP_TIMER_CHECK_1);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_RESET);
		ToSdCard(SPRAWDZENIE_SYSTEMU);
		check_on = false;
	}
	else
		restartMillisCounter(BREAKUP_TIMER_CHECK_1);
}


void CheckFault(bool fault)
{
	is_fault = fault;
}
