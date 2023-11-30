#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H
#include "../errorStates.h"
#include "../stdTypes.h"

ES_t Keypad_enuInit(void);

ES_t Keypad_enuGetPressedKey(u8 * Copy_pu8KeyValue);

#define KEYPAD_NOT_PRESSED		0xff
#endif
