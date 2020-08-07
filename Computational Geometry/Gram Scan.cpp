//�ο���ַ https://www.bilibili.com/video/BV1ZE41177JM?p=38
//Description: ͹������ļ���ⷨ
//Author: Bao Wenjie
//Date: 2020/8/4
//Email: bwj_678@qq.com
#pragma once
#include "convex hull.h"
#include <stack>
#include <algorithm>

Point* G_LTL;


/**
* @description: Gram Scan�㷨 O(nlogn)
* @param S: �㼯
* @param n: ����
*/
void Gram_Scan(Point* S[], int n)
{
	std::stack<Point*>s;
	std::stack<Point*>t;
	/* �ҳ�ltl�������Ƶ�0λ�� */
	int ltl = LTL(S, n);
	G_LTL = S[ltl];
	S[ltl] = S[0];
	S[0] = G_LTL;
	Pre_Sort(S, n);
	/* ��ʼ��Sջ */
	Point* s0 = S[0];
	Point* s1 = S[1];
	s0->setExtreme(false);
	s1->setExtreme(false);
	s.push(s0);
	s.push(s1);
	/* ��ʼ��Tջ */
	for (int i(n - 1); i > 1; i--)
	{
		t.push(S[i]);
		S[i]->setExtreme(false);
	}
	/* ��ѭ�� */
	while (!t.empty())
	{
		if (ToLeft(*s0, *s1, *t.top()))
		{
			s.push(t.top());
			t.pop();
			s0 = s1;
			s1 = s.top();
		}
		else
		{
			s.pop();
			s1 = s0;
			s.pop();
			s0 = s.top();
			s.push(s1);
		}
	}
	/* �����͹���ϵĵ� */
	while (!s.empty())
	{
		s.top()->setExtreme(true);
		s.pop();
	}
}

/**
* @description: ����ʱ������
* @param S; �㼯
*/
void Pre_Sort(Point* S[], int n)
{
	qsort(S + 1, n - 1, sizeof(Point*), compare);
}

/**
* @description: �ȽϺ���
*/
int compare(const void* a, const void* b)
{
	Point* p = *(Point**)a;
	Point* q = *(Point**)b;
	if (ToLeft(*G_LTL, *p, *q))
		return -1;
	else
		return 1;
}


/**
* @decription: LeftMost-Then-LowMost��ʼ��
* @param S: ��㼯��
* @param n: ������
*/
int LTL(Point* S[], int n)
{
	int ltl = 0;
	for (int k = 1; k < n; k++)
	{
		if ((*S[k]).getY() < (*S[ltl]).getY() ||
			((*S[k]).getY() == (*S[ltl]).getY() && (*S[k]).getX() < (*S[ltl]).getX()))
		{
			ltl = k;
		}
	}
	return ltl;
}