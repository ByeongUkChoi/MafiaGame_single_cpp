#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player
{
	private:
		std::string JOBCODE;
		std::string name;

	public:
		Player();
		Player(std::string name, std::string JOBCODE);

		void showPlayerJobCode();

		int vote();
		std::string getName();
		std::string getJobCode();
};
#endif
