#pragma once
#include<string>
#include<time.h>
extern int System_State;//ϵͳ��ѯģʽ
extern double System_Velo;//��ǰģʽ���˶��ٶ�
extern double System_Bike;//Ĭ�ϵ����г��ٶ�
extern double System_Person;//Ĭ�ϵ������ٶ�
std::string GetS();//���ո�ʽ�����ַ���
int GetInt();//���ո�ʽ����int
double GetDouble();//���ո�ʽ����double
struct Suggest {
	std::string source;
	std::string sug;
};

class Timer{
private:
	int start_time;
	int pause_time;
	double scale_val;//���ٱ���
	//����boolֵ�������״̬ 
	bool is_pause; //��¼��ʱ����״̬ ���Ƿ�����ͣ״̬��
	bool is_stop;//�Ƿ���ֹͣ״̬ 
public:
	Timer();
	bool isPause(); //���ؼ�ʱ��״̬ 
	bool isStop();
	//��ʱ�������ֶ��������ܣ�
	void Start(double ss);
	void Pause();
	void Stop();
	double Show();//����ʱ��
};
