
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
        if(++cmp && node != nullptr){
            inorder(node->left);
            cout << node->value << "   ";
            inorder(node->right);
        }
    }
     Node* search( Node* node,string searchValue){
         while(++cmp && node ) {
             if(++cmp && node->value < searchValue )
                 node = node->right;
             else if(++cmp && node->value > searchValue )
                 node = node->left;
             else {
                 return node;
             }
         }
         return nullptr;
    }
    void insert( Node* insert){
         Node* tmp;
         Node* parent;
        parent = nullptr;
        tmp = root;
        while(++cmp && tmp!= nullptr){
            parent = tmp;
            if(++cmp && insert->value < tmp->value)
                tmp = tmp->left;
            else
                tmp = tmp->right;

        }
        insert->parent = parent;     mod++;
        if(++cmp && parent == nullptr){
            this->root = insert;     mod++;
        }
        else if(++cmp && insert->value < parent->value){
            parent->left = insert;     mod++;
        }
        else{
            parent->right = insert;     mod++;
        }

    }
    void transplant( Node* oldNode, Node* newNode){
        if (++cmp && oldNode->parent == nullptr){
            this->root = newNode;     mod++;
        }
        else if(++cmp && oldNode == oldNode->parent->left){
            oldNode->parent->left = newNode;     mod++;
        }
        else{
            oldNode->parent->right = newNode;     mod++;
        }

        if(++cmp && newNode != nullptr){
            newNode->parent = oldNode->parent;     mod++;
        }
    }
     Node* min( Node* subRoot){
         Node* tmp = subRoot;
        while(++cmp && tmp->left != nullptr)
            tmp = tmp->left;
        return tmp;
    }
     Node* succ( Node* prev){
        if(++cmp && prev->right != nullptr)
            return min(prev->right);
         Node* tmp = prev->parent;
        while(++cmp && tmp!= nullptr && prev != tmp->right) {
            prev = tmp;
            tmp = tmp->right;
        }
        return tmp;

    }
    void del( Node* delNode){
        if(++cmp && delNode->left == nullptr)
            transplant(delNode,delNode->right);
        else if(++cmp && delNode->right == nullptr)
            transplant(delNode,delNode->left);
        else{
             Node* minNode = min(delNode->right);
            if(++cmp && minNode->parent != delNode){
                transplant(minNode,minNode->right);
                minNode->right = delNode->right;     mod++;
                minNode->right->parent = minNode;     mod++;
            }
            transplant(delNode,minNode);
            minNode->left = delNode->left;     mod++;
            minNode->left->parent = minNode;     mod++;

        }
        delete delNode;     ++mod;
    }

public:
    BSTree(){
        root = nullptr;
    }
    void insertWrapper(string input){
        cmp=0;
        mod=0;
        if (ispunct(input.back()))
            input.pop_back();
        auto newNode = new Node(input);     ++mod;
        insert(newNode);

        insNum++;
        insCmp+=cmp;
        insMod+=mod;
    }
    void inorderWrapper(){
        inorder(root);

        cout << endl;
    }
    void searchWrapper(string input){
        cmp=0;
        search(root,input);
   /*         cout << 1 << endl;
        else
            cout << 0 << endl;*/
        srCmp+=cmp;
        srNum++;
    }
    void deleteWrapper(string input){
        cmp=0;
        mod=0;
        auto node = search(root,input);
        if(++cmp && node != nullptr)
            del(node);

        delNum++;
        delCmp+=cmp;
        delMod+=mod;
    }
};
#endif //ZAD1_BSTREE_H
