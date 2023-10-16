#ifndef STRUCT_H
#define STRUCT_H
#include <string>
using namespace std;
struct key {
public:
    int agentpass;
    int clientpass;
    string strah;
    int stoim;

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
