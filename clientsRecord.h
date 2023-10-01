#ifndef CLIENTSRECORD_H
#define CLIENTSRECORD_H
#include <string>

struct Client {
    std::string name;
    std::string birthday;
    std::string phone_number;
    int ID;

    bool operator== (const Client &other) const {
        return
            this->name == other.name &&
            this->birthday == other.birthday &&
            this->phone_number == other.phone_number &&
            this->ID == other.ID;
    }

    bool operator!= (const Client &other) const {
        return
            this->name != other.name ||
            this->birthday != other.birthday ||
            this->phone_number != other.phone_number ||
            this->ID != other.ID;
    }

    bool operator< (const Client &other) const {
        if (this->name < other.name) {
            return true;
        }
        else if (this->name == other.name) {
            if (this->birthday < other.birthday) {
                return true;
            }
            else if (this->birthday == other.birthday) {
                if (this->phone_number < other.phone_number) {
                    return true;
                }
                else if (this->phone_number == other.phone_number) {
                    if (this->ID < other.ID) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator> (const Client &other) const {
        if (this->name > other.name) {
            return true;
        }
        else if (this->name == other.name) {
            if (this->birthday > other.birthday) {
                return true;
            }
            else if (this->birthday == other.birthday) {
                if (this->phone_number > other.phone_number) {
                    return true;
                }
                else if (this->phone_number == other.phone_number) {
                    if (this->ID > other.ID) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator<= (const Client &other) const {
        return this < &other || this == &other;
    }

    bool operator>= (const Client &other) const {
        return this > &other || this == &other;
    }
};

#endif // CLIENTSRECORD_H
