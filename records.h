#ifndef RECORDS_H
#define RECORDS_H
#include <string>

/* Assigned to Alexey Aliferov */
struct Client {
    std::string name;
    std::string birthday;
    std::string phone_number;
    std::string ID;

    bool operator== (Client &other) {
        return
            this->name == other.name &&
            this->birthday == other.birthday &&
            this->phone_number == other.phone_number &&
            this->ID == other.ID;
    }

    bool operator!= (Client &other) {
        return
            this->name != other.name ||
            this->birthday != other.birthday ||
            this->phone_number != other.phone_number ||
            this->ID != other.ID;
    }

    bool operator< (Client &other) {
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

    bool operator> (Client &other) {
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

    bool operator<= (Client &other) {
        return this < &other || this == &other;
    }

    bool operator>= (Client &other) {
        return this > &other || this == &other;
    }
};

/* Assigned to Alexey Popov */
struct Agent {
    std::string name;
    std::string fee_share;
    std::string phone_number;
    std::string ID;

    bool operator== (Agent &other) {
        return
            this->name == other.name &&
            this->fee_share == other.fee_share &&
            this->phone_number == other.phone_number &&
            this->ID == other.ID;
    }

    bool operator!= (Agent &other) {
        return
            this->name != other.name ||
            this->fee_share != other.fee_share ||
            this->phone_number != other.phone_number ||
            this->ID != other.ID;
    }

    bool operator< (Agent &other) {
        if (this->name < other.name) {
            return true;
        }
        else if (this->name == other.name) {
            if (this->fee_share < other.fee_share) {
                return true;
            }
            else if (this->fee_share == other.fee_share) {
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

    bool operator> (Agent &other) {
        if (this->name > other.name) {
            return true;
        }
        else if (this->name == other.name) {
            if (this->fee_share > other.fee_share) {
                return true;
            }
            else if (this->fee_share == other.fee_share) {
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

    bool operator<= (Agent &other) {
        return this < &other || this == &other;
    }

    bool operator>= (Agent &other) {
        return this > &other || this == &other;
    }
};

/* Assigned to Miroslav Alekseev */
struct Insurance {
    std::string type;
    std::string cost;
    std::string client_ID;
    std::string agent_ID;

    bool operator== (Insurance &other) {
        return
            this->type == other.type &&
            this->cost == other.cost &&
            this->client_ID == other.client_ID &&
            this->agent_ID == other.agent_ID;
    }

    bool operator!= (Insurance &other) {
        return
            this->type != other.type ||
            this->cost != other.cost ||
            this->client_ID != other.client_ID ||
            this->agent_ID != other.agent_ID;
    }

    bool operator< (Insurance &other) {
        if (this->type < other.type) {
            return true;
        }
        else if (this->type == other.type) {
            if (this->cost < other.cost) {
                return true;
            }
            else if (this->cost == other.cost) {
                if (this->client_ID < other.client_ID) {
                    return true;
                }
                else if (this->client_ID == other.client_ID) {
                    if (this->agent_ID < other.agent_ID) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator> (Insurance &other) {
        if (this->type > other.type) {
            return true;
        }
        else if (this->type == other.type) {
            if (this->cost > other.cost) {
                return true;
            }
            else if (this->cost == other.cost) {
                if (this->client_ID > other.client_ID) {
                    return true;
                }
                else if (this->client_ID == other.client_ID) {
                    if (this->agent_ID > other.agent_ID) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator<= (Insurance &other) {
        return this < &other || this == &other;
    }

    bool operator>= (Insurance &other) {
        return this > &other || this == &other;
    }
};

#endif // RECORDS_H
