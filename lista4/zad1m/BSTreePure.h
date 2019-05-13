
#include <functional>
//
// Created by konra on 03.05.2019.
//

#ifndef ZAD1_BSTREE_H
#define ZAD1_BSTREE_H
#include "Tree.h"
#include <iostream>
using namespace std;
struct Node{
    Node(const string& value){
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->value = string(value);
    }
    Node* left;
    Node* right;
    Node* parent;
    string value;

};
class BSTree : public Tree {
    Node* root;


    void inorder( Node* node){
        if(node != nullptr){
            inorder(node->left);
            cout << node->value << "   ";
            inorder(node->right);
        }
    }
    Node* search( Node* node,string searchValue){
        while( node ) {
            if( node->value < searchValue )
                node = node->right;
            else if( node->value > searchValue )
                node = node->left;
            else return node;
        }
        return nullptr;
    }
    void insert( Node* insert){
        Node* tmp;
        Node* parent;
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
    void transplant( Node* oldNode, Node* newNode){
        if (oldNode->parent == nullptr)
            this->root = newNode;
        else if(oldNode == oldNode->parent->left)
            oldNode->parent->left = newNode;
        else
            oldNode->parent->right = newNode;

        if(newNode != nullptr)
            newNode->parent = oldNode->parent;
    }
    Node* min( Node* subRoot){
        Node* tmp = subRoot;
        while(tmp->left != nullptr)
            tmp = tmp->left;
        return tmp;
    }
    Node* succ( Node* prev){
        if( prev->right != nullptr)
            return min(prev->right);
        Node* tmp = prev->parent;
        while(tmp!= nullptr && prev != tmp->right) {
            prev = tmp;
            tmp = tmp->right;
        }
        return tmp;

    }
    void del( Node* delNode){
        if(delNode->left == nullptr)
            transplant(delNode,delNode->right);
        else if(delNode->right == nullptr)
            transplant(delNode,delNode->left);
        else{
            Node* minNode = min(delNode->right);
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
    void insertWrapper(string input){

        auto newNode = new Node(input);
        insert(newNode);
    }
    void inorderWrapper(){
        inorder(root);

        cout << endl;
    }
    void searchWrapper(string input){
        if(search(root,input) != nullptr)
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
    void deleteWrapper(string input){
        auto node = search(root,input);
        if(node != nullptr)
            del(node);
    }
};
#endif //ZAD1_BSTREE_H
