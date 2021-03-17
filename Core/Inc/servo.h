#ifndef INC_SERVO_H_
#define INC_SERVO_H_
#include <stdint.h>

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

#define STEP ((1000 * (PWM_MAX - PWM_MIN)) / (ANGLE_MAX - ANGLE_MIN))

void set_ang(uint16_t ang);
void toggle_ang();
uint8_t get_ang();

#endif /* INC_SERVO_H_ */