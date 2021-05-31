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

       /*
        * brief Enlaza un socket a una direccion fisica del
        * servidor.
        * @param addressInfo: Clase wrapper que contiene la
        * informacion de la direccion.
        */ 
       void bind(const AddressInfo &addressInfo);

       /*
        * brief Coloca un socket a escuchar conexiones entrantes.
        * @param backlog: cantidad de conexiones maxima en espera
        * que puede encolar el socket sin aceptar.
        */        
       void listen(int backlog) const;

    public:
        /*
         * brief Constructor sin parametros.
         */
        Socket();

        /*
         * brief Constructor con parametros.
         * @param aiFlags: AI_PASSIVE para socket aceptador,
         * 0 para un socket de comunicacion.
         */
        explicit Socket(int aiFlags);

        /*
         * brief Constructor con parametros.
         * @param aiFamily: AF_INET para conectarse a direcciones
         * IPv4 o AF_INET6 para conecciones IPv6
         * @param aiSocktype: Tipo de socket a utilizar 
         * SOCK_STREAM para conexiones TCP o SOCK_DGRAM para
         * conexiones UDP.
         * @param aiFlags: AI_PASSIVE para socket aceptador,
         * 0 para un socket de comunicacion.
         */
        Socket(int aiFamily, int aiSocktype, int aiFlags);

        /*
         * brief Constructor copia.
         * @param other: Otro objeto socket.
         */
        Socket(Socket &&other);

        /*
         * brief Destructor.
         */
        ~Socket();

        /*
         * brief Asignacion por movimiento
         * @param other: Otro objeto socket.
         */
        Socket& operator=(Socket &&other);

        /*
         * brief Establece conexion con el servidor.
         * @param host: Direccion del servidor.
         * @param service: Puerto al que se quiere conectar.
         */
        void connect(const char *host, const char *service);

        /*
         * brief Coloca un socket creado con aiFlags AI_PASSIVE
         * a escuchar conexiones entrantes en el servidor.
         * @param host: Direccion del servidor.
         * @param service: Puerto al que se quiere enlazar.
         */        
        void bindAndListen(const char *host, const char *service);

        /*
         * brief Aepta un cliente al servidor.
         * @return Socket: Devuelve un socket que puede comunicarse
         * con el cliente.
         */ 
        Socket accept() const;

        /*
         * brief Envia un mensaje a traves del socket. La comunicacion
         * es en bytes.
         * @param buffer: Mensaje que se quiere enviar.
         * @param length: Tamanio del mensaje que se quiere enviar
         * (sizeof(buffer))
         */ 
        void send(const void *buffer, size_t length) const;

        /*
         * brief Recibe un mensaje a traves del socket. La comunicacion
         * es en bytes.
         * @param buffer: Buffer para retornar el mensaje que recibe el
         * socket. 
         * @param length: Tamanio del mensaje que se quiere recibir
         * (sizeof(buffer))
         * @return Devuelve 0 si alguno de los dos extremos de la conexion
         * se cerro.
         */ 
        ssize_t receive(void *buffer, size_t length) const;

        /*
         * brief Libera los recursos del socket, realiza un shutdown y
         * un close.
         */ 
        void close();
};

#endif // _SOCKET_H_
