/*
 * extinguisher.c
 *
 *  Created on: Aug 1, 2023
 *      Author: wkania
 */


#include <extinguisher.h>
#include <configuration.h>
#include <det_cable.h>
#include "stdbool.h"
#include <counter.h>
#include "gpio.h"
#include <sdcard.h>
#include "adc.h"
#include <breakup.h>

static uint8_t max_delay_count = 0;
static uint8_t delay = 0;


static void TimerToTrigExt(uint8_t time);
void ExtinguisherTriggered(uint8_t how_many_zone, uint8_t wchich_zone,uint8_t ext_count);
static uint8_t Delay();

Extinguisher extinguisher[EXTINGUISHER_COUNT_2] =
		{
				[0] = { .is_connected = true },
				[1] = { .is_connected = true },
				[2] = { .is_connected = true },
				[3] = { .is_connected = true }
		};


void GetParameter(Configuration *config)
{
	for(uint8_t i; i < config->amount_extinguisher; i++)
	{
		extinguisher[i].enabled = true;
	}
}

void ExtinguisherProcess(Configuration *config, bool wires_is_ok)
{
	static bool triggered_on;

	BreakUp *breakup_ext;
	breakup_ext = &breakup;

	for(uint8_t i = 0; i < 4; i++)
	{
		Det_Cable *cable;
		cable = &det_cable[i];

		if(cable->triggered == true && cable->is_triggered == false && wires_is_ok == true && breakup_ext->triggered == false)
		{
			HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_SET);
			TimerToTrigExt(config->time_cable_trigger);
			switch(config->amount_zone)
					{
					case 1:
							if(cable->enabled == true)
							{
								ExtinguisherTriggered(config->amount_zone, 1, 4);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_1);
							}
							break;
					case 2:
						if(config->amount_det_cables == 2)
						{
							if(i == 3)
							{
							    ExtinguisherTriggered(config->amount_zone, 1, config->amount_extinguisher);
							    ToSdCard(WYZWOLENIE_KABEL_STREFA_1);
							}
							if(i == 1)
							{
								ExtinguisherTriggered(config->amount_zone, 2, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_2);
							}
						}
						else if(config->amount_det_cables == 3)
						{
							if(i == 3 || i == 1)
							{
								ExtinguisherTriggered(config->amount_zone, 1, config->amount_extinguisher);
							    ToSdCard(WYZWOLENIE_KABEL_STREFA_1);
							}
							if(i == 2)
							{
								ExtinguisherTriggered(config->amount_zone, 2, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_2);
							}
						}
						else if(config->amount_det_cables == 4)
						{
							if(i == 3 || i == 1)
							{
								ExtinguisherTriggered(config->amount_zone, 1, config->amount_extinguisher);
							    ToSdCard(WYZWOLENIE_KABEL_STREFA_1);
							}
							if(i == 2 || i == 0)
							{
								ExtinguisherTriggered(config->amount_zone, 2, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_2);
							}
						}
						break;
					case 3:
						if(config->amount_det_cables == 3)
						{
							if(i == 3)
							{
							    ExtinguisherTriggered(config->amount_zone, 1, config->amount_extinguisher);
							    ToSdCard(WYZWOLENIE_KABEL_STREFA_1);
							}
							if(i == 1)
							{
								ExtinguisherTriggered(config->amount_zone, 2, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_2);
							}
							if(i == 2)
								ExtinguisherTriggered(config->amount_zone, 3, config->amount_extinguisher);
						}
						else if(config->amount_det_cables == 4)
						{
							if(i == 3 || i == 1)
							{
								ExtinguisherTriggered(config->amount_zone, 1, config->amount_extinguisher);
							    ToSdCard(WYZWOLENIE_KABEL_STREFA_1);
							}

							if(i == 2)
							{
								ExtinguisherTriggered(config->amount_zone, 2, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_2);
							}
							if(i == 0)
							{
								ExtinguisherTriggered(config->amount_zone, 3, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_3);
							}
						}
						break;
					case 4:
						if(config->amount_det_cables == 4)
						{
							if(i == 3)
							{
								ExtinguisherTriggered(config->amount_zone, 1, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_1);
							}
							if(i == 1)
							{
								ExtinguisherTriggered(config->amount_zone, 2, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_2);
							}
							if(i == 2)
							{
								ExtinguisherTriggered(config->amount_zone, 3, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_3);
							}
							if(i == 0)
							{
								ExtinguisherTriggered(config->amount_zone, 4, config->amount_extinguisher);
								ToSdCard(WYZWOLENIE_KABEL_STREFA_4);
							}
						}
						break;
					}
			cable->is_triggered = true;
			triggered_on = true;

		}
		if(triggered_on == true || breakup_ext->triggered == true)
		{
			if(startSecondsCounter(TRIGGERED_EXT_OFF_TIMER_1) >= TRIGGERED_EXT_OFF_TIMER_2)
			{
				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GAS1_GPIO_Port, GAS1_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GAS2_GPIO_Port, GAS2_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GAS3_GPIO_Port, GAS3_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GAS4_GPIO_Port, GAS4_Pin, GPIO_PIN_RESET);
				triggered_on = false;
				stopSecondsCounter(TRIGGERED_EXT_OFF_TIMER_1);
			}
		}
	}
}

void ExtinguisherTriggered(uint8_t how_many_zone, uint8_t wchich_zone, uint8_t ext_count)
{
	for(uint8_t i = 1; i <= EXTINGUISHER_COUNT_2; i++)
		{
		    Extinguisher *ext;
			ext = &extinguisher[i-1];
			switch(how_many_zone)
			{
			case 1:
				if(ext->enabled == true)
				{
					WchichExtinguisher(i);
					ext->is_triggered = true;
				}
				break;
			case 2:
				if(wchich_zone == 1)
				{
					if(ext_count == 2)
					    WchichExtinguisher(1);
					else if(ext_count >= 3)
					{
						WchichExtinguisher(1);
					    WchichExtinguisher(2);
					}
				}
				if(wchich_zone == 2)
				{
					if(ext_count == 2)
					    WchichExtinguisher(2);
					else if(ext_count == 3)
						WchichExtinguisher(3);
					else if(ext_count == 4)
					{
						WchichExtinguisher(3);
					    WchichExtinguisher(4);
					}
				}
				break;
			case 3:
				if(wchich_zone == 1)
				{
					if(ext_count == 3)
					    WchichExtinguisher(1);

					else if(ext_count == 4)
					{
						WchichExtinguisher(1);
					    WchichExtinguisher(2);
					}
				}
				if(wchich_zone == 2)
					WchichExtinguisher(2);
				if(wchich_zone == 3)
					WchichExtinguisher(3);
				if(wchich_zone == 4)
					WchichExtinguisher(4);
			    break;
			case 4:
				if(wchich_zone == 1)
				WchichExtinguisher(1);
				if(wchich_zone == 2)
				WchichExtinguisher(2);
				if(wchich_zone == 3)
				WchichExtinguisher(3);
				if(wchich_zone == 4)
				WchichExtinguisher(4);
			}
		}
}

void WchichExtinguisher(uint8_t number)
{
	switch(number)
	{
	case 1:
		HAL_GPIO_WritePin(GAS1_GPIO_Port, GAS1_Pin, GPIO_PIN_SET);
		//HAL_GPIO_WritePin(GAS4_GPIO_Port, GAS4_Pin, GPIO_PIN_SET);
		extinguisher[0].is_triggered = true;
		break;
	case 2:
		HAL_GPIO_WritePin(GAS2_GPIO_Port, GAS2_Pin, GPIO_PIN_SET);
		extinguisher[1].is_triggered = true;
		break;
	case 3:
		HAL_GPIO_WritePin(GAS3_GPIO_Port, GAS3_Pin, GPIO_PIN_SET);
		extinguisher[2].is_triggered = true;
		break;
	case 4:
		HAL_GPIO_WritePin(GAS4_GPIO_Port, GAS4_Pin, GPIO_PIN_SET);
		//HAL_GPIO_WritePin(GAS1_GPIO_Port, GAS1_Pin, GPIO_PIN_SET);
		extinguisher[3].is_triggered = true;
		break;
	}
}

static void TimerToTrigExt(uint8_t time)
{
	static uint8_t ext_timer = 0;
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	stopSecondsCounter(TRIGGERED_EXT_OFF_TIMER_1);

	while(ext_timer <= (time + Delay()))
	{
		if(ext_timer < (time/2) + Delay())
		{
			if(startMillisCounter(TIMER_EXTINGUISHER_2) >= EXT_LED_TIMER_1)
			{
				HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
				HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
				restartMillisCounter(TIMER_EXTINGUISHER_2);
			}
		}
		else if(ext_timer >= ((time/2)+ Delay()) && ext_timer < ((time - 3) + Delay()))
		{
			if(startMillisCounter(TIMER_EXTINGUISHER_2) >= EXT_LED_TIMER_2)
			{
				HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
				HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
				restartMillisCounter(TIMER_EXTINGUISHER_2);
			}
		}
		else if(ext_timer >= ((time - 3) + Delay()))
		{
			if(startMillisCounter(TIMER_EXTINGUISHER_2) >= EXT_LED_TIMER_3)
			{
				HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
				HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
				restartMillisCounter(TIMER_EXTINGUISHER_2);
			}
		}
		if(startSecondsCounter(TIMER_EXTINGUISHER_1) >= TIMER_EXTINGUISHER_SEC)
		{
			ext_timer++;
			restartSecondsCounter(TIMER_EXTINGUISHER_1);
		}
	}
	stopMillisCounter(TIMER_EXTINGUISHER_2);
	stopSecondsCounter(TIMER_EXTINGUISHER_1);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	delay = 0;
	max_delay_count = 0;

	ext_timer = 0;

}

static uint8_t Delay()
{
	static uint16_t delay_time_adc = 0;

	delay_time_adc = value[4];

	if(delay_time_adc >= DELAY_TRIGGER_ON && max_delay_count < DELAY_MAX_COUNT)
	{
		delay = delay + config.time_delay_trigger;
		max_delay_count++;
		ToSdCard(OPOZNIENIE_ZADZIALANIA);
		HAL_Delay(300);
	}
	return delay;
}
