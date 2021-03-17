// #ifndef SENSING_SETUP_H_
// #define SENSING_SETUP_H_

// #include <stdbool.h>
// #include "config.h"
// #include "USB_com.h"
// #include "run.h"

// #endif
#include "setup_scripts.h"
#include "clock.h"
#include "main.h"
#include "gps.h"
#include "config.h"

 // Contains the scripts for running sensor setup
 // BMPs, IMU, GPS
 
bool bmpSetup(void){
    bool report = true;
    bool singularInit = false;

 //*** TOP BMP280 ***//
    #if BMP_TOP_ENABLE
        bmpTop.i2c = I2C2_Handler();
        // watch out for this sucker
        // took me some time and an oscilloscope to figure the bit shifting out
        // will be 0x77 if the address pin is pulled HIGH
        bmpTop.i2c_addr = BMP280_TOP_I2C_ADDRESS;
        Common.bmpConfig = &bmp280_default_config;
        Common.bmpTop = &bmpTop;
        singularInit = bmp280_init(Common.bmpTop, Common.bmpConfig);
        #if SENSING_DEBUG
            if(singularInit) {
                USBprintln("Top layer BMP is working");
            }
            else {
                USBprintln("Top layer BMP is NOT working");
            }
        #endif
        report &= singularInit;
    #endif

 //*** BOTTOM BMP280 ***//
    #if BMP_BTM_ENABLE
        bmpBtm.i2c = I2C2_Handler();
        // watch out for this sucker
        // took me some time and an oscilloscope to figure the bit shifting out
        // will be 0x77 if the address pin is pulled HIGH
        bmpBtm.i2c_addr = BMP280_BTM_I2C_ADDRESS;
        Common.bmpConfig = &bmp280_default_config;
        Common.bmpBtm = &bmpBtm;
        singularInit = bmp280_init(Common.bmpBtm, Common.bmpConfig);
        #if SENSING_DEBUG
            if(singularInit) {
                USBprintln("Bottom layer BMP is working");
            }
            else {
                USBprintln("Bottom layer BMP is NOT working");
            }
        #endif
        report &= singularInit;
    #endif
    
    return report;
}

bool mpuSetup(void){
    #if MPU_ENABLE

    uint8_t attempts = 0;

    mpu.i2c_addr = MPU9250_I2C_ADDRESS;
    mpu.i2c_addr_ak = AK8963_I2C_ADDRESS;
    mpu.i2c = I2C2_Handler();


    #if SENSING_DEBUG
	    USBprintln("[SENSING] Initializing MPU9250");
	#endif

    while (!MPU9250_present(&mpu))
		{
			if (++attempts > 5)
			{
				#if SENSING_DEBUG
					USBprintln("error: [SENSING] No connection with MPU9250, no IMU data will be avaliable");
				#endif
				mpu.active = false;
				break;
			}
			delay(500);
        }
        
    if (mpu.active)
		{
			#if SENSING_DEBUG
				USBprintln("[SENSING] Initializing AK8963");
			#endif

			while (!AK8963_present(&(mpu)) && false) //####################
			{
				if (++attempts > 5)
				{
					#if SENSING_DEBUG
						USBprintln("error: [SENSING] No connection with AK8963, no IMU data will be avaliable");
					#endif

					mpu.active = false;
					break;
				}

				delay(500);
				#if SENSING_DEBUG
					USBprintln("[SENSING] AK8963 init unsuccesfull, retrying...");
				#endif
			}
		}

        if (mpu.active)
		{	
			#if SENSING_DEBUG
					USBprintln("[SENSING] Checking MPU9250 readings. Don't move the board!");
			#endif

			attempts = 0;
			writePin(LEDA, HIGH);
			delay(500);
			while (!MPU9250_SelfTest(&(mpu)))
			{
				if (++attempts > 5)
				{
					#if SENSING_DEBUG
						USBprintln("warning: [SENSING] MPU9250 SelfTest not passed, performance issues may occur");
					#endif
					break;
				}
				
				delay(500);
				#if SENSING_DEBUG
					USBprintln("[SENSING] MPU9250 SelfTest failed, retrying...");
				#endif
			}
			if (mpu9250_default_config.calibrate)
			{
				#if SENSING_DEBUG
					USBprintln("[SENSING] Performing MPU9250 calibration. Don't move the board!");
				#endif
			}
			else
			{
				#if SENSING_DEBUG
					USBprintln("warning: [SENSING] Skipping IMU calibration!");
				#endif
			}

			MPU9250_init(&(mpu), &mpu9250_default_config);
			writePin(LEDA, LOW);
			writePin(LEDB, HIGH);
			if (mpu9250_default_config.calibrate)
			{
				#if SENSING_DEBUG
					USBprintln("[SENSING] Performing AK8963 calibration. Rotate the board.");
				#endif
			}
			AK8963_init(&(mpu), &mpu9250_default_config);
			writePin(LEDB, LOW);
		}
	#else
		#if SENSING_DEBUG
			USBprintln("warning: [SENSING] MPU9250 DISABLED!");
		#endif
		mpu.active = false;    

    #endif

    Common.mpu = &mpu;

}

bool buzzerSetup(void){
    #if BUZZER_ENABLE

    Common.buzzer = &defaultBuzzer;
    buzzerDefaultInit(Common.buzzer);

    #endif
    return BUZZER_ENABLE;
}

bool gpsSetup(void){
	#if GPS_ENABLE
		uint8_t attempts = 0;
		gps.uart = Get_UART1_Instance();
		#if SENSING_DEBUG
			USBprintln("[SENSING] Initializing L86");
		#endif

		while (!GPS_init(&gps))
		{
			if (++attempts > 5)
			{
				#if SENSING_DEBUG
					USBprintln("error: [SENSING] No connection with L86, no GPS data will be avaliable");
					return false;
				#endif
				break;
			}

			delay(500);
			#if SENSING_DEBUG
				USBprintln("[SENSING] L86 init unsuccesfull, retrying...");
			#endif
		}
		gps.active = true; //######################
		gps.paused = false;
		if (gps.active && !gps.fix)
		{
			gps.latitudeDegrees = DEFAULT_LAT;
			gps.longitudeDegrees = DEFAULT_LONG;
			gps.altitude = DEFAULT_ALT;
		}
	#else
		#if SENSING_DEBUG
			USBprintln("warning: [SENSING] L86 DISABLED!");
		#endif
		gps.active = false;
	#endif

	Common.gps = &gps;
	return true;
}