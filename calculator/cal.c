#include "cal.h"

#include "../Keypad/KPD_int.h"
#include "../LCD/LCD_int.h"
#include "../stack.h"
u8 INPUT[MAXINPUT] = { 0 }, Error[] = "ERROR!!!!";
NUMS numbers, rev_numbers, remender;
operations op, rev_op;
s32 i = 0;
s32 fraction = 0, res_mul1000 = 0;
s32 is_ok = OK;
void ERROR() {
	LCD_enuSendCommand(0xc0); //////GO TO SECOND LINE IN LCD
	for (s32 it = 0; Error[it] != '\0'; it++) {
		LCD_enuDisplayChar(Error[it]);

	}
}



s32 check_the_last_operation(u8 P, s32 *resu) {

	if (P == 'x' || P == '/') {
		s32 num1, num2;
		Pop(&num2, &numbers);
		Pop(&num1, &numbers);
		if (P == 'x')
			*resu = num1 * num2;
		if (P == '/') {
			*resu = num1 / num2;
			res_mul1000 = (num1 * 1000) / num2;
			fraction = res_mul1000 - (*resu * 1000);
			if (num2 == 0) {
				ERROR();
				return ERorr;
			}

		}
		Push(*resu, &numbers);
		Pop_op(&P, &op);
	}
	return OK;
}



s32 check_the_MulDiv_operation(u8 oper) {

	s32 res, num2, num1;
	u8 pp;

	if (oper == 'x' || oper == '/') {
		Pop(&num2, &numbers);
		Pop(&num1, &numbers);
		if (oper == 'x') {
			Pop_op(&pp, &op);
			res = num1 * num2;
		} else if (oper == '/') {

			Pop_op(&pp, &op);
			if (num2 == 0) {
				ERROR();
				return ERorr;
			}
			res_mul1000 = (num1 * 1000) / num2;
			res = num1 / num2;
			fraction = res_mul1000 - (res * 1000);
		}
		Push(res, &numbers);
	}
	return OK;
}




void REVERSE_INPUT() {

	while (!StackEmpty(&numbers)) {
		s32 s1_top;
		Pop(&s1_top, &numbers);
		Push(s1_top, &rev_numbers);

	}

	while (!StackEmpty_op(&op)) {
		u8 p1_top;
		Pop_op(&p1_top, &op);
		Push_op(p1_top, &rev_op);

	}
}

void CAL_INIT() {

	Keypad_enuInit();
	LCD_enuInit();
	CreateStack(&numbers);
	CreateStack(&rev_numbers);
	CreateStack_op(&op);
	CreateStack_op(&rev_op);

}



void CAL_INPUT() {

	u8 press;

	do {

		Keypad_enuGetPressedKey(&press);

	} while (press == 0xff);
	if (press == '=') {
		LCD_enuDisplayChar(press);
		INPUT[i++] = '\0';
		CAL_OPERATION();
		CAL_OUTPUT();
	} else if (press == 'c') {
		Clear_CAL();

	}

	else if (press != 'c' && press != '=' && press != 0xff) {
		LCD_enuDisplayChar(press);
		INPUT[i++] = press;
	}
}




void CAL_OPERATION() {
	s32 num = 0;

	for (int j = 0; INPUT[j] != '\0'; j++) {
		if (IsDigit(INPUT[j])) {
			num = num * 10 + (INPUT[j] - '0');
		} else if (IsOp(INPUT[j])) {
			Push(num, &numbers);
			if (StackSize(&numbers) >= 2) {

				u8 oper = StackTop_op(&op);
				is_ok = check_the_MulDiv_operation(oper);
				if (is_ok == ERorr)
					return;

			}

			Push_op(INPUT[j], &op);
			num = 0;
		}
	}
	Push(num, &numbers);
	u8 P = StackTop_op(&op);
	s32 res;
	is_ok = check_the_last_operation(P, &res);
	if (is_ok == ERorr)
		return;
	/////REVERSE THE INPUT
	REVERSE_INPUT();
	//////final operation + -

}




void CAL_OUTPUT() {
	s32 result;

	while (!StackEmpty_op(&rev_op)) {

		s32 res = 0;
		s32 top_num1;
		Pop(&top_num1, &rev_numbers);
		s32 top_num2;
		Pop(&top_num2, &rev_numbers);
		u8 opre;
		Pop_op(&opre, &rev_op);
		switch (opre) {

		case '+':

			res = top_num1 + top_num2;
			Push(res, &rev_numbers);
			break;

		case '-':
			res = top_num1 - top_num2;
			Push(res, &rev_numbers);
		}
	}
	Pop(&result, &rev_numbers);


	if (is_ok == OK) {
		LCD_enuSendCommand(0xc0);/////GO TO SECOND LINE IN LCD
		LCD_enuDisplayIntegerNum(result);

		if (fraction > 0) {

			LCD_enuDisplayChar('.');
			LCD_enuDisplayIntegerNum(fraction);
		}
	}
}



void Clear_CAL() {
	LCD_Clear();
	ClearStack(&numbers);
	ClearStack(&rev_numbers);
	ClearStack_op(&op);
	ClearStack_op(&rev_op);
	i = 0;
	fraction = 0;
	res_mul1000 = 0;

}

