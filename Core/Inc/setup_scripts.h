#ifndef SETUP_SRIPTS_H
#define SETUP_SRIPTS_H

#include <stdbool.h>
#include "config.h"
#include "USB_com.h"
#include "run.h"

bool bmpSetup(void);
bool mpuSetup(void);
bool gpsSetup(void);
bool buzzerSetup(void);

#endif