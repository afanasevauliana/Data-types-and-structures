#include "Menu.h"
#include "MenuItem.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Expression.h"
#include "Files.h"
#include "ExceptionHandler.h"
#include <iostream>
#include <windows.h>
#include <sstream>

using namespace std;

BinaryTree* expressionTree = nullptr;
BinarySearchTree* bst = nullptr;
Files* fileManager = nullptr;

int individualTask();
int insertNode();
int removeNode();
int printBST();
int searchNode();
int findMinimum();
int findMaximum();
int clearBST();
int loadBSTFromFile();

int loadBSTFromFile() {
    try {
        if (!bst) {
            bst = new BinarySearchTree();
        }
        
        string content = fileManager->readInput();
        if (!content.empty()) {
            istringstream iss(content);
            int number;
            int count = 0;
            
            while (iss >> number) {
                bst->insert(number);
                count++;
            }
            
            if (count > 0) {
                cout << "ДДП загружено из файла. Загружено " << count << " чисел." << endl;
                bst->print();
            } else {
                cout << "Файл input.txt пустой или содержит не числа." << endl;
                cout << "Добавьте числа в формате: 10 5 15 3 7 12 20" << endl;
            }
        } else {
            cout << "Файл input.txt пустой." << endl;
        }
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка загрузки ДДП: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

int individualTask() {
    try {
        cout << "Индивидуальное задание:" << endl;
        cout << "Бинарное дерево выражения ((6*3)+(8*7)*(6*5))" << endl;
        
        if (expressionTree) delete expressionTree;
        expressionTree = new BinaryTree();
        expressionTree->buildFromExpression("((6*3)+(8*7)*(6*5))");
        
        cout << "Дерево выражения:" << endl;
        expressionTree->print();
        
        auto prefix = expressionTree->getPrefixNotation();
        auto infix = expressionTree->getInfixNotation();
        auto postfix = expressionTree->getPostfixNotation();
        
        cout << "Префиксная запись: ";
        for (const auto& token : prefix) cout << token << " ";
        cout << endl;
        
        cout << "Инфиксная запись: ";
        for (const auto& token : infix) cout << token << " ";
        cout << endl;
        
        cout << "Постфиксная запись: ";
        for (const auto& token : postfix) cout << token << " ";
        cout << endl;
        
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

int insertNode() {
    try {
        if (!bst) {
            cout << "ДДП не загружено. Сначала выполните пункт 1." << endl;
            return 1;
        }
        
        int value;
        cout << "Введите значение для добавления: ";
        cin >> value;
        
        bst->insert(value);
        cout << "Вершина " << value << " добавлена в дерево" << endl;
        
        fileManager->writeOutput("Добавлена вершина: " + to_string(value));
        
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

int removeNode() {
    try {
        if (!bst) {
            cout << "ДДП не загружено. Сначала выполните пункт 1." << endl;
            return 1;
        }
        
        int value;
        cout << "Введите значение для удаления: ";
        cin >> value;
        
        if (bst->search(value)) {
            bst->remove(value);
            cout << "Вершина " << value << " удалена из дерева" << endl;
            fileManager->writeOutput("Удалена вершина: " + to_string(value));
        } else {
            cout << "Вершина " << value << " не найдена в дереве" << endl;
        }
        
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

int printBST() {
    try {
        if (bst) {
            bst->print();
            fileManager->writeOutput("Вывод текущего ДДП:");
        } else {
            cout << "ДДП не загружено. Сначала выполните пункт 1." << endl;
        }
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

int searchNode() {
    try {
        if (!bst) {
            cout << "ДДП не загружено. Сначала выполните пункт 1." << endl;
            return 1;
        }
        
        int value;
        cout << "Введите значение для поиска: ";
        cin >> value;
        
        if (bst->search(value)) {
            cout << "Вершина " << value << " найдена в дереве" << endl;
        } else {
            cout << "Вершина " << value << " не найдена в дереве" << endl;
        }
        
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

int findMinimum() {
    try {
        if (!bst) {
            cout << "ДДП не загружено. Сначала выполните пункт 1." << endl;
            return 1;
        }
        
        int minVal = bst->findMin();
        cout << "Минимальное значение в дереве: " << minVal << endl;
        
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

int findMaximum() {
    try {
        if (!bst) {
            cout << "ДДП не загружено. Сначала выполните пункт 1." << endl;
            return 1;
        }
        
        int maxVal = bst->findMax();
        cout << "Максимальное значение в дереве: " << maxVal << endl;
        
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

int clearBST() {
    try {
        if (bst) {
            bst->clear();
            cout << "Дерево очищено" << endl;
        } else {
            cout << "Дерево не создано!" << endl;
        }
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    try {
        string inputFile = "input.txt";
        string outputFile = "output.txt";
        string errorFile = "errors.txt";
        
        if (argc >= 4) {
            inputFile = argv[1];
            outputFile = argv[2];
            errorFile = argv[3];
        }
        
        fileManager = new Files(inputFile, outputFile, errorFile);
        
        bst = new BinarySearchTree();
        loadBSTFromFile();
        cout << endl;
        
        const int ITEMS_NUMBER = 8;
        CMenuItem items[ITEMS_NUMBER] {
            CMenuItem{"Перезагрузить ДДП из файла", loadBSTFromFile},
            CMenuItem{"Индивидуальное задание", individualTask},
            CMenuItem{"Добавление вершины в ДДП", insertNode},
            CMenuItem{"Удаление вершины из ДДП", removeNode},
            CMenuItem{"Вывод (печать) дерева", printBST},
            CMenuItem{"Поиск вершины в дереве", searchNode},
            CMenuItem{"Поиск минимума в ДДП", findMinimum},
            CMenuItem{"Поиск максимума в ДДП", findMaximum}
        };
        
        CMenu menu("Управление бинарными деревьями", items, ITEMS_NUMBER);
        
        cout << "Файлы:" << endl;
        cout << "Входной: " << inputFile << " (числа для ДДП)" << endl;
        cout << "Выходной: " << outputFile << endl;
        cout << "Ошибок: " << errorFile << endl << endl;
        
        int result;
        do {
            result = menu.runCommand();
        } while (result != 0);
        
        if (expressionTree) delete expressionTree;
        if (bst) delete bst;
        if (fileManager) delete fileManager;
        
        return 0;
    }
    catch (const exception& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
        return -1;
    }
}