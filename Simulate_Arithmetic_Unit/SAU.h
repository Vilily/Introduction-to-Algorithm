#pragma once

class SAU
{
public:
	SAU();
	~SAU();

private:
	// ԭ��ת����
	int convert_to_complement(int true_code);
	// ����תԭ��
	int convert_to_truecode(int complement_code);
	// ԭ��ת����
	int convert_to_ones_complement(int true_code);
};

SAU::SAU()
{
}

SAU::~SAU()
{
}