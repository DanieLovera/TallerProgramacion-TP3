#include "Client.h"
#include "Tateti.h"
#include "GamesMonitor.h"
#include <iostream>
#include <sstream>

Client::Client(Socket &&peer, 
			   GamesMonitor &gamesMonitor) 
					: peer(std::move(peer)),
					  gamesMonitor(gamesMonitor),
					  keepTalking(true),
					  isRunning(true) { }

Client::Client(Client &&other) : peer(std::move(other.peer)),
								 gamesMonitor(other.gamesMonitor),
								 keepTalking(other.keepTalking),
								 isRunning(other.isRunning) { }

Client::~Client() { }

/*Client& Client::operator=(Client &&other) {
	if (this == &other) return *this;
	peer = std::move(other.peer);
	keepTalking = other.keepTalking;
	isRunning = other.isRunning;
	return *this;
}*/

void Client::run() {
	CommunicationProtocol communicationProtocol(peer);
	std::string gameName;


	std::string buffer;
	std::ostringstream oss;
	ssize_t receivedBytes = 0;
	while(keepTalking) {
		receivedBytes = communicationProtocol.receiveCommand(buffer);
		if (receivedBytes == 0) {break;}

		if (buffer.compare("0x6E") == 0) {
			communicationProtocol.receive(buffer);
			if (gameName.empty()) {
				Tateti tateti;
				gameName = buffer;
				gamesMonitor.putIfAbsent(std::move(buffer), std::move(tateti));
				oss << tateti;
				buffer = oss.str();
			}

		} else if (buffer.compare("0x6C") == 0) {
			buffer = gamesMonitor.toString();

		} else if (buffer.compare("0x6A") == 0) {
			communicationProtocol.receive(buffer);
			if (gameName.empty()) {
				gameName = buffer;
				oss << gamesMonitor[buffer];
				buffer = oss.str();
			}

		} else if (buffer.compare("0x70") == 0) {
			if (!gameName.empty()) {
				std::string column;
				std::string row;
				communicationProtocol.receive(column, row);
				gamesMonitor[gameName].insert(stoi(row), stoi(column));
				oss << gamesMonitor[gameName];
				buffer = oss.str();
			}

		} else {
			throw ("Invalid command entry.");
		}
		communicationProtocol.send(buffer);
	}
	isRunning = false;	
}

void Client::stop() {
	keepTalking = false;
}

bool Client::isDead() const {
	return !isRunning;
}
