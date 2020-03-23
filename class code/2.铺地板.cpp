#include <stdio.h>
#include <time.h>

//�̵ذ壺��һ��1��2�ĵذ�����2��n�ĵ��棬�� �����ֲ�ͬ���̷�����C����ʵ�ֺ�����
//������� Ϊn�����ؽ��


int count(int n)
{
	if (1 == n || 0 == n)
		return 1;
	else if (n < 0)
		return 0;
	return count(n - 1) + count(n - 2);
}

int Fibonacci(int n)
{
	int temp1 = 1, temp2 = 1, fib = 0;
	if (1 == n)
		return 1;
	if (0 == n)
		return 1;
	while (--n >= 1)
	{
		fib = temp1 + temp2;
		temp1 = temp2;
		temp2 = fib;
	}
	return fib;
}

int main()
{
	int x;
	clock_t begin, end;
	/*for (int i = 1; i < 90; i++)
	{*/
	int n;
	begin = clock();
	n = count(45);
	end = clock();

	printf("%d:%d\n", 50, n);
	printf("time:%f\n\n", double(end - begin) / CLOCKS_PER_SEC);
	//}


}