#ifndef DIRECTORIES_H
#define DIRECTORIES_H
#include "clientsTree.h"
#include "clientsHash.h"
#include "insurancesHash.h"
#include "insurancesTree.h"
#include <fstream>
#include <sstream>

struct ClientsDir {
    ClientsDir() {};
    ClientsDir(int hashTableDefaultCapacity) : clientsHashTable(hashTableDefaultCapacity) {}
    std::vector<Client> clientsList;
    ClientTree clientsNameTree = ClientTree(compareClientName, compareToName, getName);
    ClientTree clientsBirthdayTree = ClientTree(compareClientBirthday, compareToBirthday, getBirthday);
    ClientTree clientsPhoneTree = ClientTree(compareClientPhone, compareToPhone, getPhone);
    ClientHashTable clientsHashTable;

    int ADD(Client _val)
    {
        if (clientsHashTable.Search(_val) != -1) {
            return 1;
        }

        clientsList.push_back(_val);
        clientsList.back().order = clientsList.size();
        //        if (!(clientsList.find(_val))) {
        //            return -5;
        //        }


        clientsHashTable.Insert(clientsList[clientsList.size() - 1]);
        if (clientsHashTable.Search(_val) == -1) {
            return -1;
        }

        clientsNameTree.insert(clientsList[clientsList.size() - 1]);
        if (!(clientsNameTree.searchTree(_val.name)->val.find(_val))) {
            return -2;
        }

        clientsBirthdayTree.insert(clientsList[clientsList.size() - 1]);
        if (!(clientsBirthdayTree.searchTree(_val.birthday)->val.find(_val))) {
            return -3;
        }

        clientsPhoneTree.insert(clientsList[clientsList.size() - 1]);
        if (!(clientsPhoneTree.searchTree(_val.phone_number)->val.find(_val))) {
            return -4;
        }



        return 0;
    }

    int LOAD(std::string filename)
    {
        clientsNameTree.flush();
        clientsBirthdayTree.flush();
        clientsPhoneTree.flush();
        clientsHashTable.flush();
        clientsList.clear();
        std::ifstream SOURCE_FILE(filename);
        if (!SOURCE_FILE.is_open()) return 1;
        std::string line;
        while (std::getline(SOURCE_FILE, line)) {
            std::istringstream iss(line);
            Client placeholder;
            if (!(iss >> placeholder.name >> placeholder.birthday >> placeholder.phone_number >> placeholder.ID)) {
                return 2;
            }
            std::cout << ADD(placeholder) << std::endl;
        }
        SOURCE_FILE.close();
        return 0;
    }

    int SAVE(std::string filename)
    {
        std::ofstream TARGET_FILE(filename);
        if (!TARGET_FILE.is_open()) return 1;
//        NodeClientList* point = this->clientsList.head;
        for (int i = 0; i < clientsList.size(); i++) {
            TARGET_FILE << clientsList[i].name << " ";
            TARGET_FILE << clientsList[i].birthday << " ";
            TARGET_FILE << clientsList[i].phone_number << " ";
            TARGET_FILE << clientsList[i].ID << std::endl;
//            point = point->next;
        }
        TARGET_FILE.close();
        return 0;
    }

//    int REMOVE(Client _val) {
//        clientsHashTable.Delete(_val.ID);
//        clientsNameTree.remove(_val);
//        clientsBirthdayTree.remove(_val);
//        clientsPhoneTree.remove(_val);
//        clientsList.remove(_val);

//        return 0;
//    }
};

struct InsurancesDir {
    InsurancesDir() {};
    InsurancesDir(int hashTableDefaultCapacity) : insurancesHashTable(hashTableDefaultCapacity) {};
    listt insurancesList;
    tree insurancesClientIdTree = tree(price_co);
    tree insurancesAgentIdTree = tree(price_com);
    tree insurancesTypeTree = tree(price_comp);
    tree insurancesCostTree = tree(price_comparator);
    HT insurancesHashTable;

    void ADD(key _val) {
        insurancesHashTable.add(_val.clientpass, _val.agentpass, _val.strah, _val.stoim);

        insurancesClientIdTree.insert(_val);
        insurancesAgentIdTree.insert(_val);
        insurancesTypeTree.insert(_val);
        insurancesCostTree.insert(_val);
    }

};

#endif // DIRECTORIES_H
