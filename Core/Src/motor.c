#include "motor.h"
#include "main.h"
#include "clock.h"
#include "run.h"
#include "radio.c"

//bool direction = false;
bool motorRunning = false;

bool motorOpen = false;

void setMotor(void)
{
	if (!motorRunning)
	{
        HAL_GPIO_WritePin(ENB_A1_GPIO_Port, ENB_A1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOT_STBY1_GPIO_Port, MOT_STBY1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(PHA_A1_GPIO_Port, PHA_A1_Pin, GPIO_PIN_RESET);
	}
}


void enableMotor(void)
{
	if (!motorRunning)
	{
		motorRunning = true;

        HAL_GPIO_WritePin(ENB_A1_GPIO_Port, ENB_A1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOT_STBY1_GPIO_Port, MOT_STBY1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(PHA_A1_GPIO_Port, PHA_A1_Pin, GPIO_PIN_SET);
	}
}


void disableMotor(void)
{
	if (true)
	{
        HAL_GPIO_WritePin(ENB_A1_GPIO_Port, ENB_A1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOT_STBY1_GPIO_Port, MOT_STBY1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(PHA_A1_GPIO_Port, PHA_A1_Pin, GPIO_PIN_RESET);

		motorRunning = false;
	}
}

void openMotor(bool openOne, uint8_t ang){
        //int ij=100000;
        if(motorOpen == false){
            prevMillis = millis();
            motorOpen = true;
            //ij=0;
        }
        //writePin(LEDB, HIGH);
		long actMillis = millis();
        //delay(4500);
        /*if(motorOpen ==true && actMillis-prevMillis > 2000){
            disableMotor();
            motorOpen = false;
		}else{
			enableMotor();
		}*/
        while(motorOpen ==true && actMillis-prevMillis < 820*ang/360){
            togglePin(LEDB);
            if(openOne==true){
                enableMotor();
            }
            else{
                setMotor();
            }
            duplex_loop();
            //HAL_Delay(1);
            actMillis = millis();
            //ij++;
        }
        motorOpen=false;
        disableMotor();
}