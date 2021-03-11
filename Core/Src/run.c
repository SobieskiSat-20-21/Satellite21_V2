#include "run.h"
// #include "sensing_setup.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "USB_com.h"
#include "config.h"
#include "bmp280.h"
#include "sensing_setup.h"

#include "main.h"

//***** function declarations *****//
// static bool BMP280Setup(void);

bool oneTime = false;

void setup(void){
    groundAlt = 250;

    HAL_Delay(5000);
    writePin(LEDA, HIGH);
    writePin(LEDB, HIGH);
    
    
    sensingSetup();
    HAL_Delay(10);

    // if(!duplex_setup() && RUN_DEBUG) println("SX1278 NOT IN USE!");
    //else println("SX1278 IS OK");
    //prevMillis = millis();
}

void loop(void){ 
    if(!bmp280_update(Common.bmpTop)){
        if(RUN_DEBUG) USBprintln("Top layer BMP does not update!");
    }

    if(!bmp280_update(Common.bmpBtm)){
        if(RUN_DEBUG) USBprintln("Bottpm layer BMP does not update!");
    }

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


    HAL_Delay(1000);

    // duplex_loop();
    // println(Common.radio.txBuffer);

    // if(altPressure<100 && get_ang()==90 && oneTime==false){
    //     setAngle(-360);
    //     //openMotor(true, 360);
    //     oneTime=true;
    // }

    /*if(altPressure<100 && get_ang()==90)
    {
        if(motorOpen == false){
            prevMillis = millis();
            motorOpen = true;
        }
        enableMotor();
        writePin(LEDB, HIGH);
        //delay(4500);
        if(motorOpen ==true && millis()-prevMillis > 5){
            disableMotor();
            servoOpen = false;
        }
    }*/

    /*if(readPin(BTN_1))
    {
        setMotor();
        writePin(LEDD, HIGH);
    }
    else
    {
        writePin(LEDD, LOW);
        disableMotor();
        writePin(LEDC, HIGH);
    }/*

    /*char message[32];
    itoa(altPressure, message, 10);
    println(message);
    delay(16);
    if(millis() - prevMillis >= 500){
        prevMillis = millis();
        togglePin(LEDA);
    }*/

    //USBprintln(4, "T: ", temperature, " P: ", pressure);
    //USBprintln(2, "Alt: ", altPressure);

    //HAL_Delay(50);
}

float altFromPressure(float pressure){
    return ((44331.5 - 4946.62 * pow((pressure*100),(0.190263)))-groundAlt);
}

void setHeight(uint16_t a){
    groundAlt = a;
}

