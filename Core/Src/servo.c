#include "servo.h"
#include "tim.h"


void set_ang(uint16_t ang)
{
	uint16_t val;
    ANGLE_R = ang;

	if(ang > ANGLE_MAX){
		ang = ANGLE_MAX;
	}
	else if (ang < ANGLE_MIN){
		ang = ANGLE_MIN;
	}

	val = PWM_MIN + ((ang - ANGLE_MIN) * STEP) / 1000;

	__HAL_TIM_SET_COMPARE(&TIM_NO, TIM_CH_NO, val);
}

void toggle_ang(){
    if(ANGLE_R == 90){
        set_ang(0);
    }
    else{
        set_ang(90);
    }
}

uint8_t get_ang(){
	return ANGLE_R;
}