#ifndef stack_h
#define stack_h
#include "stdTypes.h"
#define maxstack 100
#define stackentry s32

 typedef struct stack{

 int top;
 stackentry entry [maxstack];


 }NUMS;
 typedef struct sstack{

 int top;
 u8 entryy [maxstack];


 }operations;

void CreateStack(NUMS*);
void Push(stackentry, NUMS*);
void Pop(stackentry*, NUMS*);
int StackFull(NUMS*);
int StackEmpty(NUMS*);
//void StackTop(stackentry* , NUMS* );
int StackSize(NUMS*);
void ClearStack(NUMS*);
void TraverseStack(NUMS*, void (*)(stackentry));
//void Revese_Stack(NUMS *,NUMS*);



void CreateStack_op(operations *ps);
void Push_op(u8 , operations *);
void Pop_op(u8*, operations *);
int StackEmpty_op(operations *ps);
char StackTop_op(operations* );
//void Revese_Stack_op(operations *,operations *);
void ClearStack_op(operations*);



int IsDigit(char c);

int IsOp(char c);
#endif
