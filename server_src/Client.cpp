#include "Client.h"
#include "Tateti.h"
#include "GamesMonitor.h"
#include <string>
#include <utility>

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

void Client::run() {
	CommunicationProtocol communicationProtocol(peer);
	Tateti tateti;
	Player player;
	std::string gameName;
	std::string buffer;

	while(keepTalking) {
		ssize_t receivedBytes = communicationProtocol.receiveCommand(buffer);
		if (receivedBytes == 0) {break;}

		if (buffer.compare("0x6E") == 0) {
			communicationProtocol.receive(buffer);
			if (gameName.empty()) {
				tateti.setPlayerOne(player);
				gameName = buffer;
				gamesMonitor.putIfAbsent(std::move(buffer), tateti);
				buffer = gamesMonitor[gameName].toString(player);
			}

		} else if (buffer.compare("0x6C") == 0) {
			buffer = gamesMonitor.toString();

		} else if (buffer.compare("0x6A") == 0) {
			communicationProtocol.receive(buffer);
			if (gameName.empty()) {
				gameName = buffer;
				gamesMonitor[gameName].setPlayerTwo(player);
				buffer = gamesMonitor[gameName].toString(player);
			}

		} else if (buffer.compare("0x70") == 0) {
			if (!gameName.empty()) {
				std::string column;
				std::string row;
				communicationProtocol.receive(column, row);
				gamesMonitor[gameName].insert(stoi(row), stoi(column), player);
				buffer = gamesMonitor[gameName].toString(player);
			}

		} else {
			throw("Invalid command entry.");
		}
		communicationProtocol.send(buffer);
	}
	//gamesMonitor.removeIfPresent(gameName);
	isRunning = false;
}

void Client::stop() {
	keepTalking = false;
}

bool Client::isDead() const {
	return !isRunning;
}
