#ifndef BUZZER_H_
#define BUZZER_H_

#include "stm32f4xx_hal.h"

typedef struct{
    TIM_HandleTypeDef* buzzerTimer;     // pointer to a timer struct
    uint16_t buzzerTimerChannel;        // channel used for PWM
    uint32_t clockFrequency;            // frequency of the timer clock
    uint16_t frequency;                 // in Hz
    uint16_t state;                     // On = 1, Off = 0
    uint16_t maxFrequency;              // self-explanatory in Hz
    uint16_t minFrequency;              // like above
} Buzzer;

Buzzer defaultBuzzer;

void buzzerDefaultInit(Buzzer* buzzer);
bool buzzerSetFrequency(Buzzer* buzzer, uint16_t frequency);
void buzzerOn(Buzzer* buzzer);
void buzzerOff(Buzzer* buzzer);
void buzzerToggle(Buzzer* buzzer);

#endif