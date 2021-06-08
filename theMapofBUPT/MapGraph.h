#pragma once
#include "Edge.h"
#include "Point.h"
#include "Road.h"
#include "Architecture.h"
#include<queue>
#include<string>
#include<vector>
const double eps = 1e-10;
#define pa std::pair<double,int>
class MapGraph
{
private:
	std::vector<Architecture> arch;//���潨����
	Road* rds[2];//�����·������
	std::vector<Point> a;//����������
	Edge** head;//����ߵ��ڽ�����
	int EdgeSiz;//ͼ�б���
	int PointSiz;//ͼ�е���
	int rdn[2];//ͼ��·������
	int archn;//ͼ�н����������
	double* dis;//rt��ÿ����ľ���
	bool* disf;//rt��ÿ�����Ƿ��Ѿ���һ��ͨ·
	int* las;//���·��ÿ�����ǰһ����
	int* nex;//���·��ÿһ����ĺ�һ����
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
	void TSPdfs(int k, int n, double v);//tsp����
public:
	void BuildGraph();//���ļ��ж��������ʣ�λ�ã����߹�ϵ����ͼ
	void Dijkstra(int rt);//���·�㷨������rt��ÿ����ľ���
	~MapGraph();//��������
	double GetDis(int x);//�����x������·���룬����ǰ��Ҫ�ȵ���Dijkstra
	int* TSP(int rt,int n,int p[]);
	//;��������·�㷨������һ����СΪn������,�����е�i��ֵ��ʾ��i�����ʵĵ����š�
	//ʵ�ַ�ʽ������+dijkstra
	void OutWay(int rt, int x);//cout�������֮�����·���ϵĵ�
	std::pair<int,int> GetType(int x);
	bool MakeCP(std::string a,std::string b);
	//��b�ַ����в���������a�����ҵ��򷵻�1�����򷵻�0.
	void Search();
	//����һ���ַ���������������ĵ���
};

bool Cmp1(Point x,Point y);//��ͳ�ƺ���ϵĵ�����
bool Cmp2(Point x,Point y);//���������ϵĵ�����
bool Cmp3(Point x, Point y);//���յ��id����

