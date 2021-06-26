#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"

using namespace std;

class SpeechManager
{
public:
	SpeechManager();

	//显示菜单
	void show_menu();

	//退出系统
	void exit_system();

	//初始化成员属性
	void initSpeech();
	
	
	//创建选手
	void createSpeaker();
	
	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存记录
	void saveRecord();

	//控制比赛流程
	void startSpeech();

	//读取记录
	void loadRecord();

	//显示往届得分
	void showRecord();

	//清空记录
	void clearRecord();

	//判断文件是否为空
	bool fileIsEmpty;
	
	~SpeechManager();
	
	//成员属性
	//保存第一轮比赛选手编号的容器
	vector<int>v1;

	//第一轮晋级选手的容器
	vector<int>v2;

	//胜出前三名选手的容器
	vector<int>vVictory;

	//存放编号以及对应具体选手容器
	map<int, Speaker>m_Speaker;

	//存放比赛轮数
	int m_Index;

	//往届记录
	map<int, vector<string>>m_Record;
};