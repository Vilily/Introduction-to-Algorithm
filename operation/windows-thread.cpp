#include <Windows.h>
#include <iostream>


//DWORD DrawCircle()
DWORD WINAPI printOne(LPVOID lpParameter)
{
	int n = (int)lpParameter;
	for (int i(0); i < n; i++)
	{
		Sleep(500);
		std::cout << 1 << std::endl;
	}
	return 0;
}

DWORD WINAPI printTwo(LPVOID lpParameter)
{
	int n = (int)lpParameter;
	for (int i(0); i < n; i++)
	{
		Sleep(500);
		std::cout << 2 << std::endl;
	}
	return 0;
}

DWORD WINAPI A(LPVOID lpParameter)
{
	int n = 1000;
	for (int i(1); i <= n; i++)
	{
		Sleep(500);
		std::cout << i << " ";
	}
	return 0;
}

DWORD WINAPI B(LPVOID lpParameter)
{
	int n = 1000;
	for (int i(n); i > 0; i--)
	{
		Sleep(500);
		std::cout << i << " ";
	}
	return 0;
}
int main()
{
	HANDLE hThread[2];
	DWORD ThreadID;
	hThread[0] = CreateThread(NULL, 0, A, LPVOID(0), 0, &ThreadID);
	hThread[1] = CreateThread(NULL, 0, B, LPVOID(0), 0, &ThreadID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	return 0;
}


//HANDLE CreateThread(
//	LPSECURITY_ATTRIBUTES lpThreadAttributes,
//	DWORD dwStackSize,
//	LPTHREAD_ROUTINE ThreadFunction, //�̺߳���
//	LPVOID lpParameter //�̺߳����Ĳ��� )

//�̺߳�����ԭ��
//DWORD ThreadFunction(
//	LPVOID lpParameter //����)