#include <utility>

//
// Created by konra on 03.05.2019.
//

#ifndef ZAD1_RBTREE_H
#define ZAD1_RBTREE_H
#include <iostream>
#include "Tree.h"
using namespace std;
enum Color{
    BLACK,RED
};
struct RBNode{

    RBNode(string value){
        this->value = move(value);
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    RBNode* left;
    RBNode* right;
    RBNode* parent;
    string value;
    Color color;

};
class RBTree : public Tree{

    RBNode* root;

    RBNode* search(RBNode* node,string searchValue){\
        while(node) {
            if(node->value < searchValue){
                node = node->right;

            }
            else if(node->value > searchValue){
                node = node->left;
            }

            else return node;
        }
        return nullptr;
    }
    void inorder(RBNode* node){
        if(node != nullptr){
            inorder(node->left);
            cout << node->value << " ";
            inorder(node->right);
        }
    }
    void leftRotate(RBNode* lNode){
        RBNode* rNode = lNode->right;
        if(rNode){
            lNode->right = rNode->left;
            if(rNode->left)
                rNode->left->parent = lNode;
            rNode->parent = lNode->parent;
        }
        if(!lNode->parent)
            this->root = rNode;
        else if (lNode == lNode->parent->left)
            lNode->parent->left = rNode;
        else
            lNode->parent->right = rNode;
        if(rNode)
            rNode->left = lNode;
        lNode->parent = rNode;
    }

    void rightRotate(RBNode* rNode){
        RBNode* lNode = rNode->left;
        if(lNode){
            rNode->left = lNode->right;
            if(lNode->right)
                lNode->right->parent = rNode;

            lNode->parent = rNode->parent;
        }
        if(!rNode->parent)
            this->root = lNode;
        else if(rNode == rNode->parent->left)
            rNode->parent->left = lNode;
        else
            rNode->parent->right = lNode;
        if(lNode)
            lNode->right = rNode;
        rNode->parent = lNode;
    }

    void insert(RBNode* newNode){
        RBNode* parentNode = nullptr;
        RBNode* tmpNode = root;
        while(tmpNode){
            parentNode = tmpNode;
            if(newNode->value < tmpNode->value)
                tmpNode = tmpNode->left;
            else
                tmpNode = tmpNode->right;
        }
        newNode->parent = parentNode;
        if(!parentNode)
            root = newNode;
        else if (newNode->value < parentNode->value)
            parentNode->left = newNode;
        else
            parentNode->right = newNode;
        newNode->color = RED;
        insertFix(newNode);
    }
    void insertFix( RBNode* newNode){
        while(newNode->parent && newNode->parent->color == RED){
            if(newNode->parent == newNode->parent->parent->left){
                RBNode* rSon = newNode->parent->parent->right;
                if(rSon && rSon->color == RED){
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
                RBNode* lSon = newNode->parent->parent->left;
                if(lSon && lSon->color == RED){
                    newNode->parent->color = BLACK;
                    lSon->color = BLACK;
                    newNode->parent->parent->color = RED;
                    newNode = newNode->parent->parent;
                }
                else {
                    if(newNode == newNode->parent->left){
                        newNode = newNode->parent;
                        rightRotate(newNode);
                    }
                    newNode->parent->color = BLACK;
                    newNode->parent->parent->color = RED;
                    leftRotate(newNode->parent->parent);
                }
            }
        }
        this->root->color = BLACK;
    }
    void transplant(RBNode* oldNode, RBNode* newNode){
        if (!oldNode->parent)
            this->root = newNode;
        else if(oldNode == oldNode->parent->left)
            oldNode->parent->left = newNode;
        else
            oldNode->parent->right = newNode;
        if(newNode)
            newNode->parent = oldNode->parent;
    }
    RBNode* min( RBNode* subRoot){
        RBNode* tmp = subRoot;
        while(tmp->left)
            tmp = tmp->left;
        return tmp;
    }
    void del( RBNode* delNode){
        RBNode* sonNode;
        RBNode* tmpNode = delNode;
        Color prevColor = tmpNode->color;
        if(!delNode->left){
            sonNode = delNode->right;
            transplant(delNode,delNode->right);
        }
        else if(!delNode->right){
            sonNode = delNode->left;
            transplant(delNode,delNode->left);
        }
        else {
            tmpNode = min(delNode->right);
            prevColor = tmpNode->color;
            sonNode = tmpNode->right;
            if(sonNode && tmpNode->parent == delNode)
                sonNode->parent = tmpNode;
            else{
                transplant(tmpNode,tmpNode->right);
                tmpNode->right = delNode->right;
                if(tmpNode->right)
                    tmpNode->right->parent = tmpNode;
            }
            transplant(delNode,tmpNode);
            tmpNode->left = delNode->left;
            tmpNode->left->parent = tmpNode;
            tmpNode->color = delNode->color;
        }
        delete delNode;////////
        if(prevColor == BLACK)
            delFix(sonNode);
    }
    void delFix( RBNode* node){
        while(node && node != this->root && node->color == BLACK){
            if(node == node->parent->left){
                RBNode* broNode = node->parent->right;
                if(broNode && broNode->color == RED){
                    broNode->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    broNode = node->parent->right;
                }
                if(broNode
                   && ( !broNode->left || broNode->left->color == BLACK)
                   && (!broNode->right || broNode->right->color == BLACK)) {
                    broNode->color = RED;
                    node = node->parent;
                }
                else{
                    if(broNode && (!broNode->right || broNode->right->color == BLACK)){
                        if(broNode->left)
                            broNode->left->color = BLACK;
                        broNode->color = RED;
                        rightRotate(broNode);
                        broNode = node->parent->right;
                    }
                    if(broNode) {
                        broNode->color = node->parent->color;
                        if(broNode->right)
                            broNode->right->color = BLACK;


                    }
                    node->parent->color = BLACK;

                    leftRotate(node->parent);
                    node = this->root;
                }
            }
            else{
                RBNode* broNode = node->parent->left;
                if(broNode && broNode->color == RED){
                    broNode->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    broNode = node->parent->left;
                }
                if(broNode
                   && ( !broNode->left || broNode->left->color == BLACK)
                   && (!broNode->right || broNode->right->color == BLACK)) {
                    broNode->color = RED;
                    node = node->parent;
                }
                else{
                    if(broNode && (!broNode->left || broNode->left->color == BLACK)){
                        if(broNode->right)
                            broNode->right->color = BLACK;
                        broNode->color = RED;
                        leftRotate(broNode);
                        broNode = node->parent->left;
                    }
                    if(broNode) {
                        broNode->color = node->parent->color;
                        if(broNode->left)
                            broNode->left->color = BLACK;
                    }
                    node->parent->color = BLACK;

                    rightRotate(node->parent);
                    node = this->root;
                }

            }

        }
        if(node)
            node->color = BLACK;
    }
public:
    RBTree(){
        root = nullptr;
    }
    void insertWrapper(string input){
        auto newNode = new RBNode(input);
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
#endif //ZAD1_RBTREE_H
