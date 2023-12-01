
#include "../calculator/cal.h"

#include "../Keypad/KPD_int.h"
#include "../LCD/LCD_int.h"
#include "../stack.h"
#include "util/delay.h"
u8 INPUT [MAXINPUT]={0},Error[]="ERROR!!!!";
NUMS numbers,rev_numbers,remender;
operations op,rev_op;
s32 i=0;
void CAL_INIT(){

	Keypad_enuInit();
	LCD_enuInit();
	CreateStack(&numbers);
	CreateStack(&rev_numbers);
	CreateStack_op(&op);
	CreateStack_op(&rev_op);



}
void CAL_INPUT(){

	u8 press;

	do{

Keypad_enuGetPressedKey(&press);


	}while(press==0xff);
	    if(press=='='){
		     LCD_enuDisplayChar(press);
			 INPUT[i++]='\0';
			 CAL_OPERATION();
		}
		else if(press=='c'){
			Clear_CAL();
		}

		else if(press!='c'&&press!='='&&press!=0xff){
		    LCD_enuDisplayChar(press);
		    INPUT[i++]=press;
	    }
}


void CAL_OPERATION(){
	s32 num=0;

	 for(int j=0;INPUT[j]!='\0';j++){




	        if(IsDigit(INPUT[j])){
	        num=num*10+(INPUT[j]-'0');
	        }

	        else if(IsOp(INPUT[j])){

	             Push(num,&numbers);
	             if(StackSize(&numbers)>=2){

	            s32 num2,num1,res;
	            u8 oper=StackTop_op(&op),pp;

	            if(oper=='x'||oper=='/'){
	             Pop(&num2,&numbers);
	             Pop(&num1,&numbers);
	             if(oper=='x'){
	                   Pop_op(&pp,&op);
	                 res=num1*num2;
	             }
	             else if(oper=='/'){
	                  Pop_op(&pp,&op);
	                  if(num2==0){
	                	  LCD_enuSendCommand(0xc0);//////GO TO SECOND LINE IN LCD
	                	  for(s32 it=0;Error[it]!='\0';it++){
	                		  LCD_enuDisplayChar(Error[it]);

	                	  }
	                	  return;
	                  }
	                 res=num1/num2;
	             }

	             Push(res,&numbers);
	            }

	        }


	    Push_op(INPUT[j],&op);
	     num=0;
	}


	        }
	 Push(num,&numbers);
	 u8 P=StackTop_op(&op);

	 if(P=='x'||P=='/'){
	     s32 num1,num2,res;
	      Pop(&num2,&numbers);
	       Pop(&num1,&numbers);
	       if(P=='x')
	       res=num1*num2;
	        if(P=='/'){
	           res=num1/num2;
	           if(num2==0){
	        	   LCD_enuSendCommand(0xc0);
	        for(s32 it=0;Error[it]!='\0';it++){

	       	       LCD_enuDisplayChar(Error[it]);
	       	                	  }
	        return;
	        }

	        }
	       Push(res,&numbers);

	        Pop_op(&P,&op);

	 }
	 /////REVERSE THE INPUT
	 while(!StackEmpty(&numbers)){
	 	s32 s1_top;
	 	Pop(&s1_top,&numbers);
	 	Push(s1_top,&rev_numbers);

	 }
	 while(!StackEmpty_op(&op)){
	 		u8 p1_top;
	 		Pop_op(&p1_top,&op);
	 		Push_op(p1_top,&rev_op);


	 	}


	  CAL_OUTPUT();

}


void CAL_OUTPUT(){
	s32 result;

	 while(!StackEmpty_op(&rev_op)){

	           s32 res=0;
	       s32 top_num1;
	       Pop(&top_num1,&rev_numbers);
	        s32 top_num2;
	       Pop(&top_num2,&rev_numbers);
	        u8 opre;
	        Pop_op(&opre,&rev_op);
	        switch(opre){

	        case'+':

	        res=top_num1+top_num2;
	        Push(res,&rev_numbers);
	        break;

	         case'-':
	        res=top_num1-top_num2;
	        Push(res,&rev_numbers);
	        }
	 }
	        Pop(&result, &rev_numbers );
	        LCD_enuSendCommand(0xc0);/////GO TO SECOND LINE IN LCD


	        LCD_enuDisplayIntegerNum(result);



	        }




void Clear_CAL(){
	 LCD_Clear();
	 ClearStack(&numbers);
	 ClearStack(&rev_numbers);
	 ClearStack_op(&op);
	 ClearStack_op(&rev_op);
i=0;

}

