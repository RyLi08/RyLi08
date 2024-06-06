/*
 * fault.c
 *
 *  Created on: Aug 2, 2023
 *      Author: wkania
 */

#include "stdbool.h"
#include "extinguisher.h"
#include "gpio.h"
#include "counter.h"
#include <sdcard.h>
#include <det_cable.h>
#include "adc.h"
#include <breakup.h>

static bool sd_fault_ext_con;
static bool sd_fault_det_cable_con;
static bool sd_fault_delay_but_con;

static bool CheckExtConnected();
static bool CheckDetCableConnected();
bool CheckDelayButConnected();
static void CheckBattery();

bool CheckWires()
{
	static bool led_off = false;

	if(CheckExtConnected() == false || CheckDetCableConnected() == false || CheckDelayButConnected() == false)
	{
		if(startSecondsCounter(CHECK_WIRES_TIMER_1) >= CHECK_WIRES_TIMER_2)
		{
			HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			HAL_GPIO_TogglePin(ALARM_GPIO_Port, ALARM_Pin);
			restartSecondsCounter(CHECK_WIRES_TIMER_1);
			led_off = true;
			CheckFault(true);
		}
		return false;
	}
	else
	{
		CheckBattery();
		if(led_off == true)
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_RESET);
			stopSecondsCounter(CHECK_WIRES_TIMER_1);
			led_off = false;
			sd_fault_ext_con = false;
			sd_fault_det_cable_con = false;
			sd_fault_delay_but_con = false;
			CheckFault(false);
		}
		return true;
	}

}

static bool CheckExtConnected()
{
	for(uint8_t i = 0; i < EXTINGUISHER_COUNT_2; i++)
	{
		Extinguisher *check_ext;
		check_ext = &extinguisher[i];

		if(check_ext->enabled == true && check_ext->is_triggered == false)
		{
			switch(i)
			{
			case 0:
				if(HAL_GPIO_ReadPin(GAS1_OK_GPIO_Port, GAS1_OK_Pin) == GPIO_PIN_SET)
				{
					if(startMillisCounter(FAULT_EXT_CON_1) >= FAULT_EXT_CON_2)
					{
						check_ext->is_connected = false;
						if(sd_fault_ext_con == false)
						{
						ToSdCard(BRAK_GAS1);
						sd_fault_ext_con = true;
						}
						stopMillisCounter(FAULT_EXT_CON_1);
					}
					return false;
				}
				break;

			case 1:
				if(HAL_GPIO_ReadPin(GAS2_OK_GPIO_Port, GAS2_OK_Pin) == GPIO_PIN_SET)
				{
					if(startMillisCounter(FAULT_EXT_CON_1) >= FAULT_EXT_CON_2)
					{
						check_ext->is_connected = false;
						if(sd_fault_ext_con == false)
						{
						ToSdCard(BRAK_GAS2);
						sd_fault_ext_con = true;
						}
						stopMillisCounter(FAULT_EXT_CON_1);
					}
					return false;
				}
				break;

			case 2:
				if(HAL_GPIO_ReadPin(GAS3_OK_GPIO_Port, GAS3_OK_Pin) == GPIO_PIN_SET)
				{
					if(startMillisCounter(FAULT_EXT_CON_1) >= FAULT_EXT_CON_2)
					{
						check_ext->is_connected = false;
						if(sd_fault_ext_con == false)
						{
						ToSdCard(BRAK_GAS3);
						sd_fault_ext_con = true;
						}
						stopMillisCounter(FAULT_EXT_CON_1);
					}
					return false;
				}
				break;

			case 3:
				if(HAL_GPIO_ReadPin(GAS4_OK_GPIO_Port, GAS4_OK_Pin) == GPIO_PIN_SET)
				{
					if(startMillisCounter(FAULT_EXT_CON_1) >= FAULT_EXT_CON_2)
					{
						check_ext->is_connected = false;
						if(sd_fault_ext_con == false)
						{
						ToSdCard(BRAK_GAS4);
						sd_fault_ext_con = true;
						}
						stopMillisCounter(FAULT_EXT_CON_1);
					}
					return false;
				}
				break;
			}
			check_ext->is_connected = true;
		}

	}
	restartMillisCounter(FAULT_EXT_CON_1);
	return true;

}

static bool CheckDetCableConnected()
{
	for(uint8_t i = 0; i < DET_CABLE_COUNT; i++)
	{
		Det_Cable *cable_f;
		cable_f = &det_cable[i];

		if(cable_f->enabled == true && cable_f->is_triggered == false)
		{
			switch(i)
			{
			case 3:
				if(cable_f->adc_value <= DET_CABLE_WRONG_CON)
				{
					if(startMillisCounter(FAULT_DET_CABLE_CON_1) >= FAULT_DET_CABLE_CON_2)
					{
						cable_f->wrong_connection = true;
						if(sd_fault_det_cable_con == false)
						{
						ToSdCard(BRAK_KABLA_DET1);
						sd_fault_det_cable_con = true;
						}
						stopMillisCounter(FAULT_DET_CABLE_CON_1);
					}
					return false;
				}
				break;
			case 1:
				if(cable_f->adc_value <= DET_CABLE_WRONG_CON)
				{
					if(startMillisCounter(FAULT_DET_CABLE_CON_1) >= FAULT_DET_CABLE_CON_2)
					{
						cable_f->wrong_connection = true;
						if(sd_fault_det_cable_con == false)
						{
						ToSdCard(BRAK_KABLA_DET2);
						sd_fault_det_cable_con = true;
						}
						stopMillisCounter(FAULT_DET_CABLE_CON_1);
					}
					return false;
				}
				break;
			case 2:
				if(cable_f->adc_value <= DET_CABLE_WRONG_CON)
				{
					if(startMillisCounter(FAULT_DET_CABLE_CON_1) >= FAULT_DET_CABLE_CON_2)
					{
						cable_f->wrong_connection = true;
						if(sd_fault_det_cable_con == false)
						{
						ToSdCard(BRAK_KABLA_DET3);
						sd_fault_det_cable_con = true;
						}
						stopMillisCounter(FAULT_DET_CABLE_CON_1);
					}
					return false;
				}
				break;
			case 0:
				if(cable_f->adc_value <= DET_CABLE_WRONG_CON)
				{
					if(startMillisCounter(FAULT_DET_CABLE_CON_1) >= FAULT_DET_CABLE_CON_2)
					{
						cable_f->wrong_connection = true;
						if(sd_fault_det_cable_con == false)
						{
						ToSdCard(BRAK_KABLA_DET4);
						sd_fault_det_cable_con = true;
						}
						stopMillisCounter(FAULT_DET_CABLE_CON_1);
					}
					return false;
				}
				break;
			}
			cable_f->wrong_connection = false;
		}
	}
	restartMillisCounter(FAULT_DET_CABLE_CON_1);
	return true;
}

bool CheckDelayButConnected()
{
	static uint16_t delay_value = 0;

	delay_value = value[4];

	if(delay_value <= DELAY_TRIGGER_FAULT)
	{
		if(startMillisCounter(FAULT_DET_CABLE_CON_1) >= FAULT_DET_CABLE_CON_2)
		{
		if(sd_fault_delay_but_con == false)
		{
		  ToSdCard(BRAK_DELAY);
		  sd_fault_delay_but_con = true;
		}
		stopMillisCounter(FAULT_DET_CABLE_CON_1);
		}
		return false;
	}
	return true;
}

static void CheckBattery()
{
	static bool check_bat_1;

	if(HAL_GPIO_ReadPin(LOW_BAT_GPIO_Port, LOW_BAT_Pin) == GPIO_PIN_RESET && check_bat_1 == false)
	{
		if(startSecondsCounter(LOW_BAT_TIMER) >= 5)
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
			ToSdCard(BATERIA);
			check_bat_1 = true;
			restartSecondsCounter(LOW_BAT_TIMER);
		}
	}
	else if(HAL_GPIO_ReadPin(LOW_BAT_GPIO_Port, LOW_BAT_Pin) == GPIO_PIN_SET && check_bat_1 == true)
	{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		check_bat_1 = false;
		stopSecondsCounter(LOW_BAT_TIMER);
	}
}
