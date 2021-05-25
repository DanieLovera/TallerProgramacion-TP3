#include "server_BoardException.h"

BoardException::BoardException(const char *msg) : msg(msg) { }

const char* BoardException::what() const noexcept {
    return msg;
}