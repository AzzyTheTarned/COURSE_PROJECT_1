#ifndef CLIENTSTREE_H
#define CLIENTSTREE_H
#include "clientsRecord.h"
#include <iostream>
#include <functional>
#include <string>

template<typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
    typedef T(fnType)(U...);
    fnType ** fnPointer = f.template target<fnType*>();
    return (size_t) *fnPointer;
}

struct NodeClientList {
    Client val;
    NodeClientList* next;
    NodeClientList(Client _val) : val(_val), next(nullptr){};
};
struct ClientList {
    NodeClientList* head;
    ClientList() : head(nullptr) {}

private:
    bool isEmpty() {
        return head == nullptr;
    }
    bool isOneItem() {
        return isEmpty() ? false : head->next == nullptr;
    }
    void removeFirst() {
        if (isEmpty()) return;
        if (isOneItem()) {
            delete head;
            head = nullptr;
            return;
        }
        NodeClientList* p = head;
        head = p->next;
        delete p;
    }
    void removeLast() {
        if (isEmpty()) return;
        if (isOneItem()) {
            delete head;
            head = nullptr;
            return;
        }
        NodeClientList* p = head;
        while (p->next->next != nullptr) p = p->next;
        delete p->next;
        p->next = nullptr;
    }
    NodeClientList* pushFirst(Client _val) {
        NodeClientList* p = new NodeClientList(_val);
        if (isEmpty()) {
            head = p;
            return p;
        }
        p->next = head;
        head = p;
        return p;
    }
    NodeClientList* pushLast(Client _val) {
        NodeClientList* p = new NodeClientList(_val);
        if (isEmpty()) {
            head = p;
            return p;
        }
        NodeClientList* i = head;
        while (i->next != nullptr) i = i->next;
        i->next = p;
        return p;
    }
public:
    void flush() {
        while (!isEmpty()) removeFirst();
    }
    void remove(Client _val) {
        if (isEmpty()) return;
        if (isOneItem()) {
            if (head->val == _val) removeFirst();
            return;
        }
        NodeClientList* p = head;
        while (p->next != nullptr && p->next->val != _val) p = p->next;
        if (p->next == nullptr) return;
        NodeClientList* toDel = p->next;
        p->next = p->next->next;
        delete toDel;
    }
    NodeClientList* push(Client _val) {
        if (isEmpty()) {
            return pushFirst(_val);
        }
        if (_val < head->val) {
            return pushFirst(_val);
        }
        if (_val == head->val) {
            return nullptr;
        }
        NodeClientList* p = head;
        while (p->next != nullptr && p->next->val <= _val) p = p->next;
        if (p->val == _val) return nullptr;
        NodeClientList* toAdd = new NodeClientList(_val);
        toAdd->next = p->next;
        p->next = toAdd;
        return toAdd;
    }
    NodeClientList* find(Client _val) {
        NodeClientList* p = head;
        while (p != nullptr && p->val != _val) p = p->next;
        return p;
    }
    void print() {
        if (isEmpty()) return;
        NodeClientList* p = head;
        while (p != nullptr) {
            std::cout << p->val.name << " - Birthday: " << p->val.birthday << " - Phone number: "
                      << p->val.phone_number << " - ID: " << p->val.ID << std::endl;
            p = p->next;
        }
        std::cout << std::endl;
    }
    void printInLine() {
        if (isEmpty()) return;
        NodeClientList* p = head;
        while (p != nullptr) {
            std::cout << "{" << p->val.name << " - Birthday: " << p->val.birthday << " - Phone number: "
                      << p->val.phone_number << " - ID: " << p->val.ID << "} ";
            p = p->next;
        }
        // std::cout << std::endl;
    }
};

// int compare_string(std::string s1, std::string s2) {
// 	int min_length = s1.size() < s2.size() ? s1.size() : s2.size();
// 	for(int index = 0; index < min_length; index++) {
// 		if(s1[index] != s2[index]) {
// 			return ((int) s1[index]) - ((int) s2[index]);
// 		}
// 	}
// 	return s2.size() - s1.size();
// }
const std::function<int(Client, Client)> compareClientName = [](Client c1, Client c2) -> int {
    // return compare_string(c1.name, c2.name);
    return -(c1.name.compare(c2.name));
};
const std::function<int(Client, Client)> compareClientBirthday = [](Client c1, Client c2) -> int {
    // return compare_string(c1.birthday, c2.birthday);
    return -(c1.birthday.compare(c2.birthday));
};
const std::function<int(Client, Client)> compareClientPhone = [](Client c1, Client c2) -> int {
    // return compare_string(c1.phone_number, c2.phone_number);
    return -(c1.phone_number.compare(c2.phone_number));
};
const std::function<int(Client, std::string)> compareToName = [](Client c, std::string s) -> int {
    // return compare_string(c.name, s);
    return -(c.name.compare(s));
};
const std::function<int(Client, std::string)> compareToBirthday = [](Client c, std::string s) -> int {
    // return compare_string(c.birthday, s);
    return -(c.birthday.compare(s));
};
const std::function<int(Client, std::string)> compareToPhone = [](Client c, std::string s) -> int {
    // return compare_string(c.phone_number, s);
    return -(c.phone_number.compare(s));
};


struct NodeClientTree {
    ClientList val;
    NodeClientTree* parent;
    NodeClientTree* left;
    NodeClientTree* right;
    bool color; // 0-black, 1-red
};

struct ClientTree {
    ClientTree(std::function<int(Client, Client)> _full_comparator, std::function<int(Client, std::string)> _semi_comparator)
    : full_comparator(_full_comparator), semi_comparator(_semi_comparator)
    {
        TNULL = new NodeClientTree;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        // full_comparator = _full_comparator;
        // semi_comparator = _semi_comparator;
    }
private:
    NodeClientTree* root;
    NodeClientTree* TNULL;
    std::function<int(Client, Client)> full_comparator;
    std::function<int(Client, std::string)> semi_comparator;

    void preOrderBase(NodeClientTree* node) {
        if (node != TNULL) {
            node->val.print();
            preOrderBase(node->left);
            preOrderBase(node->right);
        }
    }

    void inOrderBase(NodeClientTree* node) {
        if (node != TNULL) {
            inOrderBase(node->left);
            node->val.print();
            inOrderBase(node->right);
        }
    }

    void postOrderBase(NodeClientTree* node) {
        if (node != TNULL) {
            
            postOrderBase(node->left);
            postOrderBase(node->right);
            node->val.print();
        }
    }

    NodeClientTree* searchTreeBase(NodeClientTree* node, std::string key) {
        if (node == TNULL || semi_comparator(node->val.head->val, key) == 0) {
            return node;
        }
        if (semi_comparator(node->val.head->val, key) <= 0) {
            return searchTreeBase(node->left, key);
        }
        return searchTreeBase(node->right, key);
    }

    void fixDelete(NodeClientTree* x) {
        NodeClientTree* s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        // case 3.3
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        // case 3.3
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void transplant(NodeClientTree* u, NodeClientTree* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    
    int deleteNodeBase(NodeClientTree* node, std::string val) {
        NodeClientTree* z = TNULL;
        NodeClientTree* x, * y;
        while (node != TNULL) {
            if (semi_comparator(node->val.head->val, val) == 0) {
                z = node;
            }

            if (!(semi_comparator(node->val.head->val, val) <= 0)) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            std::cout << "Couldn't find key in the tree" << std::endl;
            return -1;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = maximum(z->left);
            y_original_color = y->color;
            x = y->left;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->left);
                y->left = z->left;
                y->left->parent = y;
            }

            transplant(z, y);
            y->right = z->right;
            y->right->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            fixDelete(x);
        }
        return 0;
    }

    void fixInsert(NodeClientTree* k) {
        NodeClientTree* u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // uncle
                if (u->color == 1) {
                    // case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // uncle

                if (u->color == 1) {
                    // mirror case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void printBase(NodeClientTree* root, std::string indent, bool last) {
        if (root != TNULL) {
            std::cout << indent;
            if (last) {
                std::cout << "R====";
                indent += "     ";
            } else {
                std::cout << "L====";
                indent += "|    ";
            }

            std::string sColor = root->color?"RED":"BLACK";
            // std::cout << "{" << getHours(root) << ":" << getMinutes(root) << "}" << "(" << sColor << ")" << std::endl;
            root->val.printInLine();
            printBase(root->left, indent, false);
            printBase(root->right, indent, true);
        }    
    }

    void flushBase(NodeClientTree* root) {
        if (root != TNULL) {
            flushBase(root->left);
            flushBase(root->right);
            root->val.flush();
            delete root;
            if (root->left != TNULL) root->left = TNULL;
            if (root->right != TNULL) root->right = TNULL;
            root = TNULL;
        }
    }

    int treeHeightBase (NodeClientTree* root) {
        if (root == TNULL) return 0;
        else {
            int leftHeight = treeHeightBase(root->left);
            int rightHeight = treeHeightBase(root->right);
            return std::max(leftHeight, rightHeight) + 1;
        }
    }

    NodeClientTree* getRoot() {
        return this->root;
    }
    
    void preorder() {
        preOrderBase(this->root);
    }

    void inorder() {
        inOrderBase(this->root);
    }

    void postorder() {
        postOrderBase(this->root);
    }

    NodeClientTree* minimum(NodeClientTree* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    NodeClientTree* maximum(NodeClientTree* node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    NodeClientTree* successor(NodeClientTree* x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        NodeClientTree* y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodeClientTree* predecessor(NodeClientTree* x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        NodeClientTree* y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(NodeClientTree* x) {
        NodeClientTree* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodeClientTree* x) {
        NodeClientTree* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

public:

    NodeClientTree* searchTree(std::string k) {
        return searchTreeBase(this->root, k);
    }

    void insert(Client _val) {
        NodeClientTree* y = nullptr;
        NodeClientTree* x = this->root;

        while (x!=TNULL) {
            y = x;
            if (full_comparator(_val, x->val.head->val) == 0) {
                x->val.push(_val);
                return;
            } else if (full_comparator(_val, x->val.head->val) > 0) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        NodeClientTree* node = new NodeClientTree;

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (full_comparator(_val, y->val.head->val) > 0) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    int remove(Client _val) {
        if (getAddress(full_comparator) == getAddress(compareClientName)) {
            NodeClientTree* node = searchTree(_val.name);
            if (node == TNULL) return -1;
            node->val.remove(_val);
            if (node->val.head == nullptr) {
                deleteNodeBase(this->root, _val.name);
            }
            return 0;
        } else if (getAddress(full_comparator) == getAddress(compareClientBirthday)) {
            NodeClientTree* node = searchTree(_val.birthday);
            if (node == TNULL) return -1;
            node->val.remove(_val);
            if (node->val.head == nullptr) {
                deleteNodeBase(this->root, _val.birthday);
            }
            return 0;
        } else if (getAddress(full_comparator) == getAddress(compareClientPhone)) {
            NodeClientTree* node = searchTree(_val.phone_number);
            if (node == TNULL) return -1;
            node->val.remove(_val);
            if (node->val.head == nullptr) {
                deleteNodeBase(this->root, _val.phone_number);
            }
            return 0;
        }
        // NodeClientTree* node = searchTree(_val.name);
        // if (node == TNULL) return -1;
        // node->val.remove(_val);
        // if (node->val.head == nullptr) {
        //     deleteNodeBase(this->root, _val.name);
        // }
        // return 0;
    }

    void fancyPrint() {
        if (root) {
            printBase(this->root, "", true);
        }
    }

    int getTreeHeight() {
        return treeHeightBase(this->root);
    }

    void flush() {
        flushBase(this->getRoot());
        this->root = TNULL;
    }
};
#endif // CLIENTSTREE_H
