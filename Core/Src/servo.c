#include "servo.h"
#include "tim.h"
#include "run.h"

void servoDefaultDronInit(Servo* servo){
    //#if 
    servo->servoTimer = Get_TIM3_Instance();
    servo->servoTimerChannel = TIM_CHANNEL_2;
	servo->angleMax = 180;
	servo->angleMin = 0;
    //#endif
}

void servoDefaultMainInit(Servo* servo){
    //#if 
    servo->servoTimer = Get_TIM3_Instance();
    servo->servoTimerChannel = TIM_CHANNEL_2;
	servo->angleMax = 180;
	servo->angleMin = 0;
	servo->angleCurrent = 0;
	servo->angle[0]=0;
	servo->angle[1]=90;
	servo->angle[2]=105;
    //#endif
}

void set_ang(Servo* servo, uint16_t ang)
{
	uint16_t val;
    ANGLE_R = ang;

	if(ang > servo->angleMax){
		ang = servo->angleMax;
	}
	else if (ang < servo->angleMin){
		ang = servo->angleMin;
	}

	val = PWM_MIN + ((ang - servo->angleMin) * STEP) / 1000;

	__HAL_TIM_SET_COMPARE(&TIM_NO, TIM_CH_NO, val);
}



/*void set_ang(uint16_t ang)
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
}*/

void toggle_ang(Servo* servo){
    if(ANGLE_R == 90){
        set_ang(Common.servoDron, 0);
    }
    else{
        set_ang(Common.servoDron,90);
    }
}

uint8_t get_ang(){
	return ANGLE_R;
}