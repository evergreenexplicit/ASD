//
// Created by konra on 03.05.2019.
//

#ifndef ZAD1_TREE_H
#define ZAD1_TREE_H

#include <iostream>

class Tree {
virtual void insert(struct Node* ) = 0;
virtual void del(struct Node*) = 0;
virtual struct Node* search(struct Node* ,std::string) = 0;
virtual void inorder(struct Node*) = 0;
};


#endif //ZAD1_TREE_H
