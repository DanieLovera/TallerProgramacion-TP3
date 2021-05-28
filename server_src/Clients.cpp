#include "Clients.h"
#include "Client.h"

#include <iostream>

Clients::Clients() { }

Clients::Clients(Clients &&other) : clients(std::move(other.clients)) { }

Clients::~Clients() {
	freeClients();
}

Clients& Clients::operator=(Clients &&other) {
	if (this == &other) return *this;
	freeClients();
	clients = std::move(clients);
	return *this;
}

void Clients::add(Socket &&peer) {
	Client *client = new Client(std::move(peer));
	clients.push_back(client);
	client->start();
}

void Clients::cleanDeadClients() {
	std::list<Client*>::iterator it = clients.begin();
	while(it != clients.end()) {
		if ((*it)->isDead()) {
			(*it)->join();
			delete (*it);
			it = clients.erase(it);
		} else {
			it++;
		}
	}
}

void Clients::stopClients() const {
	for (Client *client : clients) {
		client->stop();
		client->join();
	}
}

void Clients::freeClients() const {
	for (Client *client : clients) {
		if (client != nullptr) {
			delete client;
		}
	}	
}
