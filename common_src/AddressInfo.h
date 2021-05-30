#ifndef _ADDRESS_INFO_H_
#define _ADDRESS_INFO_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <exception>

class GetAddressInfoException : public std::exception {
    private:
    	int gaierr;

    public:
		explicit GetAddressInfoException(int gaierr) : gaierr(gaierr) { }

	    const char* what() const noexcept {
	       return gai_strerror(gaierr);
	    }
};

class Socket;

class AddressInfo {
	private:
		struct addrinfo *addrinfo;

		AddressInfo(const AddressInfo &other) = delete;
		AddressInfo& operator=(const AddressInfo &other) = delete;
		void createSocket(int &fileDescriptor) const;
		int connectSocket(int &fileDescriptor) const;
		int bindSocket(int &fileDescriptor) const;
		int createAndConnectSocket(int &fileDescriptor) const;
		int createAndBindSocket(int &fileDescriptor) const;
		void closeSocket(int &fileDescriptor) const;


	public:
		AddressInfo(const char *host, const char *service, 
					int aiFamily, int aiSocktype, int aiFlags);
		AddressInfo(AddressInfo &&other);
		~AddressInfo();
		AddressInfo& operator=(AddressInfo &&other);
		void connect(int &fileDescriptor) const;
		void bind(int &fileDescriptor) const;
};

#endif // _ADDRESS_INFO_H_
