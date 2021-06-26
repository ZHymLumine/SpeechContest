#include<iostream>
#include"speechManager.h"
#include<ctime>
using namespace std;

int main()
{	
	//随机数种子
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	int choice = 0;
	
	while (true)
	{	
		sm.show_menu();
		cout << "请输入你的选择:  " << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:  //退出系统
			sm.exit_system();
			break;
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		default:
			system("cls");
			break;
		}
	}

	
}