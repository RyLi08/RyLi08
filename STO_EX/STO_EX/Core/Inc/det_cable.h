/*
 * det_cable.h
 *
 *  Created on: Jul 25, 2023
 *      Author: wkania
 */

#include "stdbool.h"
#include "stdio.h"

#ifndef INC_DET_CABLE_H_
#define INC_DET_CABLE_H_

#define DET_CABLE_COUNT 4

#define DET_CABLE_TRIGGERED 2500
#define DET_CABLE_TRIGGERED_FILTER 200

#define DET_CABLE_WRONG_CON 400
#define DET_CABLE_WRONG_CON_FILTER 30

typedef struct Det_Cable {
	bool enabled;              // czy jest ten kabel załączony
	uint16_t adc_value;
	bool triggered;
	uint8_t filter_triggered;
	bool wrong_connection;
	uint8_t filter_wrong_connection;
	bool is_triggered;
	uint8_t filter_trig_off;
}Det_Cable;


extern Det_Cable det_cable[DET_CABLE_COUNT];


void DetCableProcess();
void EnabledDetCab();
bool DetCableService();

#endif /* INC_DET_CABLE_H_ */
