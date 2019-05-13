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

    RBNode* search(RBNode* node,string searchValue){

        while(++cmp && node) {
            if(++cmp && node->value < searchValue){
                node = node->right;

            }
            else if(++cmp && node->value > searchValue){
                node = node->left;
            }

            else {
                return node;

            }
        }

        return nullptr;
    }
    void inorder(RBNode* node){
        if(++cmp && node != nullptr){
            inorder(node->left);
            cout << node->value << " ";
            inorder(node->right);
        }
    }
    void leftRotate(RBNode* lNode){
        RBNode* rNode = lNode->right;
        if(++cmp && rNode){
            lNode->right = rNode->left;     mod++;
            if(++cmp && rNode->left){
                rNode->left->parent = lNode;     mod++;
            }
            rNode->parent = lNode->parent;     mod++;
        }
        if(++cmp && !lNode->parent){
            this->root = rNode;   mod++;
        }
        else if (++cmp && lNode == lNode->parent->left) {
            lNode->parent->left = rNode;    mod++;
        }
        else {
            lNode->parent->right = rNode;   mod++;
        }
        if(++cmp && rNode) {
            rNode->left = lNode;        mod++;
        }
        lNode->parent = rNode;     mod++;
    }

    void rightRotate(RBNode* rNode){
         RBNode* lNode = rNode->left;
        if(++cmp && lNode){
            rNode->left = lNode->right;     mod++;
            if(++cmp && lNode->right){
                lNode->right->parent = rNode;     mod++;
            }

            lNode->parent = rNode->parent;   mod++;
        }
        if(++cmp && !rNode->parent){
            this->root = lNode;   mod++;
        }
        else if(++cmp && rNode == rNode->parent->left){
            rNode->parent->left = lNode;   mod++;
        }
        else{
            rNode->parent->right = lNode;   mod++;
        }
        if(++cmp && lNode){
            lNode->right = rNode;   mod++;
        }
        rNode->parent = lNode;   mod++;
    }

    void insert(RBNode* newNode){

         RBNode* parentNode = nullptr;
         RBNode* tmpNode = root;
        while(++cmp && tmpNode){
            parentNode = tmpNode;
            if(++cmp && newNode->value < tmpNode->value)
                tmpNode = tmpNode->left;
            else
                tmpNode = tmpNode->right;
        }
        newNode->parent = parentNode;   mod++;
        if(++cmp && !parentNode){
            root = newNode;   mod++;
        }
        else if (++cmp && newNode->value < parentNode->value){
            parentNode->left = newNode;   mod++;
        }
        else{
            parentNode->right = newNode;   mod++;
        }
        newNode->color = RED;   mod++;
        insertFix(newNode);
    }
    void insertFix( RBNode* newNode){
        while(++cmp && newNode->parent && ++cmp &&  newNode->parent->color == RED){
            if(++cmp && newNode->parent == newNode->parent->parent->left){
                 RBNode* rSon = newNode->parent->parent->right;
                if(++cmp && rSon && ++cmp &&   rSon->color == RED){
                    newNode->parent->color = BLACK;             mod++;
                    rSon->color = BLACK;                         mod++;
                    newNode->parent->parent->color = RED;            mod++;
                    newNode = newNode->parent->parent;
                }
                else {
                    if(++cmp && newNode == newNode->parent->right){
                         newNode = newNode->parent;
                         leftRotate(newNode);
                    }
                    newNode->parent->color = BLACK;   mod++;
                    newNode->parent->parent->color = RED;   mod++;
                    rightRotate(newNode->parent->parent);
                }
            }
            else{
                 RBNode* lSon = newNode->parent->parent->left;
                if(++cmp && lSon && ++cmp && lSon->color == RED){
                    newNode->parent->color = BLACK;       mod++;
                    lSon->color = BLACK;                   mod++;
                    newNode->parent->parent->color = RED;       mod++;
                    newNode = newNode->parent->parent;
                }
                else {
                    if(++cmp && newNode == newNode->parent->left){
                        newNode = newNode->parent;
                        rightRotate(newNode);
                    }
                    newNode->parent->color = BLACK;       mod++;
                    newNode->parent->parent->color = RED;       mod++;
                    leftRotate(newNode->parent->parent);
                }
            }
        }
        this->root->color = BLACK;       mod++;
    }
    void transplant(RBNode* oldNode, RBNode* newNode){
        if (++cmp && !oldNode->parent){
            this->root = newNode;       mod++;
        }
        else if(++cmp && oldNode == oldNode->parent->left){
            oldNode->parent->left = newNode;       mod++;
        }
        else{
            oldNode->parent->right = newNode;       mod++;
        }
        if(++cmp && newNode){
            newNode->parent = oldNode->parent;       mod++;
        }
    }
     RBNode* min( RBNode* subRoot){
         RBNode* tmp = subRoot;
        while(++cmp && tmp->left)
            tmp = tmp->left;
        return tmp;
    }
    void del( RBNode* delNode){

         RBNode* sonNode;
         RBNode* tmpNode = delNode;
        Color prevColor = tmpNode->color;
        if(++cmp && !delNode->left){
            sonNode = delNode->right;
            transplant(delNode,delNode->right);
        }
        else if(++cmp && !delNode->right){
            sonNode = delNode->left;
            transplant(delNode,delNode->left);
        }
        else {
            tmpNode = min(delNode->right);
            prevColor = tmpNode->color;
            sonNode = tmpNode->right;
            if(++cmp && sonNode && ++cmp &&  tmpNode->parent == delNode){
                sonNode->parent = tmpNode;       mod++;
            }
            else{
                transplant(tmpNode,tmpNode->right);
                tmpNode->right = delNode->right;       mod++;
                if(++cmp && tmpNode->right){
                    tmpNode->right->parent = tmpNode;       mod++;
                }
            }
            transplant(delNode,tmpNode);
            tmpNode->left = delNode->left;       mod++;
            tmpNode->left->parent = tmpNode;       mod++;
            tmpNode->color = delNode->color;       mod++;
        }
        delete delNode;      ++mod;
        if(++cmp && prevColor == BLACK)
            delFix(sonNode);

    }
    void delFix( RBNode* node){
        while(++cmp && node
        && ++cmp &&  node != this->root
        && ++cmp && node->color == BLACK){
            if(++cmp && node == node->parent->left){
                 RBNode* broNode = node->parent->right;
                if(++cmp && broNode && ++cmp &&  broNode->color == RED){
                    broNode->color = BLACK;       mod++;
                    node->parent->color = RED;       mod++;
                    leftRotate(node->parent);
                    broNode = node->parent->right;
                }
                if(++cmp && broNode
                && ((++cmp &&  !broNode->left) || (++cmp && broNode->left->color == BLACK))
                && ((++cmp && !broNode->right) || (++cmp && broNode->right->color == BLACK))) {
                    broNode->color = RED;       mod++;
                    node = node->parent;
                }
                else{
                    if(++cmp && broNode && ((++cmp && !broNode->right) || (++cmp && broNode->right->color == BLACK))){
                        if(++cmp && broNode->left){
                            broNode->left->color = BLACK;       mod++;
                        }
                        broNode->color = RED;       mod++;
                        rightRotate(broNode);
                        broNode = node->parent->right;
                    }
                    if(++cmp && broNode) {
                        broNode->color = node->parent->color;       mod++;
                        if(++cmp && broNode->right){
                            broNode->right->color = BLACK;       mod++;
                        }


                    }
                    node->parent->color = BLACK;       mod++;

                    leftRotate(node->parent);
                    node = this->root;
                }
            }
            else{
                 RBNode* broNode = node->parent->left;
                if(++cmp && broNode && ++cmp &&  broNode->color == RED){
                    broNode->color = BLACK;       mod++;
                    node->parent->color = RED;       mod++;
                    rightRotate(node->parent);
                    broNode = node->parent->left;
                }
                if(++cmp && broNode
                   && ((++cmp &&  !broNode->left) || (++cmp && broNode->left->color == BLACK))
                   && ((++cmp && !broNode->right )|| (++cmp && broNode->right->color == BLACK))){
                    broNode->color = RED;       mod++;
                    node = node->parent;
                }
                else{
                    if(++cmp && broNode && ((++cmp && !broNode->left) || (++cmp && broNode->left->color == BLACK))){
                        if(++cmp && broNode->right){
                            broNode->right->color = BLACK;       mod++;
                        }
                        broNode->color = RED;       mod++;
                        leftRotate(broNode);
                        broNode = node->parent->left;
                    }
                    if(++cmp && broNode) {
                        broNode->color = node->parent->color;       mod++;
                        if(++cmp && broNode->left){
                            broNode->left->color = BLACK;       mod++;
                        }
                    }
                    node->parent->color = BLACK;       mod++;

                    rightRotate(node->parent);
                    node = this->root;
                }

            }

        }
        if(++cmp && node){
            node->color = BLACK;       mod++;
        }
    }
public:
    RBTree(){
        root = nullptr;
    }
    void insertWrapper(string input){
        cmp=0;
        mod=0;
        if (ispunct(input.back()))
            input.pop_back();
       auto newNode = new RBNode(input); ++mod;
       insert(newNode);

        insCmp+=cmp;
        insMod+=mod;
        insNum++;
    }
    void inorderWrapper(){
        inorder(root);
        cout << endl;
    }
    void searchWrapper(string input){
        cmp=0;

        search(root,input);
        srNum++;
        srCmp+=cmp;
    }
    void deleteWrapper(string input){
        cmp=0;
        mod=0;
        auto node = search(root,input);
        if(++cmp && node)
            del(node);
        delCmp+=cmp;
        delMod+=mod;
        delNum++;
    }


};
#endif //ZAD1_RBTREE_H
