#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"
#include "run.h"

void enableMotor(void);
void disableMotor(void);
void setMotor(void);
void openMotor(bool openOne, uint8_t ang);

#endif // _MOTOR_H_