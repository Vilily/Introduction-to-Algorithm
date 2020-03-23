#ifndef _STACK_H_
#define _STACK_H_
#include "Tree.h"

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
//typedef int ElementType;
typedef SearchTree ElementType;

int IsEmpty(Stack S);
//��ʼ����ջ
Stack CreateStack(void);
//���ٶ�ջ
void DisposeStack(Stack S);
//��ն�ջ
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
#endif // !_STACK_H_


