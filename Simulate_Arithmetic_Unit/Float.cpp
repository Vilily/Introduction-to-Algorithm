/**
* Float���ʵ��
* @Author: Bao Wenjie
* @Email: bwj_678@qq.com
* @Date: 2020/10/2
*/

#pragma once
#include "Num.h"
#include <string>


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
	unsigned int Exponent = (a.get_exponent_true() + 1) + (b.get_exponent_true() + 1);
	unsigned long long A = a.get_decimal_true();
	unsigned long long B = b.get_decimal_true();
	unsigned long long Decimal = 0;
	while (A)
	{
		if (A & 1)
		{
			Decimal = Decimal + B;
		}
		Decimal >>= 1;
		A >>= 1;
	}
	while ((Decimal >> (Float::Decimal_Num)) == 0)
	{
		Decimal <<= 1;
		Exponent -= 1;
	}
	Float F;
	// С��λ
	F.set_decimal(Decimal);
	// ����λ
	Exponent += (Float::E_BASE - 1);
	F.set_exponent(Exponent);
	// ����λ�ж�
	F.set_sign(a.get_sign() ^ b.get_sign());
	return F;
}

/**
* ����������˷�
* :param a: Floatԭ����
* :param b: Floatԭ����
*/
Float Float::multiply_complement_code(Float a, Float b)
{
	// eΪ�����ԭ��
	unsigned int Exponent = (a.get_exponent_true() + 1) + (b.get_exponent_true() + 1);
	unsigned long long A = a.get_decimal_complement();
	double B_tmp = (double)b.get_num();
	unsigned long long B_ = b.get_decimal_complement();
	unsigned long long B = b.get_decimal_complement();
	unsigned long long Decimal = 0;
	while (A)
	{
		if (A & 1)
		{
			Decimal = Decimal + B;
		}
		Decimal >>= 1;
		A >>= 1;
	}
	while ((Decimal >> (Float::Decimal_Num)) == 0)
	{
		Decimal <<= 1;
		Exponent -= 1;
	}
	Float F;
	// С��λ
	F.set_decimal(Decimal);
	// ����λ
	Exponent += (Float::E_BASE - 1);
	F.set_exponent(Exponent);
	// ����λ�ж�
	F.set_sign(a.get_sign() ^ b.get_sign());
	return F;
}

/**
* ������: תԭ��
*/
void Float::convert_to_true_code()
{
	//����
	if (this->num.s.sign == 0)
	{
		this->code_type = CodeType::true_;
		return;
	}
	// ���� -> ԭ��
	else if (this->code_type == CodeType::inverse_)
	{
		this->num.s.decimal ^= FLOAT_ONES;
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
	if (this->num.s.sign == 0)
	{
		this->code_type = CodeType::inverse_;
		return;
	}
	// ԭ�� -> ����
	else if (this->code_type == CodeType::true_)
	{
		this->num.s.decimal ^= FLOAT_ONES;
	}
	// ���� -> ����
	else
	{
		this->num.s.decimal -= 1;
	}
	this->code_type = CodeType::inverse_;
	return;
}

/**
* ������: ת����
*/
void Float::convert_to_complement_code()
{
	if (this->num.s.sign == 0)
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
		this->num.s.decimal += 1;
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
	u_int int_num;
	int_num.num = 0;
	this->convert_to_true_code();
	// e: �������
	unsigned int e = this->num.s.exponent;
	// x��һλ��1
	int_num.s.decimal |= 0X40000000;
	// x����λȡС��ǰ30λ
	int_num.s.decimal |= (this->num.s.decimal >> 22);
	// ������
	if (e >= E_BASE)
	{
		e = e - E_BASE;
		// ������Ʋ���30
		if (e < 30)
		{
			int_num.num >>= (30 - e);
		}
		// ����
		else
		{
			e -= 30;
			int_num.num <<= e;
		}

	}
	// �����ƣ�Ϊ0��
	else
	{
		int_num.s.decimal = 0;
	}
	// ����λ
	if (this->num.s.sign == 0)
		int_num.s.sign = 0;
	else
		int_num.s.sign = 1;
	Int* ans = new Int(int_num.num, CodeType::true_);
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
	ans |= (this->num.s.sign << 63);
	ans |= (this->num.s.exponent << 51);
	ans |= this->num.s.decimal;
	return ans;
}

/**
* ��ȡ����λ
*/
unsigned int Float::get_sign()
{
	return this->num.s.sign;
}

/**
* ��ȡ����λ(ԭ��/ԭ�洢��ʽ)
*/
unsigned long long Float::get_decimal()
{
	this->convert_to_true_code();
	return (unsigned long long)this->num.s.decimal;
}

// ��ȡС������(0.x��ʽ)
unsigned long long Float::get_decimal_true()
{
	this->convert_to_true_code();
	return (this->num.s.decimal | ((unsigned long long)0b1 << Float::Decimal_Num));
}



/**
* ��ȡС������(������ʽ/˫������ʽ)
*/
unsigned long long Float::get_decimal_complement()
{
	this->convert_to_complement_code();
	unsigned long long tmp = this->num.s.decimal;
	if (this->num.s.sign == 1)
	{
		// ����
		tmp = tmp | (unsigned long long)0b11 << (Float::Decimal_Num + 1);
	}
	else
	{
		// ����
		tmp = tmp | (unsigned long long)0b00 << (Float::Decimal_Num + 1);
	}
	return tmp;
}

/**
* ��ȡ����(����/Ӳ���洢��ʽ)
*/
unsigned int Float::get_exponent()
{
	return this->num.s.exponent;
}


/**
* ��ȡ����(ԭ��)
*/
unsigned int Float::get_exponent_true()
{
	return (unsigned int)this->num.s.exponent - Float::E_BASE;
}

/**
* ���ý���(����/Ӳ���洢��ʽ)
*/
void Float::set_exponent(unsigned long long e)
{
	this->num.s.exponent = e;
}

/**
* ����С��(ԭ��/Ӳ���洢��ʽ)
*/
void Float::set_decimal(unsigned long long x)
{
	this->num.s.decimal = x;
}

/**
* ���÷���λ(0-1/Ӳ���洢��ʽ)
*/
void Float::set_sign(unsigned int sign)
{
	this->num.s.sign = sign;
}
