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
		void freeClients() const;

	public:
		Clients();
		Clients(Clients &&other);
		~Clients();
		Clients& operator=(Clients &&other);

		void add(Socket &&peer);
		void cleanDeadClients();
		void stopClients() const;
};

#endif // _CLIENTS_H_
