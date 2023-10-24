#ifndef BDP_H
#define BDP_H
#include <insurancesList.h>
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
    return compare_string(k1.stoim , k2.stoim);
};
const function<int(key, key)> price_co = [](key k1, key k2) -> int {
    //    return compare_string(k1.clientpass, k2.clientpass);
    return compare_string(k1.clientpass,k2.clientpass);
};
const function<int(key, key)> price_com = [](key k1, key k2) -> int {
    //    return compare_string(k1.agentpass, k2.agentpass);
    return compare_string(k1.agentpass,k2.agentpass);
};
const function<int(key, key)> price_comp = [](key k1, key k2) -> int {
    return compare_string(k1.strah,k2.strah);
};
struct node
{

    node* left;
    node* right;
    List data;
    node(key k) : left(nullptr), right(nullptr) {
        data.add(k.agentpass, k.clientpass, k.strah, k.stoim,k.id);
    }
};


struct tree
{
    node* root;
    const function<int(key, key)> comparator;

    tree() : root(nullptr), comparator([](key k1, key k2) -> int {
            int agent_pass_compare_result = compare_string(k1.agentpass, k2.agentpass);
            if (agent_pass_compare_result != 0) return agent_pass_compare_result;
            int client_pass_compare_result =compare_string(k1.clientpass, k2.clientpass);
            if (client_pass_compare_result != 0) return client_pass_compare_result;
            int strah_pass_compare_result =compare_string(k1.strah, k2.strah);
            if (strah_pass_compare_result != 0) return strah_pass_compare_result;
            int stoim_pass_compare_result =compare_string(k1.stoim, k2.stoim);
            if (stoim_pass_compare_result != 0) return stoim_pass_compare_result;
        }) {}

    tree(function<int(key, key)> _comparator) : root(nullptr), comparator(_comparator) {}


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
            croot->data.add(insertable_key.agentpass, insertable_key.clientpass, insertable_key.strah, insertable_key.stoim, insertable_key.id);
        }
    }


    void clear() {
        clear(root);
    }


    void clear(node*& croot)
    {
        if (croot!= nullptr and croot->data.get(1)!=nullptr) {
            int j = 0;
            while (croot->data.get(j) != nullptr) {
                key* temp = croot->data.get(j);
                croot->data.del(temp->agentpass, temp->clientpass, temp->strah,temp->stoim);
                j++;
            }
        }
        if (croot != nullptr)
        {
            clear(croot->left);
            clear(croot->right);
            delete croot;
            croot = nullptr;
        }

    }



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
            cout << '[' << k.agentpass << ' ' << k.clientpass << ' ' << k.strah << ' ' << k.stoim <<" "<<k.id<< " ] size: " << temp->data.size();
            cout << endl;
            print(croot->left, h + 4);
        }
    }


    node* find(key insertable_key , node*& croot,node*tmeph)
    {
        if(croot == nullptr){            node* cur= nullptr;
            return cur;}
        key temp = *croot->data.get(0);
        if (croot != nullptr)
        {
            if (this->comparator(insertable_key,temp)<0)
            {
                if(croot == nullptr){            node* cur= nullptr;
                    return cur;}
                return find(insertable_key, croot->left,tmeph);

            }
            else if (this->comparator(insertable_key,temp)>0)
            {
                if(croot == nullptr){            node* cur= nullptr;
                    return cur;}
                return find(insertable_key, croot->right,tmeph);
            }
            else if (this->comparator(insertable_key,temp)==0)
            {

                tmeph=croot;
                return tmeph;

            }

        }

        node* cur= nullptr;
        return cur;
    }

    void last_to_ind(key ins, int ind,node*& croot ){
        if (croot != nullptr)
        {
            key comparable = *croot->data.get(0);
            if (this->comparator(comparable,ins) == 0 and (croot->data.get(1) == nullptr))
            {
                croot->data.get(0)->id = ind;
            }
            else if ((this->comparator(comparable, ins) == 0) and (croot->data.get(1) != nullptr)) {
                int temp;

                temp = croot->data.find(ins);
                croot->data.get(temp)->id = ind;
            }
            else if (this->comparator(ins , comparable) <0 ) last_to_ind(ins, ind,croot->left);
            else if (this->comparator(ins, comparable) > 0) last_to_ind(ins, ind,croot->right);
        }
    }


    int find_k(key insertable_key, node*& croot)

    {
        int k = 0;
        if (croot != nullptr)
        {
            key comparable_key = *croot->data.get(0);
            if ((comparator(insertable_key, comparable_key) < 0))
            {
                k++;
                if (comparator(insertable_key, comparable_key) == 0)
                {
                    return k;
                }
                else return find_k(insertable_key, croot->left);
            }
            else if (comparator(insertable_key, comparable_key) >= 0)
            {
                k++;
                if (comparator(insertable_key, comparable_key) == 0)
                {
                    return k;
                }
                else return find_k(insertable_key, croot->right);
            }
        }

        return k;
    }

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



int height(node*& croot) {
    int h1 = 0, h2 = 0;
    if (nullptr == croot) { return 0; }
    if (croot->left) { h1 = height(croot->left); }
    if (croot->right) { h1 = height(croot->right); }
    return (max(h1, h2) + 1);
}
#endif // BDP_H
