#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "CommunicationProtocol.h"
#include "Thread.h"
#include <atomic>
class GamesMonitor;

class Client : public Thread {
	private:
		Socket peer;
		GamesMonitor &gamesMonitor;
		bool isRunning;

		Client(const Client &other) = delete;
		Client& operator=(const Client &other) = delete;
		Client& operator=(Client &&other) = delete;

		/*
		 * @brief Ejecuta y crea el nuevo thread.
		 */
		void run() override;

	public:
		/*
		 * @brief Constructor con parametros.
		 * @param peer: Peer del cliente, luego de esta operacion
		 * el peer es movido como miembro de Client.
		 * @param gamesMonitor: Coleccion que almacena la informacion
		 * sobre las partidas que se estan ejecutando.
		 */
		Client(Socket &&peer, GamesMonitor &gamesMonitor);

		/*
		 * @brief Constructor por movimiento.
		 * @param other: Otro objeto Client.
		 */
		Client(Client &&other);

		/*
		 * @brief Destructor.
		 */
		~Client();

		/*
		 * @brief Detiene la ejecucion del thread.
		 */
		void stop();

		/* 
		 * @brief Informa si el hilo dejo de ejecutarse.
		 * @return bool: Devuelve true si el hilo ya termino
		 * su trabajo o false en caso contrario.
		 */
		bool isDead() const;
};

#endif // _CLIENT_H_
