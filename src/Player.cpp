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
	cout << "�÷��̾� : " << name << endl;
	cout << "�ƹ� Ű�� �Է��ϸ� ������ ���� �˴ϴ�." << endl;
	getch();
	cout << "���� : " << JOBCODE << endl;
	cout << "������ Ȯ�� �� �ƹ� Ű�� �Է��� �ּ���" << endl;
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
