#pragma once
#include "Num.h"
#include <stdio.h>
#include <iostream>

using namespace::std;
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

/**
* ��ӡԭ�롢���롢����
*/
void Num::print_codes_binary()
{
	this->print_num();
	printf("ԭ��:\n");
	this->convert_to_true_code();
	this->print_code_binary();
	printf("����:\n");
	this->convert_to_inverse_code();
	this->print_code_binary();
	printf("����:\n");
	this->convert_to_complement_code();
	this->print_code_binary();
}

