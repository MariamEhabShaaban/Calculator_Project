#ifndef CAL_H_
#define CAL_H_
#include "../stdTypes.h"
#define MAXINPUT 16
#define ERorr 65
#define OK 78

void ERROR();
s32 check_the_last_operation(u8 P, s32 *res);
s32 check_the_MulDiv_operation(u8 oper);
void REVERSE_INPUT();
void CAL_INIT();
void CAL_INPUT();

void CAL_OUTPUT();

void CAL_OPERATION();
void Clear_CAL();
#endif
