#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <queue>

#define TRUE 1
#define FALSE 0
#define INVALID -1

#define ALL_INSTRUCTION 320
#define ALL_PAGE 32
#define QUICK_PAGE  8
#define clear_period 50

//ҳ��
typedef struct {
    int pageIndex;     //ҳ��
    int pageFrameIndex;//ҳ���
    int counter;       //һ�������ڷ��ʸ�ҳ�Ĵ���
    int time;          //�������ʱ��
}PageFrame;
typedef PageFrame* pPageFrame;

//ҳ��
PageFrame pf[32];

////ҳ����ƽṹ
//typedef struct pfc_struct {
//    int pn;
//    int pfn;
//    struct pfc_struct* next;
//}pfc_type;
//
//pfc_type pfc[32];
////����ҳͷָ�룬æҳͷָ�룬æҳβָ��
//pfc_type* freepf_head, * busypf_head, * busypf_tail;
////ȱҳ����


int quickPageCount;
//���ҳ����
int errorTime;
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
    //�ý��̺���Ϊ��ʼ����������е�����
    srand(10 * GetCurrentProcessId());
    int s = (rand() % 320) + 1;
    //����ָ�����
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        commands[i] = s;
        commands[i + 1] = commands[i] + 1;
        commands[i + 2] = (s * rand()) % 320 + 1;
        commands[i + 3] = commands[i + 2] + 1;

        //��ָ�����б��ҳ��ַ��
        for (int i = 0; i < ALL_INSTRUCTION; i++)
        {
            page[i] = commands[i] / 10;
            offset[i] = commands[i] % 10;
        }
        //�û��ڴ湤������ 4 ��ҳ�浽 32 ��ҳ��
        for (int i = 4; i < 32; i++)
        {
            printf("%2d page frames", i);
            //������ FIFO �û�ʱ���� i ��ҳ��ʱ��������
            FIFO(i);
            //������ LRU �û�ʱ���� i ��ҳ��ʱ��������
            LRU(i);
            printf("\n");
        }
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
//    for (int i = 0; i < total_pf - 1; i++)
//    {
//        pfc[i].next = &pfc[i + 1];
//        pfc[i].pfn = i;
//    }
//    pfc[total_pf - 1].next = NULL;
//    pfc[total_pf - 1].pfn = total_pf - 1;
//    freepf_head = &pfc[0];
}


void FIFO(int total_pf)
{
    //��ʼ��������ݽṹ
    initialize(total_pf);
    std::queue<int> Q;
    int errorTime = 0;
    //pfc_type* p;
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        //ҳ��ʧЧ
        if (pf[page[i]].pageFrameIndex == INVALID) {
            //ʧЧ����
            errorTime += 1;
            //�޿���ҳ��
            if (quickPageCount >= 10)
            {
                int outPage = Q.front();
                pf[outPage].pageFrameIndex = INVALID;
                int inPage = page[i];
                pf[inPage].pageFrameIndex = inPage;
                Q.push(inPage);
            }
            else
            {
                int inPage = page[i];
                pf[inPage].pageFrameIndex = inPage;
                Q.push(inPage);
                quickPageCount++;
            }
        }
    }
    printf("FIFO: %6.4f", 1 - (float)errorTime / 320);
}

/**
 * �������ʹ��
 * total_pf: �û����̵��ڴ�ҳ��
 */
void LRU(int total_pf)
{
    initialize(total_pf);
    int presentTime = 0;
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        //ҳ��ʧЧ
        if (pf[page[i]].pageFrameIndex == INVALID) {
            //ʧЧ����
            errorTime++;
            //�޿���ҳ��
            if (quickPageCount >= QUICK_PAGE) {
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
                //���У������Ӹõ�Ԫ�ķ��ʴ���
                pf[page[i]].pageFrameIndex = page[i];
            }
        }
        pf[page[i]].time = presentTime;
        presentTime++;
    }
    printf("LRU: %6.4f", 1 - (float)errorTime / 320);
}


void OPT(int numCommand)
{
    initialize(numCommand);
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        //ҳ��ȱʧ
        if (pf[page[i]].pageFrameIndex == INVALID)
        {
            //ʧЧ����
            errorTime++;


        }
        //
    }
}