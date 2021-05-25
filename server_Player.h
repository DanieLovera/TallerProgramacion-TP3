#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player {
	private:
		char symbol;
		Player(const Player &player);
		Player& operator=(const Player &player);

	public:
		Player();
		Player(char symbol);
		Player(Player &&other);
		~Player();
		Player& operator=(Player &&other);
		char getSymbol() const;
};

#endif // _PLAYER_H_
