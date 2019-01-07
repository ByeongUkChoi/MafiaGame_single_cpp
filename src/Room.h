#ifndef ROOM_H
#define ROOM_H
#include <string>
#include "Player.h"

class Room
{	
	private:
		// 인원 수
		int userCnt;
		// 유저
		struct User
		{
			std::string name;
		};
		// 직업코드 [마피아,경찰,의사,시민]
		const std::string *JOBCODE;
		// 직업 수
		int jobCodeCnt;

		// 유저리스트
		User *userList;
		// 직업코드리스트
		std::string *jobCodeList;
		// 플레이어 리스트
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
