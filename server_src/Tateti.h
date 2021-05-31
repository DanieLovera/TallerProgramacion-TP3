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

		/*
		 * @brief Cambia el jugador actual al siguiente.
		 */
		void changeCurrentPlayer();

	public:
		/*
		 * @brief Constructor.
		 */
		Tateti();

		/*
		 * @brief Destructor.
		 */
		~Tateti();

		/*
		 * @brief Inserta una jugada en el juego.
		 * @param row: Fila en la que se insertara la jugada
		 * debe ser menor a 4 y mayor a 0.
		 * @param column: Columna en la que se insertara la jugada
		 * debe ser menor a 4 y mayor a 0.
		 * @param player: Jugador que realiza la jugada.
		 */
		void insert(int row, int column, const Player &player);

		/*
		 * @brief Convierte la representacion de un tablero en string.
		 * @param player: Jugador que solicita el tablero.
		 */
		std::string toString(const Player &player);

		/*
		 * @brief Indica el fin de juego.
		 * @return Devuelve el symbolo del ganador en caso de victoria,
		 * 'p' en caso de que la partida se continue jugando o 't' en caso,
		 * de empate.
		 */
		char gameOver();

		/*
		 * @brief Asigna el jugador uno.
		 * @param player: Jugador que sera insertado en la partida
		 */
		void setPlayerOne(Player &player);

		/*
		 * @brief Asigna el jugador dos.
		 * @param player: Jugador que sera insertado en la partida
		 */
		void setPlayerTwo(Player &player);
};

#endif // _TA_TE_TI_H_
