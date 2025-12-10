#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    const int n = 5;
    int my_matrix[n][n] = {
        {10, 5, 0, 22, 0},
        {5, 20, 7, 0, 4},
        {0, 7, 30, 6, 0},
        {22, 0, 6, 40, 111},
        {0, 4, 0, 111, 57}
    };
    cout << "\nИсходная симметричная матрица " << n << "x" << n << ":" << endl;
    for (int i=0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << my_matrix[i][j];
        }
        cout << endl;
    }

    cout << "\nПрофильное представление матрицы:" << endl;
    int UD[n];  // диагональ
    vector<int> UN;  // элементы профиля
    vector<int> JU;  // столбцовые индексы (1-индексация)
    vector<int> IU;  // указатели  на начало строк
    IU.push_back(1);
    int currentPos = 1;
    cout << "\nДиагональные элементы (UD): ";
    for (int i = 0; i < n; i++) {
        UD[i] = my_matrix[i][i];
        cout << UD[i] << " ";
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (my_matrix[i][j] != 0) {
                UN.push_back(my_matrix[i][j]);
                JU.push_back(j + 1);
                currentPos++;
            }
        }
        IU.push_back(currentPos);
    }
    cout << "\nПрофиль (UN, только внедиагональные элементы): ";
    for (size_t i = 0; i < UN.size(); i++) {
        cout << UN[i] << " ";
    }
    cout << "\nСтолбцовые индексы профиля (JU): ";
    for (size_t i = 0; i < JU.size(); i++) {
        cout << JU[i] << " ";
    }
    cout << "\nУказатели на начало строк (IU): ";
    for (size_t i = 0; i < IU.size(); i++) {
        cout << IU[i] << " ";
    }

    cout << "\n\nВведите номера двух столбцов для перестановки (1-" << n << "): ";
    int col1, col2;
    while (true) {
        cout << "\nПервый столбец (1-" << n << "): ";
        cin >> col1;
        if (cin.fail()) {
            cout << "Ошибка ввода. Введите целое число." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else if (col1 < 1 || col1 > n) {
            cout << "Неверный номер. Попробуйте снова и введите значение от 1 до " << n << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "Второй столбец (1-" << n << "): ";
        cin >> col2;
        if (cin.fail()) {
            cout << "Ошибка ввода. Введите целое число." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else if (col2 < 1 || col2 > n) {
            cout << "Неверный номер. Попробуйте снова и введите значение от 1 до " << n << endl;
        } else if (col2 == col1) {
            cout << "Столбцы не должны совпадать. Попробуйте снова." << endl;
        } else {
            break;
        }
    }
    
    int UD_orig[n];
    for (int i = 0; i < n; i++) UD_orig[i] = UD[i];

    int full_matrix[n][n] = {0};
    for (int i = 0; i < n; i++) {
        full_matrix[i][i] = UD[i]; // диагональ
    }
    for (int i = 0; i < n; i++) {
        int start = IU[i] - 1;
        int end = IU[i + 1] - 2;
        for (int k = start; k <= end; k++) {
            int col = JU[k] - 1;
            full_matrix[i][col] = UN[k]; // профиль (нижний треугольник + симметрия)
            full_matrix[col][i] = UN[k];
        }
    }
    for (int i = 0; i < n; i++) {
        swap(full_matrix[i][col1-1], full_matrix[i][col2-1]); // перестановка столбцов
    }
    for (int j = 0; j < n; j++) {
        swap(full_matrix[col1-1][j], full_matrix[col2-1][j]); // перестановка соответствующих строк (для сохранения симметрии)
    }
    
    cout << "\nПерестройка профильного представления:" << endl;
    UN.clear();
    JU.clear();
    IU.clear();
    IU.push_back(1);
    currentPos = 1;
    for (int i = 0; i < n; i++) {
        UD[i] = full_matrix[i][i]; // диагональ
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (full_matrix[i][j] != 0) {
                UN.push_back(full_matrix[i][j]); // профиль (только нижний треугольник)
                JU.push_back(j + 1);
                currentPos++;
            }
        }
        IU.push_back(currentPos);
    }
    
    cout << "   UD[" << col1 << "] = " << UD_orig[col1-1] << " -> " << UD[col1-1] << endl;
    cout << "   UD[" << col2 << "] = " << UD_orig[col2-1] << " -> " << UD[col2-1] << endl;
    
    cout << "\n\nПрофильное представление после перестановки:" << endl;
    cout << "Диагональные элементы (UD): ";
    for (int i = 0; i < n; i++) {
        cout << UD[i] << " ";
    }
    cout << "\nПрофиль (UN, только внедиагональные элементы): ";
    for (size_t i = 0; i < UN.size(); i++) {
        cout << UN[i] << " ";
    }
    cout << "\nСтолбцовые индексы профиля (JU): ";
    for (size_t i = 0; i < JU.size(); i++) {
        cout << JU[i] << " ";
    }
    cout << "\nУказатели на начало строк (IU): ";
    for (size_t i = 0; i < IU.size(); i++) {
        cout << IU[i] << " ";
    }

    cout << "\n\nМатрица после перестановки столбцов " << col1 << " и " << col2 << ":" << endl;
    int restored[n][n] = {0};
    for (int i = 0; i < n; i++) {
        restored[i][i] = UD[i];
    }

    for (int i = 0; i < n; i++) {
        int start = IU[i] - 1;
        int end = IU[i + 1] - 2;
        
        for (int k = start; k <= end; k++) {
            int col = JU[k] - 1;
            restored[i][col] = UN[k];
            restored[col][i] = UN[k];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << restored[i][j];
        }
        cout << endl;
    }
    
    return 0;
}