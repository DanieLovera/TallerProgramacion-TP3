#ifndef _GAMES_MONITOR_H_
#define _GAMES_MONITOR_H_

#include <map>
#include <mutex>
#include <string>

class Tateti;

class GamesMonitor {
	private:
		std::map<std::string, Tateti*> games;
		std::mutex mutex;

		GamesMonitor(const GamesMonitor &other) = delete;
		GamesMonitor(GamesMonitor &&other) = delete;
		GamesMonitor& operator=(const GamesMonitor &other) = delete;
		GamesMonitor& operator=(GamesMonitor &&other) = delete;

	public:
		/*
		 * @brief Constructor.
		 */
		GamesMonitor();

		/*
		 * @brief Destructor.
		 */
		~GamesMonitor();

		/*
		 * @brief Agrega un tateti a la coleccion, con clave
		 * key.
		 * @param key: Entrada para mapear la partida de tateti. Esta
		 * es movida como objeto miembro.
		 * @param tateti: Recibe una referencia a un tateti para
		 * almacenar su direccion de memoria en ea coleccion.
		 */
		void putIfAbsent(std::string &&key, Tateti &tateti);

		/*
		 * @brief Obtiene un tateti usando la clave key.
		 * @param key: Llave que mapea al objeto buscado.
		 * @return Devuelve una partida de tateti.
		 */
		Tateti& operator[](const std::string &key);

		/*
		 * @brief Lista las claves almacenadas en la coleccion.
		 * @return Devuelve un string con un formato de lista que
		 * representa las llaves.
		 */ 
		std::string toString();
};

#endif // _GAMES_MONITOR_H_
