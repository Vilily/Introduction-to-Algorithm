#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <queue>
#include <set>
#include <time.h> 

#define TRUE 1
#define FALSE 0
#define INVALID -1

#define ALL_INSTRUCTION 320
#define ALL_PAGE 32
#define QUICK_PAGE  8
#define clear_period 50

//ҳ����
typedef struct {
    int pageIndex;     //ҳ��
    int pageFrameIndex;//ҳ���
    int counter;       //һ�������ڷ��ʸ�ҳ�Ĵ���
    int time;          //�������ʱ��
}PageFrame;
typedef PageFrame* pPageFrame;

//ҳ��
PageFrame pf[32];


//ָ��������
int commands[ALL_INSTRUCTION];
//ÿ��ָ���ҳ��ҳ��ƫ��
int page[ALL_INSTRUCTION], offset[ALL_INSTRUCTION];

void initialize(int total_pf);
void OPT(int total_pf);
void FIFO(int total_pf);
void LRU(int total_pf);

int main()
{

//����ָ�����
for (int i = 0; i < ALL_INSTRUCTION; i += 1)
{
    commands[i] = rand()%320 + 1;
}
//��ָ�����б��ҳ��ַ��
for (int i = 0; i < ALL_INSTRUCTION; i++)
{
    page[i] = commands[i] / 10;
    offset[i] = commands[i] % 10;
}

    //�û��ڴ湤������ 4 ��ҳ�浽 32 ��ҳ��
    for (int i = 4; i < 32; i++)
    {
        printf("%2d page frames ", i);
        //������ FIFO �û�ʱ���� i ��ҳ��ʱ��������
        FIFO(i);
        //������ LRU �û�ʱ���� i ��ҳ��ʱ��������
        LRU(i);
        //
        OPT(i);
        printf("\n");
    }
    getchar();
}


void initialize(int total_pf)
{
    for (int i = 0; i < ALL_PAGE; i++)
    {
        pf[i].pageIndex = i;
        pf[i].pageFrameIndex = INVALID;
        pf[i].counter = 0;
        pf[i].time = -1;
    }
}


void FIFO(int pfTotal)
{
    //��ʼ��������ݽṹ
    initialize(pfTotal);
    std::queue<int> Q;
    int PageCount = 0;
    //�����ڴ�ҳ����
    int errorTime = 0;
    //ȱҳ����
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        //ҳ��ʧЧ
        if (pf[page[i]].pageFrameIndex == INVALID)
        {
            //ʧЧ����
            errorTime += 1;
            //�޿���ҳ��
            if (PageCount >= pfTotal)
            {
                //��̭ҳ��
                int outPage = Q.front();
                Q.pop();
                pf[outPage].pageFrameIndex = INVALID;
                //����ҳ��
                int inPage = page[i];
                pf[inPage].pageFrameIndex = inPage;
                Q.push(inPage);
            }
            else
            {
                int inPage = page[i];
                pf[inPage].pageFrameIndex = inPage;
                Q.push(inPage);
                PageCount++;
            }
        }
    }
    printf("FIFO: %6.4f", 1 - (float)errorTime / ALL_INSTRUCTION);
}

void LRU(int pfTotal)
{
    initialize(pfTotal);
    int PageCount = 0;
    //�����ڴ�ҳ����
    int presentTime = 0;
    //��ǰʱ��
    int errorTime = 0;
    //ȱҳ����
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        //ҳ��ʧЧ
        if (pf[page[i]].pageFrameIndex == INVALID)
        {
            //ʧЧ����
            errorTime++;
            //�޿���ҳ��
            if (PageCount >= pfTotal) {
                int min = 32767;
                int temp;
                //�ҳ� time ����Сֵ
                for (int j = 0; j < ALL_PAGE; j++)
                {
                    if (min > pf[j].time && pf[j].pageFrameIndex != INVALID) {
                        min = pf[j].time;
                        temp = j;
                    }
                }
                pf[temp].pageFrameIndex = INVALID;
                pf[page[i]].pageFrameIndex = page[i];
            }
            else
            {
                pf[page[i]].pageFrameIndex = page[i];
                PageCount++;
            }
        }
        //���·���ʱ��
        pf[page[i]].time = presentTime;
        presentTime++;
    }
    printf(" LRU: %6.4f ", 1 - (float)errorTime / ALL_INSTRUCTION);
}


void OPT(int pfTotal)
{
    initialize(pfTotal);
    int errorTime = 0;
    //ȱҳ����
    int PageCount = 0;
    //�����ڴ�ҳ����
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        //ҳ��ȱʧ
        if (pf[page[i]].pageFrameIndex == INVALID)
        {
            //ʧЧ����
            errorTime++;
            //�ڴ�ҳ������
            if (PageCount >= pfTotal)
            {
                std::set<int> pages;
                //��̭��ҳ��
                int outPage = 0;
                for (int j = 0; j < 32; j++)
                {
                    if (pf[j].pageFrameIndex != INVALID)
                        pages.insert(j);
                }
                for (int j = i; j < ALL_INSTRUCTION; j++)
                {
                    //page[i]��set��
                    if (pages.size() > 1)
                    {
                        pages.erase(page[j]);
                    }
                    //ֻʣ���һ��
                    else
                    {
                        break;
                    }
                }
                outPage = *pages.begin();
                pf[outPage].pageFrameIndex = INVALID;
                pf[page[i]].pageFrameIndex = page[i];
            }
            //
            else
            {
                pf[page[i]].pageFrameIndex = page[i];
                PageCount++;
            }
        }
    }
    printf(" OPT: %6.4f ", 1 - (float)errorTime / ALL_INSTRUCTION);
}