
#include<string>
#include<iostream>
#include<time.h>
#include "MyAddition.h"

int System_State = 0;//系统查询模式
double System_Velo = 1.5;//当前模式的运动速度
double System_Bike = 5.0;//默认的自行车速度
double System_Person = 1.5;//默认的行走速度

std::string GetS() {//按照格式读入字符串
	std::string a;
	getline(std::cin, a);
	while (a.size() > 100) {
		std::cout << "字符串大小需小于100，请重新输入" << std::endl;
		getline(std::cin, a);
	}
	return a;
}
int GetInt() {//按照格式读入int
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
				std::cout << "请输入-99999999到99999999之间的整数" << std::endl;
				ff = 1; break;
			}
		}
		if (!ff)return x * f;
		std::cout << "输入不合法，请重新输入" << std::endl;
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
				std::cout << "请输入-99999999到99999999之间的数" << std::endl;
				ff = 1; break;
			}
		}
		if (!ff)return x * f;
		std::cout << "输入不合法，请重新输入" << std::endl;
		getline(std::cin, a);
	}
}

Timer::Timer(){//初始化计时器状态 
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

void Timer::Start(double ss) {//开始 
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

void Timer::Pause() {//暂停 
	if (is_stop || is_pause) return;//如果处于停止/暂停状态,此动作不做任何处理，直接返回 
	else {   //否则调制为暂停状态
		is_pause = true;
		pause_time = clock(); //获取暂停时间 
	}
}
void Timer::Stop() { //停止 
	if (is_stop)return; //如果正处于停止状态（不是暂停状态），不做任何处理 
	else if (is_pause){ //改变计时器状态 
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

