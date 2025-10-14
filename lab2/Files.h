#pragma once
#include <string>
#include <vector>
#include "ExceptionHandler.h"

class BinaryTree;

class Files {
private:
    std::string inputFilename;
    std::string outputFilename;
    std::string errorFilename;

public:
    Files(const std::string& input, const std::string& output, const std::string& error);
    
    std::string readInput() const;
    std::string readExpression() const;
    void writeOutput(const std::string& data) const;
    void writeError(const std::string& error) const;
    void writeTreeOutput(const BinaryTree& tree) const;
    
    static bool fileExists(const std::string& filename);
};