/*
 * breakup.h
 *
 *  Created on: Aug 8, 2023
 *      Author: wkania
 */

#include "stdbool.h"

#ifndef INC_BREAKUP_H_
#define INC_BREAKUP_H_


#define BREAKUP_TRIGGER      1500
#define BREAKUP_CHECK        3000



typedef struct BreakUp {
	uint16_t value;
	bool triggered;
	bool check_system;
}BreakUp;

extern BreakUp breakup;

void CheckFault(bool fault);
void BreakupProcess();

#endif /* INC_BREAKUP_H_ */
