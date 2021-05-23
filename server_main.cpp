#include "common_AddressInfo.h"
#include "common_Socket.h"
#include <iostream>

#define SERVER_FLAGS AI_PASSIVE

int main(int argc, const char* argv[]) {
	try {
		Socket listener(SERVER_FLAGS);
		listener.bindAndListen("localhost", "7777");
		Socket peer = listener.accept();
		char msg[5];
		peer.receive(msg, 5);
		printf("%s\n", msg);

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
	return 0;
}
