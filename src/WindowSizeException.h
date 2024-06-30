#ifndef WINDOW_SIZE_EXCEPTION_H
#define WINDOW_SIZE_EXCEPTION_H

#include <exception>
#include <string>

class WindowSizeException : public std::exception {
private:
    std::string mensaje_error;
public:
    WindowSizeException(const std::string& mensaje);

    const char* what() const noexcept override;
};

#endif // WINDOW_SIZE_EXCEPTION_H
