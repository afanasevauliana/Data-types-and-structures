#pragma once
#include <string>
#include <exception>

class TreeException : public std::exception {
private:
    std::string message;
    
public:
    TreeException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class FileException : public std::exception {
private:
    std::string message;
    
public:
    FileException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ExpressionException : public std::exception {
private:
    std::string message;
    
public:
    ExpressionException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};