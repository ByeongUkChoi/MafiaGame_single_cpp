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
	cout << "방 생성 Room::Room()"<<endl;
}
void Room::run()
{
	system("cls");
	int inputKey;
	bool isSetGame = false;
	while(inputKey != 3)
	{
		cout << "1.게임설정, 2.게임시작, 3.종료 : ";
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
					cout << "게임 설정을 먼저 해주세요." << endl;
				}
				break;
			case 3:
				break;
			default:
				cout << "번호를 다시 입력해 주세요." << endl;
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
	// 인원 설정
	cout << "인원 수를 입력 해 주세요 : ";
	cin >> userCnt;
	userList = new User[userCnt];

	for(int i=0; i<userCnt; i++)
	{
		string name;
		cout << "이름을 입력하세요 : ";
		cin >> name;
		userList[i] = Room::addUser(name);
	}
}
void Room::setJobList()
{
	system("cls");
	cout << "총 인원 : " << userCnt << endl;
	jobCodeList = new string[userCnt];

	int totalJobCnt = 0;
	int jobCnt;
	int jobCodeListIndex = 0;
	for(int i=0; i<jobCodeCnt; i++)
	{
		cout << JOBCODE[i] << "의 수 : ";
		cin >> jobCnt;
		totalJobCnt += jobCnt;
		if(totalJobCnt > userCnt)
		{
			cout << "입력값이 잘못 되었습니다." << endl;
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
	// 직업코드리스트 배열 섞기
	suffleStringArr(jobCodeList, userCnt);
	// 플레이어 객체 생성
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
