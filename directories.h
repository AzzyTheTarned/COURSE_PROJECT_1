#ifndef DIRECTORIES_H
#define DIRECTORIES_H
#include "clientsTree.h"
#include "clientsHash.h"

struct ClientsDir {
    std::vector<Client> clientsVector;
    ClientTree clientsNameTree = ClientTree(compareClientName, compareToName);
    ClientTree clientsBirthdayTree = ClientTree(compareClientBirthday, compareToBirthday);
    ClientTree clientsPhoneTree = ClientTree(compareClientPhone, compareToPhone);
    ClientHashTable clientHashTable;
};

#endif // DIRECTORIES_H
