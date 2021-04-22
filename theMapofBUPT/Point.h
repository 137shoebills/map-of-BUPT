#pragma once
class Point
{
public:
	double cdx,cdy;//点的坐标
	int rd[2];//点所在两条路的id
	char name[50];//点的名称
	int type;
//路口为0，建筑物为1
	int id;

	//Point();
};

