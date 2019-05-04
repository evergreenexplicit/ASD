#include <utility>

//
// Created by konra on 03.05.2019.
//

#ifndef ZAD1_RBTREE_H
#define ZAD1_RBTREE_H
#include <iostream>
using namespace std;
enum Color{
    BLACK,RED
};
struct Node{

    Node(string value){
        this->value = move(value);
        left =nullptr;
        right = nullptr;
        parent = nullptr;
    }

    struct Node* left;
    struct Node* right;
    struct Node* parent;
    string value;
    Color color;

};
class RBTree : Tree{
    struct Node* root;

    void leftRotate(struct Node* lNode){
        struct Node* rNode = lNode->right;
        lNode->right = rNode->left;
        if(rNode->left != nullptr)
            rNode->left->parent = lNode;
        rNode->parent = lNode->parent;
        if(lNode->parent ==nullptr )
            this->root = rNode;
        else if (lNode == lNode->parent->left)
            lNode->parent->left = rNode;
        else
            lNode->parent->right = rNode;
        rNode->left = lNode;
        lNode->parent = rNode;
    }
    void rightRotate(struct Node* rNode){
        struct Node* lNode = rNode->left;
        rNode->left = lNode->right;
        if(lNode->right != nullptr)
            lNode->right->parent = rNode;
        lNode->parent = rNode->parent;
        if(rNode->parent == nullptr)
            this->root = lNode;
        else if(rNode == rNode->parent->left)
            rNode->parent->left = lNode;
        else
            rNode->parent->right = rNode;
        lNode->right = rNode;
        rNode->parent = lNode;
    }

    void insert(struct Node* newNode){
        struct Node* parentNode = nullptr;
        struct Node* tmpNode = root;
        while(tmpNode != nullptr){
            parentNode = tmpNode;
            if(newNode->value < tmpNode->value)
                tmpNode = tmpNode->left;
            else
                tmpNode = tmpNode->right;
        }
        newNode->parent = parentNode;
        if(parentNode == nullptr)
            root = newNode;
        else if (newNode->value < parentNode->value)
            parentNode->left = newNode;
        else
            parentNode->right = newNode;
        newNode->color = RED;
        insertFix(newNode);
    }
    void insertFix(struct Node* newNode){
        while(newNode->parent->color == RED){
            if(newNode->parent == newNode->parent->parent->left){
                struct Node* rSon = newNode->parent->parent->right;
                if(rSon->color == RED){
                    newNode->parent->color = BLACK;
                    rSon->color = BLACK;
                    newNode->parent->parent->color = RED;
                    newNode = newNode->parent->parent;
                }
                else {
                    if(newNode == newNode->parent->right){
                         newNode = newNode->parent;
                         leftRotate(newNode);
                    }
                    newNode->parent->color = BLACK;
                    newNode->parent->parent->color = RED;
                    rightRotate(newNode->parent->parent);
                }
            }
            else{
                struct Node* lSon = newNode->parent->parent->left;
                if(lSon->color == RED){
                    newNode->parent->color = BLACK;
                    lSon->color = BLACK;
                    newNode->parent->parent->color = RED;
                    newNode = newNode->parent->parent;
                }
                else {
                    if(newNode == newNode->parent->left){
                        newNode = newNode->parent;
                        rightRotate(newNode); //TODO WARN ROTATES
                    }
                    newNode->parent->color = BLACK;
                    newNode->parent->parent->color = RED;
                    leftRotate(newNode->parent->parent);
                }
            }
        }
        this->root->color = BLACK;
    }
    void transplant(struct Node* oldNode,struct Node* newNode){
        if (oldNode->parent == nullptr)
            this->root = newNode;
        else if(oldNode == oldNode->parent->left)
            oldNode->parent->left = newNode;
        else
            oldNode->parent->right = newNode;
        newNode->parent = oldNode;
    }
    struct Node* min(struct Node* subRoot){
        struct Node* tmp = subRoot;
        while(tmp->left != nullptr)
            tmp = tmp->left;
        return tmp;
    }
    void del(struct Node* delNode){
        struct Node* sonNode;
        struct Node* tmpNode = delNode;
        Color prevColor = tmpNode->color;
        if(delNode->left == nullptr){
            sonNode = delNode->right;
            transplant(delNode,delNode->right);
        }
        else if(delNode->right == nullptr){
            sonNode = delNode->left;
            transplant(delNode,delNode->left);
        }
        else {
            tmpNode = min(delNode->right);
            prevColor = tmpNode->color;
            sonNode = tmpNode->right;
            if(tmpNode->parent == delNode)
                sonNode->parent = tmpNode;
            else{
                transplant(tmpNode,tmpNode->right);
                tmpNode->right = delNode->right;
                tmpNode->right->parent = tmpNode;
            }
            transplant(delNode,tmpNode);
            tmpNode->left = delNode->left;
            tmpNode->left->parent = tmpNode;
            tmpNode->color = delNode->color;
        }
        if(prevColor == BLACK)
            delFix(sonNode);
    }
    void delFix(struct Node* node){
        while(node != this->root && node->color == BLACK){
            if(node == node->parent->left){
                struct Node* broNode = node->parent->right;
                if(broNode->color == RED){
                    broNode->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    broNode = node->parent->right;
                }
                if(broNode->left->color == BLACK
                && broNode->right->color == BLACK) {
                    broNode->color = RED;
                    node = node->parent;
                }
                else{
                    if(broNode->right->color == BLACK){
                        broNode->left->color = BLACK;
                        broNode->color = RED;
                        rightRotate(broNode);
                        broNode = node->parent->right;
                    }
                    broNode->color = node->parent->color;
                    node->parent->color = BLACK;
                    broNode->right->color = BLACK;
                    leftRotate(node->parent);
                    node = this->root;
                }
            }
            else{
                // TODO REVERSE

            }

        }
        node->color = BLACK;
    }



};
#endif //ZAD1_RBTREE_H
