#include "../stdTypes.h"
#include "../errorStates.h"

#include "../DIO/DIO_int.h"

#include "KPD_config.h"
#include "KPD_priv.h"

#include <util/delay.h>


ES_t Keypad_enuInit(void){
	ES_t Local_enuErrorstate = ES_NOK;

	Local_enuErrorstate =   DIO_enuSetPinDirection(C1_PORT,C1_PIN, DIO_u8OUTPUT);
	Local_enuErrorstate =	DIO_enuSetPinDirection(C2_PORT,C2_PIN, DIO_u8OUTPUT);
	Local_enuErrorstate =	DIO_enuSetPinDirection(C3_PORT,C3_PIN, DIO_u8OUTPUT);
	Local_enuErrorstate =	DIO_enuSetPinDirection(C4_PORT,C4_PIN, DIO_u8OUTPUT);

	Local_enuErrorstate =	DIO_enuSetPinDirection(R1_PORT,R1_PIN, DIO_u8INPUT);
	Local_enuErrorstate =	DIO_enuSetPinDirection(R2_PORT,R2_PIN, DIO_u8INPUT);
	Local_enuErrorstate =	DIO_enuSetPinDirection(R3_PORT,R3_PIN, DIO_u8INPUT);
	Local_enuErrorstate =	DIO_enuSetPinDirection(R4_PORT,R4_PIN, DIO_u8INPUT);

	Local_enuErrorstate =	DIO_enuSetPinValue(C1_PORT,C1_PIN, DIO_u8HIGH);
	Local_enuErrorstate =	DIO_enuSetPinValue(C2_PORT,C2_PIN, DIO_u8HIGH);
	Local_enuErrorstate =	DIO_enuSetPinValue(C3_PORT,C3_PIN, DIO_u8HIGH);
	Local_enuErrorstate =	DIO_enuSetPinValue(C4_PORT,C4_PIN, DIO_u8HIGH);

	Local_enuErrorstate =	DIO_enuSetPinValue(R1_PORT,R1_PIN, DIO_u8PULL_UP);
	Local_enuErrorstate =	DIO_enuSetPinValue(R2_PORT,R2_PIN, DIO_u8PULL_UP);
	Local_enuErrorstate =	DIO_enuSetPinValue(R3_PORT,R3_PIN, DIO_u8PULL_UP);
	Local_enuErrorstate =	DIO_enuSetPinValue(R4_PORT,R4_PIN, DIO_u8PULL_UP);

	 Local_enuErrorstate  =ES_OK;


		return Local_enuErrorstate;

}

ES_t Keypad_enuGetPressedKey(u8 * Copy_pu8KeyValue){
	ES_t Local_enuErrorstate=ES_NOK;
			if( Copy_pu8KeyValue!=NULL){
				    u8 Local_Au8RowPins [ROWS_NUM] = { R1_PIN , R2_PIN , R3_PIN , R4_PIN };
				    u8 Local_Au8ColPins [COLS_NUM] = { C1_PIN , C2_PIN , C3_PIN , C4_PIN };
				    u8 Local_Au8RowPorts[ROWS_NUM] = { R1_PORT , R2_PORT , R3_PORT , R4_PORT };
				    u8 Local_Au8ColPorts[COLS_NUM] = { C1_PORT , C2_PORT , C3_PORT , C4_PORT };

						*Copy_pu8KeyValue = KEY_NOT_PRESS;
						u8 Local_u8PinValue = 0xff;

				  u8 Local_Au8KeyValues[ROWS_NUM][COLS_NUM] = KEYS_VALUES;
				  u8 Local_col_it,Local_row_it;
				  for(Local_col_it=0;Local_col_it<COLS_NUM;Local_col_it++){
					  //active col
					   DIO_enuSetPinValue(Local_Au8ColPorts[Local_col_it],Local_Au8ColPins[Local_col_it],DIO_u8LOW);
					   for(Local_row_it=0;Local_row_it<ROWS_NUM;Local_row_it++){
						   DIO_enuGetPinValue(Local_Au8RowPorts[Local_row_it], Local_Au8RowPins[Local_row_it], &Local_u8PinValue);
						   if (! Local_u8PinValue)
						   				{
						   					_delay_ms(10);
						   					DIO_enuGetPinValue(Local_Au8RowPorts[Local_row_it], Local_Au8RowPins[Local_row_it], &Local_u8PinValue);
						   					if (! Local_u8PinValue)
						   					{
						   						while (! Local_u8PinValue)
						   						{
						   							DIO_enuGetPinValue(Local_Au8RowPorts[Local_row_it], Local_Au8RowPins[Local_row_it], &Local_u8PinValue);
						   						}

						   						*Copy_pu8KeyValue = Local_Au8KeyValues[Local_row_it][Local_col_it];

						   						return Local_enuErrorstate=ES_OK;
						   					}
						   				}
						   			}
					   //deactive

						   			DIO_enuSetPinValue(Local_Au8ColPorts[Local_col_it] , Local_Au8ColPins[Local_col_it] , DIO_u8HIGH);
						   		}
						   	}







			else{
				 Local_enuErrorstate=ES_NULL_POINTER;
			}


			return Local_enuErrorstate;

}




