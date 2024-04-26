#include "common.h"

string namesPrint = "老赵\t\t  老钱\t\t  老孙\t\t  老李\t\t  老周\t\t  老吴\t\t  老陈";
string names[N] = {"老赵", "老钱", "老孙", "老李", "老周", "老吴", "老陈"};
string weeksPrint = "星期一\t星期二\t星期三\t星期四\t星期五\t星期六\t星期日";
string weeks[N] = {"星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"};
vector<string> hostroySolution;
vector<string> currentSolution;
vector<vector<string>> currentAllSolution;
map<int, string> legalityMap;
map<int, string> tempLegalityMap;
int choiceFlag[N][N+1] = {0};
bool inputFlag = false;
int chance = 3;
int completedScanIndex = -1; //初始化为-1表示没有任何保安节点遍历完成
int currentNode = 0; // 当前节点位置

void color(short x){	//自定义函根据参数改变颜色
	if(x>=0&&x<=255) //参数在0-15的范围颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|x);	//高亮前景色
	else//默认的颜色白色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|x);  //高亮前景色
}

void setCursorPosition(const int &x,const int &y){//设置光标位置
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台输出句柄
	COORD setps = {//定义光标位置的结构体变量（coord:坐标）
		setps.X = x,//光标的横坐标
		setps.Y = y//光标的纵坐标}
	};
	SetConsoleCursorPosition(handle, setps);//设置光标的位置
}

void cursorShow(bool isShow){ //隐藏、显示光标
	CONSOLE_CURSOR_INFO curinfo = {//定义光标信息的结构体变量
		curinfo.dwSize = 1,//没赋值的话隐藏光标无效
		curinfo.bVisible = isShow//将光标设置不可见
	};
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台的输出句柄
	SetConsoleCursorInfo(handle, &curinfo);//设置光标的信息
}

void loading(const char loadName[]){
	cout<<loadName;
	for(int i = 0; i<3; i++){
		for(int j = 0; j<3; j++){
			cout<<".";
			this_thread::sleep_for(chrono::milliseconds(200));
		}
		cout<<"\b\b\b   \b\b\b"; //回退
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}

void quit(){ //退出控制台程序
	system("cls");
	printf_s("程序退出中");
	setCursorPosition(10, 0);
	printf_s("○○○");
	for(int k = 0; k<3; k++){
		for(int i = 0; i<3; i++){
			setCursorPosition(10+2*i, 0);
			printf_s("●");
			Sleep(200);
			if(i>0){
				setCursorPosition(10+2*i-2, 0);
				printf_s("○");
			}
		}
		setCursorPosition(10, 0);
		printf_s("○○○");
	}
	system("cls");
	Sleep(450);
	printf_s("退出成功！");
	Sleep(500);
	printf_s("\n\t\t************************************\n");
	color(11);
	printf_s("\t\t\t感谢您的使用，有缘再见！\n");
	color(14);
	printf_s("\t\t************************************\n");
	Sleep(1000);
	exit(0);
}
