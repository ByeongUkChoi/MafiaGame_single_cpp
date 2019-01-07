#ifndef GAME_H
#define GAME_H
#include <string>
#include "Player.h"

class Game 
{
	private:
		Player *playerList;
		int playerCnt;
		bool gameOver;

		void dayVote();
		void nightVote();

		void showVoteList();
		void showResultVote(int deadPlayerKey);
		void removeDeadPlayer(int deadPlayerKey);
		void checkGameOver();
	public:
		Game();
		Game(Player *playerList, int playerCnt);

		void play();

};
#endif
