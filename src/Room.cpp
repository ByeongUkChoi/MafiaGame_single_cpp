#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Room.h"
#include "Player.h"
#include "Game.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

Room::Room()
{
	jobCodeCnt = 4;
	JOBCODE =new string[jobCodeCnt]{"MAFIA","POLICE","DOCTOR","CITIZEN"};
	cout << "�� ���� Room::Room()"<<endl;
}
void Room::run()
{
	system("cls");
	int inputKey;
	bool isSetGame = false;
	while(inputKey != 3)
	{
		cout << "1.���Ӽ���, 2.���ӽ���, 3.���� : ";
		cin >> inputKey;
		switch(inputKey)
		{
			case 1:
				setGame();
				isSetGame = true;
			case 2:
				if(isSetGame)
				{
					gameStart();
				}
				else
				{
					cout << "���� ������ ���� ���ּ���." << endl;
				}
				break;
			case 3:
				break;
			default:
				cout << "��ȣ�� �ٽ� �Է��� �ּ���." << endl;
				break;
		}
	}
}
void Room::setGame()
{
	setUserList();
	setJobList();
}
void Room::gameStart()
{
	setPlayerList();
	showAllPlayerJobCode();

	Game game(playerList, userCnt);
	game.play();
}
void Room::setUserList()
{
	system("cls");
	// �ο� ����
	cout << "�ο� ���� �Է� �� �ּ��� : ";
	cin >> userCnt;
	userList = new User[userCnt];

	for(int i=0; i<userCnt; i++)
	{
		string name;
		cout << "�̸��� �Է��ϼ��� : ";
		cin >> name;
		userList[i] = Room::addUser(name);
	}
}
void Room::setJobList()
{
	system("cls");
	cout << "�� �ο� : " << userCnt << endl;
	jobCodeList = new string[userCnt];

	int totalJobCnt = 0;
	int jobCnt;
	int jobCodeListIndex = 0;
	for(int i=0; i<jobCodeCnt; i++)
	{
		cout << JOBCODE[i] << "�� �� : ";
		cin >> jobCnt;
		totalJobCnt += jobCnt;
		if(totalJobCnt > userCnt)
		{
			cout << "�Է°��� �߸� �Ǿ����ϴ�." << endl;
			totalJobCnt -= jobCnt;
			i--;
			continue;
		}

		for(int j=0; j<jobCnt; j++,jobCodeListIndex++)
		{
			jobCodeList[jobCodeListIndex] = JOBCODE[i];
		}
	}
}
void Room::setPlayerList()
{
	// �����ڵ帮��Ʈ �迭 ����
	suffleStringArr(jobCodeList, userCnt);
	// �÷��̾� ��ü ����
	playerList = new Player[userCnt];
	for(int i=0; i<userCnt; i++)
	{
		Player player(userList[i].name, jobCodeList[i]);
		playerList[i] = player;
	}
}
void Room::showAllPlayerJobCode()
{
	system("cls");
	for(int i=0; i<userCnt; i++)
	{
		playerList[i].showPlayerJobCode();
	}
}
void Room::suffleStringArr(string *arr, int size)
{
	srand((unsigned int)time(NULL));
	string temp;
	int randIndex;
	for(int i=0; i<size; i++)
	{
		randIndex = rand() % size;
		temp = jobCodeList[i];
		jobCodeList[i] = jobCodeList[randIndex];
		jobCodeList[randIndex] = temp;

	}
}
Room::User Room::addUser(string name)
{
	User user;
	user.name = name;
	return user;
}
