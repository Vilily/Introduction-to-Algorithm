//�ο���ַ https://www.bilibili.com/video/BV1ZE41177JM?p=12
//Description: ͹������ļ����㷨
//Author: Bao Wenjie
//Date: 2020/8/4
//Email: bwj_678@qq.com
#include "convex hull.h"


/**
* @description: ���p/q���Ƿ��Ǽ���
* @param S: ���еĵ�
* @param n: �ܵ���
* @param p\q: ����S[p]->S[q]
*/
bool checkEdge(Point S[], int n, int p, int q)
{
	bool LEmpty = true, REmpty = true;
	// �������е㣬�鿴�Ƿ���pqͬһ��
	for (int k = 0; k < n && (LEmpty || REmpty); k++)
	{
		if (k != p && k != q)
		{
			ToLeft(S[p], S[q], S[k]) ? LEmpty = false : REmpty = false;
		}
	}
	if (LEmpty || REmpty)
	{
		return true;
	}
	else
		return false;
}


/**
* @description: ���ü����㷨�������
* @param S: ���е������
* @param n: ����
*/
void Extreme_Edges(Point S[], int n)
{
	// ��ʼ�����е㶼���Ǽ���
	for (int k = 0; k < n; k++)
	{
		S[k].setExtreme(false);
	}

	// ö�����п��ܵı�
	for (int p = 0; p < n; p++)
	{
		for (int q = p + 1; q < n; q++)
		{
			if (checkEdge(S, n, p, q))
			{
				S[p].setExtreme(true);
				S[q].setExtreme(true);
			}
		}
	}
}