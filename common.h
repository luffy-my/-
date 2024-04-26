#pragma once
#include<iostream>
#include<Windows.h>
#include<vector>
#include<map>
#include<thread>
#include<time.h>
using namespace std;

#define N 7
extern string namesPrint; // 声明 namesPrint
extern string names[N]; // 声明 names 数组
extern string weeksPrint; // 声明 weeksPrint 
extern string weeks[N]; // 声明 weeks 数组
extern vector<string> hostroySolution; //声明历史解决方案字符串数组
extern vector<string> currentSolution; //声明当前解决方案字符串数组
extern vector<vector<string>> currentAllSolution; //声明当前所有解决方案的数组
extern map<int,string> legalityMap; //声明合法性映射
extern map<int, string> tempLegalityMap; //声明临时合法性映射
extern int currentNode; //当前节点位置
extern int choiceFlag[N][N+1]; // 声明 choiceFlag 数组
extern int chance;
extern bool inputFlag; // 声明 inputFlag 
extern void loading(const char loadName[]);
extern void setCursorPosition(const int &x,const int &y); //设置光标位置
extern void cursorShow(bool isShow); //光标显示与影藏
extern void color(short x); //控制台颜色
extern void quit(); //退出