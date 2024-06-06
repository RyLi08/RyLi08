/*
 * det_cable.c
 *
 *  Created on: Jul 25, 2023
 *      Author: wkania
 */

#include <det_cable.h>
#include <configuration.h>
#include "adc.h"

Det_Cable det_cable[DET_CABLE_COUNT];

void EnabledDetCab(Configuration *config)
{
	for(int i = 0; i < config->amount_det_cables ; i++)
	{
		if(i == 0)
			det_cable[3].enabled = true;
		else if(i == 3)
			det_cable[0].enabled = true;
		else
		det_cable[i].enabled = true;
	}
}

void DetCableProcess()
{

	for(int i = 0; i < DET_CABLE_COUNT ; i++)
	{
		Det_Cable *cable;
		cable = &det_cable[i];

		if(cable->enabled == true)
		{
			cable->adc_value = value[i];

			cable->filter_triggered = (cable->adc_value >= DET_CABLE_TRIGGERED) ? det_cable[i].filter_triggered + 1 : 0;
			cable->triggered = (cable->filter_triggered >= DET_CABLE_TRIGGERED_FILTER) ? true : false;

            if(cable->filter_triggered >=254)
            	cable->filter_triggered = 50;

		//	cable->filter_wrong_connection = (cable->adc_value <= DET_CABLE_WRONG_CON && not_connected == false) ? det_cable[i].filter_wrong_connection + 1 : 0;
			//cable->wrong_connection = (cable->filter_wrong_connection >= DET_CABLE_WRONG_CON_FILTER) ? true : false;

			//if(cable->filter_wrong_connection >= 40)
			//	not_connected = true;

			//if(cable->adc_value >= 1000)
			//	not_connected = false;
		}

	}

}

bool DetCableService()
{

	for(int i = 0; i < DET_CABLE_COUNT ; i++)
	{
		Det_Cable *cable_service;
		cable_service = &det_cable[i];

		if(cable_service->enabled == true)
		{
			cable_service->adc_value = value[i];

			cable_service->filter_triggered = (cable_service->adc_value >= DET_CABLE_TRIGGERED) ? det_cable[i].filter_triggered + 1 : 0;

			if(cable_service->filter_triggered == 200)
				cable_service->filter_triggered = 0;

			if(cable_service->filter_triggered >= DET_CABLE_TRIGGERED_FILTER && cable_service->is_triggered == false)
			{
				cable_service->is_triggered = true;
			}
			if(cable_service->is_triggered == true && cable_service->adc_value <= DET_CABLE_TRIGGERED)
				cable_service->filter_trig_off++;
			else
				cable_service->filter_trig_off = 0;

			if(cable_service->filter_trig_off == 200)
				cable_service->filter_trig_off = 0;

			if(cable_service->filter_trig_off >= DET_CABLE_TRIGGERED_FILTER)
				cable_service->is_triggered = false;

			if(cable_service->is_triggered == true)
				return true;
		}
	}
		return false;
}

