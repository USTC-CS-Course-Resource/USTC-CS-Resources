/*
 * BTree: for B- Tree.
 */

#pragma once

class Result {
public:
    BTree* t;
    int i;
    bool tag;
    Result() : t(nullptr), i(-1), tag(false) {};
    Result(BTree* t, int i, bool tag) :t(t), i(i), tag(tag) {};
};

class BTree {
public:

    static const int m = 3; // the order of the BTree
    int keynum;
    BTree* parent;
    int key[m + 1]; //key[0] not used.
    BTree* child[m]; // elements in child[i] > key[i]
    int record[m]; //for the records

    Result Search(int key);
};


Result BTree::Search(int key) {
    BTree* p = this;
    BTree* q = nullptr;
    bool found = false; 
    int i = 0;
    while (p && !found) {
        int i = 0;
        for (i = 0; i <= p->keynum && record[i] < key; i++) {
            if (record[i] == key) {
                found = true;
                return Result(p, i, true);
            }
        }
        q = p; p = p->child[i];
    }
    return Result(q, i, 0);

}