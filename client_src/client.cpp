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


		while (true) {
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
				throw ("Invalid command entry.");
			}
			communicationProtocol.receive(buffer);
			std::cout << buffer << std::endl;
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
