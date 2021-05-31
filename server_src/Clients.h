#ifndef _CLIENTS_H_
#define _CLIENTS_H_

#include "../common_src/Socket.h"
#include "GamesMonitor.h"
#include <list>
class Client;

class Clients {
	private:
		std::list<Client*> clients;
		GamesMonitor gamesMonitor;

		Clients(const Clients &other);
		Clients& operator=(const Clients &other);

		/*
		 * @brief Libera los clientes de la lista.
		 */
		void freeClients() const;

	public:
		/*
		 * @brief Constructor.
		 */
		Clients();

		/*
		 * @brief Constructor por movimiento.
		 * @param other: Otro objeto Clients.
		 */
		Clients(Clients &&other);

		/*
		 * @brief Destructor.
		 */
		~Clients();

		/*
		 * @brief Asignacion por movimiento.
		 * @param other: Otro objeto Clients.
		 * @param Clients: Se devuelve a si mismo
		 * para poder ejecutar el operador en cascada.
		 */
		Clients& operator=(Clients &&other);

		/*
		 * @brief Agrega un nuevo cliente a la lista.
		 * @param peer: recibe el peer del cliente a agregar. Esta
		 * operacion mueve el objeto Peer como miembro de la clase.
		 */
		void add(Socket &&peer);

		/*
		 * @brief Libera a los clientes que dejaron de ejecutarse.
		 */
		void cleanDeadClients();

		/*
		 * @brief Detiene ordenadamente a los clientes que controla.
		 */
		void stopClients() const;
};

#endif // _CLIENTS_H_
