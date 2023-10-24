 #ifndef RECORDS_H
#define RECORDS_H
// #include <string>
// #include<iostream>
// #include <vector>
// using namespace std;
// struct Client {
//     std::string surname;
//     std::string name;
//     std::string patronymic;
//     std::string day;
//     std::string month;
//     std::string year;
//     std::string phone_number;
//     std::string ID;

//     bool operator== (Client &other) {
//         return
//             this->surname == other.surname &&
//             this->name == other.name &&
//             this->patronymic == other.patronymic &&
//             this->day == other.day &&
//             this->month == other.month &&
//             this->year == other.year &&
//             this->phone_number == other.phone_number &&
//             this->ID == other.ID;
//     }

//     bool operator!= (Client &other) {
//         return
//             this->surname != other.surname ||
//             this->name != other.name ||
//             this->patronymic != other.patronymic ||
//             this->day != other.day ||
//             this->month != other.month ||
//             this->year != other.year ||
//             this->phone_number != other.phone_number ||
//             this->ID != other.ID;
//     }

//     bool operator< (Client &other) {
//         if (this->surname < other.surname) {
//             return true;
//         }
//         else if (this->surname == other.surname) {
//             if (this->name < other.name) {
//                 return true;
//             }
//             else if (this->name == other.name) {
//                 if (this->patronymic < other.patronymic) {
//                     return true;
//                 }
//                 else if (this->patronymic == other.patronymic) {
//                     if (this->day < other.day) {
//                         return true;
//                     }
//                     else if (this->day == other.day) {
//                         if (this->month < other.month) {
//                             return true;
//                         }
//                         else if (this->month == other.month) {
//                             if (this->year < other.year) {
//                                 return true;
//                             }
//                             else if (this->year == other.year) {
//                                 if (this->phone_number < other.phone_number) {
//                                     return true;
//                                 }
//                                 else if (this->phone_number == other.phone_number) {
//                                     if (this->ID < other.ID) {
//                                         return true;
//                                     }
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//         return false;
//     }

//     bool operator> (Client &other) {
//         if (this->surname > other.surname) {
//             return true;
//         }
//         else if (this->surname == other.surname) {
//             if (this->name > other.name) {
//                 return true;
//             }
//             else if (this->name == other.name) {
//                 if (this->patronymic > other.patronymic) {
//                     return true;
//                 }
//                 else if (this->patronymic == other.patronymic) {
//                     if (this->day > other.day) {
//                         return true;
//                     }
//                     else if (this->day == other.day) {
//                         if (this->month > other.month) {
//                             return true;
//                         }
//                         else if (this->month == other.month) {
//                             if (this->year > other.year) {
//                                 return true;
//                             }
//                             else if (this->year == other.year) {
//                                 if (this->phone_number > other.phone_number) {
//                                     return true;
//                                 }
//                                 else if (this->phone_number == other.phone_number) {
//                                     if (this->ID > other.ID) {
//                                         return true;
//                                     }
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//         return false;
//     }

//     bool operator<= (Client &other) {
//         return this < &other || this == &other;
//     }

//     bool operator>= (Client &other) {
//         return this > &other || this == &other;
//     }
// };

// struct Agent {
//     std::string surname;
//     std::string name;
//     std::string patronymic;
//     std::string fee_share;
//     std::string phone_number;
//     std::string ID;

//     bool operator== (Agent &other) {
//         return
//             this->surname == other.surname &&
//             this->name == other.name &&
//             this->patronymic == other.patronymic &&
//             this->fee_share == other.fee_share &&
//             this->phone_number == other.phone_number &&
//             this->ID == other.ID;
//     }

//     bool operator!= (Agent &other) {
//         return
//             this->surname != other.surname ||
//             this->name != other.name ||
//             this->patronymic != other.patronymic ||
//             this->fee_share != other.fee_share ||
//             this->phone_number != other.phone_number ||
//             this->ID != other.ID;
//     }

//     bool operator< (Agent &other) {
//         if (this->surname < other.surname) {
//             return true;
//         }
//         else if (this->surname == other.surname) {
//             if (this->name < other.name) {
//                 return true;
//             }
//             else if (this->name == other.name) {
//                 if (this->patronymic < other.patronymic) {
//                     return true;
//                 }
//                 else if (this->patronymic == other.patronymic) {
//                     if (this->fee_share < other.fee_share) {
//                         return true;
//                     }
//                     else if (this->fee_share == other.fee_share) {
//                         if (this->phone_number < other.phone_number) {
//                             return true;
//                         }
//                         else if (this->phone_number == other.phone_number) {
//                             if (this->ID < other.ID) {
//                                 return true;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//         return false;
//     }

//     bool operator> (Agent &other) {
//         if (this->surname > other.surname) {
//             return true;
//         }
//         else if (this->surname == other.surname) {
//             if (this->name > other.name) {
//                 return true;
//             }
//             else if (this->name == other.name) {
//                 if (this->patronymic > other.patronymic) {
//                     return true;
//                 }
//                 else if (this->patronymic == other.patronymic) {
//                     if (this->fee_share > other.fee_share) {
//                         return true;
//                     }
//                     else if (this->fee_share == other.fee_share) {
//                         if (this->phone_number > other.phone_number) {
//                             return true;
//                         }
//                         else if (this->phone_number == other.phone_number) {
//                             if (this->ID > other.ID) {
//                                 return true;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//         return false;
//     }

//     bool operator<= (Agent &other) {
//         return this < &other || this == &other;
//     }

#include "insurancesRecord.h"
// };

#include <string>
#include<iostream>
#include <vector>
using namespace std;






struct Ins {
public:
    key val;

    int hash;
    int first_hash;
    int stutus = 0;
    int count;


};

class HT
{
private:
    Ins* table;

public:
    int size;
    HT() {
        size = 50;
        table = new Ins[size];
    }
    HT(int newSize)
    {
        size = newSize;
        table = new Ins[size];


    }



    int sumHs(string word, int si) {
        int sum = 0;
        for (int j = 0; si > j; j++) {
            sum = sum + char(word[j]);
        }
        return sum;
    }

    void add(string client, string agent, string type, string cost,int id) {

        Ins temp;
        temp.val.clientpass = client;
        temp.val.agentpass = agent;
        temp.val.strah = type;
        temp.val.stoim = cost;
        temp.val.id = id;
        temp.count = 0;
        int i = first_h(temp);

        if (table[i].stutus != 1) {
            table[i] = temp;
            table[i].stutus = 1;
        }
        else {
            while ((table[i].stutus == 1) && i >= 0)
                i = second_h(temp);
            table[i] = temp;
            table[i].stutus = 1;
        }

    }

    void print() {
        for (int i = 0; i != size; i++) {
            cout <<table[i].first_hash <<" " <<table[i].val.id<<" " <<table[i].val.agentpass << " " << table[i].val.clientpass << " " << table[i].val.strah << " " << table[i].val.stoim <<" "<< table[i].stutus<<" "<<table[i].hash << endl;
        }
    }

    void del(int i) {
        for (int j = 0; j<=size;j++){
            if(table[j].val.id==i && table[j].stutus ==1)
                if (j <= size) {
                    table[j].stutus = 2;
                }
        };
    }

    void clear() {

        Ins* replace = new Ins();
        for (int i = 0; i < size; i++) {
            table[i] = *replace;
        }

    }

    key find(string agent, string client, string strah) {
        Ins temp;
        int i = 0;
        key ret;
        ret.id=0;
        temp.val.agentpass = agent;
        temp.val.clientpass = client;
        temp.val.strah = strah;
        bool check = false;
        first_h(temp);
        while (check == false or i<=size)
        {


            while (i<size)
            {

                if (i>size){

                    ret.id=-1;
                    return ret;
                }

                if (temp.first_hash == table[i].first_hash&&table[i].stutus==1) {
                    if (agent == table[i].val.agentpass) {
                        if (client == table[i].val.clientpass) {
                            if (strah == table[i].val.strah) {
                                ret.agentpass=agent;
                                ret.clientpass=client;
                                ret.strah=strah;
                                ret.stoim=table[i].val.stoim;
                                ret.id=table[i].val.id;

                                return ret;
                            }
                        }
                    }
                }
                i++;
            }
            ret.id=-1;
            return ret;

        }
    }


    void replace(int id,key ins){
        int i = 0;

        Ins temp;
        temp.val.agentpass = ins.agentpass;
        temp.val.clientpass = ins.clientpass;
        temp.val.strah = ins.strah;
        bool check = false;
        first_h(temp);
        while (check == false)
        {


            while (i<size && check ==false)
            {



                if (temp.first_hash == table[i].first_hash && table[i].stutus!=2) {
                    if (ins.agentpass == table[i].val.agentpass) {
                        if (ins.clientpass == table[i].val.clientpass) {
                            if (ins.strah == table[i].val.strah) {
                                table[i].val.id = id;
                                check = true;

                            }
                        }
                    }
                }
                i++;
            }
        }
    }

    int first_h(Ins& temp2) {

        int hash;

        int strah_s = (temp2.val.strah).size();
        int agent_s = (temp2.val.agentpass).size();
        int client_s = (temp2.val.clientpass).size();
        hash = sumHs(temp2.val.strah, strah_s) + sumHs(temp2.val.agentpass,agent_s) + sumHs(temp2.val.clientpass,client_s);
        temp2.hash = hash;
        temp2.first_hash = hash;
        int temp = 0;
        while (hash > 0.01) {
            temp += hash % 100;
            hash = hash / 100;
        };
        temp = temp % size;
        temp2.count++;
        return temp;

    }
    int second_h(Ins& temp) {
        int k1, k2;
        k1 = 1;
        k2 = 2;
        int hash = (temp.hash + temp.count * k1 + temp.count ^ 2 * k2) % size;
        temp.hash = hash;
        temp.count += 1;
        return hash;
    }

};


#endif // RECORDS_H
