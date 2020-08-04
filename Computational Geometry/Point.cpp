#ifndef _POINT_
#define _POINT_

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

Point::Point()
{
	this->x = 0;
	this->y = 0;
	this->extreme = true;
}

Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
	this->extreme = true;
}

Point::~Point()
{
}

void Point::setExtreme(bool extreme)
{
	this->extreme = extreme;
}

bool Point::getExtreme()
{
	return this->extreme;
}
#endif // !_POINT_
