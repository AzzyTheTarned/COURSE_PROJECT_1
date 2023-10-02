#ifndef DIRECTORIES_H
#define DIRECTORIES_H
#include "clientsTree.h"
#include "clientsHash.h"
#include "insurancesTree.h"

/* Assigned to Alexey Aliferov */
struct ClientsDir {
    std::vector<Client> clientsVector;
    ClientTree clientsNameTree = ClientTree(compareClientName, compareToName);
    ClientTree clientsBirthdayTree = ClientTree(compareClientBirthday, compareToBirthday);
    ClientTree clientsPhoneTree = ClientTree(compareClientPhone, compareToPhone);
    ClientHashTable clientHashTable;
};

/* Assigned to Alexey Popov */
struct AgentsDir {

};

/* Assigned to Miroslav Alekseev */
struct InsurancesDir {
    std::vector<Insurance> insurancesVector;
    tree insuranceTree;
};

#endif // DIRECTORIES_H
