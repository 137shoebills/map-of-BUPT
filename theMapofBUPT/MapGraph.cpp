#include "MapGraph.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <time.h>
#include <windows.h>
#include <conio.h>
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
	delete[]las;
	delete[]nex;
	delete[]disf;
	delete[]su;
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
	//std::cout << "��������" << std::endl;
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
	dis = new double[n + 10];
	las = new int[n + 10];
	nex = new int[n + 10];
	disf = new bool[n + 10];
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
void MapGraph::BuildGraph(std::string mapname,std::string sugname) {
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
	std::ifstream sugin;
	mapin.open(mapname.c_str());
	sugin.open(sugname.c_str());
	if (!mapin)return ;
	if (!sugin)return;
	sugn = 0;
	sugin >> sugn;
	su = new Suggest[sugn+10];
	for (int i = 0; i < sugn; ++i) {
		std::string sugs, sugp;
		sugin >> sugs >> sugp;
		su[i].source = sugs;
		su[i].sug = sugp;
	}
	int n1, n2, m,y1,y2,x1,x2;
	mapin >> n2;
	rds[1] = new Road[n2 + 10];
	rdn[1] = n2;
	for (int i = 0; i < n2; ++i) {//�������ŵĵ�·
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
	for (int i = 0;i<n1; ++i) {//������ŵĵ�·
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
	int n4 = 0;//n4Ϊ�������ϵĵ�ĸ���
	//std::cout<<m<<std::endl;
	for (int i = 0; i < m; ++i){ //���뽨���ϵ���
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
			arch[i].id[j] = id-1;
			arch[i].type[j] = type ^ 1;
			arch[i].side[j] = side;
			arch[i].ct[j] = ct;
		}n4 += q;
	}
	int n3=0;//n3Ϊ·�ڵĸ���
	for (int i = 0; i < n1; ++i) {//�����·�ڸ���
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
	for (int i = 0; i < n1; ++i) {//·�ڷ���point
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
	for (int i = 0; i < m; ++i){//�������ϵĵ����point
		for (int j = 0; j < arch[i].q; ++j) {
			int id = arch[i].id[j];
			int zz=0;
			if (arch[i].type[j] == 0) {
				zz = GetPoint(id, -1, 1, arch[i].ct[j], rds[0][id].y1);
				if (arch[i].side[j] == 0) {
					if(!MakeCP("����",a[zz].name))a[zz].name = arch[i].name + "����";
				}
				else {
					if (!MakeCP("����", a[zz].name))a[zz].name = arch[i].name + "����";
				}//std::cout << a[zz].name << zz << std::endl;
			}
			else { 
				zz = GetPoint(-1, id, 1, rds[1][id].x1, arch[i].ct[j]); 
				if (arch[i].side[j] == 0) {
					if (!MakeCP("����", a[zz].name))a[zz].name = arch[i].name + "����";
				}
				else {
					if (!MakeCP("����", a[zz].name))a[zz].name = arch[i].name + "����";
				}//std::cout << a[zz].name << zz << std::endl;
			}
		}
	}
	std::sort(a.begin(), a.end(), Cmp1);//ͳ�ƺ�·�ϵĵ�֮��Ĺ�ϵ
	for (int i = 0; i < PointSiz-1; ++i) {
		if (a[i].rd[0] == -1)continue;
		if (a[i].rd[0]==a[i+1].rd[0]) {
			double z = GetDistance(a[i].cdx,a[i].cdy,a[i+1].cdx,a[i+1].cdy);
			Init(a[i].id, a[i + 1].id, z);
		}
	}
	std::sort(a.begin(), a.end(), Cmp2);//ͳ�����ŵ�·�ϵĵ�֮��Ĺ�ϵ
	for (int i = 0; i < PointSiz - 1; ++i) {
		if (a[i].rd[1]==-1)continue;
		if (a[i].rd[1] == a[i + 1].rd[1]) {
			double z = GetDistance(a[i].cdx, a[i].cdy, a[i + 1].cdx, a[i + 1].cdy);
			Init(a[i].id, a[i + 1].id, z);
		}
	}
	std::sort(a.begin(), a.end(), Cmp3);
	mapin.close();
	std::cout<< "��ͼ�ɹ�" << std::endl;
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
	if (disf[x])std::cout << "����֮�����Ϊ:" << dis[x] << std::endl;
	else std::cout << "���ص㲻��ͨ" << std::endl;
	for (int i = x; i != rt; i = las[i]) {
		nex[las[i]] = i;
	}
	for (int i = rt; i != x; i = nex[i]) {
		if (a[i].type == 0) {
			std::cout << "����·�ڣ���·���Ǻ���· "<<a[i].rd[0]+1<<" ������· "<<a[i].rd[1]+1<<" �Ľ����,";
			if (i == rt) {
				if (a[nex[i]].rd[0] == a[i].rd[0]) {
					if (a[i].cdx < a[nex[i]].cdx)
						std::cout << "�Ӹ�·������" << std::endl;
					else
						std::cout << "�Ӹ�·��������" << std::endl;
				}
				else {
					if (a[i].cdy < a[nex[i]].cdy)
						std::cout << "�Ӹ�·��������" << std::endl;
					else
						std::cout << "�Ӹ�·������" << std::endl;
				}
			}
			else {
				if (a[nex[i]].rd[0] == a[i].rd[0]) {
					if (a[las[i]].rd[0] == a[i].rd[0])
						std::cout << "�Ӹ�·��ֱ��" << std::endl;
					else{
						int ff0 = 0, ff1 = 0;
						if (a[i].cdx < a[nex[i]].cdx)ff0 = 1;
						if (a[i].cdy > a[las[i]].cdy)ff1 = 1;
						if ((ff0 ^ ff1) == 0)
							std::cout << "�Ӹ�·�����" << std::endl;
						else
							std::cout << "�Ӹ�·���ҹ�" << std::endl;
					}
				}
				else{
					if (a[las[i]].rd[1] == a[i].rd[1])
						std::cout << "�Ӹ�·��ֱ��" << std::endl;
					else {
						int ff0 = 0, ff1 = 0;
						if (a[i].cdy < a[nex[i]].cdy)ff0 = 1;
						if (a[i].cdx > a[las[i]].cdx)ff1 = 1;
						if ((ff0 ^ ff1) == 0)
							std::cout << "�Ӹ�·���ҹ�" << std::endl;
						else
							std::cout << "�Ӹ�·�����" << std::endl;
					}
				}
			}
			//std::cout << a[i].cdx << a[i].cdy << std::endl;
		}
		else {
			if (i == rt) {
				if (a[nex[i]].rd[0] == a[i].rd[0] && a[i].rd[0] != -1) {
					if (a[i].cdx < a[nex[i]].cdx)
						std::cout << "��" << a[i].name << "����" << std::endl;
					else
						std::cout << "��" << a[i].name << "������" << std::endl;
				}
				else {
					if (a[i].cdy < a[nex[i]].cdy)
						std::cout << "��" << a[i].name << "������" << std::endl;
					else
						std::cout << "��" << a[i].name << "����" << std::endl;
				}
			}
			else {
				std::cout << "����" << a[i].name << std::endl;
				//std::cout << a[i].cdx<<a[i].cdy << std::endl;
			}
		}
	}
	if (a[x].type == 0) {
		std::cout << "�������· " << a[x].rd[0] + 1 << " ������· " << a[x].rd[1] + 1 << " �Ľ����" << std::endl;
	}
	else{
		std::cout << "����" << a[x].name << std::endl;
	}
	std::cout << "·��������" << std::endl;
	return;
}
bool MapGraph::MakeCP(std::string a, std::string b) {//��b�ַ����в���������a
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
	std::cout << "�����������:" << std::endl;
	for (int i = 0;i<PointSiz; ++i) {
		if ( a[i].type == 0)continue;
		int f = MakeCP(name,a[i].name);
		if (f) {
			++ff;
			std::cout << a[i].name << std::endl;
		}
	}
	std::cout << "��������" << ff << "�����" << std::endl;
}
void MapGraph::ClearOutWay() {
	std::string rts, xs;
	int rt = -1, x = -1;
	std::cout << "��������㣨���롰q���˳���ģʽ��" << std::endl;
	while (1) {
		rts = GetS();
		if (rts == "q") {
			std::cout << "�˳�������ѯ·��ģʽ" << std::endl;
			return;
		}
		for (int i = 0; i < PointSiz; ++i) {
			if (a[i].name == rts)rt = a[i].id;
		}
		if (rt == -1)std::cout << "���δ������������������������ƣ����롰q���˳���ģʽ��" << std::endl;
		else break;
	}
	std::cout << "�������յ㣨���롰q���˳���ģʽ��" << std::endl;
	while (1) {
		xs = GetS();
		if (xs == "q") {
			std::cout << "�˳�������ѯ·��ģʽ" << std::endl;
			return;
		}
		for (int i = 0; i < PointSiz; ++i) {
			if (a[i].name == xs)x = a[i].id;
		}
		if (rt == -1)std::cout << "�յ�δ�������������������յ����ƣ����롰q���˳���ģʽ��" << std::endl;
		else break;
	}
	OutWay(rt, x);
}
int MapGraph::FuzzyStart() {
	std::string rts;
	int rt = -1, rtn = 0, ans = -1;
	int* rtp = new int[PointSiz];
	std::cout << "��������㣨���롰q���˳���ģʽ��" << std::endl;
	while (1) {
		rts = GetS(); rtn = 0;
		if (rts == "q") {
			std::cout << "�˳�ģ����ѯ·��ģʽ" << std::endl;
			delete[]rtp;
			return ans;
		}
		for (int i = 0; i < PointSiz; ++i) {//�������ַ����ĵ������
			if ( MakeCP(rts, a[i].name) )rtp[rtn++] = i;
		}
		for (int i = 0; i < sugn; ++i) {//�����������ַ����ĵ������
			if (MakeCP(su[i].source, rts)) {
				for (int j = 0; j < PointSiz; ++j) {
					if (MakeCP(su[i].sug, a[j].name)) {
						bool fff = 0;
						for (int w = 0; w < rtn; ++w) {
							if (rtp[w] == j)fff = 1;
						}
						if(!fff)rtp[rtn++] = j;
					}
				}
			}
		}
		if (!rtn)std::cout << "���δ������������������������ƣ����롰q���˳���ģʽ��" << std::endl;
		else {
			std::cout << "�������ص����£�" << std::endl;
			for (int i = 0; i < rtn; ++i) {
				std::cout << i << ". " << a[rtp[i]].name << std::endl;
			}
			std::cout << "��������ѡ��ľ���ص����ţ�-1����������㣩" << std::endl;
			int z = GetInt();
			if (z == -1)continue;
			else if (z >= rtn || z < -1) {
				std::cout << "������Ų��Ϸ�,Ĭ�����Ϊ 0. " << a[rtp[0]].name << std::endl;

			}
			else {
				ans = rtp[z];
				break;
			}
		}
	}
	delete[]rtp;
	return ans;
}

int MapGraph::FuzzyEnd() {
	std::string xs;
	int x = -1, xn = 0, ans = -1;
	int* xp = new int[PointSiz];
	std::cout << "�������յ㣨���롰q���˳���ģʽ��" << std::endl;
	while (1) {
		xs = GetS(); xn = 0;
		if (xs == "q") {
			std::cout << "�˳�ģ����ѯ·��ģʽ" << std::endl;
			delete[]xp;
			return ans;
		}
		for (int i = 0; i < PointSiz; ++i) {//�������ַ����ĵ������
			if (MakeCP(xs, a[i].name))xp[xn++] = i;
		}
		for (int i = 0; i < sugn; ++i) {//�����������ַ����ĵ������
			if (MakeCP(su[i].source, xs)) {
				for (int j = 0; j < PointSiz; ++j) {
					if (MakeCP(su[i].sug, a[j].name)) {
						bool fff = 0;
						for (int w = 0; w < xn; ++w) {
							if (xp[w] == j)fff = 1;
						}
						if (!fff)xp[xn++] = j;
					}
				}
			}
		}
		if (!xn)std::cout << "�յ�δ�������������������յ����ƣ����롰q���˳���ģʽ��" << std::endl;
		else {
			std::cout << "�������ص����£�" << std::endl;
			for (int i = 0; i < xn; ++i) {
				std::cout << i << ". " << a[xp[i]].name << std::endl;
			}
			std::cout << "��������ѡ��ľ���ص����ţ�-1���������յ㣩" << std::endl;
			int z = GetInt();
			if (z == -1)continue;
			else if (z >= xn || z < -1) {
				std::cout << "������Ų��Ϸ�,Ĭ�����Ϊ 0. " << a[xp[0]].name << std::endl;

			}
			else {
				ans = xp[z];
				break;
			}
		}
	}
	delete[]xp;
	return ans;
}
std::string MapGraph::GetName(int i){
	return a[i].name;
}
void MapGraph::OutNeighbor(int x, int length) {
	Dijkstra(x);
	for (int i = 0; i < PointSiz; ++i) {
		if (a[i].type == 0)continue;
		else {
			if(dis[i]<length) {
				std::cout<<a[i].name<<std::endl;
			}
		}
	}
}
void MapGraph::SimJohn(int rt, int ed) {
	std::cout << "ģ�⿪ʼ" << std::endl;
	john.timer.Start(john.scale);
	double loc = 0;
	char ch = ' ';
	john.x = a[rt].cdx; john.y = a[rt].cdy;
	for (int i = rt; i != ed; i = nex[i]) {
		double disnow = loc + john.velo * (double)john.timer.Show() / 1000.0;
		//std::cout << john.timer.Show() << std::endl;
		john.p[0] = i, john.p[1] = nex[i];
		while (disnow <= (double)dis[nex[i]]) {

			john.x = a[i].cdx;
			john.y = a[i].cdy;
			if (a[i].rd[0] != -1 && a[i].rd[0] == a[nex[i]].rd[0]) {
				if (a[i].cdx < a[nex[i]].cdx)john.x += disnow - dis[i];
				else john.x -= disnow - dis[i];
			}
			else {
				if (a[i].cdy < a[nex[i]].cdy)john.y += disnow - dis[i];
				else john.y -= disnow - dis[i];
			}
			if (_kbhit()) {
				ch = _getch();
				if (ch == 's') {
					john.timer.Stop();
					loc = disnow;
					//std::cout << disnow <<' '<< dis[ed] << std::endl;
					std::cout << "��ͣģ�⣬����ģ������'k'���˳���ǰ·��ģ������'q'������ʱ������߲�����ģ������'c'" << std::endl;
					std::string ss = GetS();
					while (ss != "q" && ss != "k" && ss != "c") {
						std::cout << "���������������������ģ������'k'���˳���ǰ·��ģ������'q'������ʱ������߲�����ģ������'c'" << std::endl;
						ss = GetS();
					}
					if (ss == "q") {
						john.p[0] = john.p[1] = i;
						john.x = a[i].cdx;
						john.y = a[i].cdy;
						return;
					}
					else if (ss == "c") {
						std::cout << "������ʱ�������" << std::endl;
						john.scale = GetDouble();
						if (john.scale<0) {
							std::cout << "����������ʱ������ߣ���������Ҫ����0��" << std::endl;
							john.scale = GetDouble();
						}
						john.timer.Start(john.scale);
					}
					else if(ss=="k") john.timer.Start(john.scale);
				}
			}
			Sleep(5);
			disnow = loc + john.velo * (double)john.timer.Show() / 1000.0;
		}
		john.x = a[nex[i]].cdx; john.y = a[nex[i]].cdy;
		if (a[i].type == 0) {
			std::cout << "����·�ڣ���·���Ǻ���· " << a[i].rd[0] + 1 << " ������· " << a[i].rd[1] + 1 << " �Ľ����,";
			if (i == rt) {
				if (a[nex[i]].rd[0] == a[i].rd[0]) {
					if (a[i].cdx < a[nex[i]].cdx)
						std::cout << "�Ӹ�·������" << std::endl;
					else
						std::cout << "�Ӹ�·��������" << std::endl;
				}
				else {
					if (a[i].cdy < a[nex[i]].cdy)
						std::cout << "�Ӹ�·��������" << std::endl;
					else
						std::cout << "�Ӹ�·������" << std::endl;
				}
			}
			else {
				if (a[nex[i]].rd[0] == a[i].rd[0]) {
					if (a[las[i]].rd[0] == a[i].rd[0])
						std::cout << "�Ӹ�·��ֱ��" << std::endl;
					else {
						int ff0 = 0, ff1 = 0;
						if (a[i].cdx < a[nex[i]].cdx)ff0 = 1;
						if (a[i].cdy > a[las[i]].cdy)ff1 = 1;
						if ((ff0 ^ ff1) == 0)
							std::cout << "�Ӹ�·�����" << std::endl;
						else
							std::cout << "�Ӹ�·���ҹ�" << std::endl;
					}
				}
				else {
					if (a[las[i]].rd[1] == a[i].rd[1])
						std::cout << "�Ӹ�·��ֱ��" << std::endl;
					else {
						int ff0 = 0, ff1 = 0;
						if (a[i].cdy < a[nex[i]].cdy)ff0 = 1;
						if (a[i].cdx > a[las[i]].cdx)ff1 = 1;
						if ((ff0 ^ ff1) == 0)
							std::cout << "�Ӹ�·���ҹ�" << std::endl;
						else
							std::cout << "�Ӹ�·�����" << std::endl;
					}
				}
			}
			//std::cout << a[i].cdx << a[i].cdy << std::endl;
		}
		else {
			if (i == rt) {
				if (a[nex[i]].rd[0] == a[i].rd[0] && a[i].rd[0] != -1) {
					if (a[i].cdx < a[nex[i]].cdx)
						std::cout << "��" << a[i].name << "����" << std::endl;
					else
						std::cout << "��" << a[i].name << "������" << std::endl;
				}
				else {
					if (a[i].cdy < a[nex[i]].cdy)
						std::cout << "��" << a[i].name << "������" << std::endl;
					else
						std::cout << "��" << a[i].name << "����" << std::endl;
				}
			}
			else {
				std::cout << "����" << a[i].name << std::endl;
				//std::cout << a[i].cdx<<a[i].cdy << std::endl;
			}
		}
	}
	if (a[ed].type == 0) {
		std::cout << "�������· " << a[ed].rd[0] + 1 << " ������· " << a[ed].rd[1] + 1 << " �Ľ����" << std::endl;
	}
	else {
		std::cout << "����" << a[ed].name << std::endl;
	}
	std::cout << "·��ģ��ֹͣ" << std::endl;
	std::cout << std::endl;
	john.p[0] = john.p[1] = ed;
	john.x = a[ed].cdx;
	john.y = a[ed].cdy;
}
void MapGraph::John_Travel() {
	std::cout<<"������һ�����ֱ�ʾģ���ٶ�(��λ��m/s)"<<std::endl;
	john.velo = GetDouble();
	while(john.velo <= 0) {
		std::cout << "������һ�����ֱ�ʾģ���ٶ�(��λ��m/s),�ٶ������0" << std::endl;
		john.velo = GetDouble();
	}
	std::cout << std::endl;

	std::cout << "������һ�����ֱ�ʾʱ�����ű����ߣ�����0��������С����" << std::endl;
	john.scale = GetDouble();
	while (john.scale <= 0) {
		std::cout << "������һ�����ֱ�ʾʱ�����ű����ߣ�����0��������С����" << std::endl;
		john.scale = GetDouble();
	}
	std::cout << std::endl;

	int rt = FuzzyStart();
	if (rt == -1) {
		std::cout << "���˳�·��ģ��" << std::endl;
		std::cout << std::endl;
		return;
	}
	int ed = FuzzyEnd();
	if (ed == -1) {
		std::cout << "���˳�·��ģ��" << std::endl;
		std::cout << std::endl;
		return;
	}
	Dijkstra(rt);
	for (int i = ed; i != rt; i = las[i]) {
		nex[las[i]] = i;
	}
	while (1) {
		SimJohn(rt, ed);
		std::cout << "�Ƿ�����ѡȡĿ�ĵأ�y(��)/n����" << std::endl;
		std::string ss = GetS();
		while (ss != "y" && ss != "n") {
			std::cout << "������ 'y' �� 'n'��y(��)/n����" << std::endl;
			ss = GetS();
		}
		if (ss == "y") {
			std::cout << std::endl;
			ed = FuzzyEnd();
			Dijkstra(john.p[0]);
			for (int i = ed; i != john.p[0]; i = las[i]) {
				nex[las[i]] = i;
			}
			SimJohn(john.p[0],ed);
		}
		else if (ss == "n") {
			std::cout << "ģ�����" << std::endl;
			std::cout << std::endl;
			return;
		}
	}
}