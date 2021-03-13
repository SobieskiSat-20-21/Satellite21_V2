#include <stdbool.h>
#include "buzzer.h"
#include "main.h"

void buzzerDefaultInit(Buzzer* buzzer){
    buzzer->buzzerTimer = Get_TIM10_Instance();
    buzzer->BuzzerTimerChannel = TIM_CHANNEL_1;
    buzzer->frequency = 3600;
    buzzer->state = 0;
}

bool buzzerSetFrequency(Buzzer* buzzer, uint16_t frequency){
    buzzer->frequency = frequency;
    // amount of ticks for a timer for a given frequency
    uint16_t period = 72000000 / frequency;
    buzzer->buzzerTimer->Instance->ARR = period - 1;
    buzzer->buzzerTimer->Instance->CCR1 = period / 2 - 1;
}
void buzzerOn(Buzzer* buzzer){
    HAL_TIM_PWM_Start(buzzer->buzzerTimer, buzzer->BuzzerTimerChannel);
    buzzer->state = 1;
}
void buzzerOff(Buzzer* buzzer){
    HAL_TIM_PWM_Stop(buzzer->buzzerTimer, buzzer->BuzzerTimerChannel);
    buzzer->state = 0;
}

void buzzerToggle(Buzzer* buzzer){
    if(buzzer->state) buzzerOff(buzzer);
    else buzzerOn(buzzer);
}