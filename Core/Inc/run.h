#ifndef _RUN_H_
#define _RUN_H_

#include "main.h"

#include <stdlib.h>
#include <string.h>
#include "USB_com.h"

#include "bmp280.h"
#include "config.h"
#include "buzzer.h"
#include "mpu9250.h"


// this struct will hold all data about sensors
// its point is to be able to quickly change individual
// sensor structs just by changing a pointer
// kind of like "common" last year
// might evolve into something similar later on
// we can create multiple instances of BMP, IMU etc structs
// the ones in use will be located in the sensor struct
struct {
    BMP280 *bmpTop;
    BMP280 *bmpBtm;
    BMP280_config *bmpConfig;

    MPU9250 *mpu;

    Buzzer *buzzer;

    // SX1278 radio;
} Common;

// BMP280 structs for top layer
BMP280 bmpTop;
// BMP280 structs for bottom layer 
BMP280 bmpBtm;
// MPU9250 struct 
MPU9250 mpu;

float altPressure;

uint16_t groundAlt;

long prevMillis;

void setup(void);
void loop(void);

float altFromPressure(float pressure);
void setHeight(uint16_t a);

// ############ GPIO writing ############
#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET
#define GPIO_Port(PIN) PIN ## _GPIO_Port
#define GPIO_Pin(PIN) PIN ## _Pin
#define writePin(PIN, VAL) HAL_GPIO_WritePin(GPIO_Port(PIN), GPIO_Pin(PIN), VAL)
#define togglePin(PIN) HAL_GPIO_TogglePin(GPIO_Port(PIN), GPIO_Pin(PIN))
#define readPin(PIN) HAL_GPIO_ReadPin(GPIO_Port(PIN), GPIO_Pin(PIN))

#define delay(MS) HAL_Delay(MS);

#endif // _RUN_H_
