#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

class ListException : public std::exception {
private:
    std::string message;
public:
    ListException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif