#include <iostream>
#include <string>
#include <conio.h>
#include "Player.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

Player::Player() {}
Player::Player(string name, string JOBCODE)
{
	this->name = name;
	this->JOBCODE = JOBCODE;
}

void Player::showPlayerJobCode()
{
	cout << "플레이어 : " << name << endl;
	cout << "아무 키를 입력하면 직업이 공개 됩니다." << endl;
	getch();
	cout << "직업 : " << JOBCODE << endl;
	cout << "직업을 확인 후 아무 키를 입력해 주세요" << endl;
	getch();
	system("cls");
}
int Player::vote()
{
	int key;
	cin >> key;
	return key;
}
string Player::getName()
{
	return name;
}
string Player::getJobCode()
{
	return JOBCODE;
}
