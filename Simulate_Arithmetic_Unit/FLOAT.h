/**
* s_float��u_float���弰ʵ��
* @Author: Bao Wenjie
* @Email: bwj_678@qq.com
* @Date: 2020/10/2
*/
#pragma once


struct s_float
{
	unsigned long long num : 52; // С��
	unsigned long long e : 11;   // ����
	unsigned long long f : 1;    // ����
};

typedef struct s_float s_float;

union u_float
{
	s_float s;
	double num;
};

typedef union u_float u_float;