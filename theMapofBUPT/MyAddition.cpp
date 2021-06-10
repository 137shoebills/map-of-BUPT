
#include<string>
#include<iostream>
#include<time.h>
#include "MyAddition.h"

int System_State = 0;//ϵͳ��ѯģʽ
double System_Velo = 1.5;//��ǰģʽ���˶��ٶ�
double System_Bike = 5.0;//Ĭ�ϵ����г��ٶ�
double System_Person = 1.5;//Ĭ�ϵ������ٶ�

std::string GetS() {//���ո�ʽ�����ַ���
	std::string a;
	getline(std::cin, a);
	while (a.size() > 100) {
		std::cout << "�ַ�����С��С��100������������" << std::endl;
		getline(std::cin, a);
	}
	return a;
}
int GetInt() {//���ո�ʽ����int
	std::string a;
	getline(std::cin, a);
	int x, f, ff;
	int maxn = 99999999;
	while (1) {
		f = 1; x = 0; ff = 0;
		for (int i = 0; i < a.size(); ++i) {
			if (i == 0 && a[i] == '-') {
				f = -1; continue;
			}
			if (a[i] < '0' || a[i]>'9') {
				ff = 1; break;
			}
			x *= 10;
			x += a[i] - '0';
			if (x > maxn) {
				std::cout << "������-99999999��99999999֮�������" << std::endl;
				ff = 1; break;
			}
		}
		if (!ff)return x * f;
		std::cout << "���벻�Ϸ�������������" << std::endl;
		getline(std::cin, a);
	}
}
double GetDouble() {
	std::string a;
	getline(std::cin, a);
	int f, ff, z;
	double x = 0, now = 1;
	int maxn = 99999999;
	while (1) {
		f = 1; x = 0; now = 1;
		ff = 0; z = 0;
		for (int i = 0; i < a.size(); ++i) {
			if (i == 0 && a[i] == '-') {
				f = -1; continue;
			}
			if (a[i] == '.') {
				if (z == 1) {
					ff = 1; break;
				}
				z = 1; continue;
			}
			if (a[i] < '0' || a[i]>'9') {
				ff = 1; break;
			}
			if (!z) {
				x *= 10;
				x += a[i] - '0';
			}
			else {
				now /= 10.0;
				x += now * double(a[i] - '0');
			}
			if (x > maxn) {
				std::cout << "������-99999999��99999999֮�����" << std::endl;
				ff = 1; break;
			}
		}
		if (!ff)return x * f;
		std::cout << "���벻�Ϸ�������������" << std::endl;
		getline(std::cin, a);
	}
}

Timer::Timer(){//��ʼ����ʱ��״̬ 
	is_pause = false;
	is_stop = true;
}

bool Timer::isPause(){
	if (is_pause)
		return true;
	else
		return false;
}

bool Timer::isStop()
{
	if (is_stop)
		return true;
	return false;
}

void Timer::Start(double ss) {//��ʼ 
	if (is_stop){
		start_time = clock();
		scale_val = ss;
		is_stop = false;
	}
	else if (is_pause){
		is_pause = false;
		start_time += clock() - pause_time;
	}
}

void Timer::Pause() {//��ͣ 
	if (is_stop || is_pause) return;//�������ֹͣ/��ͣ״̬,�˶��������κδ���ֱ�ӷ��� 
	else {   //�������Ϊ��ͣ״̬
		is_pause = true;
		pause_time = clock(); //��ȡ��ͣʱ�� 
	}
}
void Timer::Stop() { //ֹͣ 
	if (is_stop)return; //���������ֹͣ״̬��������ͣ״̬���������κδ��� 
	else if (is_pause){ //�ı��ʱ��״̬ 
		is_pause = false;
		is_stop = true;
	}
	else if (!is_stop){
		is_stop = true;
	}
}

double Timer::Show(){
	double t = clock() - start_time;
	return t * scale_val;
}

