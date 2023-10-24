#ifndef AGENTSHASH_H
#define AGENTSHASH_H
#include"agentsTree.h"

struct AgentHTNode
{
    Agent value;

    int status;
    int j;
    int id;

    AgentHTNode(string fio_, string number_, int percent_, string pass_)
    {
        id = -1;
        status = 0;
        j = 1;

        value.fio = fio_;
        value.number = number_;
        value.percent = percent_;
        value.pass = pass_;
    }

    AgentHTNode()
    {
        id = -1;
        status = 0;
        j = 1;

        value.fio = "_";
        value.number = "_";
        value.percent = 0;
        value.pass = "_";
    }

    int hash_count()
    {
        int hash = 0;

        int length = value.fio.size();
        for (int i = 0; i < length; i++) {
            hash += char(value.fio[i]);
        }

        length = value.number.size();
        for (int i = 0; i < length; i++) {
            hash += char(value.number[i]);
        }

        hash += value.percent;

        length = value.pass.size();
        for (int i = 0; i < length; i++) {
            hash += char(value.pass[i]);
        }

        return hash;
    }
};

class AgentHT
{
public:
    int tabsize;
    AgentHTNode *table;

    AgentHT()
    {
        tabsize = 50;
        table = new AgentHTNode[tabsize];
    }

    AgentHT(int tabsize_)
    {
        tabsize = tabsize_;
        table = new AgentHTNode[tabsize];
    }

    ~AgentHT() { }

    void print()
    {
        for (int i = 0; i < tabsize; i++) {
            cout << table[i].value.fio << " " << table[i].value.number << " "
                 << table[i].value.percent << " " << table[i].value.pass
                 << " | status: " << table[i].status << " | ID: " << table[i].id << endl;
        }
    }

    int first_hf(AgentHTNode &node) { return (node.hash_count() % tabsize); }

    int second_hf(AgentHTNode &node) { return ((first_hf(node) + node.j) % tabsize); }

    void insert(int id_, string fio_, string number_, int percent_, string pass_)
    {
        AgentHTNode *p = new AgentHTNode(fio_, number_, percent_, pass_);
        if (table[first_hf(*p)].status != 1) {
            table[first_hf(*p)] = *p;
            table[first_hf(*p)].status = 1;
            table[first_hf(*p)].id = id_;
        } else if ((table[first_hf(*p)].status) == 1) {
            while (table[second_hf(*p)].status == 1) {
                p->j++;
            }
            table[second_hf(*p)] = *p;
            table[second_hf(*p)].status = 1;
            table[second_hf(*p)].id = id_;
        }
        delete p;
    }

    void remove(string fio_, string number_, int percent_, string pass_)
    {
        AgentHTNode *p = new AgentHTNode(fio_, number_, percent_, pass_);
        AgentHTNode *replace = new AgentHTNode();
        if (table[first_hf(*p)].status == 1) {
            while (table[second_hf(*p)].value != p->value) {
                p->j++;
            }
            table[second_hf(*p)] = *replace;
            table[second_hf(*p)].status = 2;
        }
        delete p;
    }

    AgentHTNode *find(string pass_)
    {
        int i = 0;
        while (table[i].value.pass != pass_ && i < tabsize) {
            i++;
        }
        if (table[i].value.pass == pass_) {
            return &table[i];
        } else {
            return nullptr;
        }
    }

    void clear()
    {
        AgentHTNode *replace = new AgentHTNode();
        for (int i = 0; i < tabsize; i++) {
            table[i] = *replace;
        }
    }
};

void read(const string &file_path, vector<Agent> &agents)
{
    ifstream file(file_path);
    if (!file.is_open()) {
        cout << "Failed to open file: " << file_path << endl;
        return;
    }

    string str;
    while (getline(file, str)) {
        istringstream ss(str);
        Agent k;
        ss >> k.fio >> k.number >> k.percent >> k.pass;
        agents.push_back(k);
    }
    file.close();
}

void write(const string &file_path, const vector<Agent> &agents)
{
    ofstream file(file_path);
    if (!file.is_open()) {
        cout << "Failed to open file: " << file_path << endl;
        return;
    }
    for (const auto &Agent : agents) {
        file << Agent.fio << " " << Agent.number << " " << Agent.percent << " " << Agent.pass << endl;
    }
    file.close();
}

void fill_agents(
    vector<Agent> agents_, AgentTree &fio_tree, AgentTree &number_tree, AgentTree &percent_tree,
    AgentHT &pass_hashtab) // функция используется в самом начале, после заполнения массива
{
    for (int i = 0; i < agents_.size(); i++) // заполняем fio_tree
    {
        fio_tree.insert(i, agents_[i].fio, "_", 0, "_", fio_tree.root);
    }
    for (int i = 0; i < agents_.size(); i++) // заполняем number_tree
    {
        number_tree.insert(i, "_", agents_[i].number, 0, "_", number_tree.root);
    }
    for (int i = 0; i < agents_.size(); i++) // заполняем percent_tree
    {
        percent_tree.insert(i, "_", "_", agents_[i].percent, "_", percent_tree.root);
    }
    for (int i = 0; i < agents_.size(); i++) // заполняем pass_hashtab
    {
        pass_hashtab.insert(i, agents_[i].fio, agents_[i].number, agents_[i].percent, agents_[i].pass);
    }
}

void insert_agent(vector<Agent> &agents_, AgentTree &fio_tree, AgentTree &number_tree, AgentTree &percent_tree,
                  AgentHT &pass_hashtab, string fio_, string number_, int percent_, string pass_)
{
    Agent insertable(fio_, number_, percent_, pass_);
    agents_.push_back(insertable);
    int id_ = agents_.size() - 1;

    fio_tree.insert(id_, fio_, "_", 0, "_", fio_tree.root);

    number_tree.insert(id_, "_", number_, 0, "_", number_tree.root);

    percent_tree.insert(id_, "_", "_", percent_, "_", percent_tree.root);

    pass_hashtab.insert(id_, fio_, number_, percent_, pass_);
}

/*void find_agent_fio(AgentTree fio_tree, string fio_, vector<Agent> &agents_)
{
    fio_tree.find(fio_, "_", 0, "_", fio_tree.root, agents_);
}

void find_agent_number(AgentTree number_tree, string number_, vector<Agent> &agents_)
{
    number_tree.find("_", number_, 0, "_", number_tree.root, agents_);
}

void find_agent_percent(AgentTree percent_tree, int percent_, vector<Agent> &agents_)
{
    percent_tree.find("_", "_", percent_, "_", percent_tree.root, agents_);
}*/

void find_agent_pass(AgentHT ht, string pass_)
{
    ht.find(pass_);
}

void remove_agent(vector<Agent> &agents_, AgentTree &fio_tree, AgentTree &number_tree, AgentTree &percent_tree,
                  AgentHT &pass_hashtab, Agent k)
{
    int id = pass_hashtab.find(k.pass)->id;

    fio_tree.remove(id, k.fio, "_", 0, "_", fio_tree.root);
    number_tree.remove(id, "_", k.number, 0, "_", number_tree.root);
    percent_tree.remove(id, "_", "_", k.percent, "_", percent_tree.root);
    pass_hashtab.remove(k.fio, k.number, k.percent, k.pass);

    agents_.erase(agents_.begin() + id);

    fio_tree.clear(fio_tree.root);
    number_tree.clear(number_tree.root);
    percent_tree.clear(percent_tree.root);
    pass_hashtab.clear();

    fill_agents(agents_, fio_tree, number_tree, percent_tree, pass_hashtab);
}







#endif // AGENTSHASH_H
