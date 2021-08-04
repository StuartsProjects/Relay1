//Pin_Definitions.h
/*
**************************************************************************************************

Easy Build Tracker Programs for Arduino ATMEGA328

Copyright of the author Stuart Robinson - 07/12/2018

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without
the explicit permission of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
intended purpose and free from errors.
**************************************************************************************************
*/


/*
******************************************************************************************************
Hardware definitions for the various Tracker PCBs.

Most of the Tracker programs will run on any of the Tracker boards, the only known limitation
is that any programs using softserial input (typically for a GPS) will not work when the RFM98PIHShield
board is plugged into ATMEGA2560 base. Be careful to ensure that all Pro Minis or Arduino bases are
3.3V versions.

*******************************************************************************************************
*/


//board hardware definitions

#ifdef Locator2
  #define lora_DIO0 2                   //pin connected to DIO0 on LoRa device
  #define lora_TonePin 6                //pin number for radio tone generation, connects to LoRa device pin DIO2
  #define PLED1 8                        //pin number for LED on Tracker
  #define lora_PReset 9                 //pin where LoRa device reset line is connected
  #define lora_PNSS 10                   //pin number where the NSS line for the LoRa device is connected
#endif


#ifdef Pro_Mini_Mikrobus_Shield
  #define lora_PNSS 10                  //pin number where the chip select for the LoRa device is connected
  #define lora_PReset 9                 //pin where LoRa device reset line is connected
  #define lora_TonePin 6                //pin number for radio tone generation, connects to LoRa device pin DIO2
  #define lora_DIO0 2                   //pin connected to DIO0 on LoRa device
  #define PLED1 8                       //pin number for LED 
#endif


#ifdef Relay
  #define lora_DIO0 2                    //pin connected to DIO0 on LoRa device
  #define lora_TonePin 6                 //pin connected to DIO2 on LoRa device
  #define lora_PNSS 10	                 //pin number where the NSS line for the LoRa device is connected
  #define lora_PReset A0                 //pin where LoRa device reset line is connected
  #define PLED1 A3                       //pin number for LED on Tracker
#endif
