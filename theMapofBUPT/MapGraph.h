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
	Architecture* arch;//���潨����
	Road* rds[2];//�����·������
	Point* a;//����������
	Edge** head;//����ߵ��ڽ�����
	int EdgeSiz;//ͼ�б���
	int PointSiz;//ͼ�е���
	int rdn[2];//ͼ��·������
	int archn;//ͼ�н����������
	double* dis;//rt��ÿ����ľ���
	bool* disf;//rt��ÿ�����Ƿ��Ѿ���һ��ͨ·
	int* las;//���·��ÿ�����ǰһ����
	double **TSPdis;//;��������·�����ÿ����֮�����
	double TSPmin;//tsp���������е���Сֵ��
	int* TSPway;//tsp���������л�õ�·��
	int* TSPans;//tsp��
	bool* TSPf;//tsp�����������Ƿ����ĳ��
	std::priority_queue< pa, std::vector< pa >, std::greater< pa > >q;
	double GetDistance(double x,double y,double xx,double yy);//������ֱ�߾���
	void Init(int x,int y,double vv);//����һ��˫���
	void GetHead(int n);//�����������ʼ����Ҫ�Ķ�̬�ڴ�
	int GetPoint(int rd1,int rd2,int typ,double x,double y);//����һ����
	void TSPdfs(int k, int n, double v);
public:
	void BuildGraph();//���ļ��ж��������ʣ�λ�ã����߹�ϵ����ͼ
	void Dijkstra(int rt);//���·�㷨������rt��ÿ����ľ���
	~MapGraph();//��������
	double GetDis(int x);//�����x������·����
	int* TSP(int rt,int n,int p[]);
	//;��������·�㷨������һ����СΪn�������ʾ��i�����ʵĵ㡣
	void OutWay(int rt, int x);//�������֮�����·��
	std::pair<int,int> GetType(int x);
};

bool Cmp1(Point x,Point y);//��ͳ�ƺ���ϵĵ�����
bool Cmp2(Point x,Point y);//���������ϵĵ�����
bool Cmp3(Point x, Point y);//���ձߵ�id����

