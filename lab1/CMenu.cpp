#include "./CMenu.h"
#include <iostream>
#include <limits>

CMenu::CMenu(string title, CMenuItem *items, size_t count) : title(title), items(items), count(count) {}

int CMenu::getSelect() const {
    return select;
}

bool CMenu::isRun() const {
    return running;
}

size_t CMenu::getCount() const {
    return count;
}

string CMenu::getTitle() {
    return title;
}

CMenuItem *CMenu::getItems() {
    return items;
}

void CMenu::print() {
    std::cout << "0. Exit" << std::endl;
    for (size_t i{}; i < count; ++i) {
        std::cout << i + 1 << ". ";
        items[i].print();
        std::cout << std::endl;
    }
}

int CMenu::runCommand() {
    print();
    
    while (true) {
        std::cout << "\n   Select >> ";
        if (!(std::cin >> select)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите число от 0 до " << count << "!" << std::endl;
            continue;
        }
        
        if (select == 0) {
            return 0;
        } else if (select > 0 && select <= count) {
            return items[select - 1].run();
        } else {
            std::cout << "Неверная команда. Введите число от 0 до " << count << "." << std::endl;
        }
    }
}