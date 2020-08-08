#pragma once

/**
* @description: ����
* @param x: ��ĺ�����
* @param y: ���������
* @param extrem: �Ƿ���͹��
*/
class Point
{
public:
	Point();
	Point(double x, double y);
	~Point();
	void setX(double x);
	void setY(double y);
	double getX();
	double getY();
	void setExtreme(bool extreme);
	bool getExtreme();
private:
	double x;
	double y;
	bool extreme;
};