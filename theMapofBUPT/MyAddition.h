#pragma once
#include<string>
#include<time.h>
std::string GetS();//按照格式读入字符串
int GetInt();//按照格式读入int
double GetDouble();//按照格式读入double
struct Suggest {
	std::string source;
	std::string sug;
};

class Timer{
private:
	int start_time;
	int pause_time;
	double scale_val;//加速比例
	//两个bool值标记四种状态 
	bool is_pause; //记录计时器的状态 （是否处于暂停状态）
	bool is_stop;//是否处于停止状态 
public:
	Timer();
	bool isPause(); //返回计时器状态 
	bool isStop();
	//计时器的三种动作（功能）
	void Start(double ss);
	void Pause();
	void Stop();
	double Show();//返回时间
};
