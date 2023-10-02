#ifndef INSURANCESRECORD_H
#define INSURANCESRECORD_H
#include <string>
using namespace std;
//struct Insurance {
//public:
//    int agentpass;
//    int clientpass;
//    string strah;
//    int stoim;

//    bool operator ==(const Insurance& other)
//    {
//        return (this->agentpass == other.agentpass && this->clientpass == other.clientpass && this->strah == other.strah && this->stoim == other.stoim);
//    }

//    bool operator !=(const Insurance& other)
//    {
//        return !(this->agentpass == other.agentpass && this->clientpass == other.clientpass && this->strah == other.strah && this->stoim == other.stoim);
//    }
//    bool operator >(const Insurance& other)
//    {
//        return (this->agentpass > other.agentpass && this->clientpass > other.clientpass && this->strah > other.strah && this->stoim > other.stoim);
//    }

//    bool operator <(const Insurance& other)
//    {
//        return !(this->agentpass < other.agentpass&& this->clientpass < other.clientpass&& this->strah < other.strah&& this->stoim < other.stoim);
//    }

//};

struct Insurance {
public:
    string agentpass;
    string clientpass;
    string strah;
    int stoim;

    bool operator ==(const Insurance& other)
    {
        return (this->agentpass == other.agentpass && this->clientpass == other.clientpass && this->strah == other.strah && this->stoim == other.stoim);
    }

    bool operator !=(const Insurance& other)
    {
        return !(this->agentpass == other.agentpass && this->clientpass == other.clientpass && this->strah == other.strah && this->stoim == other.stoim);
    }
    bool operator >(const Insurance& other)
    {
        return (this->agentpass > other.agentpass && this->clientpass > other.clientpass && this->strah > other.strah && this->stoim > other.stoim);
    }

    bool operator <(const Insurance& other)
    {
        return !(this->agentpass < other.agentpass&& this->clientpass < other.clientpass&& this->strah < other.strah&& this->stoim < other.stoim);
    }

};

#endif // INSURANCESRECORD_H
