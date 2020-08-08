//�ο���ַ https://www.bilibili.com/video/BV1ZE41177JM?p=18
//Description: ͹�������Incremental�㷨
//Author: Bao Wenjie
//Date: 2020/8/4
//Email: bwj_678@qq.com
#include "convex hull.h"

/**
* @description: Increment�㷨
* @param S: �㼯
* @param n: ����
*/
void Incremental_Construction(Point S[], int n)
{
	/* ��ʼ��Ϊfalse(��͹���ĵ�) */
	for (int i = 0; i < n; i++)
		S[i].setExtreme(false);
	/* ��ѭ�� */
	LinkedList* ll = new LinkedList();
	ll->addHeadNext(S);
	ll->addHeadNext(S + 1);
	for (int i = 2; i < n; i++)
		Add_Point(ll, S + i);
	/* ��� */
	LinkedListPoint* head = ll->getHead();
	LinkedListPoint* tmp = head->getNext();
	head->getPoint()->setExtreme(true);
	while (tmp != head)
	{
		tmp->getPoint()->setExtreme(true);
		tmp = tmp->getNext();
	}
}

/**
* @description: �ж�point���ܷ���ӵ�����ll��
* @param ll: ѭ������
* @param point: ��
*/
void Add_Point(LinkedList* ll, Point* point)
{
	LinkedListPoint* tmp = ll->getHead();
	/* �����С��2��ֱ����� */
	if (ll->getSize() < 2)
		ll->addToNext(tmp, point);
	else 
	{
		LinkedListPoint* a = nullptr;
		LinkedListPoint* b = nullptr;
		bool a_ = ToLeft(*point, *tmp->getPoint(), *tmp->getNext()->getPoint());
		while (!(a && b))
		{
			bool t = ToLeft(*point, *tmp->getPoint(), *tmp->getNext()->getPoint());
			if (a_ == true && t == false)
				a = tmp;
			else if(a_ == false && t == true)
				b = tmp;
			a_ = t;
		}
		ll->linkAB(a, b);
		ll->addToNext(a, point);
	}
}