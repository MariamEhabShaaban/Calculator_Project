
#include "stack.h"

void CreateStack(NUMS *ps)
{
    ps->top=0;
}

void CreateStack_op(operations *ps)
{
    ps->top=0;
}
/*void Revese_Stack(NUMS *s1,NUMS *s2){
while(StackEmpty(&s1)){
	int s1_top;
	Pop(&s1_top,&s1);
	Push(s1_top,&s2);

}

}

void Revese_Stack_op(operations *p1,operations *p2){
	while(StackEmpty(&p1)){
		u8 p1_top;
		Pop_op(&p1_top,&p1);
		Push_op(p1_top,&p2);


	}

}*/

void Push(stackentry e, NUMS *ps)
{
    ps->entry[ps->top++]=e;
}
void Push_op(u8 e, operations *OP)
{
    OP->entryy[OP->top++]=e;
}

void Pop_op(u8 *pe, operations *OP)
{
    *pe=OP->entryy[--OP->top];
}

void Pop(stackentry *pe, NUMS *ps)
{
    *pe=ps->entry[--ps->top];
}


int StackFull(NUMS *ps)
{
    return (ps->top==maxstack);
}

int StackEmpty_op(operations *ps)
{
    return ps->top;
}
int StackEmpty(NUMS *ps)
{
    return ps->top;
}
/*void StackTop(stackentry *pe ,NUMS *ps)
{

    pe=ps->entry[ps->top-1];
}*/

int StackSize(NUMS *ps)
{

    return ps->top;
}
void ClearStack(NUMS *ps)
{

    ps->top=0;
}
void ClearStack_op(operations* op){
	op->top=0;
}
void TraverseStack(NUMS *ps, void (*pf)(stackentry))
{
    for(int i=ps->top; i>0; i--)
        (*pf)(ps->entry[i-1]);

}
char StackTop_op(operations* op ){

return op->entryy[op->top-1];
}



int IsDigit(char c){
   return(c>='0' && c<='9');
}
int IsOp(char c){
   return(c=='/' || c=='x'||c=='+'||c=='-');
}
