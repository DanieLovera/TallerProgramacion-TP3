#include "Tateti.h"
#include <string> 
#include <sstream>

Tateti::Tateti() : board(), 
				   players{nullptr, nullptr},
				   currentPlayer(nullptr),
				   isGameOver(false),
				   result('p'),
				   playsMade(0) { }

Tateti::~Tateti() { }

char Tateti::gameOver() {
	char status = board.gameOver();
	return status;
}

void Tateti::insert(int row, int column, const Player &player) {
	std::lock_guard<std::mutex> lock(mutex);
	if (&player == currentPlayer) {
		char currentPlayerSymbol = currentPlayer->getSymbol();
		board.insert(currentPlayerSymbol, row, column);
		changeCurrentPlayer();
		char status = gameOver();
		if (status == 'X' || status == 'O' || status == 't') {
			result = status;
			isGameOver = true;
		}
		cv.notify_all();
	}
}

std::string Tateti::toString(const Player &player) {
	std::unique_lock<std::mutex> lock(mutex);
	while(&player != currentPlayer) {
		if (isGameOver == true) {break;}
		cv.wait(lock);
	}
	std::ostringstream oss;
	oss << board;
	if (result == player.getSymbol()) {
		oss << "Felicitaciones! Ganaste!\n";
	} else if (result == 't') {
		oss << "La partida ha terminado en empate\n";
	} else if (result != 'p') {
		oss << "Has perdido. Segui intentando!\n";
	}
	return oss.str();
}

void Tateti::setPlayerOne(Player &player) {
	player.setSymbol('O');
	players[playerO] = &player;
	currentPlayer = &player;
}

void Tateti::setPlayerTwo(Player &player) {
	player.setSymbol('X');
	players[playerX] = &player;
	if(playsMade > 0) currentPlayer = &player;
}

void Tateti::changeCurrentPlayer() {
	if (currentPlayer == players[playerO]) {
		currentPlayer = players[playerX];
	} else {
		currentPlayer = players[playerO];
	}
	playsMade++;
}
