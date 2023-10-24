#ifndef STRUCT_H
#define STRUCT_H
#include <string>
using namespace std;
struct key {
public:
    string agentpass;
    string clientpass;
    string strah;
    string stoim;
    int id;
    bool operator ==(const key& other)
    {
        return (this->agentpass == other.agentpass && this->clientpass == other.clientpass && this->strah == other.strah && this->stoim == other.stoim);
    }

    bool operator !=(const key& other)
    {
        return !(this->agentpass == other.agentpass && this->clientpass == other.clientpass && this->strah == other.strah && this->stoim == other.stoim);
    }
    bool operator >(const key& other)
    {
        return (this->agentpass > other.agentpass && this->clientpass > other.clientpass && this->strah > other.strah && this->stoim > other.stoim);
    }

    bool operator <(const key& other)
    {
        return !(this->agentpass < other.agentpass&& this->clientpass < other.clientpass&& this->strah < other.strah&& this->stoim < other.stoim);
    }

};

#endif // STRUCT_H
