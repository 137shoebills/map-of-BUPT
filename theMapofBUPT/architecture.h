#pragma once
#include<string>
class Architecture
{
public:
	std::string name;//建筑的名字
	int q;//门的数量
	int* id;//门所在边的序号
	int* type;//门所在的路的类型0横着1竖着
	int* side;//门在路哪边
	double* ct;//门的横竖坐标中的一个
};

