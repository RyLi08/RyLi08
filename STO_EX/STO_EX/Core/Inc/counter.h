/*
 * counter.h
 *
 *  Created on: Jul 26, 2023
 *      Author: wkania
 */
#include "stdbool.h"
#include "stdio.h"

#ifndef INC_COUNTER_H_
#define INC_COUNTER_H_



#define SECOUND_COUNTER_COUNT 12     //ilość liczników sekundowych
#define MILLIS_COUNTER_COUNT  7     //ilość licznikow milisekundowych

//przypisanie numeru licznikowi za jaką operację będzie odpowiadał
//sekundowy
#define CONFIGURATION_TIMER 0
#define CHOICE_LED_TIMER_1  1
#define SWITCH_LED_TIMER_1  2
#define WCHICH_ZONE_TIMER_1 3
#define TIMER_EXTINGUISHER_1 4
#define TRIGGERED_EXT_OFF_TIMER_1 5
#define CHECK_WIRES_TIMER_1 6
#define SERVICE_TIMER_1 7
#define SERVICE_LED_1 8
#define SERVICE_ALARM 9
#define BREAKUP_TIMER_TRIG_CONFIG_1 10
#define LOW_BAT_TIMER 11
//milisekundy
#define SWITCH_LED_TIMER_2 0
#define CHOICE_LED_TIMER_2 1
#define TIMER_EXTINGUISHER_2 2
#define FAULT_EXT_CON_1 3
#define FAULT_DET_CABLE_CON_1 4
#define BREAKUP_TIMER_TRIG_1 5
#define BREAKUP_TIMER_CHECK_1 6

//przypisanie ile czasu ma upłynąć dla danej operacji
//sekundy
#define CONFIGURATION_ON_TIME  5    //Czas jaki trzeba przytrzymać oba przyciski by wejść w tryb konfiguracji
#define SW_CH_LED_TIMER_1      2
#define WCHICH_ZONE_TIMER_2    1
#define TIMER_EXTINGUISHER_SEC 1
#define TRIGGERED_EXT_OFF_TIMER_2 10
#define CHECK_WIRES_TIMER_2 1
#define SERVICE_LED_2 1
//milisekundy

#define EXT_LED_TIMER_1 700
#define EXT_LED_TIMER_2 400
#define EXT_LED_TIMER_3 200
#define SW_CH_LED_TIMER_2 300
#define FAULT_EXT_CON_2 700
#define FAULT_DET_CABLE_CON_2 700
#define BREAKUP_TIMER_TRIG_2 500
#define BREAKUP_TIMER_CHECK_2 150

typedef struct Counter_T {
	bool enabled;
	uint16_t counter;
}Couter_T;


void UpdateCounter();

uint16_t startSecondsCounter(uint8_t counter);
void stopSecondsCounter(uint8_t counter);
uint16_t startMillisCounter(uint8_t counter);
void stopMillisCounter(uint8_t counter);
void restartSecondsCounter(uint8_t counter);
void restartMillisCounter(uint8_t counter);

#endif /* INC_COUNTER_H_ */
