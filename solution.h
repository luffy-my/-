#pragma once
#include"common.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<thread>
#include<time.h>
#include<ctime>
class solution{ 
	public:
	solution();
	void showSolution(); //展示解决方案
	void generateSolution(); //生成解决方案
	void findSolution(map<int,string> &candidate,const int cadidateFlag[N][N]); //查找解决方案 
	void saveSolution(); //保存解决方案
	void clearSolution(); //清除解决方案
	bool checkedLegility(int target); //合法性检测

	private:
	void showHostorySolution();
	void showCurrentSolution();
	void saveCurrentSolution();
	void concurrentSaveSolution();
	void clearCurrentSolution();
	void clearHostorySolution();
	bool identify();
};

