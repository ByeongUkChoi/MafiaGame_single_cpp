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
	cout << "��ħ ��� �ð�" <<endl;
	cout << "��ǥ�� ���ؼ� ���͸� �����ּ���" <<endl;
	getch();
	system("cls");

	int votedCnt[playerCnt] = {0,};
	for(int i=0; i<playerCnt; i++)
	{
		cout << playerList[i].getName() << "���� ��ǥ" << endl;
		showVoteList();
		bool isVoteNum = false;
		int voteNum;
		do
		{
			cout << "��ǥ�� �÷��̾��� ��ȣ : ";
			voteNum = playerList[i].vote() - 1;
			if(voteNum < playerCnt && voteNum >= 0)
			{
				isVoteNum = true;
			}
			else
			{
				cout << "�߸��� ��ȣ �Դϴ�." << endl;
			}
		}while(!isVoteNum);
		votedCnt[voteNum]++;
		system("cls");
	}
	// �ִ� ��ǥ �� ã��
	int maxVotedCnt = 0;
	for(int i=0; i<playerCnt; i++)
	{
		maxVotedCnt = votedCnt[i] > maxVotedCnt ? votedCnt[i] : maxVotedCnt;
	}
	// �ִ� ��ǥ �÷��̾� ��ȣ ã��, ������ ��� ��ǥ ��ȿ
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
	cout << "���� �Ǿ����ϴ�." << endl << endl;
	cout << "���Ǿƴ� ���� �÷��̾" << endl << endl;
	cout << "������ �ǻ��� �÷��̾" <<endl << endl;
	cout << "�ǻ��� �츱 �÷��̾ �����մϴ�." <<endl << endl;
	cout << "�Ϲ� �ù��� �ƹ� �ϵ� �� �� ������ ��ǥ�� �����մϴ�." << endl << endl;
	cout << "���� ���ؼ� �ƹ� Ű�� �����ּ���" <<endl;
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
		cout << playerList[i].getName() << "�� �ƹ� Ű�� �����ּ���"<< endl;
		getch();
		string jobCode = playerList[i].getJobCode();
		cout << "����� " << jobCode << "�Դϴ�" << endl;
		showVoteList();
		if(jobCode == "MAFIA")
		{
			cout << "���� �÷��̾ �����ϼ���." << endl;
			killPlayerKey = playerList[i].vote() - 1;
		}
		else if(jobCode == "POLICE")
		{
			cout << "������ Ȯ���� �÷��̾ �����ϼ���." << endl;
			checkJobPlayerKey = playerList[i].vote() - 1;
			cout << "�÷��̾� : " << playerList[checkJobPlayerKey].getName() << endl;
			string jobCode = playerList[checkJobPlayerKey].getJobCode();
			if(jobCode != "MAFIA")
			{
				jobCode = "HUMAN";
			}
			cout << "���� : " << jobCode << endl;
		}
		else if(jobCode == "DOCTOR")
		{
			cout << "�츱 �÷��̾ �����ϼ���." << endl;
			savePlayerKey = playerList[i].vote() - 1;
		}
		else if(jobCode == "CITIZEN")
		{
			cout << "�ƹ� �÷��̾ �����ϼ���.(�ǽɹ�����)" << endl;
			playerList[i].vote();
			cout << "�ǽɹ����� ��ǥ" << endl;
			cout << "�ù��� ��ǥ�� �ƹ��� ����� �����ϴ�." << endl;
		}
		else
		{
			cout << "[ERROR] JOBCODE";
		}
		cout << "Ȯ�� �� �ƹ� Ű�� �����ּ���." << endl;
		getch();
	}
	system("cls");
	cout << "���� ������ ��ħ�� �Ǿ����ϴ�." << endl;
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
		cout << "��ǥ ��� �ƹ��ϵ� �߻����� �ʾҽ��ϴ�." << endl;
		cout << "��� ������ ���� �ƹ� Ű�� �����ּ���." << endl;
		getch();
	}
	else
	{
		cout << "����ڰ� �߻��Ͽ����ϴ�. " <<endl;
		cout << "����� : " << playerList[deadPlayerKey].getName() <<endl;
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
		cout << "���Ǿư� ��� �׾����ϴ�." << endl;
		cout << "�ΰ��� ���ӿ��� �¸��Ͽ����ϴ�." << endl;
		gameOver = false;
	}
	else if(humanCnt <= 1)
	{
		cout << "�ΰ��� 1�� ���ҽ��ϴ�." << endl;
		cout << "���Ǿư� ���ӿ��� �¸��Ͽ����ϴ�." << endl;
		gameOver = false;
	}
	if(!gameOver)
	{
		cout << "������ ���� �մϴ�." << endl;
	}
	cout << "��� ������ ���� �ƹ� Ű�� �����ּ���." << endl;
	getch();
}
void Game::play()
{
	cout << " ���� ���� ---- ";

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
