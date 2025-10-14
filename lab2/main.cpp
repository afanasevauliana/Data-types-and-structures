#include "Menu.h"
#include "MenuItem.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Expression.h"
#include "Files.h"
#include "ExceptionHandler.h"
#include <iostream>
#include <windows.h>

using namespace std;

// Глобальные переменные для меню
BinaryTree* expressionTree = nullptr;
BinarySearchTree* bst = nullptr;
Files* fileManager = nullptr;

// 1. Индивидуальное задание
int individualTask() {
    try {
        cout << "=== Индивидуальное задание ===" << endl;
        cout << "Построить бинарное дерево выражения ((6*3)+(8*7)*(6*5))" << endl;
        cout << "и вывести обходы: префиксный, инфиксный, постфиксный" << endl;
        
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

// 2. Добавление вершины в ДДП
int insertNode() {
    try {
        if (!bst) {
            bst = new BinarySearchTree();
        }
        
        int value;
        cout << "Введите значение для добавления: ";
        cin >> value;
        
        bst->insert(value);
        cout << "Вершина " << value << " добавлена в дерево" << endl;
        
        return 1;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        if (fileManager) fileManager->writeError(e.what());
        return -1;
    }
}

// 3. Удаление вершины из ДДП
int removeNode() {
    try {
        if (!bst) {
            cout << "Дерево не создано!" << endl;
            return 1;
        }
        
        int value;
        cout << "Введите значение для удаления: ";
        cin >> value;
        
        if (bst->search(value)) {
            bst->remove(value);
            cout << "Вершина " << value << " удалена из дерева" << endl;
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

// 4. Вывод (печать) дерева
int printBST() {
    try {
        if (bst) {
            bst->print();
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

// 5. Поиск вершины в дереве
int searchNode() {
    try {
        if (!bst) {
            cout << "Дерево не создано!" << endl;
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

// 6. Поиск минимума в ДДП
int findMinimum() {
    try {
        if (!bst) {
            cout << "Дерево не создано!" << endl;
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

// 7. Поиск максимума в ДДП
int findMaximum() {
    try {
        if (!bst) {
            cout << "Дерево не создано!" << endl;
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

// 8. Удаление дерева
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
        // Обработка аргументов командной строки
        string inputFile = "input.txt";
        string outputFile = "output.txt";
        string errorFile = "errors.txt";
        
        if (argc >= 4) {
            inputFile = argv[1];
            outputFile = argv[2];
            errorFile = argv[3];
        }
        
        fileManager = new Files(inputFile, outputFile, errorFile);
        
        // Создание пунктов меню согласно заданию
        const int ITEMS_NUMBER = 8;
        CMenuItem items[ITEMS_NUMBER] {
            CMenuItem{"Индивидуальное задание", individualTask},
            CMenuItem{"Добавление вершины в ДДП", insertNode},
            CMenuItem{"Удаление вершины из ДДП", removeNode},
            CMenuItem{"Вывод (печать) дерева", printBST},
            CMenuItem{"Поиск вершины в дереве", searchNode},
            CMenuItem{"Поиск минимума в ДДП", findMinimum},
            CMenuItem{"Поиск максимума в ДДП", findMaximum},
            CMenuItem{"Удаление дерева", clearBST}
        };
        
        CMenu menu("Управление бинарными деревьями", items, ITEMS_NUMBER);
        
        cout << "Файлы:" << endl;
        cout << "Входной: " << inputFile << endl;
        cout << "Выходной: " << outputFile << endl;
        cout << "Ошибок: " << errorFile << endl << endl;
        
        int result;
        do {
            result = menu.runCommand();
        } while (result != 0);
        
        // Очистка
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