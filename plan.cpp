#include "plan.h"

void plan::choice_plan_fc(){
	inputFlag = true;
	string choice_Numstr;
	string pattern = "[ ,]+";
	vector<string> res;
	getchar();
	for(int i = 0; i<N; i++){
		int count = 0;
		cout<<"请一次性输范围为1-7的整数表示"<<names[i]<<"的第几个休息日（可输入多个），每个数字请用空格或逗号隔开："<<endl;
		getline(cin, choice_Numstr);
		trim(choice_Numstr);//去除多余的空格
		if(choice_Numstr.length()==0){
			i--;
			continue;
		}
		res = splitStr(choice_Numstr, pattern);
		cout<<endl;
		for(auto j = res.begin(); j<res.end(); j++){
			choiceFlag[i][stoi(*j)] = 1;
			count++;
		}
		choiceFlag[i][0] = count;
	}
	cout<<N<<"名保安的预选休息日如下："<<endl;
	cout<<"  \t"<<weeksPrint<<endl;
	for(int i = 0; i<N; i++){
		cout<<"  "<<names[i];
		for(int j = 1; j<=N; j++){
			//cout<<"\t"<<choiceFlag[i][j];
			if(choiceFlag[i][j]){
				color(11);
				cout<<"\t"<<"√";
				color(7);
			}
			else{
				cout<<"\t"<<"×";
			}
		}
		cout<<endl;
	}
	cout<<endl;
}

vector<string> plan::splitStr(const string &s, string &pattern){
	regex re(pattern);
	sregex_token_iterator first{s.begin(), s.end(), re, -1}, last;
	return {first, last};
}

void plan::trim(string &str){
	// 去除字符串首尾空格的函数
	str.erase(0, str.find_first_not_of(" \t\r\n\v\f"));  // 去除字符串开头的空格
	str.erase(str.find_last_not_of(" \t\r\n\v\f")+1);  // 去除字符串结尾的空格
}




