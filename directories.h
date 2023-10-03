#ifndef DIRECTORIES_H
#define DIRECTORIES_H
#include "clientsTree.h"
#include "clientsHash.h"
#include <fstream>

struct ClientsDir {
    ClientsDir(int hashTableDefaultCapacity) : clientsHashTable(hashTableDefaultCapacity) {}
    ClientList clientsList;
    ClientTree clientsNameTree = ClientTree(compareClientName, compareToName);
    ClientTree clientsBirthdayTree = ClientTree(compareClientBirthday, compareToBirthday);
    ClientTree clientsPhoneTree = ClientTree(compareClientPhone, compareToPhone);
    ClientHashTable clientsHashTable;

    int ADD(Client _val)
    {
        if (clientsHashTable.Search(_val) != -1) {
            return 1;
        }


        clientsHashTable.Insert(_val);
        if (clientsHashTable.Search(_val) == -1) {
            return -1;
        }

        clientsNameTree.insert(_val);
        if (!(clientsNameTree.searchTree(_val.name)->val.find(_val))) {
            return -2;
        }

        clientsBirthdayTree.insert(_val);
        if (!(clientsBirthdayTree.searchTree(_val.birthday)->val.find(_val))) {
            return -3;
        }

        clientsPhoneTree.insert(_val);
        if (!(clientsPhoneTree.searchTree(_val.phone_number)->val.find(_val))) {
            return -4;
        }

        clientsList.push(_val);
        if (!(clientsList.find(_val))) {
            return -5;
        }

        return 0;
    }

    int LOAD(std::string filename)
    {
        clientsNameTree.flush();
        clientsBirthdayTree.flush();
        clientsPhoneTree.flush();
        clientsHashTable = ClientHashTable(clientsHashTable.getStartCapacity());
        clientsList.flush();
        std::ifstream SOURCE_FILE(filename);
        if (!SOURCE_FILE.is_open()) return 1;
        while (SOURCE_FILE.peek() != EOF) {
            Client placeholder;
            SOURCE_FILE >> placeholder.name;
            SOURCE_FILE >> placeholder.birthday;
            SOURCE_FILE >> placeholder.phone_number;
            SOURCE_FILE >> placeholder.ID;
            if (SOURCE_FILE) {
                std::cout << ADD(placeholder) << std::endl;
            }
        }
        SOURCE_FILE.close();
        return 0;
    }

    int SAVE(std::string filename)
    {
        std::ofstream TARGET_FILE(filename);
        if (!TARGET_FILE.is_open()) return 1;
        NodeClientList* point = this->clientsList.head;
        while (point) {
            TARGET_FILE << point->val.name << " ";
            TARGET_FILE << point->val.birthday << " ";
            TARGET_FILE << point->val.phone_number << " ";
            TARGET_FILE << point->val.ID << std::endl;
            point = point->next;
        }
        TARGET_FILE.close();
        return 0;
    }
};

#endif // DIRECTORIES_H
