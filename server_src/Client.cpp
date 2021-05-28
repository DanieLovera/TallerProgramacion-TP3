#include "Client.h"
#include <iostream>

Client::Client(Socket &&peer) : peer(std::move(peer)),
								keepTalking(true),
								isRunning(true) { }

Client::Client(Client &&other) : peer(std::move(other.peer)),
								 keepTalking(other.keepTalking),
								 isRunning(other.isRunning) { }

Client::~Client() { }

Client& Client::operator=(Client &&other) {
	if (this == &other) return *this;
	peer = std::move(other.peer);
	keepTalking = other.keepTalking;
	isRunning = other.isRunning;
	return *this;
}

void Client::run() {
	CommunicationProtocol communicationProtocol(peer);

	std::string command;
	ssize_t receivedBytes = 0;
	while(keepTalking) {
		receivedBytes = communicationProtocol.receiveCommand(command);
		if (receivedBytes == 0) {break;}

		// ZONA DE TRABAJO DEL TATETI
		communicationProtocol.send(command);
	}
	isRunning = false;	
}

void Client::stop() {
	keepTalking = false;
}

bool Client::isDead() const {
	return !isRunning;
}
