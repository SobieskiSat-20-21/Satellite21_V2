#ifndef BUZZER_H_
#define BUZZER_H_

#include "stm32f4xx_hal.h"

typedef struct{
    TIM_HandleTypeDef* buzzerTimer;     // pointer to a timer struct
    uint8_t BuzzerTimerChannel;         // channel used for PWM
    uint16_t frequency;                 // in Hz
    uint8_t state;                      // On = 1, Off = 0
} Buzzer;

Buzzer defaultBuzzer;

void buzzerDefaultInit(Buzzer* buzzer);
bool buzzerSetFrequency(Buzzer* buzzer, uint16_t frequency);
void buzzerOn(Buzzer* buzzer);
void buzzerOff(Buzzer* buzzer);
void buzzerToggle(Buzzer* buzzer);

#endif