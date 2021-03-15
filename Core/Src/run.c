#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "USB_com.h"
#include "config.h"
#include "bmp280.h"
#include "setup_scripts.h"

#include "main.h"
#include "clock.h"

//***** function declarations *****//
// static bool BMP280Setup(void);

bool oneTime = false;

void setup(void){
    groundAlt = 250;

    HAL_Delay(5000);
    writePin(LEDA, LOW);
    writePin(LEDB, LOW);
    writePin(LEDC, LOW);
    writePin(LEDD, LOW);
    
    bmpSetup();
    buzzerSetup();
    mpuSetup();
    HAL_Delay(10);

}

void loop(void){ 
    if(!bmp280_update(Common.bmpTop)){
        if(RUN_DEBUG) USBprintln("Top layer BMP does not update!");
    }

    if(!bmp280_update(Common.bmpBtm)){
        if(RUN_DEBUG) USBprintln("Bottpm layer BMP does not update!");
    }

    #if RUN_DEBUG
        altPressure = altFromPressure(Common.bmpTop->pressure);
        USBAddStringToBuffer("Top - Temperature: ");
        USBAddFloatToBuffer(Common.bmpTop->temperature);
        USBAddStringToBuffer(" Pressure: ");
        USBAddFloatToBuffer(Common.bmpTop->pressure);
        USBAddStringToBuffer(" Altitude: ");
        USBAddFloatToBuffer(altPressure);
        USBTPrintBuffer();

        altPressure = altFromPressure(Common.bmpBtm->pressure);
        USBAddStringToBuffer("Bottom - Temperature: ");
        USBAddFloatToBuffer(Common.bmpBtm->temperature);
        USBAddStringToBuffer(" Pressure: ");
        USBAddFloatToBuffer(Common.bmpBtm->pressure);
        USBAddStringToBuffer(" Altitude: ");
        USBAddFloatToBuffer(altPressure);
        USBTPrintBuffer();

        USBAddStringToBuffer(" Limit_1, 2: ");
        USBAddCharToBuffer((char)readPin(LIMIT_1) + '0');
        USBAddCharToBuffer(' ');
        USBAddCharToBuffer((char)readPin(LIMIT_2) + '0');
        USBTPrintBuffer();

        USBAddStringToBuffer("Current Frequency: ");
        USBAddLongToBuffer(Common.buzzer->frequency);
        USBTPrintBuffer();

        #endif

    
    if(readPin(LIMIT_1) && readPin(LIMIT_2)) {
        buzzerToggle(Common.buzzer);
    }

    if(readPin(LIMIT_1)){
        buzzerSetFrequency(Common.buzzer ,Common.buzzer->frequency + 100);
    }

    if(readPin(LIMIT_2)){
        buzzerSetFrequency(Common.buzzer, Common.buzzer->frequency - 100);
    }

    writePin(LEDA, Common.buzzer->state);
    writePin(LEDD, Common.buzzer->state);
    writePin(LEDB, readPin(LIMIT_1));
    writePin(LEDC, readPin(LIMIT_2));

}

float altFromPressure(float pressure){
    return ((44331.5 - 4946.62 * pow((pressure*100),(0.190263)))-groundAlt);
}

void setHeight(uint16_t a){
    groundAlt = a;
}

