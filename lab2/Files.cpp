#include "Files.h"
#include "BinaryTree.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

Files::Files(const string& input, const string& output, const string& error) 
    : inputFilename(input), outputFilename(output), errorFilename(error) {}

string Files::readInput() const {
    ifstream file(inputFilename);
    if (!file.is_open()) {
        throw FileException("Не удалось открыть входной файл: " + inputFilename);
    }
    
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

string Files::readExpression() const { // метод читает выражение из файла или использует значение по умолчанию
    try {
        string expression = readInput();
        expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
        expression.erase(remove(expression.begin(), expression.end(), '\n'), expression.end());
        expression.erase(remove(expression.begin(), expression.end(), '\r'), expression.end());
        
        if (!expression.empty()) {
            return expression;
        }
    } catch (const FileException& e) {
        writeError(e.what());
    }
    return "((6*3)+(8*7)*(6*5))";
}

void Files::writeOutput(const string& data) const {
    ofstream file(outputFilename, ios::app);
    if (!file.is_open()) {
        throw FileException("Не удалось открыть выходной файл: " + outputFilename);
    }
    file << data << endl;
}

void Files::writeError(const string& error) const {
    ofstream file(errorFilename, ios::app);
    if (!file.is_open()) {
        throw FileException("Не удалось открыть файл ошибок: " + errorFilename);
    }
    file << "ОШИБКА: " << error << endl;
}

void Files::writeTreeOutput(const BinaryTree& tree) const {
    ofstream file(outputFilename, ios::app);
    if (!file.is_open()) {
        throw FileException("Не удалось открыть выходной файл: " + outputFilename);
    }
    
    file << "Бинарное дерево выражения:" << endl;
    
    auto prefix = tree.getPrefixNotation();
    auto infix = tree.getInfixNotation();
    auto postfix = tree.getPostfixNotation();
    
    file << "Префиксная запись (прямой обход): ";
    for (const auto& token : prefix) {
        file << token << " ";
    }
    file << endl;
    
    file << "Инфиксная запись (симметричный обход): ";
    for (const auto& token : infix) {
        file << token << " ";
    }
    file << endl;
    
    file << "Постфиксная запись (обратный обход): ";
    for (const auto& token : postfix) {
        file << token << " ";
    }
    file << endl << endl;
}

bool Files::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}