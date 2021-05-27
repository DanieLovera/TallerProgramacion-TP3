#include "../common_src/AddressInfo.h"
#include "../common_src/Socket.h"
#include "CommunicationProtocol.h"
#include "Tateti.h"
#include <iostream>

#include "Board.h"

#define SERVER_FLAGS AI_PASSIVE

int main(int argc, const char* argv[]) {
	try {
		Socket listener(SERVER_FLAGS);
		listener.bindAndListen("localhost", "7777");
		Socket peer = listener.accept();
		CommunicationProtocol communicationProtocol(peer);

		std::string command;
		communicationProtocol.receiveCommand(command);
		std::cout << command << std::endl;
		/*std::string row;
		std::string column;
		communicationProtocol.receive(column, row);
		std::cout << row << std::endl;
		std::cout << column << std::endl;*/

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
