#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct node {
	int data;
	struct node* next;
}Node;

/*
�͵����÷�

�ȼٶ���һ�����������Խ���headΪͷ���ĵ��������򣬲������µ�ͷ��㡣
����������������������⣺�������Ϊ��ǰ��ͷ�������ಿ�֣��ݹ�Ĺ��̾��ǣ�
�Ƚ���ͷ���������в������Ȼ������ಿ�ֽ���������󽫵�ǰ�ı�ͷ������ӵ����������β����
�ݹ����ֹ������������ֻʣһ���ڵ�ʱ��ֱ�ӷ�������ڵ㡣
*/



Node* CreatList()
{
	int n;
	scanf_s("%d", &n);
	Node* head = NULL;
	Node* tail = head;

	int x;
	scanf_s("%d", &x);
	struct node* temp;
	temp = (Node*)malloc(sizeof(struct node));
	temp->data = x;
	temp->next = NULL;

	head = temp;
	tail = temp;

	int i;
	for (i = 1; i < n; i++)
	{
		scanf_s("%d", &x);
		temp = (Node*)malloc(sizeof(struct node));
		temp->data = x;
		temp->next = NULL;

		tail->next = temp;
		tail = temp;
	}
	return head;
}

void ShowList(Node* phead)
{
	while (phead != NULL)
	{
		printf("%d ", phead->data);
		phead = phead->next;
	}
	printf("\n");
}

Node* ReverseList(Node* phead)
{
	if (phead->next == NULL)
		return phead;

	Node* temp = phead->next;
	phead->next = NULL;
	Node* tail = temp;
	Node* New = ReverseList(temp);

	if(tail!=NULL)
		tail->next = phead;

	return New;
}

int main(void)
{
	Node* phead;
	phead = CreatList();
	printf("��������ǰ������:\n");
	ShowList(phead);
	phead = ReverseList(phead);
	printf("�������ú������:\n");
	ShowList(phead);
	return 0;
}