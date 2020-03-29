#include <iostream>
#include <Windows.h>

/*
������(Mutxe)

function:
HANDLE CreateMutex(
LPSECURITY_ATTRIBUTES IpMutexAttributes,
BOOL BInitialOwner,	//��ʼ����������״̬������
LPCTSTR IpName		//���֣�����ΪNULL�����ܿ����ʹ��
);

HANDLE OpenMutex(
DWORD dwDesiredAccess,
BOOL BInheritHandle,
LPCTSTR IpName
);

BOOL ReleaseMutex(
HANDLE hMutex
);

CloseMutex(
HANDLE hObject
);
*/
using namespace::std;
int nSum = 0;
int NUMBER = 80000;
HANDLE hThread[2];
CRITICAL_SECTION cs;

DWORD WINAPI Accumulate(LPVOID lpaaram)
{
	for (int i(0); i < NUMBER; i++)
	{
		int iCopy = nSum;
		nSum = iCopy + 1;
	}
	return 0;
}

int main()
{
	HANDLE mutex = CreateMutex(NULL, true, NULL);
	InitializeCriticalSection(&cs);
	hThread[0] = CreateThread(NULL, 0, Accumulate, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, Accumulate, NULL, 0, NULL);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	cout << nSum << endl;
	return 0;
}
