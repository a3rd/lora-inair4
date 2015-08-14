/*************************************
Project: Pro Micro Arduino + LoRa iMod 4 Server
Data Rate : Determined by program
Frequency: 433Mhz
Modulation: LoRA
Transmit mode : continuous receive
*************************************/

#include <SoftwareSerial.h>

/*************************************
Software Serial Setup
Data Rate : 9600bps
Pinouts: RX (yellow wire) -> TXO (pin 0), TX (red wire) -> RX0, GNd (Blue) -> GND
Transmit mode : continuous transmit
*************************************/

SoftwareSerial console(1, 0);    // RX, TX


unsigned char mode; //lora --1 / FSK --0
unsigned char Freq_Sel; //
unsigned char Power_Sel; //
unsigned char Lora_Rate_Sel; //
unsigned char BandWide_Sel; //
unsigned char Fsk_Rate_Sel; //


/*
Pro Micro Pintouts

SCK 	15          
MOSI	16         
MISO	14
RESET 	A3, 21
DIO0 / D5	A2, 20
NSEL / CS       A0, 18
LED / D14 	A1, 19	



*/

// Pinout for Arduino Pro Micro
// 
//
//
//

int led = 19; 					// Pro Micro P19, A1, D14
int nsel = 18;					// Pro Micro P18, A0, 	SX1278	CS
int sck = 15;
int mosi = 16;
int miso = 14;
int dio0 = 20;
int reset = 21;

// Define Modes
#define SX1278_MODE_RX_CONTINUOUS			        0x00
#define SX1278_MODE_TX						0x00
#define SX1278_MODE_SLEEP					0x00
#define SX1278_MODE_STANDBY					0x00

// System Definitions for SX1278
// Filename : SX1278.h


#define 	CRC_4_5
/*
#ifdef	CR_4_5
	#define	CR	0x01
#else
	#ifdef	CR_4_6
	  #define	CR	0x02
	#else
	  #ifdef	CR_4_7
	    #define	CR	0x03
	  #else
	    #ifdef	CR_4_8
	      #define	CR	0x04
	    #endif
	  #endif
	#endif
#endif
*/

#define   CR    0x01

#define      CRC_EN

#ifdef      CRC_EN
  #define   CRC    0x01
#else
  #define  CRC    0x00
#endif

#define	LR_RegFifo 	0x00
#define	LR_RegOpMode 	0x01
#define	LR_RegFrMsb 	0x06
#define	LR_RegFrMid 	0x07
#define	LR_RegFrLsb 	0x08
#define	LR_RegPaConfig 	0x09
#define	LR_RegPaRamp 	0x0A
#define	LR_RegOcp 	0x0B
#define	LR_RegLna 	0x0C
#define	LR_RegFifoAddrPtr 	0x0D
#define	LR_RegFifoTxBaseAddr	0x0E
#define	LR_RegFifoRxBaseAddr	0x0F
#define	LR_RegFifoRxCurrentAddr	0x10
#define	LR_RegIrqFlagsMask	0x11
#define	LR_RegIrqFlags 	0x12
#define	LR_RegRxNbBytes 	0x13
#define	LR_RegRxHeaderCntValueMsb	0x14
#define	LR_RegRxHeaderCntValueLsb	0x15
#define	LR_RegRxPacketCntValueMsb	0x16
#define	LR_RegRxPacketCntValueLsb	0x17
#define	LR_RegModemStat 	0x18
#define	LR_RegPktSnrValue 	0x19
#define	LR_RegPktRssiValue 	0x1A
#define	LR_RegRssiValue 	0x1B
#define	LR_RegHopChannel 	0x1C
#define	LR_RegModemConfig1	0x1D
#define	LR_RegModemConfig2	0x1E	
#define	LR_RegSymbTimeoutLsb	0x1F
#define	LR_RegPreambleMsb 	0x20
#define	LR_RegPreambleLsb 	0x21
#define	LR_RegPayloadLength 	0x22
#define	LR_RegMaxPayloadLength	0x23
#define	LR_RegHopPeriod 	0x24
#define	LR_RegFifoRxByteAddr	0x25
	
#define	REG_LR_DIOMAPPING1	0x40
#define	REG_LR_DIOMAPPING2	0x41
	
#define	REG_LR_VERSION	0x42
	
#define	REG_LR_PLLHOP	0x44
#define	REG_LR_TCX0	0x4B
#define	REG_LR_PADAC	0x4D
#define	REG_LR_FORMERTEMP	0x5B
	
#define	REG_LR_AGCREF	0x61
#define	REG_LR_AGCTHRESH1	0x62
#define	REG_LR_AGCTHRESH1	0x62
#define	REG_LR_AGCTHRESH3	0x64

	
#define	RegFIFO	0x00
#define	RegOpMode	0x01
#define	RegBitRateMsb	0x02
#define	RegBitRateLsb	0x03
#define	RegFdevMsb	0x04
#define	RegFdevLsb	0x05
#define	RegFreqMsb	0x06
#define	ReqFreqMid	0x07
#define	RegFreqLsb	0x08
#define	RegPaConfig	0x09
#define	RegPaRamp	0x0A
#define	RegOcp	0x0B
#define	RegLna	0x0C
#define	RegRxConfig	0x0D
#define	RegRssiConfig	0x0E
#define	RegRssiCollision	0x0F
#define	RegRssiThresh	0x10
#define	RegRssiValue	0x11
#define	RegRxBw	0x12
#define	RegAfcBw	0x13
#define	RegOokPeak	0x14
#define	RegOokFix	0x15
#define	RegOokAvg	0x16
	
#define	RegAfcFei	0x1A
#define	RegAfcMsb	0x1B
#define	RegAfcLsb                               0x1C
#define	RegFeiMsb                               0x1D
#define	RegFeiLsb                               0x1E
#define	RegPreambleDetect                       0x1F
#define	RegRxTimeout1                           0x20
#define	RegRxTimeout2                           0x21
	                                 	
#define	RegRxTimeout3                           0x22
	                                       	
#define	RegRxDelay                              0x23
#define	RegOsc                                  0x24
	                                       	
#define	RegPreambleMsb                          0x25
#define	RegPreambleLsb                          0x26
	                                       	
#define	RegSyncConfig                           0x27
#define	RegSyncValue1                           0x28
#define	RegSyncValue2                           0x29
#define	RegSyncValue3                           0x2A
#define	RegSyncValue4                           0x2B
#define	RegSyncValue5                           0x2C
	                                       	
#define	RegSyncValue6                           0x2D
#define	RegSyncValue7                           0x2E
#define	RegSyncValue8                           0x2F
#define	RegPacketConfig1                        0x30
#define	RegPacketConfig2                        0x31
	                                       	
#define	RegPayloadLength                        0x32
#define	RegNodeAdrs                             0x33
#define	RegBroadcastAdrs                        0x34
#define	RegFifoThresh                           0x35
	                                       	
#define	RegSeqConfig1                           0x36
#define	RegSeqConfig2                           0x37
	                                       	
#define	RegTimerResol                           0x38
#define	RegTimer1Coef                           0x39
#define	RegTimer2Coef                           0x3A
#define	RegImageCal                             0x3B
	                                       	
#define	RegTemp                                 0x3C
#define	RegLowBat                               0x3D
#define	RegIrqFlags1                            0x3E
	                                       	
#define	RegIrqFlags2                            0x3F
	                                       	
#define	RegDioMapping1                          0x40
#define	RegDioMapping2                          0x41
#define	RegVersion                              0x42
#define	RegPllHop                               0x44
                                        	
#define	RegPaDac                                0x4D



void SPICmd8bit(unsigned char WrPara)
{
	unsigned char bitcnt;
	
	digitalWrite(nsel, LOW);
	
	digitalWrite(sck, LOW);
	
	for (bitcnt=8; bitcnt != 0; bitcnt--)
	{
		digitalWrite(sck, LOW);
	
			if (WrPara&0x80) {
				digitalWrite(mosi, HIGH);
				}
			else {
				digitalWrite(mosi, LOW);
				}
		
		digitalWrite(sck, HIGH);
		WrPara <<= 1;
	}
	
	digitalWrite(sck, LOW);
	digitalWrite(mosi, HIGH);
}	
	
unsigned char SPIRead8bit(void)
{
	unsigned char RdPara = 0;
	unsigned char bitcnt;
	
	digitalWrite(nsel, LOW);
	digitalWrite(mosi, HIGH);
	
	for ( bitcnt=8; bitcnt !=0; bitcnt--) {
		digitalWrite(sck, LOW);
		RdPara <<= 1;
		digitalWrite(sck, HIGH);
	
		if(digitalRead(miso)) {
			RdPara |= 0x01;
			}
		else {
			RdPara |= 0x00;
			}
			
	}
	digitalWrite(sck, LOW);
	return(RdPara);
}


unsigned char SPIRead(unsigned char adr)
{
	unsigned char tmp;
	SPICmd8bit(adr);
	tmp = SPIRead8bit();
	digitalWrite(nsel, HIGH);
	return(tmp);
}


void SPIWrite(unsigned char adr, unsigned char WrPara)
{
	digitalWrite(nsel, LOW);
	SPICmd8bit(adr|0x80);
	SPICmd8bit(WrPara);
	
	digitalWrite(sck, LOW);
	digitalWrite(mosi, HIGH);
	digitalWrite(nsel, HIGH);
}


void SPIBurstRead(unsigned char adr, unsigned char *ptr, unsigned char leng)
{
	unsigned char i;
		if (leng<=1) {
			return;
		}
		else {
			digitalWrite(sck, LOW);
			digitalWrite(nsel, LOW);
			SPICmd8bit(adr);
	
			for (i=0; i<leng; i++ ) {
				ptr[i] = SPIRead8bit();
			}
			
			digitalWrite(nsel, HIGH);
		}
}


void BurstWrite(unsigned char adr, unsigned char *ptr, unsigned char leng)
{
	unsigned char i;
	
	if (leng <= 1) {
		return;
	}
	else {
	digitalWrite(sck, LOW);
	digitalWrite(nsel, LOW);
	SPICmd8bit(adr|0x80);
	
		for (i=0; i<leng; i++) {
			SPICmd8bit(ptr[i]);
		}
	digitalWrite(nsel, HIGH);
	}
}

	
	// Parameter Table Definition

unsigned char sx1278FreqTbl[1][3] =
{
	{ 0x6C, 0x80, 0x00}, //434Mhz
};


unsigned char sx1278PowerTbl[4] =
{
	0xFF,
	0xFC,
	0xF9,
	0xF6,
};


unsigned char sx1278SpreadFactorTbl[7] =
{
	6,7,8,9,10,11,12
};	


unsigned char sx1278LoRaBwTbl[10] =
{
	0,1,2,3,4,5,6,7,8,9		// 7.8Khz, 10.4KHz, 15.6KHz, 20.8KHz, 31.2KHz, 41.7KHz, 62.5KHz, 125KHz, 250KHz, 500KHz
};


unsigned char sx1278Data[] = {"SX1278 Test Module"};

unsigned char RxData[64];

	
void sx1278_Standby(void)
{
	SPIWrite(LR_RegOpMode, 0x09);	// Standby & Low Frequency mode
	// SPIWrite(LR_RegOpMode, 0x01);	// standby high frfequency mode
}	

void sx1278_Sleep(void)	
{	
	SPIWrite(LR_RegOpMode, 0x08); 	// Sleep & Low Frequency mode
	// SPIWrite(LR_RegOpMode, 0x00); 	// Sleep / high frequency mode
	
}	

void sx1278_EntryLoRa(void)
{
	SPIWrite(LR_RegOpMode, 0x88); 	// Low frequency mode
	// SPIWrite(LR_RegOpMode, 0x80); 	// Sigh frequency mode
}

void sx1278_LoRaClearIrq(void)
{
	SPIWrite(LR_RegIrqFlags, 0xFF);
}


unsigned char sx1278_LoRaEntryRx(void)
{
	unsigned char addr;
	console.println("Enter sx76 Config");
	sx1278_Config();	// setting base parater
	
	SPIWrite(REG_LR_PADAC, 0x84 );
	SPIWrite(LR_RegHopPeriod, 0xFF);
	SPIWrite(REG_LR_DIOMAPPING1, 0x01 );
	
	SPIWrite(LR_RegIrqFlagsMask, 0x3f);
	
	sx1278_LoRaClearIrq();
	
	SPIWrite(LR_RegPayloadLength, 21);
	
	addr = SPIRead(LR_RegFifoRxBaseAddr);
	
	SPIWrite(LR_RegFifoAddrPtr, addr);
	SPIWrite(LR_RegOpMode, 0x8d);			// Set the Operating Mode to Continuos Rx Mode && Low Frequency Mode
	
    while (1) 	{
			if ((SPIRead(LR_RegModemStat) & 0x04) == 0x04) {
				break;
            }    
				return 0;    
	}
}	


unsigned char sx1278_LoRaReadRSSI(void)
{
	unsigned int temp = 10;
	temp = SPIRead(LR_RegRssiValue);
	temp = temp + 127 - 137;
	return (unsigned char) temp;
}



unsigned char sx1278_LoRaRxPacket (void)
{
	unsigned char i;
	unsigned char addr;
	unsigned char packet_size;
	
        	
	if (digitalRead(dio0)) 	{
	       console.println("DIO_0 shows packet recieved");
		
        	for (i = 0; i < 32; i++ ) {
				RxData[i] = 0x00;
			}
	
	addr = SPIRead(LR_RegFifoRxCurrentAddr);
	SPIWrite(LR_RegFifoAddrPtr, addr);		// RXBaseAddr --> FiFoAddrPtr
	
	if (sx1278SpreadFactorTbl[Lora_Rate_Sel] == 6 ) {
		packet_size = 21;
	} else {
		packet_size = SPIRead(LR_RegRxNbBytes);
		}
	
	SPIBurstRead(0x00, RxData, packet_size);
	
	sx1278_LoRaClearIrq();
	
	for ( i = 0; i< 17; i++ ) {
		if (RxData[i] != sx1278Data[i] ) break;
	}
	
	if ( i > 17 ) {
		return (i);
	} else return (0);
	
	}
	else return(0); // if !(digitalRead(dio0) --> this is important for recieving packets
}


unsigned char sx1278_LoRaEntryTx(void)
{
	unsigned char addr, temp;
	
	sx1278_Config();	// setting base parater
	
	SPIWrite(REG_LR_PADAC, 0x87 );
	SPIWrite(LR_RegHopPeriod, 0x00);
	SPIWrite(REG_LR_DIOMAPPING1, 0x41 );
	
	sx1278_LoRaClearIrq();
	SPIWrite(LR_RegIrqFlagsMask, 0xF7);
	SPIWrite(LR_RegPayloadLength, 21);
	
	addr = SPIRead(LR_RegFifoTxBaseAddr);
	
	SPIWrite(LR_RegFifoAddrPtr, addr);
	
	while (1) {
		temp = SPIRead(LR_RegPayloadLength);
		if (temp==21) break;
	}
	
}
	
unsigned char sx1278_LoRaTxPacket(void)
{
	unsigned char TxFlag = 0;
	unsigned char addr;
	
	BurstWrite(0x00, (unsigned char *)sx1278Data, 21);
	SPIWrite(LR_RegOpMode, 0x8b);
	
	while(1) {
		if (digitalRead(dio0)) 	{
			SPIRead(LR_RegIrqFlags);
			sx1278_LoRaClearIrq();
			sx1278_Standby();
			break;
		}
	}
}

unsigned char sx1278_ReadRSSI(void)
{
	unsigned char temp = 0xff;
	
	temp = SPIRead(0x11);
	temp >>= 1;
	temp = 127 - temp;
	return temp;
}





void sx1278_Config(void) {
	unsigned char i;
	sx1278_Sleep();		// modem must be in sleep mode
	
//	for ( i = 250; i!= 0; i-- );
	for ( i = 250; i!= 0; i-- )
        {
	delay(15);
	}

	//lora mode
	sx1278_EntryLoRa();
	
	//SPIWrite(0x5904); // change digital regulator from 1.6V to 1.47V: see errata note
	
	BurstWrite(LR_RegFrMsb, sx1278FreqTbl[Freq_Sel],3); //set the frequency parameter
	
	// set the base parameters
	
	SPIWrite(LR_RegPaConfig, sx1278PowerTbl[Power_Sel]); // set the output power parameter
	
	SPIWrite(LR_RegOcp, 0x0B); 
	SPIWrite(LR_RegLna, 0x23);
	
	if(sx1278SpreadFactorTbl[Lora_Rate_Sel]==6)
	{	
		unsigned char tmp;
		
		SPIWrite(LR_RegModemConfig1, ((sx1278LoRaBwTbl[BandWide_Sel] << 4)+(CR<<1)+0x01));
		// Implicit Enable CRC Enable (0x02) & Error Coding rate 4/5 (0x01), 4/6 (0x02), 4/7 (0x03), 4/8 (0x04)
	
		SPIWrite(LR_RegModemConfig2, ((sx1278SpreadFactorTbl[Lora_Rate_Sel]<<4)+(CRC<<2)+0x03));
		
		tmp = SPIRead(0x31);
		tmp &= 0xF8;
		tmp |= 0x05;
		SPIWrite(0x31,tmp);
		SPIWrite(0x37, 0x0C);
	}
	
	else
	{
          	console.println("config - elseif loop");
  		SPIWrite(LR_RegModemConfig1,((sx1278LoRaBwTbl[BandWide_Sel] <<4 )+(CR<<1)+0x00));
		SPIWrite(LR_RegModemConfig2, ((sx1278SpreadFactorTbl[Lora_Rate_Sel]<<4)+ (CRC<<2)+0x03));
	}
	
	SPIWrite(LR_RegSymbTimeoutLsb, 0xFF);
	
	SPIWrite(LR_RegPreambleMsb, 0x00);
	
	SPIWrite(LR_RegPreambleLsb, 12);
	
	SPIWrite(REG_LR_DIOMAPPING2, 0x01);
	
	sx1278_Standby();
        console.print("Config - finished method, forced Opmde to Standby, opmode is now : ");
        console.print(SPIRead(LR_RegOpMode));
        
        
}	
	
	
void setup() {
    pinMode(led, OUTPUT);
    pinMode(nsel, OUTPUT);
    pinMode(sck, OUTPUT);
    pinMode(mosi, OUTPUT);
    pinMode(miso, OUTPUT);
    pinMode(reset, OUTPUT);
    
    Serial.begin(9600);
    console.begin(9600);
    console.println("Software Serial Port Connected");
    console.print("OPmode is ");
    console.print(SPIRead(LR_RegOpMode), HEX);
    console.print("\n");
    
}    


void loop() {
// this is the main code to run repeatedly
	mode 			= 0x01; 	//lora mode
	Freq_Sel 		= 0x00; 	//433Mhz
	Power_Sel 		= 0x00; 	//
	Lora_Rate_Sel 	= 0x06;
	BandWide_Sel 	= 0x07;
	Fsk_Rate_Sel 	= 0x00;
	
       
    sx1278_Config();

    
	sx1278_LoRaEntryRx();
    
	digitalWrite(led, HIGH); 	// turn the LED on
	delay(500); 				// wait for 500ms
	digitalWrite(led, LOW); 	// turn the LED off
	delay(500);					// wait for 500ms
	
    int loopCnt = 0;
	while(1)
	{
	// Master
	       	char opMode = SPIRead(LR_RegOpMode);
                 console.println(" ");
                 console.print("OpMode Reg Value ");
                 console.print(opMode, HEX);

                 switch(opMode){
                   case  0:
                      console.println("OPMode is SLEEP");
                      break;
                   case 1:
                      console.println("OPMode is STANDBY");
                      break;
                 }
                      
                    
                 console.println(" ");
                 
                 if (opMode == 0){
                     SPIWrite(LR_RegOpMode, B00010001);
                     console.println("Forcing OPMode to STANDBY");
                     delay(1000);                
                     console.print("OPMOde is now : ");
                     console.print(SPIRead(LR_RegOpMode), HEX);
                     delay(3000);
                 }
                 
                digitalWrite(led, HIGH);
                delay(200);
                console.print(loopCnt);
                console.print(": Check Lora Entry Tx \n");
		sx1278_LoRaEntryTx();
                console.print(loopCnt);
                console.print(": Check Lora TX packet \n");
		sx1278_LoRaTxPacket();
		digitalWrite(led, LOW);
		sx1278_LoRaEntryRx();
		delay(200);
		loopCnt++;
                
                for (int i=0;i<26;i++){
                  sx1278Data[i] = char(0x61 + i);
                }
              
}
}












