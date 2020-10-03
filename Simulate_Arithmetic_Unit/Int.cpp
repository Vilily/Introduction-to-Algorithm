/**
* Int���ʵ��
* @Author: Bao Wenjie
* @Email: bwj_678@qq.com
* @Date: 2020/10/2
*/

#pragma once
#include "Num.h"

const unsigned int ONES = 0X7FFFFFFF; //01..31..1
const unsigned int FFFF = 0XFFFFFFFF; //111111111
const unsigned long long FLOAT_ONES = 0XFFFFFFFFFFFFFFFF;
const unsigned int E_BASE = 1023;

Int::Int()
{
	// ����
	this->num_type = NumType::int_;
	// ����
	this->code_type = CodeType::complement_;
	this->num.x = 0;
}

Int::Int(int num)
{
	// ����
	this->num_type = NumType::int_;
	// ����
	this->code_type = CodeType::complement_;
	this->num.x = num;
}

Int::Int(int num, CodeType type)
{
	// ����
	this->num_type = NumType::int_;
	// ����
	this->code_type = type;
	this->num.x = num;

}

Int::~Int()
{
}

/**
* ����: ת����
*/
void Int::convert_to_inverse_code()
{
	// ԭ�� -> ����
	if (this->code_type == CodeType::true_)
	{
		// ����
		if (this->num.s.f != 0)
		{
			this->num.s.x ^= ONES;
		}
	}
	// ���� -> ����
	else if (this->code_type == CodeType::complement_)
	{
		// ����
		if (this->num.s.f != 0)
		{
			this->num.s.x -= 1;
		}
	}
	// ���� -> ����
	else
	{
		return;
	}
	this->code_type = CodeType::inverse_;
	return;
}

/**
* ����: תԭ��
*/
void Int::convert_to_true_code()
{
	// ���� -> ԭ��
	if (this->code_type == CodeType::inverse_)
	{
		// ����
		if (this->num.s.f != 0)
		{
			this->num.s.x ^= ONES;
		}
	}
	// ���� -> ԭ��
	else if (this->code_type == CodeType::complement_)
	{
		// ����
		if (this->num.s.f != 0)
		{
			this->convert_to_inverse_code();
			this->convert_to_true_code();
		}
	}
	// ԭ�� -> ԭ��
	else
	{
		return;
	}
	this->code_type = CodeType::true_;
	return;
}

/**
* ����: ת����
*/
void Int::convert_to_complement_code()
{
	// ԭ�� -> ����
	if (this->code_type == CodeType::true_)
	{
		this->convert_to_inverse_code();
		this->convert_to_complement_code();
	}
	// ���� -> ����
	else if (this->code_type == CodeType::inverse_)
	{
		// ����
		if (this->num.s.f != 0)
		{
			this->num.s.x += 1;
		}
	}
	// ���� -> ����
	else
	{
		return;
	}
	this->code_type = CodeType::complement_;
	return;
}

/**
* ���ն����ƴ�ӡ����
*/
void Int::print_code_binary()
{
	// ����λ
	this->num_to_binary(&this->num.x, 32, 31);
	printf(" ");
	// ����λ
	this->num_to_binary(&this->num.x, 31, 0);
	printf("\n");
}

/**
* ʮ���ƴ�ӡ����
*/
void Int::print_num()
{
	// ת����
	this->convert_to_complement_code();
	printf("ʮ����Ϊ:%d\n", this->num.x);
}

/**
* ת������
*/
Float* Int::convert_to_float()
{
	this->convert_to_true_code();
	u_float num;
	// ����λ
	num.s.f = this->num.s.f;
	// ����10010101000001010001111010111000010100011110101110001
	unsigned long long tmp = this->num.s.x;
	unsigned long long i = 0;
	while (tmp > 1)
	{
		tmp >>= 1;
		i++;
	}
	tmp = this->num.s.x;
	num.s.e = i + E_BASE;
	// С��
	num.s.num = (tmp << (52 - i));
	// new����
	Float* ans = new Float(num.num, CodeType::true_);
	return ans;
}

/**
* ת����
*/
Int* Int::convert_to_int()
{
	return this;
}