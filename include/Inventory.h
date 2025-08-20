#pragma once
#include "LinkedListNode.h"
#include "Weapon.h"

namespace LoW {

    // Lista ligada circular de armas. No es dueña de Weapon.
    class Inventory {
    public:
        LinkedListNode<Weapon>* head = nullptr;
        LinkedListNode<Weapon>* tail = nullptr;
        LinkedListNode<Weapon>* current = nullptr; // arma seleccionada

        Inventory() = default;
        ~Inventory() { }

        bool empty() const { return head == nullptr; }

        int size() const {
            if (!head) return 0;
            int n = 0; auto* it = head;
            do { ++n; it = it->next; } while (it && it != head);
            return n;
        }

        // Agrega al final manteniendo el círculo
        void append(Weapon* w) {
            if (!w) return;
            auto* node = new LinkedListNode<Weapon>(w);
            if (!head) {
                head = tail = node;
                node->next = head; // circular
                current = head;    // primera arma queda seleccionada
            }
            else {
                tail->next = node;
                tail = node;
                tail->next = head; // cerrar anillo
            }
        }

        // Avanza a la siguiente arma y la devuelve
        Weapon* next() {
            if (!current) return nullptr;
            current = current->next ? current->next : head;
            return current->data;
        }

        Weapon* getCurrent() const { return current ? current->data : nullptr; }
    };
}