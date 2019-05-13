//
// Created by konra on 03.05.2019.
//
#include "Tree.h"

#ifndef ZAD1_SPLAYTREE_H
#define ZAD1_SPLAYTREE_H
class splayTree: public Tree{
private:
    Node* root = nullptr;
    void inorder( Node* node){
        if(node != nullptr){
            inorder(node->left);
            cout << node->value << " ";
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

    void leftRotate( Node* lNode){
        Node* rNode = lNode->right;
        if(rNode){
            lNode->right = rNode->left;
            if(rNode->left)
                rNode->left->parent = lNode;
            rNode->parent = lNode->parent;
        }
        if(lNode->parent ==nullptr )
            this->root = rNode;
        else if (lNode == lNode->parent->left)
            lNode->parent->left = rNode;
        else
            lNode->parent->right = rNode;
        if(rNode)
            rNode->left = lNode;
        lNode->parent = rNode;
    }

    void rightRotate( Node* rNode){
        Node* lNode = rNode->left;
        if(lNode){
            rNode->left = lNode->right;
            if(lNode->right)
                lNode->right->parent = rNode;
            lNode->parent = rNode->parent;
        }
        if(rNode->parent == nullptr)
            this->root = lNode;
        else if(rNode == rNode->parent->left)
            rNode->parent->left = lNode;
        else
            rNode->parent->right = lNode;
        if(lNode)
            lNode->right = rNode;
        rNode->parent = lNode;
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
    void splay( Node *node ) {
        while(node->parent) {
            if(!node->parent->parent) {
                if(node->parent->left == node) rightRotate(node->parent);
                else leftRotate( node->parent );
            } else if(node->parent->left == node && node->parent->parent->left == node->parent) {
                rightRotate( node->parent->parent );
                rightRotate( node->parent );
            } else if(node->parent->right == node && node->parent->parent->right == node->parent) {
                leftRotate(node->parent->parent );
                leftRotate(node->parent);
            } else if(node->parent->left == node && node->parent->parent->right == node->parent) {
                rightRotate(node->parent);
                leftRotate(node->parent);
            } else {
                leftRotate(node->parent);
                rightRotate(node->parent);
            }
        }
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

        splay(insert);
    }
    void del( Node* delNode){
        splay(delNode);

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

    Node* min( Node* subRoot){
        Node* tmp = subRoot;
        while(tmp->left)
            tmp = tmp->left;
        return tmp;
    }
public:
    void insertWrapper(string input){

        auto newNode = new Node(input);
        insert(newNode);
    }
    void inorderWrapper(){
        inorder(root);

        cout << endl;
    }
    void searchWrapper(string input){
        search(root,input);
    }
    void deleteWrapper(string input){
        auto node = search(root,input);
        if(node != nullptr)
            del(node);
    }
};
#endif //ZAD1_SPLAYTREE_H
