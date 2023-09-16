#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include "records.h"
#include <iostream>

/*
Data structures for Clients directory
Assigned to Alexey Aliferov
*/
class ClientHashTable {
    constexpr static const double rescale_factor = 0.75; // коэффициент ремасштабирования таблицы
    struct NodeClientHashTable {
        Client record;
        bool status; // true - элемент есть (статус 1), false - элемент был удален (статус 2)
        // если вместо Node nullptr - значит элемента никогда не было (статус 0)
        NodeClientHashTable(const Client& _record) : record(_record), status(true) {}
    };
    NodeClientHashTable** table;
    int size; // сколько элементов в таблице (без удаленных) //
    int size_with_deleted; // сколько элементов в таблице С удалёнными //
    int capacity; // сколько места в таблице //

    int primaryHash(const Client& _record) {
        return _record.ID % capacity;
    }
    int secondaryHash(int primary_hash, int attempt) {
        return (primary_hash + (attempt * 1));
    }
    void rescale(bool expand) { // true - расширить вдвое, false - сжать вдвое
        int past_capacity = capacity;
        capacity *= expand ? 2 : 0.5;
        size_with_deleted = 0;
        size = 0;
        NodeClientHashTable** new_table = new NodeClientHashTable*[capacity];
        for (int i = 0; i < capacity; ++i) {
            new_table[i] = nullptr;
        }
        std::swap(table, new_table);
        for (int i = 0; i < past_capacity; ++i) {
            if (new_table[i] && new_table[i]->status) {
                Insert(new_table[i]->record);
            }
        }
        for (int i = 0; i < past_capacity; ++i) {
            if (new_table[i]) {
                delete new_table[i];
            }
        }
        delete[] new_table;
    }
    int findIndex(const Client& _record) {
        int h = primaryHash(_record);
        int i = 1;
        int first_deleted = -1;
        while ((table[h] != nullptr) && (i <= capacity)) {
            if ((table[h]->record == _record) && (table[h]->status)) {
                return h;
            }
            if (table[h]->status == false && first_deleted == -1)
                first_deleted = h;
            h = secondaryHash(primaryHash(_record), i) % capacity;
            ++i;
        }
        return first_deleted == -1 ? h : first_deleted;
    }
public:
    ClientHashTable(int default_capacity) {
        capacity = default_capacity;
        size = 0;
        size_with_deleted = 0;
        table = new NodeClientHashTable*[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }
    ~ClientHashTable() {
        for (int i = 0; i < capacity; ++i) {
            if (table[i]) {
                delete table[i];
            }
        }
        delete[] table;
    }

    int Search(const Client& _record) {
        int index = findIndex(_record);
        return table[index] != nullptr && table[index]->status ? index : -1;
    }
    int Delete(const Client& _record) {
        int index = findIndex(_record);
        if (table[index] != nullptr && table[index]->status) {
            table[index]->status = false;
            --size;
            return index;
        }
        return -1;
    }
    int Insert(const Client& _record) {
        int return_index = -1;
        if (size + 1 > std::round(capacity * rescale_factor)) {
            rescale(true);
        }
        else if ((size + 1 < std::round(capacity * (1 - rescale_factor))) && (capacity <= rescale_factor)) {
            rescale(false);
        }
        int index = findIndex(_record);
        if (table[index] == nullptr) {
            table[index] = new NodeClientHashTable(_record);
            ++size_with_deleted;
            return_index = index;
        } else if (!table[index]->status) {
            table[index]->record = _record;
            table[index]->status = true;
            return_index = index;
        }
        ++size;
        return return_index;
    }
    void Print() {
        for (int i = 0; i < capacity; ++i) {
            if (!table[i]) {
                std::cout << i << ": " << " [STATUS 0]" << std::endl;
            }
            else if (table[i]->status) {
                std::cout << i << ": " << " [STATUS 1] " << table[i]->record.name << " - Birthday: "
                << table[i]->record.birthday << " - Phone number: "
                << table[i]->record.phone_number << " - ID: " << table[i]->record.ID << std::endl;
            }
            else std::cout << i << ": " << " [STATUS 2]" << std::endl;
        }
        std::cout << std::endl;
    }
};
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
