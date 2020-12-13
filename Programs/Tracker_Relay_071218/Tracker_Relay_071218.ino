#define programname "Tracker_Relay"
#define programversion "V1.2"
#define dateproduced "07/12/2018"
#define aurthorname "Stuart Robinson"
#include <Arduino.h>
/*
**************************************************************************************************

Easy Build Tracker Programs for Arduino ATMEGA328

Copyright of the author Stuart Robinson - 07/12/2018.

These programs may be used free of charge for personal, recreational and educational purposes only.

This program, or parts of it, may not be used for or in connection with any commercial purpose without
the explicit permission of the author Stuart Robinson.

The programs are supplied as is, it is up to individual to decide if the programs are suitable for the
intended purpose and free from errors.


To Do:


**************************************************************************************************
*/


                             
//#define Relay                                       //specify PCB type 
//#define Pro_Mini_Mikrobus_Shield
//#define Locator2
#define LCD_Receiver_Board

#include "Pin_Definitions.h"

//#define EnableSignalReport                          //select this option if relay is to send a signal report for the received packet
#define CalibrateTone                                 //comment in to have a calibrate tone at startup

#include <SPI.h>
#include "LoRa.h"

const float Frequency1 = 434.400;                     //relay listens on this frequency    
const float FreqOffset = 0.0;

const byte relay_Bandwidth = lora_BW62_5;             //LoRa settings for relay listen 
const byte relay_SpreadFactor = lora_SF8;            //LoRa settings for relay listen
const byte relay_CodeRate = lora_CR4_5;               //LoRa settings for relay listen
const byte relay_RateOptimisation = lora_LowDoptOFF;
const byte relay_Power = 10;
const char ThisNode = 'R';
const unsigned int Inter_Packet_Delay = 2000;          //delay from reception of packet to re-transmit


void loop()
{
  init_LoRa();
  lora_RXONLoRa();
  while (!lora_Read(lora_RegIrqFlags));
  checkforpacket();
}


void checkforpacket()
{
  //check if a packet has been received
  byte lora_Ltemp;

  lora_Ltemp = lora_Read(lora_RegIrqFlags);

  if (lora_Ltemp == 64)
  {
    lora_RXOFF();                                       //stop more packets coming in
    digitalWrite(PLED1, HIGH);
    Serial.print("Recieved Packet ");
    lora_PrintPacketInfo();                             //print the info on received packet
    Serial.println();
    delay(Inter_Packet_Delay);
    Serial.print("Re-Transmitting");
    lora_SendFIFO(lora_PacketL, 10, relay_Power);
    Serial.println(" - Done");
    digitalWrite(PLED1, LOW); 
    delay(Inter_Packet_Delay);

#ifdef EnableSignalReport
    digitalWrite(PLED1, HIGH);
    fill_FIFO_Signal_Report();
    Serial.print("Sending Signal Report");
    lora_SendFIFO(5, 10, relay_Power);
    Serial.println(" - Done");
    digitalWrite(PLED1, LOW);
#endif

  Serial.println();
  }

  if (lora_Ltemp == 96)
  {
    Serial.println();
    Serial.println(F("CRC Error"));
  }
}


void fill_FIFO_Signal_Report()
{
  //fills the LoRa FIFO with binary values for reception of last received packet
  lora_Write(lora_RegFifoTxBaseAddr, 0x00);
  digitalWrite(lora_PNSS, LOW);				//Set NSS low
  SPI.transfer(lora_WRegFifo);				//address for burst write
  SPI.transfer(bLinkReport);				//Write the packet type
  SPI.transfer('*');			                //Destination node
  SPI.transfer(ThisNode);				//Source node
  SPI.transfer(lora_PacketSNR);
  SPI.transfer(lora_PacketRSSI);
  digitalWrite(lora_PNSS, HIGH);			//finish the burst write
  lora_PacketL = 5;                                     //It is a 5byte packet
}


void led_Flash(unsigned int flashdelay, unsigned int flashes)
{
  //flash LED right at start so we can tell board is alive
  unsigned int i;

  for (i = 1; i <= flashes; i++)
  {
    
    delay(flashdelay);
    digitalWrite(PLED1, HIGH);
    delay(flashdelay);
    digitalWrite(PLED1, LOW);
  }
}


void init_LoRa()
{
  lora_Setup();                               //reset and initialise LoRa device
  lora_SetFreq(Frequency1, FreqOffset);       //set the operating frequency
  lora_SetModem(relay_Bandwidth, relay_SpreadFactor, relay_CodeRate, lora_Explicit, relay_RateOptimisation);	//setup the LoRa modem parameters
}


void setup()
{
  
  pinMode(PLED1, OUTPUT);                     //setup pin for PCB LED
  led_Flash(100, 5);

  Serial.begin(115200);                       //serial console ouput baud rate
  Serial.println(F(programname));
  Serial.println(F(programversion));
  Serial.println(F(dateproduced));
  Serial.println(F(aurthorname));

  pinMode(lora_PReset, OUTPUT);                //LoRa device reset line
  digitalWrite(lora_PReset, HIGH);               //enable
  pinMode (lora_PNSS, OUTPUT);                 //set the slave select pin as an output
  digitalWrite(lora_PNSS, HIGH);               //enable

  SPI.begin();                                 //initialize SPI
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  lora_Print();

  if (lora_CheckDevice() == 0)
  {
    Serial.println(F("Device Error"));
    while (1)
    {
      led_Flash(25, 10);
    }
  }

#ifdef CalibrateTone
  digitalWrite(PLED1, HIGH);
  init_LoRa();			                           //do the LoRa Setup
  Serial.println("Tone");
  lora_Tone(1000, 3000, relay_Power);          //transmit an FM tone, 1000hz, 3000ms
  digitalWrite(PLED1, LOW);
#endif
  Serial.println("Ready");
}


