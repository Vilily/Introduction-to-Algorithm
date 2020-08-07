//�ο���ַ https://www.bilibili.com/video/BV1ZE41177JM?p=12
//Description: Jarvis March�㷨
//Author: Bao Wenjie
//Date: 2020/8/4
//Email: bwj_678@qq.com
#pragma once
#include "convex hull.h"




/**
* @description: Jarvis March�㷨 O(n2)
* @param S: ��ļ���
* @param n: ��ĸ���
*/
void Jarvis_March(Point S[], int n)
{
	/*����Ԥ����*/
	for (int i(0); i < n; i++)
		S[i].setExtreme(false);
	int ltl = LTL(S, n);
	int k = ltl;


	do {
		S[k].setExtreme(true);
		// k:��һ���ڵ�
		// s:��¼��һ��ѡ�нڵ�
		// t:ö��ÿ���ڵ�
		int s = -1;
		for (int t = 0; t < n; t++)
			if(t != k && t != s &&
				(s == -1 || ! ToLeft(S[k], S[s], S[t])))
				/* ����s�� */
				s = t;
		k = s;
	// ����������
	} while (ltl != k);
}

/**
* @decription: LeftMost-Then-LowMost��ʼ��
* @param S: ��㼯��
* @param n: ������
*/
int LTL(Point S[], int n)
{
	int ltl = 0;
	for (int k = 1; k < n; k++)
		if (S[k].getY() < S[ltl].getY() ||
			(S[k].getY() == S[k].getY() && S[k].getX() < S[ltl].getX()))
			ltl = k;
	return ltl;
}