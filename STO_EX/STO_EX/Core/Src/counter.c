/*
 * counter.c
 *
 *  Created on: Jul 26, 2023
 *      Author: wkania
 */

#include "counter.h"

volatile Couter_T second_counters[SECOUND_COUNTER_COUNT];
volatile Couter_T millis_counters[MILLIS_COUNTER_COUNT];



void UpdateCounter()
{
	static uint16_t millis = 0;
	if(++millis == 1000)
	{
		millis = 0;
	for (uint8_t i = 0; i < SECOUND_COUNTER_COUNT; ++i)
			{
				volatile Couter_T *counter = &second_counters[i];

				if (counter->enabled)
					++counter->counter;
			}
	}
	for (uint8_t i = 0; i < MILLIS_COUNTER_COUNT; ++i)
	{
		volatile Couter_T *counter = &millis_counters[i];

		if (counter->enabled)
			++counter->counter;
	}
}

uint16_t startCounter(volatile Couter_T *counter)
{

		if (!counter->enabled)
		{
			counter->enabled = true;
			counter->counter = 0;
		}

    return counter->counter;
}

void stopCounter(volatile Couter_T *counter)
{

	counter->enabled = false;
	counter->counter = 0;

}

void haltCounter(volatile Couter_T *counter)
{

    counter->enabled = false;

}

void restartCounter(volatile Couter_T *counter)
{
	{
		counter->enabled = true;
		counter->counter = 0;
	}
}


uint16_t startSecondsCounter(uint8_t counter)
{
	return startCounter(&second_counters[counter]);
}

uint16_t startMillisCounter(uint8_t counter)
{
	return startCounter(&millis_counters[counter]);
}

void stopSecondsCounter(uint8_t counter)
{
	stopCounter(&second_counters[counter]);
}

void stopMillisCounter(uint8_t counter)
{
	stopCounter(&millis_counters[counter]);
}

void restartSecondsCounter(uint8_t counter)
{
	restartCounter(&second_counters[counter]);
}

void restartMillisCounter(uint8_t counter)
{
	restartCounter(&millis_counters[counter]);
}
