# InAir4 Setup 


##InAir4 Pinouts

The InAir4 module is manufactuered by Modtronix, and with a Semtech SX1278 (SX1276) LoRa Module, set to __433MHz__, 3.3V input, SMA Connector. Modtronix has a range of antennas that can be used with the LoRa module that are avialable as well.

http://modtronix.com/inair4.html

The pins are labelled as follows. Make sure that the model is inAir4 - this should be printed on the PCB.

|()||()|
|:------:|:------:|:------:|
|GND| |NC|
|CS| |3.3V|
|DIO3| |SCK|
|RST| |MISO|
|DIO0| |MOSI|
|DIO1||NC|
|DIO2||VSWITCH|


###Pinout Description
|Label|Function|
|--------|--------:|
| GND	 | Ground PIN |  
| CS	 | Chip Select |  	
| DIO3	 | Digital Input / Output (3) |		
| RST	 |	Reset Pin |	
| DIO0 	 | Digital Input / Output (0) |		
| DIO1 	 | Digital Input / Output (1) |		
| DIO2 	 | Digital Input / Output (2)		
|	  |  	|
| NC	 | Not Connected | 	
| 3.3V	 | Vin, 3.3VDC  |	
| SCK	 |	SPI Clock	|
| MISO	 |	SPI MISO	|
| MOSI 	 | SPI MOSI		|
| NC 	 |	Not Connected |	
| VSWITCH 	 |		VSWITCH |

###Module Image

![inAir4 Image](https://cloud.githubusercontent.com/assets/6830154/9263753/1c1a8d3c-4263-11e5-8cd1-7023b1fc0c16.jpg )

###Bottom View

![inAir4 Bottom View](https://cloud.githubusercontent.com/assets/6830154/9263729/e834d1e4-4262-11e5-9c69-55152146cd1b.jpg )

###Pin Layout

![inAir4 Pin Layout](ttps://cloud.githubusercontent.com/assets/6830154/9263731/ece3c20e-4262-11e5-90cd-973d31fcff24.gif )

###Schematic 

![inAir4 Schematic](https://cloud.githubusercontent.com/assets/6830154/9263723/d29a771c-4262-11e5-85eb-6f83b0d87d32.jpg )

##Setting up the LoRa InAir4 Module with Arduino Pro Micro

The example code in this repo using GPIOs that can be configured accordingly, here we are using the Arduino Pro Micro.

To keep things simple the pins are wired as follows:

|ProMicro|()||()|ProMicro|
|:------:|:------:|:------:|:------:|:------:|
|**GND** |GND| |NC||
|**18**|CS| |3.3V|**3.3VDC**|
||?| |SCK|**SCK**|
|**21**|RST| |MISO|**MISO**|
||?| |MOSI|**MOSI**|
||?||NC||
|**20**|DIO2||VSWITCH|**3.3VDC**|


This can be found in the example code where the pins are configured as follows:

<code>SCK 	15</code> 

<code>MOSI	16 </code> 

<code>MISO	14</code>

<code>RESET 	21</code>

<code>DIO0 	20</code>

<code>NSEL    18</code>

<code>LED 	19	</code>


##Concept of Operation

There are two Arduino Pro Micros, each with a InAir4 module connected as per the pinouts above. One should be programmed as the lora-client and one should be programmed as the lora-server.

There are two ways to monitor the inAir4 modules,
1. Through the USB serial port, 9600 8N1 _or_
2. Through the console port. This is using a USB <--> 3.3V level cable, connected to pins 1,2 & GND

The code can be easily altered to have hte debug messages come to the _serial_ instead of the _console_ . A simple find and replace can make this change.

###Registers
On power up there is some communication back and forth between the arduino and the inAir4. This can be used to confirm that the power is wired correctly and the SPI interface is functioning.

###Config 
sx1278_Config() sets all the registers as requried. Just about everything is fixed - including the frequency at 433Mhz. Before changing any settings its recommended that the two units are tested at short range with the default settings.

###Setup
After config it goes to sx1278_Setup() which configures all the GPIO pins. This is self explanatory.

###Loop
In the main loop the code will force the lora-client into RX_continuous mode, and the lora-server into TX mode. An arbitary message is loaded into the TX buffer that should be sent out the first time around then after a shortly delay the TX buffer is rewritten with the alphabest. 

The contains of the opmode register and RX buffer are continually output, so all changes to the data transmission should be seen there.




