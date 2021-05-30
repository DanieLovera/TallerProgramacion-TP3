#include "Socket.h"
#include "AddressInfo.h"
#include "ErrnoException.h"
#include <cerrno>
#include <unistd.h>

#define CLIENT_SOCKET 0
#define MAX_PENDING_CONNECTIONS 10
#define UNVALID_SOCKET -1
#define ERROR -1

Socket::Socket() : Socket(CLIENT_SOCKET) { }

Socket::Socket(int aiFlags) : Socket(AF_INET, SOCK_STREAM, aiFlags) { }

Socket::Socket(int aiFamily, int aiSocktype, int aiFlags) 
	: fileDescriptor(UNVALID_SOCKET), 								
	  aiFamily(aiFamily), 
      aiSocktype(aiSocktype), 
	  aiFlags(aiFlags) { }
 
Socket::Socket(Socket &&other) : fileDescriptor(other.fileDescriptor), 
								 aiFamily(other.aiFamily), 
								 aiSocktype(other.aiSocktype), 
								 aiFlags(other.aiFlags) { 
	other.fileDescriptor = UNVALID_SOCKET;
	other.aiFamily = 0;
	other.aiSocktype = 0;
	other.aiFlags = 0;
}

Socket::~Socket() { 
	close();
}

Socket& Socket::operator=(Socket &&other) {
	if (this == &other) return *this;
	close();
	fileDescriptor = other.fileDescriptor;
	aiFamily = other.aiFamily;
	aiSocktype = other.aiSocktype;
	aiFlags = other.aiFlags;
	other.fileDescriptor = UNVALID_SOCKET;
	other.aiFamily = 0;
	other.aiSocktype = 0;
	other.aiFlags = 0;
	return *this;
}

void Socket::connect(const char *host, const char *service) {
	AddressInfo addressInfo(host, service, aiFamily, aiSocktype, aiFlags);
	addressInfo.connect(fileDescriptor);
}

void Socket::bindAndListen(const char *host, const char *service) {
	AddressInfo addressInfo(host, service, aiFamily, aiSocktype, aiFlags);
	bind(addressInfo);
	listen(MAX_PENDING_CONNECTIONS);
}

Socket Socket::accept() const {
	int fileDescriptor = ::accept(this->fileDescriptor, nullptr, nullptr);
	if (fileDescriptor == ERROR) {throw ErrnoException(errno);}
	Socket peer;
	peer.fileDescriptor = fileDescriptor;
	return peer;
}

void Socket::send(const void *buffer, size_t length) const {
	const char *currentBuffer = static_cast<const char*>(buffer);
	ssize_t sentBytes = 0;
	ssize_t sentBytesAux = 0;
	size_t remainingBytes = (length - sentBytes);

	while (remainingBytes > 0 && sentBytesAux != ERROR) {
		sentBytesAux = ::send(fileDescriptor, 
							  (currentBuffer + sentBytes), 
							  remainingBytes, 
							  MSG_NOSIGNAL);
		sentBytes += sentBytesAux;
		remainingBytes = (length - sentBytes);
	}
	if (sentBytesAux == ERROR) {throw ErrnoException(errno);}
}

ssize_t Socket::receive(void *buffer, size_t length) const {
	char *currentBuffer = static_cast<char*>(buffer);
	ssize_t receivedBytes = 0;
	ssize_t receivedBytesAux = 1;
	size_t remainingBytes = (length - receivedBytes);

	while (remainingBytes > 0 && 
		   (receivedBytesAux != ERROR && receivedBytesAux != 0)) {
		receivedBytesAux = recv(fileDescriptor, 
 							    (currentBuffer + receivedBytes), 
							  	remainingBytes, 
							  	MSG_NOSIGNAL);
		receivedBytes += receivedBytesAux;
		remainingBytes = (length - receivedBytes);
	}
	if (receivedBytesAux == ERROR) {throw ErrnoException(errno);}
	return receivedBytesAux;
}

void Socket::bind(const AddressInfo &addressInfo) {
	addressInfo.bind(fileDescriptor);
}

void Socket::listen(int backlog) const {
	int status = ::listen(fileDescriptor, backlog);
	if (status == ERROR) {throw ErrnoException(errno);}
}

void Socket::close() {
	if (fileDescriptor != UNVALID_SOCKET) {
		shutdown(fileDescriptor, SHUT_RDWR);
		::close(fileDescriptor);
		fileDescriptor = UNVALID_SOCKET;
	}
}
