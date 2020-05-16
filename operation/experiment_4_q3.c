#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <windows.h>

void test()
{
    int i = 0;
    while (i < 10000000)
    {
        i++;
    }
}

void method1()
{
    clock_t start = clock();
    test(); //�����Ժ���
    clock_t end = clock();
    double runtime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("����һ��%f", runtime);
}

void method2()
{
    LARGE_INTEGER beginTime;
    LARGE_INTEGER endTime;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&beginTime);
    test(); //�����Ժ���
    QueryPerformanceCounter(&endTime);
    double runtime = (double)(endTime.QuadPart - beginTime.QuadPart) / frequency.QuadPart;
    printf("��������%f", runtime);
}

int main()
{
    method1();
    printf("\n");
    Sleep(1000);
    method2();
    getchar();
}
