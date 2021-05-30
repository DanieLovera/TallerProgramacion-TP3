#include "CommunicationProtocol.h"
#include <cstring>
#include <string>

#define CLIENT_SOCKET 0
#define SERVER_CLOSED 0

CommunicationProtocol::CommunicationProtocol(Socket &socket) 
	: socket(socket) { }

CommunicationProtocol::CommunicationProtocol(CommunicationProtocol &&other)
	: socket(other.socket) { }

CommunicationProtocol::~CommunicationProtocol() {}

void CommunicationProtocol::send(const std::string &command) const {
	sendCommand(command);
}

void CommunicationProtocol::send(const std::string &command, 
								 const std::string &msg) const {
	sendCommand(command);
	sendSize(msg.length());
	sendMsg(msg);
}

void CommunicationProtocol::send(const std::string &command, 
								 const std::string &column,
							  	 const std::string &row) const {
	sendCommand(command);
	sendPlay(row, column);
}

ssize_t CommunicationProtocol::receive(std::string &buffer) const {
	size_t size = 0;
	ssize_t receivedBytes = receiveSize(size);
	if (receivedBytes != SERVER_CLOSED) {
		receivedBytes =	receiveMsg(buffer, size);
	}
	return receivedBytes;
}

void CommunicationProtocol::sendCommand(const std::string &command) const {
	uint8_t _command = static_cast<uint8_t>(std::stoi(command, nullptr, 16));
	socket.send((const void*) &_command, sizeof(uint8_t));
}

void CommunicationProtocol::sendSize(size_t size) const {
	uint16_t _size = static_cast<uint16_t>(size);
	_size = htons(_size);
	socket.send((const void*) &_size, sizeof(uint16_t));
}

void CommunicationProtocol::sendMsg(const std::string &msg) const {
	const char *_msg = msg.c_str();
	socket.send((const void*) _msg, ::strlen(_msg)); 
}

void CommunicationProtocol::sendPlay(const std::string &row, 
									 const std::string &column) const {
	uint8_t play = playToByte(row, column);
	socket.send((const void*) &play, sizeof(uint8_t));
}

uint8_t CommunicationProtocol::playToByte(const std::string &row, 
										  const std::string &column) const {
	int _row = (std::stoi(row) - 1);
	int _column = (std::stoi(column) - 1);
	_column = (_column << 4);
	return (_row | _column);
}

ssize_t CommunicationProtocol::receiveSize(size_t &size) const {
	uint16_t _size = 0;
	ssize_t receivedBytes = socket.receive((void *) &_size, sizeof(_size));
	_size = ntohs(_size);
	size = _size;
	return receivedBytes;
}

ssize_t CommunicationProtocol::receiveMsg(std::string &buffer, 
										  const size_t &size) const {
	char *_buffer = new char[size + 1];
	ssize_t receivedBytes = socket.receive((void *) _buffer, size);
	_buffer[size] = '\0';
	buffer = _buffer;
	delete [] _buffer;
	return receivedBytes;
}
