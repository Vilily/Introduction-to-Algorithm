#pragma once
#define MAX_BIG_NUM_LEN	1000
class BigNum
{
public:
	BigNum();
	BigNum(int x);
	BigNum(long long x);
	~BigNum();
	void setNum(char str[]);
	/***************** �Ƚ����� ************************/
	friend int compare(BigNum& a, BigNum& b);
	friend bool operator< (BigNum& a, BigNum& b);
	friend bool operator> (BigNum& a, BigNum& b);
	friend bool operator<= (BigNum& a, BigNum& b);
	friend bool operator>= (BigNum& a, BigNum& b);
	friend bool operator== (BigNum& a, BigNum& b);
	/******************** �������� *************************/
	// �����Ƿ��ţ�Ĭ��������
	friend BigNum add(BigNum& a, BigNum& b);
	friend BigNum sub(BigNum& a, BigNum& b);
	friend BigNum mulInt(BigNum& a, int b);
	friend BigNum mul(BigNum& a, BigNum& b);
	friend BigNum divInt(BigNum& a, int b, int& r);
	friend BigNum div(BigNum& a, BigNum& b);
	// ���Ƿ���
	friend BigNum operator+(BigNum& a, BigNum& b);
	friend BigNum operator-(BigNum& a, BigNum& b);
	/******************* ������� ***************************/
	ostream operator<< (ostream& os);
	istream operator>> (istream& in);

private:
	// 0-1000��low-high
	int num[MAX_BIG_NUM_LEN];
	// false: negative; true: positive
	bool sign;
	int len;
};