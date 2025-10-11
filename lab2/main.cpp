#include "Menu.h"
#include "MenuItem.h"
#include "BinaryTree.h"
#include <cmath>
#include <limits>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

BinaryTree tree;

#pragma region Функции для меню

int insertNode() {
    try {
        cout << "Введите значение для добавления: ";
        int value;
        cin >> value;
        
        tree.insert(value);
        cout << "Узел " << value << " успешно добавлен в дерево." << endl;
        
        return 1;
    }
    catch (const exception& e) {
        ofstream errorFile("errors.txt", ios::app);
        errorFile << "Ошибка при добавлении узла: " << e.what() << endl;
        errorFile.close();
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int deleteNode() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 0;
        }
        
        cout << "Введите значение для удаления: ";
        int value;
        cin >> value;
        
        TreeNode* found = tree.search(value);
        if (found) {
            tree.deleteNode(value);
            cout << "Узел " << value << " успешно удален." << endl;
        } else {
            cout << "Узел " << value << " не найден в дереве." << endl;
        }
        
        return 1;
    }
    catch (const exception& e) {
        ofstream errorFile("errors.txt", ios::app);
        errorFile << "Ошибка при удалении узла: " << e.what() << endl;
        errorFile.close();
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int searchNode() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 0;
        }
        
        cout << "Введите значение для поиска: ";
        int value;
        cin >> value;
        
        TreeNode* found = tree.search(value);
        if (found) {
            cout << "Узел " << value << " найден в дереве." << endl;
        } else {
            cout << "Узел " << value << " не найден в дереве." << endl;
        }
        
        return 1;
    }
    catch (const exception& e) {
        ofstream errorFile("errors.txt", ios::app);
        errorFile << "Ошибка при поиске узла: " << e.what() << endl;
        errorFile.close();
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int findMinMax() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 0;
        }
        
        TreeNode* minNode = tree.findMin();
        TreeNode* maxNode = tree.findMax();
        
        cout << "Минимальный элемент: " << minNode->data << endl;
        cout << "Максимальный элемент: " << maxNode->data << endl;
        
        return 1;
    }
    catch (const exception& e) {
        ofstream errorFile("errors.txt", ios::app);
        errorFile << "Ошибка при поиске min/max: " << e.what() << endl;
        errorFile.close();
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int printTree() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 0;
        }
        
        cout << "\n   ВИЗУАЛИЗАЦИЯ ДЕРЕВА\n";
        cout << tree.printTreeVisual();
        
        cout << "\n    ОБХОДЫ ДЕРЕВА\n";
        cout << "Инфиксная запись: " << tree.getInfixNotation() << endl;
        cout << "Префиксная запись: " << tree.getPrefixNotation() << endl;
        cout << "Постфиксная запись: " << tree.getPostfixNotation() << endl;
        
        cout << "\n    ИНФОРМАЦИЯ\n";
        cout << "Количество узлов: " << tree.countNodes() << endl;
        cout << "Высота дерева: " << tree.getHeight() << endl;
        
        return 1;
    }
    catch (const exception& e) {
        ofstream errorFile("errors.txt", ios::app);
        errorFile << "Ошибка при выводе дерева: " << e.what() << endl;
        errorFile.close();
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
    catch (const exception& e) {
        ofstream errorFile("errors.txt", ios::app);
        errorFile << "Ошибка при загрузке из файла: " << e.what() << endl;
        errorFile.close();
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int saveToFile() {
    try {
        if (tree.isEmpty()) {
            cout << "Дерево пусто!" << endl;
            return 0;
        }
        
        cout << "Введите имя файла для сохранения: ";
        string filename;
        cin >> filename;
        
        tree.saveToFile(filename);
        cout << "Дерево успешно сохранено в файл " << filename << endl;
        
        return 1;
    }
    catch (const exception& e) {
        ofstream errorFile("errors.txt", ios::app);
        errorFile << "Ошибка при сохранении в файл: " << e.what() << endl;
        errorFile.close();
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
    catch (const exception& e) {
        ofstream errorFile("errors.txt", ios::app);
        errorFile << "Ошибка при очистке дерева: " << e.what() << endl;
        errorFile.close();
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

int processExpressionTree() {
    try {
        BinaryTree exprTree;
        exprTree.insert(20); // корень - умножение
        exprTree.insert(10); // левое поддерево - сложение
        exprTree.insert(30); // правое поддерево - умножение
        exprTree.insert(5);  // 6*3
        exprTree.insert(15); // 8*7  
        exprTree.insert(25); // 6
        exprTree.insert(35); // 5
        
        cout << "\n    ДЕРЕВО ВЫРАЖЕНИЯ ((6*3)+(8*7))*(6*5) ===\n";
        cout << exprTree.printTreeVisual();
        cout << "\n    ОБХОДЫ ДЕРЕВА ВЫРАЖЕНИЯ\n";
        cout << "Инфиксная запись: " << exprTree.getInfixNotation() << endl;
        cout << "Префиксная запись: " << exprTree.getPrefixNotation() << endl;
        cout << "Постфиксная запись: " << exprTree.getPostfixNotation() << endl;
        exprTree.saveToFile("expression_output.txt");
        cout << "\nРезультаты сохранены в файл 'expression_output.txt'" << endl;
        return 1;
    }
    catch (const exception& e) {
        ofstream errorFile("errors.txt", ios::app);
        errorFile << "Ошибка при обработке дерева выражений: " << e.what() << endl;
        errorFile.close();
        cout << "Ошибка: " << e.what() << endl;
        return 0;
    }
}

#pragma endregion
const int ITEMS_NUMBER = 9;

int main() {
    system("chcp 65001 > nul");
    CMenuItem items[ITEMS_NUMBER] {
        CMenuItem{"Добавить узел", insertNode},
        CMenuItem{"Удалить узел", deleteNode},
        CMenuItem{"Найти узел", searchNode},
        CMenuItem{"Найти min/max", findMinMax},
        CMenuItem{"Вывести дерево", printTree},
        CMenuItem{"Загрузить из файла", loadFromFile},
        CMenuItem{"Сохранить в файл", saveToFile},
        CMenuItem{"Очистить дерево", clearTree},
        CMenuItem{"Дерево выражения", processExpressionTree}
    };
    CMenu menu("Меню:", items, ITEMS_NUMBER);
    while (menu.runCommand()) {};
    return 0;
}