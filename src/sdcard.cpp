#include "sdcard.h"



void test_sdcard(void)
{
	if(!SD.begin(4, SPI, 1000000))
    {
        Serial.println("Card Mount Failed");
    }
    else
    {
        Serial.println("Card Mount Success");
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
    }
    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }
}
