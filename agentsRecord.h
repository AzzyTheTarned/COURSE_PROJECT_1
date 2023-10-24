#ifndef AGENTSRECORD_H
#define AGENTSRECORD_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Agent
{
public:
    string fio;
    string number;
    int percent;
    string pass;

    Agent(string fio_, string number_, int percent_, string pass_)
    {
        fio = fio_;
        number = number_;
        percent = percent_;
        pass = pass_;
    }

    Agent()
    {
        fio = "_";
        number = "_";
        percent = 0;
        pass = "_";
    }

    bool operator==(const Agent &other)
    {
        return (this->fio == other.fio && this->number == other.number
                && this->percent == other.percent && this->pass == other.pass);
    }

    bool operator!=(const Agent &other)
    {
        return !(this->fio == other.fio && this->number == other.number
                 && this->percent == other.percent && this->pass == other.pass);
    }

    bool operator>(const Agent &other)
    {
        return ((this->fio < other.fio) || (this->fio == other.fio && this->number < other.number)
                || (this->fio == other.fio && this->number == other.number
                    && this->percent > other.percent)
                || (this->fio == other.fio && this->number == other.number
                    && this->percent == other.percent && this->pass < other.pass));
    }

    bool operator<(const Agent &other)
    {
        return ((this->fio > other.fio) || (this->fio == other.fio && this->number > other.number)
                || (this->fio == other.fio && this->number == other.number
                    && this->percent < other.percent)
                || (this->fio == other.fio && this->number == other.number
                    && this->percent == other.percent && this->pass > other.pass));
    }
};



#endif // AGENTSRECORD_H
