#ifndef ROOM_H
#define ROOM_H
#include <string>
#include "Player.h"

class Room
{	
	private:
		// �ο� ��
		int userCnt;
		// ����
		struct User
		{
			std::string name;
		};
		// �����ڵ� [���Ǿ�,����,�ǻ�,�ù�]
		const std::string *JOBCODE;
		// ���� ��
		int jobCodeCnt;

		// ��������Ʈ
		User *userList;
		// �����ڵ帮��Ʈ
		std::string *jobCodeList;
		// �÷��̾� ����Ʈ
		Player *playerList;

		User addUser(std::string name);
		void suffleStringArr(std::string *arr, int size);
	public:
		Room();
		void setUserList();
		void setJobList();
		void setPlayerList();
		void showAllPlayerJobCode();

		void run();
		void setGame();
		void gameStart();
};
#endif
