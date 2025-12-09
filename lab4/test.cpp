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
    int UD[n];  // Диагональ
    vector<int> UN;  // Элементы профиля
    vector<int> JU;  // Столбцовые индексы (1-индексация)
    vector<int> IU;  // Указатели  на начало строк
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
    swap(UD[col1-1], UD[col2-1]);
    cout << "1. Перестановка диагональных элементов:" << endl;
    cout << "   UD[" << col1 << "] = " << UD_orig[col1-1] << " -> " << UD[col2-1] << endl;
    cout << "   UD[" << col2 << "] = " << UD_orig[col2-1] << " -> " << UD[col1-1] << endl;


    cout << "\n2. Перестановка в профиле:" << endl;
    int changed_cnt = 0;
    for (size_t i = 0; i < JU.size(); i++) {
        if (JU[i] == col1) {
            JU[i] = col2;
            changed_cnt++;
            cout << "   JU[" << i+1 << "]: столбец " << col1 << " -> " << col2 << endl;
        } else if (JU[i] == col2) {
            JU[i] = col1;
            changed_cnt++;
            cout << "   JU[" << i+1 << "]: столбец " << col2 << " -> " << col1 << endl;
        }
    }
    cout << "   Всего изменено " << changed_cnt << " элементов в JU" << endl;
    
    
    cout << "\n3. Сортировка элементов в строках по возрастанию столбцов:" << endl;
    
    for (int i = 0; i < n; i++) {
        int start = IU[i] - 1;      // Начало строки i в UN
        int end = IU[i + 1] - 2;    // Конец строки i в UN
        int cnt = end - start + 1; // Количество элементов в строке
        
        if (cnt > 1) {
            vector<pair<int, int>> rowData;
            for (int k = start; k <= end; k++) {
                rowData.push_back({JU[k], UN[k]});
            }
            sort(rowData.begin(), rowData.end());
            for (int k = 0; k < cnt; k++) {
                JU[start + k] = rowData[k].first;
                UN[start + k] = rowData[k].second;
            }
            
            cout << "   Строка " << i+1 << " отсортирована (" << cnt << " элемента)" << endl;
        }
    }
    
    
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
    return 0;
}