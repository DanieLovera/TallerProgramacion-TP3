#include "Listener.h"
#include "Clients.h"

#include <iostream>
#include <utility>
#define SERVER_FLAGS AI_PASSIVE

Listener::Listener(const char *service) 
	: Listener("localhost", service) { }

Listener::Listener(const char *host, 
				   const char *service) 
	: listener(AI_PASSIVE), isRunning(true) { 
	listener.bindAndListen(host, service);
}

Listener::Listener(Listener &&other) : listener(std::move(other.listener)), 
									   isRunning(other.isRunning) { }

Listener::~Listener() { }

Listener& Listener::operator=(Listener &&other) {
	if (this == &other) return *this;
	listener = std::move(other.listener);
	isRunning = other.isRunning;
	return *this;
}

void Listener::run() {
	Clients clients;

	while (isRunning) {
		try { 
			Socket peer = listener.accept();
			clients.add(std::move(peer));
			clients.cleanDeadClients();
		} catch(const std::exception &exception) {
			break;
		}
	}
	clients.stopClients();
}

void Listener::stop() {
	isRunning = false;
	listener.close();
}
