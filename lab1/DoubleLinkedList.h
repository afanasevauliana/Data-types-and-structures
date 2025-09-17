#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <iostream>
#include "Exception.h"

struct Node {
    double data;
    Node* prev;
    Node* next;
    
    Node(double value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoubleLinkedList {
private:
    Node* head;
    Node* tail;
    int size;
    
public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoubleLinkedList() { clear(); }
    
    void addToEnd(double value);
    void print() const;
    void clear();
    bool isEmpty() const { return size == 0; }
    int getSize() const { return size; }
    double getAt(int index) const;
    double calculateVariant3() const;
};

void DoubleLinkedList::addToEnd(double value) {
    Node* newNode = new Node(value);
    
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void DoubleLinkedList::print() const {
    if (isEmpty()) {
        throw ListException("Список пуст!");
    }
    
    std::cout << "Список [" << size << " элементов]: ";
    
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " → ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

void DoubleLinkedList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

double DoubleLinkedList::getAt(int index) const {
    if (index < 0 || index >= size) {
        throw ListException("Индекс выходит за границы списка!");
    }
    
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

double DoubleLinkedList::calculateVariant3() const {
    if (isEmpty()) {
        throw ListException("Список пуст для вычисления!");
    }
    
    if (size == 1) {
        return 2 * head->data; // (x1 + x1) = 2*x1
    }
    
    double result = 1.0;
    Node* front = head;
    Node* back = tail;
    
    for (int i = 0; i < size / 2; i++) {
        result *= (front->data + back->data);
        front = front->next;
        back = back->prev;
    }
    
    if (size % 2 != 0) { // на случай, если кол-во элементов нечетное
        result *= (front->data + front->data); // средний элемент
    }
    
    return result;
}

#endif