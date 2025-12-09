#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

// Функция для вывода матрицы в обычном виде на основе профильного хранения
void printMatrixFromProfile(int UD[], int UN[], int IU[], int JU[], int n) {
    cout << "Матрица в обычном представлении:" << endl;
    
    for (int i = 0; i < n; i++) {
        // Вычисляем начало и конец профиля для строки i
        int start = IU[i] - 1;  // IU индексируется с 1 в описании
        int end = IU[i + 1] - 2;  // -2 потому что последний элемент строки - диагональный
        
        // Для каждого столбца j
        for (int j = 0; j < n; j++) {
            if (i == j) {
                // Диагональный элемент
                cout << setw(4) << UD[i];
            } else {
                // Ищем элемент в профиле
                bool found = false;
                for (int k = start; k <= end && !found; k++) {
                    if (JU[k] - 1 == j) {  // JU индексируется с 1
                        cout << setw(4) << UN[k];
                        found = true;
                    }
                }
                if (!found) {
                    cout << setw(4) << "0";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Функция перестановки двух столбцов в профильной схеме
void swapColumnsProfile(int UD[], int UN[], int IU[], int JU[], int n, int col1, int col2) {
    if (col1 == col2 || col1 < 1 || col2 < 1 || col1 > n || col2 > n) {
        cout << "Неверные номера столбцов!" << endl;
        return;
    }
    
    // Приводим к 0-индексации
    int c1 = col1 - 1;
    int c2 = col2 - 1;
    
    cout << "Перестановка столбцов " << col1 << " и " << col2 << "..." << endl;
    
    // Особый случай: если переставляем диагональные элементы
    if (c1 == c2) {
        return; // Ничего не делаем
    }
    
    // В профильной схеме хранятся только элементы нижнего треугольника
    // При перестановке столбцов симметрия может нарушиться
    
    // 1. Обмен диагональных элементов
    swap(UD[c1], UD[c2]);
    
    // 2. Обмен элементов в профиле
    // Проходим по всем строкам
    for (int i = 0; i < n; i++) {
        int start = IU[i] - 1;
        int end = IU[i + 1] - 2;
        
        // Проходим по профилю строки i
        for (int k = start; k <= end; k++) {
            int currentCol = JU[k] - 1;
            
            // Если нашли столбец col1
            if (currentCol == c1) {
                // Проверяем, есть ли в этой строке столбец col2
                bool hasCol2 = false;
                int col2Pos = -1;
                for (int m = start; m <= end; m++) {
                    if (JU[m] - 1 == c2) {
                        hasCol2 = true;
                        col2Pos = m;
                        break;
                    }
                }
                
                if (hasCol2) {
                    // Если есть оба столбца, меняем значения
                    swap(UN[k], UN[col2Pos]);
                } else {
                    // Если есть только col1, а col2 нет в профиле
                    // В профильной схеме это сложно, т.к. меняется структура
                    // Для упрощения: если элемент ненулевой, он должен появиться в профиле
                    // Но это меняет структуру профиля
                    cout << "Внимание: перестановка может изменить структуру профиля!" << endl;
                    JU[k] = c2 + 1; // Просто меняем индекс столбца
                }
            } 
            // Если нашли столбец col2 (и не обработали выше)
            else if (currentCol == c2) {
                bool hasCol1 = false;
                int col1Pos = -1;
                for (int m = start; m <= end; m++) {
                    if (JU[m] - 1 == c1) {
                        hasCol1 = true;
                        col1Pos = m;
                        break;
                    }
                }
                
                if (!hasCol1) {
                    JU[k] = c1 + 1; // Меняем индекс столбца
                }
                // Если hasCol1 = true, уже обработали в первом if
            }
        }
    }
    
    // 3. После перестановки нужно отсортировать элементы в каждой строке по столбцам
    // (в профильной схеме обычно хранят в порядке возрастания столбцов)
    for (int i = 0; i < n; i++) {
        int start = IU[i] - 1;
        int end = IU[i + 1] - 2;
        int count = end - start + 1;
        
        if (count > 0) {
            // Создаем массивы для сортировки
            vector<pair<int, double>> rowElements; // (столбец, значение)
            for (int k = start; k <= end; k++) {
                rowElements.push_back({JU[k] - 1, UN[k]});
            }
            
            // Сортируем по столбцам
            sort(rowElements.begin(), rowElements.end());
            
            // Возвращаем обратно
            for (int k = 0; k < count; k++) {
                JU[start + k] = rowElements[k].first + 1;
                UN[start + k] = rowElements[k].second;
            }
        }
    }
}

// Функция для вывода профильного представления
void printProfileFormat(int UD[], int UN[], int IU[], int JU[], int n, const string& name) {
    cout << "\n" << name << " (профильный формат):" << endl;
    
    cout << "UD (" << n << " элементов): ";
    for (int i = 0; i < n; i++) {
        cout << setw(4) << UD[i];
    }
    cout << endl;
    
    int unSize = IU[n] - 1;  // Последний элемент IU указывает на первую свободную позицию
    cout << "UN (" << unSize << " элементов): ";
    for (int i = 0; i < unSize; i++) {
        cout << setw(4) << UN[i];
    }
    cout << endl;
    
    cout << "IU (" << n + 1 << " элементов): ";
    for (int i = 0; i <= n; i++) {
        cout << setw(4) << IU[i];
    }
    cout << endl;
    
    cout << "JU (" << unSize << " элементов): ";
    for (int i = 0; i < unSize; i++) {
        cout << setw(4) << JU[i];
    }
    cout << endl;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    // Пример симметричной матрицы 5x5
    const int n = 5;
    
    // Диагональные элементы
    int UD[n] = {1, 2, 3, 4, 5};
    
    // Внедиагональные элементы профиля (по строкам)
    int UN[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    // Указатели на диагональные элементы в UN
    // IU[i] указывает на позицию в UN, где начинается строка i (1-индексация)
    // IU[n] указывает на первую свободную позицию
    int IU[n + 1] = {1, 2, 4, 7, 9, 11};
    
    // Столбцовые индексы для элементов в UN
    int JU[10] = {2, 3, 4, 3, 4, 5, 4, 5, 5, 5};  // 1-индексация
    
    cout << "ИСХОДНАЯ МАТРИЦА" << endl;
    cout << "================" << endl;
    
    printProfileFormat(UD, UN, IU, JU, n, "Исходная матрица");
    cout << endl;
    
    // Выводим матрицу в обычном виде
    cout << "Матрица 5x5:" << endl;
    printMatrixFromProfile(UD, UN, IU, JU, n);
    
    // Запрос столбцов для перестановки
    int col1, col2;
    cout << "Введите номера двух столбцов для перестановки (1-" << n << "): ";
    cin >> col1 >> col2;
    
    // Выполняем перестановку
    swapColumnsProfile(UD, UN, IU, JU, n, col1, col2);
    
    cout << "\nМАТРИЦА ПОСЛЕ ПЕРЕСТАНОВКИ СТОЛБЦОВ" << endl;
    cout << "===================================" << endl;
    
    printProfileFormat(UD, UN, IU, JU, n, "Матрица после перестановки");
    cout << endl;
    
    // Выводим матрицу в обычном виде после перестановки
    cout << "Матрица после перестановки столбцов " << col1 << " и " << col2 << ":" << endl;
    printMatrixFromProfile(UD, UN, IU, JU, n);
    
    // Демонстрация с другим примером
    cout << "\nДОПОЛНИТЕЛЬНЫЙ ПРИМЕР" << endl;
    cout << "=====================" << endl;
    
    // Пример из методички (рис. 1(a) - симметричная ленточная матрица 7x7)
    const int n2 = 7;
    
    int UD2[n2] = {1, 2, 3, 4, 5, 6, 7};
    int UN2[7] = {8, 9, 10, 11, 12, 13, 14}; // Примерные значения
    int IU2[n2 + 1] = {1, 2, 4, 7, 9, 11, 14, 15}; // Из примера на стр. 11
    int JU2[14] = {2, 3, 4, 3, 4, 5, 4, 5, 6, 5, 6, 7, 6, 7}; // Примерные индексы
    
    printProfileFormat(UD2, UN2, IU2, JU2, n2, "Пример из методички");
    
    // Перестановка столбцов 2 и 5
    swapColumnsProfile(UD2, UN2, IU2, JU2, n2, 2, 5);
    
    printProfileFormat(UD2, UN2, IU2, JU2, n2, "После перестановки столбцов 2 и 5");
    
    return 0;
}