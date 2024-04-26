#include"main.h"

int main(){
	int choice = 0;
	bool flag = true;
	while(flag){
		cout<<"  保安休息日排版系统"<<endl;
		cout<<"########################"<<endl;
		cout<<"  1.预选休息日信息录入"<<endl;;
		cout<<"  2.轮休方案管理"<<endl;
		cout<<"  3.清屏"<<endl;
		cout<<"  4.退出"<<endl;
		cout<<"########################"<<endl;
		cout<<"请选择您的操作：";
		cin>>choice;
		switch(choice){
			case 1:
				{
					plan p;
					p.choice_plan_fc();
				}break;
			case 2:
				{
					solution s;
				}break;
			case 3:
				{
					system("cls");
				}break;
			case 4:
				{
					quit();//退出
				}break;
			default:
				if(cin.fail()){//输入非法字符，cin被锁
					cin.clear();//解锁
					cin.ignore(1024);
				}
		}
	}
}