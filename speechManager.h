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

	//��ʾ�˵�
	void show_menu();

	//�˳�ϵͳ
	void exit_system();

	//��ʼ����Ա����
	void initSpeech();
	
	
	//����ѡ��
	void createSpeaker();
	
	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼
	void saveRecord();

	//���Ʊ�������
	void startSpeech();

	//��ȡ��¼
	void loadRecord();

	//��ʾ����÷�
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;
	
	~SpeechManager();
	
	//��Ա����
	//�����һ�ֱ���ѡ�ֱ�ŵ�����
	vector<int>v1;

	//��һ�ֽ���ѡ�ֵ�����
	vector<int>v2;

	//ʤ��ǰ����ѡ�ֵ�����
	vector<int>vVictory;

	//��ű���Լ���Ӧ����ѡ������
	map<int, Speaker>m_Speaker;

	//��ű�������
	int m_Index;

	//�����¼
	map<int, vector<string>>m_Record;
};