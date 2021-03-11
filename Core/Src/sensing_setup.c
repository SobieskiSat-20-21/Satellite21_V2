// #ifndef SENSING_SETUP_H_
// #define SENSING_SETUP_H_

// #include <stdbool.h>
// #include "config.h"
// #include "USB_com.h"
// #include "run.h"

// #endif
#include "sensing_setup.h"

 // Contains the scripts for running sensor setup
 // BMPs, IMU, GPS
 
bool sensingSetup(void){
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
        #if RUN_DEBUG
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
        #if RUN_DEBUG
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

