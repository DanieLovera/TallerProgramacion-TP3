#ifndef _BOARD_EXCEPTION_H_
#define _BOARD_EXCEPTION_H_

#include <string.h>
#include <exception>

class BoardException : public std::exception {
    private:
        const char *msg;

    public:
        explicit BoardException(const char *msg);
        const char* what() const noexcept override;
};

#endif // _BOARD_EXCEPTION_H_
