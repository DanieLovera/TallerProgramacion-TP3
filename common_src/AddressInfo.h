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
       /*
        * brief Constructor con parametros.
        * @param gaierr: Codigo de error generado por getdddrinfo
        */            	
		explicit GetAddressInfoException(int gaierr) : gaierr(gaierr) { }

       /*
        * brief Mensaje de error.
        * @return Mensaje.
        */        
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

       /*
        * brief Crea un socket.
        * @param fileDescriptor: Devuelve el file descriptor
        * del socket.
        */        
		void createSocket(int &fileDescriptor) const;

       /*
        * brief Conecta un socket.
        * @param fileDescriptor: file descriptor del socket a 
        * conectar.
        */       		
		int connectSocket(const int &fileDescriptor) const;

	   /*
        * brief Enlaza un socket.
        * @param fileDescriptor: file descriptor del socket
        * a enlazar.
        */       	
		int bindSocket(int &fileDescriptor) const;

       /*
        * brief Crea y conecta un socket.
        * @param fileDescriptor: file descriptor del socket a 
        * crear y conectar.
        */       	
		int createAndConnectSocket(int &fileDescriptor) const;

	   /*
        * brief Crea y enlaza un socket.
        * @param fileDescriptor: file descriptor del socket a 
        * crear y enlazar.
        */      
		int createAndBindSocket(int &fileDescriptor) const;

	   /*
        * brief Cierra un socket.
        * @param fileDescriptor: file descriptor a liberar.
        */      		
		void closeSocket(int &fileDescriptor) const;

	public:
		/*
		 * brief Constructor con parametros.
		 * @param host: Dominio de la maquina que se busca.
		 * @para service: Puerto.
	     * @param aiFamily: AF_INET para conectarse a direcciones
         * IPv4 o AF_INET6 para conecciones IPv6
         * @param aiSocktype: Tipo de socket a utilizar 
         * SOCK_STREAM para conexiones TCP o SOCK_DGRAM para
         * conexiones UDP.
         * @param aiFlags: AI_PASSIVE para socket aceptador,
         * 0 para un socket de comunicacion.
		 */
		AddressInfo(const char *host, const char *service, 
					int aiFamily, int aiSocktype, int aiFlags);

		/*
		 * @brief Constructor de movimiento.
		 * @param other: Otra AddressInfo.
		 */
		AddressInfo(AddressInfo &&other);

		/*
		 * @brief Destructor.
		 */
		~AddressInfo();

		/*
		 * @brief Asignacion por movimiento.
	 	 * @param other: Otra AddressInfo.
		 */
		AddressInfo& operator=(AddressInfo &&other);

		/*
		 * @brief Conecta un socket.
	 	 * @param fileDescriptor: file descriptor del socket
	 	 * conectado.
		 */	
		void connect(int &fileDescriptor) const;

		/*
		 * @brief Enlaza un socket.
		 * @param fileDescriptor: fileDescriptor del socket
		 * enlazado.
		 */
		void bind(int &fileDescriptor) const;
};

#endif // _ADDRESS_INFO_H_
