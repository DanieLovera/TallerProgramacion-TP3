#include "Player.h"
#include <iostream>

Player::Player() : Player('O') { }

Player::Player(char symbol) : symbol(symbol) { }

Player::Player(Player &&other) : symbol(other.symbol){ }

Player::~Player() { }

Player& Player::operator=(Player &&other) {
	if (this == &other) return *this;
	symbol = other.symbol;
	other.symbol = 'O';
	return *this;
}

void Player::setSymbol(char symbol) {
	this->symbol = symbol;
}

char Player::getSymbol() const {
	return symbol;
}
