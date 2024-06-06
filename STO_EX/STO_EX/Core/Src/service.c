/*
 * service.c
 *
 *  Created on: Aug 4, 2023
 *      Author: wkania
 */

#include <counter.h>
#include <configuration.h>
#include <gpio.h>
#include <det_cable.h>
#include <stdbool.h>
#include <service.h>
#include <sdcard.h>


static bool service_mode = true;

void ServiceModeOn(bool on_off);

void ServiceProcess()
{
	static bool service_cable_on = false;

	ServiceModeOn(true);

	while(service_mode == 1)
	{
		ServiceModeOn(false);

		if(DetCableService() == true)
		{
			if(startSecondsCounter(SERVICE_ALARM) >= 1)
			{
				HAL_GPIO_TogglePin(ALARM_GPIO_Port, ALARM_Pin);
			    stopSecondsCounter(SERVICE_ALARM);
			}

			if(service_cable_on == false)
			{
				service_cable_on = true;
				ToSdCard(KABEL_SERWIS);
			}
		}
		else if(HAL_GPIO_ReadPin(ALARM_GPIO_Port, ALARM_Pin) == true)
				HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_RESET);
		else if(service_cable_on == true)
		{
			if(startSecondsCounter(SERVICE_TIMER_1) >= 1)
				{
				  service_cable_on = false;
			      stopSecondsCounter(SERVICE_TIMER_1);
				}
		}

		if(startSecondsCounter(SERVICE_LED_1) >= SERVICE_LED_2)
		{
			HAL_GPIO_TogglePin(LED_SERWIS_GPIO_Port, LED_SERWIS_Pin);
			HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
			restartSecondsCounter(SERVICE_LED_1);
		}

	}
}

void ServiceModeOn(bool on_off)
{
	static bool service_sd = false;
	static uint8_t service_timer = 0;

	if(HAL_GPIO_ReadPin(SERWIS_IN_GPIO_Port, SERWIS_IN_Pin) == GPIO_PIN_SET)
	{
		if(startSecondsCounter(SERVICE_TIMER_1) >= 1)
			{
			service_timer++;
			restartSecondsCounter(SERVICE_TIMER_1);
			}
	}
	else if (HAL_GPIO_ReadPin(SERWIS_IN_GPIO_Port, SERWIS_IN_Pin) == GPIO_PIN_RESET &&
			service_timer >= SERVICE_TIMER_2 && service_timer <= SERVICE_TIMER_3)
	{
		service_mode = on_off;
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_SERWIS_GPIO_Port, LED_SERWIS_Pin, GPIO_PIN_RESET);
		stopSecondsCounter(SERVICE_TIMER_1);
		stopSecondsCounter(SERVICE_LED_1);
		service_timer = 0;
		if(service_sd == false)
		{
			ToSdCard(SERWIS_ON);
			service_sd = true;
		}
		else
		{
			ToSdCard(SERWIS_OFF);
			service_sd = false;
		}

	}
	else
	{
		restartSecondsCounter(SERVICE_TIMER_1);
		service_timer = 0;
	}
}
