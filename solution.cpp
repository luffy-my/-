#include"solution.h"

using namespace std;
solution::solution(){
	while(true){
		cout<<"++++++++++++++++++++++++"<<endl;
		cout<<"\t1.查看解决方案"<<endl;
		cout<<"\t2.生成解决方案"<<endl;
		cout<<"\t3.保存解决方案"<<endl;
		cout<<"\t4.清空解决方案"<<endl;
		cout<<"\t0.返回上一级"<<endl;
		cout<<"++++++++++++++++++++++++"<<endl;
		cout<<"请选择您的操作：";
		int choice;
		cin>>choice;
		switch(choice){
			case 1:
				{
					showSolution();
				}
				break;
			case 2:
				{
					generateSolution();
				}
				break;
			case 3:
				{
					saveSolution();
				}
				break;
			case 4:
				{
					clearSolution();
				}
				break;
			case 0:
				{
					cout<<endl<<endl;
					return;
				};
			default:
				if(cin.fail()){//输入非法字符，cin被锁
					cin.clear();//解锁
					cin.ignore(1024, '\n');
				}
		}
	}
}

void solution::showSolution(){

	while(true){
		cout<<"1.查看历史的所有排班解决方案"<<endl;
		cout<<"2.查看当前的排班解决方案"<<endl;
		cout<<"0.返回上一级"<<endl;
		cout<<"请选择您的操作：";
		int choice;
		cin>>choice;
		switch(choice){
			case 1:
				{
					showHostorySolution();
				}
				break;
			case 2:
				{
					showCurrentSolution();
				}
				break;
			case 0:return;
			default:
				if(cin.fail()){//输入非法字符，cin被锁
					cin.clear();
					cin.ignore(1024, '\n');
				}
		}
	}
}

void solution::generateSolution(){

	if(!inputFlag){
		color(12);
		cout<<"==>请完成操作1再来尝试[手动滑稽]<=="<<endl;
		color(7);
		return;
	}

	cursorShow(false);
	loading("analysing");
	cout<<"\r";


	// 临时的预选方案
	int myChoiceFlag[N][N+1] = {0};
	for(int i = 0; i<N; i++){
		for(int j = 0; j<=N; j++){
			myChoiceFlag[i][j] = choiceFlag[i][j];
		}
	}

	int clearFlag = false; // 同一列的抹除标志
	int currentGuardIndex = 0; //记录当前保安的索引
	while(true){
		clearFlag = false;
		for(int day = 1; day<=N; day++){
			if(myChoiceFlag[currentGuardIndex][0]==1&&myChoiceFlag[currentGuardIndex][day]==1){ //保安只预选了一天休息日，且当日可用，则预先考虑

				// 做出决策
				legalityMap[currentGuardIndex] = weeks[day-1]; // 合法性映射存储解决方案必须包含的结果，所有决策都绝对合法

				clearFlag = true;
				//同属于列的休息日全部被清空
				for(int k = 0; k<N; k++){
					if(myChoiceFlag[k][day]==1){
						myChoiceFlag[k][0] -= 1;
						myChoiceFlag[k][day] = 0;
					}
				}

				currentGuardIndex = 0;
				break;
			}
		}
		currentGuardIndex++;
		if(currentGuardIndex==N&&clearFlag==0) break;
	}


	for(int k = 0; k<N; k++){
		if(myChoiceFlag[k][0]>0){
			clearFlag = 0;
		}
	}
	if(legalityMap.size()<N){

		// 根据首轮化简的休息日预选方案确定新方案

		//保存临时合法性映射
		tempLegalityMap = map<int, string>(legalityMap.begin(), legalityMap.end());

		// 待确定的候选映射
		map<int, string> candidateMap;
		for(int k = 0; k<N; k++){
			if(myChoiceFlag[k][0]>0){
				candidateMap[k] = weeks[k];
			}
		}

		// 待确定的预选标志
		int candidateChoice[N][N] = {0};
		bool flag = false;
		for(int i = 0, k = 0; i<N; i++){
			for(int j = 1; j<=N; j++){
				if(myChoiceFlag[i][0]>0){
					candidateChoice[k][j-1] = myChoiceFlag[i][j];
					flag = true;
				}
			}
			if(!flag){
				k--;
			}
			k++;
		}
		findSolution(candidateMap, candidateChoice);//寻找新的解决方案
		inputFlag = false; //输入标志更新
		color(7);
	}
	else{
		for(const auto &week:legalityMap){
			currentSolution.push_back(week.second);
		}
		currentAllSolution.push_back(currentSolution);
		//只有一种解决方案
		color(14);
		cout<<"唯一方案："<<endl;
		color(7);
		cout<<"  "<<namesPrint<<endl;
		cout<<"  ";
		color(11);
		for(const auto &week:legalityMap){
			cout<<week.second<<"\t  ";
		}
		color(7);
		cout<<endl;
	}
	cursorShow(true);
}

//Core Function
void solution::findSolution(map<int, string> &candidateMap, const int candiateFlag[N][N]){
	static int count = 0;
	if(tempLegalityMap.size()==N){ // 临时合法映射已经满足所有保安
		// 所有保安都分配了休息日，输出解决方案
		color(14);
		cout<<"解决方案"<<++count<<":"<<endl;
		color(11);
		cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		for(const auto &week:tempLegalityMap){
			currentSolution.push_back(week.second);
			cout<<week.second<<"\t";
		}
		cout<<endl<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
		cout<<endl;
		currentAllSolution.push_back(currentSolution);
		currentSolution.clear();//清空当前解决方案
		return;
	}
	if(candidateMap.size()==0){
		return;
	}
	int currentNode = 0;
	if(!candidateMap.empty())
		currentNode = candidateMap.begin()->first;
	for(int j = 0; j<N; j++){
		if(candiateFlag[currentNode][j]==1){
			// 决策开始...

			//检查决策的合法性
			bool isLegility = checkedLegility(j);
			if(isLegility==true){//决策合法

				tempLegalityMap[currentNode] = weeks[j]; //保存本轮相对合法的决策，但不确保最后不冲突
				//递归到一个保安位置
				map<int, string> newCandidateMap(next(candidateMap.begin(), 1), candidateMap.end());
				findSolution(newCandidateMap, candiateFlag); // 递归寻找决策
				//回溯决策，删除当前节点的值，寻找当前节点的下一个待确定的位置，无论查找成功与否都要回溯
				tempLegalityMap.erase(currentNode);
			}
		}
	}
}

void solution::saveSolution(){

	if(currentAllSolution.size()==0){
		color(12);
		cout<<"==>请完成操作1再来尝试[手动滑稽]<=="<<endl;
		color(7);
	}
	int choice;
	while(true){
		cout<<"1.保存当前解决方案并同步到历史解决方案"<<endl;
		cout<<"2.仅保存当前解决方案"<<endl;
		cout<<"0.返回上一级"<<endl;
		cout<<"请选择您的操作：";
		cin>>choice;
		switch(choice){
			case 1:
				{
					concurrentSaveSolution();
				}
				break;
			case 2:
				{
					saveCurrentSolution();
				}
				break;
			case 0:
				{
					cout<<endl<<endl;
					return;
				};
			default:
				if(cin.fail()){//输入非法字符，cin被锁
					cin.clear();
					cin.ignore(1024, '\n');
				}
		}
	}
}

void solution::clearSolution(){

	int choice;
	while(true){
		cout<<"1.清除当前解决方案"<<endl;
		cout<<"2.清除历史解决方案"<<endl;
		cout<<"0.返回上一级"<<endl;
		cout<<"请选择您的操作：";
		cin>>choice;
		switch(choice){
			case 1:
				{
					clearCurrentSolution();
				}break;
			case 2:
				{
					clearHostorySolution();
				}break;
			case 0:
				{
					cout<<endl<<endl;
					return;
				};
			default:
				if(cin.fail()){//输入非法字符，cin被锁
					cin.clear();
					cin.ignore(1024, '\n');
				}
		}
	}
}

//合法性检测
bool solution::checkedLegility(int target){

	for(const auto &pair:tempLegalityMap){
		if(pair.second==weeks[target]){
			return false;
		}
	}
	return true;
}

void solution::showHostorySolution(){

	cursorShow(false);
	loading("loading");
	if(hostroySolution.size()==0){
		ifstream file;
		file.open("hostorySolution.txt", ios::in);//默认文本文件形式打开

		if(file){
			stringstream ss; //字符串流
			ss<<file.rdbuf();//一次性读取文件全部内容
			string allContent = ss.str();
			cout<<"\r";
			cout<<allContent;
		}
		file.close();
	}
	//else{
	//	int count = 0;
	//	for(const auto &solution:hostroySolution){
	//		cout<<"解决方案"<<++count<<"\n";
	//		for(const auto &week:solution){
	//			cout<<week<<"\t"; // 在元素之间添加空格分隔
	//		}
	//		cout<<endl; // 每个子向量写完后换行
	//	}
	//}
	cursorShow(true);
}

void solution::showCurrentSolution(){
	cursorShow(false);
	loading("loading");
	if(currentAllSolution.size()==0){
		ifstream file;
		file.open("currentSolution.txt", ios::in);//默认文本文件形式打开

		if(file){
			stringstream ss; //字符串流
			ss<<file.rdbuf();//一次性读取文件全部内容
			string allContent = ss.str();
			if(allContent=="") cout<<endl<<"你要看的文件信息飞走了V|V"<<endl;
			cout<<"\r";
			cout<<allContent;
		}
		file.close();
	}
	else{
		int count = 0;
		for(const auto &solution:currentAllSolution){
			cout<<"解决方案"<<++count<<":"<<endl;
			for(const auto &week:solution){
				cout<<week<<"\t"; // 在元素之间添加空格分隔
			}
			cout<<endl; // 每个子向量写完后换行
		}
	}
	cursorShow(true);
}

void solution::saveCurrentSolution(){
	ofstream ofs;
	ofs.open("currentSolution.txt", ios::basic_ios::trunc);//以写入截断模式打开，不存在则创建
	//写入解决方案
	//获取当前时间
	auto now = chrono::system_clock::now();
	auto now_c = chrono::system_clock::to_time_t(now);
	// 创建足够大的缓冲区并使用 `strftime` 转换为字符串
	struct tm localtime;
	localtime_s(&localtime, &now_c);//转换为本地时区
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localtime);
	cursorShow(false);
	loading("saving");
	ofs<<buffer<<"\n";
	int count = 0;
	for(const auto &solution:currentAllSolution){
		ofs<<"解决方案"<<++count<<":"<<"\n";
		for(const auto &item:solution){
			ofs<<item<<"\t"; // 在元素之间添加空格分隔
		}
		ofs<<"\n"; // 每个子向量写完后换行
	}
	ofs.close();
	color(14);
	cout<<"\r文件已被保存！"<<endl;
	color(7);
	cursorShow(true);
}

void solution::concurrentSaveSolution(){

	ofstream ofs1, ofs2;
	ofs1.open("currentSolution.txt", ios::out|ios::ios_base::trunc); //以追加模式打开，不存在则创建
	ofs2.open("hostorySolution.txt", ios::out|ios::ios_base::app); //以追加模式打开，不存在则创建
	//写入解决方案
	//获取当前时间
	auto now = chrono::system_clock::now();
	auto now_c = chrono::system_clock::to_time_t(now);
	// 创建足够大的缓冲区并使用 `strftime` 转换为字符串
	struct tm localtime;
	localtime_s(&localtime, &now_c);//转换为本地时区
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localtime);
	cursorShow(false);
	loading("saving");
	ofs1<<buffer<<"\n";
	ofs2<<buffer<<"\n";
	int count = 0;
	for(const auto &solution:currentAllSolution){
		ofs1<<"解决方案"<<++count<<"\n";
		ofs2<<"解决方案"<<count<<"\n";
		for(const auto &item:solution){
			ofs1<<item<<"\t"; // 在元素之间添加空格分隔
			ofs2<<item<<"\t";
		}
		ofs1<<"\n"; // 每个子向量写完后换行
		ofs2<<"\n"; // 每个子向量写完后换行
	}
	ofs2<<"\n";
	ofs1.close();
	ofs2.close();
	color(14);
	cout<<"\r"<<"文件已被保存和同步！"<<endl;
	color(7);
	currentAllSolution.clear();//清空当前的所有解决方案
	cursorShow(true);
}

void solution::clearCurrentSolution(){

	cout<<endl<<"确认是否删除y|N：";
	string confirm;
	getline(cin, confirm);
	if(confirm!="y"&&confirm!="Y"){
		cout<<endl<<"您取消了对当前方案的清空"<<endl;
		return;
	}
	cursorShow(false);
	loading("clearing");
	ofstream outfile;//输文件出流
	outfile.open("currentSolution.dat", ios::out|ios::trunc);//截断文件流达到清空文件的目的
	outfile.close();
	color(14);
	cout<<"\r文件已被清空！"<<endl;
	color(7);
	cursorShow(true);
}

void solution::clearHostorySolution(){
	color(12);
	cout<<"警告!";
	color(7);
	cout<<"您正在进行危险操作, 请输入密码验证身份：";
	bool isIllegal = identify();
	cin.clear();
	cin.ignore(1024, '\n');
	if(isIllegal) return;
	// 安全性验证
	color(12);
	cout<<endl<<"确认是否删除y|N：";
	color(7);
	string confirm = "";
	getline(cin, confirm);
	if(confirm!="y"&&confirm!="Y"){
		cout<<endl<<"您取消了对历史方案的清空"<<endl;
		return;
	}
	ofstream outfile;//输文件出流
	cursorShow(false);
	loading("clear");
	outfile.open("hostorySolution.txt", ios::out|ios::trunc);//截断文件流达到清空文件的目的
	outfile.close();
	color(14);
	cout<<"\r"<<"文件已被清空！"<<endl;
	color(7);
	cursorShow(true);

}

//身份确认
bool solution::identify(){

	string password;
	char ch;
	while((ch = _getch())!='\r'){
		if(ch=='\b'||ch==8){ // 处理退格键
			if(!password.empty()){
				password.pop_back();
				cout<<"\b \b"; // 删除一个星号并后退光标位置
			}
		}
		else if(isprint(ch)){ // 只接受可打印字符作为密码
			password.push_back(ch);
			cout<<'*'; // 输出星号代替实际字符
		}
	}
	if(password!="root"){
		cout<<endl;
		this_thread::sleep_for(chrono::seconds(2));
		cout<<"\a";
		if(chance>1){
			cout<<"密码错误！"<<"剩余输入次数为"<<--chance<<endl;
		}
		else{
			cout<<"文件已被上锁，请联系管理员解决"<<endl;
		}
		return true;
	}
	return false;
}
