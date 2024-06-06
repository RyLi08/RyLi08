/*
 * extinguisher.h
 *
 *  Created on: Aug 1, 2023
 *      Author: wkania
 */

#include <configuration.h>
#include <stdbool.h>

#ifndef INC_EXTINGUISHER_H_
#define INC_EXTINGUISHER_H_

#define EXTINGUISHER_COUNT_2 4

#define DELAY_TRIGGER_ON 3500
#define DELAY_TRIGGER_FAULT 500
#define DELAY_MAX_COUNT 3


typedef struct Extinguisher {
	bool enabled;
	bool is_connected;
	bool is_triggered;
}Extinguisher;

extern Extinguisher extinguisher[EXTINGUISHER_COUNT_2];

void GetParameter(Configuration *config);
void ExtinguisherProcess(Configuration *config, bool wires_is_ok);
void WchichExtinguisher(uint8_t number);

#endif /* INC_EXTINGUISHER_H_ */
