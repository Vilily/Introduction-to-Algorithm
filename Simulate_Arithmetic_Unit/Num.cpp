#pragma once
#include "Num.h"
#include <stdio.h>


/************************************* ���ֳ��� ******************************************/

Num::Num()
{
}

Num::~Num()
{
}

/**
* ���ڴ��е���Ϣ�Զ��������
* @param p: ��ʼ��ַ
* @param n: �����λ��
* @return void
*/
void Num::num_to_binary(void* p, int n)
{
	unsigned long long num = *(unsigned long long*)p;
	for (int i(0); i < n; i++)
		printf("%lld", (num >> (n - 1 - i)) & 1);
	printf("\n");
}

/************************************* ������ ******************************************/

Int::Int()
{
	// ������
	this->is_float = NumType::float_;
}

Int::~Int()
{
}

/************************************* �������� ******************************************/
Float::Float()
{
	this->is_float = NumType::float_;
}

Float::~Float()
{
}