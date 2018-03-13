//
/*
**************************************************************************************************

Easy Build LoRaTracker Programs for Arduino ATMEGA328

Copyright of the author Stuart Robinson - 13/08/2016

HTTP://WWW.LORATRACKER.UK

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without
the explicit permission of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
intended purpose and free from errors.
**************************************************************************************************
*/


/*
******************************************************************************************************
Hardware definitions for the various LoRaTracker PCBs.

Most of the LoRaTracker programs will run on any of the LoRaTracker boards, the only known limitation
is that any programs using softserial input (typically for a GPS) will not work when the RFM98PIHShield
board is plugged into ATMEGA2560 base. Be careful to ensure that all Pro Minis or Arduino bases are
3.3V versions.

PIHTracker2 - Tracker PCB, 50mm x 22mm with the date 02/16, for RFM98 only
PIHTracker3 - Tracker PCB, 50mm x 22mm with the date 04/16, for RFM98 or DRF1278F
RFM98PIHShield2 - Shiled PCB, 50mm x 50mm with date April 2016, for RFM98 only
Relay - Relay PCB 42mm x 20mm with date July 2016

*******************************************************************************************************
*/


//board hardware definitions

#ifdef PIHTracker3
  #define lora_DIO0 2                   //pin connected to DIO0 on LoRa device
  #define Audio_Out 3                   //pin number for external tone generation
  #define lora_TonePin 4                //pin number for radio tone generation, connects to LoRa device pin DIO2
  #define WDI 5                         //pin for using a watchdog device
  #define Switch1 6                     //pin for switch input
  #define GPSPOWER 7                    //pin controls power to GPS
  #define lora_PNSS 8                   //pin number where the NSS line for the LoRa device is connected
  #define lora_PReset 9	                //pin where LoRa device reset line is connected
  #define PLED1 10                      //pin number for LED on Tracker
  #define PLED2 13                      //pin number for standard LED on pin 13 of Pro Mini

  #define SupplyAD A0                   //pin for supply AD
  #define GPSBACKUP A1                  //use for GPS backup power
  #define CON2_1 A1                     //connected to CON2 pin 1 on external header
  #define GPSTX A2                      //pin number for TX output - RX into GPS
  #define GPSRX A3                      //pin number for RX input - TX from GPS
  #define RCPulse A4                    //pin used to read RC pulse
  #define DisplayTX A5                  //soft serial TX pin for Digole Serial LCD
  
  #define GPSBaud 9600                  //GPS baud rate
  #define ADMultiplier 10               //multiplier for supply volts calculation
#endif


#ifdef PIHTracker2
  #define lora_DIO0 2                   //pin connected to DIO0 on LoRa device
  #define Audio_Out 3                   //pin number for external tone generation
  #define lora_TonePin 4                //pin number for radio tone generation, connects to LoRa device pin DIO2
  #define WDI 5                         //pin for using a watchdog device
  #define Switch1 6                     //pin for switch input
  #define lora_PNSS 8	                //pin number where the NSS line for the LoRa device is connected
  #define lora_PReset 9	                //pin where LoRa device reset line is connected
  #define PLED1 10                      //pin number for LED on Tracker
  #define PLED2 13                      //pin number for standard LED on pin 13 of Pro Mini

  #define GPSPOWER A0                   //pin controls power to GPS
  #define CON2_1 A1                     //connected to CON2 pin 1 on external header
  #define GPSTX A2                      //pin number for TX output - RX into GPS
  #define GPSRX A3                      //pin number for RX input - TX from GPS
  #define RCPulse A4                    //pin used to read RC pulse
  #define DisplayTX A5                  //soft serial TX pin for Digole Serial LCD
  #define SupplyAD A7                   //pin for supply AD

  #define GPSBaud 9600                  //GPS baud rate
  #define ADMultiplier 10               //multiplier for supply volts calculation
#endif


#ifdef RFM98PIHShield2
  #define Switch1 2                     //pin for switch
  #define RCPulse 4                     //External RC Pulse sense
  #define lora_TonePin 6                //pin number for tone generation, connects to LoRa device DIO2.
  #define lora_AFSKRTTYPin 6            //pin number for outputing AFSK RTTY, may be the same as lora_TonePin
  #define FRAM_NSS 7                    //Select for FRAM
  #define Buzzer 7                      //Buzzer for receiver
  #define DisplayTX 8                   //Soft serial TX pin for Digole Serial LCD
  #define PLED1 9                       //pin number for LED on Tracker
  #define GPSPOWER 10                   //Controls power to GPS
  #define PLED2 13                      //pin number for LED fitted to most shield bases
  
  #define lora_PNSS A0	                //pin number where the NSS line for the LoRa device is connected.
  #define Switch2 A0                    //pin for switch2
  #define lora_PReset A1	        //pin where LoRa device reset line is connected
  #define GPSRX A2
  #define GPSTX A3
  #define SupplyAD A6                   //pin for supply AD
  
  #define GPSBaud 9600                  //GPS baud rate
  #define ADMultiplier 10               //multiplier for supply volts calculation
#endif


#ifdef Relay
  #define lora_DIO0 2                   //pin connected to DIO0 on LoRa device
  #define Switch1 3                     //pin for switch
  #define lora_DIO5 4                   //pin connected to DIO5 on LoRa device
  #define RCPulse 5                     //pin used to read RC pulse
  #define lora_DIO2 6                   //pin connected to DIO2 on LoRa device
  #define lora_TonePin 6                //pin connected to DIO2 on LoRa device
  #define lora_DIO1 7                   //pin connected to DIO1 on LoRa device
  #define lora_DIO4 8                   //pin connected to DIO4 on LoRa device
  #define lora_DIO3 9                   //pin connected to DIO3 on LoRa device
  #define lora_PNSS 10	                //pin number where the NSS line for the LoRa device is connected
  #define PLED2 13                      //pin number for standard LED on pin 13 of Pro Mini
  
  #define lora_PReset A0                //pin where LoRa device reset line is connected
  #define SupplyAD A1                   //pin for supply AD
  #define WDI A2                        //pin for using a watchdog device
  #define PLED1 A3                      //pin number for LED on Tracker
  #define GPSTX A4                      //pin number for TX output - RX into GPS
  #define GPSRX A5                      //pin number for RX input - TX from GPS
  #define Audio_Out A7                  //Unused pin
  #define GPSPOWER A7                   //Unused pin
  #define GPSBaud 9600                  //GPS baud rate
  #define ADMultiplier 10               //multiplier for supply volts calculation
#endif

const char ACK = 'A';
const char LinkReport = 'B';            //HAB Style in CSV
const char bLinkReport = 'b';           //binary style
const char ClearToSend = 'C';
const char ClearToSendCommand = 'c';
const char Error = 'E';                      
const char NoFix = 'F';
const char NoGPS = 'G';
const char GLONASSDetected = 'g';
const char LongPayload = '$';
const char Memory = 'M';
const char NACK = 'N';
const char NACKCommand = 'n';
const char PowerUp = 'P';               //or reset
const char Repeated = 'R';
const char ShortPayload = 'S';
const char Test = 'T';
const char Wakeup = 'W';
const char ResetTracker = 'X';
const char Config1 = 'Y';
const char Config0 = 'Z';
const char WritePacketEEPROM = '0';    //Write bytes to EEPROM 
const char Bind = '#';

const char Broadcast = '*';            //broadcast address
const char PacketStart = '$';          //command packets have a payload of at least one byte, so put this at start

