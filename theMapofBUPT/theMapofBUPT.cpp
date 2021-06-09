// theMapofBUPT.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include "MyAddition.h"
#include "MapGraph.h"
std::string Shahe_Map = "Shahe_Map_Data.txt";
std::string Benbu_Map = "Benbu_Map_Data.txt";
std::string Suggest_Data = "suggest_data.txt";
MapGraph ben, sha;
int bus_sta[2] = { 0,0 }; //本部和沙河公交车站地点，0为本部，1为沙河
int schbus_sta[2] = { 0,0 };//本部和沙河校车站地点，0为本部，1为沙河
void FuzzyOutWay() {
    std::cout << "请输入模糊查询的类型：" << std::endl;
    std::cout << "0.本部内路径查询。" << std::endl;
    std::cout << "1.沙河内路径查询。" << std::endl;
    std::cout << "2.本部到沙河路径查询。" << std::endl;
    std::cout << "3.沙河到本部路径查询。" << std::endl;
    std::cout << "-1. 退出查询" << std::endl;
    int cmd = GetInt(), rt = 0, ed = 0;
    while (cmd < 0 || cmd>3) {
        if (cmd == -1)return;
        std::cout << "输入查询类型不合法，请重新输入（输入-1退出查询）" << std::endl;
        cmd = GetInt();
    }
    if (cmd == 0) {
        std::cout << "进入本部内路径查询模式" << std::endl;
        rt = ben.FuzzyStart();
        if (rt == -1)return;
        ed = ben.FuzzyEnd();
        if (ed == -1)return;
        ben.OutWay(rt, ed);
    }
    else if (cmd == 1) {
        std::cout << "进入沙河内路径查询模式" << std::endl;
        rt = sha.FuzzyStart();
        if (rt == -1)return;
        ed = sha.FuzzyEnd();
        if (ed == -1)return;
        sha.OutWay(rt, ed);
    }
    else if (cmd == 2) {
        std::cout << "进入本部到沙河路径查询模式" << std::endl;
        rt = ben.FuzzyStart();
        if (rt == -1)return;
        ed = sha.FuzzyEnd();
        if (ed == -1)return;
        std::cout << "请输入校区之间交通方式：0. 校车。1. 公交车。" << std::endl;
        int tra = GetInt();
        for (;tra!=1&&tra!=0;) {
            std::cout << "输入不合法，请输入 1 或 0 " << std::endl;
            tra = GetInt();
        }
        if (tra == 1) {
            std::cout << "从起点到本部校门的路径如下" << std::endl;
            ben.OutWay(rt, bus_sta[0]);
            std::cout << "从沙河校门到目的地的路径如下" << std::endl;
            sha.OutWay(bus_sta[1], ed);
        }else{
            std::cout << "从起点到本部校车站点的路径如下" << std::endl;
            ben.OutWay(rt, schbus_sta[0]);
            std::cout << "从沙河校车站点到目的地的路径如下" << std::endl;
            sha.OutWay(schbus_sta[1], ed);
        }
    }
    else {
        std::cout << "进入沙河到本部路径查询模式" << std::endl;
        rt = sha.FuzzyStart();
        if (rt == -1)return;
        ed = ben.FuzzyEnd();
        if (ed == -1)return;
        std::cout << "请输入校区之间交通方式：0. 校车。1. 公交车。" << std::endl;
        int tra = GetInt();
        for (; tra != 1 && tra != 0;) {
            std::cout << "输入不合法，请输入 1 或 0 " << std::endl;
            tra = GetInt();
        }
        if (tra == 1) {
            std::cout << "从起点到沙河校门的路径如下" << std::endl;
            ben.OutWay(rt, bus_sta[1]);
            std::cout << "从本部校门到目的地的路径如下" << std::endl;
            sha.OutWay(bus_sta[0], ed);
        }
        else {
            std::cout << "从起点到沙河校车站点的路径如下" << std::endl;
            ben.OutWay(rt, schbus_sta[1]);
            std::cout << "从本部校车站点到目的地的路径如下" << std::endl;
            sha.OutWay(schbus_sta[0], ed);
        }
    }
}
void FuzzyTSP() {
    std::cout << "请输入模糊途径多点查询的类型：" << std::endl;
    std::cout << "0.本部内途径多点路径查询。" << std::endl;
    std::cout << "1.沙河内途径多点路径查询。" << std::endl;
    std::cout << "-1. 退出查询" << std::endl;
    int cmd = GetInt(), rt = 0, xn=0;
    int* xp = NULL;
    while (cmd < 0 || cmd>1) {
        if (cmd == -1)return;
        std::cout << "输入查询类型不合法，请重新输入（输入-1退出查询）" << std::endl;
        cmd = GetInt();
    }
    std::cout << std::endl;
    if (cmd == 0) {
        std::cout << "进入本部内途径多点路径查询模式" << std::endl;
        std::cout << std::endl;
        rt = ben.FuzzyStart();
        std::cout << std::endl;
        if (rt == -1)return;
        std::cout << "输入途径地点数目(1到7之间的整数)" << std::endl;
        xn = GetInt();
        while (xn < 1 || xn>7) {
            std::cout << "请重新输入途径地点数目(1到7之间的整数)" << std::endl;
            xn = GetInt();
        }
        std::cout << std::endl;
        xp = new int[xn];
        for (int i = 0; i < xn; ++i) {
            xp[i] = ben.FuzzyEnd();
            std::cout << std::endl;
            if (xp[i] == -1) {
                delete[]xp;
                return;
            }
        }
        xp = ben.TSP(rt, xn, xp);
        for (int i = 0; i < xn; ++i) {
            std::cout << "第" << i + 1 << "个应该前往的地点是" << ben.GetName(xp[i]) << std::endl;
        }
        std::cout << std::endl;
        std::cout << "是否输出具体路径,若输出具体路径请输入1，输入其他数字退出。" << std::endl;
        int zz = GetInt();
        if (zz != 1) { 
            delete[]xp;
            return; 
        }
        std::cout << std::endl;
        std::cout << "输出具体路径如下" << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < xn; ++i) {
            if (i != 0) {
                std::cout << "从 " << ben.GetName(xp[i - 1]) << " 到 " << ben.GetName(xp[i]) << std::endl;
                ben.OutWay(xp[i - 1], xp[i]);
            }
            else {
                std::cout << "从 " << ben.GetName(rt) << " 到 " << ben.GetName(xp[i]) << std::endl;
                ben.OutWay(rt, xp[i]);
            }
            std::cout << std::endl;
        }
    }
    else if (cmd == 1) {
        std::cout << "进入沙河内途径多点路径查询模式" << std::endl;
        std::cout << std::endl;
        rt = sha.FuzzyStart();
        std::cout << std::endl;
        if (rt == -1)return;
        std::cout << "输入途径地点数目(1到7之间的整数)" << std::endl;
        xn = GetInt();
        while (xn < 1 || xn>7) {
            std::cout << "请重新输入途径地点数目(1到7之间的整数)" << std::endl;
            xn = GetInt();
        }
        std::cout << std::endl; 
        xp = new int[xn];
        for (int i = 0; i < xn; ++i) {
            xp[i] = sha.FuzzyEnd();
            std::cout << std::endl;
            if (xp[i] == -1) {
                delete[]xp;
                return;
            }
        }
        xp = sha.TSP(rt, xn, xp);
        for (int i = 0; i < xn; ++i) {
            std::cout << "第" << i + 1 << "个应该前往的地点是" << sha.GetName(xp[i]) << std::endl;
        }
        std::cout << std::endl;
        std::cout << "是否输出具体路径,若输出具体路径请输入1，输入其他数字退出。" << std::endl;
        int zz = GetInt();
        if (zz != 1) {
            delete[]xp;
            return;
        }
        std::cout << std::endl;
        std::cout << "输出具体路径如下：" << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < xn; ++i) {
            if (i != 0) {
                std::cout << "从 " << sha.GetName(xp[i - 1]) << " 到 " << sha.GetName(xp[i]) << std::endl;
                sha.OutWay(xp[i - 1], xp[i]);
            }
            else {
                std::cout << "从 " << sha.GetName(rt) << " 到 " << sha.GetName(xp[i]) << std::endl;
                sha.OutWay(rt, xp[i]);
            }
            std::cout << std::endl;
        }
    }
    delete[]xp;
    return;
}
int main()
{
    std::cout << "建立本部地图\n";
    ben.BuildGraph(Benbu_Map,Suggest_Data);
    std::cout << "建立沙河地图\n";
    sha.BuildGraph(Shahe_Map,Suggest_Data);
    for (;;)FuzzyTSP();
    //int x, y;
    //std::cin>>x>>y;
    //b.OutWay(y,x);
    //b.Search();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
