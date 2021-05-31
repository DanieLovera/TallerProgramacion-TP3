#include "AddressInfo.h"
#include "Socket.h"
#include "ErrnoException.h"
#include <cerrno>
#include <cstring> 
#include <unistd.h>

#define GET_ADDR_INFO_SUCCESS 0 
#define ERROR -1

AddressInfo::AddressInfo(const char *host, const char *service, 
						 int aiFamily, int aiSocktype, int aiFlags) : addrinfo(nullptr) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = aiFamily;
	hints.ai_socktype = aiSocktype;
	hints.ai_flags = aiFlags;
	int gaierr = getaddrinfo(host, service, &hints, &addrinfo);
	if (gaierr != GET_ADDR_INFO_SUCCESS) {throw GetAddressInfoException(gaierr);}
}

AddressInfo::AddressInfo(AddressInfo &&other) : addrinfo(other.addrinfo) { 
	other.addrinfo = nullptr;
}

AddressInfo::~AddressInfo() {
	if (addrinfo != nullptr) {
		freeaddrinfo(addrinfo);
	}
}

AddressInfo& AddressInfo::operator=(AddressInfo &&other) {
	if (this == &other) return *this;
	freeaddrinfo(addrinfo);
	addrinfo = other.addrinfo;
	other.addrinfo = nullptr;
	return *this;
}

void AddressInfo::connect(int &fileDescriptor) const {
	int status = ERROR;
	struct addrinfo *addrinfoAux = addrinfo;
	while (addrinfoAux != nullptr && status == ERROR) {
		status = createAndConnectSocket(fileDescriptor);
		addrinfoAux = addrinfoAux->ai_next;
	}
	if (status == ERROR) {throw ErrnoException(errno);}
}

void AddressInfo::bind(int &fileDescriptor) const {
	int status = ERROR;
	struct addrinfo *addrinfoAux = addrinfo;
	while (addrinfo != nullptr && status == ERROR) {
		status = createAndBindSocket(fileDescriptor);
		addrinfoAux = addrinfoAux->ai_next;
	}
	if (status == ERROR) {throw ErrnoException(errno);}
}

void AddressInfo::createSocket(int &fileDescriptor) const {
	fileDescriptor = socket(addrinfo->ai_family, 
							addrinfo->ai_socktype, 
							addrinfo->ai_protocol);
}

int AddressInfo::connectSocket(const int &fileDescriptor) const {
	int status = ::connect(fileDescriptor, addrinfo->ai_addr, 
						   addrinfo->ai_addrlen);
	return status;
}

int AddressInfo::bindSocket(int &fileDescriptor) const {
	int val = 1;
	int status = ERROR;
	setsockopt(fileDescriptor, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	status = ::bind(fileDescriptor, addrinfo->ai_addr, addrinfo->ai_addrlen);
	return status;
}

int AddressInfo::createAndConnectSocket(int &fileDescriptor) const {
	int status = ERROR;

	createSocket(fileDescriptor);
	status = connectSocket(fileDescriptor);
	if (status == ERROR) {
		closeSocket(fileDescriptor);
	}
	return status;
}

int AddressInfo::createAndBindSocket(int &fileDescriptor) const {
	int status = ERROR;

	createSocket(fileDescriptor);
	status = bindSocket(fileDescriptor);
	if (status == ERROR) {
		closeSocket(fileDescriptor);
	}
	return status;
}

void AddressInfo::closeSocket(int &fileDescriptor) const {
	close(fileDescriptor);
}
