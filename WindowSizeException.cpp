#include "WindowSizeException.h"

WindowSizeException::WindowSizeException(const std::string& mensaje) : mensaje_error(mensaje) {}

const char* WindowSizeException::what() const noexcept {
    return mensaje_error.c_str();
}
