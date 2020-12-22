/**
* Num�࣬Int�ࡢFloat��Ķ���
* @Author: Bao Wenjie
* @Email: bwj_678@qq.com
* @Date: 2020/10/2
*/

#pragma once
#include "INT.h"
#include "FLOAT.h"
#include <iostream>
#include <ostream>
#include <string.h>

using std::ostream;
using std::istream;
using std::string;
using std::operator+;
using std::operator-;

/**
* ������𡾸�������������
*/
enum class NumType
{
	int_ = 1,
	float_ = 2
};

/**
* �������ԭ�롢���롢���롿
*/
enum class CodeType
{
	true_ = 1,
	inverse_ = 2,
	complement_ = 3
};

/**
* ���ֳ���
*/
class Num;

/**
* ������
*/
class Int;

/**
* ��������
*/
class Float;

/************************************* ���ֳ��� ******************************************/
class Num
{
public:
	Num();
	~Num();
	/***** ���� *****/
	// �������ͱ�ʶ��
	NumType num_type;
	// �������ͱ�ʶ��
	CodeType code_type;

	/***** ���󷽷� *****/
	// תԭ��
	virtual void convert_to_true_code() = 0;
	// ת����
	virtual void convert_to_inverse_code() = 0;
	// ת����
	virtual void convert_to_complement_code() = 0;
	// ת����
	virtual Int* convert_to_int() = 0;
	// ת������
	virtual Float* convert_to_float() = 0;
	// �����ƴ�ӡ����
	virtual void print_code_binary() = 0;
	// ʮ���ƴ�ӡ����
	virtual void print_num() = 0;
	// ��ȡ������
	virtual long long get_num() = 0;
	// ��ȡ����λ
	virtual unsigned int get_sign() = 0;
	// ��ȡ����λ
	virtual unsigned long long get_decimal() = 0;
	// ��ȡ����λ
	virtual unsigned int get_exponent() = 0;

	/***** ��̬���� *****/
	// ������ִ洢�Ķ�������ʽ
	static void num_to_binary(void* p, int high, int low = 0);

	/***** ��ͨ���� *****/
	// ��ӡ���б������
	void print_codes_binary();	

	/***** ��Ԫ���� *****/
	// << ����
	friend ostream& operator<<(ostream& os, Num* num);

};


/************************************* ������ ******************************************/
class Int : public Num
{
public:
	Int();
	Int(int num);
	Int(int num, CodeType type);
	~Int();

private:
	// ����
	u_int num;

public:
	// תԭ��
	void convert_to_true_code();
	// ת����
	void convert_to_inverse_code();
	// ת����
	void convert_to_complement_code();
	// ת������
	Float* convert_to_float();
	// ת����
	Int* convert_to_int();
	// �������
	string get_string();

	// ��ӡ����
	void print_code_binary();
	// ʮ���ƴ�ӡ����
	void print_num();
	// ��ȡ������
	long long get_num();
	// ��ȡ����λ
	unsigned int get_sign();
	// ��ȡ����λ
	unsigned long long get_decimal();
	// ��ȡ����λ
	unsigned int get_exponent();

	// << ����
	friend ostream& operator<<(ostream& os, Int num);
	// >> ����
	friend ostream& operator<<(ostream& os, Int num);
	// + ����
	Int operator+(Int& num);
	// - ����
	Int operator-(Int& num);

};

/************************************* �������� ******************************************/
class Float : public Num
{
public:
	Float();
	Float(double num);
	Float(double num, CodeType type);
	~Float();
	/* ԭ��һλ�˷� */
	static Float multiply_true_code(Float a, Float b);
	/* ����һλ�˷� */
	static Float multiply_complement_code(Float a, Float b);

private:
	// ������
	u_float num;
	
public:
	/* ���� */
	// С��λ��
	static const int Decimal_Num = 52;
	// ����λ��
	static const int Exponent_Num = 11;
	// ����λ��
	static const int Sign_Num = 1;
	// ����ƫ��ֵ
	static const unsigned int E_BASE = 1023;
	// ȫΪ1
	static const unsigned long long FLOAT_ONES = 0XFFFFFFFFFFFFFFFF;


	/* ���� */
	// תԭ��
	void convert_to_true_code();
	// ת����
	void convert_to_inverse_code();
	// ת����
	void convert_to_complement_code();
	// ת������
	Float* convert_to_float();
	// ת����
	Int* convert_to_int();
	// ��ӡ����
	void print_code_binary();
	// ʮ���ƴ�ӡ����
	void print_num();
	// �������
	string get_string();

	// ��ȡ������
	long long get_num();
	// ��ȡ����λ
	unsigned int get_sign();
	// ��ȡС������(�洢��ʽ)
	unsigned long long get_decimal();
	// ��ȡС������(ԭ����ʽ/����������λ)
	unsigned long long get_decimal_true();
	// ��ȡС������(������ʽ/˫������ʽ)
	unsigned long long get_decimal_complement();
	// ��ȡ����(������ʽ)
	unsigned int get_exponent();
	// ��ȡ����(ԭ����ʽ)
	unsigned int get_exponent_true();

	// ���ý���
	void set_exponent(unsigned long long e);
	// ����С��
	void set_decimal(unsigned long long x);
	// ���÷���λ
	void set_sign(unsigned int sign);
	// ��Ԫ���������
	friend ostream& operator<<(ostream& os, Float num);
};


