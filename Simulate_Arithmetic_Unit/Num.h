#pragma once
#include "INT.h"

enum NumType
{
	int_ = 1,
	float_ = 2
};


/************************************* ���ֳ��� ******************************************/
class Num
{
public:
	Num();
	~Num();
	// ������ִ洢�Ķ�������ʽ
	static void num_to_binary(void* p, int n);

protected:
	// ��ʶ��
	NumType is_float;
private:
};


/************************************* ������ ******************************************/
class Int : Num
{
public:
	Int();
	~Int();

private:

};




/************************************* �������� ******************************************/
class Float : Num
{
public:
	Float();
	~Float();

private:

};


