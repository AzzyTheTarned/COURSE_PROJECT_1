#ifndef BDP_H
#define BDP_H
#include <insurancesList.h>
struct node
{

    node* left;
    node* right;
    listt data;
    node(key k) : left(nullptr), right(nullptr) {
        data.add(k.agentpass, k.clientpass, k.strah, k.stoim);
    }
};

int compare_string(string s1, string s2) {
    int min_length = s1.size() < s2.size() ? s1.size() : s2.size();
    for (int index = 0; index < min_length; index++) {
        if (s1[index] != s2[index]) {
            return ((int)s1[index]) - ((int)s2[index]);
        }
    }
    return s2.size() - s1.size();
}

const function<int(key, key)> price_comparator = [](key k1, key k2) -> int {
    return k1.stoim - k2.stoim;
};
const function<int(key, key)> price_co = [](key k1, key k2) -> int {
//    return compare_string(k1.clientpass, k2.clientpass);
    return k1.clientpass - k2.clientpass;
};
const function<int(key, key)> price_com = [](key k1, key k2) -> int {
//    return compare_string(k1.agentpass, k2.agentpass);
    return k1.agentpass - k2.agentpass;
};
const function<int(key, key)> price_comp = [](key k1, key k2) -> int {
    return compare_string(k1.strah,k2.strah);
};

struct tree
{
    node* root;
    const function<int(key, key)> comparator;

    tree() : root(nullptr), comparator([](key k1, key k2) -> int {
            int agent_pass_compare_result = compare_string(k1.strah, k2.strah);
            if (agent_pass_compare_result != 0) return agent_pass_compare_result;
            //return compare_string(k1.clientpass, k2.clientpass);
        }) {}
    tree(function<int(key, key)> _comparator) : root(nullptr), comparator(_comparator) {}\




    void insert(key insertable_key) {
        insert(insertable_key, root);
    }

    void insert(key insertable_key, node*& croot)
    {
        if (croot == nullptr)
        {
            croot = new node(insertable_key);
            return;
        }
        key comparable_key = *croot->data.get(0);
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
            key k = *temp->data.get(0);
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
                key comparable_key_l = *croot->left->data.get(0);

                key comparable_key = *croot->data.get(0);

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

    void remove(key ins) {
        remove(ins, root);
    }
    void remove(key ins, node*& croot)
    {
        if (croot != nullptr)
        {
            key comparable = *croot->data.get(0);
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
#endif // BDP_H
