#include "MapGraph.h"
#include <fstream>
#include<iostream>
#include <cmath>
bool Cmp1(Point x, Point y) {
	if (x.rd[0] != y.rd[0]) return x.rd[0] < y.rd[0];
	else return x.cdx < y.cdx;
}
bool Cmp2(Point x, Point y) {
	if (x.rd[1] != y.rd[1])return x.rd[1] < y.rd[1];
	else return x.cdy < y.cdy;
}
bool Cmp3(Point x, Point y) {
	return x.id < y.id;
}
MapGraph::~MapGraph() {
	delete []las;
	delete []disf;
	delete []a;
	while (!q.empty())q.pop();
	for (int i = 1; i <= PointSiz; ++i) {
		for (Edge* j = head[i];j!=NULL;) {
			Edge *w = j->next;
			delete j;
			j = w;
		}
	}
	delete[]head;
	//std::cout << "调用析构" << std::endl;
}
void MapGraph::Init(int x, int y,double vv) {
	Edge* nod = new Edge;
	nod->y = y; nod->next = head[x]; nod->val = vv;
	head[x] = nod;
	//std::cout << head[x]->y << std::endl;
	nod = new Edge;
	nod->y = x; nod->next = head[y]; nod->val = vv;
	head[y] = nod;
}
double MapGraph::GetDistance(double x, double y, double xx, double yy){
	x = x - xx;
	y = y - yy;
	return std::sqrt(x*x+y*y);
}
void MapGraph::GetHead(int n) {
	a = new Point [n+10];
	head = new Edge * [n+10];
	for (int i = 1; i <= n; ++i)head[i] = NULL;
	dis = new double[n+10];
	las = new int[n+10];
	disf = new bool[n+10];
}
int MapGraph::GetPoint(int rd1, int rd2, int typ, double x, double y){
	a[PointSiz].id = PointSiz;
	a[PointSiz].rd[0] = rd1;
	a[PointSiz].rd[1] = rd2;
	a[PointSiz].type = typ;
	a[PointSiz].cdx = x;
	a[PointSiz].cdy = y;
	PointSiz++;
	return PointSiz-1;
}
void MapGraph::BuildGraph() {
	/*int n,x,y,m;
	std::cin >> n>>m;
	PointSiz = n;
	EdgeSiz = m;
	GetHead(n);
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i].cdx >> a[i].cdy >> a[i].type >> a[i].name;
	}
	for (int i = 1; i <= m; ++i) {
		std::cin >> x >> y;
		double vv = getDistance(a[x].cdx,a[x].cdy,a[y].cdx,a[y].cdy);
		Init(x,y,vv);
	}*/
	std::ifstream mapin;
	mapin.open("Map_Data.txt");
	if (!mapin)return ;
	int n1, n2, m,y1,y2,x1,x2;
	mapin >> n2;
	rds[1] = new Road[n2 + 10];
	rdn[1] = n2;
	for (int i = 0; i < n2; ++i) {//读入竖着的道路
		int t;//id
		mapin >> x1 >> y1 >> y2 >> t;
		rds[1][i].y1 = y1;
		rds[1][i].y2 = y2;
		rds[1][i].x1 = x1;
		rds[1][i].x2 = x1;
	}
	mapin >> n1;
	//std::cout << n1 << n2 << std::endl;
	rds[0] = new Road[n1+10];
	rdn[0] = n1;
	for (int i = 0;i<n1; ++i) {//读入横着的道路
		int t;//id
		mapin >> y1 >> x1 >> x2 >> t;
		rds[0][i].x1 = x1;
		rds[0][i].x2 = x2;
		rds[0][i].y1 = y1;
		rds[0][i].y2 = y1;
	}
	mapin >> m;
	arch = new Architecture[m+10];
	archn = m;
	char name[50]; int q;
	int n4 = 0;//n4为建筑物上的点的个数
	//std::cout<<m<<std::endl;
	for (int i = 0; i < m; ++i){ //读入建筑上的门
		int t;
		mapin >> t >> name >> q;
		//std::cout<<name<<std::endl;
		int id, side,type;
		double ct;
		arch[i].q = q;
		arch[i].id = new int[q];
		arch[i].side = new int[q];
		arch[i].ct = new double[q];
		arch[i].type = new int[q];
		for (int j = 0; j < q; ++j) {
			mapin >> type >> id >> side >> ct;
			arch[i].id[j] = id;
			arch[i].type[j] = type ^ 1;
			arch[i].side[j] = side;
			arch[i].ct[j] = ct;
		}n4 += q;
	}
	int n3=0;//n3为路口的个数
	for (int i = 0; i < n1; ++i) {//计算出路口个数
		for (int j = 0;j<n2; ++j) {
			if (rds[0][i].x1<rds[1][j].x1) {
				if (rds[0][i].x2 > rds[1][j].x1) {
					if (rds[1][j].y1 < rds[0][i].y1) {
						if (rds[1][j].y2 > rds[0][i].y1) {
							n3++;
							//std::cout << i+1 << ' ' << j+1 << std::endl;
							//std::cout << rds[0][i].x1 << ' ' << rds[0][i].x2 << ' ' << rds[0][i].y1 << ' ' << rds[0][i].y2 << std::endl;
							//std::cout << rds[1][j].x1 << ' ' << rds[1][j].x2 << ' ' << rds[1][j].y1 << ' ' << rds[1][j].y2 << std::endl;

						}
					}
				}
			}
		}
	}
	GetHead(n4 + n3 + 30);
	PointSiz = 0;
	for (int i = 0; i < n1; ++i) {//路口放入point
		for (int j = 0; j < n2; ++j) {
			if (rds[0][i].x1 < rds[1][j].x1) {
				if (rds[0][i].x2 > rds[1][j].x1) {
					if (rds[1][j].y1 < rds[0][i].y1) {
						if (rds[1][j].y2 > rds[0][i].y1) {
							int zz=GetPoint(i,j,0,rds[1][j].x1,rds[0][i].y1);
							std::cout << zz << ' ' << i+1 << ' ' << j+1 << std::endl;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < m; ++i){//建筑物上的点放入point
		for (int j = 0; j < arch[i].q; ++j) {
			int id = arch[i].id[j];
			if (arch[i].type[j] == 0)GetPoint(id, -1, 1,arch[i].ct[j], rds[0][id].y1);
			else GetPoint(-1,id,1,rds[1][id].x1,arch[i].ct[j]);
		}
	}
	std::sort(a, a + PointSiz, Cmp1);//统计横路上的点之间的关系
	for (int i = 0; i < PointSiz-1; ++i) {
		if (a[i].rd[0] == -1)continue;
		if (a[i].rd[0]==a[i+1].rd[0]) {
			double z = GetDistance(a[i].cdx,a[i].cdy,a[i+1].cdx,a[i+1].cdy);
			Init(a[i].id, a[i + 1].id, z);
		}
	}
	std::sort(a, a + PointSiz, Cmp2);//统计竖着的路上的点之间的关系
	for (int i = 0; i < PointSiz - 1; ++i) {
		if (a[i].rd[1]==-1)continue;
		if (a[i].rd[1] == a[i + 1].rd[1]) {
			double z = GetDistance(a[i].cdx, a[i].cdy, a[i + 1].cdx, a[i + 1].cdy);
			Init(a[i].id, a[i + 1].id, z);
		}
	}
	std::sort(a, a + PointSiz, Cmp3);
	mapin.close();
}
std::pair<int,int> MapGraph::GetType(int x) {
	int type=0,num=0;
	type = a[x].type;
	return std::make_pair(type,num);
}
void MapGraph::Dijkstra(int rt) {
	for (int i = 1; i <= PointSiz; ++i)disf[i]=0;
	while (!q.empty()) q.pop();
	dis[rt] = 0; disf[rt] = 1;
	q.push(std::make_pair(dis[rt], rt));
	while (!q.empty()) {
		double vv = q.top().first;
		int x = q.top().second; 
		q.pop();
		if (dis[x]!=0&&vv > dis[x])continue;
		for (Edge *z = head[x]; z!=NULL; z = z->next) {
			if (disf[z->y]==0||dis[z->y] > dis[x] + z->val) {
				dis[z->y] = dis[x] + z->val;
				las[z->y] = x;
				disf[z->y] = 1;
				q.push(std::make_pair(dis[z->y], z->y));
			}
		}
	}
	//if (!disf[ed])return -1;
	//return dis[ed];
}
double MapGraph::GetDis(int x) {
	if (!disf[x])return -1;
	else return dis[x];
}
void MapGraph::TSPdfs(int k,int n,double v) {
	if (k == n) {
		if (v > TSPmin)return;
		TSPmin = v;
		for (int i = 0; i < n; ++i)TSPans[i] = TSPway[i];
		return;
	}
	for (int i = 0; i < n; ++i) {
		if (!TSPf[i]) {
			TSPf[i] = 1;
			TSPway[k] = i;
			TSPdfs(k + 1, n, v + TSPdis[TSPway[k - 1]][i]);
			TSPf[i] = 0;
		}
	}
}
int* MapGraph::TSP(int rt,int n,int p[]) {
	TSPdis = new double*[n];
	for (int i = 0;i<n; ++i) {
		TSPdis[i] = new double[n];
	}
	TSPans = new int[n];
	TSPway = new int[n];
	TSPf = new bool[n];
	TSPmin = 0;
	for (int i = 0; i < n; ++i) {
		Dijkstra(p[i]);
		for (int j = 0; j < n; ++j) {
			TSPdis[i][j] = GetDis(p[j]);
		}
		if(i!=n-1)TSPmin += TSPdis[i][i + 1];
		TSPans[i] = i;
	}Dijkstra(rt);
	TSPmin += GetDis(p[0]);
	for (int i = 0; i < n; ++i) {
		TSPway[0] = i;
		TSPf[i] = 1;
		TSPdfs(1, n, GetDis(p[i]));
		TSPf[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		delete TSPdis[i];
	}delete TSPdis;
	delete TSPway;
	delete TSPf;
	return TSPans;
}
void MapGraph::OutWay(int rt,int x) {
	Dijkstra(rt);
	std::cout << a[rt].rd[0]+1 << ' ' << a[rt].rd[1]+1 << std::endl;
	std::cout << a[x].rd[0]+1 << ' ' << a[x].rd[1]+1 << std::endl;
	if (disf[x])std::cout << dis[x] << std::endl;
	else std::cout << -1 << std::endl;
	std::cout << std::endl;
	for (int i = x; i != rt; i = las[i]) {
		if (a[i].type == 0) {
			std::cout << a[i].rd[0]+1 << ' ' << a[i].rd[1]+1<<std::endl;
		}
	}
	return;
}