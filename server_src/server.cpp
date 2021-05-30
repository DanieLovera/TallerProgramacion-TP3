#include "../common_src/AddressInfo.h"
#include "../common_src/Socket.h"
#include "CommunicationProtocol.h"
#include "Tateti.h"
#include "Clients.h"
#include "Listener.h"
#include <iostream>

#include "Board.h"
#define CLOSE_SIGNAL 'q'

int main(int argc, const char* argv[]) {
	try {
		if (argc != 2) return 1;
		Listener listener(argv[1]);
		listener.start();

		char closeSignal;
		do {
			closeSignal = std::cin.get();
		} while (closeSignal != CLOSE_SIGNAL);

		listener.stop();
		listener.join();
		return 0;
	} catch(const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		return 1;
	} catch(...) {
		std::cerr << "Unknow error!";
		return 1;
	}
}
