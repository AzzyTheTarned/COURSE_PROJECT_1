#ifndef CLIENTSHASH_H
#define CLIENTSHASH_H
#include "clientsRecord.h"
#include <iostream>

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
    int start_capacity;

    // int primaryHash(int key) {
    //     return key % capacity;
    // }
    int primaryHash(std::string key) {
        int hash = 0;
        for (int i = 0; i < key.length(); ++i) {
            hash += key[i];
        }
        return hash % capacity;
    }
    // int primaryHash(const Client& _record) {
    //     return _record.ID % capacity;
    // }
    int primaryHash(const Client& _record) {
        int hash = 0;
        for (int i = 0; i < _record.ID.length(); ++i) {
            hash += _record.ID[i];
        }
        return hash % capacity;
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
    int findIndex(std::string _key) {
        int h = primaryHash(_key);
        int i = 1;
        int first_deleted = -1;
        while ((table[h] != nullptr) && (i <= capacity)) {
            if ((table[h]->record.ID == _key) && (table[h]->status)) {
                return h;
            }
            if (table[h]->status == false && first_deleted == -1)
                first_deleted = h;
            h = secondaryHash(primaryHash(_key), i) % capacity;
            ++i;
        }
        return first_deleted == -1 ? h : first_deleted;
    }
public:
    NodeClientHashTable** getTable() {
        return table;
    }
    int getStartCapacity() {
        return start_capacity;
    }

    ClientHashTable() {
        capacity = 10;
        start_capacity = 10;
        size = 0;
        size_with_deleted = 0;
        table = new NodeClientHashTable*[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }
    ClientHashTable(int default_capacity) {
        capacity = default_capacity;
        start_capacity = default_capacity;
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


    int Search(std::string _key) {
        int index = findIndex(_key);
        return table[index] != nullptr && table[index]->status ? index : -1;
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
    int Delete(std::string _key) {
        int index = findIndex(_key);
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
    void flush() {
        for (int i = 0; i < capacity; ++i) {
            if (table[i]) {
                delete table[i];
            }
        }
        delete[] table;
        capacity = start_capacity;
        size = 0;
        size_with_deleted = 0;
        table = new NodeClientHashTable*[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }
    void reconstruct(unsigned int _capacity) {
        for (int i = 0; i < capacity; ++i) {
            if (table[i]) {
                delete table[i];
            }
        }
        delete[] table;
        capacity = _capacity;
        start_capacity = _capacity;
        size = 0;
        size_with_deleted = 0;
        table = new NodeClientHashTable*[_capacity];
        for (int i = 0; i < _capacity; ++i) {
            table[i] = nullptr;
        }
    }
};

#endif // CLIENTSHASH_H
