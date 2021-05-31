#ifndef _BOARD_EXCEPTION_H_
#define _BOARD_EXCEPTION_H_

#include <string.h>
#include <exception>

class BoardException : public std::exception {
    private:
        const char *msg;

    public:
    	/*
    	 * @brief Constructor con parametros
    	 * @param msg: Mensaje que describe la 
    	 * excepcion.
    	 */
        explicit BoardException(const char *msg);

        /*
         * @brief Muestra el mensaje que describe la excepcion.
         * @return Devuelve el Mensaje.
         */
        const char* what() const noexcept override;
};

#endif // _BOARD_EXCEPTION_H_
