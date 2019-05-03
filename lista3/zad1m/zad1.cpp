#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include "../zad2/PriorityQueue.h"
#include "../zad2/graphs.h"
using namespace std;
int main(int argc, char* argv[])
{
    int commandNum,val,prio;
    cin >> commandNum;

    auto * pq = new PriorityQueue<int>();

    string command;
    while(commandNum > 0){
        cin >> command;
        if(command == "insert"){//switch
            cin >> val;
            cin >> prio;
            pq->insert(val, prio);
        }else if(command == "empty"){
            pq->empty();
        }else if(command == "top"){
            pq->top();
        }else if(command == "pop"){
            pq->pop();
        }else if(command == "priority"){
            cin >> val;
            cin >> prio;
            pq->priority(val, prio);
        }else if(command == "print"){
            pq->print();
        }



        commandNum--;
    }


}