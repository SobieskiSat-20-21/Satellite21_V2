#ifndef _USB_COM_
#define _USB_COM_

#include "usbd_cdc_if.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// buffer for USB communication
#define USBBufferTXSize 64

char USBBufferTX[USBBufferTXSize];

// adds char to USBBufferTX
bool USBAddCharToBuffer(char pass);

// ads string to USBBufferTX
bool USBAddStringToBuffer(char* pass);

// adds long to the USBBufferTX
bool USBAddLongToBuffer(long pass);

// ads float to the USBBufferTX
bool USBAddFloatToBuffer(float pass);

// transmits the prepared buffer if not empty
void USBTPrintBuffer();

// turns float into array of chars
bool formatFloat(float value, char *buffer);

// prints the num amount of strings
// void USBprint(int num, ...);

// prints the num amount of strings in new line
// void USBprintln(int num, ...);

// prints one string
void USBprint(char *pointer);

// prints one string in a new line
void USBprintln(char* pointer);


#endif // _USB_COM_ //