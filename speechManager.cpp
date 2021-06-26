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

//��ʾ�˵�
void SpeechManager::show_menu()
{
	cout << "*****************************************" << endl;
	cout << "***********  ��ӭ�μ��ݽ�����  ***********" << endl;
	cout << "***********  1.��ʼ�ݽ�����  *************" << endl;
	cout << "***********  2.�鿴�����¼  *************" << endl;
	cout << "***********  3.��ձ�����¼  *************" << endl;
	cout << "***********  0.�˳���������  *************" << endl;

}

//�˳�ϵͳ
void SpeechManager::exit_system()
{
	cout << "��ӭ���´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��ǩ
void SpeechManager::speechDraw()
{
	cout << "���ڽ��е�" << this->m_Index << "�ֱ�����ǩ" << endl;
	cout << "--------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£� " << endl;
	if (this->m_Index == 1)  //��һ�ֱ���
	{
		random_shuffle(v1.begin(), v1.end());
		for (auto it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
			
		}
		cout << endl;
	}
	else  //�ڶ��ֱ���	
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

//����
void SpeechManager::speechContest()
{	
	cout << "----------------��" << this->m_Index << "�ֱ�����ʽ��ʼ----------------" << endl;
	vector<int>src;
	map<double, int, greater<double>> groupScore; //��ʱ���� ��������Ͷ�Ӧ���

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
		//����ί�ķ��� ���뵽deque������
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  // 60 ~ 100
			d.push_back(score);
		}

		//����
		sort(d.begin(), d.end());

		//ȥ����ߺ���ͷ�
		d.pop_back();
		d.pop_front();

		//ȡƽ����
		double sum = 0;
		for (deque<double>::iterator dit = d.begin(); dit != d.end(); dit++)
		{
			sum += *dit; //�ۼ�ÿ����ί�ķ���
		}

		double avg = sum / (double)d.size();

		//��ƽ���� ��ֵ��ѡ������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ� " << endl;
			for (auto mit = groupScore.begin(); mit != groupScore.end(); mit++)
			{
				cout << "��ţ� " << mit->second << "  ������ " << this->m_Speaker[mit->second].m_Name
					<< " �ɼ�" << this->m_Speaker[mit->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//ȡǰ����
			for (auto mit = groupScore.begin(); mit != groupScore.end()&& count<3; mit++, count++)
			{
				if (this->m_Index == 1)   //��һ�α�����ǰ���� ���浽 v2��
				{
					this->v2.push_back(mit->second);
				}
				else    
				{
					this->vVictory.push_back(mit->second);  //�ڶ��α�����ǰ�������浽 ��ʤ�� vVictory
				}
			}

			groupScore.clear();

			cout << endl;
		}
	}
	
	cout << "-----------------��" << this->m_Index << "�ֱ������------------" << endl;
}

//��ʾ�������
void SpeechManager::showScore()
{
	cout << "------------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£� -------------" << endl;
	
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
		cout << "��ţ� " << *it << "  ������ " << this->m_Speaker[*it].m_Name
			<< " �ɼ�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");

	this->show_menu();
}


//�����¼
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);  //д�ļ�
	
	//��ÿ���˵�����д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//�ر��ļ�
	ofs.close();

	cout << "��¼�Ѿ�����" << endl;
	
	this->fileIsEmpty = false;  //���ļ�Ϊ�ձ�־��Ϊfalse
}
//���Ʊ�������
void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1.��ǩ
	speechDraw();

	//2.����
	speechContest();
	
	//3.��ʾ�������
	showScore();

	this->m_Index++;

	//�ڶ��ֱ���
	//1.��ǩ
	speechDraw();

	//2.����
	speechContest();

	//3.��ʾ���ս��
	showScore();

	//4.�������
	saveRecord();

	//���ñ���
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "���������ϣ�" << endl;

	system("pause");
	system("cls");

}

//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open())
	{	
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�Ϊ��" << endl;
		ifs.close();
		return;
	}


	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch);

	string data;
	int index = 1;  //��������


	while (ifs >> data)
	{

		vector<string>v; //����ÿ���ַ���
		int pos = -1;
		int start = 0;  //��ʼλ��
		
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
		cout << it->first << " �ھ���ţ� " << it->second[0] << " ������ " << it->second[1] << endl;
	}*/  //����m_Record
}

//��ʾ����÷�
void SpeechManager::showRecord()
{	
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
		{
			cout << "��" << it->first << "��" <<
				"�ھ����: " << it->second[0] << " �÷֣� " << it->second[1] << " "
				"�Ǿ���ţ�" << it->second[2] << " �÷֣� " << it->second[3] << " "
				"������ţ�" << it->second[4] << " �÷֣� " << it->second[5] << " " << endl;
		}
	}
	

	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ�����?" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.ȡ��" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);  //����ڣ���ɾ�������´���
		ofs.close();

		this->initSpeech();

		this->createSpeaker();

		this->loadRecord();

		cout << "����ɹ�" << endl;
	}
	system("pause");
}

// ��ʼ����Ա����
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//��ʼ����������
	this->m_Index = 1;

	//����¼�е��������
	this->m_Record.clear();
}

//����ѡ��
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}
		 // 12��ѡ�ֱ��
		this->v1.push_back(i + 10001);
		
		//ѡ�ֱ�� �Լ���Ӧ��ѡ�� ��ŵ�map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
SpeechManager::~SpeechManager()
{

}