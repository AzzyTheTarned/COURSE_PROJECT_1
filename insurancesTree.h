#ifndef INSURANCESTREE_H
#define INSURANCESTREE_H

#include <iostream>
#include <string>
#include <functional>
#include "insurancesRecord.h"
using namespace std;


int compare_string(string s1, string s2) {
    int min_length = s1.size() < s2.size() ? s1.size() : s2.size();
    for (int index = 0; index < min_length; index++) {
        if (s1[index] != s2[index]) {
            return ((int)s1[index]) - ((int)s2[index]);
        }
    }
    return s2.size() - s1.size();
}

struct Node {
    Insurance val;
    Node* next;
    Node(string agentp, string clientp, string str, int sto)
    {
        this->val.agentpass = agentp;
        this->val.clientpass = clientp;
        this->val.strah = str;
        this->val.stoim = sto;
        next = nullptr;
    }


};

struct List {
    Node* first;
    List() : first(nullptr) {}

    bool is_empty(Node* first) {
        return first == nullptr;
    }


    bool find(string agentp, string clientp, string str, int sto)
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


    void add(string agentp, string clientp, string str, int sto)
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


    Insurance* get(int k) {

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

    void del(string agentp, string clientp, string str, int sto) {
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

struct node
{

    node* left;
    node* right;
    List data;
    node(Insurance k) : left(nullptr), right(nullptr) {
        data.add(k.agentpass, k.clientpass, k.strah, k.stoim);
    }
};


struct tree
{
    node* root;
    const function<int(Insurance, Insurance)> comparator;

    tree() : root(nullptr), comparator([](Insurance k1, Insurance k2) -> int {
            int agent_pass_compare_result = compare_string(k1.agentpass, k2.agentpass);
            if (agent_pass_compare_result != 0) return agent_pass_compare_result;
            return compare_string(k1.clientpass, k2.clientpass);
        }) {}

    tree(function<int(Insurance, Insurance)> _comparator) : root(nullptr), comparator(_comparator) {}

    void insert(Insurance insertable_key) {
        insert(insertable_key, root);
    }

    void insert(Insurance insertable_key, node*& croot)
    {
        if (croot == nullptr)
        {
            croot = new node(insertable_key);
            return;
        }
        Insurance comparable_key = *croot->data.get(0);
        if (this->comparator(insertable_key, comparable_key) < 0)
        {
            if (croot->left != nullptr) insert(insertable_key, croot->left);
            else croot->left = new node(insertable_key);
        }
        else if (this->comparator(insertable_key, comparable_key) > 0)
        {
            if (croot->right != nullptr)
            {
                insert(insertable_key, croot->right);
            }
            else
            {
                croot->right = new node(insertable_key);
            }
        }
        else {
            croot->data.add(insertable_key.agentpass, insertable_key.clientpass, insertable_key.strah, insertable_key.stoim);
        }
    }




    /*
    void clear(node*& croot)
    {
            if (croot != nullptr)
            {
                    clear(croot->left);
                    clear(croot->right);
                    delete croot;
                    croot = nullptr;
            }

                  }

      */

    void print() {
        print(root, 0);
    }

    void print(node*& croot, int h)
    {
        if (croot != nullptr)
        {
            print(croot->right, h + 4);
            for (int i = 1; i <= h; i++) cout << " ";
            node* temp = croot;
            Insurance k = *temp->data.get(0);
            cout << '[' << k.agentpass << ' ' << k.clientpass << ' ' << k.strah << ' ' << k.stoim << " ] size: " << temp->data.size();
            cout << endl;
            print(croot->left, h + 4);
        }
    }


    /*	node* find(key insertable_key, node*& croot)
            {
                    if (croot != nullptr)
                    {

                                  if ((hh < croot->hours) || (hh == croot->hours && mm < croot->minutes))
                                  {
                                          if (hh == croot->hours && mm == croot->minutes)
                                          {
                                                  return croot;
                                          }
                                          else find(hh, mm, croot->left);
                                  }
                                  else if ((hh >= croot->hours) || (hh == croot->hours && mm >= croot->minutes))
                                  {
                                          if (hh == croot->hours && mm == croot->minutes)
                                          {
                                                  return croot;
                                          }
                                          else find(hh, mm, croot->right);
                                  }
                          }
                  }*/
    void find_min(node*& croot, node*& ins) {
        node* pre;
        find_min(croot, ins, pre);
    }
    void find_min(node*& croot , node*& ins , node*&pre)
    {
        if (croot != nullptr)
        {
            node* min = croot;

            if (croot->left != nullptr) {
                Insurance comparable_key_l = *croot->left->data.get(0);

                Insurance comparable_key = *croot->data.get(0);

                if ((croot->left != nullptr) && ((this->comparator(comparable_key_l, comparable_key) < 0)))
                {
                    min = croot->left;
                    pre = croot;
                    find_min(croot->left, ins, pre);

                }
            }
            else if (croot->left == nullptr) {
                ins->data = croot->data;
                if (croot->right != nullptr) {
                    pre->left = croot->right;
                }
                else {


                    delete croot;
                    pre->left = nullptr;
                }
            }

        }
    }

    void remove(Insurance ins) {
        remove(ins, root);
    }
    void remove(Insurance ins, node*& croot)
    {
        if (croot != nullptr)
        {
            Insurance comparable = *croot->data.get(0);
            if (this->comparator(comparable,ins) == 0 and (croot->data.get(1) == nullptr))
            {
                if (ins.agentpass == comparable.agentpass && ins.clientpass == comparable.clientpass && ins.stoim == comparable.stoim && ins.strah == comparable.strah) {
                    if (croot->left == nullptr && croot->right == nullptr)
                    {
                        delete croot;
                        croot = nullptr;
                    }
                    else if (croot->left != nullptr && croot->right == nullptr)
                    {
                        node* pleft = croot;
                        croot = croot->left;
                        delete pleft;
                    }
                    else if (croot->left == nullptr && croot->right != nullptr)
                    {
                        node* pright = croot;
                        croot = croot->right;
                        delete pright;
                    }
                    else if (croot->left != nullptr && croot->right != nullptr)
                    {
                        find_min(croot->right,croot);



                    }
                }
            }
            else if ((this->comparator(comparable, ins) == 0) and (croot->data.get(1) != nullptr)) {

                croot->data.del(ins.agentpass,ins.clientpass,ins.strah, ins.stoim);
            }
            else if (this->comparator(ins , comparable) <0 ) remove(ins, croot->left);
            else if (this->comparator(ins, comparable) > 0) remove(ins, croot->right);
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


#endif // INSURANCESTREE_H
