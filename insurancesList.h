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
    Node(int agentp, int clientp, string str, int sto)
    {
        this->val.agentpass = agentp;
        this->val.clientpass = clientp;
        this->val.strah = str;
        this->val.stoim = sto;
        next = nullptr;
    }


};

struct listt {
    Node* first;
    listt() : first(nullptr) {}

    bool is_empty(Node* first) {
        return first == nullptr;
    }


    bool find(int agentp, int clientp, string str, int sto)
    {
        Node* z = new Node(agentp, clientp, str, sto);
        if (!is_empty(first))
        {
            Node* p = first;
            while (p && p->val != z->val) p = p->next;
            if (p && p->val == z->val)
            {
                return true;
            }
            else return false;
            return (p && p->val == z->val) ? p : nullptr;
        }
        return false;
    }


    void add(int agentp, int clientp, string str, int sto)
    {

        Node* node = new Node(agentp, clientp, str, sto);

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

    void del(int agentp, int clientp, string str, int sto) {
        Node* ode = new Node(agentp,  clientp,  str,  sto);
        Node* temp;

        Node* current = first;
        Node* First = first;

        if (agentp == current->val.agentpass && clientp == current->val.clientpass && str == current->val.strah && sto == current->val.stoim) {
            temp = First;
            first = current->next;
            delete temp;
            //First = nullptr;
            temp = nullptr;
        }
        else
            while (current->next != nullptr ) {
                if (agentp == current->next->val.agentpass && clientp == current->next->val.clientpass && str == current->next->val.strah && sto == current->next->val.stoim) {
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




/*
int height(node*& croot) {
        int h1 = 0, h2 = 0;
        if (nullptr == croot) { return 0; }
        if (croot->left) { h1 = height(croot->left); }
        if (croot->right) { h1 = height(croot->right); }
        return (max(h1, h2) + 1);
}
*/



/*int main()
{
    function<int(key, key)> price_comparator = [](key k1, key k2) -> int {
        return k1.stoim -k2.stoim;
    };
    function<int(key, key)> price_co = [](key k1, key k2) -> int {
        return compare_string(k1.clientpass, k2.clientpass);
    };
    function<int(key, key)> price_com = [](key k1, key k2) -> int {
        return compare_string(k1.agentpass, k2.agentpass);
    };
    function<int(key, key)> price_comp = [](key k1, key k2) -> int {
        return compare_string(k1.strah,k2.strah);
    };
    tree tree1(price_co);
    tree tree2(price_com);
    tree tree3(price_comp);
    tree tree4(price_comparator);
    key k1;
    key k2;
    k1.agentpass = "A";
    k1.clientpass = "AAA";
    k1.stoim = 100;
    k2.agentpass = "B";
    k2.clientpass = "AAA";
    k2.stoim = 200;
    key k3;
    k3.agentpass = "C";
    k3.clientpass = "B";
    k3.stoim = 150;
    key k4;
    k4.stoim = 250;
    key k5;
    k5.stoim = 225;
    tree4.insert(k1);
    tree4.insert(k2);
    tree4.insert(k3);
    tree4.insert(k4);
    tree4.insert(k5);
    tree4.print();
    cout << endl;
    tree4.remove(k3);
    tree4.print();
    cout << endl;
}*/
#endif // OS_H
