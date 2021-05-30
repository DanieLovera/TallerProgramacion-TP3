#include "CommunicationProtocol.h"
#include <cstring>
#include <cmath>
#include <string>
#include <utility>

#define CLIENT_SOCKET 0
#define CLIENT_CLOSED 0

CommunicationProtocol::CommunicationProtocol(Socket &socket) 
	: socket(socket) { }

CommunicationProtocol::CommunicationProtocol(CommunicationProtocol &&other)
	: socket(other.socket) { }

CommunicationProtocol::~CommunicationProtocol() { }

ssize_t CommunicationProtocol::receiveCommand(std::string &buffer) const {
	uint8_t _buffer = 0;
	char hexCommand[5];
	ssize_t receivedBytes = socket.receive((void*) &_buffer, sizeof(uint8_t));
	snprintf(hexCommand, sizeof(hexCommand),"0x%02X", _buffer);
	buffer = hexCommand;
	return receivedBytes;
}

ssize_t CommunicationProtocol::receive(std::string &msg) const {
	size_t size = 0;
	ssize_t receivedBytes = 0;
	receivedBytes = receiveSize(size);
	if (receivedBytes != CLIENT_CLOSED) {
		receivedBytes = receiveMsg(msg, size);
	}
	return receivedBytes;
}

ssize_t CommunicationProtocol::receive(std::string &column,
							  	 	std::string &row) const {
	uint8_t compressedPlay = 0;
	ssize_t receivedBytes = socket.receive((void*) &compressedPlay, 
							sizeof(uint8_t));
	byteToPlay(compressedPlay, column, row);
	return receivedBytes;
}

void CommunicationProtocol::send(const std::string &buffer) const {
	size_t size = buffer.length();
	sendSize(size);
	sendMsg(buffer);
}

ssize_t CommunicationProtocol::receiveSize(size_t &size) const {
	uint16_t _size = 0;
	ssize_t receivedBytes = socket.receive((void*) &_size, sizeof(uint16_t));
	_size = ntohs(_size);
	size = _size;
	return receivedBytes;
}

ssize_t CommunicationProtocol::receiveMsg(std::string &msg, size_t size) const {
	char *buffer = new char[size + 1];
	ssize_t receivedBytes = socket.receive((void *)buffer, size);
	buffer[size] = '\0';
	msg = buffer;
	delete [] buffer;
	return receivedBytes;
}

void CommunicationProtocol::byteToPlay(uint8_t compressedPlay,  
									   std::string &column, 
									   std::string &row) const {
	const int bits = 4;
	int rowMask = (pow(2,bits) - 1);
	int _column = (compressedPlay >> bits) + 1;
	int _row = (compressedPlay & rowMask) + 1;
	column = std::move(std::to_string(_column));
	row = std::move(std::to_string(_row));
}

void CommunicationProtocol::sendSize(const size_t &size) const {
	uint16_t _size = static_cast<uint16_t>(size);
	_size = htons(_size);
	socket.send((const void *) &_size, sizeof(_size));
}

void CommunicationProtocol::sendMsg(const std::string &msg) const {
	const char * _msg = msg.c_str();
	socket.send((const void *) _msg, strlen(_msg));
}
