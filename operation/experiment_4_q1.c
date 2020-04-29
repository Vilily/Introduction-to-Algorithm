#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define TRUE 1
#define FALSE 0
#define INVALID -1

#define ALL_INSTRUCTION 320 //�� 320 ��ָ��
#define ALL_PAGE 32 //����ҳ�� 32
#define clear_period 50

//ҳ��
typedef struct {
    int pageIndex;//ҳ��
    int pageFrameIndex;//ҳ���
    int counter;//һ�������ڷ��ʸ�ҳ�Ĵ���
    int time;//�������ʱ��
}PageFrame;

//ҳ��
PageFrame pf[32];

//ҳ����ƽṹ
typedef struct pfc_struct {
    int pn;
    int pfn;
    struct pfc_struct* next;
}pfc_type;

pfc_type pfc[32];
//����ҳͷָ�룬æҳͷָ�룬æҳβָ��
pfc_type* freepf_head, * busypf_head, * busypf_tail;
//ȱҳ����
int disaffect;
//ָ��������
int a[ALL_INSTRUCTION];
//ÿ��ָ���ҳ��ҳ��ƫ��
int page[ALL_INSTRUCTION], offset[ALL_INSTRUCTION];

void initialize(int total_pf);
void FIFO(int total_pf);
void LRU(int total_pf);

int main()
{
    //�ý��̺���Ϊ��ʼ����������е�����
    srand(10 * GetCurrentProcessId());
    int s = (float)319 * rand() / 32767 / 32767 / 2 + 1;
    //����ָ�����
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        if (s < 0 || s > 319)
        {
            printf("when i == %d,error: s == %d\n", i, s);
            exit(0);
        }
        //����ѡһָ����ʵ� m
        a[i] = s;
        //˳��ִ����һ��ָ��
        a[i + 1] = a[i] + 1;
        //ִ��ǰ��ַָ�� m
        a[i + 2] = (float)a[i] * rand() / 32868 / 32767 / 2;
        //˳��ִ��һ��ָ��
        a[i + 3] = a[i + 2] + 1;
        s = (float)(318 - a[i + 2]) * rand() / 32767 / 32767 / 2 + a[i + 2] + 2;
        if ((a[i + 2] > 318) || (s > 319)) {
            printf("a[%d + 2],a number which is: %d and s = %d\n", i, a[i + 2], s);
        }
        //��ָ�����б��ҳ��ַ��
        for (int i = 0; i < ALL_INSTRUCTION; i++)
        {
            page[i] = a[i] / 10;
            offset[i] = a[i] % 10;
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
    for (int i = 0; i < total_pf - 1; i++)
    {
        pfc[i].next = &pfc[i + 1];
        pfc[i].pfn = i;
    }
    pfc[total_pf - 1].next = NULL;
    pfc[total_pf - 1].pfn = total_pf - 1;
    freepf_head = &pfc[0];
}


void FIFO(int total_pf)
{
    //��ʼ��������ݽṹ
    initialize(total_pf);
    busypf_head = busypf_tail = NULL;
    int disfeffect = 0;
    pfc_type* p;
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        //ҳ��ʧЧ
        if (pf[page[i]].pageFrameIndex == INVALID) {
            //ʧЧ����
            disfeffect += 1;
            //�޿���ҳ��
            if (freepf_head == NULL) {
                p = busypf_head->next;
                pf[busypf_head->pn].pageFrameIndex = INVALID;
                //�ͷ�æҳ����еĵ�һ��ҳ��
                freepf_head = busypf_head;
                freepf_head->next = NULL;
                busypf_head = p;
            }
            //�� FIFO ��ʽ������ҳ�����ڴ�
            p = freepf_head->next;
            freepf_head->next = NULL;
            freepf_head->pn = page[i];
            pl[page[i]].pfn = freepf_head->pfn;
            if (busypf_tail == NULL)
            {
                busypf_head = busypf_tail = freepf_head;
            }
            else
            {
                //free ҳ�����һ��
                busypf_tail->next = freepf_head;
                busypf_tail = freepf_head;
            }
            freepf_head = p;
        }
    }
    printf("FIFO: %6.4f", 1 - (float)disfeffect / 320);
}

/**
 * �������ʹ��
 * total_pf: �û����̵��ڴ�ҳ��
 */
void LRU(int total_pf)
{
    initialize(total_pf);
    int present_time = 0;
    int diseffect = 0;
    for (int i = 0; i < ALL_INSTRUCTION; i++)
    {
        //ҳ��ʧЧ
        if (pl[page[i]].pfn == INVALID) {
            diseffect++;
            //�޿���ҳ��
            if (freepf_head == NULL) {
                int min = 32767;
                int minj;
                //�ҳ� time ����Сֵ
                for (int j = 0; j < ALL_PAGE; j++)
                {
                    if (min > pl[j].time && pl[j].pfn != INVALID) {
                        min = pl[j].time;
                        minj = j;
                    }
                    //�ڳ�һ����Ԫ
                    freepf_head = &pfc[pl[minj].pfn];
                    pl[minj].pfn = INVALID;
                    pl[minj].time = -1;
                    freepf_head->next = NULL;
                }
                //�п���ҳ����Ϊ��Ч
                pl[page[i]].pfn = freepf_head->pfn;
                pl[page[i]].time = present_time;
                //����һ�� free ҳ��
                freepf_head = freepf_head->next;
            }
            else
            {
                //���У������Ӹõ�Ԫ�ķ��ʴ���
                pl[page[i]].time = present_time;
            }
        }
        present_time++;
    }
    printf("LRU: %6.4f", 1 - (float)diseffect / 320);
}