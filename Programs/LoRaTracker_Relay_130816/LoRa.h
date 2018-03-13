//LoRa.h
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
**************************************************************************************************
Constant definitions
**************************************************************************************************
*/

//LoRa names for bandwidth settings
const byte lora_BW7_8 = 0;      //7.8khz
const byte lora_BW10_4 = 16;    //10.4khz
const byte lora_BW15_6 = 32;    //15.6khz
const byte lora_BW20_8 = 48;    //20.8khz
const byte lora_BW31_2 = 64;    //31.2khz
const byte lora_BW41_7 = 80;    //41.7khz
const byte lora_BW62_5 = 96;    //62.5khz
const byte lora_BW125 = 112;    //125khz
const byte lora_BW250 = 128;    //250khz
const byte lora_BW500 = 144;    //500khz

//Spreading Factors
const byte lora_SF6 = 6;
const byte lora_SF7 = 7;
const byte lora_SF8 = 8;
const byte lora_SF9 = 9;
const byte lora_SF10 = 10;
const byte lora_SF11 = 11;
const byte lora_SF12 = 12;

//LORA names for coding rate settings
const byte lora_CR4_5 = 2;	//4:5
const byte lora_CR4_6 = 4;	//4:6
const byte lora_CR4_7 = 6;	//4:7
const byte lora_CR4_8 = 8;	//4:8

//LORA Header Settings
const byte lora_Explicit    = 0;	//Use to set explicit header
const byte lora_Implicit    = 1;	//Use to set implicit header

//Misc definitions
const byte lora_Deviation = 0x52;       //direct mode deviation
const byte lora_LowDoptON = 0x08;       //value to turn low data rate optimisation on
const byte lora_LowDoptOFF = 0x00;      //value to turn low data rate optimisation off


//SX1278 Register names
const byte lora_RegFifo = 0x00;
const byte lora_WRegFifo = 0x80;
const byte lora_RegOpMode = 0x01;
const byte lora_RegFdevLsb = 0x05;
const byte lora_RegFrMsb = 0x06;
const byte lora_RegFrMid = 0x07;
const byte lora_RegFrLsb = 0x08;
const byte lora_RegPaConfig = 0x09;
const byte lora_RegOcp = 0x0B;
const byte lora_RegLna = 0x0C;
const byte lora_RegFifoAddrPtr = 0x0D;
const byte lora_RegFifoTxBaseAddr = 0x0E;
const byte lora_RegFifoRxBaseAddr = 0x0F;
const byte lora_RegFifoRxCurrentAddr = 0x10;
const byte lora_RegIrqFlagsMask = 0x11;
const byte lora_RegIrqFlags = 0x12;
const byte lora_RegRxNbBytes = 0x13;
const byte lora_RegRxHeaderCntValueMsb = 0x14;
const byte lora_RegRxHeaderCntValueLsb = 0x15;
const byte lora_RegRxPacketCntValueMsb = 0x16;
const byte lora_RegRxPacketCntValueLsb = 0x17;
const byte lora_RegPktSnrValue = 0x19;
const byte lora_RegPktRssiValue = 0x1A;
const byte lora_RegRssiValue = 0x1B;
const byte lora_RegFsiMSB = 0x1D;
const byte lora_RegFsiLSB = 0x1E;
const byte lora_RegModemConfig1 = 0x1D;
const byte lora_RegModemConfig2 = 0x1E;
const byte lora_RegSymbTimeoutLsb = 0x1F;
const byte lora_RegPreambleLsb = 0x21;
const byte lora_RegPayloadLength = 0x22;
const byte lora_RegFifoRxByteAddr = 0x25;
const byte lora_RegModemConfig3 = 0x26;
const byte lora_RegPacketConfig2 = 0x31;
const byte lora_TXdefaultpower = 10;
const byte lora_RegPllHop = 0x44;

//Variables RX
byte  lora_PacketL;			//length of packet received, includes source, destination and packet type
byte  lora_PacketRSSI;			//RSSI of received packet
byte  lora_PacketSNR;			//signal to noise ratio of received packet

/*
**************************************************************************************************
Library Functions
**************************************************************************************************
*/

void lora_ResetDev()
{
  //resets the LoRa device
  digitalWrite(lora_PReset, LOW);	//take reset line low
  delay(5);
  digitalWrite(lora_PReset, HIGH);	//take it high
}


void lora_Write(byte lora_LReg, byte lora_LData)
{
  //write a byte to a LoRa register
  digitalWrite(lora_PNSS, LOW);		//set NSS low
  SPI.transfer(lora_LReg | 0x80);	//mask address for write
  SPI.transfer(lora_LData);		//write the byte
  digitalWrite(lora_PNSS, HIGH);	//set NSS high
}

byte lora_Read(byte lora_LReg)
{
  //read a byte from a LoRa register
  byte lora_LRegData;
  digitalWrite(lora_PNSS, LOW);		//set NSS low
  SPI.transfer(lora_LReg & 0x7F);	//mask address for read
  lora_LRegData = SPI.transfer(0);	//read the byte
  digitalWrite(lora_PNSS, HIGH);	//set NSS high
  return lora_LRegData;
}


void lora_SetFreq(float lora_LFreq, float lora_LOffset)
{
  //set the LoRa frequency
  lora_LFreq =  lora_LFreq + lora_LOffset;
  byte lora_LFMsb, lora_LFMid, lora_LFLsb;
  long lora_LLongFreq;
  lora_LLongFreq = ((lora_LFreq * 1000000) / 61.03515625);
  lora_LFMsb =  lora_LLongFreq >> 16;
  lora_LFMid = (lora_LLongFreq & 0x00FF00) >> 8;
  lora_LFLsb =  (lora_LLongFreq & 0x0000FF);
  lora_Write(lora_RegFrMsb, lora_LFMsb);
  lora_Write(lora_RegFrMid, lora_LFMid);
  lora_Write(lora_RegFrLsb, lora_LFLsb);
}


byte lora_CheckDevice()
{
  //check there is a device out there, program a frequency setting registers and read back
  byte lora_Lvar1;
  lora_Write(lora_RegFrMid, 0xAA);              //write test value
  lora_Lvar1 = lora_Read(lora_RegFrMid);        //read it back

  if (lora_Lvar1 == 0xAA)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


void lora_Setup()
{
  //initialise LoRa device registers and check its responding
  lora_ResetDev();				                //clear all registers to default
  lora_Write(lora_RegOpMode, 0x08);		                //RegOpMode, need to set to sleep mode before configure for LoRa mode
  lora_Write(lora_RegOcp, 0x2B);
}


byte lora_TXONDirect(byte lora_LTXPower)
{
  //turns on transmitter,in direct mode for FSK and audio  power level is from 2(dBm) to 17(dBm)
  lora_Write(lora_RegPaConfig, (lora_LTXPower + 0xEE));
  lora_Write(lora_RegOpMode, 0x0B);		                //TX on direct mode, low frequency mode
}


void lora_TXOFF()
{
  //turns off transmitter
  lora_Write(lora_RegOpMode, 0x08);                             //TX and RX to sleep, in direct mode
}


void lora_DirectSetup()
{
  //setup LoRa device for direct modulation mode
  lora_Write(lora_RegOpMode, 0x08);
  lora_Write(lora_RegPacketConfig2, 0x00);	                //set continuous mode
}


void lora_Tone(int lora_LFreq, int lora_LToneLen, int lora_LTXPower )
{
  //transmit an FM tone
  lora_DirectSetup();
  lora_Write(lora_RegFdevLsb, lora_Deviation);	               //LSB of deviation, 5kHz
  lora_TXONDirect(lora_LTXPower);		               //transmit on
  tone(lora_TonePin, lora_LFreq);
  delay(lora_LToneLen);
  noTone(lora_TonePin);
  lora_Write(lora_RegFdevLsb, 0);	                       //LSB of deviation, 5kHz
  lora_TXOFF();
}

void lora_SetModem(byte lora_LBW, byte lora_LSF, byte lora_LCR, byte lora_LHDR, byte lora_LLDROPT)
{
  lora_Write(lora_RegOpMode, 0x08);		               //RegOpMode, need to set to sleep mode before configure for LoRa mode
  lora_Write(lora_RegOpMode, 0x88);		               //goto LoRa mode
  lora_Write(lora_RegModemConfig1, (lora_LBW + lora_LCR + lora_LHDR));
  lora_Write(lora_RegModemConfig2, (lora_LSF * 16 + 7));
  lora_Write(lora_RegModemConfig3, lora_LLDROPT);
}


/*
**************************************************************************************************
Library Functions RX
**************************************************************************************************
*/


void lora_RXOFF()
{
  //turn receiver off
  lora_Write(lora_RegOpMode, 0x89);                                 //TX and RX to sleep, in direct mode
}


void lora_PrintPacketInfo()
{
  //print the information for packet last received
  byte lora_Lvar1;
  char lora_LChar;

  lora_PacketL = lora_Read(lora_RegRxNbBytes);
  lora_PacketRSSI = lora_Read(lora_RegPktRssiValue);
  lora_PacketSNR = lora_Read(lora_RegPktSnrValue);

  Serial.print(F("SNR,"));
  if (lora_PacketSNR > 127)
  {
    lora_Lvar1 =  (255 - lora_PacketSNR) / 4;
    lora_LChar = '-';
  }
  else
  {
    lora_Lvar1 = lora_PacketSNR / 4;
    lora_LChar = '+';
  }

  Serial.print(lora_LChar);
  Serial.print(lora_Lvar1);
  Serial.print(F("dB"));

  lora_Lvar1 = 137 - lora_PacketRSSI;
  Serial.print(F(",RSSI,-"));
  Serial.print(lora_Lvar1);
  Serial.print(F("dB"));
  Serial.print(F(",LEN,"));
  Serial.print(lora_PacketL);
}


void lora_RXONLoRa()
{
  //puts LoRa device into listen mode and receives packet into FIFO
  lora_Write(lora_RegOpMode, 0x09);
  lora_Write(lora_RegFifoRxBaseAddr, 0x00);
  lora_Write(lora_RegIrqFlagsMask, 0x9F);                          //only allow rxdone and crc error
  lora_Write(lora_RegIrqFlags, 0xFF);
  lora_Write(lora_RegOpMode, 0x8D);                                //go into RX mode
}


/*
**************************************************************************************************
Library Functions TX
**************************************************************************************************
*/


void lora_TXONLoRa(byte lora_LTXPower)
{
  //turns on LoRa transmitter, Sends packet, power level is from 2 to 17
  lora_Write(lora_RegPaConfig, (lora_LTXPower + 0xEE));			//set TX power
  lora_Write(lora_RegOpMode, 0x8B);					//transmit on in direct low frequency mode
}


void lora_SendFIFO(byte lora_LPacketL, long lora_LTXTimeout, byte lora_LTXPower)
{
  //send contents of FIFO,
  byte lora_LRegData;
  lora_Write(lora_RegOpMode, 0x09);
  lora_Write(lora_RegIrqFlags, 0xFF);
  lora_Write(lora_RegIrqFlagsMask, 0xF7);
  lora_Write(lora_RegPayloadLength, lora_LPacketL);
  lora_Write(lora_RegFifoTxBaseAddr, 0x00);
  lora_LTXTimeout = lora_LTXTimeout * 945;		                 //convert seconds to mS, delay in TX done loop is 1ms

  lora_TXONLoRa(lora_LTXPower);

  do
  {
    delay(1);
    lora_LTXTimeout--;
    lora_LRegData = lora_Read(lora_RegIrqFlags);
  }
  while (lora_LTXTimeout > 0 && lora_LRegData == 0) ;	                 //use a timeout counter, just in case the TX sent flag is missed
}

