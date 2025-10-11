#include "./Menu.h"
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
    std::cout << "\n" << title << ":\n";
    for (size_t i{}; i < count; ++i) {
        std::cout << i + 1 << ". ";
        items[i].print();
        std::cout << std::endl;
    }
    std::cout << "0. Выход" << std::endl;
}

int CMenu::runCommand() {
    while (true) {
        print();
        std::cout << "\n   Выберите пункт >> ";
        if (!(std::cin >> select)) {
            std::cout << "Введите корректное число!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (select == 0) {
            std::cout << "Выход из программы...\n";
            return 0;
        }
        else if (select > 0 && select <= static_cast<int>(count)) {
            items[select - 1].run();
            continue;
        }
        else {
            std::cout << "Введите число от 0 до " << count << "!\n";
        }
    }
}