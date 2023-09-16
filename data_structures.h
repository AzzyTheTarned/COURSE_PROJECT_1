#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include "records.h"
#include <iostream>

/*
Data structures for Clients directory
Assigned to Alexey Aliferov
*/
struct NodeClientList {
    Client val;
    NodeClientList* next;
    NodeClientList(Client _val) : val(_val), next(nullptr){};
};
struct ClientList {
    NodeClientList* head;
    ClientList() : head(nullptr) {}

private:
    bool isEmpty() {
        return head == nullptr;
    }
    bool isOneItem() {
        return isEmpty() ? false : head->next == nullptr;
    }
    void removeFirst() {
        if (isEmpty()) return;
        if (isOneItem()) {
            delete head;
            head = nullptr;
            return;
        }
        NodeClientList* p = head;
        head = p->next;
        delete p;
    }
    void removeLast() {
        if (isEmpty()) return;
        if (isOneItem()) {
            delete head;
            head = nullptr;
            return;
        }
        NodeClientList* p = head;
        while (p->next->next != nullptr) p = p->next;
        delete p->next;
        p->next = nullptr;
    }
    NodeClientList* pushFirst(Client _val) {
        NodeClientList* p = new NodeClientList(_val);
        if (isEmpty()) {
            head = p;
            return p;
        }
        p->next = head;
        head = p;
        return p;
    }
    NodeClientList* pushLast(Client _val) {
        NodeClientList* p = new NodeClientList(_val);
        if (isEmpty()) {
            head = p;
            return p;
        }
        NodeClientList* i = head;
        while (i->next != nullptr) i = i->next;
        i->next = p;
        return p;
    }
public:
    void flush() {
        while (!isEmpty()) removeFirst();
    }
    void remove(Client _val) {
        if (isEmpty()) return;
        if (isOneItem()) {
            if (head->val == _val) removeFirst();
            return;
        }
        NodeClientList* p = head;
        while (p->next != nullptr && p->next->val != _val) p = p->next;
        if (p->next == nullptr) return;
        NodeClientList* toDel = p->next;
        p->next = p->next->next;
        delete toDel;
    }
    NodeClientList* push(Client _val) {
        if (isEmpty()) {
            return pushFirst(_val);
        }
        if (_val < head->val) {
            return pushFirst(_val);
        }
        if (_val == head->val) {
            return nullptr;
        }
        NodeClientList* p = head;
        while (p->next != nullptr && p->next->val <= _val) p = p->next;
        if (p->val == _val) return nullptr;
        NodeClientList* toAdd = new NodeClientList(_val);
        toAdd->next = p->next;
        p->next = toAdd;
        return toAdd;
    }
    NodeClientList* find(Client _val) {
        NodeClientList* p = head;
        while (p != nullptr && p->val != _val) p = p->next;
        return p;
    }
    void print() {
        if (isEmpty()) return;
        NodeClientList* p = head;
        while (p != nullptr) {
            std::cout << p->val.name << " - Birthday: " << p->val.birthday << " - Phone number: "
            << p->val.phone_number << " - ID: " << p->val.ID << std::endl;
            p = p->next;
        }
        std::cout << std::endl;
    }
};

/*
Data structures for Agents directory
Assigned to Alexey Popov
*/

/*
Data structures for Insurance directory
Assigned to Miroslav Alekseev
*/

#endif // DATA_STRUCTURES_H
