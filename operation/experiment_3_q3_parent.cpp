#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <atlstr.h>

using namespace std;


int main()
{
	HANDLE hParentRead, hParentWrite, hChildRead, hChildWrite; //����4�����

	STARTUPINFO si = { 0 };							//������Ϣ�ṹ��
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi = { 0 };                 //������Ϣ�ṹ��

	SECURITY_ATTRIBUTES sa = { 0 };				   //��ȫ����������		
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;                      //���þ���ɼ̳�

	//�����ܵ�1. �����̶� -> �ӽ���д
	CreatePipe(&hParentRead, &hChildWrite, &sa, 0);

	//�����ܵ�2. �ӽ��̶� -> ������д.
	CreatePipe(&hChildRead, &hParentWrite, &sa, 0);

	////���ｫ�ӽ���д�ض��� stdout��. �ӽ��̶�ȡ�ض���stdinput��
	si.hStdInput = hChildRead;
	si.hStdOutput = hChildWrite;


	CString str = _T("D:/cpp/cpp algorithm/operation/experiment_3_q3/son_.exe");
	LPWSTR commandLine = str.GetBuffer();
	CreateProcess(commandLine, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	char buffer [10];
	for (int i = 1; i <= 100; i++)
	{
		_itoa_s(i, buffer, 10);
		WriteFile(hParentWrite, buffer, 10, NULL, 0);//ʹ��writeFile�����ܵ�,��son������������.
		Sleep(10);
	}
	Sleep(10000);
	return 0;
}