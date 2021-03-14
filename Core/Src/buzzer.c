#include <stdbool.h>
#include "buzzer.h"
#include "main.h"
#include "config.h"

void buzzerDefaultInit(Buzzer* buzzer){
    #if BUZZER_ENABLE

    buzzer->buzzerTimer = Get_TIM10_Instance();
    buzzer->buzzerTimerChannel = TIM_CHANNEL_1;
    buzzer->clockFrequency = 72000000;
    buzzer->frequency = 2700;
    buzzer->state = 0;
    buzzer->maxFrequency = 5500;
    buzzer->minFrequency = 1100;

    #endif
}

// returns true if the requested frequency has been set
// returns false if the value is out of range
// in that case min or max frequency is set accordingly
bool buzzerSetFrequency(Buzzer* buzzer, uint16_t frequency){
    #if BUZZER_ENABLE

    if(frequency > buzzer->maxFrequency){
        buzzer->frequency = buzzer->maxFrequency;
        return false;
    }
    else if(frequency < buzzer->minFrequency){
        buzzer->frequency = buzzer->minFrequency;
        return false;
    }
    buzzer->frequency = frequency;
    // amount of ticks for a timer for a given frequency
    uint16_t period = buzzer->clockFrequency / frequency;
    buzzer->buzzerTimer->Instance->ARR = period - 1;
    buzzer->buzzerTimer->Instance->CCR1 = period / 2 - 1;

    #endif
}
void buzzerOn(Buzzer* buzzer){
    #if BUZZER_ENABLE

    HAL_TIM_PWM_Start(buzzer->buzzerTimer, buzzer->buzzerTimerChannel);
    buzzer->state = 1;

    #endif
}
void buzzerOff(Buzzer* buzzer){
    #if BUZZER_ENABLE

    HAL_TIM_PWM_Stop(buzzer->buzzerTimer, buzzer->buzzerTimerChannel);
    buzzer->state = 0;
    
    #endif
}

void buzzerToggle(Buzzer* buzzer){
    #if BUZZER_ENABLE

    if(buzzer->state) buzzerOff(buzzer);
    else buzzerOn(buzzer);

    #endif
}