#include "MapGraph.h"
#include <fstream>
#include<iostream>
#include <cmath>
#include "MyAddition.h"
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
	a.clear();
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
	head = new Edge * [n+10];
	for (int i = 1; i <= n; ++i)head[i] = NULL;
	dis = new double[n+10];
	las = new int[n+10];
	disf = new bool[n+10];
}
int MapGraph::GetPoint(int rd1, int rd2, int typ, double x, double y){
	Point bb;
	bb.id = PointSiz;
	bb.rd[0] = rd1;
	bb.rd[1] = rd2;
	bb.type = typ;
	bb.cdx = x;
	bb.cdy = y;
	a.push_back(bb);
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
	Architecture ar;
	archn = m;
	std::string na;
	int q;
	int n4 = 0;//n4为建筑物上的点的个数
	//std::cout<<m<<std::endl;
	for (int i = 0; i < m; ++i){ //读入建筑上的门
		int t;
		mapin >> t >> na >> q;
		//std::cout<<na<<std::endl;
		int id, side,type;
		double ct;
		ar.name = na;
		ar.q = q;
		ar.id = new int[q];
		ar.side = new int[q];
		ar.ct = new double[q];
		ar.type = new int[q];
		arch.push_back(ar);
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
							//std::cout << zz << ' ' << i+1 << ' ' << j+1 << std::endl;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < m; ++i){//建筑物上的点放入point
		for (int j = 0; j < arch[i].q; ++j) {
			int id = arch[i].id[j];
			int zz=0;
			if (arch[i].type[j] == 0) {
				zz = GetPoint(id, -1, 1, arch[i].ct[j], rds[0][id].y1);
				if (arch[i].side[j] == 0) {
					a[zz].name = arch[i].name + "南门";
				}
				else {

					a[zz].name = arch[i].name + "北门";
				}//std::cout << a[zz].name << std::endl;
			}
			else { 
				zz = GetPoint(-1, id, 1, rds[1][id].x1, arch[i].ct[j]); 
				if (arch[i].side[j] == 0) {
					a[zz].name = arch[i].name + "东门";
				}
				else {

					a[zz].name = arch[i].name + "西门";
				}//std::cout << a[zz].name << std::endl;
			}
		}
	}
	std::sort(a.begin(), a.end(), Cmp1);//统计横路上的点之间的关系
	for (int i = 0; i < PointSiz-1; ++i) {
		if (a[i].rd[0] == -1)continue;
		if (a[i].rd[0]==a[i+1].rd[0]) {
			double z = GetDistance(a[i].cdx,a[i].cdy,a[i+1].cdx,a[i+1].cdy);
			Init(a[i].id, a[i + 1].id, z);
		}
	}
	std::sort(a.begin(), a.end(), Cmp2);//统计竖着的路上的点之间的关系
	for (int i = 0; i < PointSiz - 1; ++i) {
		if (a[i].rd[1]==-1)continue;
		if (a[i].rd[1] == a[i + 1].rd[1]) {
			double z = GetDistance(a[i].cdx, a[i].cdy, a[i + 1].cdx, a[i + 1].cdy);
			Init(a[i].id, a[i + 1].id, z);
		}
	}
	std::sort(a.begin(), a.end(), Cmp3);
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
	for (int i = 0; i < n; ++i)TSPans[i] = p[TSPans[i]];
	
	for (int i = 0; i < n; ++i) {
		delete TSPdis[i];
	}delete TSPdis;
	delete TSPway;
	delete TSPf;
	return TSPans;
}
void MapGraph::OutWay(int rt,int x) {
	Dijkstra(rt);
	//std::cout << a[rt].rd[0]+1 << ' ' << a[rt].rd[1]+1 << std::endl;
	//std::cout << a[x].rd[0]+1 << ' ' << a[x].rd[1]+1 << std::endl;
	if (disf[x])std::cout << "两地之间距离为:" << dis[x] << std::endl;
	else std::cout << "两地点不连通" << std::endl;
	for (int i = x; i != rt; i = las[i]) {
		if (a[i].type == 0) {
			std::cout<<"经过路口，两路口编号分别为：" << a[i].rd[0]+1 << ' ' << a[i].rd[1]+1<<std::endl;
		}
		else {
			std::cout << "经过"<< a[i].name << std::endl;
		}
	}
	std::cout << std::endl;
	return;
}
bool MapGraph::MakeCP(std::string a, std::string b) {//在b字符串中查找子序列a
	int** f;
	f = new int* [100];
	for (int i = 0; i < 100; ++i) {
		f[i] = new int[100];
		for (int j = 0; j < 100; ++j)f[i][j] = 0;
	}
	std::string aa = '0' + a;
	std::string bb = '0' + b;
	for (int i = 0; i <= b.size(); ++i) f[i][0] = 1;
	for (int i = 1; i < bb.size(); ++i) {
		for (int j = 1; j < aa.size(); ++j) {
			if (bb[i] == aa[j] && f[i - 1][j - 1]) {
				f[i][j] = 1;
			}
			if (f[i - 1][j])f[i][j] = 1;
		}
	}
	int xx = f[b.size()][a.size()];
	for (int i = 0; i < 100; ++i) {
		delete[] f[i];
	}
	delete[] f;
	return xx;
}
void MapGraph::Search() {
	std::string name,cmd;
	name = GetS();
	int ff = 0;
	std::cout << "搜索结果如下:" << std::endl;
	for (int i = 0;i<PointSiz; ++i) {
		if ( a[i].type == 0)continue;
		int f = MakeCP(name,a[i].name);
		if (f) {
			++ff;
			std::cout << a[i].name << std::endl;
		}
	}
	std::cout << "共搜索到" << ff << "个结果" << std::endl;
}