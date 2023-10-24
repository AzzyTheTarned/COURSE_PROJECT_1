#ifndef OS_H
#define OS_H
#include <iostream>
#include <string>
#include <functional>
#include "insurancesRecord.h"
using namespace std;



struct Node {
    key val;
    Node* next;
    Node(string agentp, string clientp, string str, string sto, int index)
    {
        this->val.agentpass = agentp;
        this->val.clientpass = clientp;
        this->val.strah = str;
        this->val.stoim = sto;
        this->val.id = index;
        next = nullptr;
    }


};

struct List {
    Node* first;
    List() : first(nullptr) {}

    bool is_empty(Node* first) {
        return first == nullptr;
    }


    int find(key ins)
    {   int i =0;
        Node* z = new Node(ins.agentpass, ins.clientpass, ins.strah, ins.stoim, ins.id);
        if (!is_empty(first))
        {
            Node* p = first;
            while (p && p->val != z->val) {
                i++;
                p = p->next;
            };
            if (p && p->val == z->val)
            {
                return i;

            }





        }
    };


    void add(string agentp, string clientp, string str, string sto, int index)
    {

        Node* node = new Node(agentp, clientp, str, sto, index);

        if (first == nullptr) {
            first = node;
            return;
        }

        if (first->next == nullptr) {
            if (node->val > first->val) {
                first->next = node;
            }
            else {
                node->next = first;
                first = node;
            }

            return;
        }

        Node* current = first;
        if (node->val < current->val) {
            node->next = first;
            first = node;
            return;
        }

        while (current->next != nullptr) {
            if (node->val < current->next->val) {
                node->next = current->next;
                current->next = node;
                return;
            }

            current = current->next;
        }

        current->next = node;
    }


    key* get(int k) {

        int o = 0;
        Node* current = first;
        while (current != nullptr) {



            if (o == k) {
                return&current->val;
            }
            current = current->next;
            o++;
        }
        return nullptr;


    }

    int size() {
        int counter = 0;
        Node* jumper = first;
        while (jumper != nullptr) {
            jumper = jumper->next;
            counter++;
        }
        return counter;
    }

    void del(string agentp, string clientp, string str,string stoim) {

        Node* temp;

        Node* current = first;
        Node* First = first;

        if (agentp == current->val.agentpass && clientp == current->val.clientpass && str == current->val.strah&& stoim == current->val.stoim) {
            temp = First;
            first = current->next;
            delete temp;
            //First = nullptr;
            temp = nullptr;
        }
        else
            while (current->next != nullptr ) {
                if (agentp == current->next->val.agentpass && clientp == current->next->val.clientpass && str == current->next->val.strah && stoim==current->val.stoim) {
                    Node* helper = current->next;
                    if (current->next->next != nullptr) {
                        current->next = current->next->next;
                        delete helper;
                        helper = nullptr;

                    }
                    else
                    {

                        delete helper;
                        helper = nullptr;
                        current->next = nullptr;
                    }
                }
                else
                {
                    current = current->next;
                }

            }

    }


};
#endif // OS_H
