#ifndef _THREAD_H_
#define _THREAD_H_

#include <thread>

class Thread {
	private:
		std::thread thread;
		Thread(const Thread &thread) = delete;
		Thread& operator=(const Thread &thread) = delete;

	public:
		/*
		 * @brief Constructor de la clase.
		 */
		Thread();

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		Thread(Thread &&other);

		/*
		 * @brief Destructor de la clase.
		 */
		virtual ~Thread();

		/*
		 * @brief Asignacion por moviento
		 * @param other: Objeto del cual se moveran los recursos.
		 * @returns Devuelve una referencia a si mismo.
		 */
		Thread& operator=(Thread &&other);

		/*
		 * @brief Inicia la ejecucion del thread.
		 */
		void start();

		/*
		 * @brief Sincroniza el thread principal con la finalizacion
		 * del nuevo spawneado.
		 */
		void join();

		/*
		 * @brief Operacion que se ejecutara concurrentemente en el thread.
		 */	
		virtual void run() = 0;
};

#endif //_THREAD_H_
