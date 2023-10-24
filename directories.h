#ifndef DIRECTORIES_H
#define DIRECTORIES_H
#include "clientsTree.h"
#include "clientsHash.h"
#include "insurancesHash.h"
#include "insurancesTree.h"
#include "agentsHash.h"
#include "agentsTree.h"
#include <fstream>
#include <sstream>
#include <vector>

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
        if (clientsHashTable.Search(_val.ID) != -1) {
            return 1;
        }

        clientsList.push_back(_val);
        clientsList.back().order = clientsList.size();
        //        if (!(clientsList.find(_val))) {
        //            return -5;
        //        }


        clientsHashTable.Insert(clientsList[clientsList.size() - 1]);
        //        if (clientsHashTable.Search(_val) == -1) {
        //            return -1;
        //        }

        clientsNameTree.insert(clientsList[clientsList.size() - 1]);
        //        if (!(clientsNameTree.searchTree(_val.name)->val.find(_val))) {
        //            return -2;
        //        }

        clientsBirthdayTree.insert(clientsList[clientsList.size() - 1]);
        //        if (!(clientsBirthdayTree.searchTree(_val.birthday)->val.find(_val))) {
        //            return -3;
        //        }

        clientsPhoneTree.insert(clientsList[clientsList.size() - 1]);
        //        if (!(clientsPhoneTree.searchTree(_val.phone_number)->val.find(_val))) {
        //            return -4;
        //        }



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
            //            std::cout <<
            ADD(placeholder)
            //                < std::endl
            ;
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

    int REMOVE(Client _val, int list_index) {
        clientsHashTable.Delete(_val.ID);
        clientsNameTree.removeFromName(_val);
        clientsBirthdayTree.removeFromBirthday(_val);
        clientsPhoneTree.removeFromPhone(_val);

        if (list_index != (clientsList.size() - 1)) {
            clientsHashTable.getTable()[clientsHashTable.Search(clientsList.back().ID)]->record.order = list_index + 1;
            clientsNameTree.searchTree(clientsList.back().name)->val.find(clientsList.back())->val.order = list_index + 1;
            clientsBirthdayTree.searchTree(clientsList.back().birthday)->val.find(clientsList.back())->val.order = list_index + 1;
            clientsNameTree.searchTree(clientsList.back().name)->val.find(clientsList.back())->val.order = list_index + 1;
            clientsList[list_index] = clientsList.back();
            clientsList[list_index].order = list_index + 1;
        }
        clientsList.pop_back();

        return 0;
    }
};

struct InsurancesDir {
    InsurancesDir() {};
    InsurancesDir(int hashTableDefaultCapacity) : insurancesHashTable(hashTableDefaultCapacity) {};
    std::vector<key> insurancesList;
    tree insurancesClientIdTree = tree(price_co);
    tree insurancesAgentIdTree = tree(price_com);
    tree insurancesTypeTree = tree(price_comp);
    tree insurancesCostTree = tree(price_comparator);
    HT insurancesHashTable;
    int tid;
    void ADD(key _val) {
        if(_val.agentpass!=_val.clientpass){
            if(insurancesHashTable.size > tid-1){
                key temp;

                if(insurancesList.empty()==true){

                    _val.id = tid;
                    insurancesHashTable.add(_val.clientpass, _val.agentpass, _val.strah, _val.stoim, _val.id);

                    insurancesClientIdTree.insert(_val);
                    insurancesAgentIdTree.insert(_val);
                    insurancesTypeTree.insert(_val);
                    insurancesCostTree.insert(_val);
                    insurancesList.push_back(_val);
                }
                else{
                    temp=insurancesHashTable.find(_val.agentpass,_val.clientpass,_val.strah);
                    if( temp.id==-1 ){
                        tid++;
                        _val.id = tid;
                        insurancesHashTable.add(_val.clientpass, _val.agentpass, _val.strah, _val.stoim, _val.id);

                        insurancesClientIdTree.insert(_val);
                        insurancesAgentIdTree.insert(_val);
                        insurancesTypeTree.insert(_val);
                        insurancesCostTree.insert(_val);
                        insurancesList.push_back(_val);
                    }
                }
            }
        }
    }

    int LOAD(std::string filename) {
        insurancesClientIdTree.clear();
        insurancesAgentIdTree.clear();
        insurancesCostTree.clear();
        insurancesTypeTree.clear();
        insurancesList.clear();
        insurancesHashTable.clear();
        std::ifstream SOURCE_FILE(filename);
        if (!SOURCE_FILE.is_open()) return 1;
        std::string line;
        tid=1;
        while (std::getline(SOURCE_FILE, line)) {
            std::istringstream iss(line);
            key placeholder;

            if (!(iss >> placeholder.agentpass >> placeholder.clientpass >> placeholder.strah >> placeholder.stoim)) {
                placeholder.id = tid;
                tid++;
                return 2;
            }

            //            std::cout <<

            ADD(placeholder)
            //                < std::endl
            ;
        }
        SOURCE_FILE.close();
        return 0;
    }

    int REMOVE(key _val) {

        if (_val.id==insurancesList.size()){
            insurancesClientIdTree.remove(_val);
            insurancesAgentIdTree.remove(_val);
            insurancesCostTree.remove(_val);
            insurancesTypeTree.remove(_val);
            insurancesList.pop_back();
            insurancesHashTable.del(_val.id);
            tid--;
        }
        else{
            insurancesClientIdTree.remove(_val);
            insurancesClientIdTree.last_to_ind(insurancesList[insurancesList.size()-1],_val.id,insurancesClientIdTree.root);
            insurancesAgentIdTree.remove(_val);
            insurancesAgentIdTree.last_to_ind(insurancesList[insurancesList.size()-1],_val.id,insurancesAgentIdTree.root);
            insurancesCostTree.remove(_val);
            insurancesCostTree.last_to_ind(insurancesList[insurancesList.size()-1],_val.id,insurancesCostTree.root);
            insurancesTypeTree.remove(_val);
            insurancesTypeTree.last_to_ind(insurancesList[insurancesList.size()-1],_val.id,insurancesTypeTree.root);
            insurancesHashTable.del(_val.id);
            insurancesHashTable.replace(_val.id,insurancesList[insurancesList.size()-1]);
            tid = insurancesList.size()-1;

            if (_val.id != (insurancesList.size())) {
                int temp = insurancesList[_val.id].id;

                insurancesList[_val.id-1].agentpass = insurancesList[tid].agentpass;
                insurancesList[_val.id-1].clientpass = insurancesList[tid].clientpass;
                insurancesList[_val.id-1].strah = insurancesList[tid].strah;
                insurancesList[_val.id-1].stoim = insurancesList[tid].stoim;


            }
            insurancesList.pop_back();
        }

        return 0;
    }

};
struct AgentsDir
{
    AgentsDir()
    {

    }

    AgentsDir(int hashTableDefaultCapacity)
    {
        agentsHashTable = hashTableDefaultCapacity;
    }

    std::vector<Agent> agents;

    AgentTree agentFIOTree;
    AgentTree agentNumTree;
    AgentTree agentPerTree;
    AgentHT agentsHashTable;

    void ADD(Agent k)
    {
        insert_agent(agents, agentFIOTree, agentNumTree, agentPerTree, agentsHashTable, k.fio, k.number, k.percent, k.pass);
    }

    int LOAD(std::string filename) {

        agentFIOTree.clear(agentFIOTree.root);
        agentNumTree.clear(agentNumTree.root);
        agentPerTree.clear(agentPerTree.root);
        agents.clear();
        agentsHashTable.clear();
        std::ifstream SOURCE_FILE(filename);
        if (!SOURCE_FILE.is_open()) return 1;
        std::string line;
        while (std::getline(SOURCE_FILE, line)) {
            std::istringstream iss(line);
            Agent placeholder;

            if (!(iss >> placeholder.fio >> placeholder.number >> placeholder.percent >> placeholder.pass)) {
                return 2;
            }
            ADD(placeholder);
        }
        SOURCE_FILE.close();
        return 0;
    }

    int SAVE(std::string filename)
    {
        std::ofstream TARGET_FILE(filename);
        if (!TARGET_FILE.is_open()) return 1;
        for (int i = 0; i < agents.size(); i++) {
            TARGET_FILE << agents[i].fio << " ";
            TARGET_FILE << agents[i].number << " ";
            TARGET_FILE << agents[i].percent << " ";
            TARGET_FILE << agents[i].pass << std::endl;
        }
        TARGET_FILE.close();
        return 0;
    }

    int REMOVE(Agent k)
    {
        remove_agent(agents, agentFIOTree, agentNumTree, agentPerTree, agentsHashTable, k);
        return 0;
    }

};

#endif // DIRECTORIES_H
