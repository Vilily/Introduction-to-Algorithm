#pragma once

/**
* ���ֻ����洢�ṹ
*/

struct s_int
{
	int f : 1; // ����λ
	int x : 31;// ����λ
};

typedef struct s_int s_int;

union u_int
{
	s_int s;
	int x;
};

typedef union u_int u_int;
