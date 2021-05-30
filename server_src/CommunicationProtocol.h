#ifndef _COMMUNICATION_PROTOCOL_H_
#define _COMMUNICATION_PROTOCOL_H_

#include "../common_src/Socket.h"
#include <string>

class CommunicationProtocol {
	private:
		Socket &socket;

		CommunicationProtocol(const CommunicationProtocol &other) = delete;
		CommunicationProtocol& operator=(const CommunicationProtocol &other) = delete;
		CommunicationProtocol& operator=(CommunicationProtocol &&other) = delete;
		ssize_t receiveSize(size_t &size) const;
		ssize_t receiveMsg(std::string &msg, size_t size) const;
		void byteToPlay(uint8_t compressedPlay,  
						std::string &column, 
						std::string &row) const;
		void sendSize(const size_t &size) const;
		void sendMsg(const std::string &msg) const;

	public:
		explicit CommunicationProtocol(Socket &socket);
		CommunicationProtocol(CommunicationProtocol &&other);
		~CommunicationProtocol();

		ssize_t receiveCommand(std::string &command) const;
		ssize_t receive(std::string &msg) const;
		ssize_t receive(std::string &column,
					 	std::string &row) const;
		void send(const std::string &buffer) const;
};

#endif // _COMMUNICATION_PROTOCOL_H_
