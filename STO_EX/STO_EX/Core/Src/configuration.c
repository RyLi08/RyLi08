/*
 * configuration.c
 * W tym znajduje sie algorytm ustawiania parametrów pracy STO i jego zapis do pamięci.
 *  Created on: Jul 26, 2023
 *      Author: wkania
 */

#include "stdbool.h"
#include "stdio.h"
#include "rtc.h"
#include <configuration.h>
#include "gpio.h"
#include <counter.h>
#include <led_operation.h>
#include <sdcard.h>
#include <det_cable.h>
#include <extinguisher.h>

static void BlinkChoiceLed(uint8_t count);
static void ChoiceValueToConfig(switch_option_t option);
static void BlinkSwitcheLed(uint8_t count);
static void ForceDefaultConfig();
static bool TryToModeConfig();

volatile static uint8_t sw_change = 0;
uint8_t choice_cable_count = 1;
uint8_t extinguisher_count = 1;
uint8_t zone_count = 1;
uint8_t cable_trig_time = 1;
uint8_t breakup_trig_time = 1;
uint8_t delay_trig_time = 1;


volatile bool buttonSwPressed = false;
volatile bool buttonChPressed = false;

Configuration config = {
	.amount_det_cables = DEFAULT_AMOUNT_DET_CABLES,
	.amount_extinguisher = DEFAULT_AMOUNT_EXTINGUISHER,
	.amount_zone = DEFAULT_AMOUNT_ZONE,
	.time_breakup_trigger = DEFAULT_TIME_BREAKUP_TRIGGER,
	.time_cable_trigger = DEFAULT_TIME_CABLE_TRIG,
	.time_delay_trigger = DEFAULT_TIME_DELAY_TRIGGER,
	.config_mode = false
};


static void SaveConfiguration(Configuration config)
{

	WriteToBackupReg(RTC_BKP_DET_CABLES, config.amount_det_cables);
	WriteToBackupReg(RTC_BKP_EXTINGUISHER, config.amount_extinguisher);
	WriteToBackupReg(RTC_BKP_ZONE, config.amount_zone);
	WriteToBackupReg(RTC_BKP_TIME_DET_CABLE, config.time_cable_trigger);
	WriteToBackupReg(RTC_BKP_TIME_BREAKUP, config.time_breakup_trigger);
	WriteToBackupReg(RTC_BKP_TIME_DELAY, config.time_delay_trigger);

	ToSdCard(CONFIG_UPADATE);

	choice_cable_count = 1;
	extinguisher_count = 1;
	zone_count = 1;
	cable_trig_time = 1;
    breakup_trig_time = 1;

    EnabledDetCab(&config);
    GetParameter(&config);

}

void LoadConfiguration()
{

	config.amount_det_cables = ReadBackupReg(RTC_BKP_DET_CABLES);
	config.amount_extinguisher = ReadBackupReg(RTC_BKP_EXTINGUISHER);
	config.amount_zone = ReadBackupReg(RTC_BKP_ZONE);
	config.time_cable_trigger = ReadBackupReg(RTC_BKP_TIME_DET_CABLE);
	config.time_breakup_trigger = ReadBackupReg(RTC_BKP_TIME_BREAKUP);
	config.time_delay_trigger = ReadBackupReg(RTC_BKP_TIME_DELAY);

	if(config.amount_det_cables != 0)
	{
		ToSdCard(CONFIG_ACTUAL);
	}
	else
	{
		ForceDefaultConfig();
		ToSdCard(CONFIG_ACTUAL);
	}
	EnabledDetCab(&config);
	GetParameter(&config);
}

void WriteToBackupReg(uint32_t nr_reg, uint16_t value)
{
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();

  HAL_RTCEx_BKUPWrite(&hrtc, nr_reg, value);

  HAL_PWR_DisableBkUpAccess();
}

uint16_t ReadBackupReg(uint32_t nr_reg)
{
  uint16_t value;

  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();

  value = HAL_RTCEx_BKUPRead(&hrtc, nr_reg);

  HAL_PWR_DisableBkUpAccess();
  return value;
}

void ConfigurationMode()
{
	if(TryToModeConfig() == true)
	{
		if(startSecondsCounter(CONFIGURATION_TIMER) >= CONFIGURATION_ON_TIME)
		{

			ConfigurationModeIsOn(true);
			HAL_Delay(1000);
			ConfigurationModeIsOn(false);
			stopSecondsCounter(CONFIGURATION_TIMER);
			config.config_mode = true;
		}
	}
	else
		restartSecondsCounter(CONFIGURATION_TIMER);

	while(config.config_mode == true)
	{

		if (HAL_GPIO_ReadPin(SWITCH_SW_GPIO_Port, SWITCH_SW_Pin) == GPIO_PIN_RESET)
		{
		    buttonSwPressed = false;
            HAL_Delay(300);
		    }
		if (HAL_GPIO_ReadPin(CHOICE_SW_GPIO_Port, CHOICE_SW_Pin) == GPIO_PIN_RESET)
		{
		    buttonChPressed = false;
            HAL_Delay(300);
		    }

        switch(sw_change)
        {
        case 0:
    	    if(startSecondsCounter(SWITCH_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
    	    {
    	    BlinkSwitcheLed(2);
    	    ChoiceValueToConfig(CABLE_COUNT);
    	    restartSecondsCounter(SWITCH_LED_TIMER_1);
    	    }
            break;
        case 1:
    	    if(startSecondsCounter(SWITCH_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
    	    {
    	    BlinkSwitcheLed(4);
    	    ChoiceValueToConfig(EXTINGUISHER_COUNT);
    	    restartSecondsCounter(SWITCH_LED_TIMER_1);
    	    }
    	    break;
        case 2:
    	    if(startSecondsCounter(SWITCH_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
    	    {
    	    BlinkSwitcheLed(6);
    	    ChoiceValueToConfig(ZONE_COUNT);
    	    restartSecondsCounter(SWITCH_LED_TIMER_1);
    	    }
    	    break;
        case 3:
    	    if(startSecondsCounter(SWITCH_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
    	    {
    	    BlinkSwitcheLed(8);
    	    ChoiceValueToConfig(CABLE_TRIG_TIME);
    	    restartSecondsCounter(SWITCH_LED_TIMER_1);
    	    }
    	    break;
        case 4:
    	    if(startSecondsCounter(SWITCH_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
    	    {
    	    BlinkSwitcheLed(10);
    	    ChoiceValueToConfig(BREAKUP_TRIG_TIME);
    	    restartSecondsCounter(SWITCH_LED_TIMER_1);
    	    }
    	    break;
        case 5:
    	    if(startSecondsCounter(SWITCH_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
    	    {
    	    BlinkSwitcheLed(12);
    	    ChoiceValueToConfig(DELAY_TIME);
    	    restartSecondsCounter(SWITCH_LED_TIMER_1);
    	    }
    	    break;
        default:
	    config.config_mode = false;
	    sw_change = 0;
		ConfigurationModeIsOn(true);
		HAL_Delay(2000);
		ConfigurationModeIsOn(false);
		SaveConfiguration(config);
	    break;

        }
	}
}

static void ChoiceValueToConfig(switch_option_t option)
{

	switch(option)
	{
	case CABLE_COUNT:
		switch(choice_cable_count)
		{
		case 1:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.amount_det_cables = OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;

		case 2:
			if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
			   {
		   	   BlinkChoiceLed(4);
			   config.amount_det_cables = OPTION_2;
			   restartSecondsCounter(CHOICE_LED_TIMER_1);
			   }
			   break;
		case 3:
			if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
			{
			   BlinkChoiceLed(6);
			   config.amount_det_cables = OPTION_3;
			   restartSecondsCounter(CHOICE_LED_TIMER_1);
			   }
			   break;
		case 4:
			if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
			   {
			   BlinkChoiceLed(8);
			   config.amount_det_cables = OPTION_4;
			   restartSecondsCounter(CHOICE_LED_TIMER_1);
			   }
			   break;
		default:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.amount_det_cables = OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
			   choice_cable_count = 1;
		}
	case EXTINGUISHER_COUNT:
        switch(extinguisher_count)
        {
		case 1:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.amount_extinguisher = OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 2:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(4);
	    	   config.amount_extinguisher = OPTION_2;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 3:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(6);
	    	   config.amount_extinguisher = OPTION_3;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 4:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(8);
	    	   config.amount_extinguisher = OPTION_4;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		default:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.amount_extinguisher = OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   extinguisher_count = 1;
        }
    case ZONE_COUNT:
    	switch(zone_count)
    	{
		case 1:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.amount_zone = OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 2:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(4);
	    	   config.amount_zone = OPTION_2;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 3:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(6);
	    	   config.amount_zone = OPTION_3;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 4:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(8);
	    	   config.amount_zone = OPTION_4;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		default:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.amount_zone = OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   zone_count = 1;
    	}
   case CABLE_TRIG_TIME:
    	switch(cable_trig_time)
    	{
		case 1:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.time_cable_trigger = TIME_CABLE_OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 2:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(4);
	    	   config.time_cable_trigger = TIME_CABLE_OPTION_2;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 3:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(6);
	    	   config.time_cable_trigger = TIME_CABLE_OPTION_3;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 4:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(8);
	    	   config.time_cable_trigger = TIME_CABLE_OPTION_4;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		default:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.time_cable_trigger = TIME_CABLE_OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   cable_trig_time = 1;
    	}
   case BREAKUP_TRIG_TIME:
     	switch(breakup_trig_time)
    	{
		case 1:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.time_breakup_trigger = TIME_BREAKUP_OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 2:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(4);
	    	   config.time_breakup_trigger = TIME_BREAKUP_OPTION_2;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 3:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(6);
	    	   config.time_breakup_trigger = TIME_BREAKUP_OPTION_3;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		case 4:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(8);
	    	   config.time_breakup_trigger = TIME_BREAKUP_OPTION_4;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   break;
		default:
	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
	    	   {
	    	   BlinkChoiceLed(2);
	    	   config.time_breakup_trigger = TIME_BREAKUP_OPTION_1;
	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
	    	   }
	    	   breakup_trig_time = 1;
    	}
        case DELAY_TIME:
          	switch(delay_trig_time)
         	{
     		case 1:
     	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
     	    	   {
     	    	   BlinkChoiceLed(2);
     	    	   config.time_delay_trigger = TIME_DELAY_OPTION_1;
     	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
     	    	   }
     	    	   break;
     		case 2:
     	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
     	    	   {
     	    	   BlinkChoiceLed(4);
     	    	   config.time_delay_trigger = TIME_DELAY_OPTION_2;
     	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
     	    	   }
     	    	   break;
     		case 3:
     	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
     	    	   {
     	    	   BlinkChoiceLed(6);
     	    	   config.time_delay_trigger = TIME_DELAY_OPTION_3;
     	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
     	    	   }
     	    	   break;
     		case 4:
     	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
     	    	   {
     	    	   BlinkChoiceLed(8);
     	    	   config.time_delay_trigger = TIME_DELAY_OPTION_4;
     	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
     	    	   }
     	    	   break;
     		default:
     	    	if(startSecondsCounter(CHOICE_LED_TIMER_1) >= SW_CH_LED_TIMER_1)
     	    	   {
     	    	   BlinkChoiceLed(2);
     	    	   config.time_delay_trigger = TIME_DELAY_OPTION_1;
     	      	   restartSecondsCounter(CHOICE_LED_TIMER_1);
     	    	   }
     	    	   delay_trig_time = 1;
         	}

	}
}

static void BlinkChoiceLed(uint8_t count)
{
	static uint8_t x = 0;
	while(x <= count - 1)
	{
    	if(startMillisCounter(CHOICE_LED_TIMER_2) >= SW_CH_LED_TIMER_2)
    	{
    	HAL_GPIO_TogglePin(CHOICE_LED_GPIO_Port, CHOICE_LED_Pin);
    	stopMillisCounter(CHOICE_LED_TIMER_2);
    	x++;
    	}
	}
   x = 0;
}

static void BlinkSwitcheLed(uint8_t count)
{
static uint8_t x = 0;

  while(x <= count - 1)
  {
    	if(startMillisCounter(SWITCH_LED_TIMER_2) >= SW_CH_LED_TIMER_2)
    	{
    	HAL_GPIO_TogglePin(SWITCH_LED_GPIO_Port, SWITCH_LED_Pin);
    	stopMillisCounter(SWITCH_LED_TIMER_2);
    	x++;
    	}
  }
  x = 0;
}

static bool TryToModeConfig()
{
	if(HAL_GPIO_ReadPin(SWITCH_SW_GPIO_Port, SWITCH_SW_Pin) == true &&
	   HAL_GPIO_ReadPin(CHOICE_SW_GPIO_Port, CHOICE_SW_Pin) == true)
	{
		return true;
	}
	else
		return false;
}

void SwButtonCount()
{
	buttonSwPressed = true;
	if(config.config_mode == true)
	sw_change++;
}

bool SwButPressed()
{
	return buttonSwPressed;
}

void ChButtonCount()
{
	buttonChPressed = true;
	if(config.config_mode == true)
	{
		if(sw_change == 0)
	        choice_cable_count++;
		else if(sw_change == 1)
	    	extinguisher_count++;
	    else if(sw_change == 2)
	    	zone_count++;
	    else if(sw_change == 3)
	    	cable_trig_time++;
	    else if(sw_change == 4)
	    	breakup_trig_time++;
	    else if(sw_change == 5)
	    	delay_trig_time++;
	}
}

bool ChButPressed()
{
	return buttonChPressed;
}

static void ForceDefaultConfig()
{
	config.amount_det_cables = DEFAULT_AMOUNT_DET_CABLES;
	config.amount_extinguisher = DEFAULT_AMOUNT_EXTINGUISHER;
	config.amount_zone = DEFAULT_AMOUNT_ZONE;
	config.time_breakup_trigger = DEFAULT_TIME_BREAKUP_TRIGGER;
	config.time_cable_trigger = DEFAULT_TIME_CABLE_TRIG;
	config.config_mode = false;
}
