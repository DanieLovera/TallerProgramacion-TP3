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

		void sendCommand(const std::string &command) const;
		void sendSize(size_t size) const;
		void sendMsg(const std::string &msg) const;
		void sendPlay(const std::string &row, 
					  const std::string &column) const;
		uint8_t playToByte(const std::string &row, 
						   const std::string &column) const;
		ssize_t receiveSize(size_t &size) const;
		ssize_t receiveMsg(std::string &buffer, size_t &size) const;

	public:
		CommunicationProtocol(Socket &socket);
		CommunicationProtocol(CommunicationProtocol &&other);
		~CommunicationProtocol();

		void send(const std::string &command) const;
		void send(const std::string &command, 
				  const std::string &msg) const;
		void send(const std::string &command, 
			   	  const std::string &column,
				  const std::string &row) const;
		ssize_t receive(std::string &buffer) const;
};

#endif // _COMMUNICATION_PROTOCOL_H_
