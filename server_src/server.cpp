#include "../common_src/AddressInfo.h"
#include "../common_src/Socket.h"
#include "CommunicationProtocol.h"
#include "Tateti.h"
#include "Clients.h"
#include "Listener.h"
#include <iostream>

#include "Board.h"
#define CLOSED_SIGNAL 'q'

int main(int argc, const char* argv[]) {
	try {
		Listener listener("7777");
		listener.start();

		char closedSignal;
		do {
			closedSignal = std::cin.get();
		} while (closedSignal != CLOSED_SIGNAL);

		listener.stop();
		listener.join();
		return 0;
	} catch (const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "Unknow error!";
		return 1;
	}
}
