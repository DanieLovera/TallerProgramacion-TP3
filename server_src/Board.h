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

		/*
		 * @brief Revisa si hay 3 simbolos iguales en las filas.
		 * @return Devuelve verdadero si hay 3 en linea o falso
		 * en caso contrario.
		 */
		bool checkRows();

		/*
		 * @brief Revisa si hay 3 simbolos iguales en las columnas.
		 * @return Devuelve verdadero si hay 3 en linea o falso
		 * en caso contrario.
		 */
		bool checkColumns();

		/*
		 * @brief Revisa si hay 3 simbolos iguales en la diagonal.
		 * @return Devuelve verdadero si hay 3 en linea o falso
		 * en caso contrario.
		 */		
		bool checkDiagonal();

		/*
		 * @brief Revisa si hay 3 simbolos iguales en la antiDiagonal.
		 * @return Devuelve verdadero si hay 3 en linea o falso
		 * en caso contrario.
		 */		
		bool checkAntiDiagonal();

		/*
		 * @brief Revisa si hay 3 simbolos iguales en la fila.
		 * @param row: Fila que se revisara.
		 * @return Devuelve verdadero si hay 3 en linea o falso
		 * en caso contrario.
		 */		
		bool checkRow(int row);

		/*
		 * @brief Revisa si hay 3 simbolos iguales en la columna.
		 * @param row: Columna que se revisara.
		 * @return Devuelve verdadero si hay 3 en linea o falso
		 * en caso contrario.
		 */				
		bool checkColumn(int column); 

	public: 
		/*
		 * Constructor.
		 */
		Board();

		/*
		 * Constructor por movimiento.
		 * @param other: Otro objeto Board.
		 */
		Board(Board &&other);

		/*
		 * Destructor.
		 */
		~Board();

		/*
		 * Asignacion por Movimiento.
		 * @param other: Otro objeto Board. 
		 */
		Board& operator=(Board &&other);

		/*
		 * @brief Inserta una jugada en el tablero.
		 * @param symbol: Recibe un caracter con el symbolo
		 * que se va a insertar en el tablero.
		 * @param row: Recibe una fila con la posicion del
		 * tablero en que se jugara.
		 * @param colum: Recibe una columna con la posicion del 
		 * tableron en que se jugara.
		 */
		void insert(char symbol, int row, int column);

		/*
		 * @brief Operador de salida para Board.
		 * @param os: Ostream que guarda el tablero.
		 * @param obj: Objeto Board que se utiliza para el output del 
		 * programa.
		 */
		friend std::ostream& operator<<(std::ostream &os, const Board &obj);

		/*
		 * @brief Indica el fin de juego del tablero.
		 * @return Devuelve el symbolo del ganador en caso de victoria,
		 * 'p' en caso de que la partida se continue jugando o 't' en caso,
		 * de empate.
		 */
		char gameOver();
};

#endif // _BOARD_H_
