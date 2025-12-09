#include <iostream>
#include <stack>
#include <windows.h>

using namespace std;

class Graph {
private:
    int n;
    int** GM;

public:
    Graph(int vertices) : n(vertices) {
        GM = new int*[n];
        for (int i = 0; i < n; i++) {
            GM[i] = new int[n];
            for (int j = 0; j < n; j++) {
                GM[i][j] = 0;
            }
        }
    }
    ~Graph() {
        for (int i = 0; i < n; i++) {
            delete[] GM[i];
        }
        delete[] GM;
    }
    
    void addEdge(int u, int v) {
        GM[u-1][v-1] = 1;
        GM[v-1][u-1] = 1;
    }
    
    void printMatrix() {
        cout << "Матрица смежности:" << endl;
        cout << "   ";
        for (int i = 1; i <= n; i++) cout << i << " ";
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << i+1 << ": ";
            for (int j = 0; j < n; j++) {
                cout << GM[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void findSimplePath(int start, int end) {
        if (start < 1 || start > n || end < 1 || end > n) {
            cout << "\nОшибка: номера вершин должны быть от 1 до " << n << "!" << endl;
            return;
        }
    
        int internalStart = start - 1;
        int internalEnd = end - 1;
        bool* visited = new bool[n];
        int* parent = new int[n];
        int* queue = new int[n];
        int count = 0, head = 0;
        for (int i = 0; i < n; i++) {
            visited[i] = false;
            parent[i] = -1;
        }
        
        cout << "\nАлгоритм работы:" << endl;
        queue[count++] = internalStart;
        visited[internalStart] = true;
        cout << "Посещена вершина " << start << endl;
        bool pathFound = false;
        while (head < count && !pathFound) {
            int current = queue[head++];
            if (current == internalEnd) {
                cout << "Найдена конечная вершина " << end << endl;
                pathFound = true;
                break;
            }
            
            for (int i = 0; i < n; i++) {
                if (GM[current][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    parent[i] = current;
                    queue[count++] = i;
                    cout << "Посещена вершина " << i+1
                         << " (из вершины " << current+1 << ")" << endl;
                }
            }
        }
        
        if (pathFound) {
            reconstructAndPrintPath(internalStart, internalEnd, parent);
        } else {
            cout << "Путь из " << start << " в " << end << " не существует!" << endl;
        }
        delete[] visited;
        delete[] parent;
        delete[] queue;
    }

private:
    void reconstructAndPrintPath(int internalStart, int internalEnd, int* parent) {
        stack<int> pathStack;
        int current = internalEnd;
        
        while (current != -1) {
            pathStack.push(current);
            current = parent[current];
        }
        cout << "Простой путь из " << internalStart+1 << " в " << internalEnd+1 << ":" << endl;
        
        cout << pathStack.top() + 1;
        pathStack.pop();
        int edgeCount = 0;
        
        while (!pathStack.empty()) {
            cout << " -> " << pathStack.top() + 1;
            pathStack.pop();
            edgeCount++;
        }
        cout << endl;
        cout << "Длина пути (кол-во ребер): " << edgeCount << endl;
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    cout << "*Все вершины нумеруются с 1" << endl;
    Graph g(9);
    g.addEdge(1, 2);
    g.addEdge(1, 8);
    g.addEdge(2, 3);
    g.addEdge(2, 8);
    g.addEdge(3, 4);
    g.addEdge(3, 6);
    g.addEdge(3, 9);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.addEdge(7, 9);
    g.addEdge(8, 9);
    g.printMatrix();
    
    int start, end;
    bool inputOk = false;
    while (!inputOk) {
        cout << "Введите начальную вершину (1-9): ";
        cin >> start;
        
        if (cin.fail()) {
            cout << "Ошибка: введите ЧИСЛО от 1 до 9" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else if (start < 1 || start > 9) {
            cout << "Ошибка: вершина должна быть от 1 до 9" << endl;
            cin.ignore(1000, '\n');
        } else {
            inputOk = true;
            cin.ignore(1000, '\n');
        }
    }

    inputOk = false;
    
    while (!inputOk) {
        cout << "Введите конечную вершину (1-9): ";
        cin >> end;
        
        if (cin.fail()) {
            cout << "Введите ЧИСЛО от 1 до 9" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else if (end < 1 || end > 9) {
            cout << "Вершина должна быть от 1 до 9!" << endl;
            cin.ignore(1000, '\n');
        } else {
            inputOk = true;
            cin.ignore(1000, '\n');
        }
    }

    g.findSimplePath(start, end);
    return 0;
}