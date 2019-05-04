#include <utility>

//
// Created by konra on 03.05.2019.
//

#ifndef ZAD1_BSTREE_H
#define ZAD1_BSTREE_H
#include "Tree.h"
#include <iostream>
using namespace std;
struct Node{
    explicit Node(string value){
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->value = std::move(value);
    }
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    string value;

};
class BSTree :public Tree{
    struct Node* root;


    void inorder(struct Node* node){
        if(node != nullptr){
            inorder(node->left);
            cout << node->value << endl;
            inorder(node->right);
        }
    }
    struct Node* search(struct Node* node,string searchValue){
        if(node == nullptr || node->value == searchValue)
            return node;
        if(searchValue < node->value)
            search(node->left,searchValue);
        else
            search(node->right,searchValue);
    }
    void insert(struct Node* insert){
        struct Node* tmp;
        struct Node* parent;
        parent = nullptr;
        tmp = root;
        while(tmp!= nullptr){
            parent = tmp;
            if(insert->value < tmp->value)
                tmp = tmp->left;
            else
                tmp = tmp->right;

        }
        insert->parent = parent;
        if(parent == nullptr)
            this->root = insert;
        else if(insert->value < parent->value)
            parent->left = insert;
        else
            parent->right = insert;
    }
    void transplant(struct Node* oldNode,struct Node* newNode){
        if (oldNode->parent == nullptr)
            this->root = newNode;
        else if(oldNode == oldNode->parent->left)
            oldNode->parent->left = newNode;
        else
            oldNode->parent->right = newNode;

        if(newNode != nullptr)
            newNode->parent = oldNode;
    }
    struct Node* min(struct Node* subRoot){
        struct Node* tmp = subRoot;
        while(tmp->left != nullptr)
            tmp = tmp->left;
        return tmp;
    }
    struct Node* succ(struct Node* prev){
        if( prev->right != nullptr)
            return min(prev->right);
        struct Node* tmp = prev->parent;
        while(tmp!= nullptr && prev != tmp->right) {
            prev = tmp;
            tmp = tmp->right;
        }
        return tmp;

    }
    void del(struct Node* delNode){
        if(delNode->left == nullptr)
            transplant(delNode,delNode->right);
        else if(delNode->right == nullptr)
            transplant(delNode,delNode->left);
        else{
            struct Node* minNode = min(delNode->right);
            if(minNode->parent != delNode){
                transplant(minNode,minNode->right);
                minNode->right = delNode->right;
                minNode->right->parent = minNode;
            }
            transplant(delNode,minNode);
            minNode->left = delNode->left;
            minNode->left->parent = minNode;

        }
        delete delNode;///////////////
    }

public:
    BSTree(){
        root = nullptr;
    }
};
#endif //ZAD1_BSTREE_H
