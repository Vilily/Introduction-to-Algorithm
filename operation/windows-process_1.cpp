#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <atlstr.h>
//�½�����
//1:
//int system(const char* command);

//2:
//UINT WinExec(
//	LPCSTR lpCmdLine, // command line
//	UINT uCmdShow // window style
//);

//3:
//HINSTANCE ShellExecute(
//	HWND hwnd,
//	LPCTSTR lpVerb,
//	LPCTSTR lpFile,
//	LPCTSTR lpParameters,
//	LPCTSTR lpDirectory,
//	INT nShowCmd
//);

//4:
//BOOL CreateProcess
//(
//	LPCTSTR lpApplicationName, // ��ִ�г�����
//	LPTSTR lpCommandLine, //[��ִ�г�����]�������
//	LPSECURITY_ATTRIBUTES lpProcessAttributes��
//	LPSECURITY_ATTRIBUTES lpThreadAttributes,
//	BOOL bInheritHandles,
//	DWORD dwCreationFlags, //������־
//	LPVOID lpEnvironment,
//	LPCTSTR lpCurrentDirectory,
//	LPSTARTUPINFO lpStartupInfo,
//	LPPROCESS_INFORMATION lpProcessInformation
//);


//��������
//1:
//VOID ExitProcess(UINT uExitCode);

//2:
//TerminateProcess(
//	HANDLE hProcess,
//	UINT uExitCode);


int main()
{
	//system("D:\\Snake.exe");
	//WinExec("D:\\Snake.exe", SW_SHOWMAXIMIZED);
	//ShellExecute(NULL, "open", "D:\\Snake.exe", NULL, NULL, SW_SHOWNORMAL);

	CString str = _T("D:\\Snake.exe");
	LPWSTR commandLine = str.GetBuffer();
	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si) };
	CreateProcess(commandLine, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
	return 0;
}