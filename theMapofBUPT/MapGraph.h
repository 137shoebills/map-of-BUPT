#pragma once
#include "Edge.h"
#include "Point.h"
#include "Road.h"
#include "Architecture.h"
#include<queue>
const double eps = 1e-10;
#define pa std::pair<double,int>
class MapGraph
{
private:
	Architecture* arch;//储存建筑物
	Road* rds[2];//储存道路的数组
	Point* a;//储存点的数组
	Edge** head;//储存边的邻接链表
	int EdgeSiz;//图中边数
	int PointSiz;//图中点数
	int rdn[2];//图中路的数量
	int archn;//图中建筑物的数量
	double* dis;//rt到每个点的距离
	bool* disf;//rt到每个点是否已经有一条通路
	int* las;//最短路中每个点的前一个点
	double **TSPdis;//途径多点最短路所需的每两点之间距离
	double TSPmin;//tsp搜索过程中的最小值。
	int* TSPway;//tsp搜索过程中获得的路径
	int* TSPans;//tsp答案
	bool* TSPf;//tsp搜索过程中是否遍历某点
	std::priority_queue< pa, std::vector< pa >, std::greater< pa > >q;
	double GetDistance(double x,double y,double xx,double yy);//求两点直线距离
	void Init(int x,int y,double vv);//建立一条双向边
	void GetHead(int n);//输入点数，初始化需要的动态内存
	int GetPoint(int rd1,int rd2,int typ,double x,double y);//储存一个点
	void TSPdfs(int k, int n, double v);
public:
	void BuildGraph();//从文件中读入点的性质，位置，连线关系并建图
	void Dijkstra(int rt);//最短路算法，计算rt到每个点的距离
	~MapGraph();//析构函数
	double GetDis(int x);//输出到x点的最短路距离
	int* TSP(int rt,int n,int p[]);
	//途径多点最短路算法，返回一个大小为n的数组表示第i个访问的点。
	void OutWay(int rt, int x);//输出两点之间最短路径
	std::pair<int,int> GetType(int x);
};

bool Cmp1(Point x,Point y);//先统计横边上的点排序
bool Cmp2(Point x,Point y);//考虑竖边上的点排序
bool Cmp3(Point x, Point y);//按照边的id排序

