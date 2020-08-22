/**
* @Title: ǰ����
* @Author: Bao Wenjie
* @Email: bwj_678@qq.com
* @Date: 2020/8/22
*/

#include <iostream>
#define MAXN	100
using namespace::std;
struct Edge
{
	int to;
	int value;
	int next;
};
Edge Graph[MAXN];
int head[MAXN];
int cnt = 0;

void init(int n);
void addedge(int from, int to, int value);
int main()
{
	// ����
	int n, m;
	cout << "������������" << endl;
	// �����
	cin >> n;
	init(n);
	// ����
	cout << "�����������" << endl;
	cin >> m;
	int from, to, value;
	for (int i(0); i < m; i++)
	{
		cin >> from >> to >> value;
		addedge(from, to, value);
	}
	// ����
	cout << "���������" << endl;
	for (int i(0); i < m; i++)
	{
		int start = head[i];
		while (start != -1)
		{
			printf("%d %d %d\n", i, Graph[start].to, Graph[start].value);
			start = Graph[start].next;
		}
	}
}


/**
* ǰ���ǳ�ʼ��
*/
void init(int n)
{
	for (int i(0); i < n; i++)
		head[i] = -1;
	cnt = 0;
}
/**
* ��ͼ����ӱ�
*/
void addedge(int from, int to, int value)
{
	Graph[cnt].to = to;
	Graph[cnt].value = value;
	Graph[cnt].next = head[from];
	head[from] = cnt++;
}
