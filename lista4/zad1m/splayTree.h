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
        if(++cmp &&node != nullptr){
            inorder(node->left);
            cout << node->value << " ";
            inorder(node->right);
        }
    }

    Node* search( Node* node,string searchValue){
        while(++cmp &&  node ) {
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

    void leftRotate( Node* lNode){
        Node* rNode = lNode->right;
        if(++cmp &&rNode){
            lNode->right = rNode->left;     mod++;
            if(++cmp &&rNode->left){
                rNode->left->parent = lNode;     mod++;
            }
            rNode->parent = lNode->parent;     mod++;
        }
        if(++cmp &&lNode->parent ==nullptr ){
            this->root = rNode;     mod++;
        }
        else if (++cmp &&lNode == lNode->parent->left){
            lNode->parent->left = rNode;     mod++;
        }
        else{
            lNode->parent->right = rNode;     mod++;
        }
        if(++cmp &&rNode){
            rNode->left = lNode;     mod++;
        }
        lNode->parent = rNode;     mod++;
    }

    void rightRotate( Node* rNode){
        Node* lNode = rNode->left;
        if(++cmp &&lNode){
            rNode->left = lNode->right;     mod++;
            if(lNode->right){
                lNode->right->parent = rNode;     mod++;
            }
            lNode->parent = rNode->parent;     mod++;
        }
        if(++cmp &&rNode->parent == nullptr){
            this->root = lNode;     mod++;
        }
        else if(++cmp &&rNode == rNode->parent->left){
            rNode->parent->left = lNode;     mod++;
        }
        else{
            rNode->parent->right = lNode;     mod++;
        }
        if(++cmp && lNode){
            lNode->right = rNode;     mod++;
        }
        rNode->parent = lNode;     mod++;
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
    void splay( Node *node ) {
        while(++cmp && node->parent) {
            if(++cmp && !node->parent->parent) {
                if(++cmp && node->parent->left == node)
                    rightRotate(node->parent);
                else
                    leftRotate( node->parent );
            } else if(++cmp && node->parent->left == node
            && ++cmp && node->parent->parent->left == node->parent) {
                rightRotate( node->parent->parent );
                rightRotate( node->parent );
            } else if(++cmp && node->parent->right == node
            &&++cmp &&  node->parent->parent->right == node->parent) {
                leftRotate(node->parent->parent );
                leftRotate(node->parent);
            } else if(++cmp && node->parent->left == node
            && ++cmp &&  node->parent->parent->right == node->parent) {
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

        splay(insert);
    }
    void del( Node* delNode){
        splay(delNode);

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

    Node* min( Node* subRoot){
        Node* tmp = subRoot;
        while(++cmp && tmp->left)
            tmp = tmp->left;
        return tmp;
    }
public:
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
        srNum++;
        srCmp+=cmp;
    }
    void deleteWrapper(string input){
        cmp=0;
        mod=0;
        auto node = search(root,input);
        if(node != nullptr)
            del(node);

        delNum++;
        delCmp+=cmp;
        delMod+=mod;
    }
};
#endif //ZAD1_SPLAYTREE_H
