#include "../common_src/AddressInfo.h"
#include "../common_src/Socket.h"
#include "CommunicationProtocol.h"

#include <iostream>
#include <sstream>
#include <string>
#define WIN_MSG "Felicitaciones! Ganaste!"
#define LOST_MSG "Has perdido. Segui intentando!"
#define TIE_MSG "La partida ha terminado en empate"

int main(int argc, const char* argv[]) {
	try {
		if (argc != 3) return 1;
		Socket socket;
		socket.connect(argv[1], argv[2]);
		CommunicationProtocol communicationProtocol(socket);
		bool gameOver = false;

		while (!gameOver) {
			std::string userEntry;
			std::getline(std::cin, userEntry);

			std::istringstream iss(userEntry);
			std::string buffer;
			iss >> buffer;

			if (buffer.compare("crear") == 0) {
				iss >> buffer;
				communicationProtocol.send("0x6E", buffer);

			} else if (buffer.compare("listar") == 0) {
				communicationProtocol.send("0x6C");

			} else if (buffer.compare("unirse") == 0) {
				iss >> buffer;
				communicationProtocol.send("0x6A", buffer);

			} else if (buffer.compare("jugar") == 0) {
				std::string column;
				iss >> column;
				std::string row;
				iss >> row;
				communicationProtocol.send("0x70", column, row);

			} else {
				throw("Invalid command entry.");
			}
			communicationProtocol.receive(buffer);
			std::cout << buffer;
			gameOver = (buffer.find(WIN_MSG) != std::string::npos || 
						buffer.find(LOST_MSG) != std::string::npos ||
						buffer.find(TIE_MSG) != std::string::npos);
		}
		return 0;
	}

	catch(const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		return 1;
	}

	catch(...) {
		std::cerr << "Unknow error!";
		return 1;
	}
}
