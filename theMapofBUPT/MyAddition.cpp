
#include<string>
#include<iostream>
#include "MyAddition.h"
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
