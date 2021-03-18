#ifndef INC_SERVO_H_
#define INC_SERVO_H_
#include <stdint.h>
#include "stm32f4xx_hal.h"

/* konfiguracja timera do generowania PWM */
#define TIM_NO htim3
#define TIM_CH_NO TIM_CHANNEL_2

/* zakresy katowe pracy serwomechanizmu */
#define ANGLE_MIN 0
#define ANGLE_MAX 180
/* zakres PWM */
#define PWM_MIN 350
#define PWM_MAX 2500

uint8_t ANGLE_R;

typedef struct{
    TIM_HandleTypeDef* servoTimer;     // pointer to a timer struct
    uint16_t servoTimerChannel;        // channel used for PWM
    uint16_t angleMax;
    uint16_t angleMin;
    uint16_t angleCurrent;
    uint8_t angle[3];
} Servo;

Servo defaultServoDron;
Servo defaultServoMain;

#define STEP ((1000 * (PWM_MAX - PWM_MIN)) / (ANGLE_MAX - ANGLE_MIN))

void defaultServoDronInit(Servo *servo);
void defaultServoMainInit(Servo *servo);
void set_ang(Servo *servo, uint16_t ang);
void toggle_ang(Servo* servo);
uint8_t get_ang();

#endif /* INC_SERVO_H_ */