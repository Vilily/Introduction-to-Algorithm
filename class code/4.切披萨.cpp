#include <stdio.h>

using namespace::std;

int PizzaCut(int n)
{
	if (n == 0)
		return 1;
	return (PizzaCut(n - 1) + n);
}

int main()
{
	int n;
	scanf_s("%d", &n);
	printf_s("%d\n", PizzaCut(n));
	return 0;
}


/*
��������n�������ʹһ������������n��
��0��ʱ����1��
*/
