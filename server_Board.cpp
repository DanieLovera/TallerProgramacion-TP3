#include "server_Board.h"
#include "server_BoardException.h"
#include <cstring>

#define EXIST_A_WINNER 1
#define PLAYING 0
#define TIE -1

Board::Board() : tilesFilled (0) { 
	memset(board, emptySymbol, rows * columns);
}

Board::Board(Board &&other) { 
	tilesFilled = other.tilesFilled;
	memcpy(board, other.board, sizeof(other.board));
	memset(other.board, emptySymbol, rows * columns);
	other.tilesFilled = 0;
}

Board::~Board() { }

Board& Board::operator=(Board &&other) {
	if (this == &other) return *this;
	tilesFilled = other.tilesFilled;
	memcpy(board, other.board, sizeof(other.board));
	memset(other.board, emptySymbol, rows * columns);
	other.tilesFilled = 0;
	return *this;
}

void Board::insert(char symbol, int row, int column) {
	if (symbol != nought && symbol != cross) {
		throw BoardException("Invalid entry, unexpected board symbol.");
	}
	if (row > Board::rows || column > Board::columns) {
		throw BoardException("Out of bound board insertion.");
	}
	char currentSymbol = board[row - 1][column - 1];
	if (currentSymbol != emptySymbol) {
		throw BoardException("Invalid entry, board tile taken.");
	}
	board[row - 1][column - 1] = symbol;
	tilesFilled++;
}

int Board::gameOver() const {
	bool existWinner = (checkRows() || checkColumns() ||
		    checkDiagonal() || checkAntiDiagonal());
	if (existWinner) {
		return EXIST_A_WINNER;
	} else if (!existWinner && tilesFilled < rows * columns) {
		return PLAYING;
	}
	return TIE;
}

bool Board::checkRows() const {
	bool win = false;
	int i = 0;
	while ((i < rows) && (win == false)) {
		win = checkRow(i);
		i++;
	}
	return win;
}

bool Board::checkColumns() const {
	bool win = false;
	int j = 0;
	while ((j < columns) && (win == false)) {
		win = checkColumn(j);
		j++;
	}
	return win;
}

bool Board::checkDiagonal() const {
	bool win = true;
	int i = 0;
	if (emptySymbol == board[i][i]) {win = false;}
	while ((i < rows - 1) && (win == true)) {
		win = (board[i][i] == board[i+1][i+1]);
		i++;
	}
	return win;
}

bool Board::checkAntiDiagonal() const {
	bool win = true;
	int j = 0;
	if (emptySymbol == board[rows-1][j]) {win = false;}
	while ((j < columns - 1) && (win == true)) {
		win = (board[(columns-1) - j][j] == board[(columns-2) - j][j+1]);
		j++;
	}
	return win;
}

bool Board::checkRow(int row) const {
	bool win = true;
	int j = 0;
	if (emptySymbol == board[row][j]) {win = false;}
	while ((j < columns - 1) && (win == true)) {
		win = (board[row][j] == board[row][j+1]);
		j++;
	}
	return win;
}

bool Board::checkColumn(int column) const {
	bool win = true;
	int i = 0;
	if (emptySymbol == board[i][column]) {win = false;}
	while ((i < rows - 1) && (win == true)) {
		win = (board[i][column] == board[i+1][column]);
		i++;
	}
	return win;
}

std::ostream& operator<<(std::ostream &os, const Board &obj) {
	os << "    1   2   3  \n";
	os << "  +---+---+---+\n";
	os << "1 | " << obj.board[0][0] << " | " << obj.board[0][1] << " | " << obj.board[0][2] << " |\n";
	os << "  +---+---+---+\n";
	os << "2 | " << obj.board[1][0] << " | " << obj.board[1][1] << " | " << obj.board[1][2] << " |\n";
	os << "  +---+---+---+\n";
	os << "3 | " << obj.board[2][0] << " | " << obj.board[2][1] << " | " << obj.board[2][2] << " |\n";
	os << "  +---+---+---+\n";
	return os;
}
