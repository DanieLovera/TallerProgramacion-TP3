#ifndef _TA_TE_TI_H_
#define _TA_TE_TI_H_

#include "Board.h"
#include "Player.h"
#include <string>
#include <mutex>
#include <condition_variable>

class Tateti {
	private:
		static const int totalPlayers = 2;
		static const int playerO = 0;
		static const int playerX = 1;
		Board board;
		Player *players[totalPlayers];
		Player *currentPlayer;
		std::mutex mutex;
		std::condition_variable cv;
		bool isGameOver;
		char result;
		int playsMade;

		Tateti(const Tateti &other) = delete;
		Tateti& operator=(const Tateti &other) = delete;
		Tateti(Tateti &&other) = delete;
		Tateti& operator=(Tateti &&other) = delete;
		void changeCurrentPlayer();

	public:
		Tateti();
		~Tateti();

		void insert(int row, int column, const Player &player);
		std::string toString(const Player &player);
		char gameOver();
		void setPlayerOne(Player &player);
		void setPlayerTwo(Player &player);
};

#endif // _TA_TE_TI_H_
