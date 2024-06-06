/*
 * configuration.h
 *
 *  Created on: Jul 26, 2023
 *      Author: wkania
 */

#include "stdbool.h"
#include "stdio.h"

#ifndef INC_CONFIGURATION_H_
#define INC_CONFIGURATION_H_

#define DEFAULT_AMOUNT_DET_CABLES             1
#define DEFAULT_AMOUNT_EXTINGUISHER           2
#define DEFAULT_AMOUNT_ZONE                   1
#define DEFAULT_TIME_CABLE_TRIG               10
#define DEFAULT_TIME_BREAKUP_TRIGGER          0
#define DEFAULT_TIME_DELAY_TRIGGER            5

#define RTC_BKP_DET_CABLES                    0x01u
#define RTC_BKP_EXTINGUISHER                  0x02u
#define RTC_BKP_ZONE                          0x03u
#define RTC_BKP_TIME_DET_CABLE                0x04u
#define RTC_BKP_TIME_BREAKUP                  0x05u
#define RTC_BKP_TIME_DELAY                    0x06u

//#define RTC_BKP_OPTION_1                      0x06u
//#define RTC_BKP_OPTION_2                      0x07u
//#define RTC_BKP_OPTION_3                      0x08u
//#define RTC_BKP_OPTION_4                      0x09u
//#define RTC_BKP_OPTION_5                      0x0Au

#define OPTION_1                              1
#define OPTION_2                              2
#define OPTION_3                              3
#define OPTION_4                              4

#define TIME_CABLE_OPTION_1                   3
#define TIME_CABLE_OPTION_2                   5
#define TIME_CABLE_OPTION_3                   10
#define TIME_CABLE_OPTION_4                   15

#define TIME_BREAKUP_OPTION_1                 0
#define TIME_BREAKUP_OPTION_2                 2
#define TIME_BREAKUP_OPTION_3                 4
#define TIME_BREAKUP_OPTION_4                 6

#define TIME_DELAY_OPTION_1                   5
#define TIME_DELAY_OPTION_2                   10
#define TIME_DELAY_OPTION_3                   15
#define TIME_DELAY_OPTION_4                   20

typedef enum switch_option_t {
	CABLE_COUNT,
	EXTINGUISHER_COUNT,
	ZONE_COUNT,
	CABLE_TRIG_TIME,
	BREAKUP_TRIG_TIME,
	DELAY_TIME,
	CONFIG_OUT
}switch_option_t;


typedef struct Configuration{
	uint8_t amount_det_cables;          //ilość kabli detekcyjnych
	uint8_t amount_extinguisher;        //ilość gaśnic
	uint8_t amount_zone;                //ilość stref gaśniczych
	uint8_t time_cable_trigger;         //czas do wyzwolenia gaśnicy po detekcji kabla
	uint8_t time_breakup_trigger;       //czas do wyzwolenia gasnicy po zerwaniu zrywki
	uint8_t time_delay_trigger;
	bool config_mode;                   //tryb wejscie w tryb konfiguracji
}Configuration;


extern Configuration config;



void ConfigurationMode();

void SwButtonCount();
bool SwButPressed();
void ChButtonCount();
bool ChButPressed();
void LoadConfiguration();
void WriteToBackupReg(uint32_t nr_reg, uint16_t value);
uint16_t ReadBackupReg(uint32_t nr_reg);

#endif /* INC_CONFIGURATION_H_ */
