#include <iostream>
#include <string>
#include <conio.h>
#include "Game.h"
#include "Player.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

Game::Game(){}
Game::Game(Player *playerList, int playerCnt)
{
	this->playerList = playerList;
	this->playerCnt = playerCnt;
}
void Game::dayVote()
{
	cout << "아침 토론 시간" <<endl;
	cout << "투표를 위해서 엔터를 눌러주세요" <<endl;
	getch();
	system("cls");

	int votedCnt[playerCnt] = {0,};
	for(int i=0; i<playerCnt; i++)
	{
		cout << playerList[i].getName() << "님의 투표" << endl;
		showVoteList();
		bool isVoteNum = false;
		int voteNum;
		do
		{
			cout << "투표할 플레이어의 번호 : ";
			voteNum = playerList[i].vote() - 1;
			if(voteNum < playerCnt && voteNum >= 0)
			{
				isVoteNum = true;
			}
			else
			{
				cout << "잘못된 번호 입니다." << endl;
			}
		}while(!isVoteNum);
		votedCnt[voteNum]++;
		system("cls");
	}
	// 최대 득표 수 찾기
	int maxVotedCnt = 0;
	for(int i=0; i<playerCnt; i++)
	{
		maxVotedCnt = votedCnt[i] > maxVotedCnt ? votedCnt[i] : maxVotedCnt;
	}
	// 최대 득표 플레이어 번호 찾기, 동점일 경우 투표 무효
	int maxVotedPlayerKey = -1;
	for(int i=0; i<playerCnt; i++)
	{
		if(votedCnt[i] == maxVotedCnt)
		{
			if(maxVotedPlayerKey == -1)
			{
				maxVotedPlayerKey = i;
			}
			else
			{
				maxVotedPlayerKey = -1;
				break;
			}
		}
	}
	showResultVote(maxVotedPlayerKey);
}
void Game::nightVote()
{
	system("cls");
	cout << "밤이 되었습니다." << endl << endl;
	cout << "마피아는 죽일 플레이어를" << endl << endl;
	cout << "경찰은 의삼할 플레이어를" <<endl << endl;
	cout << "의사은 살릴 플레이어를 선택합니다." <<endl << endl;
	cout << "일반 시민은 아무 일도 할 수 없지만 투표에 참여합니다." << endl << endl;
	cout << "진행 위해서 아무 키나 눌러주세요" <<endl;
	getch();

	int killPlayerKey = - 2;
	int savePlayerKey = - 3;
	int checkJobPlayerKey;

	//cout << playerCnt << endl;
	//cout << playerList[0].getName() << endl;
	//cout << "___" <<endl;

	//for(int i=0; i<playerCnt; i++)
	//{
	//	cout << playerList[i].getName() << endl;
	//}
	for(int i=0; i<playerCnt; i++)
	{
		system("cls");
		cout << playerList[i].getName() << "님 아무 키나 눌러주세요"<< endl;
		getch();
		string jobCode = playerList[i].getJobCode();
		cout << "당신은 " << jobCode << "입니다" << endl;
		showVoteList();
		if(jobCode == "MAFIA")
		{
			cout << "죽일 플레이어를 선택하세요." << endl;
			killPlayerKey = playerList[i].vote() - 1;
		}
		else if(jobCode == "POLICE")
		{
			cout << "직업을 확인할 플레이어를 선택하세요." << endl;
			checkJobPlayerKey = playerList[i].vote() - 1;
			cout << "플레이어 : " << playerList[checkJobPlayerKey].getName() << endl;
			string jobCode = playerList[checkJobPlayerKey].getJobCode();
			if(jobCode != "MAFIA")
			{
				jobCode = "HUMAN";
			}
			cout << "직업 : " << jobCode << endl;
		}
		else if(jobCode == "DOCTOR")
		{
			cout << "살릴 플레이어를 선택하세요." << endl;
			savePlayerKey = playerList[i].vote() - 1;
		}
		else if(jobCode == "CITIZEN")
		{
			cout << "아무 플레이어나 선택하세요.(의심방지용)" << endl;
			playerList[i].vote();
			cout << "의심방지용 투표" << endl;
			cout << "시민의 투표는 아무런 기능이 없습니다." << endl;
		}
		else
		{
			cout << "[ERROR] JOBCODE";
		}
		cout << "확인 후 아무 키나 눌러주세요." << endl;
		getch();
	}
	system("cls");
	cout << "밤이 지나고 아침이 되었습니다." << endl;
	int deadPlayerKey;
	if(killPlayerKey == savePlayerKey)
	{
		deadPlayerKey = -1;
	}
	else
	{
		deadPlayerKey = killPlayerKey;
	}
	showResultVote(deadPlayerKey);
}
void Game::showVoteList()
{
	string playerName;
	for(int i=0; i<playerCnt; i++)
	{
		cout << i+1 << ". " << playerList[i].getName() << endl;
	}
}
void Game::showResultVote(int deadPlayerKey)
{
	if(deadPlayerKey == -1)
	{
		cout << "투표 결과 아무일도 발생하지 않았습니다." << endl;
		cout << "계속 진행을 위해 아무 키나 눌러주세요." << endl;
		getch();
	}
	else
	{
		cout << "사망자가 발생하였습니다. " <<endl;
		cout << "사망자 : " << playerList[deadPlayerKey].getName() <<endl;
		removeDeadPlayer(deadPlayerKey);
	}
}
void Game::removeDeadPlayer(int deadPlayerKey)
{
	int newPlayerCnt = playerCnt - 1;
	//Player removedPlayerList[newPlayerCnt];
	Player *removedPlayerList;
	removedPlayerList = new Player[newPlayerCnt];
	for(int i=0,j=0; i<playerCnt; i++)
	{
		if(deadPlayerKey != i)
		{
			removedPlayerList[j++] = playerList[i];
		}
	}
	this->playerCnt = newPlayerCnt;
	this->playerList = removedPlayerList;

	checkGameOver();

}
void Game::checkGameOver()
{
	int mafiaCnt = 0;
	int humanCnt = 0;
	for(int i=0; i<playerCnt; i++)
	{
		if(playerList[i].getJobCode() == "MAFIA")
		{
			mafiaCnt++;
		}
		else
		{
			humanCnt++;
		}
	}
	if(mafiaCnt == 0)
	{
		cout << "마피아가 모두 죽었습니다." << endl;
		cout << "인간이 게임에서 승리하였습니다." << endl;
		gameOver = false;
	}
	else if(humanCnt <= 1)
	{
		cout << "인간이 1명 남았습니다." << endl;
		cout << "마피아가 게임에서 승리하였습니다." << endl;
		gameOver = false;
	}
	if(!gameOver)
	{
		cout << "게임을 종료 합니다." << endl;
	}
	cout << "계속 진행을 위해 아무 키나 눌러주세요." << endl;
	getch();
}
void Game::play()
{
	cout << " 게임 시작 ---- ";

	gameOver = true;
	while(gameOver)
	{
		dayVote();
		if(!gameOver)
		{
			break;
		}
		nightVote();
	}
}
