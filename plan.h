#pragma once
#include"common.h"
#include<iostream>
#include<vector>
#include <string>
#include <regex>
using namespace std;
class plan{ 
	public:
	void choice_plan_fc();
	vector<string> splitStr(const string &s,string &pattern);
	void trim(string &str);
};

