#pragma once
class Architecture
{
public:
	int name[50];
	int q;//门的数量
	int* id;//门所在边的序号
	int* type;//门所在的路的类型0横着1竖着
	int* side;//门在路哪边
	double* ct;//门的横竖坐标中的一个
};

