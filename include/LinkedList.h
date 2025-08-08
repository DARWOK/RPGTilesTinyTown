#pragma once
#include <iostream>
#include <string>

class LinkedList {
private:
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}
    
    ~LinkedList() {
        clear();
    }

    // Agregar nodo al final
    void append(const std::string& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Imprimir lista
    void print() const {
        Node* current = head;
        std::cout << "Linked List (strings): ";
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
    }
    
    // Limpiar memoria
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
