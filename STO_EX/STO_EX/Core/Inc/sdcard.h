/*
 * sdcard.h
 *
 *  Created on: 11 sie 2022
 *      Author: WKania
 */

#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_


typedef enum zdarzenia_t{
	OPOZNIENIE_ZADZIALANIA,  //Operator po wystąpieniu pożaru opóźnił proces wyzwolenia gaśnicy
	BATERIA,                 //niski poziom baterii zasilającej układ
	MANUALNE_WYZWOLENIE,     //Ręczne wyzwolenie systemu gaśniczego
	WYZWOLENIE_KABEL_STREFA_1,        //Przepalenie się kabla detekcyjnego przez wystąpienie pożaru lub przez inegerencje osób trzecich
	WYZWOLENIE_KABEL_STREFA_2,
	WYZWOLENIE_KABEL_STREFA_3,
	WYZWOLENIE_KABEL_STREFA_4,
	SPRAWDZENIE_SYSTEMU,      // przycisnienie zrywki
	BRAK_GAS1,
	BRAK_GAS2,
	BRAK_GAS3,
	BRAK_GAS4,
	BRAK_KABLA_DET1,
	BRAK_KABLA_DET2,
	BRAK_KABLA_DET3,
	BRAK_KABLA_DET4,
	NORMAL_WORK,
	GASNICA_URUCHOMIONA,
    SERWIS_ON,
	SERWIS_OFF,
	CONFIG_UPADATE,
	CONFIG_ACTUAL,
	KABEL_SERWIS,
	BRAK_DELAY,
	BRAK,
}zdarzenia_t;

extern zdarzenia_t global_event;

void InitSd();
void ToSdCard(zdarzenia_t sd_event);
//void to_sdcard(SdFunction *sd1);
//void sd_process();


#endif /* INC_SDCARD_H_ */
