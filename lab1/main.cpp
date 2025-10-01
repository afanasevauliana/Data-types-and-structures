#include <iostream>
#include <locale>
#include "CMenu.h"
#include "DoubleLinkedList.h"
#include "FileHandler.h"
#include "Exception.h"

DoubleLinkedList* currentList = nullptr;
FileHandler* currentFileHandler = nullptr;

int showList() {
    try {
        std::cout << "Содержимое списка: ";
        currentList->print();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        currentFileHandler->writeError(e.what());
    }
    return 1;
}

int calculateFormula() {
    try {
        double result = currentList->calculateVariant3();
        std::cout << "Результат вычисления (x1+xn)*(x2+xn-1)*...*(xn+x1): " << result << std::endl;
        currentFileHandler->writeOutput("Результат вычисления: " + std::to_string(result));
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        currentFileHandler->writeError(e.what());
    }
    return 1;
}

int checkEmpty() {
    std::cout << "Список " << (currentList->isEmpty() ? "пуст" : "не пуст") << std::endl;
    return 1;
}

int getSize() {
    std::cout << "Размер списка: " << currentList->getSize() << std::endl;
    return 1;
}

int exitProgram() {
    std::cout << "Выход из программы..." << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    #ifdef _WIN32
    system("chcp 65001");
    #endif
    setlocale(LC_ALL, "ru_RU.UTF-8");

    if (argc != 4) {
        std::cerr << "Использование: " << argv[0] << " input.txt output.txt errors.txt" << std::endl;
        return 1;
    }
    
    try {
        FileHandler fileHandler(argv[1], argv[2], argv[3]);
        DoubleLinkedList list = fileHandler.readInput();
        
        // устанавливаем текущие объекты
        currentList = &list;
        currentFileHandler = &fileHandler;
        
        std::cout << "Данные успешно загружены из файла!" << std::endl;
        
        CMenuItem items[] = {
            CMenuItem("Показать список", showList),
            CMenuItem("Вычислить формулу", calculateFormula),
            CMenuItem("Проверить пустоту", checkEmpty),
            CMenuItem("Получить размер", getSize)
        };
        
        CMenu menu("Главное меню", items, 4);
        
        int result;
        do {
            result = menu.runCommand();
        } while (result != 0);
         
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        std::ofstream errFile(argv[3]);
        if (errFile.is_open()) {
            errFile << "КРИТИЧЕСКАЯ ОШИБКА: " << e.what() << std::endl;
            errFile.close();
        }
        return 1;
    }
    
    return 0;
}