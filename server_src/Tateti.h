#ifndef _TA_TE_TI_H_
#define _TA_TE_TI_H_

#include "Board.h"
#include "Player.h"
#include <string>
#include <ostream>

class Tateti {
	private:
		static const int totalPlayers = 2;
		static const int playerO = 0;
		static const int playerX = 1;
		Board board;
		//std::string nameID;
		Player players[totalPlayers];
		Player *currentPlayer;

		Tateti(const Tateti &other) = delete;
		Tateti& operator=(const Tateti &other) = delete;

		void changeCurrentPlayer();

	public:
		//Tateti(std::string nameID);
		Tateti();
		Tateti(Tateti &&other);
		~Tateti();
		Tateti& operator=(Tateti &&other);
		friend std::ostream& operator<<(std::ostream& os, const Tateti &obj);

		void insert(int row, int column);
		bool gameOver() const;
};

#endif // _TA_TE_TI_H_
