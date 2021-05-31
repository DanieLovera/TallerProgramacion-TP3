#ifndef _ERRNO_EXCEPTION_H_
#define _ERRNO_EXCEPTION_H_

#include <string.h>
#include <exception>

class ErrnoException : public std::exception {
    private:
        int _errno;

    public:
       /*
        * brief Constructor con parametros.
        * @param _errno: error ocurrido, debe ser
        * un codigo de error valido devuelto por alguna
        * de las bibliotecas estandar de cpp.
        */        
        explicit ErrnoException(int _errno);

       /*
        * brief Mensaje que que describe el error.
        * @return Mensaje.
        */                
        const char* what() const noexcept override;
};

#endif // _ERRNO_EXCEPTION_H_
