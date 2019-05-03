//
// Created by konra on 25.04.2019.
//

#ifndef ZAD1M_PRIORITYQUEUE_H
#define ZAD1M_PRIORITYQUEUE_H
#include <iostream>

#include<vector>
#include<string>


using namespace std;
template<class T>
struct Node {
    double priority;
    T value;
    Node(T value,double priority){
        this->value = value;
        this->priority = priority;
    }
};
template <class T>
class PriorityQueue{

    int size;
    std::vector<Node<T>> list;
public:
    PriorityQueue(){
        size = 0;

    }

    bool isEmpty(){
        return size < 1;
    }

    T extract_min(){
        T min = list[0].value;
        list[0] = list[size-1];
        list.pop_back();
        size--;
        heapify(0);
        return min;
    }

private:
    int parent(int idx){
        return idx/2;
    }
    int leftChild(int idx){
        return 2*idx;
    }
    int rightChild(int idx){
        return 2*idx+1;
    }
    void heapify(int idx){
        int left = leftChild(idx);
        int right = rightChild(idx);
        int temp;
        if(left <=size-1 &&  list[left].priority < list[right].priority)
            temp = left;
        else
            temp = idx;

        if(right <= size-1 && list[right].priority  < list[temp].priority)
            temp = right;

        if(temp != idx){
            std::swap(list[idx],list[temp]);
            heapify(temp);
        }

    }


    T min(){
        return list[0].value;
    }

public:

    void top(){
        if(isEmpty())
            std::cout << endl;
        else
            std::cout << min() << endl;
    }
    void pop(){
        if(isEmpty())
            std::cout << endl;
        else
            std::cout << extract_min() << endl;
    }


    void insert(T value, double priority){
        size++;

        struct Node<T>* node = new Node<T>(value,priority);
        list.push_back(*node);

        int temp = size-1;
        while (temp > 0 && list[parent(temp)].priority > priority){
            list[temp] = list[parent(temp)];
            temp = parent(temp);

        }
        list[temp] = *node;
    }

    void priority(T value, double priority){
        int temp;
        for(temp = 0;temp<size;temp++){
            if(list[temp].value == value && list[temp].priority > priority){
                del(temp);
                insert(value,priority);
                temp--;
            }

        }


    }
    void del(int idx){
        if(idx>=size )
            return;
        list[idx] = list[size-1];
        list.pop_back();////////////////
        size--;
        heapify(idx);
    }
    void empty(){
        std::cout << isEmpty() << endl;

    }
    void getSize(){
        std::cout << list.size() << endl;
    }
    void print(){
        for(int i = 0;i<size;i++){
            std::cout << "(" << list[i].value << "," << list[i].priority << ") ";
        }
        std::cout << endl;
    }

};

#endif //ZAD1M_PRIORITYQUEUE_H
