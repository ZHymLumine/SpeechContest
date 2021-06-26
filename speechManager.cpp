#include"speechManager.h"
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<map>
#include<string>
#include<fstream>

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
	
}

//显示菜单
void SpeechManager::show_menu()
{
	cout << "*****************************************" << endl;
	cout << "***********  欢迎参加演讲比赛  ***********" << endl;
	cout << "***********  1.开始演讲比赛  *************" << endl;
	cout << "***********  2.查看往届记录  *************" << endl;
	cout << "***********  3.清空比赛记录  *************" << endl;
	cout << "***********  0.退出比赛程序  *************" << endl;

}

//退出系统
void SpeechManager::exit_system()
{
	cout << "欢迎您下次使用" << endl;
	system("pause");
	exit(0);
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "正在进行第" << this->m_Index << "轮比赛抽签" << endl;
	cout << "--------------------------" << endl;
	cout << "抽签后演讲顺序如下： " << endl;
	if (this->m_Index == 1)  //第一轮比赛
	{
		random_shuffle(v1.begin(), v1.end());
		for (auto it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
			
		}
		cout << endl;
	}
	else  //第二轮比赛	
	{
		random_shuffle(v2.begin(), v2.end());
		for (auto it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";

		}
		cout << endl;
	}
	cout << "---------------------------" << endl;
	system("pause");
}

//比赛
void SpeechManager::speechContest()
{	
	cout << "----------------第" << this->m_Index << "轮比赛正式开始----------------" << endl;
	vector<int>src;
	map<double, int, greater<double>> groupScore; //临时容器 储存分数和对应编号

	int num = 0;
	if (this->m_Index == 1)
	{
		src = this->v1;
	}
	else
	{
		src = this->v2;
	}
	
	for (vector<int>::iterator it = src.begin(); it != src.end(); it++)
	{	
		num++;
		//将评委的分数 放入到deque容器中
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  // 60 ~ 100
			d.push_back(score);
		}

		//排序
		sort(d.begin(), d.end());

		//去除最高和最低分
		d.pop_back();
		d.pop_front();

		//取平均分
		double sum = 0;
		for (deque<double>::iterator dit = d.begin(); dit != d.end(); dit++)
		{
			sum += *dit; //累加每个评委的分数
		}

		double avg = sum / (double)d.size();

		//将平均分 赋值给选手身上
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次： " << endl;
			for (auto mit = groupScore.begin(); mit != groupScore.end(); mit++)
			{
				cout << "编号： " << mit->second << "  姓名： " << this->m_Speaker[mit->second].m_Name
					<< " 成绩" << this->m_Speaker[mit->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//取前三名
			for (auto mit = groupScore.begin(); mit != groupScore.end()&& count<3; mit++, count++)
			{
				if (this->m_Index == 1)   //第一次比赛的前三名 保存到 v2中
				{
					this->v2.push_back(mit->second);
				}
				else    
				{
					this->vVictory.push_back(mit->second);  //第二次比赛的前三名保存到 优胜组 vVictory
				}
			}

			groupScore.clear();

			cout << endl;
		}
	}
	
	cout << "-----------------第" << this->m_Index << "轮比赛完毕------------" << endl;
}

//显示比赛结果
void SpeechManager::showScore()
{
	cout << "------------第" << this->m_Index << "轮晋级选手信息如下： -------------" << endl;
	
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号： " << *it << "  姓名： " << this->m_Speaker[*it].m_Name
			<< " 成绩" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");

	this->show_menu();
}


//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);  //写文件
	
	//将每个人的数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();

	cout << "记录已经保存" << endl;
	
	this->fileIsEmpty = false;  //将文件为空标志改为false
}
//控制比赛流程
void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1.抽签
	speechDraw();

	//2.比赛
	speechContest();
	
	//3.显示晋级结果
	showScore();

	this->m_Index++;

	//第二轮比赛
	//1.抽签
	speechDraw();

	//2.比赛
	speechContest();

	//3.显示最终结果
	showScore();

	//4.保存分数
	saveRecord();

	//重置比赛
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;

	system("pause");
	system("cls");

}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open())
	{	
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "文件为空" << endl;
		ifs.close();
		return;
	}


	//文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch);

	string data;
	int index = 1;  //比赛届数


	while (ifs >> data)
	{

		vector<string>v; //储存每个字符串
		int pos = -1;
		int start = 0;  //开始位置
		
		while (true)
		{
			pos = data.find(",", start);

			if (pos == -1)
			{
				break;
			}
			
			string temp = data.substr(start, pos - start);
		
			v.push_back(temp);
			start = pos + 1;
		}
		
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	/*for (auto it = this->m_Record.begin(); it != this->m_Record.end(); it++)
	{
		cout << it->first << " 冠军编号： " << it->second[0] << " 分数： " << it->second[1] << endl;
	}*/  //遍历m_Record
}

//显示往届得分
void SpeechManager::showRecord()
{	
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或记录为空！" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
		{
			cout << "第" << it->first << "届" <<
				"冠军编号: " << it->second[0] << " 得分： " << it->second[1] << " "
				"亚军编号：" << it->second[2] << " 得分： " << it->second[3] << " "
				"季军编号：" << it->second[4] << " 得分： " << it->second[5] << " " << endl;
		}
	}
	

	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空?" << endl;
	cout << "1.确认" << endl;
	cout << "2.取消" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);  //如存在，则删除后重新创建
		ofs.close();

		this->initSpeech();

		this->createSpeaker();

		this->loadRecord();

		cout << "清除成功" << endl;
	}
	system("pause");
}

// 初始化成员属性
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比赛轮数
	this->m_Index = 1;

	//将记录中的数据清空
	this->m_Record.clear();
}

//创建选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}
		 // 12名选手编号
		this->v1.push_back(i + 10001);
		
		//选手编号 以及对应的选手 存放到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
SpeechManager::~SpeechManager()
{

}