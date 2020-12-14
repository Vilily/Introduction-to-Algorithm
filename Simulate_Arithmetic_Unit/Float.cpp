/**
* Float���ʵ��
* @Author: Bao Wenjie
* @Email: bwj_678@qq.com
* @Date: 2020/10/2
*/

#pragma once
#include "Num.h"
#include <string>

const unsigned long long FLOAT_ONES = 0XFFFFFFFFFFFFFFFF;
const unsigned int E_BASE = 1023;

Float::Float()
{
	// ������
	this->num_type = NumType::float_;
	// ����
	this->code_type = CodeType::true_;
	this->num.num = (double)0;
}

Float::Float(double num)
{
	// ������
	this->num_type = NumType::float_;
	// ��������
	this->code_type = CodeType::true_;
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
* ������ԭ��˷�
* :param a: Floatԭ����
* :param b: Floatԭ����
*/
Float Float::multiply_true_code(Float a, Float b)
{
	
	// eΪ�����ԭ��
	a.print_codes_binary();
	b.print_codes_binary();
	unsigned int e = a.get_e_true() + b.get_e_true();
	unsigned long long A = a.get_x_true();
	//Num::num_to_binary(&A, 63);
	//printf("\n");
	unsigned long long B = b.get_x_true();
	//Num::num_to_binary(&B, 63);
	//printf("\n");
	unsigned long long C = 0;
	while (A)
	{
		if (A & 1)
			C = C + B;
		C >>= 1;
		A >>= 1;
	}
	Float F;
	F.set_x(C);
	e += E_BASE;
	F.set_e(e);
	return F;
}

/**
* ����˷�
* :param a: Floatԭ����
* :param b: Floatԭ����
*/
Float Float::multiply_complement_code(Float a, Float b)
{
	return a;
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
	// ��ӡ����λ
	this->num_to_binary(&this->num, 64, 63);
	printf(" ");
	// ��ӡ����
	this->num_to_binary(&this->num, 63, 52);
	printf(" ");
	// ��ӡС��
	this->num_to_binary(&this->num, 52, 0);
	printf("\n");
}

/**
* ʮ���ƴ�ӡ����
*/
void Float::print_num()
{
	// ת����
	this->convert_to_true_code();
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
	u_int num;
	num.num = 0;
	this->convert_to_true_code();
	// e: �������
	unsigned int e = this->num.s.e;
	// x��һλ��1
	num.s.x |= 0X40000000;
	// x����λȡС��ǰ30λ
	num.s.x |= (this->num.s.num >> 22);
	// ������
	if (e >= E_BASE)
	{
		e = e - E_BASE;
		// ������Ʋ���30
		if (e < 30)
		{
			num.num >>= (30 - e);
		}
		// ����
		else
		{
			e -= 30;
			num.num <<= e;
		}

	}
	// �����ƣ�Ϊ0��
	else
	{
		num.s.x = 0;
	}
	// ����λ
	if (this->num.s.f == 0)
		num.s.f = 0;
	else
		num.s.f = 1;
	Int* ans = new Int(num.num, CodeType::true_);
	return ans;
}

/**
* ��ȡʮ�������ֵ��ַ���
*/
string Float::get_string()
{
	string ans = "";
	ans += std::to_string(this->num.num);
	return ans;
}


/**
* << ����
*/
ostream& operator<<(ostream& os, Float num)
{
	os << num.get_string();
	return os;
}

/**
* ��ȡnum(��double���long long,�����ƴ洢����)
*/
long long Float::get_num()
{
	long long ans = 0;
	ans |= (this->num.s.f << 63);
	ans |= (this->num.s.e << 51);
	ans |= this->num.s.num;
	return ans;
}

/**
* ��ȡ����λ
*/
unsigned long long Float::get_sign()
{
	return (unsigned long long)this->num.s.f;
}

/**
* ��ȡ����λ(ԭ��/ԭ�洢��ʽ)
*/
unsigned long long Float::get_x()
{
	this->convert_to_true_code();
	return (unsigned long long)this->num.s.num;
}

// ��ȡС������(0.x��ʽ)
unsigned long long Float::get_x_true()
{
	this->convert_to_true_code();
	return (this->num.s.num | ((unsigned long long)1 << 52));
}



/**
* ��ȡС������(������ʽ)
*/
unsigned long long Float::get_x_complement()
{
	this->convert_to_complement_code();
	return this->num.s.num;
}

/**
* ��ȡ����(����/Ӳ���洢��ʽ)
*/
unsigned long long Float::get_e()
{
	return (unsigned long long)this->num.s.e;
}


/**
* ��ȡ����(ԭ��)
*/
unsigned long long Float::get_e_true()
{
	return this->num.s.e - E_BASE;
}

/**
* ���ý���(����/Ӳ���洢��ʽ)
*/
void Float::set_e(unsigned long long e)
{
	this->num.s.e = e;
}

/**
* ����С��(ԭ��/Ӳ���洢��ʽ)
*/
void Float::set_x(unsigned long long x)
{
	this->num.s.num = x;
}
