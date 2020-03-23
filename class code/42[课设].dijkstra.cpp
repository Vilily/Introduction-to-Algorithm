#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAX 100
#define INF 99999


typedef struct graph
{
    char vexs[MAX];       // ���㼯��
    int vexnum;           // ������
    int edgnum;           // ����
    int matrix[MAX][MAX]; // �ڽӾ���
}Graph, * PGraph;

// �ߵĽṹ��
typedef struct EdgeData
{
    char start; // �ߵ����
    char end;   // �ߵ��յ�
    int weight; // �ߵ�Ȩ��
}EData;



//G��ͼ��root��ʼ�ڵ㣬prevÿ���ڵ����·��ǰ���ڵ㣬distÿ���ڵ�����·
void dijkstra(Graph G, int root, int prev[], int dist[])
{
    int i, j, k;
    int min;
    int tmp;
    int flag[MAX];      // flag[i]=1��ʾ"����vs"��"����i"�����·���ѳɹ���ȡ��

    // ��ʼ��
    for (i = 0; i < G.vexnum; i++)
    {
        flag[i] = 0;              // ����i�����·����û��ȡ����
        prev[i] = 0;              // ����i��ǰ������Ϊ0��
        dist[i] = G.matrix[root][i];// ����i�����·��Ϊ"����vs"��"����i"��Ȩ��
    }

    // ��"����vs"������г�ʼ��
    flag[root] = 1;
    dist[root] = 0;

    // ����G.vexnum-1�Σ�ÿ���ҳ�һ����������·����
    for (i = 1; i < G.vexnum; i++)
    {
        // Ѱ�ҵ�ǰ��С��·����kΪ����
        min = MAX;
        for (j = 0; j < G.vexnum; j++)
        {
            if (flag[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }
        // ���"����k"Ϊ�Ѿ���ȡ�����·��
        flag[k] = 1;

        // ����������ǰ���·����ǰ������
        for (j = 0; j < G.vexnum; j++)
        {

            tmp = (G.matrix[k][j] == INF ? INF : (min + G.matrix[k][j])); // ��ֹ���
            if (flag[j] == 0 && (tmp < dist[j]))
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    // ��ӡdijkstra���·���Ľ��
    printf("dijkstra(%c): \n", G.vexs[root]);
    for (i = 0; i < G.vexnum; i++)
        printf("  shortest(%d, %d)=%d\n", G.vexs[root], G.vexs[i], dist[i]);
}

int main()
{
    char vexs[100];
    int matrix[100][100];
    int vlen = 7;
    int i, j;
    printf("Please input the number of points\n");
    scanf_s("%d", &vlen);
    for (i = 0; i < vlen; i++)
        vexs[i] = i;
    printf("Please input the matrix of graph, -1 represents the MAX\n");
    for (i = 0; i < vlen; i++)
    {
        for (j = 0; j < vlen; j++)
        {
            scanf_s("%d", &matrix[i][j]);
        }
    }

    Graph* pG;

    // ����"������"��"����"
    if ((pG = (Graph*)malloc(sizeof(Graph))) == NULL)
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // ��ʼ��"������"
    pG->vexnum = vlen;
    // ��ʼ��"����"
    for (i = 0; i < pG->vexnum; i++)
        pG->vexs[i] = vexs[i];

    // ��ʼ��"��"
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            pG->matrix[i][j] = (matrix[i][j] == -1)? INF : matrix[i][j];

    // ͳ�Ʊߵ���Ŀ
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            if (i != j && pG->matrix[i][j] != INF)
                pG->edgnum++;
    pG->edgnum /= 2;
    int prev[MAX] = { 0 };
    int dist[MAX] = { 0 };

    dijkstra(*pG, 0, prev, dist);
}