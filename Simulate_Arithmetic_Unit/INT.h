/**
* s_int,u_int����
* @Author: Bao Wenjie
* @Email: bwj_678@qq.com
* @Date: 2020/10/2
*/
#pragma once

struct s_int
{
	int x : 31; // ����λ
	int f : 1;  // ����λ
};

typedef struct s_int s_int;

union u_int
{
	s_int s;
	int x;
};

typedef union u_int u_int;
