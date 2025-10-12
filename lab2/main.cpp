#include "Menu.h"
#include "MenuItem.h"
#include "BinaryTree.h"
#include "TreeException.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
using namespace std;

BinaryTree tree;
string inputFile = "input.txt";
string outputFile = "output.txt";
string errorFile = "errors.txt";

void logError(const string& message) {
    ofstream err(errorFile, ios::app);
    err << "Ошибка: " << message << endl;
    err.close();
}

#pragma region Функции для меню

int insertNode() {
    try {
        cout << "Введите значение для добавления: ";
        int value;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw TreeException("Некорректный ввод числа");
        }
        
        tree.insert(value);
        cout << "Узел " << value << " успешно добавлен в дерево." << endl;
        
        return 1;
    }
    catch (const TreeException& e) {
        logError(e.what());
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int deleteNode() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 1;
        }
        
        cout << "Введите значение для удаления: ";
        int value;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw TreeException("Некорректный ввод числа");
        }
        
        TreeNode* found = tree.search(value);
        if (found) {
            tree.deleteNode(value);
            cout << "Узел " << value << " успешно удален." << endl;
        } else {
            cout << "Узел " << value << " не найден в дереве." << endl;
        }
        
        return 1;
    }
    catch (const TreeException& e) {
        logError(e.what());
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int searchNode() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 1;
        }
        
        cout << "Введите значение для поиска: ";
        int value;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw TreeException("Некорректный ввод числа");
        }
        
        TreeNode* found = tree.search(value);
        if (found) {
            cout << "Узел " << value << " найден в дереве." << endl;
        } else {
            cout << "Узел " << value << " не найден в дереве." << endl;
        }
        
        return 1;
    }
    catch (const TreeException& e) {
        logError(e.what());
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int findMinMax() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 1;
        }
        
        TreeNode* minNode = tree.findMin();
        TreeNode* maxNode = tree.findMax();
        
        cout << "Минимальный элемент: " << minNode->data << endl;
        cout << "Максимальный элемент: " << maxNode->data << endl;
        
        return 1;
    }
    catch (const TreeException& e) {
        logError(e.what());
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int printTree() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 1;
        }
        
        cout << "\n    ВИЗУАЛИЗАЦИЯ ДЕРЕВА" << endl;
        cout << tree.printTreeVisual();
        
        cout << "\n    ОБХОДЫ ДЕРЕВА" << endl;
        cout << "Инфиксная запись: " << tree.getInfixNotation() << endl;
        cout << "Префиксная запись: " << tree.getPrefixNotation() << endl;
        cout << "Постфиксная запись: " << tree.getPostfixNotation() << endl;
        
        cout << "\n    ИНФОРМАЦИЯ" << endl;
        cout << "Количество узлов: " << tree.countNodes() << endl;
        cout << "Высота дерева: " << tree.getHeight() << endl;
        
        return 1;
    }
    catch (const TreeException& e) {
        logError(e.what());
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int loadFromFile() {
    try {
        cout << "Введите имя файла для загрузки: ";
        string filename;
        cin >> filename;
        
        tree.loadFromFile(filename);
        cout << "Дерево успешно загружено из файла " << filename << endl;
        
        return 1;
    }
    catch (const TreeException& e) {
        logError(e.what());
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int saveToFile() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 1;
        }
        
        cout << "Введите имя файла для сохранения: ";
        string filename;
        cin >> filename;
        
        tree.saveToFile(filename);
        cout << "Дерево успешно сохранено в файл " << filename << endl;
        
        return 1;
    }
    catch (const TreeException& e) {
        logError(e.what());
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int clearTree() {
    try {
        tree.clear();
        cout << "Дерево успешно очищено." << endl;
        return 1;
    }
    catch (const TreeException& e) {
        logError(e.what());
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int processExpressionTree() {
    try {
        tree.buildExpressionTree();
        tree.saveToFile(outputFile);
        cout << "\n    ДЕРЕВО ВЫРАЖЕНИЯ ((6*3)+(8*7))*(6*5)" << endl;
        cout << tree.printTreeVisual();
        
        cout << "\n    ОБХОДЫ ДЕРЕВА ВЫРАЖЕНИЯ" << endl;
        cout << "Инфиксная запись: " << tree.getInfixNotation() << endl;
        cout << "Префиксная запись: " << tree.getPrefixNotation() << endl;
        cout << "Постфиксная запись: " << tree.getPostfixNotation() << endl;
        
        cout << "\nРезультаты сохранены в файл: " << outputFile << endl;
        
        return 1;
    }
    catch (const TreeException& e) {
        logError(e.what());
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

#pragma endregion

const int ITEMS_NUMBER = 9;

int main(int argc, char* argv[]) {
    system("chcp 65001 > nul");
    if (argc >= 4) {
        inputFile = argv[1];
        outputFile = argv[2];
        errorFile = argv[3];
        cout << "Используются файлы:\n";
        cout << "Входной: " << inputFile << "\n";
        cout << "Выходной: " << outputFile << "\n"; 
        cout << "Ошибок: " << errorFile << "\n\n";
    } else {
        cout << "Используются файлы по умолчанию:\n";
        cout << "Входной: " << inputFile << "\n";
        cout << "Выходной: " << outputFile << "\n";
        cout << "Ошибок: " << errorFile << "\n\n";
        }
    
    ofstream out(outputFile, ios::trunc);
    out.close();
    ofstream err(errorFile, ios::trunc);
    err.close();

    try {
        tree.loadFromFile(inputFile);
        cout << "Данные загружены из файла " << inputFile << endl;
    } 
    catch (const TreeException& e) {
        cout << "Не удалось загрузить данные из " << inputFile << " (файл не существует или пустой)" << endl;
    }
    
    CMenuItem items[ITEMS_NUMBER] {
        CMenuItem{"Добавить узел", insertNode},
        CMenuItem{"Удалить узел", deleteNode},
        CMenuItem{"Найти узел", searchNode},
        CMenuItem{"Найти min/max", findMinMax},
        CMenuItem{"Вывести дерево", printTree},
        CMenuItem{"Загрузить из файла", loadFromFile},
        CMenuItem{"Сохранить в файл", saveToFile},
        CMenuItem{"Очистить дерево", clearTree},
        CMenuItem{"Дерево выражения из моего варианта", processExpressionTree}
    };
    
    CMenu menu("Меню", items, ITEMS_NUMBER);
    while (menu.runCommand()) {};
    return 0;
}