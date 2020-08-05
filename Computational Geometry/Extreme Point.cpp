//�ο���ַ https://www.bilibili.com/video/BV1ZE41177JM?p=12
//Description: ͹������ļ���ⷨ
//Author: Bao Wenjie
//Date: 2020/8/4
//Email: bwj_678@qq.com

#include <iostream>
#include "..\Computational Geometry\Point.cpp"

using namespace::std;

/**
* @description: ��������ʽ�������������
* @param a\b\p: ������������
* @return area: ���
*/
double Area2(Point& a, Point& b, Point& p)
{
	return a.getX() * b.getY() - a.getY() * b.getX() +
		   b.getX() * p.getY() - b.getY() * p.getX() +
		   p.getX() * a.getY() - p.getY() * a.getX();
}
/**
* @description: �жϵ�p�Ƿ���a->b���������
* @param a\b: a->b��������β
* @param p: ���жϵĵ�
* ps:
*
*      |a.x  a.y  1|
* 2s = |b.x  b.y  1|
*      |p.x  p.y  1|
*/
bool ToLeft(Point& a, Point& b, Point& p)
{
	return Area2(a, b, p) > 0;
}

/**
* @description: �ж�p���Ƿ���a��b��c���㹹�ɵ�������������
* @param a\b\c: �������������������
* @param p: ���жϵĵ�
* @return isIn: �Ƿ�������
*/
bool InTriangle(Point& a, Point& b, Point& c, Point& p)
{
	bool tmp1 = ToLeft(a, b, p);
	bool tmp2 = ToLeft(b, c, p);
	bool tmp3 = ToLeft(c, a, p);
	if (tmp1 == tmp2 && tmp2 == tmp3)
		return true;
	else
		return false;
}
/**
* ����͹��
* @param S: �������
* @param n: ��ĸ���
* @return void
**/
void extremePoint(Point S[], int n)
{
	// �����нڵ��ʼ��Ϊ͹��
	for (int s = 0; s < n; s++)
	{
		S[s].setExtreme(true);
	}
	for (int p = 0; p < n; p++)
	{
		for (int q = p + 1; q < n; q++)
		{
			for (int r = q + 1; r < n; r++)
			{
				for (int s = 0; s < n; s++)
				{
					if (s == p || s == q || s == r || !S[s].getExtreme())
						continue;
					if (InTriangle(S[p], S[q], S[r], S[s]))
						S[s].setExtreme(false);
				}
			}
		}
	}
}