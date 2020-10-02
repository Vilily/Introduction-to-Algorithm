/**
* Float���ʵ��
* @Author: Bao Wenjie
* @Email: bwj_678@qq.com
* @Date: 2020/10/2
*/

#pragma once
#include "Num.h"

const unsigned long long FLOAT_ONES = 0XFFFFFFFFFFFFFFFF;
const unsigned int E_BASE = 1023;

Float::Float()
{
	// ������
	this->num_type = NumType::float_;
	// ����
	this->code_type = CodeType::complement_;
	this->num.num = (double)0;
}

Float::Float(double num)
{
	// ������
	this->num_type = NumType::float_;
	// ��������
	this->code_type = CodeType::complement_;
	this->num.num = num;
}

Float::Float(double num, CodeType type)
{
	// ������
	this->num_type = NumType::float_;
	// ��������
	this->code_type = type;
	this->num.num = num;
}

Float::~Float()
{
}

/**
* ������: תԭ��
*/
void Float::convert_to_true_code()
{
	//����
	if (this->num.s.f == 0)
	{
		this->code_type = CodeType::true_;
		return;
	}
	// ���� -> ԭ��
	else if (this->code_type == CodeType::inverse_)
	{
		this->num.s.num ^= FLOAT_ONES;
	}
	// ���� -> ԭ��
	else if (this->code_type == CodeType::complement_)
	{
		this->convert_to_inverse_code();
		this->convert_to_true_code();
	}
	this->code_type = CodeType::true_;
	return;
}

/**
* ������: ת����
*/
void Float::convert_to_inverse_code()
{
	// ����
	if (this->num.s.f == 0)
	{
		this->code_type = CodeType::inverse_;
		return;
	}
	// ԭ�� -> ����
	else if (this->code_type == CodeType::true_)
	{
		this->num.s.num ^= FLOAT_ONES;
	}
	// ���� -> ����
	else
	{
		this->num.s.num -= 1;
	}
	this->code_type = CodeType::inverse_;
	return;
}

/**
* ������: ת����
*/
void Float::convert_to_complement_code()
{
	if (this->num.s.f == 0)
	{
		this->code_type = CodeType::complement_;
		return;
	}
	// ԭ��  -> ����
	else if (this->code_type == CodeType::true_)
	{
		this->convert_to_inverse_code();
		this->convert_to_complement_code();
	}
	// ���� -> ����
	else if (this->code_type == CodeType::inverse_)
	{
		this->num.s.num += 1;
	}
	this->code_type = CodeType::complement_;
	return;
}

/**
* ��ӡ
*/
void Float::print_code_binary()
{
	this->num_to_binary(&this->num, 64);
}

/**
* ʮ���ƴ�ӡ����
*/
void Float::print_num()
{
	printf("ʮ����Ϊ:%lf\n", this->num.num);
}
// ת������
Float* Float::convert_to_float()
{
	return this;
}

// ת����
Int* Float::convert_to_int()
{
	return NULL;
}