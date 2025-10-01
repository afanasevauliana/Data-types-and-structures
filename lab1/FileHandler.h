#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>
#include "DoubleLinkedList.h"
#include "Exception.h"

class FileHandler {
private:
    std::string inputFile;
    std::string outputFile;
    std::string errorFile;
    
public:
    FileHandler(const std::string& in, const std::string& out, const std::string& err)
        : inputFile(in), outputFile(out), errorFile(err) {}
    
    DoubleLinkedList readInput();
    void writeOutput(const std::string& result);
    void writeError(const std::string& error);
};

DoubleLinkedList FileHandler::readInput() {
    DoubleLinkedList list;
    std::ifstream inFile(inputFile);
    
    if (!inFile.is_open()) {
        throw ListException("Не удалось открыть входной файл: " + inputFile);
    }
    
    int n;
    inFile >> n;
    
    if (n <= 0) {
        throw ListException("Количество элементов должно быть положительным!");
    }
    
    for (int i = 0; i < n; i++) {
        double value;
        if (!(inFile >> value)) {
            throw ListException("Ошибка чтения данных из файла!");
        }
        list.addToEnd(value);
    }
    
    inFile.close();
    return list;
}

void FileHandler::writeOutput(const std::string& result) {
    std::ofstream outFile(outputFile, std::ios::app);
    if (outFile.is_open()) {
        outFile << result << std::endl;
        outFile.close();
    }
}

void FileHandler::writeError(const std::string& error) {
    std::ofstream errFile(errorFile, std::ios::app);
    if (errFile.is_open()) {
        errFile << "ОШИБКА: " << error << std::endl;
        errFile.close();
    }
}

#endif