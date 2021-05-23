#include "common_AddressInfo.h"
#include "common_Socket.h"
#include <iostream>

int main(int argc, const char* argv[]) {
	try {
		Socket socket;
		socket.connect("localhost", "7777");
		const char *buffer = "hola";
		socket.send(buffer, 5);

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
