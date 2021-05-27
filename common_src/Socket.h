#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "AddressInfo.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

class Socket {
    private:
	     int fileDescriptor;
       int aiFamily;
       int aiSocktype;
       int aiFlags;

       Socket(const Socket &other) = delete;
       Socket& operator=(const Socket &other) = delete;
       void bind(const AddressInfo &addressInfo);
       void listen(int backlog) const;

    public:
        Socket();
        Socket(int aiFlags);
        Socket(int aiFamily, int aiSocktype, int aiFlags);
        Socket(Socket &&other);
        ~Socket();
        Socket& operator=(Socket &&other);

        void connect(const char *host, const char *service);
        void bindAndListen(const char *host, const char *service);
        Socket accept() const;
        void send(const void *buffer, size_t length) const;
        ssize_t receive(void *buffer, size_t length) const;
        void close();
};

#endif // _SOCKET_H_
