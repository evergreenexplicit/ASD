#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "timer.h"
#include "graphsMST.h"
#include "PriorityQueue.h"
int main(int argc, char* argv[]) {
    int numV, numE, u,v,start;
    double weight;
    cin >> numV;
    Graph *g = new Graph(numV);
    cin >> numE;

    while(numE>0){
        cin >> u;
        cin >> v;
        cin >> weight;
        g->add_edge(u-1,v-1,weight);
        g->add_edge(v-1,u-1,weight);
        numE--;
    }
    string s;
    if(argc == 2){
        s = argv[1];
    }
    if(s == "-k"){
        auto t = Timer::start();
        g->krusgal();
        auto t1 = Timer::stop(t);
        cout << "krusgal" <<endl;
        g->print();
        cout << "time in ms  = " << t1 << endl;
    }else if(s == "-p"){
        auto t = Timer::start();
        g->prim();
        auto t1 = Timer::stop(t);
        cout << "prim" <<endl;
        g->print();
        cout << "time in ms  = " << t1 << endl;
    }
}