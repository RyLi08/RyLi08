/*
 * sdcard.c
 *
 *  Created on: 11 sie 2022
 *      Author: WKania
 */

#include "fatfs.h"
#include "rtc.h"
#include "ff.h"
#include "fatfs_sd.h"

#include <sdcard.h>
#include <stdbool.h>
#include "gpio.h"
#include <configuration.h>

static FATFS fs;
static FIL fil;
static FRESULT fres;

RTC_TimeTypeDef time;
RTC_DateTypeDef date;



static void OpenFile();
static void CloseFile();

void InitSd()
{

	fres = f_mount(&fs,"", 0);
	fres = f_open(&fil, "STO.txt", FA_OPEN_EXISTING);
	if (HAL_GPIO_ReadPin(SD_DETECT_GPIO_Port, SD_DETECT_Pin) == GPIO_PIN_RESET && fres != FR_OK)
	{
    HAL_Delay(500);
    fres = f_mount(&fs,"", 0);
    fres = f_open(&fil, "STO.txt", FA_OPEN_APPEND | FA_WRITE);
	   if(fres != FR_OK)
	   {
	   Error_Handler();
	   }
	f_puts("Czas                                Zdarzenie\n", &fil);
	CloseFile();
    }
	OpenFile();
	f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Zalaczenie systemu\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
	CloseFile();
}

void ToSdCard(zdarzenia_t sd_event)
{
   Configuration *config_sd = &config;

	switch(sd_event)
	{
	case BATERIA:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                niski poziom baterii\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;
	case OPOZNIENIE_ZADZIALANIA:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                opoznienie zadziałania\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;
	case MANUALNE_WYZWOLENIE:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                reczne wyzwolenie gaśnicy\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;
	case WYZWOLENIE_KABEL_STREFA_1:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                kabel detekcyjny - wyzwolenie gasnicy strefa 1\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case WYZWOLENIE_KABEL_STREFA_2:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                kabel detekcyjny - wyzwolenie gasnicy strefa 2\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case WYZWOLENIE_KABEL_STREFA_3:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                kabel detekcyjny - wyzwolenie gasnicy strefa 3\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case WYZWOLENIE_KABEL_STREFA_4:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                kabel detekcyjny - wyzwolenie gasnicy strefa 4\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case SPRAWDZENIE_SYSTEMU:

		OpenFile();
	    f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Sprawdzenie działania systemu\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
	    sd_event = BRAK;
		CloseFile();
		break;

	case BRAK_GAS1:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Gasnica 1 nie podłaczona\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		 break;

	case BRAK_GAS2:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Gasnica 2 nie podłaczona\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		 break;

	case BRAK_GAS3:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Gasnica 3 nie podłaczona\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		 break;

	case BRAK_GAS4:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Gasnica 4 nie podłaczona\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		 break;

	case BRAK_KABLA_DET1:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Kabel detekcyjny 1 nie podlaczony\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case BRAK_KABLA_DET2:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Kabel detekcyjny 2 nie podlaczony\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case BRAK_KABLA_DET3:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Kabel detekcyjny 3 nie podlaczony\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case BRAK_KABLA_DET4:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Kabel detekcyjny 4 nie podlaczony\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case NORMAL_WORK:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Prawidlowia praca\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
	    CloseFile();
		break;

	case GASNICA_URUCHOMIONA:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Gasnice uruchomione\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;
	case SERWIS_ON:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Zalaczony tryb serwisowy\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case SERWIS_OFF:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Wylaczony tryb serwisowy\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case CONFIG_UPADATE:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Zmiana konfiguracji:\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		f_printf(&fil,"Ilosc kabli:                                  %d szt.             \n", config_sd->amount_det_cables);
		f_printf(&fil,"Ilosc gasnic:                                 %d szt.             \n", config_sd->amount_extinguisher);
		f_printf(&fil,"Ilosc stref gasniczych:                       %d szt.             \n", config_sd->amount_zone);
		f_printf(&fil,"czas wyzwolenia gasnicy - przewod:            %d sek.             \n", config_sd->time_cable_trigger);
		f_printf(&fil,"czas wyzwolenia gasnicy - zrywka:             %d sek.             \n", config_sd->time_breakup_trigger);
		f_printf(&fil,"czas opoznienia wyzwolenia:                   %d sek.             \n", config_sd->time_delay_trigger);
		sd_event = BRAK;
		CloseFile();
		break;
	case CONFIG_ACTUAL:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                obecna konfiguracja:\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		f_printf(&fil,"Ilosc kabli:                                  %d szt.             \n", config_sd->amount_det_cables);
		f_printf(&fil,"Ilosc gasnic:                                 %d szt.             \n", config_sd->amount_extinguisher);
		f_printf(&fil,"Ilosc stref gasniczych:                       %d szt.             \n", config_sd->amount_zone);
		f_printf(&fil,"czas wyzwolenia gasnicy - przewod:            %d sek.             \n", config_sd->time_cable_trigger);
		f_printf(&fil,"czas wyzwolenia gasnicy - zrywka:             %d sek.             \n", config_sd->time_breakup_trigger);
		f_printf(&fil,"czas opoznienia wyzwolenia:                   %d sek.             \n", config_sd->time_delay_trigger);
		sd_event = BRAK;
		CloseFile();
		break;

	case KABEL_SERWIS:

		OpenFile();
		f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Kabel detekcyjny został zwarty trybie serwisowym\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
		sd_event = BRAK;
		CloseFile();
		break;

	case BRAK_DELAY:

			OpenFile();
			f_printf(&fil,"%04d-%02d-%02d, %02d:%02d:%02d                Break przycisku opoznienia\n", 2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
			sd_event = BRAK;
			CloseFile();
			break;
	}

}

static void OpenFile()
{
	fres = f_mount(&fs,"", 0);
	fres = f_open(&fil, "STO.txt", FA_OPEN_APPEND | FA_WRITE);
	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
}

static void CloseFile()
{
    fres = f_close(&fil);
	fres = f_mount(NULL, "", 1);
}




