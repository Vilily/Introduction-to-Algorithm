//�ο���ַ https://www.bilibili.com/video/BV1ZE41177JM?p=67
//Description: �����ཻ���
//Author: Bao Wenjie
//Date: 2020/8/4
//Email: bwj_678@qq.com

#include <algorithm>
#include"geometric intersection.h"

/**
* @description: ��������Ƿ����ཻ���
* @param S: ���伯��
* @param n: �������
*/
bool Interval_Intersection_Detection(Interval S[], int n)
{
	/* ������� */
	EndPoint** EP = new EndPoint * [2 * n];
	for (int i = 0; i < n; i++)
	{
		EP[i * 2] = new EndPoint(S[i].left, Left);
		EP[i * 2 + 1] = new EndPoint(S[i].right, Right);
	}
	/* ���� */
	qsort(EP, 2 * n, sizeof(EndPoint*), cmp);
	/* ɨ�� */
	bool ans = false;
	int last = EP[0]->endpoint;
	for (int i = 1; i < 2 * n; i++)
	{
		if (EP[i]->endpoint == last)
		{
			ans = true;
			break;
		}
		else
		{
			last = EP[i]->endpoint;
		}
	}
	return ans;
}

/**
* @description: �ȽϺ���
*/
int cmp(const void* a, const void* b)
{
	return (*(EndPoint**)a)->value - (*(EndPoint**)b)->value;
}