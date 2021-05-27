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
		void receiveSize(size_t &size) const;
		void receiveMsg(std::string &msg, size_t size) const;
		void byteToPlay(uint8_t compressedPlay,  
						std::string &column, 
						std::string &row) const;
		void sendSize(const size_t &size) const;
		void sendMsg(const std::string &msg) const;

	public:
		CommunicationProtocol(Socket &socket);
		CommunicationProtocol(CommunicationProtocol &&other);
		~CommunicationProtocol();

		void receiveCommand(std::string &command) const;
		void receive(std::string &msg) const;
		void receive(std::string &column,
					 std::string &row) const;
		void send(const std::string &buffer) const;
};

#endif // _COMMUNICATION_PROTOCOL_H_
