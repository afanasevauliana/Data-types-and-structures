#pragma once
#include <iostream>
using namespace std;

class Graph
{
public:
    int A[7][7]; //матрица смежности
    int str; //размер матрицы

    Graph() { //стандартный конструктор графа
        this->str = 7;
        for(int i = 0; i < this->str; i++)
            for(int j = i; j < this->str; j++) {
                this->A[i][j] = 0;
                this->A[j][i] = this->A[i][j];
            }
    }
    
    Graph(int _n) { //конструктор графа
        this->str = _n;
        for(int i = 0; i < this->str; i++)
            for(int j = i; j < this->str; j++) {
                this->A[i][j] = 0;
                this->A[j][i] = this->A[i][j];
            }
    }
    //обращение к элементу матрицы
    int& operator()(int _i, int _j) {
        return this->A[_i][_j];
    }
    
    void setMatrix(int _n) { //изменение матрицы
        this->str = _n;
    }
    
    void ShowGraph() { //показ матрицы
        system("cls");
        cout << "Матрица смежности:\n";
        for(int i = 0; i < str; i++) {
            for(int j = 0; j < str; j++) {
                cout << " " << A[i][j] << " ";
            }
            cout << "\n";
        }
    }
};