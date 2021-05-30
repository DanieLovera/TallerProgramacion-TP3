#ifndef _ERRNO_EXCEPTION_H_
#define _ERRNO_EXCEPTION_H_

#include <string.h>
#include <exception>

class ErrnoException : public std::exception {
    private:
        int _errno;

    public:
        explicit ErrnoException(int _errno);
        const char* what() const noexcept override;
};

#endif // _ERRNO_EXCEPTION_H_
