#include "Tateti.h"

/*Tateti::Tateti(std::string nameID) : board(), nameID(nameID), 
									 players{Player('O'), Player('X')}, 
									 currentPlayer(&players[playerO]) { }*/
Tateti::Tateti() : board(), 
				   players{Player('O'), Player('X')}, 
				   currentPlayer(&players[playerO]) { }

Tateti::Tateti(Tateti &&other) { }

Tateti::~Tateti() { }

Tateti& Tateti::operator=(Tateti &&other) {
	return *this;
}

void Tateti::insert(int row, int column) {
	char currentPlayerSymbol = currentPlayer->getSymbol();
	board.insert(currentPlayerSymbol,row, column);
	changeCurrentPlayer();
}

bool Tateti::gameOver() const {
	int status = board.gameOver();
	return status;
}

std::ostream& operator<<(std::ostream& os, const Tateti &obj) {
	os << obj.board;
	return os;
}

void Tateti::changeCurrentPlayer() {
	if (currentPlayer == &players[playerO]) {
		currentPlayer = &players[playerX];
	} else {
		currentPlayer = &players[playerO];
	}
}

