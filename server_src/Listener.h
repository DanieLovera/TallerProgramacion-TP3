#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "../common_src/Socket.h"
#include "Thread.h"
#include <atomic>

class Listener : public Thread {
	private:
		Socket listener;
		bool isRunning;

		Listener(const Listener &other) = delete;
		Listener& operator=(const Listener &other) = delete;

		/*
		 * @brief Ejecuta y crea el nuevo thread.
		 */
		void run() override;

	public:
		/*
		 * Constructor con parametros.
		 * @param service: Puerto en el que se creara
		 * el hilo aceptador.
		 */
		explicit Listener(const char *service);

		/*
		 * Constructor con parametros.
		 * @param host: Dominio en donde escuchara el socket.
		 * @param service: Puerto en donde enlazara el socket.
		 */
		Listener(const char *host, 
				 const char *service);

		/*
		 * Constructor por movimiento.
		 * @param other: Otro objeto Listener.
		 */
		Listener(Listener &&other);

		/*
		 * Destructor.
		 */
		~Listener();

		/*
		 * Operador asignacion por movimiento.
		 * @param other: Otro objeto Listener.
		 * @return Devuelve el mismo objeto creado para permitir
		 * asignaciones en cascada.
		 */
		Listener& operator=(Listener &&other);

		/*
		 * Detiene el hilo aceptador.
		 */
		void stop();
};

#endif // _LISTENER_H_
