#include <easyx.h>
#include <random>
#include <iostream>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>

#define PHI_SUM		5
#define CHOP_SUM	5
#define CHOP_AVAI	-1
#define PHI_EMPTY	-1
#define LINE_WIDTH	5
#define BK_COLOR	BLACK
#define LINE_COLOR	WHITE

#define EAT_PIC		"./eat.jpg"
#define THINK_PIC	"./think.jpg"
#define CHOP_PIC	"./chop.jpg"

#define CHOP_SIZE	20
#define PHI_SIZE	50

#define CHOP1_POSI  350, 500
#define CHOP2_POSI  500, 500
#define CHOP3_POSI  550, 350
#define CHOP4_POSI  400, 250
#define CHOP5_POSI  280, 350

#define PHI1_POSI	425, 650
#define PHI2_POSI	685, 480
#define PHI3_POSI	545, 200
#define PHI4_POSI	200, 200
#define PHI5_POSI	200, 480

using namespace::std;


//����ṹ��
struct point 
{
	int x;
	int y;
};

//���ߺ���
void thinking(int philosopherID);
void eating(int philosopherID);

//���������������
void getChopsticksDeadLock(int philosopherID, int chopstickID);
void putChopsticksDeadLock(int philosopherID, int chopstickID);
DWORD WINAPI philosopherDeadLock(LPVOID lpParameter);
void beginEating(bool isDeadLock);

//�������ⷨ
void getChopsticks(int philosopherID, int chopstickID);
void putChopsticks(int philosopherID, int chopstickID);
DWORD WINAPI philosopher(LPVOID lpParameter);
//ͼ�ν��溯��
void initGraph();
void drawEat(int philosopherID);
void drawThink(int philosopherID);
void drawGetChop(int chopID, int philosopherID);
void drawPutChop(int chopID, int philosopherID);

//ȫ�ֱ���
IMAGE chopImage;		//����ͼƬ
IMAGE phiEatImage;		//��ѧ�ҳԷ�ͼƬ
IMAGE phiThinkImage;	//��ѧ��˼��ͼƬ
struct point chopPosi[5];
struct point phiPosi[5];

//���ӻ�����
CRITICAL_SECTION mutex[CHOP_SUM];
//����״̬������
HANDLE leftMutex;
HANDLE rightMutex;
HANDLE philosophers[PHI_SUM];



int main()
{
	loadimage(&chopImage, _T(CHOP_PIC), 50, 33);
	loadimage(&phiEatImage, _T(EAT_PIC), 70, 70);
	loadimage(&phiThinkImage, _T(THINK_PIC), 70, 70);
	int x;
	bool isDeadLock;
	cout << "�����룺\n������1\n��������2\n";
	cin >> x;
	if (x == 1)
		isDeadLock = true;
	else
		isDeadLock = false;
	initGraph();
	beginEating(isDeadLock);
}

/************************************************************************************/
void initGraph()
{
	initgraph(1200, 750, SHOWCONSOLE);

	
	putimage(CHOP1_POSI, &chopImage);
	putimage(CHOP2_POSI, &chopImage);
	putimage(CHOP3_POSI, &chopImage);
	putimage(CHOP4_POSI, &chopImage);
	putimage(CHOP5_POSI, &chopImage);


	putimage(PHI1_POSI, &phiEatImage);
	putimage(PHI2_POSI, &phiEatImage);
	putimage(PHI3_POSI, &phiEatImage);
	putimage(PHI4_POSI, &phiEatImage);
	putimage(PHI5_POSI, &phiEatImage);

	chopPosi[0] = { CHOP1_POSI + 33};
	chopPosi[1] = { CHOP2_POSI };
	chopPosi[2] = { 50 + CHOP3_POSI};
	chopPosi[3] = { CHOP4_POSI };
	chopPosi[4] = { CHOP5_POSI };

	phiPosi[0] = { PHI1_POSI };
	phiPosi[1] = { PHI2_POSI };
	phiPosi[2] = { PHI3_POSI };
	phiPosi[3] = { PHI4_POSI };
	phiPosi[4] = { PHI5_POSI };

	setlinestyle(PS_SOLID, LINE_WIDTH);
}

void drawEat(int philosopherID)
{
	putimage(phiPosi[philosopherID].x, phiPosi[philosopherID].y, &phiEatImage);
}

void drawThink(int philosopherID)
{
	putimage(phiPosi[philosopherID].x, phiPosi[philosopherID].y, &phiThinkImage);
}

void drawGetChop(int chopID, int philosopherID)
{
	setlinecolor(LINE_COLOR);
	line(chopPosi[chopID].x, chopPosi[chopID].y, phiPosi[philosopherID].x, phiPosi[philosopherID].y);
}

void drawPutChop(int chopID, int philosopherID)
{
	setlinecolor(BK_COLOR);
	line(chopPosi[chopID].x, chopPosi[chopID].y, phiPosi[philosopherID].x, phiPosi[philosopherID].y);
}

/*****************************************************************************************/



DWORD WINAPI philosopherDeadLock(LPVOID lpParameter)
{
	int id = (int)lpParameter;
	int leftID = id;
	int rightID = ((id + 1) % PHI_SUM);
	while (true)
	{
		//˼��
		drawThink(id);
		thinking(id);
		//��ȡ�����
		getChopsticksDeadLock(id, leftID);
		drawGetChop(leftID, id);
		//��ȡ�ҿ���
		getChopsticksDeadLock(id, rightID);
		drawGetChop(rightID, id);
		//�Է�
		drawEat(id);
		eating(id);
		drawPutChop(leftID, id);
		drawPutChop(rightID, id);
		//���������
		putChopsticksDeadLock(id, leftID);
		
		//�����ҿ���
		putChopsticksDeadLock(id, rightID);
		
	}
}

void thinking(int philosopherID)
{
	Sleep((rand() % 4 + 1) * 100);
}

void eating(int philosopherID)
{
	Sleep((rand() % 4 + 1) * 100);
}


/*****************Dead Lock Solution*********************************************/



void getChopsticksDeadLock(int philosopherID, int chopstickID)
{
	EnterCriticalSection(&(mutex[chopstickID]));
}

void putChopsticksDeadLock(int philosopherID, int chopstickID)
{
	LeaveCriticalSection(&(mutex[chopstickID]));
}

void beginEating()
{
	int i;
	for (i = 0; i < CHOP_SUM; i++)
	{
		InitializeCriticalSection(&(mutex[i]));
	}
	rightMutex = CreateSemaphore(NULL, 4, 4, NULL);
	leftMutex = CreateSemaphore(NULL, 4, 4, NULL);

	DWORD ThreadID;
	for (i = 0; i < PHI_SUM; i++)
	{
		philosophers[i] = CreateThread(NULL, 0, philosopher, (LPVOID)(i), 0, &ThreadID);
	}
	WaitForMultipleObjects(5, philosophers, false, INFINITE);

}

void beginEatingDeadLock()
{
	int i;
	for (i = 0; i < CHOP_SUM; i++)
	{
		InitializeCriticalSection(&(mutex[i]));
	}
	rightMutex = CreateSemaphore(NULL, 4, 4, NULL);
	leftMutex = CreateSemaphore(NULL, 4, 4, NULL);

	DWORD ThreadID;
	for (i = 0; i < PHI_SUM; i++)
	{
		philosophers[i] = CreateThread(NULL, 0, philosopherDeadLock, (LPVOID)(i), 0, &ThreadID);
	}
	WaitForMultipleObjects(5, philosophers, false, INFINITE);

}

/**************************Not Dead Lock Solution**************************/


void getChopsticks(int philosopherID, int chopstickID)
{
	EnterCriticalSection(&(mutex[chopstickID]));
	//���ֱ�
	//if (philosopherID == chopstickID)
	//{
	//	//WaitForSingleObject(leftMutex, INFINITE);
	//	EnterCriticalSection(&mutex[chopstickID]);
	//}
	////���ֱ�
	//else
	//{
	//	//WaitForSingleObject(rightMutex, INFINITE);
	//	EnterCriticalSection(&mutex[chopstickID]);
	//}
}

void putChopsticks(int philosopherID, int chopstickID)
{
	LeaveCriticalSection(&(mutex[chopstickID]));
	//���ֱ�
	//if (philosopherID == chopstickID)
	//{
	//	//ReleaseSemaphore(leftMutex, 1, NULL);
	//	LeaveCriticalSection(&mutex[chopstickID]);
	//}
	////���ֱ�
	//else
	//{
	//	//ReleaseSemaphore(rightMutex, 1, NULL);
	//	LeaveCriticalSection(&mutex[chopstickID]);
	//}
}

DWORD WINAPI philosopher(LPVOID lpParameter)
{
	int id = (int)lpParameter;
	int leftID = id;
	int rightID = ((id + 1) % PHI_SUM);

	while (true)
	{
		//˼��
		drawThink(id);
		thinking(id);
		//��ȡ�����
		getChopsticks(id, leftID);
		drawGetChop(leftID, id);
		//��ȡ�ҿ���
		getChopsticks(id, rightID);
		drawGetChop(rightID, id);
		//�Է�
		drawEat(id);
		eating(id);
		//���������
		drawPutChop(leftID, id);
		drawPutChop(rightID, id);
		putChopsticks(id, leftID);
		
		//�����ҿ���
		putChopsticks(id, rightID);
	}
	return 0;
}

/*****************************************************************************/
