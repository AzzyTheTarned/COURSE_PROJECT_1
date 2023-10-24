#ifndef AGENTSTREE_H
#define AGENTSTREE_H
#include "agentsList.h"
struct AgentTreeNode
{
    int id;
    Agent value;

    AgentTreeNode *left;
    AgentTreeNode *right;
    AgentList clones;

    int count;

    AgentTreeNode()
    {
        id = -1;
        value.fio = "_";
        value.number = "_";
        value.percent = 0;
        value.pass = "_";
        left = nullptr;
        right = nullptr;

        count = 0;
    }

    AgentTreeNode(int id_, string fio_, string number_, int percent_, string pass_)
    {
        id = id_;
        value.fio = fio_;
        value.number = number_;
        value.percent = percent_;
        value.pass = pass_;
        left = nullptr;
        right = nullptr;

        count = 0;
    }

    AgentTreeNode(string fio_, string number_, int percent_, string pass_)
    {
        id = -1;
        value.fio = fio_;
        value.number = number_;
        value.percent = percent_;
        value.pass = pass_;
        left = nullptr;
        right = nullptr;

        count = 0;
    }
};

struct AgentTree
{
    AgentTreeNode *root;

    AgentTree() { root = nullptr; }

    void insert(int id_, string fio_, string number_, int percent_, string pass_, AgentTreeNode *&proot)
    {
        AgentTreeNode *p = new AgentTreeNode(id_, fio_, number_, percent_, pass_);
        if (proot == nullptr) {
            proot = p;
        } else if (p->value < proot->value) {
            insert(id_, fio_, number_, percent_, pass_, proot->left);
        } else if (p->value > proot->value) {
            insert(id_, fio_, number_, percent_, pass_, proot->right);
        } else if (p->value == proot->value) {
            AgentListNode *z = new AgentListNode();
            z->value = p->value;
            proot->count++;
            proot->clones.push_back(id_, z);
        }
    }

    void clear(AgentTreeNode *&proot)
    {
        if (proot != nullptr) {
            clear(proot->left);
            clear(proot->right);
            proot->clones.clear();
            delete proot;
            proot = nullptr;
        }
    }

    void print(AgentTreeNode *&proot, int h)
    {
        if (proot != nullptr) {
            print(proot->right, h + 10);
            for (int i = 1; i <= h; i++)
                cout << " ";
            cout << proot->value.fio << " " << proot->value.number << " " << proot->value.percent
                 << " " << proot->value.pass << " | ID: " << proot->id
                 << " | clones: " << proot->count << endl;
            print(proot->left, h + 10);
        }
    }

    AgentTreeNode* find(string fio_, string number_, int percent_, string pass_, AgentTreeNode *&proot)
    {
        AgentTreeNode *p = new AgentTreeNode(fio_, number_, percent_, pass_);
        if (proot != nullptr) {
            if (p->value < proot->value) {
                return find(fio_, number_, percent_, pass_, proot->left);
            } else if (p->value > proot->value) {
                return find(fio_, number_, percent_, pass_, proot->right);
            } else if (p->value == proot->value) {
                return proot;
            }
        }
    }

    AgentTreeNode *find_min(AgentTreeNode *&proot)
    {
        if (proot != nullptr) {
            AgentTreeNode *min = proot;
            if ((proot->left != nullptr) && (proot->left->value < proot->value)) {
                min = proot->left;
                find_min(proot->left);
            } else if (proot->left == nullptr)
                return min;
        }
    }

    void remove(int id_, string fio_, string number_, int percent_, string pass_, AgentTreeNode *&proot)
    {
        AgentTreeNode *z = new AgentTreeNode(id_, fio_, number_, percent_, pass_);
        if (proot != nullptr) {
            if ((proot->value == z->value) && (proot->id == z->id)) {
                if (proot->clones.first == nullptr) {
                    if (proot->left == nullptr && proot->right == nullptr) {
                        delete proot;
                        proot = nullptr;
                    } else if (proot->left != nullptr && proot->right == nullptr) {
                        AgentTreeNode *pleft = proot;
                        proot = proot->left;
                        delete pleft;
                    } else if (proot->left == nullptr && proot->right != nullptr) {
                        AgentTreeNode *pright = proot;
                        proot = proot->right;
                        delete pright;
                    } else if (proot->left != nullptr && proot->right != nullptr) {
                        AgentTreeNode *p = find_min(proot->right);
                        AgentTreeNode *n = proot->left;
                        proot = p;
                        p->left = n;
                    }
                } else if (proot->clones.first != nullptr) {
                    AgentTreeNode *zamena = new AgentTreeNode(id_, fio_, number_, percent_, pass_);
                    zamena->clones = proot->clones;
                    zamena->id = zamena->clones.first->id;
                    zamena->value = zamena->clones.first->value;
                    zamena->clones.remove_first();
                    zamena->count = proot->count - 1;
                    zamena->left = proot->left;
                    zamena->right = proot->right;
                    proot = zamena;
                }
            } else if ((proot->value == z->value) && (proot->id != z->id)) {
                proot->count--;
                proot->clones.remove(id_, fio_, number_, percent_, pass_);
            } else if (z->value < proot->value)
                remove(id_, fio_, number_, percent_, pass_, proot->left);
            else if (z->value > proot->value)
                remove(id_, fio_, number_, percent_, pass_, proot->right);
        }
    }
};







#endif // AGENTSTREE_H
