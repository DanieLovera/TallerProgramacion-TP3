#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player {
	private:
		char symbol;
		Player(const Player &player) = delete;
		Player& operator=(const Player &player) = delete;

	public:
		/*
		 * @brief Constructor.
		 */
		Player();

		/*
		 * @brief Constructor con parametros
		 * @param symbol: Simbolo que usara el jugador.
		 */
		explicit Player(char symbol);

		/*
		 * @brief Constructor por movimiento.
		 * @param other: Otro objeto Player.
		 */
		Player(Player &&other);

		/*
		 * @brief Destructor.
		 */
		~Player();

		/*
		 * @brief Operador asignacion por movimiento.
		 * @param other: Otro objeto Player.
		 * @return Devuelve una referencia a si mismo.
		 */
		Player& operator=(Player &&other);

		/*
		 * @brief Asigna un simbolo al jugador.
		 * @param symbol: Caracter con el simbolo que usara
		 * el jugador.
		 */
		void setSymbol(char symbol);

		/*
		 * @brief Obtiene el simbolo del jugador.
		 * @return Devuelve el simbolo.
		 */
		char getSymbol() const;
};

#endif // _PLAYER_H_
