# InAir4 Setup 

## InAir4 Pinouts

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


## Pinout Description
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

## Module Image

![inAir4 Image](https://cloud.githubusercontent.com/assets/6830154/9263753/1c1a8d3c-4263-11e5-8cd1-7023b1fc0c16.jpg [height=2in])

## Bottom View

![inAir4 Bottom View](https://cloud.githubusercontent.com/assets/6830154/9263729/e834d1e4-4262-11e5-9c69-55152146cd1b.jpg [height=2in])

##Pin Layout

![inAir4 Pin Layout](ttps://cloud.githubusercontent.com/assets/6830154/9263731/ece3c20e-4262-11e5-90cd-973d31fcff24.gif [height=2in])

## Schematic 

![inAir4 Schematic](https://cloud.githubusercontent.com/assets/6830154/9263723/d29a771c-4262-11e5-85eb-6f83b0d87d32.jpg [height=2in])

# Setting up the LoRa InAir4 Module with Arduino Pro Micro

The InAir4 module is manufactuered by Modtronix, and with a Semtech SX1278 (SX1276) LoRa Module, set to __433MHz__, 3.3V input, SMA Connector. Modtronix has a range of antennas that can be used with the LoRa module that are avialable as well.

[http://modtronix.com/inair4.html]

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

