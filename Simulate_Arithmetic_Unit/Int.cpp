/**
* Int���ʵ��
* @Author: Bao Wenjie
* @Email: bwj_678@qq.com
* @Date: 2020/10/2
*/

#pragma once
#include "Num.h"
#include <string>

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
	this->num.num = 0;
}

Int::Int(int num)
{
	// ����
	this->num_type = NumType::int_;
	// ����
	this->code_type = CodeType::complement_;
	this->num.num = num;
}

Int::Int(int num, CodeType type)
{
	// ����
	this->num_type = NumType::int_;
	// ����
	this->code_type = type;
	this->num.num = num;

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
		if (this->num.s.sign != 0)
		{
			this->num.s.decimal ^= ONES;
		}
	}
	// ���� -> ����
	else if (this->code_type == CodeType::complement_)
	{
		// ����
		if (this->num.s.sign != 0)
		{
			this->num.s.decimal -= 1;
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
		if (this->num.s.sign != 0)
		{
			this->num.s.decimal ^= ONES;
		}
	}
	// ���� -> ԭ��
	else if (this->code_type == CodeType::complement_)
	{
		// ����
		if (this->num.s.sign != 0)
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
		if (this->num.s.sign != 0)
		{
			this->num.s.decimal += 1;
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
	this->num_to_binary(&this->num.num, 32, 31);
	printf(" ");
	// ����λ
	this->num_to_binary(&this->num.num, 31, 0);
	printf("\n");
}

/**
* ʮ���ƴ�ӡ����
*/
void Int::print_num()
{
	// ת����
	this->convert_to_complement_code();
	printf("ʮ����Ϊ:%d\n", this->num.num);
}

/**
* ת������
*/
Float* Int::convert_to_float()
{
	this->convert_to_true_code();
	u_float num;
	// ����λ
	num.s.sign = this->num.s.sign;
	// ����10010101000001010001111010111000010100011110101110001
	unsigned long long tmp = this->num.s.decimal;
	unsigned long long i = 0;
	while (tmp > 1)
	{
		tmp >>= 1;
		i++;
	}
	tmp = this->num.s.decimal;
	num.s.exponent = i + E_BASE;
	// С��
	num.s.decimal = (tmp << (52 - i));
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

/**
* ��ȡʮ�������ֵ��ַ���
*/
string Int::get_string()
{
	string ans = "";
	ans += std::to_string(this->num.num);
	return ans;
}

/**
* << ����
*/
ostream& operator<<(ostream& os, Int num)
{
	os << num.get_string();
	return os;
}

/**
* ��ȡnum
*/
long long Int::get_num()
{
	long long ans = 0;
	ans |= this->num.num;
	return ans;
}

/**
* ��ȡ����λ
*/
unsigned int Int::get_sign()
{
	return this->num.s.sign;
}

/**
* ��ȡ����λ
*/
unsigned long long Int::get_decimal()
{
	return this->num.s.decimal;
}

/**
* ��ȡ����
*/
unsigned int Int::get_exponent()
{
	return 0;
}

/**
* + ����
*/
Int Int::operator+(Int& num)
{
	// ��ȡA�Ĳ���
	this->convert_to_complement_code();
	long long a = this->get_num();
	// ��ȡB�Ĳ���
	num.convert_to_complement_code();
	long long b = num.get_num();
	int s = 0;
	int c = 0;
	for (int i(0); i < 32; i++)
	{
		int a_ = (a >> i) & 1;
		int b_ = (b >> i) & 1;
		// ��λ��
		int c1 = (a_) ^ (b_) ^ s;
		// ��λ
		s = (a_ & b_) | (a_ & s) | (b_ & s);
		// 
		c |= (c1 << i);
	}
	Int ans = { c, CodeType::complement_ };
	return ans;
}