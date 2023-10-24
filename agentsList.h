#ifndef AGENTSLIST_H
#define AGENTSLIST_H
#include"agentsRecord.h"
struct AgentListNode
{
    int id;
    Agent value;
    AgentListNode *next;

    AgentListNode()
    {
        id = -1;
        value.fio = "_";
        value.number = "_";
        value.percent = 0;
        value.pass = "_";
        next = nullptr;
    }

    AgentListNode(int id_, string fio_, string number_, int percent_, string pass_)
    {
        id = id_;
        value.fio = fio_;
        value.number = number_;
        value.percent = percent_;
        value.pass = pass_;
        next = nullptr;
    }
};

struct AgentList
{
    AgentListNode *first;

    AgentList() { first = nullptr; }

    void print(vector<Agent> &agents)
    {
        if (first != nullptr) {
            AgentListNode *p = first;
            while (p != nullptr) {
                cout << agents[p->id].fio << " " << agents[p->id].number << " " << agents[p->id].percent
                     << " " << agents[p->id].pass << endl;
                p = p->next;
            }
            cout << endl;
        }
    }

    void push_back(int id_, AgentListNode *&p)
    {
        if (first == nullptr) {
            first = p;
            first->id = id_;
        } else {
            AgentListNode *pval = first;
            AgentListNode *pnext = first->next;
            while (pnext != nullptr) {
                pval = pval->next;
                pnext = pnext->next;
            }
            pval->next = p;
            pval->next->id = id_;
        }
    }

    void remove_first()
    {
        if (first != nullptr) {
            AgentListNode *p = first;
            first = p->next;
            delete p;
        }
    }

    void remove(int id_, string fio_, string number_, int percent_, string pass_)
    {
        AgentListNode *p = new AgentListNode(id_, fio_, number_, percent_, pass_);
        if (first != nullptr) {
            if (first->value == p->value) {
                remove_first();
                return;
            }
            AgentListNode *pfirst = first;
            AgentListNode *pnext = first->next;
            while (pnext && pnext->value != p->value) {
                pnext = pnext->next;
                pfirst = pfirst->next;
            }
            pfirst->next = pnext->next;
            delete pnext;
        }
    }

    void clear()
    {
        while (first != nullptr) {
            AgentListNode *current = first;
            first = first->next;
            delete current;
        }
    }
};
#endif // AGENTSLIST_H
