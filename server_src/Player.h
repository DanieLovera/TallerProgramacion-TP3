#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player {
	private:
		char symbol;
		Player(const Player &player);
		Player& operator=(const Player &player);

	public:
		Player();
		explicit Player(char symbol);
		Player(Player &&other);
		~Player();
		Player& operator=(Player &&other);
		void setSymbol(char symbol);
		char getSymbol() const;
};

#endif // _PLAYER_H_
