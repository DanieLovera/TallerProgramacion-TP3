#include "../common_src/AddressInfo.h"
#include "../common_src/Socket.h"
#include "CommunicationProtocol.h"

#include <iostream>
#include <sstream>
#include <string>

int main(int argc, const char* argv[]) {
	try {
		Socket socket;
		socket.connect("localhost", "7777");
		CommunicationProtocol communicationProtocol(socket);

		std::string userEntry;
		std::getline(std::cin, userEntry);

		std::istringstream iss(userEntry);
		std::string command;
		iss >> command;

		if (command.compare("crear") == 0) {
			std::string name;
			iss >> name;
			communicationProtocol.send("0x6E", name);

		} else if (command.compare("listar") == 0) {
			communicationProtocol.send("0x6C");

		} else if (command.compare("unirse") == 0) {
			std::string name;
			iss >> name;
			communicationProtocol.send("0x6A", name);

		} else if (command.compare("jugar") == 0) {
			std::string column;
			iss >> column;
			std::string row;
			iss >> row;
			communicationProtocol.send("0x70", column, row);

		} else {
			std::cout << "Cualquiera" << std::endl;
		}
		return 0;
	}

	catch (const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		return 1;
	}

	catch (...) {
		std::cerr << "Unknow error!";
		return 1;
	}
}
