#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define ROWS_NUM	4
#define COLS_NUM	4

#define C1_PORT		DIO_u8PORTA
#define C1_PIN		DIO_u8PIN0

#define C2_PORT		DIO_u8PORTA
#define C2_PIN		DIO_u8PIN1

#define C3_PORT		DIO_u8PORTA
#define C3_PIN		DIO_u8PIN2

#define C4_PORT		DIO_u8PORTA
#define C4_PIN		DIO_u8PIN3

#define R1_PORT		DIO_u8PORTA
#define R1_PIN		DIO_u8PIN4

#define R2_PORT		DIO_u8PORTA
#define R2_PIN		DIO_u8PIN5

#define R3_PORT		DIO_u8PORTA
#define R3_PIN		DIO_u8PIN6

#define R4_PORT		DIO_u8PORTA
#define R4_PIN		DIO_u8PIN7

#define KEYS_VALUES				{\
									{'7', '8', '9', '/'},\
									{'4', '5', '6', 'x'},\
									{'1', '2', '3', '-'},\
									{'c', '0', '=', '+'},\
								}



#endif
