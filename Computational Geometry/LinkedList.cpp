//Description: LinkedList��ʵ��
//Author: Bao Wenjie
//Date: 2020/8/4
//Email: bwj_678@qq.com

#include "LinkedList.h"

/***********************************  LikedListPoint  *************************************/

LinkedListPoint::LinkedListPoint(Point* point)
{
	this->point = point;
	this->last = nullptr;
	this->next = nullptr;
}

void LinkedListPoint::setNext(LinkedListPoint* next)
{
	this->next = next;
}

void LinkedListPoint::setLast(LinkedListPoint* last)
{
	this->last = last;
}

LinkedListPoint* LinkedListPoint::getNext()
{
	return this->next;
}

LinkedListPoint* LinkedListPoint::getLast()
{
	return this->last;
}

void LinkedListPoint::setPoint(Point* point)
{
	this->point = point;
}

Point* LinkedListPoint::getPoint()
{
	return this->point;
}

LinkedListPoint::LinkedListPoint()
{
	this->point = nullptr;
	this->last = nullptr;
	this->next = nullptr;
}

/************************************  LikedList  **************************************/
LinkedList::LinkedList()
{
	this->head = nullptr;
	this->size = 0;
}

LinkedList::~LinkedList()
{
	LinkedListPoint* tmp = this->head;
	this->head->setNext(nullptr);
	while (tmp)
	{
		LinkedListPoint* tmp_ = tmp->getNext();
		delete(tmp);
		tmp = tmp_;
	}
}

LinkedListPoint* LinkedList::getHead()
{
	return this->head;
}

int LinkedList::getSize()
{
	return this->size;
}

/**
* @description: ��ӽ�㵽nowP����һ��
* @param nowP: ��ǰ�ڵ�
* @param point: ����ӵĽڵ������
*/
void LinkedList::addToNext(LinkedListPoint* nowP, Point* point)
{
	LinkedListPoint* tmp = new LinkedListPoint(point);
	tmp->setNext(nowP->getNext());
	tmp->setLast(nowP);
	nowP->setNext(tmp);
	tmp->getNext()->setLast(tmp);
	this->size++;
}

/**
* @description: ����a->next��b
* @param a: ǰ��Ľڵ�
* @param b: ����Ľڵ�
*/
void LinkedList::linkAB(LinkedListPoint* a, LinkedListPoint* b)
{
	LinkedListPoint* tmp = a->getNext();
	/* ����A->B */
	a->setNext(b);
	b->setLast(a);
	/* �ͷ�AB�м�ռ� */
	while (tmp != b && tmp != nullptr)
	{
		LinkedListPoint* tmp_ = tmp->getNext();
		if (tmp == this->head)
			this->head = a;
		delete(tmp);
		this->size--;
		tmp = tmp_;
	}
}

/**
* @description: ��ӽڵ㵽Head����һ��
*/
void LinkedList::addHeadNext(Point* point)
{
	if (this->head == nullptr)
	{
		this->head = new LinkedListPoint(point);
		this->head->setNext(this->head);
		this->head->setLast(this->head);
		this->size++;
	}
	else
	{
		LinkedListPoint* tmp = new LinkedListPoint(point);
		tmp->setNext(this->head->getNext());
		tmp->getNext()->setLast(tmp);
		tmp->setLast(this->head);
		this->head->setNext(tmp);
		this->size++;
	}
}