#include "ErrnoException.h"

ErrnoException::ErrnoException(int _errno) : _errno(_errno) { }

const char* ErrnoException::what() const noexcept {
    return strerror(_errno);
}
