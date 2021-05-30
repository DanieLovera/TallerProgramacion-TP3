#ifndef _BOARD_H_
#define _BOARD_H_

#include <ostream>

class Board {
	private:
		static const char nought = 'O';
		static const char cross = 'X';
		static const char emptySymbol = ' ';
		char winner;
		static const int rows = 3;
		static const int columns = rows;
		char board[rows][columns];
		int tilesFilled;

		Board(const Board &other) = delete;
		Board& operator=(const Board &other) = delete;
		bool checkRows();
		bool checkColumns();
		bool checkDiagonal();
		bool checkAntiDiagonal();
		bool checkRow(int row);
		bool checkColumn(int column); 

	public: 
		Board();
		Board(Board &&other);
		~Board();
		Board& operator=(Board &&other);

		void insert(char symbol, int row, int column);
		friend std::ostream& operator<<(std::ostream &os, const Board &obj);
		char gameOver();
};

#endif // _BOARD_H_
