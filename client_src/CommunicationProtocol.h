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

		/*
		 * @brief Envia un comando al servidor.
		 * @param command: Comando que se quiere enviar, debe
		 * tener un formato en hexadecimal con dos cifras 
		 * unicamente "0x00".
		 */
		void sendCommand(const std::string &command) const;
		
		/*
		 * @brief Envio el tamanio de un mensaje.
		 * @param size: tamanio del mensaje que se quiere enviar.
		 */
		void sendSize(size_t size) const;

		/*
		 * @brief Envia un mensaje.
		 * @param msg: Mensaje a enviar.
		 */		
		void sendMsg(const std::string &msg) const;

		/*
		 * @brief Envia una jugada al servidor.
		 * @param row: fila en la que se jugara debe
		 * ser menor a 4 y mayor a 0.
		 * @param column: columna en la que se jugara debe
		 * ser menor a 4 y mayor a 0.
		 */		
		void sendPlay(const std::string &row, 
					  const std::string &column) const;

		/*
		 * @brief Convierte una jugada (fila y columna) a un byte.
		 * @param row: fila en la que se jugara debe
		 * ser menor a 4 y mayor a 0.
		 * @param column: columna en la que se jugara debe
		 * ser menor a 4 y mayor a 0.
		 */		
		uint8_t playToByte(const std::string &row, 
						   const std::string &column) const;

		/*
		 * @brief Recibe un tamanio del servidor.
		 * @param size: Buffer para almacenar el size recibido.
		 */			
		ssize_t receiveSize(size_t &size) const;

		/*
		 * @brief Recibe un mensaje del servidor.
		 * @param buffer: Buffer para almacenar el mensaje recibido.
		 * @param size: Tamanio del mensaje que se recibira.
		 */			
		ssize_t receiveMsg(std::string &buffer, const size_t &size) const;

	public:
		/*
		 * @brief Constructor con parametros.
		 * @param socket: Socket involucrado en la comunicacion.
		 */
		explicit CommunicationProtocol(Socket &socket);

		/*
		 * @brief Constructor copia.
		 * @param other: Otro objeto CommunicationProtocol.
		 */
		CommunicationProtocol(CommunicationProtocol &&other);

	 	/*
		 * @brief Destructor.
		 */
		~CommunicationProtocol();

		/*
		 * @brief Envia un comando al servidor.
		 * @param command: Comando a enviar, debe tener el formato
		 * en hexadecimal de dos digitos "0x00"
		 */
		void send(const std::string &command) const;

		/*
		 * @brief Envia un comando y mensaje al servidor.
		 * @param command: Comando a enviar, debe tener el formato
		 * en hexadecimal de dos digitos "0x00"
		 * @param msg: Mensaje a enviar.
		 */	
		void send(const std::string &command, 
				  const std::string &msg) const;

		/*
		 * @brief Envia un comando, y una jugada al servidor.
		 * @param command: Comando a enviar, debe tener el formato
		 * en hexadecimal de dos digitos "0x00"
		 * @param row: fila en la que se jugara debe
		 * ser menor a 4 y mayor a 0.
		 * @param column: columna en la que se jugara debe
		 * ser menor a 4 y mayor a 0.
		 */			
		void send(const std::string &command, 
			   	  const std::string &column,
				  const std::string &row) const;

		/*
		 * @brief Recibe un mensaje del servidor
		 * @param buffer: Buffer en donde se almacena el mensaje
		 * recibido
		 * @return Devuelve un 0 si el servidor cierra el canal
		 * de comunicacion.
		 */				
		ssize_t receive(std::string &buffer) const;
};

#endif // _COMMUNICATION_PROTOCOL_H_
