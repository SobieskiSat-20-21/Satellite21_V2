#ifndef DUPLEX_C
#define DUPLEX_C

#include "run.h"
#include <stdbool.h>
#include "config.h"
#include "USB_com.h"

#include "sx1278.h"

bool transmitting;
uint8_t packetNumber;

static SX1278_config sx1278_default_config =
{
	433000000,			// radio frequency (d=61.035)[Hz]
	SX1278_POWER_17DBM,	// output power (11:20)[dBm]
	SX1278_SF_9,		// spreading factor (6:12)
	SX1278_CR_4_8,		// coding rate (5:8)
	SX1278_BW_125KHZ,	// bandwidth (8:500)[kHz]
	SX1278_CRC_DIS,		// verify packet checksum at reception
	500				// receive timeout [ms]
};


static void send_info_packet(void)
{
	SX1278_transmit(&(Common.radio), Common.radio.txBuffer, 9);
}

static bool duplex_setup(void)
{
	//(*Common.log_print)("*D00"); // [DUPLEX] Hello!
	#if RADIO_ENABLE
		Common.radio.reset = LR_RST_Pin;		Common.radio.reset_port = LR_RST_GPIO_Port;
		Common.radio.dio0 = LR_D0_Pin;			Common.radio.dio0_port = LR_D0_GPIO_Port;
		Common.radio.nss = LR_NSS_Pin;			Common.radio.nss_port = LR_NSS_GPIO_Port;
		Common.radio.spi = Get_SPI1_Instance();
		Common.radio.config = sx1278_default_config;
		Common.radio.useDio0IRQ = true;

		#if DUPLEX_DEBUG
			USBprintln("[DUPLEX] Initializing SX1278");
		#endif
		//(*Common.log_print)("*D01");

		uint8_t attempts = 0;
		while (!SX1278_init(&(Common.radio)))
		{
			if (++attempts > 5)
			{
				#if DUPLEX_DEBUG
					USBprintln("error: [DUPLEX] No connection with SX1278, radio is not active");
				#endif
				//(*Common.log_print)("*ED01");
				return false;
			}

			#if DUPLEX_DEBUG
				USBprintln("[DUPLEX] Init unsuccessful, retrying...");
			#endif
			delay(500);
		}
		#if DUPLEX_DEBUG
			USBprintln("[DUPLEX] Successful radio init");
		#endif
		//(*Common.log_print)("*D02");
		
		packetNumber = 1;
		transmitting = true;

		send_info_packet(); // Send packet to kickstart duplex
		return true;
	#else // RADIO_ENABLE
		#if DUPLEX_DEBUG
			USBprintln("warning: [DUPLEX] RADIO DISABLED!");
		#endif
		(*Common.log_print)("*WD00");
		Common.radio.active = false;
		return false;
	#endif
}

static bool duplex_checkINT(void)
{
	return ((Common.radio.pendingIRQ && HAL_GPIO_ReadPin(Common.radio.dio0_port, Common.radio.dio0) == HIGH) || SX1278_intTimeout(&(Common.radio)));
}

static void decodePacket()
{
	if (Common.radio.newPacket && Common.radio.rxBuffer[0] != 0)
	{
		uint32_t recv = Common.radio.rxBuffer[0];
		uint32_t valu = Common.radio.rxBuffer[1];
		//Servo
		if(recv == 1){
			if(valu==0){
				set_ang(90);
				writePin(LEDD,LOW);
			}
			else if(valu==1){
				set_ang(0);
				writePin(LEDD,HIGH);
			}
			else{
				set_ang(valu);
			}
		}
		//Parachute
		if(recv == 2){
			if(valu==0){
				writePin(LEDC,LOW);
				//openMotor(false,360);
			}
			else if(valu==1){
				writePin(LEDC,HIGH);
				////openMotor(true,360);
			}
		}
		//Set height
		if(recv == 3){
			if(valu==0){
				setHeight(0);
			}
			else if(valu==1){
				//groundAlt=(44331.5 - 4946.62 * pow((Common.bmp1->pressure*100),(0.190263)));
				setHeight((uint16_t)(44331.5 - 4946.62 * pow((Common.bmpTop->pressure*100),(0.190263))));
			}
		}
		//Control motor
		if(recv == 4){
			if(valu==0){
				////openMotor(false, 360);
			}
			else if(valu==1){
				////openMotor(true, 120);
			}
			else if(valu==2){
				////openMotor(true, 240);
			}
		}
	}
}

static void preparePacket()
{
	// format: TEMP-2, PRES-3, LAT-4, LON-4, ALT-2, YAW-1, PITCH-1, ROLL-1, SPS1-1, SPS10-1, OPMODE-1, PN-1
	uint32_t temv = 0;

	temv = (uint32_t)((Common.bmpTop->temperature + 10) * 1000);
	memcpy(Common.radio.txBuffer + 0, (uint8_t*)&temv, 3);	// 0:2

	temv = (uint32_t)(Common.bmpTop->pressure * 10000);
	memcpy(Common.radio.txBuffer + 3, (uint8_t*)&temv, 4);	// 3:7

	Common.radio.txBuffer[8]=packetNumber;

	Common.radio.txLen = 9;
}

static void duplex_loop(void)
{
	#if RADIO_ENABLE
		if (Common.radio.active && Common.radio.useDio0IRQ && duplex_checkINT())	// Manually check for interrupt
		{
			//&& duplex_checkINT()
			SX1278_dio0_IRQ(&(Common.radio));
			if (!transmitting)	// If in receiving mode: decode packet
			{
				decodePacket();
				#if DUPLEX_DEBUG
					if (Common.radio.rxTimeout)
					{
						USBprintln("[DUPLEX] Receive timeout.");
					}
				#endif
			}

			transmitting = true;

			if (packetNumber == 5)
			{
				SX1278_receive(&(Common.radio));
				#if DUPLEX_DEBUG
					if (Common.radio.rxTimeout)
					{
						USBprintln("[DUPLEX] Receive start.");
					}
				#endif
				packetNumber = 0;
				transmitting = false;
				return;
			}
			else
			{
				preparePacket();
				SX1278_transmit(&(Common.radio), Common.radio.txBuffer, Common.radio.txLen);	// Packet is written directly to memory buffer of the instance
				togglePin(LEDA);
				packetNumber++;
				return;
			}
		}
	#endif
	return;
}

#endif
