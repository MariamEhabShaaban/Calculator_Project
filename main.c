
#include "stdTypes.h"
#include "errorStates.h"

#include "DIO/DIO_int.h"

#include "LCD/LCD_int.h"
#include "Keypad/KPD_int.h"

#include "calculator/cal.h"


int main (void)
{

	CAL_INIT();

   while(1){
    CAL_INPUT();

  }

	return 0;
}
